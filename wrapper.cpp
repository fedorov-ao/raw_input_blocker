/*
*  MIT License
*
*  Copyright (c) 2025 Alexander Fedorov
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
*/

#include <string>
#include <sstream>
#include <fstream>
#include <chrono>
#include <stdexcept>
#include <cassert>

#include "logging.hpp"
#include "config.hpp"

#undef _WIN32_WINNT
#define _WIN32_WINNT 0x1234
#define _USER32_
#undef STRICT

/* Headers that depend on Windows-related stuff must be included after above #defines and #undef */
#include "user32.hpp"
#include "vkeys.hpp"
#include "mingw.thread.h"
#include "mingw.mutex.h"

/* raw input filter */
class RawInputTest
{
public:
  virtual bool test(PRAWINPUT) =0;
  virtual ~RawInputTest() {}
};


class RawInputFilter : public APIUser32
{
public:
  virtual UINT GetRawInputData (HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader);
  virtual UINT GetRawInputBuffer (PRAWINPUT pData, PUINT pcbSize, UINT cbSizeHeader);

  void set_test(std::shared_ptr<RawInputTest> const & spRawInputTest);

  RawInputFilter(std::string const & dllPath, std::shared_ptr<RawInputTest> const & spRawInputTest=nullptr);

private:
  UINT fill_filtered_(UINT cbSizeHeader);

  std::shared_ptr<RawInputTest> spRawInputTest_;
  typedef std::vector<uint8_t> buffer_t;
  buffer_t buffer_, filtered_;
  buffer_t::value_type * pCurrentFiltered_, * pEndFiltered_;
};


UINT RawInputFilter::GetRawInputData(HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
{
  auto r = APIUser32::GetRawInputData(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);
  if (r != 0)
  {
    //if (uiCommand == RID_HEADER)
    //  lpHeader = reinterpret_cast<LPRAWINPUTHEADER>(pData);
    if (uiCommand == RID_INPUT)
    {
      auto pRawInput = reinterpret_cast<LPRAWINPUT>(pData);
      if (spRawInputTest_ && !spRawInputTest_->test(pRawInput))
        return 0;
    }
  }
  return r;
}


UINT RawInputFilter::GetRawInputBuffer (PRAWINPUT pData, PUINT pcbSize, UINT cbSizeHeader)
{
  static const UINT er = static_cast<UINT const>(-1);

  if (pCurrentFiltered_ == pEndFiltered_ && fill_filtered_(cbSizeHeader) == er)
  {
    *pcbSize = 0;
    return er;
  }

  if (pData == NULL)
  {
    *pcbSize = pEndFiltered_ - pCurrentFiltered_;
    return 0;
  }

  uint8_t * pBeginData = reinterpret_cast<uint8_t *>(pData);
  uint8_t * pEndData = pBeginData + *pcbSize;
  uint8_t * pCurrentData = pBeginData;
  UINT nMessages = 0;
  *pcbSize = 0;

  while (pCurrentFiltered_ < pEndFiltered_)
  {
    UINT const size = reinterpret_cast<PRAWINPUT>(pCurrentFiltered_)->header.dwSize;

    if (pEndData - pCurrentData < size)
    {
      if (nMessages == 0)
      {
        SetLastError(ERROR_INSUFFICIENT_BUFFER);
        nMessages = static_cast<UINT>(-1);
      }
      break;
    }

    memcpy(pCurrentData, pCurrentFiltered_, size);
    pCurrentFiltered_ += size;
    pCurrentData += size;
    *pcbSize += size;
    nMessages += 1;
  }

  logging::log("wrapper", logging::LogLevel::debug, "nMessages: ", nMessages);
  return nMessages;
}


void RawInputFilter::set_test(std::shared_ptr<RawInputTest> const & spRawInputTest)
{
  spRawInputTest_ = spRawInputTest;
}


RawInputFilter::RawInputFilter(std::string const & dllPath, std::shared_ptr<RawInputTest> const & spRawInputTest)
  : APIUser32(dllPath), spRawInputTest_(spRawInputTest),
    buffer_(), filtered_(), pCurrentFiltered_(nullptr), pEndFiltered_(nullptr)
{}


UINT RawInputFilter::fill_filtered_(UINT cbSizeHeader)
{
  static const UINT er = static_cast<UINT const>(-1);
  UINT cbSize = 0;
  UINT r = APIUser32::GetRawInputBuffer(NULL, &cbSize, cbSizeHeader);
  //TODO Check if GetRawInputBuffer() returns (UINT)-1 when checking for buffer size.
  if (r == er && GetLastError() != ERROR_INSUFFICIENT_BUFFER)
    return er;
  logging::log("wrapper", logging::LogLevel::debug, "requested buffer size: ", cbSize);
  /* When running under Wine 8.0, GetRawInputBuffer() writes incorrect requested buffer size in cbSize
     if first argument is NULL. When actually trying to read data in user-supplied buffer (ptr to which
     is supplied in first argument, GetRawInputBuffer() returns (UINT)-1 and sets last error to
     ERROR_INSUFFICIENT_BUFFER. So the following loop tries to guess needed buffer size by doubling it
     on failure. */
  for (int i = 0; i < 3; ++i)
  {
    buffer_.resize(cbSize);
    r = APIUser32::GetRawInputBuffer(reinterpret_cast<PRAWINPUT>(buffer_.data()), &cbSize, cbSizeHeader);
    if (r != er)
      break;
    if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
      cbSize *= 2;
    else
      return er;
  }
  uint8_t * ptr = buffer_.data();
  uint8_t const * end = ptr + cbSize;
  logging::log("wrapper", logging::LogLevel::debug, "buffer size: ", buffer_.size(), "; r: ", r, "; cbSize: ", cbSize);
  filtered_.clear();
  for (UINT i = 0; i < r; ++i)
  {
    PRAWINPUT current = reinterpret_cast<PRAWINPUT>(ptr);
    if (ptr > end)
    {
      logging::log("wrapper", logging::LogLevel::error, "message ", i, " pointer out of bounds");
      return er;
    }
    UINT const size = current->header.dwSize;
    if (size < cbSizeHeader)
    {
      logging::log("wrapper", logging::LogLevel::error, "message ", i, " size does not match");
      return er;
    }

    if (spRawInputTest_ && spRawInputTest_->test(current))
    {
      logging::log("wrapper", logging::LogLevel::debug, "accepting message ", i);
      filtered_.insert(filtered_.end(), ptr, ptr + size);
    }
    else
      logging::log("wrapper", logging::LogLevel::debug, "skipping message ", i);

    ptr += size;
  }
  logging::log("wrapper", logging::LogLevel::debug, "filtered size: ", filtered_.size());
  pCurrentFiltered_ = filtered_.data();
  pEndFiltered_ = pCurrentFiltered_ + filtered_.size();
}


RawInputFilter * g_pRawInputFilter = nullptr;


class CompositeRawInputTest : public RawInputTest
{
public:
  typedef std::function<bool(bool,bool)> combine_t;

  virtual bool test(PRAWINPUT pRawInput);

  void add(std::shared_ptr<RawInputTest> const & spChild);

  CompositeRawInputTest(combine_t const & combine, bool initial=true);

private:
  combine_t combine_;
  bool initial_;
  std::vector<std::shared_ptr<RawInputTest> > children_;
};


bool CompositeRawInputTest::test(PRAWINPUT pRawInput)
{
  auto r = initial_;
  for (auto & spChild : children_)
    r = combine_(r, spChild->test(pRawInput));
  return r;
}


void CompositeRawInputTest::add(std::shared_ptr<RawInputTest> const & spChild)
{
  children_.push_back(spChild);
}


CompositeRawInputTest::CompositeRawInputTest(combine_t const & combine, bool initial)
  : combine_(combine), initial_(initial), children_()
{}


class DeviceHandleRawInputTest : public RawInputTest
{
public:
  virtual bool test(PRAWINPUT pRawInput);

  void set_state(bool state);
  bool get_state() const;
  void push_state(bool state);
  void pop_state();

  DeviceHandleRawInputTest(HANDLE handle, bool state=true);

private:
  typedef std::recursive_mutex mutex_t;
  typedef std::unique_lock<mutex_t> lock_t;

  HANDLE const handle_;
  bool state_;
  std::vector<bool> states_;
  mutable mutex_t mutex_;
};


bool DeviceHandleRawInputTest::test(PRAWINPUT pRawInput)
{
  lock_t l (mutex_);

  if (pRawInput->header.hDevice == handle_ && state_ == false)
    return false;
  else
    return true;
}

void DeviceHandleRawInputTest::set_state(bool state)
{
  lock_t l (mutex_);
  state_ = state;
  logging::log("wrapper", logging::LogLevel::debug, "state: ", state_);
}


bool DeviceHandleRawInputTest::get_state() const
{
  lock_t l (mutex_);
  return state_;
}


void DeviceHandleRawInputTest::push_state(bool state)
{
  lock_t l (mutex_);
  states_.push_back(state_);
  state_ = state;
  logging::log("wrapper", logging::LogLevel::debug, "state: ", state_);
}


void DeviceHandleRawInputTest::pop_state()
{
  lock_t l (mutex_);
  state_ = states_.back();
  logging::log("wrapper", logging::LogLevel::debug, "state: ", state_);
  states_.pop_back();
}


DeviceHandleRawInputTest::DeviceHandleRawInputTest(HANDLE handle, bool state)
  : handle_(handle), state_(state), states_(), mutex_()
{}


/* Key map */
enum class KeyEventType : int { press=0, release=1 };


KeyEventType name2ket(char const * name)
{
  static struct { char const * name; KeyEventType ket; } const n2k[] = { { "press", KeyEventType::press }, { "release", KeyEventType::release } };
  for (auto const & p : n2k)
    if (std::strcmp(p.name, name) == 0)
      return p.ket;
  throw std::runtime_error("Invalid key event type");
}


char const * ket2name(KeyEventType ket)
{
  switch(ket)
  {
    case KeyEventType::press:
      return "pressed";
    case KeyEventType::release:
      return "released";
    default:
      return "invalid";
  }
}


class GKSKeyMap
{
public:
  typedef UINT key_t;
  typedef std::function<void()> callback_t;

  void update();

  unsigned int add(key_t key, KeyEventType ket, callback_t const & cb);
  void remove(unsigned int id);

  GKSKeyMap();
  ~GKSKeyMap() =default;

private:
  struct Data
  {
    typedef std::map<int, std::map<unsigned int, callback_t> > callbacks_t;

    callbacks_t callbacks;
    bool state;

    Data();
  };

  std::map<key_t, Data> data_;
  unsigned int id_ = 0;
  std::map<unsigned int, std::pair<key_t, KeyEventType> > ids_;
};


void GKSKeyMap::update()
{
  logging::log("wrapper", logging::LogLevel::debug, "GKSKeyMap::update()");
  for (auto & p : data_)
  {
    auto const & key = p.first;
    bool currentState = GetKeyState(key) & 0x8000;
    logging::log("wrapper", logging::LogLevel::debug, "key ", key2name(key), ": state: ", currentState);
    auto & prevState = p.second.state;
    if (currentState != prevState)
    {
      auto const ket = (currentState && !prevState) ? KeyEventType::press : KeyEventType::release;
      for (auto & cb : p.second.callbacks[static_cast<int>(ket)])
        cb.second();
      logging::log("wrapper", logging::LogLevel::debug, "key ", key2name(key), " ", ket2name(ket));
      prevState = currentState;
    }
  }
}


unsigned int GKSKeyMap::add(GKSKeyMap::key_t key, KeyEventType ket, GKSKeyMap::callback_t const & cb)
{
  auto id = ++id_;
  auto it = data_.find(key);
  if (it == data_.end())
    data_[key] = Data();
  data_[key].callbacks[static_cast<int>(ket)][id] = cb;
  ids_[id] = decltype(ids_)::mapped_type(key, ket);
  return id;
}


void GKSKeyMap::remove(unsigned int id)
{
  auto const & p = ids_[id];
  data_[p.first].callbacks[static_cast<int>(p.second)].erase(id);
}


GKSKeyMap::GKSKeyMap() : data_()
{}


GKSKeyMap::Data::Data() : callbacks(), state(false)
{
  KeyEventType kets[] = { KeyEventType::press, KeyEventType::release };
  for (auto ket : kets)
    callbacks[static_cast<int>(ket)] = callbacks_t::mapped_type();
}

config::config_t g_config;

void init_config()
{
  auto configPath = "user32.cfg";
  std::ifstream configStream (configPath);
  if (!configStream.is_open())
    throw std::runtime_error(stream_to_str("Failed to load config from: ", configPath));
  g_config = nlohmann::json::parse(configStream);
}


void init_log()
{
  auto formatter = [](logging::LogMessage const & lm)
  {
    static char const fmt[] = "%H:%M:%S";
    size_t const n = 128;
    char timeCstr[n] = {0};
    auto time = std::localtime(&lm.time);
    std::strftime(timeCstr, n, fmt, time);
    return stream_to_str("(", lm.source, ") <", timeCstr, "> [", lm.level, "] ", lm.msg);
  };
  auto const logPath = "user32.log";
  auto spLogFileSteam = std::make_shared<std::fstream>(logPath, std::ios::out|std::ios::trunc);
  auto streamHolder = [spLogFileSteam]() -> std::fstream& { return *spLogFileSteam; };
  auto spLogPrinter = std::make_shared<logging::StreamLogPrinter>(formatter, streamHolder);
  logging::root_logger().add_printer(spLogPrinter);
  auto logLevel = logging::n2ll(config::get_d<std::string>(g_config, "logLevel", "DEBUG"));
  logging::root_logger().set_level(logLevel);
  logging::log("init", logging::LogLevel::info, "Logging initialized");
}


struct RawInputDeviceProps
{
  HANDLE hDevice;
  DWORD dwType;
  std::string name;
  union
  {
    RID_DEVICE_INFO_MOUSE    mouse;
    RID_DEVICE_INFO_KEYBOARD keyboard;
    RID_DEVICE_INFO_HID      hid;
  };
};

std::vector<RawInputDeviceProps> get_raw_input_device_props()
{
  std::vector<RAWINPUTDEVICELIST> deviceLists;
  UINT nDevices = 0;
  std::size_t const szRawInputDeviceList = sizeof(RAWINPUTDEVICELIST);
  while (true)
  {
    if (GetRawInputDeviceList(NULL, &nDevices, szRawInputDeviceList) != 0)
      throw std::runtime_error("Failed to get number of raw input devices");
    deviceLists.resize(nDevices);
    nDevices = GetRawInputDeviceList(deviceLists.data(), &nDevices, szRawInputDeviceList);
    if (nDevices == (UINT)-1)
    {
      if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        throw std::runtime_error("Failed to get raw input device list");
      continue;
    }
    break;
  }

  std::vector<RawInputDeviceProps> deviceProps;
  for (auto const & deviceList : deviceLists)
  {
    RawInputDeviceProps ridp;
    ridp.hDevice = deviceList.hDevice;
    ridp.dwType = deviceList.dwType;
    UINT nName;
    if (GetRawInputDeviceInfoA(ridp.hDevice, RIDI_DEVICENAME, NULL, &nName) < 0)
      throw std::runtime_error("Failed to get device name length");
    std::vector<char> temp (nName);
    if (GetRawInputDeviceInfoA(ridp.hDevice, RIDI_DEVICENAME, temp.data(), &nName) < 0)
      throw std::runtime_error("Failed to get device name");
    ridp.name = temp.data();
    RID_DEVICE_INFO rdi;
    UINT cbRdi = sizeof(rdi);
    rdi.cbSize = cbRdi;
    if (GetRawInputDeviceInfoA(ridp.hDevice, RIDI_DEVICEINFO, &rdi, &cbRdi) < 0)
      throw std::runtime_error("Failed to get device info");
    if (rdi.dwType == RIM_TYPEMOUSE)
      ridp.mouse = rdi.mouse;
    else if (rdi.dwType == RIM_TYPEKEYBOARD)
      ridp.keyboard = rdi.keyboard;
    else if (rdi.dwType == RIM_TYPEHID)
      ridp.hid = rdi.hid;
    else
      assert(false);
    deviceProps.push_back(ridp);
  }

  return deviceProps;
}


char const * devtype2name(DWORD devType)
{
  switch (devType)
  {
    case RIM_TYPEMOUSE:
      return "mouse";
    case RIM_TYPEKEYBOARD:
      return "keyboard";
    case RIM_TYPEHID:
      return "hid";
    default:
      return "unknown";
  }
}


void print_raw_input_devices()
{
  logging::log("wrapper", logging::LogLevel::info, "===Raw input devices===");
  auto deviceProps = get_raw_input_device_props();
  std::stringstream ss;
  for (auto const & dp : deviceProps)
  {
    ss.str("");
    ss.clear();
    auto name = dp.name;
    std::replace(name.begin(), name.end(), '\\', '/');
    ss << "name: \"" <<  name << "\"; type: " << dp.dwType << " (" << devtype2name(dp.dwType) << "); ";

    if (dp.dwType == RIM_TYPEMOUSE)
    {
      auto const & mouse = dp.mouse;
      ss << "buttons: " << mouse.dwNumberOfButtons << "; sample rate: " << mouse.dwSampleRate;
      if (mouse.fHasHorizontalWheel)
        ss << "; has horizontal wheel";
    }
    else if (dp.dwType == RIM_TYPEKEYBOARD)
    {
      auto const & keyboard = dp.keyboard;
      ss << "mode: " << keyboard.dwKeyboardMode << "; function keys: " << keyboard.dwNumberOfFunctionKeys
         << "; indicators: " << keyboard.dwNumberOfIndicators << "; total keys: " << keyboard.dwNumberOfKeysTotal; 
    }
    else if (dp.dwType == RIM_TYPEHID)
    {
      auto const & hid = dp.hid;
      ss << std::hex<< "vendor id: " << hid.dwVendorId << "; product id: " << hid.dwProductId
         << "; usage page: " << hid.usUsagePage << "; usage: " << hid.usUsage;
    }

    logging::log("wrapper", logging::LogLevel::info, ss.str());
  }
  logging::log("wrapper", logging::LogLevel::info, "=======================");
}


GKSKeyMap g_keyMap;

void init_raw_input_filter()
{
  logging::log("wrapper", logging::LogLevel::debug, "init_raw_input_filter()");

  std::map<std::string, HANDLE> nameToHandle;
  auto deviceProps = get_raw_input_device_props();
  for (auto const & dp : deviceProps)
    nameToHandle[dp.name] = dp.hDevice;

  auto spCompositeRawInputTest = std::make_shared<CompositeRawInputTest>(std::logical_and<bool>(), true);
  std::map<HANDLE, std::shared_ptr<DeviceHandleRawInputTest> > handleToRawInputTest;
  auto make_test =
    [&spCompositeRawInputTest, &handleToRawInputTest](HANDLE hDevice, bool state=true)
    {
      std::shared_ptr<DeviceHandleRawInputTest> spRawInputTest;
      auto it = handleToRawInputTest.find(hDevice);
      if (it == handleToRawInputTest.end())
      {
        spRawInputTest = std::make_shared<DeviceHandleRawInputTest>(hDevice, state);
        handleToRawInputTest[hDevice] = spRawInputTest;
        spCompositeRawInputTest->add(spRawInputTest);
      }
      else
        spRawInputTest = it->second;
      return spRawInputTest;
    };

  if (g_config.contains("devices"))
  {
    logging::log("init", logging::LogLevel::debug, "Processing \"devices\"");
    for (auto const el : config::get(g_config, "devices").items())
    {
      auto const & alias = el.key();
      auto const & di = el.value();
      auto const devName = config::get_escaped_string(di, "name");
      auto const & devHandle = nameToHandle[devName];
      nameToHandle[alias] = devHandle;
      auto const state = config::get_d<bool>(di, "state", true);
      auto const spRawInputTest = make_test(devHandle, state);
      logging::log("init", logging::LogLevel::debug, "devName: ", devName, "; alias: ", alias, "; devHandle: ", devHandle, "; spRawInputTest: ", spRawInputTest);
    }
  }

  if (g_config.contains("bindings"))
  {
    logging::log("init", logging::LogLevel::debug, "Processing \"bindings\"");
    auto const & bindings = config::get(g_config, "bindings"); 
    for (auto const & binding : bindings)
    {
      auto const & on = config::get(binding, "on");
      auto const key = name2key(config::get<std::string>(on, "key").c_str());
      auto const ket = name2ket(config::get<std::string>(on, "event").c_str());

      auto const & do_ = config::get(binding, "do");
      auto const & devName = config::get_escaped_string(do_, "name");
      HANDLE const & devHandle = nameToHandle[devName];
      std::shared_ptr<DeviceHandleRawInputTest> spRawInputTest = make_test(devHandle);
      logging::log("init", logging::LogLevel::debug, "name: ", devName, "; devHandle: ", devHandle, "; spRawInputTest:", spRawInputTest);

      std::function<void()> action;
      auto const & actionName = config::get<std::string>(do_, "action");
      if (actionName == "enable")
        action = [spRawInputTest]() { spRawInputTest->set_state(true); };
      else if (actionName == "disable")
        action = [spRawInputTest]() { spRawInputTest->set_state(false); };
      else if (actionName == "toggle")
        action = [spRawInputTest]() { spRawInputTest->set_state(!spRawInputTest->get_state()); };
      else if (actionName == "set_state")
      {
        auto const state = config::get<bool>(do_, "state");
        action = [spRawInputTest, state]() { spRawInputTest->set_state(state); };
      }
      else if (actionName == "push_state")
      {
        auto const state = config::get<bool>(do_, "state");
        action = [spRawInputTest, state]() { spRawInputTest->push_state(state); };
      }
      else if (actionName == "pop_state")
        action = [spRawInputTest]() { spRawInputTest->pop_state(); };
      else
        throw std::runtime_error("Invalid action");

      g_keyMap.add(key, ket, action);
    }

    auto const updatePeriod = config::get_d<unsigned int>(g_config, "updatePeriod", 0.1);
    std::thread t (
      [&g_keyMap, updatePeriod]() {
        while (true)
        {
          g_keyMap.update();
          std::this_thread::sleep_for(std::chrono::seconds(updatePeriod));
        }
      }
    );
    t.detach();
  }

  auto r = static_cast<RawInputFilter *>(IUser32::get_instance());
  r->set_test(spCompositeRawInputTest);

  logging::log("wrapper", logging::LogLevel::debug, "init_raw_input_filter() exit");
}

void init_user32()
{
  logging::log("init", logging::LogLevel::debug, "init_user32()");

  /* json does not like backslashes in strings, so can use forward slashes in dll path specified in config. */
  auto dllPath = config::get_escaped_string_d(g_config, "dllPath", "");
  auto const printDevs = config::get_d<bool>(g_config, "printDevices", true);

  IUser32::instance_factory_t instanceFactory;
  auto const isEnabled = config::get_d<bool>(g_config, "enabled", true);
  if (isEnabled)
  {
    logging::log("init", logging::LogLevel::info, "Input filter is enabled");
    instanceFactory = [dllPath]() -> IUser32::instance_ptr_t { return IUser32::instance_ptr_t(new RawInputFilter(dllPath)); };
  }
  else
  {
    logging::log("init", logging::LogLevel::info, "Input filter is disabled");
    instanceFactory = [dllPath]() -> IUser32::instance_ptr_t { return IUser32::instance_ptr_t(new APIUser32(dllPath)); };
  }

  auto postinitCallback = [printDevs]()
  {
    init_raw_input_filter();
    if (printDevs)
      print_raw_input_devices();
  };

  /* LoadLibrary() shall not be called from DllMain(): https://learn.microsoft.com/en-us/windows/win32/dlls/dllmain#remarks
     So main initialization by default is deferred until fist call to the wrapped funcion. */
  if (config::get_d<bool>(g_config, "deferInit", true))
    IUser32::set_instance_factory(instanceFactory, postinitCallback);
  else
  {
    IUser32::set_instance(instanceFactory());
    postinitCallback();
  }

  logging::log("init", logging::LogLevel::debug, "init_user32() exit");
}


BOOL WINAPI DllMain(HINSTANCE hInst, DWORD reason,LPVOID v)
try {
  if (reason == DLL_PROCESS_ATTACH)
  {
    /* Printing error message to file while log is not initialized. */
    try {
      init_config();
      init_log();
    } catch (std::exception & e)
    {
      std::fstream fs("user32.error", std::ios::out|std::ios::trunc);
      fs << e.what() << std::endl;
      throw;
    } catch (...)
    {
      std::fstream fs("user32.error", std::ios::out|std::ios::trunc);
      fs << "unknown exception";
      throw;
    }
    logging::log("init", logging::LogLevel::debug, "DllMain()");
    init_user32();
    logging::log("init", logging::LogLevel::info, "Dll attached");
  }

  if (reason == DLL_PROCESS_DETACH)
  {
    logging::log("init", logging::LogLevel::info, "Dll detached");
  }

  return TRUE;
} catch (std::exception const & e)
{
  logging::log("init", logging::LogLevel::error, "Exception in DllMain(): ", e.what());
  return FALSE;
}

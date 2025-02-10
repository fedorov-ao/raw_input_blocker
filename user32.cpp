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

#include "user32.hpp"
#include "logging.hpp"
#include <stdexcept>
#include <cassert>

#include <mingw.thread.h>
#include <mingw.mutex.h>

/* IUser32 */
bool IUser32::has_instance()
{
  return upInstance_ != nullptr;
}


IUser32 * IUser32::get_instance()
{
  /* Check before acquiring mutex. */
  if (!upInstance_)
  {
    if (!instaceFactory_)
      throw std::runtime_error("Instance is not initialized and instance factory is not set.");

    typedef std::recursive_mutex mutex_t;
    typedef std::unique_lock<mutex_t> lock_t;

    static mutex_t mutex;
    lock_t lock (mutex);

    /* Check again after acquiring mutex. */
    if (!upInstance_)
    {
      upInstance_ = instaceFactory_();
      assert(upInstance_);
      if (postinitCallback_)
        postinitCallback_();
    }
  }
  assert(upInstance_);
  return upInstance_.get();
}


void IUser32::set_instance(IUser32::instance_ptr_t && upInstance)
{
  upInstance_ = std::move(upInstance);
}


void IUser32::set_instance_factory(IUser32::instance_factory_t const & instaceFactory, IUser32::postinit_callback_t const & postinitCallback)
{
  instaceFactory_ = instaceFactory;
  postinitCallback_ = postinitCallback;
}


IUser32::instance_ptr_t IUser32::upInstance_;
IUser32::instance_factory_t IUser32::instaceFactory_;
IUser32::postinit_callback_t IUser32::postinitCallback_;


extern "C"
{

DLLEXPORT int WINAPIV wsprintfA (LPSTR arg0, LPCSTR arg1, ...)
{
  logging::log("wrapper", logging::LogLevel::debug, "wsprintfA()");
  va_list arglist;
  va_start(arglist, arg1);
  auto r = IUser32::get_instance()->wvsprintfA(arg0, arg1, arglist);
  va_end(arglist);
  return r;
}

DLLEXPORT int WINAPIV wsprintfW (LPWSTR arg0, LPCWSTR arg1, ...)
{
  logging::log("wrapper", logging::LogLevel::debug, "wsprintfW()");
  va_list arglist;
  va_start(arglist, arg1);
  auto r = IUser32::get_instance()->wvsprintfW(arg0, arg1, arglist);
  va_end(arglist);
  return r;
}

DLLEXPORT int WINAPI wvsprintfA (LPSTR arg0, LPCSTR arg1, va_list arglist)
{
  logging::log("wrapper", logging::LogLevel::debug, "wvsprintfA()");
  return IUser32::get_instance()->wvsprintfA(arg0, arg1, arglist);
}

DLLEXPORT int WINAPI wvsprintfW (LPWSTR arg0, LPCWSTR arg1, va_list arglist)
{
  logging::log("wrapper", logging::LogLevel::debug, "wvsprintfW()");
  return IUser32::get_instance()->wvsprintfW(arg0, arg1, arglist);
}

DLLEXPORT HKL WINAPI LoadKeyboardLayoutA (LPCSTR pwszKLID, UINT Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadKeyboardLayoutA()");
  return IUser32::get_instance()->LoadKeyboardLayoutA(pwszKLID, Flags);
}

DLLEXPORT HKL WINAPI LoadKeyboardLayoutW (LPCWSTR pwszKLID, UINT Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadKeyboardLayoutW()");
  return IUser32::get_instance()->LoadKeyboardLayoutW(pwszKLID, Flags);
}

DLLEXPORT HKL WINAPI ActivateKeyboardLayout (HKL hkl, UINT Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ActivateKeyboardLayout()");
  return IUser32::get_instance()->ActivateKeyboardLayout(hkl, Flags);
}

DLLEXPORT int WINAPI ToUnicodeEx (UINT wVirtKey, UINT wScanCode, CONST BYTE * lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "ToUnicodeEx()");
  return IUser32::get_instance()->ToUnicodeEx(wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags, dwhkl);
}

DLLEXPORT WINBOOL WINAPI UnloadKeyboardLayout (HKL hkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnloadKeyboardLayout()");
  return IUser32::get_instance()->UnloadKeyboardLayout(hkl);
}

DLLEXPORT WINBOOL WINAPI GetKeyboardLayoutNameA (LPSTR pwszKLID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardLayoutNameA()");
  return IUser32::get_instance()->GetKeyboardLayoutNameA(pwszKLID);
}

DLLEXPORT WINBOOL WINAPI GetKeyboardLayoutNameW (LPWSTR pwszKLID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardLayoutNameW()");
  return IUser32::get_instance()->GetKeyboardLayoutNameW(pwszKLID);
}

DLLEXPORT int WINAPI GetKeyboardLayoutList (int nBuff, HKL * lpList)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardLayoutList()");
  return IUser32::get_instance()->GetKeyboardLayoutList(nBuff, lpList);
}

DLLEXPORT HKL WINAPI GetKeyboardLayout (DWORD idThread)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardLayout()");
  return IUser32::get_instance()->GetKeyboardLayout(idThread);
}

DLLEXPORT int WINAPI GetMouseMovePointsEx (UINT cbSize, LPMOUSEMOVEPOINT lppt, LPMOUSEMOVEPOINT lpptBuf, int nBufPoints, DWORD resolution)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMouseMovePointsEx()");
  return IUser32::get_instance()->GetMouseMovePointsEx(cbSize, lppt, lpptBuf, nBufPoints, resolution);
}

DLLEXPORT HDESK WINAPI CreateDesktopA (LPCSTR lpszDesktop, LPCSTR lpszDevice, LPDEVMODEA pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDesktopA()");
  return IUser32::get_instance()->CreateDesktopA(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa);
}

DLLEXPORT HDESK WINAPI CreateDesktopW (LPCWSTR lpszDesktop, LPCWSTR lpszDevice, LPDEVMODEW pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDesktopW()");
  return IUser32::get_instance()->CreateDesktopW(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa);
}

DLLEXPORT HDESK WINAPI CreateDesktopExA (LPCSTR lpszDesktop, LPCSTR lpszDevice, DEVMODEA * pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa, ULONG ulHeapSize, PVOID pvoid)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDesktopExA()");
  return IUser32::get_instance()->CreateDesktopExA(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa, ulHeapSize, pvoid);
}

DLLEXPORT HDESK WINAPI CreateDesktopExW (LPCWSTR lpszDesktop, LPCWSTR lpszDevice, DEVMODEW * pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa, ULONG ulHeapSize, PVOID pvoid)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDesktopExW()");
  return IUser32::get_instance()->CreateDesktopExW(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa, ulHeapSize, pvoid);
}

DLLEXPORT HDESK WINAPI OpenDesktopA (LPCSTR lpszDesktop, DWORD dwFlags, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenDesktopA()");
  return IUser32::get_instance()->OpenDesktopA(lpszDesktop, dwFlags, fInherit, dwDesiredAccess);
}

DLLEXPORT HDESK WINAPI OpenDesktopW (LPCWSTR lpszDesktop, DWORD dwFlags, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenDesktopW()");
  return IUser32::get_instance()->OpenDesktopW(lpszDesktop, dwFlags, fInherit, dwDesiredAccess);
}

DLLEXPORT HDESK WINAPI OpenInputDesktop (DWORD dwFlags, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenInputDesktop()");
  return IUser32::get_instance()->OpenInputDesktop(dwFlags, fInherit, dwDesiredAccess);
}

DLLEXPORT WINBOOL WINAPI EnumDesktopsA (HWINSTA hwinsta, DESKTOPENUMPROCA lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDesktopsA()");
  return IUser32::get_instance()->EnumDesktopsA(hwinsta, lpEnumFunc, lParam);
}

DLLEXPORT WINBOOL WINAPI EnumDesktopsW (HWINSTA hwinsta, DESKTOPENUMPROCW lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDesktopsW()");
  return IUser32::get_instance()->EnumDesktopsW(hwinsta, lpEnumFunc, lParam);
}

DLLEXPORT WINBOOL WINAPI EnumDesktopWindows (HDESK hDesktop, WNDENUMPROC lpfn, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDesktopWindows()");
  return IUser32::get_instance()->EnumDesktopWindows(hDesktop, lpfn, lParam);
}

DLLEXPORT WINBOOL WINAPI SwitchDesktop (HDESK hDesktop)
{
  logging::log("wrapper", logging::LogLevel::debug, "SwitchDesktop()");
  return IUser32::get_instance()->SwitchDesktop(hDesktop);
}

DLLEXPORT WINBOOL WINAPI SetThreadDesktop (HDESK hDesktop)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetThreadDesktop()");
  return IUser32::get_instance()->SetThreadDesktop(hDesktop);
}

DLLEXPORT WINBOOL WINAPI CloseDesktop (HDESK hDesktop)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseDesktop()");
  return IUser32::get_instance()->CloseDesktop(hDesktop);
}

DLLEXPORT HDESK WINAPI GetThreadDesktop (DWORD dwThreadId)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetThreadDesktop()");
  return IUser32::get_instance()->GetThreadDesktop(dwThreadId);
}

DLLEXPORT HWINSTA WINAPI CreateWindowStationA (LPCSTR lpwinsta, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateWindowStationA()");
  return IUser32::get_instance()->CreateWindowStationA(lpwinsta, dwFlags, dwDesiredAccess, lpsa);
}

DLLEXPORT HWINSTA WINAPI CreateWindowStationW (LPCWSTR lpwinsta, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateWindowStationW()");
  return IUser32::get_instance()->CreateWindowStationW(lpwinsta, dwFlags, dwDesiredAccess, lpsa);
}

DLLEXPORT HWINSTA WINAPI OpenWindowStationA (LPCSTR lpszWinSta, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenWindowStationA()");
  return IUser32::get_instance()->OpenWindowStationA(lpszWinSta, fInherit, dwDesiredAccess);
}

DLLEXPORT HWINSTA WINAPI OpenWindowStationW (LPCWSTR lpszWinSta, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenWindowStationW()");
  return IUser32::get_instance()->OpenWindowStationW(lpszWinSta, fInherit, dwDesiredAccess);
}

DLLEXPORT WINBOOL WINAPI EnumWindowStationsA (WINSTAENUMPROCA lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumWindowStationsA()");
  return IUser32::get_instance()->EnumWindowStationsA(lpEnumFunc, lParam);
}

DLLEXPORT WINBOOL WINAPI EnumWindowStationsW (WINSTAENUMPROCW lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumWindowStationsW()");
  return IUser32::get_instance()->EnumWindowStationsW(lpEnumFunc, lParam);
}

DLLEXPORT WINBOOL WINAPI CloseWindowStation (HWINSTA hWinSta)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseWindowStation()");
  return IUser32::get_instance()->CloseWindowStation(hWinSta);
}

DLLEXPORT WINBOOL WINAPI SetProcessWindowStation (HWINSTA hWinSta)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProcessWindowStation()");
  return IUser32::get_instance()->SetProcessWindowStation(hWinSta);
}

DLLEXPORT HWINSTA WINAPI GetProcessWindowStation (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetProcessWindowStation()");
  return IUser32::get_instance()->GetProcessWindowStation();
}

DLLEXPORT WINBOOL WINAPI SetUserObjectSecurity (HANDLE hObj, PSECURITY_INFORMATION pSIRequested, PSECURITY_DESCRIPTOR pSID)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetUserObjectSecurity()");
  return IUser32::get_instance()->SetUserObjectSecurity(hObj, pSIRequested, pSID);
}

DLLEXPORT WINBOOL WINAPI GetUserObjectSecurity (HANDLE hObj, PSECURITY_INFORMATION pSIRequested, PSECURITY_DESCRIPTOR pSID, DWORD nLength, LPDWORD lpnLengthNeeded)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUserObjectSecurity()");
  return IUser32::get_instance()->GetUserObjectSecurity(hObj, pSIRequested, pSID, nLength, lpnLengthNeeded);
}

DLLEXPORT WINBOOL WINAPI GetUserObjectInformationA (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength, LPDWORD lpnLengthNeeded)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUserObjectInformationA()");
  return IUser32::get_instance()->GetUserObjectInformationA(hObj, nIndex, pvInfo, nLength, lpnLengthNeeded);
}

DLLEXPORT WINBOOL WINAPI GetUserObjectInformationW (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength, LPDWORD lpnLengthNeeded)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUserObjectInformationW()");
  return IUser32::get_instance()->GetUserObjectInformationW(hObj, nIndex, pvInfo, nLength, lpnLengthNeeded);
}

DLLEXPORT WINBOOL WINAPI SetUserObjectInformationA (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetUserObjectInformationA()");
  return IUser32::get_instance()->SetUserObjectInformationA(hObj, nIndex, pvInfo, nLength);
}

DLLEXPORT WINBOOL WINAPI SetUserObjectInformationW (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetUserObjectInformationW()");
  return IUser32::get_instance()->SetUserObjectInformationW(hObj, nIndex, pvInfo, nLength);
}

DLLEXPORT WINBOOL WINAPI IsHungAppWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsHungAppWindow()");
  return IUser32::get_instance()->IsHungAppWindow(hwnd);
}

DLLEXPORT VOID WINAPI DisableProcessWindowsGhosting (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "DisableProcessWindowsGhosting()");
  IUser32::get_instance()->DisableProcessWindowsGhosting();
}

DLLEXPORT UINT WINAPI RegisterWindowMessageA (LPCSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterWindowMessageA()");
  return IUser32::get_instance()->RegisterWindowMessageA(lpString);
}

DLLEXPORT UINT WINAPI RegisterWindowMessageW (LPCWSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterWindowMessageW()");
  return IUser32::get_instance()->RegisterWindowMessageW(lpString);
}

DLLEXPORT WINBOOL WINAPI TrackMouseEvent (LPTRACKMOUSEEVENT lpEventTrack)
{
  logging::log("wrapper", logging::LogLevel::debug, "TrackMouseEvent()");
  return IUser32::get_instance()->TrackMouseEvent(lpEventTrack);
}

DLLEXPORT WINBOOL WINAPI DrawEdge (HDC hdc, LPRECT qrc, UINT edge, UINT grfFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawEdge()");
  return IUser32::get_instance()->DrawEdge(hdc, qrc, edge, grfFlags);
}

DLLEXPORT WINBOOL WINAPI DrawFrameControl (HDC arg0, LPRECT arg1, UINT arg2, UINT arg3)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawFrameControl()");
  return IUser32::get_instance()->DrawFrameControl(arg0, arg1, arg2, arg3);
}

DLLEXPORT WINBOOL WINAPI DrawCaption (HWND hwnd, HDC hdc, CONST RECT * lprect, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawCaption()");
  return IUser32::get_instance()->DrawCaption(hwnd, hdc, lprect, flags);
}

DLLEXPORT WINBOOL WINAPI DrawAnimatedRects (HWND hwnd, int idAni, CONST RECT * lprcFrom, CONST RECT * lprcTo)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawAnimatedRects()");
  return IUser32::get_instance()->DrawAnimatedRects(hwnd, idAni, lprcFrom, lprcTo);
}

DLLEXPORT WINBOOL WINAPI GetMessageA (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMessageA()");
  return IUser32::get_instance()->GetMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

DLLEXPORT WINBOOL WINAPI GetMessageW (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMessageW()");
  return IUser32::get_instance()->GetMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

DLLEXPORT WINBOOL WINAPI TranslateMessage (CONST MSG * lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "TranslateMessage()");
  return IUser32::get_instance()->TranslateMessage(lpMsg);
}

DLLEXPORT LRESULT WINAPI DispatchMessageA (CONST MSG * lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "DispatchMessageA()");
  return IUser32::get_instance()->DispatchMessageA(lpMsg);
}

DLLEXPORT LRESULT WINAPI DispatchMessageW (CONST MSG * lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "DispatchMessageW()");
  return IUser32::get_instance()->DispatchMessageW(lpMsg);
}

DLLEXPORT WINBOOL WINAPI SetMessageQueue (int cMessagesMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMessageQueue()");
  return IUser32::get_instance()->SetMessageQueue(cMessagesMax);
}

DLLEXPORT WINBOOL WINAPI PeekMessageA (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "PeekMessageA()");
  return IUser32::get_instance()->PeekMessageA(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

DLLEXPORT WINBOOL WINAPI PeekMessageW (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "PeekMessageW()");
  return IUser32::get_instance()->PeekMessageW(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

DLLEXPORT WINBOOL WINAPI RegisterHotKey (HWND hWnd, int id, UINT fsModifiers, UINT vk)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterHotKey()");
  return IUser32::get_instance()->RegisterHotKey(hWnd, id, fsModifiers, vk);
}

DLLEXPORT WINBOOL WINAPI UnregisterHotKey (HWND hWnd, int id)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterHotKey()");
  return IUser32::get_instance()->UnregisterHotKey(hWnd, id);
}

DLLEXPORT WINBOOL WINAPI ExitWindowsEx (UINT uFlags, DWORD dwReason)
{
  logging::log("wrapper", logging::LogLevel::debug, "ExitWindowsEx()");
  return IUser32::get_instance()->ExitWindowsEx(uFlags, dwReason);
}

DLLEXPORT WINBOOL WINAPI SwapMouseButton (WINBOOL fSwap)
{
  logging::log("wrapper", logging::LogLevel::debug, "SwapMouseButton()");
  return IUser32::get_instance()->SwapMouseButton(fSwap);
}

DLLEXPORT DWORD WINAPI GetMessagePos (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMessagePos()");
  return IUser32::get_instance()->GetMessagePos();
}

DLLEXPORT LONG WINAPI GetMessageTime (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMessageTime()");
  return IUser32::get_instance()->GetMessageTime();
}

DLLEXPORT LPARAM WINAPI GetMessageExtraInfo (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMessageExtraInfo()");
  return IUser32::get_instance()->GetMessageExtraInfo();
}

DLLEXPORT DWORD WINAPI GetUnpredictedMessagePos (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUnpredictedMessagePos()");
  return IUser32::get_instance()->GetUnpredictedMessagePos();
}

DLLEXPORT WINBOOL WINAPI IsWow64Message (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWow64Message()");
  return IUser32::get_instance()->IsWow64Message();
}

DLLEXPORT LPARAM WINAPI SetMessageExtraInfo (LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMessageExtraInfo()");
  return IUser32::get_instance()->SetMessageExtraInfo(lParam);
}

DLLEXPORT LRESULT WINAPI SendMessageA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageA()");
  return IUser32::get_instance()->SendMessageA(hWnd, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI SendMessageW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageW()");
  return IUser32::get_instance()->SendMessageW(hWnd, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI SendMessageTimeoutA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageTimeoutA()");
  return IUser32::get_instance()->SendMessageTimeoutA(hWnd, Msg, wParam, lParam, fuFlags, uTimeout, lpdwResult);
}

DLLEXPORT LRESULT WINAPI SendMessageTimeoutW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageTimeoutW()");
  return IUser32::get_instance()->SendMessageTimeoutW(hWnd, Msg, wParam, lParam, fuFlags, uTimeout, lpdwResult);
}

DLLEXPORT WINBOOL WINAPI SendNotifyMessageA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendNotifyMessageA()");
  return IUser32::get_instance()->SendNotifyMessageA(hWnd, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI SendNotifyMessageW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendNotifyMessageW()");
  return IUser32::get_instance()->SendNotifyMessageW(hWnd, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI SendMessageCallbackA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, SENDASYNCPROC lpResultCallBack, ULONG_PTR dwData)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageCallbackA()");
  return IUser32::get_instance()->SendMessageCallbackA(hWnd, Msg, wParam, lParam, lpResultCallBack, dwData);
}

DLLEXPORT WINBOOL WINAPI SendMessageCallbackW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, SENDASYNCPROC lpResultCallBack, ULONG_PTR dwData)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageCallbackW()");
  return IUser32::get_instance()->SendMessageCallbackW(hWnd, Msg, wParam, lParam, lpResultCallBack, dwData);
}

DLLEXPORT LONG WINAPI BroadcastSystemMessageExA (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam, PBSMINFO pbsmInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "BroadcastSystemMessageExA()");
  return IUser32::get_instance()->BroadcastSystemMessageExA(flags, lpInfo, Msg, wParam, lParam, pbsmInfo);
}

DLLEXPORT LONG WINAPI BroadcastSystemMessageExW (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam, PBSMINFO pbsmInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "BroadcastSystemMessageExW()");
  return IUser32::get_instance()->BroadcastSystemMessageExW(flags, lpInfo, Msg, wParam, lParam, pbsmInfo);
}

DLLEXPORT LONG WINAPI BroadcastSystemMessageA (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "BroadcastSystemMessageA()");
  return IUser32::get_instance()->BroadcastSystemMessageA(flags, lpInfo, Msg, wParam, lParam);
}

DLLEXPORT LONG WINAPI BroadcastSystemMessageW (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "BroadcastSystemMessageW()");
  return IUser32::get_instance()->BroadcastSystemMessageW(flags, lpInfo, Msg, wParam, lParam);
}

DLLEXPORT HPOWERNOTIFY WINAPI RegisterPowerSettingNotification (HANDLE hRecipient, LPCGUID PowerSettingGuid, DWORD Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterPowerSettingNotification()");
  return IUser32::get_instance()->RegisterPowerSettingNotification(hRecipient, PowerSettingGuid, Flags);
}

DLLEXPORT WINBOOL WINAPI UnregisterPowerSettingNotification (HPOWERNOTIFY Handle)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterPowerSettingNotification()");
  return IUser32::get_instance()->UnregisterPowerSettingNotification(Handle);
}

DLLEXPORT HPOWERNOTIFY WINAPI RegisterSuspendResumeNotification (HANDLE hRecipient, DWORD Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterSuspendResumeNotification()");
  return IUser32::get_instance()->RegisterSuspendResumeNotification(hRecipient, Flags);
}

DLLEXPORT WINBOOL WINAPI UnregisterSuspendResumeNotification (HPOWERNOTIFY Handle)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterSuspendResumeNotification()");
  return IUser32::get_instance()->UnregisterSuspendResumeNotification(Handle);
}

DLLEXPORT WINBOOL WINAPI PostMessageA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "PostMessageA()");
  return IUser32::get_instance()->PostMessageA(hWnd, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI PostMessageW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "PostMessageW()");
  return IUser32::get_instance()->PostMessageW(hWnd, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI PostThreadMessageA (DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "PostThreadMessageA()");
  return IUser32::get_instance()->PostThreadMessageA(idThread, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI PostThreadMessageW (DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "PostThreadMessageW()");
  return IUser32::get_instance()->PostThreadMessageW(idThread, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI AttachThreadInput (DWORD idAttach, DWORD idAttachTo, WINBOOL fAttach)
{
  logging::log("wrapper", logging::LogLevel::debug, "AttachThreadInput()");
  return IUser32::get_instance()->AttachThreadInput(idAttach, idAttachTo, fAttach);
}

DLLEXPORT WINBOOL WINAPI ReplyMessage (LRESULT lResult)
{
  logging::log("wrapper", logging::LogLevel::debug, "ReplyMessage()");
  return IUser32::get_instance()->ReplyMessage(lResult);
}

DLLEXPORT WINBOOL WINAPI WaitMessage (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "WaitMessage()");
  return IUser32::get_instance()->WaitMessage();
}

DLLEXPORT DWORD WINAPI WaitForInputIdle (HANDLE hProcess, DWORD dwMilliseconds)
{
  logging::log("wrapper", logging::LogLevel::debug, "WaitForInputIdle()");
  return IUser32::get_instance()->WaitForInputIdle(hProcess, dwMilliseconds);
}

DLLEXPORT LRESULT WINAPI DefWindowProcA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefWindowProcA()");
  return IUser32::get_instance()->DefWindowProcA(hWnd, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI DefWindowProcW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefWindowProcW()");
  return IUser32::get_instance()->DefWindowProcW(hWnd, Msg, wParam, lParam);
}

DLLEXPORT VOID WINAPI PostQuitMessage (int nExitCode)
{
  logging::log("wrapper", logging::LogLevel::debug, "PostQuitMessage()");
  IUser32::get_instance()->PostQuitMessage(nExitCode);
}

DLLEXPORT WINBOOL WINAPI InSendMessage (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "InSendMessage()");
  return IUser32::get_instance()->InSendMessage();
}

DLLEXPORT DWORD WINAPI InSendMessageEx (LPVOID lpReserved)
{
  logging::log("wrapper", logging::LogLevel::debug, "InSendMessageEx()");
  return IUser32::get_instance()->InSendMessageEx(lpReserved);
}

DLLEXPORT UINT WINAPI GetDoubleClickTime (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDoubleClickTime()");
  return IUser32::get_instance()->GetDoubleClickTime();
}

DLLEXPORT WINBOOL WINAPI SetDoubleClickTime (UINT arg0)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDoubleClickTime()");
  return IUser32::get_instance()->SetDoubleClickTime(arg0);
}

DLLEXPORT ATOM WINAPI RegisterClassA (CONST WNDCLASSA * lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClassA()");
  return IUser32::get_instance()->RegisterClassA(lpWndClass);
}

DLLEXPORT ATOM WINAPI RegisterClassW (CONST WNDCLASSW * lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClassW()");
  return IUser32::get_instance()->RegisterClassW(lpWndClass);
}

DLLEXPORT WINBOOL WINAPI UnregisterClassA (LPCSTR lpClassName, HINSTANCE hInstance)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterClassA()");
  return IUser32::get_instance()->UnregisterClassA(lpClassName, hInstance);
}

DLLEXPORT WINBOOL WINAPI UnregisterClassW (LPCWSTR lpClassName, HINSTANCE hInstance)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterClassW()");
  return IUser32::get_instance()->UnregisterClassW(lpClassName, hInstance);
}

DLLEXPORT WINBOOL WINAPI GetClassInfoA (HINSTANCE hInstance, LPCSTR lpClassName, LPWNDCLASSA lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassInfoA()");
  return IUser32::get_instance()->GetClassInfoA(hInstance, lpClassName, lpWndClass);
}

DLLEXPORT WINBOOL WINAPI GetClassInfoW (HINSTANCE hInstance, LPCWSTR lpClassName, LPWNDCLASSW lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassInfoW()");
  return IUser32::get_instance()->GetClassInfoW(hInstance, lpClassName, lpWndClass);
}

DLLEXPORT ATOM WINAPI RegisterClassExA (CONST WNDCLASSEXA * lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClassExA()");
  return IUser32::get_instance()->RegisterClassExA(lpWndClass);
}

DLLEXPORT ATOM WINAPI RegisterClassExW (CONST WNDCLASSEXW * lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClassExW()");
  return IUser32::get_instance()->RegisterClassExW(lpWndClass);
}

DLLEXPORT WINBOOL WINAPI GetClassInfoExA (HINSTANCE hInstance, LPCSTR lpszClass, LPWNDCLASSEXA lpwcx)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassInfoExA()");
  return IUser32::get_instance()->GetClassInfoExA(hInstance, lpszClass, lpwcx);
}

DLLEXPORT WINBOOL WINAPI GetClassInfoExW (HINSTANCE hInstance, LPCWSTR lpszClass, LPWNDCLASSEXW lpwcx)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassInfoExW()");
  return IUser32::get_instance()->GetClassInfoExW(hInstance, lpszClass, lpwcx);
}

#ifdef STRICT
DLLEXPORT LRESULT WINAPI CallWindowProcA (WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallWindowProcA()");
  return IUser32::get_instance()->CallWindowProcA(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI CallWindowProcW (WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallWindowProcW()");
  return IUser32::get_instance()->CallWindowProcW(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

#else

DLLEXPORT LRESULT WINAPI CallWindowProcA (FARPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallWindowProcA()");
  return IUser32::get_instance()->CallWindowProcA(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI CallWindowProcW (FARPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallWindowProcW()");
  return IUser32::get_instance()->CallWindowProcW(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

#endif

DLLEXPORT HDEVNOTIFY WINAPI RegisterDeviceNotificationA (HANDLE hRecipient, LPVOID NotificationFilter, DWORD Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterDeviceNotificationA()");
  return IUser32::get_instance()->RegisterDeviceNotificationA(hRecipient, NotificationFilter, Flags);
}

DLLEXPORT HDEVNOTIFY WINAPI RegisterDeviceNotificationW (HANDLE hRecipient, LPVOID NotificationFilter, DWORD Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterDeviceNotificationW()");
  return IUser32::get_instance()->RegisterDeviceNotificationW(hRecipient, NotificationFilter, Flags);
}

DLLEXPORT WINBOOL WINAPI UnregisterDeviceNotification (HDEVNOTIFY Handle)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterDeviceNotification()");
  return IUser32::get_instance()->UnregisterDeviceNotification(Handle);
}

DLLEXPORT HWND WINAPI CreateWindowExA (DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateWindowExA()");
  return IUser32::get_instance()->CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

DLLEXPORT HWND WINAPI CreateWindowExW (DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateWindowExW()");
  return IUser32::get_instance()->CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

DLLEXPORT WINBOOL WINAPI IsWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWindow()");
  return IUser32::get_instance()->IsWindow(hWnd);
}

DLLEXPORT WINBOOL WINAPI IsMenu (HMENU hMenu)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsMenu()");
  return IUser32::get_instance()->IsMenu(hMenu);
}

DLLEXPORT WINBOOL WINAPI IsChild (HWND hWndParent, HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsChild()");
  return IUser32::get_instance()->IsChild(hWndParent, hWnd);
}

DLLEXPORT WINBOOL WINAPI DestroyWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyWindow()");
  return IUser32::get_instance()->DestroyWindow(hWnd);
}

DLLEXPORT WINBOOL WINAPI ShowWindow (HWND hWnd, int nCmdShow)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowWindow()");
  return IUser32::get_instance()->ShowWindow(hWnd, nCmdShow);
}

DLLEXPORT WINBOOL WINAPI AnimateWindow (HWND hWnd, DWORD dwTime, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "AnimateWindow()");
  return IUser32::get_instance()->AnimateWindow(hWnd, dwTime, dwFlags);
}

DLLEXPORT WINBOOL WINAPI UpdateLayeredWindow (HWND hWnd, HDC hdcDst, POINT * pptDst, SIZE * psize, HDC hdcSrc, POINT * pptSrc, COLORREF crKey, BLENDFUNCTION * pblend, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "UpdateLayeredWindow()");
  return IUser32::get_instance()->UpdateLayeredWindow(hWnd, hdcDst, pptDst, psize, hdcSrc, pptSrc, crKey, pblend, dwFlags);
}

DLLEXPORT WINBOOL WINAPI UpdateLayeredWindowIndirect (HWND hWnd, const UPDATELAYEREDWINDOWINFO * pULWInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "UpdateLayeredWindowIndirect()");
  return IUser32::get_instance()->UpdateLayeredWindowIndirect(hWnd, pULWInfo);
}

DLLEXPORT WINBOOL WINAPI GetLayeredWindowAttributes (HWND hwnd, COLORREF * pcrKey, BYTE * pbAlpha, DWORD * pdwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetLayeredWindowAttributes()");
  return IUser32::get_instance()->GetLayeredWindowAttributes(hwnd, pcrKey, pbAlpha, pdwFlags);
}

DLLEXPORT WINBOOL WINAPI PrintWindow (HWND hwnd, HDC hdcBlt, UINT nFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "PrintWindow()");
  return IUser32::get_instance()->PrintWindow(hwnd, hdcBlt, nFlags);
}

DLLEXPORT WINBOOL WINAPI SetLayeredWindowAttributes (HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetLayeredWindowAttributes()");
  return IUser32::get_instance()->SetLayeredWindowAttributes(hwnd, crKey, bAlpha, dwFlags);
}

DLLEXPORT WINBOOL WINAPI ShowWindowAsync (HWND hWnd, int nCmdShow)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowWindowAsync()");
  return IUser32::get_instance()->ShowWindowAsync(hWnd, nCmdShow);
}

DLLEXPORT WINBOOL WINAPI FlashWindow (HWND hWnd, WINBOOL bInvert)
{
  logging::log("wrapper", logging::LogLevel::debug, "FlashWindow()");
  return IUser32::get_instance()->FlashWindow(hWnd, bInvert);
}

DLLEXPORT WINBOOL WINAPI FlashWindowEx (PFLASHWINFO pfwi)
{
  logging::log("wrapper", logging::LogLevel::debug, "FlashWindowEx()");
  return IUser32::get_instance()->FlashWindowEx(pfwi);
}

DLLEXPORT WINBOOL WINAPI ShowOwnedPopups (HWND hWnd, WINBOOL fShow)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowOwnedPopups()");
  return IUser32::get_instance()->ShowOwnedPopups(hWnd, fShow);
}

DLLEXPORT WINBOOL WINAPI OpenIcon (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenIcon()");
  return IUser32::get_instance()->OpenIcon(hWnd);
}

DLLEXPORT WINBOOL WINAPI CloseWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseWindow()");
  return IUser32::get_instance()->CloseWindow(hWnd);
}

DLLEXPORT WINBOOL WINAPI MoveWindow (HWND hWnd, int X, int Y, int nWidth, int nHeight, WINBOOL bRepaint)
{
  logging::log("wrapper", logging::LogLevel::debug, "MoveWindow()");
  return IUser32::get_instance()->MoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
}

DLLEXPORT WINBOOL WINAPI SetWindowPos (HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowPos()");
  return IUser32::get_instance()->SetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

DLLEXPORT WINBOOL WINAPI GetWindowPlacement (HWND hWnd, WINDOWPLACEMENT * lpwndpl)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowPlacement()");
  return IUser32::get_instance()->GetWindowPlacement(hWnd, lpwndpl);
}

DLLEXPORT WINBOOL WINAPI SetWindowPlacement (HWND hWnd, CONST WINDOWPLACEMENT * lpwndpl)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowPlacement()");
  return IUser32::get_instance()->SetWindowPlacement(hWnd, lpwndpl);
}

DLLEXPORT WINBOOL WINAPI GetWindowDisplayAffinity (HWND hWnd, DWORD * pdwAffinity)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowDisplayAffinity()");
  return IUser32::get_instance()->GetWindowDisplayAffinity(hWnd, pdwAffinity);
}

DLLEXPORT WINBOOL WINAPI SetWindowDisplayAffinity (HWND hWnd, DWORD dwAffinity)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowDisplayAffinity()");
  return IUser32::get_instance()->SetWindowDisplayAffinity(hWnd, dwAffinity);
}

DLLEXPORT HDWP WINAPI BeginDeferWindowPos (int nNumWindows)
{
  logging::log("wrapper", logging::LogLevel::debug, "BeginDeferWindowPos()");
  return IUser32::get_instance()->BeginDeferWindowPos(nNumWindows);
}

DLLEXPORT HDWP WINAPI DeferWindowPos (HDWP hWinPosInfo, HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DeferWindowPos()");
  return IUser32::get_instance()->DeferWindowPos(hWinPosInfo, hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
}

DLLEXPORT WINBOOL WINAPI EndDeferWindowPos (HDWP hWinPosInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "EndDeferWindowPos()");
  return IUser32::get_instance()->EndDeferWindowPos(hWinPosInfo);
}

DLLEXPORT WINBOOL WINAPI IsWindowVisible (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWindowVisible()");
  return IUser32::get_instance()->IsWindowVisible(hWnd);
}

DLLEXPORT WINBOOL WINAPI IsIconic (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsIconic()");
  return IUser32::get_instance()->IsIconic(hWnd);
}

DLLEXPORT WINBOOL WINAPI AnyPopup (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "AnyPopup()");
  return IUser32::get_instance()->AnyPopup();
}

DLLEXPORT WINBOOL WINAPI BringWindowToTop (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "BringWindowToTop()");
  return IUser32::get_instance()->BringWindowToTop(hWnd);
}

DLLEXPORT WINBOOL WINAPI IsZoomed (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsZoomed()");
  return IUser32::get_instance()->IsZoomed(hWnd);
}

DLLEXPORT HWND WINAPI CreateDialogParamA (HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDialogParamA()");
  return IUser32::get_instance()->CreateDialogParamA(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT HWND WINAPI CreateDialogParamW (HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDialogParamW()");
  return IUser32::get_instance()->CreateDialogParamW(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT HWND WINAPI CreateDialogIndirectParamA (HINSTANCE hInstance, LPCDLGTEMPLATEA lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDialogIndirectParamA()");
  return IUser32::get_instance()->CreateDialogIndirectParamA(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT HWND WINAPI CreateDialogIndirectParamW (HINSTANCE hInstance, LPCDLGTEMPLATEW lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDialogIndirectParamW()");
  return IUser32::get_instance()->CreateDialogIndirectParamW(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT INT_PTR WINAPI DialogBoxParamA (HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DialogBoxParamA()");
  return IUser32::get_instance()->DialogBoxParamA(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT INT_PTR WINAPI DialogBoxParamW (HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DialogBoxParamW()");
  return IUser32::get_instance()->DialogBoxParamW(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT INT_PTR WINAPI DialogBoxIndirectParamA (HINSTANCE hInstance, LPCDLGTEMPLATEA hDialogTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DialogBoxIndirectParamA()");
  return IUser32::get_instance()->DialogBoxIndirectParamA(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT INT_PTR WINAPI DialogBoxIndirectParamW (HINSTANCE hInstance, LPCDLGTEMPLATEW hDialogTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DialogBoxIndirectParamW()");
  return IUser32::get_instance()->DialogBoxIndirectParamW(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

DLLEXPORT WINBOOL WINAPI EndDialog (HWND hDlg, INT_PTR nResult)
{
  logging::log("wrapper", logging::LogLevel::debug, "EndDialog()");
  return IUser32::get_instance()->EndDialog(hDlg, nResult);
}

DLLEXPORT HWND WINAPI GetDlgItem (HWND hDlg, int nIDDlgItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDlgItem()");
  return IUser32::get_instance()->GetDlgItem(hDlg, nIDDlgItem);
}

DLLEXPORT WINBOOL WINAPI SetDlgItemInt (HWND hDlg, int nIDDlgItem, UINT uValue, WINBOOL bSigned)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDlgItemInt()");
  return IUser32::get_instance()->SetDlgItemInt(hDlg, nIDDlgItem, uValue, bSigned);
}

DLLEXPORT UINT WINAPI GetDlgItemInt (HWND hDlg, int nIDDlgItem, WINBOOL * lpTranslated, WINBOOL bSigned)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDlgItemInt()");
  return IUser32::get_instance()->GetDlgItemInt(hDlg, nIDDlgItem, lpTranslated, bSigned);
}

DLLEXPORT WINBOOL WINAPI SetDlgItemTextA (HWND hDlg, int nIDDlgItem, LPCSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDlgItemTextA()");
  return IUser32::get_instance()->SetDlgItemTextA(hDlg, nIDDlgItem, lpString);
}

DLLEXPORT WINBOOL WINAPI SetDlgItemTextW (HWND hDlg, int nIDDlgItem, LPCWSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDlgItemTextW()");
  return IUser32::get_instance()->SetDlgItemTextW(hDlg, nIDDlgItem, lpString);
}

DLLEXPORT UINT WINAPI GetDlgItemTextA (HWND hDlg, int nIDDlgItem, LPSTR lpString, int cchMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDlgItemTextA()");
  return IUser32::get_instance()->GetDlgItemTextA(hDlg, nIDDlgItem, lpString, cchMax);
}

DLLEXPORT UINT WINAPI GetDlgItemTextW (HWND hDlg, int nIDDlgItem, LPWSTR lpString, int cchMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDlgItemTextW()");
  return IUser32::get_instance()->GetDlgItemTextW(hDlg, nIDDlgItem, lpString, cchMax);
}

DLLEXPORT WINBOOL WINAPI CheckDlgButton (HWND hDlg, int nIDButton, UINT uCheck)
{
  logging::log("wrapper", logging::LogLevel::debug, "CheckDlgButton()");
  return IUser32::get_instance()->CheckDlgButton(hDlg, nIDButton, uCheck);
}

DLLEXPORT WINBOOL WINAPI CheckRadioButton (HWND hDlg, int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
{
  logging::log("wrapper", logging::LogLevel::debug, "CheckRadioButton()");
  return IUser32::get_instance()->CheckRadioButton(hDlg, nIDFirstButton, nIDLastButton, nIDCheckButton);
}

DLLEXPORT UINT WINAPI IsDlgButtonChecked (HWND hDlg, int nIDButton)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsDlgButtonChecked()");
  return IUser32::get_instance()->IsDlgButtonChecked(hDlg, nIDButton);
}

DLLEXPORT LRESULT WINAPI SendDlgItemMessageA (HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendDlgItemMessageA()");
  return IUser32::get_instance()->SendDlgItemMessageA(hDlg, nIDDlgItem, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI SendDlgItemMessageW (HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendDlgItemMessageW()");
  return IUser32::get_instance()->SendDlgItemMessageW(hDlg, nIDDlgItem, Msg, wParam, lParam);
}

DLLEXPORT HWND WINAPI GetNextDlgGroupItem (HWND hDlg, HWND hCtl, WINBOOL bPrevious)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetNextDlgGroupItem()");
  return IUser32::get_instance()->GetNextDlgGroupItem(hDlg, hCtl, bPrevious);
}

DLLEXPORT HWND WINAPI GetNextDlgTabItem (HWND hDlg, HWND hCtl, WINBOOL bPrevious)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetNextDlgTabItem()");
  return IUser32::get_instance()->GetNextDlgTabItem(hDlg, hCtl, bPrevious);
}

DLLEXPORT int WINAPI GetDlgCtrlID (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDlgCtrlID()");
  return IUser32::get_instance()->GetDlgCtrlID(hWnd);
}

DLLEXPORT LONG WINAPI GetDialogBaseUnits (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDialogBaseUnits()");
  return IUser32::get_instance()->GetDialogBaseUnits();
}

DLLEXPORT LRESULT WINAPI DefDlgProcA (HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefDlgProcA()");
  return IUser32::get_instance()->DefDlgProcA(hDlg, Msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI DefDlgProcW (HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefDlgProcW()");
  return IUser32::get_instance()->DefDlgProcW(hDlg, Msg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI CallMsgFilterA (LPMSG lpMsg, int nCode)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallMsgFilterA()");
  return IUser32::get_instance()->CallMsgFilterA(lpMsg, nCode);
}

DLLEXPORT WINBOOL WINAPI CallMsgFilterW (LPMSG lpMsg, int nCode)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallMsgFilterW()");
  return IUser32::get_instance()->CallMsgFilterW(lpMsg, nCode);
}

DLLEXPORT WINBOOL WINAPI OpenClipboard (HWND hWndNewOwner)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenClipboard()");
  return IUser32::get_instance()->OpenClipboard(hWndNewOwner);
}

DLLEXPORT WINBOOL WINAPI CloseClipboard (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseClipboard()");
  return IUser32::get_instance()->CloseClipboard();
}

DLLEXPORT DWORD WINAPI GetClipboardSequenceNumber (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardSequenceNumber()");
  return IUser32::get_instance()->GetClipboardSequenceNumber();
}

DLLEXPORT HWND WINAPI GetClipboardOwner (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardOwner()");
  return IUser32::get_instance()->GetClipboardOwner();
}

DLLEXPORT HWND WINAPI SetClipboardViewer (HWND hWndNewViewer)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClipboardViewer()");
  return IUser32::get_instance()->SetClipboardViewer(hWndNewViewer);
}

DLLEXPORT HWND WINAPI GetClipboardViewer (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardViewer()");
  return IUser32::get_instance()->GetClipboardViewer();
}

DLLEXPORT WINBOOL WINAPI ChangeClipboardChain (HWND hWndRemove, HWND hWndNewNext)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeClipboardChain()");
  return IUser32::get_instance()->ChangeClipboardChain(hWndRemove, hWndNewNext);
}

DLLEXPORT HANDLE WINAPI SetClipboardData (UINT uFormat, HANDLE hMem)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClipboardData()");
  return IUser32::get_instance()->SetClipboardData(uFormat, hMem);
}

DLLEXPORT HANDLE WINAPI GetClipboardData (UINT uFormat)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardData()");
  return IUser32::get_instance()->GetClipboardData(uFormat);
}

DLLEXPORT UINT WINAPI RegisterClipboardFormatA (LPCSTR lpszFormat)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClipboardFormatA()");
  return IUser32::get_instance()->RegisterClipboardFormatA(lpszFormat);
}

DLLEXPORT UINT WINAPI RegisterClipboardFormatW (LPCWSTR lpszFormat)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClipboardFormatW()");
  return IUser32::get_instance()->RegisterClipboardFormatW(lpszFormat);
}

DLLEXPORT int WINAPI CountClipboardFormats (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "CountClipboardFormats()");
  return IUser32::get_instance()->CountClipboardFormats();
}

DLLEXPORT UINT WINAPI EnumClipboardFormats (UINT format)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumClipboardFormats()");
  return IUser32::get_instance()->EnumClipboardFormats(format);
}

DLLEXPORT int WINAPI GetClipboardFormatNameA (UINT format, LPSTR lpszFormatName, int cchMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardFormatNameA()");
  return IUser32::get_instance()->GetClipboardFormatNameA(format, lpszFormatName, cchMaxCount);
}

DLLEXPORT int WINAPI GetClipboardFormatNameW (UINT format, LPWSTR lpszFormatName, int cchMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardFormatNameW()");
  return IUser32::get_instance()->GetClipboardFormatNameW(format, lpszFormatName, cchMaxCount);
}

DLLEXPORT WINBOOL WINAPI EmptyClipboard (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "EmptyClipboard()");
  return IUser32::get_instance()->EmptyClipboard();
}

DLLEXPORT WINBOOL WINAPI IsClipboardFormatAvailable (UINT format)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsClipboardFormatAvailable()");
  return IUser32::get_instance()->IsClipboardFormatAvailable(format);
}

DLLEXPORT int WINAPI GetPriorityClipboardFormat (UINT * paFormatPriorityList, int cFormats)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPriorityClipboardFormat()");
  return IUser32::get_instance()->GetPriorityClipboardFormat(paFormatPriorityList, cFormats);
}

DLLEXPORT HWND WINAPI GetOpenClipboardWindow (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetOpenClipboardWindow()");
  return IUser32::get_instance()->GetOpenClipboardWindow();
}

DLLEXPORT WINBOOL WINAPI AddClipboardFormatListener (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "AddClipboardFormatListener()");
  return IUser32::get_instance()->AddClipboardFormatListener(hwnd);
}

DLLEXPORT WINBOOL WINAPI RemoveClipboardFormatListener (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "RemoveClipboardFormatListener()");
  return IUser32::get_instance()->RemoveClipboardFormatListener(hwnd);
}

DLLEXPORT WINBOOL WINAPI GetUpdatedClipboardFormats (PUINT lpuiFormats, UINT cFormats, PUINT pcFormatsOut)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUpdatedClipboardFormats()");
  return IUser32::get_instance()->GetUpdatedClipboardFormats(lpuiFormats, cFormats, pcFormatsOut);
}

DLLEXPORT WINBOOL WINAPI CharToOemA (LPCSTR lpszSrc, LPSTR lpszDst)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharToOemA()");
  return IUser32::get_instance()->CharToOemA(lpszSrc, lpszDst);
}

DLLEXPORT WINBOOL WINAPI CharToOemW (LPCWSTR lpszSrc, LPSTR lpszDst)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharToOemW()");
  return IUser32::get_instance()->CharToOemW(lpszSrc, lpszDst);
}

DLLEXPORT WINBOOL WINAPI OemToCharA (LPCSTR lpszSrc, LPSTR lpszDst)
{
  logging::log("wrapper", logging::LogLevel::debug, "OemToCharA()");
  return IUser32::get_instance()->OemToCharA(lpszSrc, lpszDst);
}

DLLEXPORT WINBOOL WINAPI OemToCharW (LPCSTR lpszSrc, LPWSTR lpszDst)
{
  logging::log("wrapper", logging::LogLevel::debug, "OemToCharW()");
  return IUser32::get_instance()->OemToCharW(lpszSrc, lpszDst);
}

DLLEXPORT WINBOOL WINAPI CharToOemBuffA (LPCSTR lpszSrc, LPSTR lpszDst, DWORD cchDstLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharToOemBuffA()");
  return IUser32::get_instance()->CharToOemBuffA(lpszSrc, lpszDst, cchDstLength);
}

DLLEXPORT WINBOOL WINAPI CharToOemBuffW (LPCWSTR lpszSrc, LPSTR lpszDst, DWORD cchDstLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharToOemBuffW()");
  return IUser32::get_instance()->CharToOemBuffW(lpszSrc, lpszDst, cchDstLength);
}

DLLEXPORT WINBOOL WINAPI OemToCharBuffA (LPCSTR lpszSrc, LPSTR lpszDst, DWORD cchDstLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "OemToCharBuffA()");
  return IUser32::get_instance()->OemToCharBuffA(lpszSrc, lpszDst, cchDstLength);
}

DLLEXPORT WINBOOL WINAPI OemToCharBuffW (LPCSTR lpszSrc, LPWSTR lpszDst, DWORD cchDstLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "OemToCharBuffW()");
  return IUser32::get_instance()->OemToCharBuffW(lpszSrc, lpszDst, cchDstLength);
}

DLLEXPORT LPSTR WINAPI CharUpperA (LPSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharUpperA()");
  return IUser32::get_instance()->CharUpperA(lpsz);
}

DLLEXPORT LPWSTR WINAPI CharUpperW (LPWSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharUpperW()");
  return IUser32::get_instance()->CharUpperW(lpsz);
}

DLLEXPORT DWORD WINAPI CharUpperBuffA (LPSTR lpsz, DWORD cchLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharUpperBuffA()");
  return IUser32::get_instance()->CharUpperBuffA(lpsz, cchLength);
}

DLLEXPORT DWORD WINAPI CharUpperBuffW (LPWSTR lpsz, DWORD cchLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharUpperBuffW()");
  return IUser32::get_instance()->CharUpperBuffW(lpsz, cchLength);
}

DLLEXPORT LPSTR WINAPI CharLowerA (LPSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharLowerA()");
  return IUser32::get_instance()->CharLowerA(lpsz);
}

DLLEXPORT LPWSTR WINAPI CharLowerW (LPWSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharLowerW()");
  return IUser32::get_instance()->CharLowerW(lpsz);
}

DLLEXPORT DWORD WINAPI CharLowerBuffA (LPSTR lpsz, DWORD cchLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharLowerBuffA()");
  return IUser32::get_instance()->CharLowerBuffA(lpsz, cchLength);
}

DLLEXPORT DWORD WINAPI CharLowerBuffW (LPWSTR lpsz, DWORD cchLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharLowerBuffW()");
  return IUser32::get_instance()->CharLowerBuffW(lpsz, cchLength);
}

DLLEXPORT LPSTR WINAPI CharNextA (LPCSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharNextA()");
  return IUser32::get_instance()->CharNextA(lpsz);
}

DLLEXPORT LPWSTR WINAPI CharNextW (LPCWSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharNextW()");
  return IUser32::get_instance()->CharNextW(lpsz);
}

DLLEXPORT LPSTR WINAPI CharPrevA (LPCSTR lpszStart, LPCSTR lpszCurrent)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharPrevA()");
  return IUser32::get_instance()->CharPrevA(lpszStart, lpszCurrent);
}

DLLEXPORT LPWSTR WINAPI CharPrevW (LPCWSTR lpszStart, LPCWSTR lpszCurrent)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharPrevW()");
  return IUser32::get_instance()->CharPrevW(lpszStart, lpszCurrent);
}

DLLEXPORT LPSTR WINAPI CharNextExA (WORD CodePage, LPCSTR lpCurrentChar, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharNextExA()");
  return IUser32::get_instance()->CharNextExA(CodePage, lpCurrentChar, dwFlags);
}

DLLEXPORT LPSTR WINAPI CharPrevExA (WORD CodePage, LPCSTR lpStart, LPCSTR lpCurrentChar, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharPrevExA()");
  return IUser32::get_instance()->CharPrevExA(CodePage, lpStart, lpCurrentChar, dwFlags);
}

DLLEXPORT WINBOOL WINAPI IsCharAlphaA (CHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharAlphaA()");
  return IUser32::get_instance()->IsCharAlphaA(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharAlphaW (WCHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharAlphaW()");
  return IUser32::get_instance()->IsCharAlphaW(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharAlphaNumericA (CHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharAlphaNumericA()");
  return IUser32::get_instance()->IsCharAlphaNumericA(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharAlphaNumericW (WCHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharAlphaNumericW()");
  return IUser32::get_instance()->IsCharAlphaNumericW(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharUpperA (CHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharUpperA()");
  return IUser32::get_instance()->IsCharUpperA(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharUpperW (WCHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharUpperW()");
  return IUser32::get_instance()->IsCharUpperW(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharLowerA (CHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharLowerA()");
  return IUser32::get_instance()->IsCharLowerA(ch);
}

DLLEXPORT WINBOOL WINAPI IsCharLowerW (WCHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharLowerW()");
  return IUser32::get_instance()->IsCharLowerW(ch);
}

DLLEXPORT HWND WINAPI SetFocus (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetFocus()");
  return IUser32::get_instance()->SetFocus(hWnd);
}

DLLEXPORT HWND WINAPI GetActiveWindow (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetActiveWindow()");
  return IUser32::get_instance()->GetActiveWindow();
}

DLLEXPORT HWND WINAPI GetFocus (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetFocus()");
  return IUser32::get_instance()->GetFocus();
}

DLLEXPORT UINT WINAPI GetKBCodePage (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKBCodePage()");
  return IUser32::get_instance()->GetKBCodePage();
}

DLLEXPORT SHORT WINAPI GetKeyState (int nVirtKey)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyState()");
  return IUser32::get_instance()->GetKeyState(nVirtKey);
}

DLLEXPORT SHORT WINAPI GetAsyncKeyState (int vKey)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAsyncKeyState()");
  return IUser32::get_instance()->GetAsyncKeyState(vKey);
}

DLLEXPORT WINBOOL WINAPI GetKeyboardState (PBYTE lpKeyState)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardState()");
  return IUser32::get_instance()->GetKeyboardState(lpKeyState);
}

DLLEXPORT WINBOOL WINAPI SetKeyboardState (LPBYTE lpKeyState)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetKeyboardState()");
  return IUser32::get_instance()->SetKeyboardState(lpKeyState);
}

DLLEXPORT int WINAPI GetKeyNameTextA (LONG lParam, LPSTR lpString, int cchSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyNameTextA()");
  return IUser32::get_instance()->GetKeyNameTextA(lParam, lpString, cchSize);
}

DLLEXPORT int WINAPI GetKeyNameTextW (LONG lParam, LPWSTR lpString, int cchSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyNameTextW()");
  return IUser32::get_instance()->GetKeyNameTextW(lParam, lpString, cchSize);
}

DLLEXPORT int WINAPI GetKeyboardType (int nTypeFlag)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardType()");
  return IUser32::get_instance()->GetKeyboardType(nTypeFlag);
}

DLLEXPORT int WINAPI ToAscii (UINT uVirtKey, UINT uScanCode, CONST BYTE * lpKeyState, LPWORD lpChar, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ToAscii()");
  return IUser32::get_instance()->ToAscii(uVirtKey, uScanCode, lpKeyState, lpChar, uFlags);
}

DLLEXPORT int WINAPI ToAsciiEx (UINT uVirtKey, UINT uScanCode, CONST BYTE * lpKeyState, LPWORD lpChar, UINT uFlags, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "ToAsciiEx()");
  return IUser32::get_instance()->ToAsciiEx(uVirtKey, uScanCode, lpKeyState, lpChar, uFlags, dwhkl);
}

DLLEXPORT int WINAPI ToUnicode (UINT wVirtKey, UINT wScanCode, CONST BYTE * lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ToUnicode()");
  return IUser32::get_instance()->ToUnicode(wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags);
}

DLLEXPORT DWORD WINAPI OemKeyScan (WORD wOemChar)
{
  logging::log("wrapper", logging::LogLevel::debug, "OemKeyScan()");
  return IUser32::get_instance()->OemKeyScan(wOemChar);
}

DLLEXPORT SHORT WINAPI VkKeyScanA (CHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "VkKeyScanA()");
  return IUser32::get_instance()->VkKeyScanA(ch);
}

DLLEXPORT SHORT WINAPI VkKeyScanW (WCHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "VkKeyScanW()");
  return IUser32::get_instance()->VkKeyScanW(ch);
}

DLLEXPORT SHORT WINAPI VkKeyScanExA (CHAR ch, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "VkKeyScanExA()");
  return IUser32::get_instance()->VkKeyScanExA(ch, dwhkl);
}

DLLEXPORT SHORT WINAPI VkKeyScanExW (WCHAR ch, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "VkKeyScanExW()");
  return IUser32::get_instance()->VkKeyScanExW(ch, dwhkl);
}

DLLEXPORT VOID WINAPI keybd_event (BYTE bVk, BYTE bScan, DWORD dwFlags, ULONG_PTR dwExtraInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "keybd_event()");
  IUser32::get_instance()->keybd_event(bVk, bScan, dwFlags, dwExtraInfo);
}

DLLEXPORT VOID WINAPI mouse_event (DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "mouse_event()");
  IUser32::get_instance()->mouse_event(dwFlags, dx, dy, dwData, dwExtraInfo);
}

DLLEXPORT UINT WINAPI SendInput (UINT cInputs, LPINPUT pInputs, int cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendInput()");
  return IUser32::get_instance()->SendInput(cInputs, pInputs, cbSize);
}

DLLEXPORT WINBOOL WINAPI GetTouchInputInfo (HTOUCHINPUT hTouchInput, UINT cInputs, PTOUCHINPUT pInputs, int cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTouchInputInfo()");
  return IUser32::get_instance()->GetTouchInputInfo(hTouchInput, cInputs, pInputs, cbSize);
}

DLLEXPORT WINBOOL WINAPI CloseTouchInputHandle (HTOUCHINPUT hTouchInput)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseTouchInputHandle()");
  return IUser32::get_instance()->CloseTouchInputHandle(hTouchInput);
}

DLLEXPORT WINBOOL WINAPI RegisterTouchWindow (HWND hwnd, ULONG ulFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterTouchWindow()");
  return IUser32::get_instance()->RegisterTouchWindow(hwnd, ulFlags);
}

DLLEXPORT WINBOOL WINAPI UnregisterTouchWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterTouchWindow()");
  return IUser32::get_instance()->UnregisterTouchWindow(hwnd);
}

DLLEXPORT WINBOOL WINAPI IsTouchWindow (HWND hwnd, PULONG pulFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsTouchWindow()");
  return IUser32::get_instance()->IsTouchWindow(hwnd, pulFlags);
}

DLLEXPORT WINBOOL WINAPI InitializeTouchInjection (UINT32 maxCount, DWORD dwMode)
{
  logging::log("wrapper", logging::LogLevel::debug, "InitializeTouchInjection()");
  return IUser32::get_instance()->InitializeTouchInjection(maxCount, dwMode);
}

DLLEXPORT WINBOOL WINAPI InjectTouchInput (UINT32 count, CONST POINTER_TOUCH_INFO * contacts)
{
  logging::log("wrapper", logging::LogLevel::debug, "InjectTouchInput()");
  return IUser32::get_instance()->InjectTouchInput(count, contacts);
}

DLLEXPORT WINBOOL WINAPI GetPointerType (UINT32 pointerId, POINTER_INPUT_TYPE * pointerType)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerType()");
  return IUser32::get_instance()->GetPointerType(pointerId, pointerType);
}

DLLEXPORT WINBOOL WINAPI GetPointerCursorId (UINT32 pointerId, UINT32 * cursorId)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerCursorId()");
  return IUser32::get_instance()->GetPointerCursorId(pointerId, cursorId);
}

DLLEXPORT WINBOOL WINAPI GetPointerInfo (UINT32 pointerId, POINTER_INFO * pointerInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerInfo()");
  return IUser32::get_instance()->GetPointerInfo(pointerId, pointerInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerInfoHistory (UINT32 pointerId, UINT32 * entriesCount, POINTER_INFO * pointerInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerInfoHistory()");
  return IUser32::get_instance()->GetPointerInfoHistory(pointerId, entriesCount, pointerInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFrameInfo (UINT32 pointerId, UINT32 * pointerCount, POINTER_INFO * pointerInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFrameInfo()");
  return IUser32::get_instance()->GetPointerFrameInfo(pointerId, pointerCount, pointerInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFrameInfoHistory (UINT32 pointerId, UINT32 * entriesCount, UINT32 * pointerCount, POINTER_INFO * pointerInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFrameInfoHistory()");
  return IUser32::get_instance()->GetPointerFrameInfoHistory(pointerId, entriesCount, pointerCount, pointerInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerTouchInfo (UINT32 pointerId, POINTER_TOUCH_INFO * touchInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerTouchInfo()");
  return IUser32::get_instance()->GetPointerTouchInfo(pointerId, touchInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerTouchInfoHistory (UINT32 pointerId, UINT32 * entriesCount, POINTER_TOUCH_INFO * touchInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerTouchInfoHistory()");
  return IUser32::get_instance()->GetPointerTouchInfoHistory(pointerId, entriesCount, touchInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFrameTouchInfo (UINT32 pointerId, UINT32 * pointerCount, POINTER_TOUCH_INFO * touchInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFrameTouchInfo()");
  return IUser32::get_instance()->GetPointerFrameTouchInfo(pointerId, pointerCount, touchInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFrameTouchInfoHistory (UINT32 pointerId, UINT32 * entriesCount, UINT32 * pointerCount, POINTER_TOUCH_INFO * touchInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFrameTouchInfoHistory()");
  return IUser32::get_instance()->GetPointerFrameTouchInfoHistory(pointerId, entriesCount, pointerCount, touchInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerPenInfo (UINT32 pointerId, POINTER_PEN_INFO * penInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerPenInfo()");
  return IUser32::get_instance()->GetPointerPenInfo(pointerId, penInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerPenInfoHistory (UINT32 pointerId, UINT32 * entriesCount, POINTER_PEN_INFO * penInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerPenInfoHistory()");
  return IUser32::get_instance()->GetPointerPenInfoHistory(pointerId, entriesCount, penInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFramePenInfo (UINT32 pointerId, UINT32 * pointerCount, POINTER_PEN_INFO * penInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFramePenInfo()");
  return IUser32::get_instance()->GetPointerFramePenInfo(pointerId, pointerCount, penInfo);
}

DLLEXPORT WINBOOL WINAPI GetPointerFramePenInfoHistory (UINT32 pointerId, UINT32 * entriesCount, UINT32 * pointerCount, POINTER_PEN_INFO * penInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFramePenInfoHistory()");
  return IUser32::get_instance()->GetPointerFramePenInfoHistory(pointerId, entriesCount, pointerCount, penInfo);
}

DLLEXPORT WINBOOL WINAPI SkipPointerFrameMessages (UINT32 pointerId)
{
  logging::log("wrapper", logging::LogLevel::debug, "SkipPointerFrameMessages()");
  return IUser32::get_instance()->SkipPointerFrameMessages(pointerId);
}

DLLEXPORT WINBOOL WINAPI RegisterPointerInputTarget (HWND hwnd, POINTER_INPUT_TYPE pointerType)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterPointerInputTarget()");
  return IUser32::get_instance()->RegisterPointerInputTarget(hwnd, pointerType);
}

DLLEXPORT WINBOOL WINAPI UnregisterPointerInputTarget (HWND hwnd, POINTER_INPUT_TYPE pointerType)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterPointerInputTarget()");
  return IUser32::get_instance()->UnregisterPointerInputTarget(hwnd, pointerType);
}

DLLEXPORT WINBOOL WINAPI EnableMouseInPointer (WINBOOL fEnable)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnableMouseInPointer()");
  return IUser32::get_instance()->EnableMouseInPointer(fEnable);
}

DLLEXPORT WINBOOL WINAPI IsMouseInPointerEnabled (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsMouseInPointerEnabled()");
  return IUser32::get_instance()->IsMouseInPointerEnabled();
}

DLLEXPORT WINBOOL WINAPI RegisterTouchHitTestingWindow (HWND hwnd, ULONG value)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterTouchHitTestingWindow()");
  return IUser32::get_instance()->RegisterTouchHitTestingWindow(hwnd, value);
}

DLLEXPORT WINBOOL WINAPI EvaluateProximityToRect (const RECT * controlBoundingBox, const TOUCH_HIT_TESTING_INPUT * pHitTestingInput, TOUCH_HIT_TESTING_PROXIMITY_EVALUATION * pProximityEval)
{
  logging::log("wrapper", logging::LogLevel::debug, "EvaluateProximityToRect()");
  return IUser32::get_instance()->EvaluateProximityToRect(controlBoundingBox, pHitTestingInput, pProximityEval);
}

DLLEXPORT WINBOOL WINAPI EvaluateProximityToPolygon (UINT32 numVertices, const POINT * controlPolygon, const TOUCH_HIT_TESTING_INPUT * pHitTestingInput, TOUCH_HIT_TESTING_PROXIMITY_EVALUATION * pProximityEval)
{
  logging::log("wrapper", logging::LogLevel::debug, "EvaluateProximityToPolygon()");
  return IUser32::get_instance()->EvaluateProximityToPolygon(numVertices, controlPolygon, pHitTestingInput, pProximityEval);
}

DLLEXPORT LRESULT WINAPI PackTouchHitTestingProximityEvaluation (const TOUCH_HIT_TESTING_INPUT * pHitTestingInput, const TOUCH_HIT_TESTING_PROXIMITY_EVALUATION * pProximityEval)
{
  logging::log("wrapper", logging::LogLevel::debug, "PackTouchHitTestingProximityEvaluation()");
  return IUser32::get_instance()->PackTouchHitTestingProximityEvaluation(pHitTestingInput, pProximityEval);
}

DLLEXPORT WINBOOL WINAPI GetWindowFeedbackSetting (HWND hwnd, FEEDBACK_TYPE feedback, DWORD dwFlags, UINT32 * pSize, VOID * config)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowFeedbackSetting()");
  return IUser32::get_instance()->GetWindowFeedbackSetting(hwnd, feedback, dwFlags, pSize, config);
}

DLLEXPORT WINBOOL WINAPI SetWindowFeedbackSetting (HWND hwnd, FEEDBACK_TYPE feedback, DWORD dwFlags, UINT32 size, CONST VOID * configuration)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowFeedbackSetting()");
  return IUser32::get_instance()->SetWindowFeedbackSetting(hwnd, feedback, dwFlags, size, configuration);
}

DLLEXPORT WINBOOL WINAPI GetLastInputInfo (PLASTINPUTINFO plii)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetLastInputInfo()");
  return IUser32::get_instance()->GetLastInputInfo(plii);
}

DLLEXPORT UINT WINAPI MapVirtualKeyA (UINT uCode, UINT uMapType)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapVirtualKeyA()");
  return IUser32::get_instance()->MapVirtualKeyA(uCode, uMapType);
}

DLLEXPORT UINT WINAPI MapVirtualKeyW (UINT uCode, UINT uMapType)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapVirtualKeyW()");
  return IUser32::get_instance()->MapVirtualKeyW(uCode, uMapType);
}

DLLEXPORT UINT WINAPI MapVirtualKeyExA (UINT uCode, UINT uMapType, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapVirtualKeyExA()");
  return IUser32::get_instance()->MapVirtualKeyExA(uCode, uMapType, dwhkl);
}

DLLEXPORT UINT WINAPI MapVirtualKeyExW (UINT uCode, UINT uMapType, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapVirtualKeyExW()");
  return IUser32::get_instance()->MapVirtualKeyExW(uCode, uMapType, dwhkl);
}

DLLEXPORT WINBOOL WINAPI GetInputState (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetInputState()");
  return IUser32::get_instance()->GetInputState();
}

DLLEXPORT DWORD WINAPI GetQueueStatus (UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetQueueStatus()");
  return IUser32::get_instance()->GetQueueStatus(flags);
}

DLLEXPORT HWND WINAPI GetCapture (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCapture()");
  return IUser32::get_instance()->GetCapture();
}

DLLEXPORT HWND WINAPI SetCapture (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCapture()");
  return IUser32::get_instance()->SetCapture(hWnd);
}

DLLEXPORT WINBOOL WINAPI ReleaseCapture (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "ReleaseCapture()");
  return IUser32::get_instance()->ReleaseCapture();
}

DLLEXPORT DWORD WINAPI MsgWaitForMultipleObjects (DWORD nCount, CONST HANDLE * pHandles, WINBOOL fWaitAll, DWORD dwMilliseconds, DWORD dwWakeMask)
{
  logging::log("wrapper", logging::LogLevel::debug, "MsgWaitForMultipleObjects()");
  return IUser32::get_instance()->MsgWaitForMultipleObjects(nCount, pHandles, fWaitAll, dwMilliseconds, dwWakeMask);
}

DLLEXPORT DWORD WINAPI MsgWaitForMultipleObjectsEx (DWORD nCount, CONST HANDLE * pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "MsgWaitForMultipleObjectsEx()");
  return IUser32::get_instance()->MsgWaitForMultipleObjectsEx(nCount, pHandles, dwMilliseconds, dwWakeMask, dwFlags);
}

DLLEXPORT UINT_PTR WINAPI SetTimer (HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetTimer()");
  return IUser32::get_instance()->SetTimer(hWnd, nIDEvent, uElapse, lpTimerFunc);
}

DLLEXPORT WINBOOL WINAPI KillTimer (HWND hWnd, UINT_PTR uIDEvent)
{
  logging::log("wrapper", logging::LogLevel::debug, "KillTimer()");
  return IUser32::get_instance()->KillTimer(hWnd, uIDEvent);
}

DLLEXPORT WINBOOL WINAPI IsWindowUnicode (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWindowUnicode()");
  return IUser32::get_instance()->IsWindowUnicode(hWnd);
}

DLLEXPORT WINBOOL WINAPI EnableWindow (HWND hWnd, WINBOOL bEnable)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnableWindow()");
  return IUser32::get_instance()->EnableWindow(hWnd, bEnable);
}

DLLEXPORT WINBOOL WINAPI IsWindowEnabled (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWindowEnabled()");
  return IUser32::get_instance()->IsWindowEnabled(hWnd);
}

DLLEXPORT HACCEL WINAPI LoadAcceleratorsA (HINSTANCE hInstance, LPCSTR lpTableName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadAcceleratorsA()");
  return IUser32::get_instance()->LoadAcceleratorsA(hInstance, lpTableName);
}

DLLEXPORT HACCEL WINAPI LoadAcceleratorsW (HINSTANCE hInstance, LPCWSTR lpTableName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadAcceleratorsW()");
  return IUser32::get_instance()->LoadAcceleratorsW(hInstance, lpTableName);
}

DLLEXPORT HACCEL WINAPI CreateAcceleratorTableA (LPACCEL paccel, int cAccel)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateAcceleratorTableA()");
  return IUser32::get_instance()->CreateAcceleratorTableA(paccel, cAccel);
}

DLLEXPORT HACCEL WINAPI CreateAcceleratorTableW (LPACCEL paccel, int cAccel)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateAcceleratorTableW()");
  return IUser32::get_instance()->CreateAcceleratorTableW(paccel, cAccel);
}

DLLEXPORT WINBOOL WINAPI DestroyAcceleratorTable (HACCEL hAccel)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyAcceleratorTable()");
  return IUser32::get_instance()->DestroyAcceleratorTable(hAccel);
}

DLLEXPORT int WINAPI CopyAcceleratorTableA (HACCEL hAccelSrc, LPACCEL lpAccelDst, int cAccelEntries)
{
  logging::log("wrapper", logging::LogLevel::debug, "CopyAcceleratorTableA()");
  return IUser32::get_instance()->CopyAcceleratorTableA(hAccelSrc, lpAccelDst, cAccelEntries);
}

DLLEXPORT int WINAPI CopyAcceleratorTableW (HACCEL hAccelSrc, LPACCEL lpAccelDst, int cAccelEntries)
{
  logging::log("wrapper", logging::LogLevel::debug, "CopyAcceleratorTableW()");
  return IUser32::get_instance()->CopyAcceleratorTableW(hAccelSrc, lpAccelDst, cAccelEntries);
}

DLLEXPORT int WINAPI TranslateAcceleratorA (HWND hWnd, HACCEL hAccTable, LPMSG lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "TranslateAcceleratorA()");
  return IUser32::get_instance()->TranslateAcceleratorA(hWnd, hAccTable, lpMsg);
}

DLLEXPORT int WINAPI TranslateAcceleratorW (HWND hWnd, HACCEL hAccTable, LPMSG lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "TranslateAcceleratorW()");
  return IUser32::get_instance()->TranslateAcceleratorW(hWnd, hAccTable, lpMsg);
}

DLLEXPORT UINT_PTR WINAPI SetCoalescableTimer (HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc, ULONG uToleranceDelay)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCoalescableTimer()");
  return IUser32::get_instance()->SetCoalescableTimer(hWnd, nIDEvent, uElapse, lpTimerFunc, uToleranceDelay);
}

DLLEXPORT int WINAPI GetSystemMetrics (int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSystemMetrics()");
  return IUser32::get_instance()->GetSystemMetrics(nIndex);
}

DLLEXPORT HMENU WINAPI LoadMenuA (HINSTANCE hInstance, LPCSTR lpMenuName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadMenuA()");
  return IUser32::get_instance()->LoadMenuA(hInstance, lpMenuName);
}

DLLEXPORT HMENU WINAPI LoadMenuW (HINSTANCE hInstance, LPCWSTR lpMenuName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadMenuW()");
  return IUser32::get_instance()->LoadMenuW(hInstance, lpMenuName);
}

DLLEXPORT HMENU WINAPI LoadMenuIndirectA (CONST MENUTEMPLATEA * lpMenuTemplate)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadMenuIndirectA()");
  return IUser32::get_instance()->LoadMenuIndirectA(lpMenuTemplate);
}

DLLEXPORT HMENU WINAPI LoadMenuIndirectW (CONST MENUTEMPLATEW * lpMenuTemplate)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadMenuIndirectW()");
  return IUser32::get_instance()->LoadMenuIndirectW(lpMenuTemplate);
}

DLLEXPORT HMENU WINAPI GetMenu (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenu()");
  return IUser32::get_instance()->GetMenu(hWnd);
}

DLLEXPORT WINBOOL WINAPI SetMenu (HWND hWnd, HMENU hMenu)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenu()");
  return IUser32::get_instance()->SetMenu(hWnd, hMenu);
}

DLLEXPORT WINBOOL WINAPI ChangeMenuA (HMENU hMenu, UINT cmd, LPCSTR lpszNewItem, UINT cmdInsert, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeMenuA()");
  return IUser32::get_instance()->ChangeMenuA(hMenu, cmd, lpszNewItem, cmdInsert, flags);
}

DLLEXPORT WINBOOL WINAPI ChangeMenuW (HMENU hMenu, UINT cmd, LPCWSTR lpszNewItem, UINT cmdInsert, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeMenuW()");
  return IUser32::get_instance()->ChangeMenuW(hMenu, cmd, lpszNewItem, cmdInsert, flags);
}

DLLEXPORT WINBOOL WINAPI HiliteMenuItem (HWND hWnd, HMENU hMenu, UINT uIDHiliteItem, UINT uHilite)
{
  logging::log("wrapper", logging::LogLevel::debug, "HiliteMenuItem()");
  return IUser32::get_instance()->HiliteMenuItem(hWnd, hMenu, uIDHiliteItem, uHilite);
}

DLLEXPORT int WINAPI GetMenuStringA (HMENU hMenu, UINT uIDItem, LPSTR lpString, int cchMax, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuStringA()");
  return IUser32::get_instance()->GetMenuStringA(hMenu, uIDItem, lpString, cchMax, flags);
}

DLLEXPORT int WINAPI GetMenuStringW (HMENU hMenu, UINT uIDItem, LPWSTR lpString, int cchMax, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuStringW()");
  return IUser32::get_instance()->GetMenuStringW(hMenu, uIDItem, lpString, cchMax, flags);
}

DLLEXPORT UINT WINAPI GetMenuState (HMENU hMenu, UINT uId, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuState()");
  return IUser32::get_instance()->GetMenuState(hMenu, uId, uFlags);
}

DLLEXPORT WINBOOL WINAPI DrawMenuBar (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawMenuBar()");
  return IUser32::get_instance()->DrawMenuBar(hWnd);
}

DLLEXPORT HMENU WINAPI GetSystemMenu (HWND hWnd, WINBOOL bRevert)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSystemMenu()");
  return IUser32::get_instance()->GetSystemMenu(hWnd, bRevert);
}

DLLEXPORT HMENU WINAPI CreateMenu (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateMenu()");
  return IUser32::get_instance()->CreateMenu();
}

DLLEXPORT HMENU WINAPI CreatePopupMenu (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreatePopupMenu()");
  return IUser32::get_instance()->CreatePopupMenu();
}

DLLEXPORT WINBOOL WINAPI DestroyMenu (HMENU hMenu)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyMenu()");
  return IUser32::get_instance()->DestroyMenu(hMenu);
}

DLLEXPORT DWORD WINAPI CheckMenuItem (HMENU hMenu, UINT uIDCheckItem, UINT uCheck)
{
  logging::log("wrapper", logging::LogLevel::debug, "CheckMenuItem()");
  return IUser32::get_instance()->CheckMenuItem(hMenu, uIDCheckItem, uCheck);
}

DLLEXPORT WINBOOL WINAPI EnableMenuItem (HMENU hMenu, UINT uIDEnableItem, UINT uEnable)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnableMenuItem()");
  return IUser32::get_instance()->EnableMenuItem(hMenu, uIDEnableItem, uEnable);
}

DLLEXPORT HMENU WINAPI GetSubMenu (HMENU hMenu, int nPos)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSubMenu()");
  return IUser32::get_instance()->GetSubMenu(hMenu, nPos);
}

DLLEXPORT UINT WINAPI GetMenuItemID (HMENU hMenu, int nPos)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuItemID()");
  return IUser32::get_instance()->GetMenuItemID(hMenu, nPos);
}

DLLEXPORT int WINAPI GetMenuItemCount (HMENU hMenu)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuItemCount()");
  return IUser32::get_instance()->GetMenuItemCount(hMenu);
}

DLLEXPORT WINBOOL WINAPI InsertMenuA (HMENU hMenu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "InsertMenuA()");
  return IUser32::get_instance()->InsertMenuA(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI InsertMenuW (HMENU hMenu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "InsertMenuW()");
  return IUser32::get_instance()->InsertMenuW(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI AppendMenuA (HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "AppendMenuA()");
  return IUser32::get_instance()->AppendMenuA(hMenu, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI AppendMenuW (HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "AppendMenuW()");
  return IUser32::get_instance()->AppendMenuW(hMenu, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI ModifyMenuA (HMENU hMnu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "ModifyMenuA()");
  return IUser32::get_instance()->ModifyMenuA(hMnu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI ModifyMenuW (HMENU hMnu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "ModifyMenuW()");
  return IUser32::get_instance()->ModifyMenuW(hMnu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

DLLEXPORT WINBOOL WINAPI RemoveMenu (HMENU hMenu, UINT uPosition, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RemoveMenu()");
  return IUser32::get_instance()->RemoveMenu(hMenu, uPosition, uFlags);
}

DLLEXPORT WINBOOL WINAPI DeleteMenu (HMENU hMenu, UINT uPosition, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DeleteMenu()");
  return IUser32::get_instance()->DeleteMenu(hMenu, uPosition, uFlags);
}

DLLEXPORT WINBOOL WINAPI SetMenuItemBitmaps (HMENU hMenu, UINT uPosition, UINT uFlags, HBITMAP hBitmapUnchecked, HBITMAP hBitmapChecked)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuItemBitmaps()");
  return IUser32::get_instance()->SetMenuItemBitmaps(hMenu, uPosition, uFlags, hBitmapUnchecked, hBitmapChecked);
}

DLLEXPORT LONG WINAPI GetMenuCheckMarkDimensions (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuCheckMarkDimensions()");
  return IUser32::get_instance()->GetMenuCheckMarkDimensions();
}

DLLEXPORT WINBOOL WINAPI TrackPopupMenu (HMENU hMenu, UINT uFlags, int x, int y, int nReserved, HWND hWnd, CONST RECT * prcRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "TrackPopupMenu()");
  return IUser32::get_instance()->TrackPopupMenu(hMenu, uFlags, x, y, nReserved, hWnd, prcRect);
}

DLLEXPORT WINBOOL WINAPI TrackPopupMenuEx (HMENU arg0, UINT arg1, int arg2, int arg3, HWND arg4, LPTPMPARAMS arg5)
{
  logging::log("wrapper", logging::LogLevel::debug, "TrackPopupMenuEx()");
  return IUser32::get_instance()->TrackPopupMenuEx(arg0, arg1, arg2, arg3, arg4, arg5);
}

DLLEXPORT WINBOOL WINAPI GetMenuInfo (HMENU arg0, LPMENUINFO arg1)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuInfo()");
  return IUser32::get_instance()->GetMenuInfo(arg0, arg1);
}

DLLEXPORT WINBOOL WINAPI SetMenuInfo (HMENU arg0, LPCMENUINFO arg1)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuInfo()");
  return IUser32::get_instance()->SetMenuInfo(arg0, arg1);
}

DLLEXPORT WINBOOL WINAPI EndMenu (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "EndMenu()");
  return IUser32::get_instance()->EndMenu();
}

DLLEXPORT WINBOOL WINAPI CalculatePopupWindowPosition (const POINT * anchorPoint, const SIZE * windowSize, UINT flags, RECT * excludeRect, RECT * popupWindowPosition)
{
  logging::log("wrapper", logging::LogLevel::debug, "CalculatePopupWindowPosition()");
  return IUser32::get_instance()->CalculatePopupWindowPosition(anchorPoint, windowSize, flags, excludeRect, popupWindowPosition);
}

DLLEXPORT WINBOOL WINAPI InsertMenuItemA (HMENU hmenu, UINT item, WINBOOL fByPosition, LPCMENUITEMINFOA lpmi)
{
  logging::log("wrapper", logging::LogLevel::debug, "InsertMenuItemA()");
  return IUser32::get_instance()->InsertMenuItemA(hmenu, item, fByPosition, lpmi);
}

DLLEXPORT WINBOOL WINAPI InsertMenuItemW (HMENU hmenu, UINT item, WINBOOL fByPosition, LPCMENUITEMINFOW lpmi)
{
  logging::log("wrapper", logging::LogLevel::debug, "InsertMenuItemW()");
  return IUser32::get_instance()->InsertMenuItemW(hmenu, item, fByPosition, lpmi);
}

DLLEXPORT WINBOOL WINAPI GetMenuItemInfoA (HMENU hmenu, UINT item, WINBOOL fByPosition, LPMENUITEMINFOA lpmii)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuItemInfoA()");
  return IUser32::get_instance()->GetMenuItemInfoA(hmenu, item, fByPosition, lpmii);
}

DLLEXPORT WINBOOL WINAPI GetMenuItemInfoW (HMENU hmenu, UINT item, WINBOOL fByPosition, LPMENUITEMINFOW lpmii)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuItemInfoW()");
  return IUser32::get_instance()->GetMenuItemInfoW(hmenu, item, fByPosition, lpmii);
}

DLLEXPORT WINBOOL WINAPI SetMenuItemInfoA (HMENU hmenu, UINT item, WINBOOL fByPositon, LPCMENUITEMINFOA lpmii)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuItemInfoA()");
  return IUser32::get_instance()->SetMenuItemInfoA(hmenu, item, fByPositon, lpmii);
}

DLLEXPORT WINBOOL WINAPI SetMenuItemInfoW (HMENU hmenu, UINT item, WINBOOL fByPositon, LPCMENUITEMINFOW lpmii)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuItemInfoW()");
  return IUser32::get_instance()->SetMenuItemInfoW(hmenu, item, fByPositon, lpmii);
}

DLLEXPORT UINT WINAPI GetMenuDefaultItem (HMENU hMenu, UINT fByPos, UINT gmdiFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuDefaultItem()");
  return IUser32::get_instance()->GetMenuDefaultItem(hMenu, fByPos, gmdiFlags);
}

DLLEXPORT WINBOOL WINAPI SetMenuDefaultItem (HMENU hMenu, UINT uItem, UINT fByPos)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuDefaultItem()");
  return IUser32::get_instance()->SetMenuDefaultItem(hMenu, uItem, fByPos);
}

DLLEXPORT WINBOOL WINAPI GetMenuItemRect (HWND hWnd, HMENU hMenu, UINT uItem, LPRECT lprcItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuItemRect()");
  return IUser32::get_instance()->GetMenuItemRect(hWnd, hMenu, uItem, lprcItem);
}

DLLEXPORT int WINAPI MenuItemFromPoint (HWND hWnd, HMENU hMenu, POINT ptScreen)
{
  logging::log("wrapper", logging::LogLevel::debug, "MenuItemFromPoint()");
  return IUser32::get_instance()->MenuItemFromPoint(hWnd, hMenu, ptScreen);
}

DLLEXPORT DWORD WINAPI DragObject (HWND hwndParent, HWND hwndFrom, UINT fmt, ULONG_PTR data, HCURSOR hcur)
{
  logging::log("wrapper", logging::LogLevel::debug, "DragObject()");
  return IUser32::get_instance()->DragObject(hwndParent, hwndFrom, fmt, data, hcur);
}

DLLEXPORT WINBOOL WINAPI DragDetect (HWND hwnd, POINT pt)
{
  logging::log("wrapper", logging::LogLevel::debug, "DragDetect()");
  return IUser32::get_instance()->DragDetect(hwnd, pt);
}

DLLEXPORT WINBOOL WINAPI DrawIcon (HDC hDC, int X, int Y, HICON hIcon)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawIcon()");
  return IUser32::get_instance()->DrawIcon(hDC, X, Y, hIcon);
}

DLLEXPORT int WINAPI DrawTextA (HDC hdc, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawTextA()");
  return IUser32::get_instance()->DrawTextA(hdc, lpchText, cchText, lprc, format);
}

DLLEXPORT int WINAPI DrawTextW (HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawTextW()");
  return IUser32::get_instance()->DrawTextW(hdc, lpchText, cchText, lprc, format);
}

DLLEXPORT int WINAPI DrawTextExA (HDC hdc, LPSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawTextExA()");
  return IUser32::get_instance()->DrawTextExA(hdc, lpchText, cchText, lprc, format, lpdtp);
}

DLLEXPORT int WINAPI DrawTextExW (HDC hdc, LPWSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawTextExW()");
  return IUser32::get_instance()->DrawTextExW(hdc, lpchText, cchText, lprc, format, lpdtp);
}

DLLEXPORT WINBOOL WINAPI GrayStringA (HDC hDC, HBRUSH hBrush, GRAYSTRINGPROC lpOutputFunc, LPARAM lpData, int nCount, int X, int Y, int nWidth, int nHeight)
{
  logging::log("wrapper", logging::LogLevel::debug, "GrayStringA()");
  return IUser32::get_instance()->GrayStringA(hDC, hBrush, lpOutputFunc, lpData, nCount, X, Y, nWidth, nHeight);
}

DLLEXPORT WINBOOL WINAPI GrayStringW (HDC hDC, HBRUSH hBrush, GRAYSTRINGPROC lpOutputFunc, LPARAM lpData, int nCount, int X, int Y, int nWidth, int nHeight)
{
  logging::log("wrapper", logging::LogLevel::debug, "GrayStringW()");
  return IUser32::get_instance()->GrayStringW(hDC, hBrush, lpOutputFunc, lpData, nCount, X, Y, nWidth, nHeight);
}

DLLEXPORT WINBOOL WINAPI DrawStateA (HDC hdc, HBRUSH hbrFore, DRAWSTATEPROC qfnCallBack, LPARAM lData, WPARAM wData, int x, int y, int cx, int cy, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawStateA()");
  return IUser32::get_instance()->DrawStateA(hdc, hbrFore, qfnCallBack, lData, wData, x, y, cx, cy, uFlags);
}

DLLEXPORT WINBOOL WINAPI DrawStateW (HDC hdc, HBRUSH hbrFore, DRAWSTATEPROC qfnCallBack, LPARAM lData, WPARAM wData, int x, int y, int cx, int cy, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawStateW()");
  return IUser32::get_instance()->DrawStateW(hdc, hbrFore, qfnCallBack, lData, wData, x, y, cx, cy, uFlags);
}

DLLEXPORT LONG WINAPI TabbedTextOutA (HDC hdc, int x, int y, LPCSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions, int nTabOrigin)
{
  logging::log("wrapper", logging::LogLevel::debug, "TabbedTextOutA()");
  return IUser32::get_instance()->TabbedTextOutA(hdc, x, y, lpString, chCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
}

DLLEXPORT LONG WINAPI TabbedTextOutW (HDC hdc, int x, int y, LPCWSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions, int nTabOrigin)
{
  logging::log("wrapper", logging::LogLevel::debug, "TabbedTextOutW()");
  return IUser32::get_instance()->TabbedTextOutW(hdc, x, y, lpString, chCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
}

DLLEXPORT DWORD WINAPI GetTabbedTextExtentA (HDC hdc, LPCSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTabbedTextExtentA()");
  return IUser32::get_instance()->GetTabbedTextExtentA(hdc, lpString, chCount, nTabPositions, lpnTabStopPositions);
}

DLLEXPORT DWORD WINAPI GetTabbedTextExtentW (HDC hdc, LPCWSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTabbedTextExtentW()");
  return IUser32::get_instance()->GetTabbedTextExtentW(hdc, lpString, chCount, nTabPositions, lpnTabStopPositions);
}

DLLEXPORT WINBOOL WINAPI UpdateWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "UpdateWindow()");
  return IUser32::get_instance()->UpdateWindow(hWnd);
}

DLLEXPORT HWND WINAPI SetActiveWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetActiveWindow()");
  return IUser32::get_instance()->SetActiveWindow(hWnd);
}

DLLEXPORT HWND WINAPI GetForegroundWindow (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetForegroundWindow()");
  return IUser32::get_instance()->GetForegroundWindow();
}

DLLEXPORT WINBOOL WINAPI PaintDesktop (HDC hdc)
{
  logging::log("wrapper", logging::LogLevel::debug, "PaintDesktop()");
  return IUser32::get_instance()->PaintDesktop(hdc);
}

DLLEXPORT VOID WINAPI SwitchToThisWindow (HWND hwnd, WINBOOL fUnknown)
{
  logging::log("wrapper", logging::LogLevel::debug, "SwitchToThisWindow()");
  IUser32::get_instance()->SwitchToThisWindow(hwnd, fUnknown);
}

DLLEXPORT WINBOOL WINAPI SetForegroundWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetForegroundWindow()");
  return IUser32::get_instance()->SetForegroundWindow(hWnd);
}

DLLEXPORT WINBOOL WINAPI AllowSetForegroundWindow (DWORD dwProcessId)
{
  logging::log("wrapper", logging::LogLevel::debug, "AllowSetForegroundWindow()");
  return IUser32::get_instance()->AllowSetForegroundWindow(dwProcessId);
}

DLLEXPORT WINBOOL WINAPI LockSetForegroundWindow (UINT uLockCode)
{
  logging::log("wrapper", logging::LogLevel::debug, "LockSetForegroundWindow()");
  return IUser32::get_instance()->LockSetForegroundWindow(uLockCode);
}

DLLEXPORT HWND WINAPI WindowFromDC (HDC hDC)
{
  logging::log("wrapper", logging::LogLevel::debug, "WindowFromDC()");
  return IUser32::get_instance()->WindowFromDC(hDC);
}

DLLEXPORT HDC WINAPI GetDC (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDC()");
  return IUser32::get_instance()->GetDC(hWnd);
}

DLLEXPORT HDC WINAPI GetDCEx (HWND hWnd, HRGN hrgnClip, DWORD flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDCEx()");
  return IUser32::get_instance()->GetDCEx(hWnd, hrgnClip, flags);
}

DLLEXPORT HDC WINAPI GetWindowDC (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowDC()");
  return IUser32::get_instance()->GetWindowDC(hWnd);
}

DLLEXPORT int WINAPI ReleaseDC (HWND hWnd, HDC hDC)
{
  logging::log("wrapper", logging::LogLevel::debug, "ReleaseDC()");
  return IUser32::get_instance()->ReleaseDC(hWnd, hDC);
}

DLLEXPORT HDC WINAPI BeginPaint (HWND hWnd, LPPAINTSTRUCT lpPaint)
{
  logging::log("wrapper", logging::LogLevel::debug, "BeginPaint()");
  return IUser32::get_instance()->BeginPaint(hWnd, lpPaint);
}

DLLEXPORT WINBOOL WINAPI EndPaint (HWND hWnd, CONST PAINTSTRUCT * lpPaint)
{
  logging::log("wrapper", logging::LogLevel::debug, "EndPaint()");
  return IUser32::get_instance()->EndPaint(hWnd, lpPaint);
}

DLLEXPORT WINBOOL WINAPI GetUpdateRect (HWND hWnd, LPRECT lpRect, WINBOOL bErase)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUpdateRect()");
  return IUser32::get_instance()->GetUpdateRect(hWnd, lpRect, bErase);
}

DLLEXPORT int WINAPI GetUpdateRgn (HWND hWnd, HRGN hRgn, WINBOOL bErase)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUpdateRgn()");
  return IUser32::get_instance()->GetUpdateRgn(hWnd, hRgn, bErase);
}

DLLEXPORT int WINAPI SetWindowRgn (HWND hWnd, HRGN hRgn, WINBOOL bRedraw)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowRgn()");
  return IUser32::get_instance()->SetWindowRgn(hWnd, hRgn, bRedraw);
}

DLLEXPORT int WINAPI GetWindowRgn (HWND hWnd, HRGN hRgn)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowRgn()");
  return IUser32::get_instance()->GetWindowRgn(hWnd, hRgn);
}

DLLEXPORT int WINAPI GetWindowRgnBox (HWND hWnd, LPRECT lprc)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowRgnBox()");
  return IUser32::get_instance()->GetWindowRgnBox(hWnd, lprc);
}

DLLEXPORT int WINAPI ExcludeUpdateRgn (HDC hDC, HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "ExcludeUpdateRgn()");
  return IUser32::get_instance()->ExcludeUpdateRgn(hDC, hWnd);
}

DLLEXPORT WINBOOL WINAPI InvalidateRect (HWND hWnd, CONST RECT * lpRect, WINBOOL bErase)
{
  logging::log("wrapper", logging::LogLevel::debug, "InvalidateRect()");
  return IUser32::get_instance()->InvalidateRect(hWnd, lpRect, bErase);
}

DLLEXPORT WINBOOL WINAPI ValidateRect (HWND hWnd, CONST RECT * lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "ValidateRect()");
  return IUser32::get_instance()->ValidateRect(hWnd, lpRect);
}

DLLEXPORT WINBOOL WINAPI InvalidateRgn (HWND hWnd, HRGN hRgn, WINBOOL bErase)
{
  logging::log("wrapper", logging::LogLevel::debug, "InvalidateRgn()");
  return IUser32::get_instance()->InvalidateRgn(hWnd, hRgn, bErase);
}

DLLEXPORT WINBOOL WINAPI ValidateRgn (HWND hWnd, HRGN hRgn)
{
  logging::log("wrapper", logging::LogLevel::debug, "ValidateRgn()");
  return IUser32::get_instance()->ValidateRgn(hWnd, hRgn);
}

DLLEXPORT WINBOOL WINAPI RedrawWindow (HWND hWnd, CONST RECT * lprcUpdate, HRGN hrgnUpdate, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RedrawWindow()");
  return IUser32::get_instance()->RedrawWindow(hWnd, lprcUpdate, hrgnUpdate, flags);
}

DLLEXPORT WINBOOL WINAPI LockWindowUpdate (HWND hWndLock)
{
  logging::log("wrapper", logging::LogLevel::debug, "LockWindowUpdate()");
  return IUser32::get_instance()->LockWindowUpdate(hWndLock);
}

DLLEXPORT WINBOOL WINAPI ScrollWindow (HWND hWnd, int XAmount, int YAmount, CONST RECT * lpRect, CONST RECT * lpClipRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollWindow()");
  return IUser32::get_instance()->ScrollWindow(hWnd, XAmount, YAmount, lpRect, lpClipRect);
}

DLLEXPORT WINBOOL WINAPI ScrollDC (HDC hDC, int dx, int dy, CONST RECT * lprcScroll, CONST RECT * lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollDC()");
  return IUser32::get_instance()->ScrollDC(hDC, dx, dy, lprcScroll, lprcClip, hrgnUpdate, lprcUpdate);
}

DLLEXPORT int WINAPI ScrollWindowEx (HWND hWnd, int dx, int dy, CONST RECT * prcScroll, CONST RECT * prcClip, HRGN hrgnUpdate, LPRECT prcUpdate, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollWindowEx()");
  return IUser32::get_instance()->ScrollWindowEx(hWnd, dx, dy, prcScroll, prcClip, hrgnUpdate, prcUpdate, flags);
}

DLLEXPORT int WINAPI SetScrollPos (HWND hWnd, int nBar, int nPos, WINBOOL bRedraw)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetScrollPos()");
  return IUser32::get_instance()->SetScrollPos(hWnd, nBar, nPos, bRedraw);
}

DLLEXPORT int WINAPI GetScrollPos (HWND hWnd, int nBar)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetScrollPos()");
  return IUser32::get_instance()->GetScrollPos(hWnd, nBar);
}

DLLEXPORT WINBOOL WINAPI SetScrollRange (HWND hWnd, int nBar, int nMinPos, int nMaxPos, WINBOOL bRedraw)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetScrollRange()");
  return IUser32::get_instance()->SetScrollRange(hWnd, nBar, nMinPos, nMaxPos, bRedraw);
}

DLLEXPORT WINBOOL WINAPI GetScrollRange (HWND hWnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetScrollRange()");
  return IUser32::get_instance()->GetScrollRange(hWnd, nBar, lpMinPos, lpMaxPos);
}

DLLEXPORT WINBOOL WINAPI ShowScrollBar (HWND hWnd, int wBar, WINBOOL bShow)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowScrollBar()");
  return IUser32::get_instance()->ShowScrollBar(hWnd, wBar, bShow);
}

DLLEXPORT WINBOOL WINAPI EnableScrollBar (HWND hWnd, UINT wSBflags, UINT wArrows)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnableScrollBar()");
  return IUser32::get_instance()->EnableScrollBar(hWnd, wSBflags, wArrows);
}

DLLEXPORT WINBOOL WINAPI SetPropA (HWND hWnd, LPCSTR lpString, HANDLE hData)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetPropA()");
  return IUser32::get_instance()->SetPropA(hWnd, lpString, hData);
}

DLLEXPORT WINBOOL WINAPI SetPropW (HWND hWnd, LPCWSTR lpString, HANDLE hData)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetPropW()");
  return IUser32::get_instance()->SetPropW(hWnd, lpString, hData);
}

DLLEXPORT HANDLE WINAPI GetPropA (HWND hWnd, LPCSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPropA()");
  return IUser32::get_instance()->GetPropA(hWnd, lpString);
}

DLLEXPORT HANDLE WINAPI GetPropW (HWND hWnd, LPCWSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPropW()");
  return IUser32::get_instance()->GetPropW(hWnd, lpString);
}

DLLEXPORT HANDLE WINAPI RemovePropA (HWND hWnd, LPCSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "RemovePropA()");
  return IUser32::get_instance()->RemovePropA(hWnd, lpString);
}

DLLEXPORT HANDLE WINAPI RemovePropW (HWND hWnd, LPCWSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "RemovePropW()");
  return IUser32::get_instance()->RemovePropW(hWnd, lpString);
}

DLLEXPORT int WINAPI EnumPropsExA (HWND hWnd, PROPENUMPROCEXA lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumPropsExA()");
  return IUser32::get_instance()->EnumPropsExA(hWnd, lpEnumFunc, lParam);
}

DLLEXPORT int WINAPI EnumPropsExW (HWND hWnd, PROPENUMPROCEXW lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumPropsExW()");
  return IUser32::get_instance()->EnumPropsExW(hWnd, lpEnumFunc, lParam);
}

DLLEXPORT int WINAPI EnumPropsA (HWND hWnd, PROPENUMPROCA lpEnumFunc)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumPropsA()");
  return IUser32::get_instance()->EnumPropsA(hWnd, lpEnumFunc);
}

DLLEXPORT int WINAPI EnumPropsW (HWND hWnd, PROPENUMPROCW lpEnumFunc)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumPropsW()");
  return IUser32::get_instance()->EnumPropsW(hWnd, lpEnumFunc);
}

DLLEXPORT WINBOOL WINAPI SetWindowTextA (HWND hWnd, LPCSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowTextA()");
  return IUser32::get_instance()->SetWindowTextA(hWnd, lpString);
}

DLLEXPORT WINBOOL WINAPI SetWindowTextW (HWND hWnd, LPCWSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowTextW()");
  return IUser32::get_instance()->SetWindowTextW(hWnd, lpString);
}

DLLEXPORT int WINAPI GetWindowTextA (HWND hWnd, LPSTR lpString, int nMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowTextA()");
  return IUser32::get_instance()->GetWindowTextA(hWnd, lpString, nMaxCount);
}

DLLEXPORT int WINAPI GetWindowTextW (HWND hWnd, LPWSTR lpString, int nMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowTextW()");
  return IUser32::get_instance()->GetWindowTextW(hWnd, lpString, nMaxCount);
}

DLLEXPORT int WINAPI GetWindowTextLengthA (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowTextLengthA()");
  return IUser32::get_instance()->GetWindowTextLengthA(hWnd);
}

DLLEXPORT int WINAPI GetWindowTextLengthW (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowTextLengthW()");
  return IUser32::get_instance()->GetWindowTextLengthW(hWnd);
}

DLLEXPORT WINBOOL WINAPI GetClientRect (HWND hWnd, LPRECT lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClientRect()");
  return IUser32::get_instance()->GetClientRect(hWnd, lpRect);
}

DLLEXPORT WINBOOL WINAPI GetWindowRect (HWND hWnd, LPRECT lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowRect()");
  return IUser32::get_instance()->GetWindowRect(hWnd, lpRect);
}

DLLEXPORT WINBOOL WINAPI AdjustWindowRect (LPRECT lpRect, DWORD dwStyle, WINBOOL bMenu)
{
  logging::log("wrapper", logging::LogLevel::debug, "AdjustWindowRect()");
  return IUser32::get_instance()->AdjustWindowRect(lpRect, dwStyle, bMenu);
}

DLLEXPORT WINBOOL WINAPI AdjustWindowRectEx (LPRECT lpRect, DWORD dwStyle, WINBOOL bMenu, DWORD dwExStyle)
{
  logging::log("wrapper", logging::LogLevel::debug, "AdjustWindowRectEx()");
  return IUser32::get_instance()->AdjustWindowRectEx(lpRect, dwStyle, bMenu, dwExStyle);
}

DLLEXPORT WINBOOL WINAPI SetWindowContextHelpId (HWND arg0, DWORD arg1)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowContextHelpId()");
  return IUser32::get_instance()->SetWindowContextHelpId(arg0, arg1);
}

DLLEXPORT DWORD WINAPI GetWindowContextHelpId (HWND arg0)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowContextHelpId()");
  return IUser32::get_instance()->GetWindowContextHelpId(arg0);
}

DLLEXPORT WINBOOL WINAPI SetMenuContextHelpId (HMENU arg0, DWORD arg1)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuContextHelpId()");
  return IUser32::get_instance()->SetMenuContextHelpId(arg0, arg1);
}

DLLEXPORT DWORD WINAPI GetMenuContextHelpId (HMENU arg0)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuContextHelpId()");
  return IUser32::get_instance()->GetMenuContextHelpId(arg0);
}

DLLEXPORT int WINAPI MessageBoxA (HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxA()");
  return IUser32::get_instance()->MessageBoxA(hWnd, lpText, lpCaption, uType);
}

DLLEXPORT int WINAPI MessageBoxW (HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxW()");
  return IUser32::get_instance()->MessageBoxW(hWnd, lpText, lpCaption, uType);
}

DLLEXPORT int WINAPI MessageBoxExA (HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxExA()");
  return IUser32::get_instance()->MessageBoxExA(hWnd, lpText, lpCaption, uType, wLanguageId);
}

DLLEXPORT int WINAPI MessageBoxExW (HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType, WORD wLanguageId)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxExW()");
  return IUser32::get_instance()->MessageBoxExW(hWnd, lpText, lpCaption, uType, wLanguageId);
}

DLLEXPORT int WINAPI MessageBoxIndirectA (CONST MSGBOXPARAMSA * lpmbp)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxIndirectA()");
  return IUser32::get_instance()->MessageBoxIndirectA(lpmbp);
}

DLLEXPORT int WINAPI MessageBoxIndirectW (CONST MSGBOXPARAMSW * lpmbp)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxIndirectW()");
  return IUser32::get_instance()->MessageBoxIndirectW(lpmbp);
}

DLLEXPORT WINBOOL WINAPI MessageBeep (UINT uType)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBeep()");
  return IUser32::get_instance()->MessageBeep(uType);
}

DLLEXPORT int WINAPI ShowCursor (WINBOOL bShow)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowCursor()");
  return IUser32::get_instance()->ShowCursor(bShow);
}

DLLEXPORT WINBOOL WINAPI SetCursorPos (int X, int Y)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCursorPos()");
  return IUser32::get_instance()->SetCursorPos(X, Y);
}

DLLEXPORT HCURSOR WINAPI SetCursor (HCURSOR hCursor)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCursor()");
  return IUser32::get_instance()->SetCursor(hCursor);
}

DLLEXPORT WINBOOL WINAPI GetCursorPos (LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCursorPos()");
  return IUser32::get_instance()->GetCursorPos(lpPoint);
}

DLLEXPORT WINBOOL WINAPI ClipCursor (CONST RECT * lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "ClipCursor()");
  return IUser32::get_instance()->ClipCursor(lpRect);
}

DLLEXPORT WINBOOL WINAPI GetClipCursor (LPRECT lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipCursor()");
  return IUser32::get_instance()->GetClipCursor(lpRect);
}

DLLEXPORT HCURSOR WINAPI GetCursor (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCursor()");
  return IUser32::get_instance()->GetCursor();
}

DLLEXPORT WINBOOL WINAPI CreateCaret (HWND hWnd, HBITMAP hBitmap, int nWidth, int nHeight)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateCaret()");
  return IUser32::get_instance()->CreateCaret(hWnd, hBitmap, nWidth, nHeight);
}

DLLEXPORT UINT WINAPI GetCaretBlinkTime (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCaretBlinkTime()");
  return IUser32::get_instance()->GetCaretBlinkTime();
}

DLLEXPORT WINBOOL WINAPI SetCaretBlinkTime (UINT uMSeconds)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCaretBlinkTime()");
  return IUser32::get_instance()->SetCaretBlinkTime(uMSeconds);
}

DLLEXPORT WINBOOL WINAPI DestroyCaret (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyCaret()");
  return IUser32::get_instance()->DestroyCaret();
}

DLLEXPORT WINBOOL WINAPI HideCaret (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "HideCaret()");
  return IUser32::get_instance()->HideCaret(hWnd);
}

DLLEXPORT WINBOOL WINAPI ShowCaret (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowCaret()");
  return IUser32::get_instance()->ShowCaret(hWnd);
}

DLLEXPORT WINBOOL WINAPI SetCaretPos (int X, int Y)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCaretPos()");
  return IUser32::get_instance()->SetCaretPos(X, Y);
}

DLLEXPORT WINBOOL WINAPI GetCaretPos (LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCaretPos()");
  return IUser32::get_instance()->GetCaretPos(lpPoint);
}

DLLEXPORT WINBOOL WINAPI ClientToScreen (HWND hWnd, LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "ClientToScreen()");
  return IUser32::get_instance()->ClientToScreen(hWnd, lpPoint);
}

DLLEXPORT WINBOOL WINAPI ScreenToClient (HWND hWnd, LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScreenToClient()");
  return IUser32::get_instance()->ScreenToClient(hWnd, lpPoint);
}

DLLEXPORT int WINAPI MapWindowPoints (HWND hWndFrom, HWND hWndTo, LPPOINT lpPoints, UINT cPoints)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapWindowPoints()");
  return IUser32::get_instance()->MapWindowPoints(hWndFrom, hWndTo, lpPoints, cPoints);
}

DLLEXPORT HWND WINAPI WindowFromPoint (POINT Point)
{
  logging::log("wrapper", logging::LogLevel::debug, "WindowFromPoint()");
  return IUser32::get_instance()->WindowFromPoint(Point);
}

DLLEXPORT HWND WINAPI ChildWindowFromPoint (HWND hWndParent, POINT Point)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChildWindowFromPoint()");
  return IUser32::get_instance()->ChildWindowFromPoint(hWndParent, Point);
}

DLLEXPORT HWND WINAPI ChildWindowFromPointEx (HWND hwnd, POINT pt, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChildWindowFromPointEx()");
  return IUser32::get_instance()->ChildWindowFromPointEx(hwnd, pt, flags);
}

DLLEXPORT WINBOOL WINAPI SetPhysicalCursorPos (int X, int Y)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetPhysicalCursorPos()");
  return IUser32::get_instance()->SetPhysicalCursorPos(X, Y);
}

DLLEXPORT WINBOOL WINAPI GetPhysicalCursorPos (LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPhysicalCursorPos()");
  return IUser32::get_instance()->GetPhysicalCursorPos(lpPoint);
}

DLLEXPORT WINBOOL WINAPI LogicalToPhysicalPoint (HWND hWnd, LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "LogicalToPhysicalPoint()");
  return IUser32::get_instance()->LogicalToPhysicalPoint(hWnd, lpPoint);
}

DLLEXPORT WINBOOL WINAPI PhysicalToLogicalPoint (HWND hWnd, LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "PhysicalToLogicalPoint()");
  return IUser32::get_instance()->PhysicalToLogicalPoint(hWnd, lpPoint);
}

DLLEXPORT HWND WINAPI WindowFromPhysicalPoint (POINT Point)
{
  logging::log("wrapper", logging::LogLevel::debug, "WindowFromPhysicalPoint()");
  return IUser32::get_instance()->WindowFromPhysicalPoint(Point);
}

DLLEXPORT DWORD WINAPI GetSysColor (int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSysColor()");
  return IUser32::get_instance()->GetSysColor(nIndex);
}

DLLEXPORT HBRUSH WINAPI GetSysColorBrush (int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSysColorBrush()");
  return IUser32::get_instance()->GetSysColorBrush(nIndex);
}

DLLEXPORT WINBOOL WINAPI SetSysColors (int cElements, CONST INT * lpaElements, CONST COLORREF * lpaRgbValues)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetSysColors()");
  return IUser32::get_instance()->SetSysColors(cElements, lpaElements, lpaRgbValues);
}

DLLEXPORT WINBOOL WINAPI DrawFocusRect (HDC hDC, CONST RECT * lprc)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawFocusRect()");
  return IUser32::get_instance()->DrawFocusRect(hDC, lprc);
}

DLLEXPORT int WINAPI FillRect (HDC hDC, CONST RECT * lprc, HBRUSH hbr)
{
  logging::log("wrapper", logging::LogLevel::debug, "FillRect()");
  return IUser32::get_instance()->FillRect(hDC, lprc, hbr);
}

DLLEXPORT int WINAPI FrameRect (HDC hDC, CONST RECT * lprc, HBRUSH hbr)
{
  logging::log("wrapper", logging::LogLevel::debug, "FrameRect()");
  return IUser32::get_instance()->FrameRect(hDC, lprc, hbr);
}

DLLEXPORT WINBOOL WINAPI InvertRect (HDC hDC, CONST RECT * lprc)
{
  logging::log("wrapper", logging::LogLevel::debug, "InvertRect()");
  return IUser32::get_instance()->InvertRect(hDC, lprc);
}

DLLEXPORT WINBOOL WINAPI SetRect (LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetRect()");
  return IUser32::get_instance()->SetRect(lprc, xLeft, yTop, xRight, yBottom);
}

DLLEXPORT WINBOOL WINAPI SetRectEmpty (LPRECT lprc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetRectEmpty()");
  return IUser32::get_instance()->SetRectEmpty(lprc);
}

DLLEXPORT WINBOOL WINAPI CopyRect (LPRECT lprcDst, CONST RECT * lprcSrc)
{
  logging::log("wrapper", logging::LogLevel::debug, "CopyRect()");
  return IUser32::get_instance()->CopyRect(lprcDst, lprcSrc);
}

DLLEXPORT WINBOOL WINAPI InflateRect (LPRECT lprc, int dx, int dy)
{
  logging::log("wrapper", logging::LogLevel::debug, "InflateRect()");
  return IUser32::get_instance()->InflateRect(lprc, dx, dy);
}

DLLEXPORT WINBOOL WINAPI IntersectRect (LPRECT lprcDst, CONST RECT * lprcSrc1, CONST RECT * lprcSrc2)
{
  logging::log("wrapper", logging::LogLevel::debug, "IntersectRect()");
  return IUser32::get_instance()->IntersectRect(lprcDst, lprcSrc1, lprcSrc2);
}

DLLEXPORT WINBOOL WINAPI UnionRect (LPRECT lprcDst, CONST RECT * lprcSrc1, CONST RECT * lprcSrc2)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnionRect()");
  return IUser32::get_instance()->UnionRect(lprcDst, lprcSrc1, lprcSrc2);
}

DLLEXPORT WINBOOL WINAPI SubtractRect (LPRECT lprcDst, CONST RECT * lprcSrc1, CONST RECT * lprcSrc2)
{
  logging::log("wrapper", logging::LogLevel::debug, "SubtractRect()");
  return IUser32::get_instance()->SubtractRect(lprcDst, lprcSrc1, lprcSrc2);
}

DLLEXPORT WINBOOL WINAPI OffsetRect (LPRECT lprc, int dx, int dy)
{
  logging::log("wrapper", logging::LogLevel::debug, "OffsetRect()");
  return IUser32::get_instance()->OffsetRect(lprc, dx, dy);
}

DLLEXPORT WINBOOL WINAPI IsRectEmpty (CONST RECT * lprc)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsRectEmpty()");
  return IUser32::get_instance()->IsRectEmpty(lprc);
}

DLLEXPORT WINBOOL WINAPI EqualRect (CONST RECT * lprc1, CONST RECT * lprc2)
{
  logging::log("wrapper", logging::LogLevel::debug, "EqualRect()");
  return IUser32::get_instance()->EqualRect(lprc1, lprc2);
}

DLLEXPORT WINBOOL WINAPI PtInRect (CONST RECT * lprc, POINT pt)
{
  logging::log("wrapper", logging::LogLevel::debug, "PtInRect()");
  return IUser32::get_instance()->PtInRect(lprc, pt);
}

DLLEXPORT WORD WINAPI GetWindowWord (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowWord()");
  return IUser32::get_instance()->GetWindowWord(hWnd, nIndex);
}

DLLEXPORT WORD WINAPI SetWindowWord (HWND hWnd, int nIndex, WORD wNewWord)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowWord()");
  return IUser32::get_instance()->SetWindowWord(hWnd, nIndex, wNewWord);
}

DLLEXPORT LONG WINAPI GetWindowLongA (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowLongA()");
  return IUser32::get_instance()->GetWindowLongA(hWnd, nIndex);
}

DLLEXPORT LONG WINAPI GetWindowLongW (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowLongW()");
  return IUser32::get_instance()->GetWindowLongW(hWnd, nIndex);
}

DLLEXPORT LONG WINAPI SetWindowLongA (HWND hWnd, int nIndex, LONG dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowLongA()");
  return IUser32::get_instance()->SetWindowLongA(hWnd, nIndex, dwNewLong);
}

DLLEXPORT LONG WINAPI SetWindowLongW (HWND hWnd, int nIndex, LONG dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowLongW()");
  return IUser32::get_instance()->SetWindowLongW(hWnd, nIndex, dwNewLong);
}

DLLEXPORT LONG_PTR WINAPI GetWindowLongPtrA (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowLongPtrA()");
  return IUser32::get_instance()->GetWindowLongPtrA(hWnd, nIndex);
}

DLLEXPORT LONG_PTR WINAPI GetWindowLongPtrW (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowLongPtrW()");
  return IUser32::get_instance()->GetWindowLongPtrW(hWnd, nIndex);
}

DLLEXPORT LONG_PTR WINAPI SetWindowLongPtrA (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowLongPtrA()");
  return IUser32::get_instance()->SetWindowLongPtrA(hWnd, nIndex, dwNewLong);
}

DLLEXPORT LONG_PTR WINAPI SetWindowLongPtrW (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowLongPtrW()");
  return IUser32::get_instance()->SetWindowLongPtrW(hWnd, nIndex, dwNewLong);
}

DLLEXPORT WORD WINAPI GetClassWord (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassWord()");
  return IUser32::get_instance()->GetClassWord(hWnd, nIndex);
}

DLLEXPORT WORD WINAPI SetClassWord (HWND hWnd, int nIndex, WORD wNewWord)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClassWord()");
  return IUser32::get_instance()->SetClassWord(hWnd, nIndex, wNewWord);
}

DLLEXPORT DWORD WINAPI GetClassLongA (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassLongA()");
  return IUser32::get_instance()->GetClassLongA(hWnd, nIndex);
}

DLLEXPORT DWORD WINAPI GetClassLongW (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassLongW()");
  return IUser32::get_instance()->GetClassLongW(hWnd, nIndex);
}

DLLEXPORT DWORD WINAPI SetClassLongA (HWND hWnd, int nIndex, LONG dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClassLongA()");
  return IUser32::get_instance()->SetClassLongA(hWnd, nIndex, dwNewLong);
}

DLLEXPORT DWORD WINAPI SetClassLongW (HWND hWnd, int nIndex, LONG dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClassLongW()");
  return IUser32::get_instance()->SetClassLongW(hWnd, nIndex, dwNewLong);
}

DLLEXPORT ULONG_PTR WINAPI GetClassLongPtrA (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassLongPtrA()");
  return IUser32::get_instance()->GetClassLongPtrA(hWnd, nIndex);
}

DLLEXPORT ULONG_PTR WINAPI GetClassLongPtrW (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassLongPtrW()");
  return IUser32::get_instance()->GetClassLongPtrW(hWnd, nIndex);
}

DLLEXPORT ULONG_PTR WINAPI SetClassLongPtrA (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClassLongPtrA()");
  return IUser32::get_instance()->SetClassLongPtrA(hWnd, nIndex, dwNewLong);
}

DLLEXPORT ULONG_PTR WINAPI SetClassLongPtrW (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClassLongPtrW()");
  return IUser32::get_instance()->SetClassLongPtrW(hWnd, nIndex, dwNewLong);
}

DLLEXPORT WINBOOL WINAPI GetProcessDefaultLayout (DWORD * pdwDefaultLayout)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetProcessDefaultLayout()");
  return IUser32::get_instance()->GetProcessDefaultLayout(pdwDefaultLayout);
}

DLLEXPORT WINBOOL WINAPI SetProcessDefaultLayout (DWORD dwDefaultLayout)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProcessDefaultLayout()");
  return IUser32::get_instance()->SetProcessDefaultLayout(dwDefaultLayout);
}

DLLEXPORT HWND WINAPI GetDesktopWindow (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDesktopWindow()");
  return IUser32::get_instance()->GetDesktopWindow();
}

DLLEXPORT HWND WINAPI GetParent (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetParent()");
  return IUser32::get_instance()->GetParent(hWnd);
}

DLLEXPORT HWND WINAPI SetParent (HWND hWndChild, HWND hWndNewParent)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetParent()");
  return IUser32::get_instance()->SetParent(hWndChild, hWndNewParent);
}

DLLEXPORT WINBOOL WINAPI EnumChildWindows (HWND hWndParent, WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumChildWindows()");
  return IUser32::get_instance()->EnumChildWindows(hWndParent, lpEnumFunc, lParam);
}

DLLEXPORT HWND WINAPI FindWindowA (LPCSTR lpClassName, LPCSTR lpWindowName)
{
  logging::log("wrapper", logging::LogLevel::debug, "FindWindowA()");
  return IUser32::get_instance()->FindWindowA(lpClassName, lpWindowName);
}

DLLEXPORT HWND WINAPI FindWindowW (LPCWSTR lpClassName, LPCWSTR lpWindowName)
{
  logging::log("wrapper", logging::LogLevel::debug, "FindWindowW()");
  return IUser32::get_instance()->FindWindowW(lpClassName, lpWindowName);
}

DLLEXPORT HWND WINAPI FindWindowExA (HWND hWndParent, HWND hWndChildAfter, LPCSTR lpszClass, LPCSTR lpszWindow)
{
  logging::log("wrapper", logging::LogLevel::debug, "FindWindowExA()");
  return IUser32::get_instance()->FindWindowExA(hWndParent, hWndChildAfter, lpszClass, lpszWindow);
}

DLLEXPORT HWND WINAPI FindWindowExW (HWND hWndParent, HWND hWndChildAfter, LPCWSTR lpszClass, LPCWSTR lpszWindow)
{
  logging::log("wrapper", logging::LogLevel::debug, "FindWindowExW()");
  return IUser32::get_instance()->FindWindowExW(hWndParent, hWndChildAfter, lpszClass, lpszWindow);
}

DLLEXPORT HWND WINAPI GetShellWindow (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetShellWindow()");
  return IUser32::get_instance()->GetShellWindow();
}

DLLEXPORT WINBOOL WINAPI RegisterShellHookWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterShellHookWindow()");
  return IUser32::get_instance()->RegisterShellHookWindow(hwnd);
}

DLLEXPORT WINBOOL WINAPI DeregisterShellHookWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DeregisterShellHookWindow()");
  return IUser32::get_instance()->DeregisterShellHookWindow(hwnd);
}

DLLEXPORT WINBOOL WINAPI EnumWindows (WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumWindows()");
  return IUser32::get_instance()->EnumWindows(lpEnumFunc, lParam);
}

DLLEXPORT WINBOOL WINAPI EnumThreadWindows (DWORD dwThreadId, WNDENUMPROC lpfn, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumThreadWindows()");
  return IUser32::get_instance()->EnumThreadWindows(dwThreadId, lpfn, lParam);
}

DLLEXPORT int WINAPI GetClassNameA (HWND hWnd, LPSTR lpClassName, int nMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassNameA()");
  return IUser32::get_instance()->GetClassNameA(hWnd, lpClassName, nMaxCount);
}

DLLEXPORT int WINAPI GetClassNameW (HWND hWnd, LPWSTR lpClassName, int nMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassNameW()");
  return IUser32::get_instance()->GetClassNameW(hWnd, lpClassName, nMaxCount);
}

DLLEXPORT HWND WINAPI GetTopWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTopWindow()");
  return IUser32::get_instance()->GetTopWindow(hWnd);
}

DLLEXPORT DWORD WINAPI GetWindowThreadProcessId (HWND hWnd, LPDWORD lpdwProcessId)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowThreadProcessId()");
  return IUser32::get_instance()->GetWindowThreadProcessId(hWnd, lpdwProcessId);
}

DLLEXPORT WINBOOL WINAPI IsGUIThread (WINBOOL bConvert)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsGUIThread()");
  return IUser32::get_instance()->IsGUIThread(bConvert);
}

DLLEXPORT HWND WINAPI GetLastActivePopup (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetLastActivePopup()");
  return IUser32::get_instance()->GetLastActivePopup(hWnd);
}

DLLEXPORT HWND WINAPI GetWindow (HWND hWnd, UINT uCmd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindow()");
  return IUser32::get_instance()->GetWindow(hWnd, uCmd);
}

#ifdef STRICT

DLLEXPORT HHOOK WINAPI SetWindowsHookA (int nFilterType, HOOKPROC pfnFilterProc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookA()");
  return IUser32::get_instance()->SetWindowsHookA(nFilterType, pfnFilterProc);
}

DLLEXPORT HHOOK WINAPI SetWindowsHookW (int nFilterType, HOOKPROC pfnFilterProc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookW()");
  return IUser32::get_instance()->SetWindowsHookW(nFilterType, pfnFilterProc);
}

#else

DLLEXPORT HOOKPROC WINAPI SetWindowsHookA (int nFilterType, HOOKPROC pfnFilterProc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookA()");
  return IUser32::get_instance()->SetWindowsHookA(nFilterType, pfnFilterProc);
}

DLLEXPORT HOOKPROC WINAPI SetWindowsHookW (int nFilterType, HOOKPROC pfnFilterProc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookW()");
  return IUser32::get_instance()->SetWindowsHookW(nFilterType, pfnFilterProc);
}

#endif

DLLEXPORT WINBOOL WINAPI UnhookWindowsHook (int nCode, HOOKPROC pfnFilterProc)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnhookWindowsHook()");
  return IUser32::get_instance()->UnhookWindowsHook(nCode, pfnFilterProc);
}

DLLEXPORT HHOOK WINAPI SetWindowsHookExA (int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookExA()");
  return IUser32::get_instance()->SetWindowsHookExA(idHook, lpfn, hmod, dwThreadId);
}

DLLEXPORT HHOOK WINAPI SetWindowsHookExW (int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookExW()");
  return IUser32::get_instance()->SetWindowsHookExW(idHook, lpfn, hmod, dwThreadId);
}

DLLEXPORT WINBOOL WINAPI UnhookWindowsHookEx (HHOOK hhk)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnhookWindowsHookEx()");
  return IUser32::get_instance()->UnhookWindowsHookEx(hhk);
}

DLLEXPORT LRESULT WINAPI CallNextHookEx (HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallNextHookEx()");
  return IUser32::get_instance()->CallNextHookEx(hhk, nCode, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI CheckMenuRadioItem (HMENU hmenu, UINT first, UINT last, UINT check, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CheckMenuRadioItem()");
  return IUser32::get_instance()->CheckMenuRadioItem(hmenu, first, last, check, flags);
}

DLLEXPORT HBITMAP WINAPI LoadBitmapA (HINSTANCE hInstance, LPCSTR lpBitmapName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadBitmapA()");
  return IUser32::get_instance()->LoadBitmapA(hInstance, lpBitmapName);
}

DLLEXPORT HBITMAP WINAPI LoadBitmapW (HINSTANCE hInstance, LPCWSTR lpBitmapName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadBitmapW()");
  return IUser32::get_instance()->LoadBitmapW(hInstance, lpBitmapName);
}

DLLEXPORT HCURSOR WINAPI LoadCursorA (HINSTANCE hInstance, LPCSTR lpCursorName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadCursorA()");
  return IUser32::get_instance()->LoadCursorA(hInstance, lpCursorName);
}

DLLEXPORT HCURSOR WINAPI LoadCursorW (HINSTANCE hInstance, LPCWSTR lpCursorName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadCursorW()");
  return IUser32::get_instance()->LoadCursorW(hInstance, lpCursorName);
}

DLLEXPORT HCURSOR WINAPI LoadCursorFromFileA (LPCSTR lpFileName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadCursorFromFileA()");
  return IUser32::get_instance()->LoadCursorFromFileA(lpFileName);
}

DLLEXPORT HCURSOR WINAPI LoadCursorFromFileW (LPCWSTR lpFileName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadCursorFromFileW()");
  return IUser32::get_instance()->LoadCursorFromFileW(lpFileName);
}

DLLEXPORT HCURSOR WINAPI CreateCursor (HINSTANCE hInst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID * pvANDPlane, CONST VOID * pvXORPlane)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateCursor()");
  return IUser32::get_instance()->CreateCursor(hInst, xHotSpot, yHotSpot, nWidth, nHeight, pvANDPlane, pvXORPlane);
}

DLLEXPORT WINBOOL WINAPI DestroyCursor (HCURSOR hCursor)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyCursor()");
  return IUser32::get_instance()->DestroyCursor(hCursor);
}

DLLEXPORT WINBOOL WINAPI SetSystemCursor (HCURSOR hcur, DWORD id)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetSystemCursor()");
  return IUser32::get_instance()->SetSystemCursor(hcur, id);
}

DLLEXPORT HICON WINAPI LoadIconA (HINSTANCE hInstance, LPCSTR lpIconName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadIconA()");
  return IUser32::get_instance()->LoadIconA(hInstance, lpIconName);
}

DLLEXPORT HICON WINAPI LoadIconW (HINSTANCE hInstance, LPCWSTR lpIconName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadIconW()");
  return IUser32::get_instance()->LoadIconW(hInstance, lpIconName);
}

DLLEXPORT UINT WINAPI PrivateExtractIconsA (LPCSTR szFileName, int nIconIndex, int cxIcon, int cyIcon, HICON * phicon, UINT * piconid, UINT nIcons, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "PrivateExtractIconsA()");
  return IUser32::get_instance()->PrivateExtractIconsA(szFileName, nIconIndex, cxIcon, cyIcon, phicon, piconid, nIcons, flags);
}

DLLEXPORT UINT WINAPI PrivateExtractIconsW (LPCWSTR szFileName, int nIconIndex, int cxIcon, int cyIcon, HICON * phicon, UINT * piconid, UINT nIcons, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "PrivateExtractIconsW()");
  return IUser32::get_instance()->PrivateExtractIconsW(szFileName, nIconIndex, cxIcon, cyIcon, phicon, piconid, nIcons, flags);
}

DLLEXPORT HICON WINAPI CreateIcon (HINSTANCE hInstance, int nWidth, int nHeight, BYTE cPlanes, BYTE cBitsPixel, CONST BYTE * lpbANDbits, CONST BYTE * lpbXORbits)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateIcon()");
  return IUser32::get_instance()->CreateIcon(hInstance, nWidth, nHeight, cPlanes, cBitsPixel, lpbANDbits, lpbXORbits);
}

DLLEXPORT WINBOOL WINAPI DestroyIcon (HICON hIcon)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyIcon()");
  return IUser32::get_instance()->DestroyIcon(hIcon);
}

DLLEXPORT int WINAPI LookupIconIdFromDirectory (PBYTE presbits, WINBOOL fIcon)
{
  logging::log("wrapper", logging::LogLevel::debug, "LookupIconIdFromDirectory()");
  return IUser32::get_instance()->LookupIconIdFromDirectory(presbits, fIcon);
}

DLLEXPORT int WINAPI LookupIconIdFromDirectoryEx (PBYTE presbits, WINBOOL fIcon, int cxDesired, int cyDesired, UINT Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "LookupIconIdFromDirectoryEx()");
  return IUser32::get_instance()->LookupIconIdFromDirectoryEx(presbits, fIcon, cxDesired, cyDesired, Flags);
}

DLLEXPORT HICON WINAPI CreateIconFromResource (PBYTE presbits, DWORD dwResSize, WINBOOL fIcon, DWORD dwVer)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateIconFromResource()");
  return IUser32::get_instance()->CreateIconFromResource(presbits, dwResSize, fIcon, dwVer);
}

DLLEXPORT HICON WINAPI CreateIconFromResourceEx (PBYTE presbits, DWORD dwResSize, WINBOOL fIcon, DWORD dwVer, int cxDesired, int cyDesired, UINT Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateIconFromResourceEx()");
  return IUser32::get_instance()->CreateIconFromResourceEx(presbits, dwResSize, fIcon, dwVer, cxDesired, cyDesired, Flags);
}

DLLEXPORT HANDLE WINAPI LoadImageA (HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadImageA()");
  return IUser32::get_instance()->LoadImageA(hInst, name, type, cx, cy, fuLoad);
}

DLLEXPORT HANDLE WINAPI LoadImageW (HINSTANCE hInst, LPCWSTR name, UINT type, int cx, int cy, UINT fuLoad)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadImageW()");
  return IUser32::get_instance()->LoadImageW(hInst, name, type, cx, cy, fuLoad);
}

DLLEXPORT HANDLE WINAPI CopyImage (HANDLE h, UINT type, int cx, int cy, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CopyImage()");
  return IUser32::get_instance()->CopyImage(h, type, cx, cy, flags);
}

DLLEXPORT WINBOOL WINAPI DrawIconEx (HDC hdc, int xLeft, int yTop, HICON hIcon, int cxWidth, int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawIconEx()");
  return IUser32::get_instance()->DrawIconEx(hdc, xLeft, yTop, hIcon, cxWidth, cyWidth, istepIfAniCur, hbrFlickerFreeDraw, diFlags);
}

DLLEXPORT HICON WINAPI CreateIconIndirect (PICONINFO piconinfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateIconIndirect()");
  return IUser32::get_instance()->CreateIconIndirect(piconinfo);
}

DLLEXPORT HICON WINAPI CopyIcon (HICON hIcon)
{
  logging::log("wrapper", logging::LogLevel::debug, "CopyIcon()");
  return IUser32::get_instance()->CopyIcon(hIcon);
}

DLLEXPORT WINBOOL WINAPI GetIconInfo (HICON hIcon, PICONINFO piconinfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetIconInfo()");
  return IUser32::get_instance()->GetIconInfo(hIcon, piconinfo);
}

DLLEXPORT WINBOOL WINAPI GetIconInfoExA (HICON hicon, PICONINFOEXA piconinfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetIconInfoExA()");
  return IUser32::get_instance()->GetIconInfoExA(hicon, piconinfo);
}

DLLEXPORT WINBOOL WINAPI GetIconInfoExW (HICON hicon, PICONINFOEXW piconinfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetIconInfoExW()");
  return IUser32::get_instance()->GetIconInfoExW(hicon, piconinfo);
}

DLLEXPORT int WINAPI LoadStringA (HINSTANCE hInstance, UINT uID, LPSTR lpBuffer, int cchBufferMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadStringA()");
  return IUser32::get_instance()->LoadStringA(hInstance, uID, lpBuffer, cchBufferMax);
}

DLLEXPORT int WINAPI LoadStringW (HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int cchBufferMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadStringW()");
  return IUser32::get_instance()->LoadStringW(hInstance, uID, lpBuffer, cchBufferMax);
}

DLLEXPORT WINBOOL WINAPI IsDialogMessageA (HWND hDlg, LPMSG lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsDialogMessageA()");
  return IUser32::get_instance()->IsDialogMessageA(hDlg, lpMsg);
}

DLLEXPORT WINBOOL WINAPI IsDialogMessageW (HWND hDlg, LPMSG lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsDialogMessageW()");
  return IUser32::get_instance()->IsDialogMessageW(hDlg, lpMsg);
}

DLLEXPORT WINBOOL WINAPI MapDialogRect (HWND hDlg, LPRECT lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapDialogRect()");
  return IUser32::get_instance()->MapDialogRect(hDlg, lpRect);
}

DLLEXPORT int WINAPI DlgDirListA (HWND hDlg, LPSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT uFileType)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirListA()");
  return IUser32::get_instance()->DlgDirListA(hDlg, lpPathSpec, nIDListBox, nIDStaticPath, uFileType);
}

DLLEXPORT int WINAPI DlgDirListW (HWND hDlg, LPWSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT uFileType)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirListW()");
  return IUser32::get_instance()->DlgDirListW(hDlg, lpPathSpec, nIDListBox, nIDStaticPath, uFileType);
}

DLLEXPORT WINBOOL WINAPI DlgDirSelectExA (HWND hwndDlg, LPSTR lpString, int chCount, int idListBox)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirSelectExA()");
  return IUser32::get_instance()->DlgDirSelectExA(hwndDlg, lpString, chCount, idListBox);
}

DLLEXPORT WINBOOL WINAPI DlgDirSelectExW (HWND hwndDlg, LPWSTR lpString, int chCount, int idListBox)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirSelectExW()");
  return IUser32::get_instance()->DlgDirSelectExW(hwndDlg, lpString, chCount, idListBox);
}

DLLEXPORT int WINAPI DlgDirListComboBoxA (HWND hDlg, LPSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT uFiletype)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirListComboBoxA()");
  return IUser32::get_instance()->DlgDirListComboBoxA(hDlg, lpPathSpec, nIDComboBox, nIDStaticPath, uFiletype);
}

DLLEXPORT int WINAPI DlgDirListComboBoxW (HWND hDlg, LPWSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT uFiletype)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirListComboBoxW()");
  return IUser32::get_instance()->DlgDirListComboBoxW(hDlg, lpPathSpec, nIDComboBox, nIDStaticPath, uFiletype);
}

DLLEXPORT WINBOOL WINAPI DlgDirSelectComboBoxExA (HWND hwndDlg, LPSTR lpString, int cchOut, int idComboBox)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirSelectComboBoxExA()");
  return IUser32::get_instance()->DlgDirSelectComboBoxExA(hwndDlg, lpString, cchOut, idComboBox);
}

DLLEXPORT WINBOOL WINAPI DlgDirSelectComboBoxExW (HWND hwndDlg, LPWSTR lpString, int cchOut, int idComboBox)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirSelectComboBoxExW()");
  return IUser32::get_instance()->DlgDirSelectComboBoxExW(hwndDlg, lpString, cchOut, idComboBox);
}

DLLEXPORT int WINAPI SetScrollInfo (HWND hwnd, int nBar, LPCSCROLLINFO lpsi, WINBOOL redraw)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetScrollInfo()");
  return IUser32::get_instance()->SetScrollInfo(hwnd, nBar, lpsi, redraw);
}

DLLEXPORT WINBOOL WINAPI GetScrollInfo (HWND hwnd, int nBar, LPSCROLLINFO lpsi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetScrollInfo()");
  return IUser32::get_instance()->GetScrollInfo(hwnd, nBar, lpsi);
}

DLLEXPORT LRESULT WINAPI DefFrameProcA (HWND hWnd, HWND hWndMDIClient, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefFrameProcA()");
  return IUser32::get_instance()->DefFrameProcA(hWnd, hWndMDIClient, uMsg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI DefFrameProcW (HWND hWnd, HWND hWndMDIClient, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefFrameProcW()");
  return IUser32::get_instance()->DefFrameProcW(hWnd, hWndMDIClient, uMsg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI DefMDIChildProcA (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefMDIChildProcA()");
  return IUser32::get_instance()->DefMDIChildProcA(hWnd, uMsg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI DefMDIChildProcW (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefMDIChildProcW()");
  return IUser32::get_instance()->DefMDIChildProcW(hWnd, uMsg, wParam, lParam);
}

DLLEXPORT WINBOOL WINAPI TranslateMDISysAccel (HWND hWndClient, LPMSG lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "TranslateMDISysAccel()");
  return IUser32::get_instance()->TranslateMDISysAccel(hWndClient, lpMsg);
}

DLLEXPORT UINT WINAPI ArrangeIconicWindows (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "ArrangeIconicWindows()");
  return IUser32::get_instance()->ArrangeIconicWindows(hWnd);
}

DLLEXPORT HWND WINAPI CreateMDIWindowA (LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateMDIWindowA()");
  return IUser32::get_instance()->CreateMDIWindowA(lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hInstance, lParam);
}

DLLEXPORT HWND WINAPI CreateMDIWindowW (LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateMDIWindowW()");
  return IUser32::get_instance()->CreateMDIWindowW(lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hInstance, lParam);
}

DLLEXPORT WORD WINAPI TileWindows (HWND hwndParent, UINT wHow, CONST RECT * lpRect, UINT cKids, const HWND * lpKids)
{
  logging::log("wrapper", logging::LogLevel::debug, "TileWindows()");
  return IUser32::get_instance()->TileWindows(hwndParent, wHow, lpRect, cKids, lpKids);
}

DLLEXPORT WORD WINAPI CascadeWindows (HWND hwndParent, UINT wHow, CONST RECT * lpRect, UINT cKids, const HWND * lpKids)
{
  logging::log("wrapper", logging::LogLevel::debug, "CascadeWindows()");
  return IUser32::get_instance()->CascadeWindows(hwndParent, wHow, lpRect, cKids, lpKids);
}

DLLEXPORT WINBOOL WINAPI WinHelpA (HWND hWndMain, LPCSTR lpszHelp, UINT uCommand, ULONG_PTR dwData)
{
  logging::log("wrapper", logging::LogLevel::debug, "WinHelpA()");
  return IUser32::get_instance()->WinHelpA(hWndMain, lpszHelp, uCommand, dwData);
}

DLLEXPORT WINBOOL WINAPI WinHelpW (HWND hWndMain, LPCWSTR lpszHelp, UINT uCommand, ULONG_PTR dwData)
{
  logging::log("wrapper", logging::LogLevel::debug, "WinHelpW()");
  return IUser32::get_instance()->WinHelpW(hWndMain, lpszHelp, uCommand, dwData);
}

DLLEXPORT DWORD WINAPI GetGuiResources (HANDLE hProcess, DWORD uiFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetGuiResources()");
  return IUser32::get_instance()->GetGuiResources(hProcess, uiFlags);
}

DLLEXPORT LONG WINAPI ChangeDisplaySettingsA (LPDEVMODEA lpDevMode, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeDisplaySettingsA()");
  return IUser32::get_instance()->ChangeDisplaySettingsA(lpDevMode, dwFlags);
}

DLLEXPORT LONG WINAPI ChangeDisplaySettingsW (LPDEVMODEW lpDevMode, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeDisplaySettingsW()");
  return IUser32::get_instance()->ChangeDisplaySettingsW(lpDevMode, dwFlags);
}

DLLEXPORT LONG WINAPI ChangeDisplaySettingsExA (LPCSTR lpszDeviceName, LPDEVMODEA lpDevMode, HWND hwnd, DWORD dwflags, LPVOID lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeDisplaySettingsExA()");
  return IUser32::get_instance()->ChangeDisplaySettingsExA(lpszDeviceName, lpDevMode, hwnd, dwflags, lParam);
}

DLLEXPORT LONG WINAPI ChangeDisplaySettingsExW (LPCWSTR lpszDeviceName, LPDEVMODEW lpDevMode, HWND hwnd, DWORD dwflags, LPVOID lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeDisplaySettingsExW()");
  return IUser32::get_instance()->ChangeDisplaySettingsExW(lpszDeviceName, lpDevMode, hwnd, dwflags, lParam);
}

DLLEXPORT WINBOOL WINAPI EnumDisplaySettingsA (LPCSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEA lpDevMode)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplaySettingsA()");
  return IUser32::get_instance()->EnumDisplaySettingsA(lpszDeviceName, iModeNum, lpDevMode);
}

DLLEXPORT WINBOOL WINAPI EnumDisplaySettingsW (LPCWSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEW lpDevMode)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplaySettingsW()");
  return IUser32::get_instance()->EnumDisplaySettingsW(lpszDeviceName, iModeNum, lpDevMode);
}

DLLEXPORT WINBOOL WINAPI EnumDisplaySettingsExA (LPCSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEA lpDevMode, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplaySettingsExA()");
  return IUser32::get_instance()->EnumDisplaySettingsExA(lpszDeviceName, iModeNum, lpDevMode, dwFlags);
}

DLLEXPORT WINBOOL WINAPI EnumDisplaySettingsExW (LPCWSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEW lpDevMode, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplaySettingsExW()");
  return IUser32::get_instance()->EnumDisplaySettingsExW(lpszDeviceName, iModeNum, lpDevMode, dwFlags);
}

DLLEXPORT WINBOOL WINAPI EnumDisplayDevicesA (LPCSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEA lpDisplayDevice, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplayDevicesA()");
  return IUser32::get_instance()->EnumDisplayDevicesA(lpDevice, iDevNum, lpDisplayDevice, dwFlags);
}

DLLEXPORT WINBOOL WINAPI EnumDisplayDevicesW (LPCWSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEW lpDisplayDevice, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplayDevicesW()");
  return IUser32::get_instance()->EnumDisplayDevicesW(lpDevice, iDevNum, lpDisplayDevice, dwFlags);
}

DLLEXPORT LONG WINAPI GetDisplayConfigBufferSizes (UINT32 flags, UINT32 * numPathArrayElements, UINT32 * numModeInfoArrayElements)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDisplayConfigBufferSizes()");
  return IUser32::get_instance()->GetDisplayConfigBufferSizes(flags, numPathArrayElements, numModeInfoArrayElements);
}

DLLEXPORT LONG WINAPI SetDisplayConfig (UINT32 numPathArrayElements, DISPLAYCONFIG_PATH_INFO * pathArray, UINT32 numModeInfoArrayElements, DISPLAYCONFIG_MODE_INFO * modeInfoArray, UINT32 flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDisplayConfig()");
  return IUser32::get_instance()->SetDisplayConfig(numPathArrayElements, pathArray, numModeInfoArrayElements, modeInfoArray, flags);
}

DLLEXPORT LONG WINAPI QueryDisplayConfig (UINT32 flags, UINT32 * numPathArrayElements, DISPLAYCONFIG_PATH_INFO * pathArray, UINT32 * numModeInfoArrayElements, DISPLAYCONFIG_MODE_INFO * modeInfoArray, DISPLAYCONFIG_TOPOLOGY_ID * currentTopologyId)
{
  logging::log("wrapper", logging::LogLevel::debug, "QueryDisplayConfig()");
  return IUser32::get_instance()->QueryDisplayConfig(flags, numPathArrayElements, pathArray, numModeInfoArrayElements, modeInfoArray, currentTopologyId);
}

DLLEXPORT LONG WINAPI DisplayConfigGetDeviceInfo (DISPLAYCONFIG_DEVICE_INFO_HEADER * requestPacket)
{
  logging::log("wrapper", logging::LogLevel::debug, "DisplayConfigGetDeviceInfo()");
  return IUser32::get_instance()->DisplayConfigGetDeviceInfo(requestPacket);
}

DLLEXPORT LONG WINAPI DisplayConfigSetDeviceInfo (DISPLAYCONFIG_DEVICE_INFO_HEADER * setPacket)
{
  logging::log("wrapper", logging::LogLevel::debug, "DisplayConfigSetDeviceInfo()");
  return IUser32::get_instance()->DisplayConfigSetDeviceInfo(setPacket);
}

DLLEXPORT WINBOOL WINAPI SystemParametersInfoA (UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
  logging::log("wrapper", logging::LogLevel::debug, "SystemParametersInfoA()");
  return IUser32::get_instance()->SystemParametersInfoA(uiAction, uiParam, pvParam, fWinIni);
}

DLLEXPORT WINBOOL WINAPI SystemParametersInfoW (UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
  logging::log("wrapper", logging::LogLevel::debug, "SystemParametersInfoW()");
  return IUser32::get_instance()->SystemParametersInfoW(uiAction, uiParam, pvParam, fWinIni);
}

DLLEXPORT VOID WINAPI SetDebugErrorLevel (DWORD dwLevel)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDebugErrorLevel()");
  IUser32::get_instance()->SetDebugErrorLevel(dwLevel);
}

DLLEXPORT VOID WINAPI SetLastErrorEx (DWORD dwErrCode, DWORD dwType)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetLastErrorEx()");
  IUser32::get_instance()->SetLastErrorEx(dwErrCode, dwType);
}

DLLEXPORT int WINAPI InternalGetWindowText (HWND hWnd, LPWSTR pString, int cchMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "InternalGetWindowText()");
  return IUser32::get_instance()->InternalGetWindowText(hWnd, pString, cchMaxCount);
}

DLLEXPORT WINBOOL WINAPI CancelShutdown (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "CancelShutdown()");
  return IUser32::get_instance()->CancelShutdown();
}

DLLEXPORT HMONITOR WINAPI MonitorFromPoint (POINT pt, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "MonitorFromPoint()");
  return IUser32::get_instance()->MonitorFromPoint(pt, dwFlags);
}

DLLEXPORT HMONITOR WINAPI MonitorFromRect (LPCRECT lprc, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "MonitorFromRect()");
  return IUser32::get_instance()->MonitorFromRect(lprc, dwFlags);
}

DLLEXPORT HMONITOR WINAPI MonitorFromWindow (HWND hwnd, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "MonitorFromWindow()");
  return IUser32::get_instance()->MonitorFromWindow(hwnd, dwFlags);
}

DLLEXPORT WINBOOL WINAPI EndTask (HWND hWnd, WINBOOL fShutDown, WINBOOL fForce)
{
  logging::log("wrapper", logging::LogLevel::debug, "EndTask()");
  return IUser32::get_instance()->EndTask(hWnd, fShutDown, fForce);
}

DLLEXPORT WINBOOL WINAPI SoundSentry (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "SoundSentry()");
  return IUser32::get_instance()->SoundSentry();
}

DLLEXPORT WINBOOL WINAPI GetMonitorInfoA (HMONITOR hMonitor, LPMONITORINFO lpmi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMonitorInfoA()");
  return IUser32::get_instance()->GetMonitorInfoA(hMonitor, lpmi);
}

DLLEXPORT WINBOOL WINAPI GetMonitorInfoW (HMONITOR hMonitor, LPMONITORINFO lpmi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMonitorInfoW()");
  return IUser32::get_instance()->GetMonitorInfoW(hMonitor, lpmi);
}

DLLEXPORT WINBOOL WINAPI EnumDisplayMonitors (HDC hdc, LPCRECT lprcClip, MONITORENUMPROC lpfnEnum, LPARAM dwData)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplayMonitors()");
  return IUser32::get_instance()->EnumDisplayMonitors(hdc, lprcClip, lpfnEnum, dwData);
}

DLLEXPORT VOID WINAPI NotifyWinEvent (DWORD event, HWND hwnd, LONG idObject, LONG idChild)
{
  logging::log("wrapper", logging::LogLevel::debug, "NotifyWinEvent()");
  IUser32::get_instance()->NotifyWinEvent(event, hwnd, idObject, idChild);
}

DLLEXPORT HWINEVENTHOOK WINAPI SetWinEventHook (DWORD eventMin, DWORD eventMax, HMODULE hmodWinEventProc, WINEVENTPROC pfnWinEventProc, DWORD idProcess, DWORD idThread, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWinEventHook()");
  return IUser32::get_instance()->SetWinEventHook(eventMin, eventMax, hmodWinEventProc, pfnWinEventProc, idProcess, idThread, dwFlags);
}

DLLEXPORT WINBOOL WINAPI IsWinEventHookInstalled (DWORD event)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWinEventHookInstalled()");
  return IUser32::get_instance()->IsWinEventHookInstalled(event);
}

DLLEXPORT WINBOOL WINAPI UnhookWinEvent (HWINEVENTHOOK hWinEventHook)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnhookWinEvent()");
  return IUser32::get_instance()->UnhookWinEvent(hWinEventHook);
}

DLLEXPORT WINBOOL WINAPI GetGUIThreadInfo (DWORD idThread, PGUITHREADINFO pgui)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetGUIThreadInfo()");
  return IUser32::get_instance()->GetGUIThreadInfo(idThread, pgui);
}

DLLEXPORT WINBOOL WINAPI BlockInput (WINBOOL fBlockIt)
{
  logging::log("wrapper", logging::LogLevel::debug, "BlockInput()");
  return IUser32::get_instance()->BlockInput(fBlockIt);
}

DLLEXPORT UINT WINAPI GetWindowModuleFileNameA (HWND hwnd, LPSTR pszFileName, UINT cchFileNameMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowModuleFileNameA()");
  return IUser32::get_instance()->GetWindowModuleFileNameA(hwnd, pszFileName, cchFileNameMax);
}

DLLEXPORT UINT WINAPI GetWindowModuleFileNameW (HWND hwnd, LPWSTR pszFileName, UINT cchFileNameMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowModuleFileNameW()");
  return IUser32::get_instance()->GetWindowModuleFileNameW(hwnd, pszFileName, cchFileNameMax);
}

DLLEXPORT WINBOOL WINAPI SetProcessDPIAware (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProcessDPIAware()");
  return IUser32::get_instance()->SetProcessDPIAware();
}

DLLEXPORT WINBOOL WINAPI IsProcessDPIAware (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsProcessDPIAware()");
  return IUser32::get_instance()->IsProcessDPIAware();
}

DLLEXPORT WINBOOL WINAPI GetCursorInfo (PCURSORINFO pci)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCursorInfo()");
  return IUser32::get_instance()->GetCursorInfo(pci);
}

DLLEXPORT WINBOOL WINAPI GetWindowInfo (HWND hwnd, PWINDOWINFO pwi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowInfo()");
  return IUser32::get_instance()->GetWindowInfo(hwnd, pwi);
}

DLLEXPORT WINBOOL WINAPI GetTitleBarInfo (HWND hwnd, PTITLEBARINFO pti)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTitleBarInfo()");
  return IUser32::get_instance()->GetTitleBarInfo(hwnd, pti);
}

DLLEXPORT WINBOOL WINAPI GetMenuBarInfo (HWND hwnd, LONG idObject, LONG idItem, PMENUBARINFO pmbi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuBarInfo()");
  return IUser32::get_instance()->GetMenuBarInfo(hwnd, idObject, idItem, pmbi);
}

DLLEXPORT WINBOOL WINAPI GetScrollBarInfo (HWND hwnd, LONG idObject, PSCROLLBARINFO psbi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetScrollBarInfo()");
  return IUser32::get_instance()->GetScrollBarInfo(hwnd, idObject, psbi);
}

DLLEXPORT WINBOOL WINAPI GetComboBoxInfo (HWND hwndCombo, PCOMBOBOXINFO pcbi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetComboBoxInfo()");
  return IUser32::get_instance()->GetComboBoxInfo(hwndCombo, pcbi);
}

DLLEXPORT HWND WINAPI GetAncestor (HWND hwnd, UINT gaFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAncestor()");
  return IUser32::get_instance()->GetAncestor(hwnd, gaFlags);
}

DLLEXPORT HWND WINAPI RealChildWindowFromPoint (HWND hwndParent, POINT ptParentClientCoords)
{
  logging::log("wrapper", logging::LogLevel::debug, "RealChildWindowFromPoint()");
  return IUser32::get_instance()->RealChildWindowFromPoint(hwndParent, ptParentClientCoords);
}

DLLEXPORT UINT WINAPI RealGetWindowClassA (HWND hwnd, LPSTR ptszClassName, UINT cchClassNameMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "RealGetWindowClassA()");
  return IUser32::get_instance()->RealGetWindowClassA(hwnd, ptszClassName, cchClassNameMax);
}

DLLEXPORT UINT WINAPI RealGetWindowClassW (HWND hwnd, LPWSTR ptszClassName, UINT cchClassNameMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "RealGetWindowClassW()");
  return IUser32::get_instance()->RealGetWindowClassW(hwnd, ptszClassName, cchClassNameMax);
}

DLLEXPORT WINBOOL WINAPI GetAltTabInfoA (HWND hwnd, int iItem, PALTTABINFO pati, LPSTR pszItemText, UINT cchItemText)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAltTabInfoA()");
  return IUser32::get_instance()->GetAltTabInfoA(hwnd, iItem, pati, pszItemText, cchItemText);
}

DLLEXPORT WINBOOL WINAPI GetAltTabInfoW (HWND hwnd, int iItem, PALTTABINFO pati, LPWSTR pszItemText, UINT cchItemText)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAltTabInfoW()");
  return IUser32::get_instance()->GetAltTabInfoW(hwnd, iItem, pati, pszItemText, cchItemText);
}

DLLEXPORT DWORD WINAPI GetListBoxInfo (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetListBoxInfo()");
  return IUser32::get_instance()->GetListBoxInfo(hwnd);
}

DLLEXPORT WINBOOL WINAPI LockWorkStation (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "LockWorkStation()");
  return IUser32::get_instance()->LockWorkStation();
}

DLLEXPORT WINBOOL WINAPI UserHandleGrantAccess (HANDLE hUserHandle, HANDLE hJob, WINBOOL bGrant)
{
  logging::log("wrapper", logging::LogLevel::debug, "UserHandleGrantAccess()");
  return IUser32::get_instance()->UserHandleGrantAccess(hUserHandle, hJob, bGrant);
}

DLLEXPORT UINT WINAPI GetRawInputData (HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawInputData");
  return IUser32::get_instance()->GetRawInputData(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);
}

DLLEXPORT UINT WINAPI GetRawInputDeviceInfoA (HANDLE hDevice, UINT uiCommand, LPVOID pData, PUINT pcbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawInputDeviceInfoA");
  return IUser32::get_instance()->GetRawInputDeviceInfoA(hDevice, uiCommand, pData, pcbSize);
}

DLLEXPORT UINT WINAPI GetRawInputDeviceInfoW (HANDLE hDevice, UINT uiCommand, LPVOID pData, PUINT pcbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawInputDeviceInfoW");
  return IUser32::get_instance()->GetRawInputDeviceInfoW(hDevice, uiCommand, pData, pcbSize);
}

DLLEXPORT UINT WINAPI GetRawInputBuffer (PRAWINPUT pData, PUINT pcbSize, UINT cbSizeHeader)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawInputBuffer");
  return IUser32::get_instance()->GetRawInputBuffer(pData, pcbSize, cbSizeHeader);
}

DLLEXPORT WINBOOL WINAPI RegisterRawInputDevices (PCRAWINPUTDEVICE pRawInputDevices, UINT uiNumDevices, UINT cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterRawInputDevices");
  return IUser32::get_instance()->RegisterRawInputDevices(pRawInputDevices, uiNumDevices, cbSize);
}

DLLEXPORT UINT WINAPI GetRegisteredRawInputDevices (PRAWINPUTDEVICE pRawInputDevices, PUINT puiNumDevices, UINT cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRegisteredRawInputDevices");
  return IUser32::get_instance()->GetRegisteredRawInputDevices(pRawInputDevices, puiNumDevices, cbSize);
}

DLLEXPORT UINT WINAPI GetRawInputDeviceList (PRAWINPUTDEVICELIST pRawInputDeviceList, PUINT puiNumDevices, UINT cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawInputDeviceList");
  return IUser32::get_instance()->GetRawInputDeviceList(pRawInputDeviceList, puiNumDevices, cbSize);
}

DLLEXPORT LRESULT WINAPI DefRawInputProc (PRAWINPUT * paRawInput, INT nInput, UINT cbSizeHeader)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefRawInputProc");
  return IUser32::get_instance()->DefRawInputProc(paRawInput, nInput, cbSizeHeader);
}

DLLEXPORT WINBOOL WINAPI GetPointerDevices (UINT32 * deviceCount, POINTER_DEVICE_INFO * pointerDevices)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerDevices()");
  return IUser32::get_instance()->GetPointerDevices(deviceCount, pointerDevices);
}

DLLEXPORT WINBOOL WINAPI GetPointerDevice (HANDLE device, POINTER_DEVICE_INFO * pointerDevice)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerDevice()");
  return IUser32::get_instance()->GetPointerDevice(device, pointerDevice);
}

DLLEXPORT WINBOOL WINAPI GetPointerDeviceProperties (HANDLE device, UINT32 * propertyCount, POINTER_DEVICE_PROPERTY * pointerProperties)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerDeviceProperties()");
  return IUser32::get_instance()->GetPointerDeviceProperties(device, propertyCount, pointerProperties);
}

DLLEXPORT WINBOOL WINAPI RegisterPointerDeviceNotifications (HWND window, WINBOOL notifyRange)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterPointerDeviceNotifications()");
  return IUser32::get_instance()->RegisterPointerDeviceNotifications(window, notifyRange);
}

DLLEXPORT WINBOOL WINAPI GetPointerDeviceRects (HANDLE device, RECT * pointerDeviceRect, RECT * displayRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerDeviceRects()");
  return IUser32::get_instance()->GetPointerDeviceRects(device, pointerDeviceRect, displayRect);
}

DLLEXPORT WINBOOL WINAPI GetPointerDeviceCursors (HANDLE device, UINT32 * cursorCount, POINTER_DEVICE_CURSOR_INFO * deviceCursors)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerDeviceCursors()");
  return IUser32::get_instance()->GetPointerDeviceCursors(device, cursorCount, deviceCursors);
}

DLLEXPORT WINBOOL WINAPI GetRawPointerDeviceData (UINT32 pointerId, UINT32 historyCount, UINT32 propertiesCount, POINTER_DEVICE_PROPERTY * pProperties, LONG * pValues)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawPointerDeviceData()");
  return IUser32::get_instance()->GetRawPointerDeviceData(pointerId, historyCount, propertiesCount, pProperties, pValues);
}

DLLEXPORT WINBOOL WINAPI ChangeWindowMessageFilter (UINT message, DWORD dwFlag)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeWindowMessageFilter()");
  return IUser32::get_instance()->ChangeWindowMessageFilter(message, dwFlag);
}

DLLEXPORT WINBOOL WINAPI ChangeWindowMessageFilterEx (HWND hwnd, UINT message, DWORD action, PCHANGEFILTERSTRUCT pChangeFilterStruct)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeWindowMessageFilterEx()");
  return IUser32::get_instance()->ChangeWindowMessageFilterEx(hwnd, message, action, pChangeFilterStruct);
}

DLLEXPORT WINBOOL WINAPI GetGestureInfo (HGESTUREINFO hGestureInfo, PGESTUREINFO pGestureInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetGestureInfo()");
  return IUser32::get_instance()->GetGestureInfo(hGestureInfo, pGestureInfo);
}

DLLEXPORT WINBOOL WINAPI GetGestureExtraArgs (HGESTUREINFO hGestureInfo, UINT cbExtraArgs, PBYTE pExtraArgs)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetGestureExtraArgs()");
  return IUser32::get_instance()->GetGestureExtraArgs(hGestureInfo, cbExtraArgs, pExtraArgs);
}

DLLEXPORT WINBOOL WINAPI CloseGestureInfoHandle (HGESTUREINFO hGestureInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseGestureInfoHandle()");
  return IUser32::get_instance()->CloseGestureInfoHandle(hGestureInfo);
}

DLLEXPORT WINBOOL WINAPI SetGestureConfig (HWND hwnd, DWORD dwReserved, UINT cIDs, PGESTURECONFIG pGestureConfig, UINT cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetGestureConfig()");
  return IUser32::get_instance()->SetGestureConfig(hwnd, dwReserved, cIDs, pGestureConfig, cbSize);
}

DLLEXPORT WINBOOL WINAPI GetGestureConfig (HWND hwnd, DWORD dwReserved, DWORD dwFlags, PUINT pcIDs, PGESTURECONFIG pGestureConfig, UINT cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetGestureConfig()");
  return IUser32::get_instance()->GetGestureConfig(hwnd, dwReserved, dwFlags, pcIDs, pGestureConfig, cbSize);
}

DLLEXPORT WINBOOL WINAPI ShutdownBlockReasonCreate (HWND hWnd, LPCWSTR pwszReason)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShutdownBlockReasonCreate()");
  return IUser32::get_instance()->ShutdownBlockReasonCreate(hWnd, pwszReason);
}

DLLEXPORT WINBOOL WINAPI ShutdownBlockReasonQuery (HWND hWnd, LPWSTR pwszBuff, DWORD * pcchBuff)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShutdownBlockReasonQuery()");
  return IUser32::get_instance()->ShutdownBlockReasonQuery(hWnd, pwszBuff, pcchBuff);
}

DLLEXPORT WINBOOL WINAPI ShutdownBlockReasonDestroy (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShutdownBlockReasonDestroy()");
  return IUser32::get_instance()->ShutdownBlockReasonDestroy(hWnd);
}

DLLEXPORT WINBOOL WINAPI GetCurrentInputMessageSource (INPUT_MESSAGE_SOURCE * inputMessageSource)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCurrentInputMessageSource()");
  return IUser32::get_instance()->GetCurrentInputMessageSource(inputMessageSource);
}

DLLEXPORT WINBOOL WINAPI GetCIMSSM (INPUT_MESSAGE_SOURCE * inputMessageSource)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCIMSSM()");
  return IUser32::get_instance()->GetCIMSSM(inputMessageSource);
}

DLLEXPORT WINBOOL WINAPI GetAutoRotationState (PAR_STATE pState)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAutoRotationState()");
  return IUser32::get_instance()->GetAutoRotationState(pState);
}

DLLEXPORT WINBOOL WINAPI GetDisplayAutoRotationPreferences (ORIENTATION_PREFERENCE * pOrientation)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDisplayAutoRotationPreferences()");
  return IUser32::get_instance()->GetDisplayAutoRotationPreferences(pOrientation);
}

DLLEXPORT WINBOOL WINAPI GetDisplayAutoRotationPreferencesByProcessId (DWORD dwProcessId, ORIENTATION_PREFERENCE * pOrientation, WINBOOL * fRotateScreen)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDisplayAutoRotationPreferencesByProcessId()");
  return IUser32::get_instance()->GetDisplayAutoRotationPreferencesByProcessId(dwProcessId, pOrientation, fRotateScreen);
}

DLLEXPORT WINBOOL WINAPI SetDisplayAutoRotationPreferences (ORIENTATION_PREFERENCE orientation)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDisplayAutoRotationPreferences()");
  return IUser32::get_instance()->SetDisplayAutoRotationPreferences(orientation);
}

DLLEXPORT WINBOOL WINAPI IsImmersiveProcess (HANDLE hProcess)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsImmersiveProcess()");
  return IUser32::get_instance()->IsImmersiveProcess(hProcess);
}

DLLEXPORT WINBOOL WINAPI SetProcessRestrictionExemption (WINBOOL fEnableExemption)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProcessRestrictionExemption()");
  return IUser32::get_instance()->SetProcessRestrictionExemption(fEnableExemption);
}

DLLEXPORT WINBOOL WINAPI GetPointerInputTransform (UINT32 pointerId, UINT32 historyCount, UINT32 * inputTransform)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerInputTransform()");
  return IUser32::get_instance()->GetPointerInputTransform(pointerId, historyCount, inputTransform);
}

DLLEXPORT WINBOOL WINAPI IsMousePointerEnabled (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsMousePointerEnabled()");
  return IUser32::get_instance()->IsMousePointerEnabled();
}

DLLEXPORT UINT_PTR WINAPI SetSystemTimer (HWND hwnd, UINT_PTR id, UINT timeout, void * unknown)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetSystemTimer()");
  return IUser32::get_instance()->SetSystemTimer(hwnd, id, timeout, unknown);
}

DLLEXPORT DWORD WINAPI CalcMenuBar (HWND hwnd, DWORD left, DWORD right, DWORD top, RECT * rect)
{
  logging::log("wrapper", logging::LogLevel::debug, "CalcMenuBar()");
  return IUser32::get_instance()->CalcMenuBar(hwnd, left, right, top, rect);
}

DLLEXPORT UINT WINAPI WINNLSGetIMEHotkey (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "WINNLSGetIMEHotkey()");
  return IUser32::get_instance()->WINNLSGetIMEHotkey(hwnd);
}

DLLEXPORT HWND WINAPI GetTaskmanWindow (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTaskmanWindow()");
  return IUser32::get_instance()->GetTaskmanWindow();
}

DLLEXPORT BOOL WINAPI DdeDisconnect (HCONV hConv)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeDisconnect()");
  return IUser32::get_instance()->DdeDisconnect(hConv);
}

DLLEXPORT HSZ WINAPI DdeCreateStringHandleA (DWORD idInst, LPCSTR psz, INT codepage)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeCreateStringHandleA()");
  return IUser32::get_instance()->DdeCreateStringHandleA(idInst, psz, codepage);
}

DLLEXPORT BOOL WINAPI SetProcessDpiAwarenessInternal (DPI_AWARENESS awareness)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProcessDpiAwarenessInternal()");
  return IUser32::get_instance()->SetProcessDpiAwarenessInternal(awareness);
}

DLLEXPORT BOOL WINAPI SetDeskWallpaper (const char * filename)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDeskWallpaper()");
  return IUser32::get_instance()->SetDeskWallpaper(filename);
}

DLLEXPORT NTSTATUS WINAPI User32ImmTranslateMessage (void * args, ULONG size)
{
  logging::log("wrapper", logging::LogLevel::debug, "User32ImmTranslateMessage()");
  return IUser32::get_instance()->User32ImmTranslateMessage(args, size);
}

DLLEXPORT DWORD WINAPI DdeGetData (HDDEDATA hData, LPBYTE pDst, DWORD cbMax, DWORD cbOff)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeGetData()");
  return IUser32::get_instance()->DdeGetData(hData, pDst, cbMax, cbOff);
}

DLLEXPORT DWORD_PTR WINAPI SetSysColorsTemp (const COLORREF * pPens, const HBRUSH * pBrushes, DWORD_PTR n)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetSysColorsTemp()");
  return IUser32::get_instance()->SetSysColorsTemp(pPens, pBrushes, n);
}

DLLEXPORT LRESULT WINAPI StaticWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "StaticWndProcW()");
  return IUser32::get_instance()->StaticWndProcW(hwnd, msg, wParam, lParam);
}

DLLEXPORT LPBYTE WINAPI DdeAccessData (HDDEDATA hData, LPDWORD pcbDataSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeAccessData()");
  return IUser32::get_instance()->DdeAccessData(hData, pcbDataSize);
}

DLLEXPORT BOOL WINAPI DdeUnaccessData (HDDEDATA hData)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeUnaccessData()");
  return IUser32::get_instance()->DdeUnaccessData(hData);
}

DLLEXPORT UINT WINAPI DdeInitializeA (LPDWORD pidInst, PFNCALLBACK pfnCallback, DWORD afCmd, DWORD ulRes)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeInitializeA()");
  return IUser32::get_instance()->DdeInitializeA(pidInst, pfnCallback, afCmd, ulRes);
}

DLLEXPORT UINT WINAPI DdeInitializeW (LPDWORD pidInst, PFNCALLBACK pfnCallback, DWORD afCmd, DWORD ulRes)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeInitializeW()");
  return IUser32::get_instance()->DdeInitializeW(pidInst, pfnCallback, afCmd, ulRes);
}

DLLEXPORT BOOL WINAPI DdeUninitialize (DWORD idInst)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeUninitialize()");
  return IUser32::get_instance()->DdeUninitialize(idInst);
}

DLLEXPORT VOID WINAPI LoadLocalFonts (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadLocalFonts()");
  IUser32::get_instance()->LoadLocalFonts();
}

DLLEXPORT LPSTR WINAPI CharPrevExW (WORD codepage, LPCWSTR start, LPCWSTR ptr, DWORD flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharPrevExW()");
  return IUser32::get_instance()->CharPrevExW(codepage, start, ptr, flags);
}

DLLEXPORT HWND WINAPI GetProgmanWindow (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetProgmanWindow()");
  return IUser32::get_instance()->GetProgmanWindow();
}

DLLEXPORT DPI_AWARENESS_CONTEXT WINAPI SetThreadDpiAwarenessContext (DPI_AWARENESS_CONTEXT context)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetThreadDpiAwarenessContext()");
  return IUser32::get_instance()->SetThreadDpiAwarenessContext(context);
}

DLLEXPORT LPARAM WINAPI PackDDElParam (UINT msg, UINT_PTR uiLo, UINT_PTR uiHi)
{
  logging::log("wrapper", logging::LogLevel::debug, "PackDDElParam()");
  return IUser32::get_instance()->PackDDElParam(msg, uiLo, uiHi);
}

DLLEXPORT BOOL WINAPI DdeFreeDataHandle (HDDEDATA hData)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeFreeDataHandle()");
  return IUser32::get_instance()->DdeFreeDataHandle(hData);
}

DLLEXPORT BOOL WINAPI AlignRects (LPRECT rect, DWORD b, DWORD c, DWORD d)
{
  logging::log("wrapper", logging::LogLevel::debug, "AlignRects()");
  return IUser32::get_instance()->AlignRects(rect, b, c, d);
}

DLLEXPORT DWORD WINAPI DdeQueryStringW (DWORD idInst, HSZ hsz, LPWSTR psz, DWORD cchMax, INT iCodePage)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeQueryStringW()");
  return IUser32::get_instance()->DdeQueryStringW(idInst, hsz, psz, cchMax, iCodePage);
}

DLLEXPORT DWORD WINAPI SetLogonNotifyWindow (HWINSTA hwinsta, HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetLogonNotifyWindow()");
  return IUser32::get_instance()->SetLogonNotifyWindow(hwinsta, hwnd);
}

DLLEXPORT HCURSOR WINAPI GetCursorFrameInfo (HCURSOR handle, DWORD reserved, DWORD istep, DWORD * rate, DWORD * steps)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCursorFrameInfo()");
  return IUser32::get_instance()->GetCursorFrameInfo(handle, reserved, istep, rate, steps);
}

DLLEXPORT DWORD WINAPI DdeQueryStringA (DWORD idInst, HSZ hsz, LPSTR psz, DWORD cchMax, INT iCodePage)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeQueryStringA()");
  return IUser32::get_instance()->DdeQueryStringA(idInst, hsz, psz, cchMax, iCodePage);
}

DLLEXPORT BOOL WINAPI DdeSetQualityOfService (HWND hwndClient, const SECURITY_QUALITY_OF_SERVICE * pqosNew, PSECURITY_QUALITY_OF_SERVICE pqosPrev)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeSetQualityOfService()");
  return IUser32::get_instance()->DdeSetQualityOfService(hwndClient, pqosNew, pqosPrev);
}

DLLEXPORT UINT WINAPI DdeGetLastError (DWORD idInst)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeGetLastError()");
  return IUser32::get_instance()->DdeGetLastError(idInst);
}

DLLEXPORT LRESULT WINAPI ComboWndProcA (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ComboWndProcA()");
  return IUser32::get_instance()->ComboWndProcA(hwnd, message, wParam, lParam);
}

DLLEXPORT BOOL WINAPI DdeDisconnectList (HCONVLIST hConvList)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeDisconnectList()");
  return IUser32::get_instance()->DdeDisconnectList(hConvList);
}

DLLEXPORT LRESULT WINAPI SendIMEMessageExA (HWND hwnd, LPARAM lparam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendIMEMessageExA()");
  return IUser32::get_instance()->SendIMEMessageExA(hwnd, lparam);
}

DLLEXPORT INT WINAPI DdeCmpStringHandles (HSZ hsz1, HSZ hsz2)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeCmpStringHandles()");
  return IUser32::get_instance()->DdeCmpStringHandles(hsz1, hsz2);
}

DLLEXPORT DWORD WINAPI RegisterTasklist (DWORD x)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterTasklist()");
  return IUser32::get_instance()->RegisterTasklist(x);
}

DLLEXPORT LRESULT WINAPI IconTitleWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "IconTitleWndProc()");
  return IUser32::get_instance()->IconTitleWndProc(hWnd, msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI SendIMEMessageExW (HWND hwnd, LPARAM lparam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendIMEMessageExW()");
  return IUser32::get_instance()->SendIMEMessageExW(hwnd, lparam);
}

DLLEXPORT LRESULT WINAPI ComboWndProcW (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ComboWndProcW()");
  return IUser32::get_instance()->ComboWndProcW(hwnd, message, wParam, lParam);
}

DLLEXPORT HCONVLIST WINAPI DdeConnectList (DWORD idInst, HSZ hszService, HSZ hszTopic, HCONVLIST hConvList, PCONVCONTEXT pCC)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeConnectList()");
  return IUser32::get_instance()->DdeConnectList(idInst, hszService, hszTopic, hConvList, pCC);
}

DLLEXPORT HCONV WINAPI DdeQueryNextServer (HCONVLIST hConvList, HCONV hConvPrev)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeQueryNextServer()");
  return IUser32::get_instance()->DdeQueryNextServer(hConvList, hConvPrev);
}

DLLEXPORT BOOL WINAPI RegisterUserApiHook (const struct user_api_hook * new_hook, struct user_api_hook * old_hook)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterUserApiHook()");
  return IUser32::get_instance()->RegisterUserApiHook(new_hook, old_hook);
}

DLLEXPORT void WINAPI UnregisterUserApiHook (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterUserApiHook()");
  IUser32::get_instance()->UnregisterUserApiHook();
}

DLLEXPORT LRESULT WINAPI StaticWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "StaticWndProcA()");
  return IUser32::get_instance()->StaticWndProcA(hwnd, msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI MDIClientWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "MDIClientWndProcW()");
  return IUser32::get_instance()->MDIClientWndProcW(hwnd, msg, wParam, lParam);
}

DLLEXPORT BOOL WINAPI DdeKeepStringHandle (DWORD idInst, HSZ hsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeKeepStringHandle()");
  return IUser32::get_instance()->DdeKeepStringHandle(idInst, hsz);
}

DLLEXPORT DWORD WINAPI GetAppCompatFlags (HTASK hTask)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAppCompatFlags()");
  return IUser32::get_instance()->GetAppCompatFlags(hTask);
}

DLLEXPORT HWND WINAPI SetProgmanWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProgmanWindow()");
  return IUser32::get_instance()->SetProgmanWindow(hwnd);
}

DLLEXPORT BOOL WINAPI DdeEnableCallback (DWORD idInst, HCONV hConv, UINT wCmd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeEnableCallback()");
  return IUser32::get_instance()->DdeEnableCallback(idInst, hConv, wCmd);
}

DLLEXPORT DPI_HOSTING_BEHAVIOR WINAPI GetThreadDpiHostingBehavior (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetThreadDpiHostingBehavior()");
  return IUser32::get_instance()->GetThreadDpiHostingBehavior();
}

DLLEXPORT LRESULT WINAPI MDIClientWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "MDIClientWndProcA()");
  return IUser32::get_instance()->MDIClientWndProcA(hwnd, msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI EditWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EditWndProcW()");
  return IUser32::get_instance()->EditWndProcW(hwnd, msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI ButtonWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ButtonWndProcW()");
  return IUser32::get_instance()->ButtonWndProcW(hwnd, msg, wParam, lParam);
}

DLLEXPORT HWND WINAPI SetTaskmanWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetTaskmanWindow()");
  return IUser32::get_instance()->SetTaskmanWindow(hwnd);
}

DLLEXPORT BOOL WINAPI DdeImpersonateClient (HCONV hConv)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeImpersonateClient()");
  return IUser32::get_instance()->DdeImpersonateClient(hConv);
}

DLLEXPORT UINT WINAPI DdeQueryConvInfo (HCONV hConv, DWORD id, PCONVINFO lpConvInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeQueryConvInfo()");
  return IUser32::get_instance()->DdeQueryConvInfo(hConv, id, lpConvInfo);
}

DLLEXPORT void WINAPI CalcChildScroll (HWND hwnd, INT scroll)
{
  logging::log("wrapper", logging::LogLevel::debug, "CalcChildScroll()");
  IUser32::get_instance()->CalcChildScroll(hwnd, scroll);
}

DLLEXPORT HCONV WINAPI DdeConnect (DWORD idInst, HSZ hszService, HSZ hszTopic, PCONVCONTEXT pCC)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeConnect()");
  return IUser32::get_instance()->DdeConnect(idInst, hszService, hszTopic, pCC);
}

DLLEXPORT HCONV WINAPI DdeReconnect (HCONV hConv)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeReconnect()");
  return IUser32::get_instance()->DdeReconnect(hConv);
}

DLLEXPORT LPWSTR WINAPI CharNextExW (WORD codepage, LPCWSTR ptr, DWORD flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharNextExW()");
  return IUser32::get_instance()->CharNextExW(codepage, ptr, flags);
}

DLLEXPORT LRESULT WINAPI EditWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EditWndProcA()");
  return IUser32::get_instance()->EditWndProcA(hwnd, msg, wParam, lParam);
}

DLLEXPORT BOOL WINAPI GetProcessDpiAwarenessInternal (HANDLE process, DPI_AWARENESS * awareness)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetProcessDpiAwarenessInternal()");
  return IUser32::get_instance()->GetProcessDpiAwarenessInternal(process, awareness);
}

DLLEXPORT void WINAPI RegisterSystemThread (DWORD flags, DWORD reserved)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterSystemThread()");
  IUser32::get_instance()->RegisterSystemThread(flags, reserved);
}

DLLEXPORT BOOL WINAPI SetWindowCompositionAttribute (HWND hwnd, WINDOWCOMPOSITIONATTRIBDATA const * pwcad)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowCompositionAttribute()");
  return IUser32::get_instance()->SetWindowCompositionAttribute(hwnd, pwcad);
}

DLLEXPORT HDDEDATA WINAPI DdeClientTransaction (LPBYTE pData, DWORD cbData, HCONV hConv, HSZ hszItem, UINT wFmt, UINT wType, DWORD dwTimeout, LPDWORD pdwResult)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeClientTransaction()");
  return IUser32::get_instance()->DdeClientTransaction(pData, cbData, hConv, hszItem, wFmt, wType, dwTimeout, pdwResult);
}

DLLEXPORT BOOL WINAPI DdeAbandonTransaction (DWORD idInst, HCONV hConv, DWORD idTransaction)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeAbandonTransaction()");
  return IUser32::get_instance()->DdeAbandonTransaction(idInst, hConv, idTransaction);
}

DLLEXPORT LRESULT WINAPI ScrollBarWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollBarWndProcA()");
  return IUser32::get_instance()->ScrollBarWndProcA(hwnd, msg, wParam, lParam);
}

DLLEXPORT HKL WINAPI LoadKeyboardLayoutEx (HKL layout, const WCHAR * name, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadKeyboardLayoutEx()");
  return IUser32::get_instance()->LoadKeyboardLayoutEx(layout, name, flags);
}

DLLEXPORT int WINAPI RegisterServicesProcess (DWORD ServicesProcessId)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterServicesProcess()");
  return IUser32::get_instance()->RegisterServicesProcess(ServicesProcessId);
}

DLLEXPORT HDDEDATA WINAPI DdeCreateDataHandle (DWORD idInst, LPBYTE pSrc, DWORD cb, DWORD cbOff, HSZ hszItem, UINT wFmt, UINT afCmd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeCreateDataHandle()");
  return IUser32::get_instance()->DdeCreateDataHandle(idInst, pSrc, cb, cbOff, hszItem, wFmt, afCmd);
}

DLLEXPORT HDDEDATA WINAPI DdeAddData (HDDEDATA hData, LPBYTE pSrc, DWORD cb, DWORD cbOff)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeAddData()");
  return IUser32::get_instance()->DdeAddData(hData, pSrc, cb, cbOff);
}

DLLEXPORT LRESULT WINAPI ScrollBarWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollBarWndProcW()");
  return IUser32::get_instance()->ScrollBarWndProcW(hwnd, msg, wParam, lParam);
}

DLLEXPORT HDDEDATA WINAPI DdeNameService (DWORD idInst, HSZ hsz1, HSZ hsz2, UINT afCmd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeNameService()");
  return IUser32::get_instance()->DdeNameService(idInst, hsz1, hsz2, afCmd);
}

DLLEXPORT LRESULT WINAPI ButtonWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ButtonWndProcA()");
  return IUser32::get_instance()->ButtonWndProcA(hwnd, msg, wParam, lParam);
}

DLLEXPORT INT WINAPI GetSystemMetricsForDpi (INT index, UINT dpi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSystemMetricsForDpi()");
  return IUser32::get_instance()->GetSystemMetricsForDpi(index, dpi);
}

DLLEXPORT DPI_HOSTING_BEHAVIOR WINAPI GetWindowDpiHostingBehavior (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowDpiHostingBehavior()");
  return IUser32::get_instance()->GetWindowDpiHostingBehavior(hwnd);
}

DLLEXPORT DWORD WINAPI SetWindowStationUser (DWORD x1, DWORD x2)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowStationUser()");
  return IUser32::get_instance()->SetWindowStationUser(x1, x2);
}

DLLEXPORT BOOL WINAPI SystemParametersInfoForDpi (UINT action, UINT val, PVOID ptr, UINT winini, UINT dpi)
{
  logging::log("wrapper", logging::LogLevel::debug, "SystemParametersInfoForDpi()");
  return IUser32::get_instance()->SystemParametersInfoForDpi(action, val, ptr, winini, dpi);
}

DLLEXPORT LRESULT WINAPI MessageWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageWndProc()");
  return IUser32::get_instance()->MessageWndProc(hwnd, message, wParam, lParam);
}

DLLEXPORT BOOL WINAPI IsWindowRedirectedForPrint (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWindowRedirectedForPrint()");
  return IUser32::get_instance()->IsWindowRedirectedForPrint(hwnd);
}

DLLEXPORT BOOL WINAPI WINNLSGetEnableStatus (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "WINNLSGetEnableStatus()");
  return IUser32::get_instance()->WINNLSGetEnableStatus(hwnd);
}

DLLEXPORT BOOL WINAPI KillSystemTimer (HWND hwnd, UINT_PTR id)
{
  logging::log("wrapper", logging::LogLevel::debug, "KillSystemTimer()");
  return IUser32::get_instance()->KillSystemTimer(hwnd, id);
}

DLLEXPORT HSZ WINAPI DdeCreateStringHandleW (DWORD idInst, LPCWSTR psz, INT codepage)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeCreateStringHandleW()");
  return IUser32::get_instance()->DdeCreateStringHandleW(idInst, psz, codepage);
}

DLLEXPORT INT_PTR WINAPI MDI_MoreWindowsDlgProc (HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "MDI_MoreWindowsDlgProc()");
  return IUser32::get_instance()->MDI_MoreWindowsDlgProc(hDlg, iMsg, wParam, lParam);
}

DLLEXPORT BOOL WINAPI WINNLSEnableIME (HWND hwnd, BOOL enable)
{
  logging::log("wrapper", logging::LogLevel::debug, "WINNLSEnableIME()");
  return IUser32::get_instance()->WINNLSEnableIME(hwnd, enable);
}

DLLEXPORT BOOL WINAPI AdjustWindowRectExForDpi (LPRECT rect, DWORD style, BOOL menu, DWORD dwExStyle, UINT dpi)
{
  logging::log("wrapper", logging::LogLevel::debug, "AdjustWindowRectExForDpi()");
  return IUser32::get_instance()->AdjustWindowRectExForDpi(rect, style, menu, dwExStyle, dpi);
}

DLLEXPORT DPI_AWARENESS_CONTEXT WINAPI GetThreadDpiAwarenessContext (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetThreadDpiAwarenessContext()");
  return IUser32::get_instance()->GetThreadDpiAwarenessContext();
}

DLLEXPORT BOOL WINAPI DdeFreeStringHandle (DWORD idInst, HSZ hsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeFreeStringHandle()");
  return IUser32::get_instance()->DdeFreeStringHandle(idInst, hsz);
}

DLLEXPORT BOOL WINAPI DrawCaptionTempA (HWND hwnd, HDC hdc, const RECT * rect, HFONT hFont, HICON hIcon, LPCSTR str, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawCaptionTempA()");
  return IUser32::get_instance()->DrawCaptionTempA(hwnd, hdc, rect, hFont, hIcon, str, uFlags);
}

DLLEXPORT WORD WINAPI TileChildWindows (HWND parent, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "TileChildWindows()");
  return IUser32::get_instance()->TileChildWindows(parent, flags);
}

DLLEXPORT LPARAM WINAPI ReuseDDElParam (LPARAM lParam, UINT msgIn, UINT msgOut, UINT_PTR uiLo, UINT_PTR uiHi)
{
  logging::log("wrapper", logging::LogLevel::debug, "ReuseDDElParam()");
  return IUser32::get_instance()->ReuseDDElParam(lParam, msgIn, msgOut, uiLo, uiHi);
}

DLLEXPORT BOOL WINAPI ImpersonateDdeClientWindow (HWND hWndClient, HWND hWndServer)
{
  logging::log("wrapper", logging::LogLevel::debug, "ImpersonateDdeClientWindow()");
  return IUser32::get_instance()->ImpersonateDdeClientWindow(hWndClient, hWndServer);
}

DLLEXPORT UINT WINAPI GetDpiForSystem (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDpiForSystem()");
  return IUser32::get_instance()->GetDpiForSystem();
}

DLLEXPORT BOOL WINAPI User32InitializeImmEntryTable (DWORD magic)
{
  logging::log("wrapper", logging::LogLevel::debug, "User32InitializeImmEntryTable()");
  /* Cannot just always return FALSE here, because DLL won't load. */
  try
  {
    if (!IUser32::has_instance())
    {
      logging::log("wrapper", logging::LogLevel::debug, "User32InitializeImmEntryTable(): User32 instance not ready, returning FALSE");
      return FALSE;
    }
    return IUser32::get_instance()->User32InitializeImmEntryTable(magic);
  }
  catch (std::runtime_error & e)
  {
    logging::log("wrapper", logging::LogLevel::debug, "Exception in User32InitializeImmEntryTable(): ", e.what());
    return FALSE;
  }
}

DLLEXPORT BOOL WINAPI EnableNonClientDpiScaling (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnableNonClientDpiScaling()");
  return IUser32::get_instance()->EnableNonClientDpiScaling(hwnd);
}

DLLEXPORT BOOL WINAPI ImmSetActiveContext (HWND arg0, HIMC arg1, BOOL arg2)
{
  logging::log("wrapper", logging::LogLevel::debug, "ImmSetActiveContext()");
  return IUser32::get_instance()->ImmSetActiveContext(arg0, arg1, arg2);
}

DLLEXPORT BOOL WINAPI IsValidDpiAwarenessContext (DPI_AWARENESS_CONTEXT context)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsValidDpiAwarenessContext()");
  return IUser32::get_instance()->IsValidDpiAwarenessContext(context);
}

DLLEXPORT void WINAPI ScrollChildren (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollChildren()");
  IUser32::get_instance()->ScrollChildren(hWnd, uMsg, wParam, lParam);
}

DLLEXPORT WORD WINAPI CascadeChildWindows (HWND parent, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CascadeChildWindows()");
  return IUser32::get_instance()->CascadeChildWindows(parent, flags);
}

DLLEXPORT DPI_AWARENESS_CONTEXT WINAPI GetWindowDpiAwarenessContext (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowDpiAwarenessContext()");
  return IUser32::get_instance()->GetWindowDpiAwarenessContext(hwnd);
}

DLLEXPORT HDEVNOTIFY WINAPI I_ScRegisterDeviceNotification (DEVICE_NOTIFICATION_DETAILS * details, LPVOID filter, DWORD flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "I_ScRegisterDeviceNotification()");
  return IUser32::get_instance()->I_ScRegisterDeviceNotification(details, filter, flags);
}

DLLEXPORT BOOL WINAPI I_ScUnregisterDeviceNotification (HDEVNOTIFY handle)
{
  logging::log("wrapper", logging::LogLevel::debug, "I_ScUnregisterDeviceNotification()");
  return IUser32::get_instance()->I_ScUnregisterDeviceNotification(handle);
}

DLLEXPORT BOOL WINAPI DdeSetUserHandle (HCONV hConv, DWORD id, DWORD hUser)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeSetUserHandle()");
  return IUser32::get_instance()->DdeSetUserHandle(hConv, id, hUser);
}

DLLEXPORT BOOL WINAPI DdePostAdvise (DWORD idInst, HSZ hszTopic, HSZ hszItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdePostAdvise()");
  return IUser32::get_instance()->DdePostAdvise(idInst, hszTopic, hszItem);
}

DLLEXPORT DWORD WINAPI GetAppCompatFlags2 (HTASK hTask)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAppCompatFlags2()");
  return IUser32::get_instance()->GetAppCompatFlags2(hTask);
}

DLLEXPORT BOOL WINAPI AreDpiAwarenessContextsEqual (DPI_AWARENESS_CONTEXT ctx1, DPI_AWARENESS_CONTEXT ctx2)
{
  logging::log("wrapper", logging::LogLevel::debug, "AreDpiAwarenessContextsEqual()");
  return IUser32::get_instance()->AreDpiAwarenessContextsEqual(ctx1, ctx2);
}

DLLEXPORT DPI_AWARENESS WINAPI GetAwarenessFromDpiAwarenessContext (DPI_AWARENESS_CONTEXT context)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAwarenessFromDpiAwarenessContext()");
  return IUser32::get_instance()->GetAwarenessFromDpiAwarenessContext(context);
}

DLLEXPORT BOOL WINAPI SetShellWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetShellWindow()");
  return IUser32::get_instance()->SetShellWindow(hwnd);
}

DLLEXPORT LRESULT WINAPI ImeWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ImeWndProcW()");
  return IUser32::get_instance()->ImeWndProcW(hwnd, msg, wParam, lParam);
}

DLLEXPORT UINT WINAPI GetDpiForWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDpiForWindow()");
  return IUser32::get_instance()->GetDpiForWindow(hwnd);
}

DLLEXPORT BOOL WINAPI UnpackDDElParam (UINT msg, LPARAM lParam, PUINT_PTR puiLo, PUINT_PTR puiHi)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnpackDDElParam()");
  return IUser32::get_instance()->UnpackDDElParam(msg, lParam, puiLo, puiHi);
}

DLLEXPORT BOOL WINAPI FreeDDElParam (UINT msg, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "FreeDDElParam()");
  return IUser32::get_instance()->FreeDDElParam(msg, lParam);
}

DLLEXPORT void WINAPI UserRegisterWowHandlers (const struct wow_handlers16 * new_, struct wow_handlers32 * orig)
{
  logging::log("wrapper", logging::LogLevel::debug, "UserRegisterWowHandlers()");
  IUser32::get_instance()->UserRegisterWowHandlers(new_, orig);
}

DLLEXPORT LRESULT WINAPI ImeWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ImeWndProcA()");
  return IUser32::get_instance()->ImeWndProcA(hwnd, msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI ListBoxWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ListBoxWndProcW()");
  return IUser32::get_instance()->ListBoxWndProcW(hwnd, msg, wParam, lParam);
}

DLLEXPORT LRESULT WINAPI ListBoxWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ListBoxWndProcA()");
  return IUser32::get_instance()->ListBoxWndProcA(hwnd, msg, wParam, lParam);
}

DLLEXPORT DPI_HOSTING_BEHAVIOR WINAPI SetThreadDpiHostingBehavior (DPI_HOSTING_BEHAVIOR value)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetThreadDpiHostingBehavior()");
  return IUser32::get_instance()->SetThreadDpiHostingBehavior(value);
}

DLLEXPORT DWORD WINAPI RegisterLogonProcess (HANDLE hprocess, BOOL x)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterLogonProcess()");
  return IUser32::get_instance()->RegisterLogonProcess(hprocess, x);
}

} //extern "C"


/* APIUser32 */
int APIUser32::wvsprintfA (LPSTR arg0, LPCSTR arg1, va_list arglist)
{
  logging::log("wrapper", logging::LogLevel::debug, "wvsprintfA()");
  return wvsprintfA_(arg0, arg1, arglist);
}

int APIUser32::wvsprintfW (LPWSTR arg0, LPCWSTR arg1, va_list arglist)
{
  logging::log("wrapper", logging::LogLevel::debug, "wvsprintfW()");
  return wvsprintfW_(arg0, arg1, arglist);
}

HKL APIUser32::LoadKeyboardLayoutA (LPCSTR pwszKLID, UINT Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadKeyboardLayoutA()");
  return LoadKeyboardLayoutA_(pwszKLID, Flags);
}

HKL APIUser32::LoadKeyboardLayoutW (LPCWSTR pwszKLID, UINT Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadKeyboardLayoutW()");
  return LoadKeyboardLayoutW_(pwszKLID, Flags);
}

HKL APIUser32::ActivateKeyboardLayout (HKL hkl, UINT Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ActivateKeyboardLayout()");
  return ActivateKeyboardLayout_(hkl, Flags);
}

int APIUser32::ToUnicodeEx (UINT wVirtKey, UINT wScanCode, CONST BYTE * lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "ToUnicodeEx()");
  return ToUnicodeEx_(wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags, dwhkl);
}

WINBOOL APIUser32::UnloadKeyboardLayout (HKL hkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnloadKeyboardLayout()");
  return UnloadKeyboardLayout_(hkl);
}

WINBOOL APIUser32::GetKeyboardLayoutNameA (LPSTR pwszKLID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardLayoutNameA()");
  return GetKeyboardLayoutNameA_(pwszKLID);
}

WINBOOL APIUser32::GetKeyboardLayoutNameW (LPWSTR pwszKLID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardLayoutNameW()");
  return GetKeyboardLayoutNameW_(pwszKLID);
}

int APIUser32::GetKeyboardLayoutList (int nBuff, HKL * lpList)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardLayoutList()");
  return GetKeyboardLayoutList_(nBuff, lpList);
}

HKL APIUser32::GetKeyboardLayout (DWORD idThread)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardLayout()");
  return GetKeyboardLayout_(idThread);
}

int APIUser32::GetMouseMovePointsEx (UINT cbSize, LPMOUSEMOVEPOINT lppt, LPMOUSEMOVEPOINT lpptBuf, int nBufPoints, DWORD resolution)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMouseMovePointsEx()");
  return GetMouseMovePointsEx_(cbSize, lppt, lpptBuf, nBufPoints, resolution);
}

HDESK APIUser32::CreateDesktopA (LPCSTR lpszDesktop, LPCSTR lpszDevice, LPDEVMODEA pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDesktopA()");
  return CreateDesktopA_(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa);
}

HDESK APIUser32::CreateDesktopW (LPCWSTR lpszDesktop, LPCWSTR lpszDevice, LPDEVMODEW pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDesktopW()");
  return CreateDesktopW_(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa);
}

HDESK APIUser32::CreateDesktopExA (LPCSTR lpszDesktop, LPCSTR lpszDevice, DEVMODEA * pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa, ULONG ulHeapSize, PVOID pvoid)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDesktopExA()");
  return CreateDesktopExA_(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa, ulHeapSize, pvoid);
}

HDESK APIUser32::CreateDesktopExW (LPCWSTR lpszDesktop, LPCWSTR lpszDevice, DEVMODEW * pDevmode, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa, ULONG ulHeapSize, PVOID pvoid)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDesktopExW()");
  return CreateDesktopExW_(lpszDesktop, lpszDevice, pDevmode, dwFlags, dwDesiredAccess, lpsa, ulHeapSize, pvoid);
}

HDESK APIUser32::OpenDesktopA (LPCSTR lpszDesktop, DWORD dwFlags, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenDesktopA()");
  return OpenDesktopA_(lpszDesktop, dwFlags, fInherit, dwDesiredAccess);
}

HDESK APIUser32::OpenDesktopW (LPCWSTR lpszDesktop, DWORD dwFlags, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenDesktopW()");
  return OpenDesktopW_(lpszDesktop, dwFlags, fInherit, dwDesiredAccess);
}

HDESK APIUser32::OpenInputDesktop (DWORD dwFlags, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenInputDesktop()");
  return OpenInputDesktop_(dwFlags, fInherit, dwDesiredAccess);
}

WINBOOL APIUser32::EnumDesktopsA (HWINSTA hwinsta, DESKTOPENUMPROCA lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDesktopsA()");
  return EnumDesktopsA_(hwinsta, lpEnumFunc, lParam);
}

WINBOOL APIUser32::EnumDesktopsW (HWINSTA hwinsta, DESKTOPENUMPROCW lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDesktopsW()");
  return EnumDesktopsW_(hwinsta, lpEnumFunc, lParam);
}

WINBOOL APIUser32::EnumDesktopWindows (HDESK hDesktop, WNDENUMPROC lpfn, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDesktopWindows()");
  return EnumDesktopWindows_(hDesktop, lpfn, lParam);
}

WINBOOL APIUser32::SwitchDesktop (HDESK hDesktop)
{
  logging::log("wrapper", logging::LogLevel::debug, "SwitchDesktop()");
  return SwitchDesktop_(hDesktop);
}

WINBOOL APIUser32::SetThreadDesktop (HDESK hDesktop)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetThreadDesktop()");
  return SetThreadDesktop_(hDesktop);
}

WINBOOL APIUser32::CloseDesktop (HDESK hDesktop)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseDesktop()");
  return CloseDesktop_(hDesktop);
}

HDESK APIUser32::GetThreadDesktop (DWORD dwThreadId)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetThreadDesktop()");
  return GetThreadDesktop_(dwThreadId);
}

HWINSTA APIUser32::CreateWindowStationA (LPCSTR lpwinsta, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateWindowStationA()");
  return CreateWindowStationA_(lpwinsta, dwFlags, dwDesiredAccess, lpsa);
}

HWINSTA APIUser32::CreateWindowStationW (LPCWSTR lpwinsta, DWORD dwFlags, ACCESS_MASK dwDesiredAccess, LPSECURITY_ATTRIBUTES lpsa)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateWindowStationW()");
  return CreateWindowStationW_(lpwinsta, dwFlags, dwDesiredAccess, lpsa);
}

HWINSTA APIUser32::OpenWindowStationA (LPCSTR lpszWinSta, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenWindowStationA()");
  return OpenWindowStationA_(lpszWinSta, fInherit, dwDesiredAccess);
}

HWINSTA APIUser32::OpenWindowStationW (LPCWSTR lpszWinSta, WINBOOL fInherit, ACCESS_MASK dwDesiredAccess)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenWindowStationW()");
  return OpenWindowStationW_(lpszWinSta, fInherit, dwDesiredAccess);
}

WINBOOL APIUser32::EnumWindowStationsA (WINSTAENUMPROCA lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumWindowStationsA()");
  return EnumWindowStationsA_(lpEnumFunc, lParam);
}

WINBOOL APIUser32::EnumWindowStationsW (WINSTAENUMPROCW lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumWindowStationsW()");
  return EnumWindowStationsW_(lpEnumFunc, lParam);
}

WINBOOL APIUser32::CloseWindowStation (HWINSTA hWinSta)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseWindowStation()");
  return CloseWindowStation_(hWinSta);
}

WINBOOL APIUser32::SetProcessWindowStation (HWINSTA hWinSta)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProcessWindowStation()");
  return SetProcessWindowStation_(hWinSta);
}

HWINSTA APIUser32::GetProcessWindowStation (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetProcessWindowStation()");
  return GetProcessWindowStation_();
}

WINBOOL APIUser32::SetUserObjectSecurity (HANDLE hObj, PSECURITY_INFORMATION pSIRequested, PSECURITY_DESCRIPTOR pSID)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetUserObjectSecurity()");
  return SetUserObjectSecurity_(hObj, pSIRequested, pSID);
}

WINBOOL APIUser32::GetUserObjectSecurity (HANDLE hObj, PSECURITY_INFORMATION pSIRequested, PSECURITY_DESCRIPTOR pSID, DWORD nLength, LPDWORD lpnLengthNeeded)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUserObjectSecurity()");
  return GetUserObjectSecurity_(hObj, pSIRequested, pSID, nLength, lpnLengthNeeded);
}

WINBOOL APIUser32::GetUserObjectInformationA (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength, LPDWORD lpnLengthNeeded)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUserObjectInformationA()");
  return GetUserObjectInformationA_(hObj, nIndex, pvInfo, nLength, lpnLengthNeeded);
}

WINBOOL APIUser32::GetUserObjectInformationW (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength, LPDWORD lpnLengthNeeded)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUserObjectInformationW()");
  return GetUserObjectInformationW_(hObj, nIndex, pvInfo, nLength, lpnLengthNeeded);
}

WINBOOL APIUser32::SetUserObjectInformationA (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetUserObjectInformationA()");
  return SetUserObjectInformationA_(hObj, nIndex, pvInfo, nLength);
}

WINBOOL APIUser32::SetUserObjectInformationW (HANDLE hObj, int nIndex, PVOID pvInfo, DWORD nLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetUserObjectInformationW()");
  return SetUserObjectInformationW_(hObj, nIndex, pvInfo, nLength);
}

WINBOOL APIUser32::IsHungAppWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsHungAppWindow()");
  return IsHungAppWindow_(hwnd);
}

VOID APIUser32::DisableProcessWindowsGhosting (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "DisableProcessWindowsGhosting()");
  DisableProcessWindowsGhosting_();
}

UINT APIUser32::RegisterWindowMessageA (LPCSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterWindowMessageA()");
  return RegisterWindowMessageA_(lpString);
}

UINT APIUser32::RegisterWindowMessageW (LPCWSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterWindowMessageW()");
  return RegisterWindowMessageW_(lpString);
}

WINBOOL APIUser32::TrackMouseEvent (LPTRACKMOUSEEVENT lpEventTrack)
{
  logging::log("wrapper", logging::LogLevel::debug, "TrackMouseEvent()");
  return TrackMouseEvent_(lpEventTrack);
}

WINBOOL APIUser32::DrawEdge (HDC hdc, LPRECT qrc, UINT edge, UINT grfFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawEdge()");
  return DrawEdge_(hdc, qrc, edge, grfFlags);
}

WINBOOL APIUser32::DrawFrameControl (HDC arg0, LPRECT arg1, UINT arg2, UINT arg3)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawFrameControl()");
  return DrawFrameControl_(arg0, arg1, arg2, arg3);
}

WINBOOL APIUser32::DrawCaption (HWND hwnd, HDC hdc, CONST RECT * lprect, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawCaption()");
  return DrawCaption_(hwnd, hdc, lprect, flags);
}

WINBOOL APIUser32::DrawAnimatedRects (HWND hwnd, int idAni, CONST RECT * lprcFrom, CONST RECT * lprcTo)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawAnimatedRects()");
  return DrawAnimatedRects_(hwnd, idAni, lprcFrom, lprcTo);
}

WINBOOL APIUser32::GetMessageA (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMessageA()");
  return GetMessageA_(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

WINBOOL APIUser32::GetMessageW (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMessageW()");
  return GetMessageW_(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

WINBOOL APIUser32::TranslateMessage (CONST MSG * lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "TranslateMessage()");
  return TranslateMessage_(lpMsg);
}

LRESULT APIUser32::DispatchMessageA (CONST MSG * lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "DispatchMessageA()");
  return DispatchMessageA_(lpMsg);
}

LRESULT APIUser32::DispatchMessageW (CONST MSG * lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "DispatchMessageW()");
  return DispatchMessageW_(lpMsg);
}

WINBOOL APIUser32::SetMessageQueue (int cMessagesMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMessageQueue()");
  return SetMessageQueue_(cMessagesMax);
}

WINBOOL APIUser32::PeekMessageA (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "PeekMessageA()");
  return PeekMessageA_(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

WINBOOL APIUser32::PeekMessageW (LPMSG lpMsg, HWND hWnd, UINT wMsgFilterMin, UINT wMsgFilterMax, UINT wRemoveMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "PeekMessageW()");
  return PeekMessageW_(lpMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg);
}

WINBOOL APIUser32::RegisterHotKey (HWND hWnd, int id, UINT fsModifiers, UINT vk)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterHotKey()");
  return RegisterHotKey_(hWnd, id, fsModifiers, vk);
}

WINBOOL APIUser32::UnregisterHotKey (HWND hWnd, int id)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterHotKey()");
  return UnregisterHotKey_(hWnd, id);
}

WINBOOL APIUser32::ExitWindowsEx (UINT uFlags, DWORD dwReason)
{
  logging::log("wrapper", logging::LogLevel::debug, "ExitWindowsEx()");
  return ExitWindowsEx_(uFlags, dwReason);
}

WINBOOL APIUser32::SwapMouseButton (WINBOOL fSwap)
{
  logging::log("wrapper", logging::LogLevel::debug, "SwapMouseButton()");
  return SwapMouseButton_(fSwap);
}

DWORD APIUser32::GetMessagePos (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMessagePos()");
  return GetMessagePos_();
}

LONG APIUser32::GetMessageTime (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMessageTime()");
  return GetMessageTime_();
}

LPARAM APIUser32::GetMessageExtraInfo (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMessageExtraInfo()");
  return GetMessageExtraInfo_();
}

DWORD APIUser32::GetUnpredictedMessagePos (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUnpredictedMessagePos()");
  return GetUnpredictedMessagePos_();
}

WINBOOL APIUser32::IsWow64Message (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWow64Message()");
  return IsWow64Message_();
}

LPARAM APIUser32::SetMessageExtraInfo (LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMessageExtraInfo()");
  return SetMessageExtraInfo_(lParam);
}

LRESULT APIUser32::SendMessageA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageA()");
  return SendMessageA_(hWnd, Msg, wParam, lParam);
}

LRESULT APIUser32::SendMessageW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageW()");
  return SendMessageW_(hWnd, Msg, wParam, lParam);
}

LRESULT APIUser32::SendMessageTimeoutA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageTimeoutA()");
  return SendMessageTimeoutA_(hWnd, Msg, wParam, lParam, fuFlags, uTimeout, lpdwResult);
}

LRESULT APIUser32::SendMessageTimeoutW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, UINT fuFlags, UINT uTimeout, PDWORD_PTR lpdwResult)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageTimeoutW()");
  return SendMessageTimeoutW_(hWnd, Msg, wParam, lParam, fuFlags, uTimeout, lpdwResult);
}

WINBOOL APIUser32::SendNotifyMessageA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendNotifyMessageA()");
  return SendNotifyMessageA_(hWnd, Msg, wParam, lParam);
}

WINBOOL APIUser32::SendNotifyMessageW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendNotifyMessageW()");
  return SendNotifyMessageW_(hWnd, Msg, wParam, lParam);
}

WINBOOL APIUser32::SendMessageCallbackA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, SENDASYNCPROC lpResultCallBack, ULONG_PTR dwData)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageCallbackA()");
  return SendMessageCallbackA_(hWnd, Msg, wParam, lParam, lpResultCallBack, dwData);
}

WINBOOL APIUser32::SendMessageCallbackW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam, SENDASYNCPROC lpResultCallBack, ULONG_PTR dwData)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendMessageCallbackW()");
  return SendMessageCallbackW_(hWnd, Msg, wParam, lParam, lpResultCallBack, dwData);
}

LONG APIUser32::BroadcastSystemMessageExA (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam, PBSMINFO pbsmInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "BroadcastSystemMessageExA()");
  return BroadcastSystemMessageExA_(flags, lpInfo, Msg, wParam, lParam, pbsmInfo);
}

LONG APIUser32::BroadcastSystemMessageExW (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam, PBSMINFO pbsmInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "BroadcastSystemMessageExW()");
  return BroadcastSystemMessageExW_(flags, lpInfo, Msg, wParam, lParam, pbsmInfo);
}

LONG APIUser32::BroadcastSystemMessageA (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "BroadcastSystemMessageA()");
  return BroadcastSystemMessageA_(flags, lpInfo, Msg, wParam, lParam);
}

LONG APIUser32::BroadcastSystemMessageW (DWORD flags, LPDWORD lpInfo, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "BroadcastSystemMessageW()");
  return BroadcastSystemMessageW_(flags, lpInfo, Msg, wParam, lParam);
}

HPOWERNOTIFY APIUser32::RegisterPowerSettingNotification (HANDLE hRecipient, LPCGUID PowerSettingGuid, DWORD Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterPowerSettingNotification()");
  return RegisterPowerSettingNotification_(hRecipient, PowerSettingGuid, Flags);
}

WINBOOL APIUser32::UnregisterPowerSettingNotification (HPOWERNOTIFY Handle)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterPowerSettingNotification()");
  return UnregisterPowerSettingNotification_(Handle);
}

HPOWERNOTIFY APIUser32::RegisterSuspendResumeNotification (HANDLE hRecipient, DWORD Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterSuspendResumeNotification()");
  return RegisterSuspendResumeNotification_(hRecipient, Flags);
}

WINBOOL APIUser32::UnregisterSuspendResumeNotification (HPOWERNOTIFY Handle)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterSuspendResumeNotification()");
  return UnregisterSuspendResumeNotification_(Handle);
}

WINBOOL APIUser32::PostMessageA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "PostMessageA()");
  return PostMessageA_(hWnd, Msg, wParam, lParam);
}

WINBOOL APIUser32::PostMessageW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "PostMessageW()");
  return PostMessageW_(hWnd, Msg, wParam, lParam);
}

WINBOOL APIUser32::PostThreadMessageA (DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "PostThreadMessageA()");
  return PostThreadMessageA_(idThread, Msg, wParam, lParam);
}

WINBOOL APIUser32::PostThreadMessageW (DWORD idThread, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "PostThreadMessageW()");
  return PostThreadMessageW_(idThread, Msg, wParam, lParam);
}

WINBOOL APIUser32::AttachThreadInput (DWORD idAttach, DWORD idAttachTo, WINBOOL fAttach)
{
  logging::log("wrapper", logging::LogLevel::debug, "AttachThreadInput()");
  return AttachThreadInput_(idAttach, idAttachTo, fAttach);
}

WINBOOL APIUser32::ReplyMessage (LRESULT lResult)
{
  logging::log("wrapper", logging::LogLevel::debug, "ReplyMessage()");
  return ReplyMessage_(lResult);
}

WINBOOL APIUser32::WaitMessage (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "WaitMessage()");
  return WaitMessage_();
}

DWORD APIUser32::WaitForInputIdle (HANDLE hProcess, DWORD dwMilliseconds)
{
  logging::log("wrapper", logging::LogLevel::debug, "WaitForInputIdle()");
  return WaitForInputIdle_(hProcess, dwMilliseconds);
}

LRESULT APIUser32::DefWindowProcA (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefWindowProcA()");
  return DefWindowProcA_(hWnd, Msg, wParam, lParam);
}

LRESULT APIUser32::DefWindowProcW (HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefWindowProcW()");
  return DefWindowProcW_(hWnd, Msg, wParam, lParam);
}

VOID APIUser32::PostQuitMessage (int nExitCode)
{
  logging::log("wrapper", logging::LogLevel::debug, "PostQuitMessage()");
  PostQuitMessage_(nExitCode);
}

WINBOOL APIUser32::InSendMessage (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "InSendMessage()");
  return InSendMessage_();
}

DWORD APIUser32::InSendMessageEx (LPVOID lpReserved)
{
  logging::log("wrapper", logging::LogLevel::debug, "InSendMessageEx()");
  return InSendMessageEx_(lpReserved);
}

UINT APIUser32::GetDoubleClickTime (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDoubleClickTime()");
  return GetDoubleClickTime_();
}

WINBOOL APIUser32::SetDoubleClickTime (UINT arg0)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDoubleClickTime()");
  return SetDoubleClickTime_(arg0);
}

ATOM APIUser32::RegisterClassA (CONST WNDCLASSA * lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClassA()");
  return RegisterClassA_(lpWndClass);
}

ATOM APIUser32::RegisterClassW (CONST WNDCLASSW * lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClassW()");
  return RegisterClassW_(lpWndClass);
}

WINBOOL APIUser32::UnregisterClassA (LPCSTR lpClassName, HINSTANCE hInstance)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterClassA()");
  return UnregisterClassA_(lpClassName, hInstance);
}

WINBOOL APIUser32::UnregisterClassW (LPCWSTR lpClassName, HINSTANCE hInstance)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterClassW()");
  return UnregisterClassW_(lpClassName, hInstance);
}

WINBOOL APIUser32::GetClassInfoA (HINSTANCE hInstance, LPCSTR lpClassName, LPWNDCLASSA lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassInfoA()");
  return GetClassInfoA_(hInstance, lpClassName, lpWndClass);
}

WINBOOL APIUser32::GetClassInfoW (HINSTANCE hInstance, LPCWSTR lpClassName, LPWNDCLASSW lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassInfoW()");
  return GetClassInfoW_(hInstance, lpClassName, lpWndClass);
}

ATOM APIUser32::RegisterClassExA (CONST WNDCLASSEXA * lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClassExA()");
  return RegisterClassExA_(lpWndClass);
}

ATOM APIUser32::RegisterClassExW (CONST WNDCLASSEXW * lpWndClass)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClassExW()");
  return RegisterClassExW_(lpWndClass);
}

WINBOOL APIUser32::GetClassInfoExA (HINSTANCE hInstance, LPCSTR lpszClass, LPWNDCLASSEXA lpwcx)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassInfoExA()");
  return GetClassInfoExA_(hInstance, lpszClass, lpwcx);
}

WINBOOL APIUser32::GetClassInfoExW (HINSTANCE hInstance, LPCWSTR lpszClass, LPWNDCLASSEXW lpwcx)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassInfoExW()");
  return GetClassInfoExW_(hInstance, lpszClass, lpwcx);
}

#ifdef STRICT
LRESULT APIUser32::CallWindowProcA (WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallWindowProcA()");
  return CallWindowProcA_(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

LRESULT APIUser32::CallWindowProcW (WNDPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallWindowProcW()");
  return CallWindowProcW_(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

#else

LRESULT APIUser32::CallWindowProcA (FARPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallWindowProcA()");
  return CallWindowProcA_(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

LRESULT APIUser32::CallWindowProcW (FARPROC lpPrevWndFunc, HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallWindowProcW()");
  return CallWindowProcW_(lpPrevWndFunc, hWnd, Msg, wParam, lParam);
}

#endif

HDEVNOTIFY APIUser32::RegisterDeviceNotificationA (HANDLE hRecipient, LPVOID NotificationFilter, DWORD Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterDeviceNotificationA()");
  return RegisterDeviceNotificationA_(hRecipient, NotificationFilter, Flags);
}

HDEVNOTIFY APIUser32::RegisterDeviceNotificationW (HANDLE hRecipient, LPVOID NotificationFilter, DWORD Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterDeviceNotificationW()");
  return RegisterDeviceNotificationW_(hRecipient, NotificationFilter, Flags);
}

WINBOOL APIUser32::UnregisterDeviceNotification (HDEVNOTIFY Handle)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterDeviceNotification()");
  return UnregisterDeviceNotification_(Handle);
}

HWND APIUser32::CreateWindowExA (DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateWindowExA()");
  return CreateWindowExA_(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

HWND APIUser32::CreateWindowExW (DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateWindowExW()");
  return CreateWindowExW_(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

WINBOOL APIUser32::IsWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWindow()");
  return IsWindow_(hWnd);
}

WINBOOL APIUser32::IsMenu (HMENU hMenu)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsMenu()");
  return IsMenu_(hMenu);
}

WINBOOL APIUser32::IsChild (HWND hWndParent, HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsChild()");
  return IsChild_(hWndParent, hWnd);
}

WINBOOL APIUser32::DestroyWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyWindow()");
  return DestroyWindow_(hWnd);
}

WINBOOL APIUser32::ShowWindow (HWND hWnd, int nCmdShow)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowWindow()");
  return ShowWindow_(hWnd, nCmdShow);
}

WINBOOL APIUser32::AnimateWindow (HWND hWnd, DWORD dwTime, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "AnimateWindow()");
  return AnimateWindow_(hWnd, dwTime, dwFlags);
}

WINBOOL APIUser32::UpdateLayeredWindow (HWND hWnd, HDC hdcDst, POINT * pptDst, SIZE * psize, HDC hdcSrc, POINT * pptSrc, COLORREF crKey, BLENDFUNCTION * pblend, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "UpdateLayeredWindow()");
  return UpdateLayeredWindow_(hWnd, hdcDst, pptDst, psize, hdcSrc, pptSrc, crKey, pblend, dwFlags);
}

WINBOOL APIUser32::UpdateLayeredWindowIndirect (HWND hWnd, const UPDATELAYEREDWINDOWINFO * pULWInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "UpdateLayeredWindowIndirect()");
  return UpdateLayeredWindowIndirect_(hWnd, pULWInfo);
}

WINBOOL APIUser32::GetLayeredWindowAttributes (HWND hwnd, COLORREF * pcrKey, BYTE * pbAlpha, DWORD * pdwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetLayeredWindowAttributes()");
  return GetLayeredWindowAttributes_(hwnd, pcrKey, pbAlpha, pdwFlags);
}

WINBOOL APIUser32::PrintWindow (HWND hwnd, HDC hdcBlt, UINT nFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "PrintWindow()");
  return PrintWindow_(hwnd, hdcBlt, nFlags);
}

WINBOOL APIUser32::SetLayeredWindowAttributes (HWND hwnd, COLORREF crKey, BYTE bAlpha, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetLayeredWindowAttributes()");
  return SetLayeredWindowAttributes_(hwnd, crKey, bAlpha, dwFlags);
}

WINBOOL APIUser32::ShowWindowAsync (HWND hWnd, int nCmdShow)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowWindowAsync()");
  return ShowWindowAsync_(hWnd, nCmdShow);
}

WINBOOL APIUser32::FlashWindow (HWND hWnd, WINBOOL bInvert)
{
  logging::log("wrapper", logging::LogLevel::debug, "FlashWindow()");
  return FlashWindow_(hWnd, bInvert);
}

WINBOOL APIUser32::FlashWindowEx (PFLASHWINFO pfwi)
{
  logging::log("wrapper", logging::LogLevel::debug, "FlashWindowEx()");
  return FlashWindowEx_(pfwi);
}

WINBOOL APIUser32::ShowOwnedPopups (HWND hWnd, WINBOOL fShow)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowOwnedPopups()");
  return ShowOwnedPopups_(hWnd, fShow);
}

WINBOOL APIUser32::OpenIcon (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenIcon()");
  return OpenIcon_(hWnd);
}

WINBOOL APIUser32::CloseWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseWindow()");
  return CloseWindow_(hWnd);
}

WINBOOL APIUser32::MoveWindow (HWND hWnd, int X, int Y, int nWidth, int nHeight, WINBOOL bRepaint)
{
  logging::log("wrapper", logging::LogLevel::debug, "MoveWindow()");
  return MoveWindow_(hWnd, X, Y, nWidth, nHeight, bRepaint);
}

WINBOOL APIUser32::SetWindowPos (HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowPos()");
  return SetWindowPos_(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}

WINBOOL APIUser32::GetWindowPlacement (HWND hWnd, WINDOWPLACEMENT * lpwndpl)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowPlacement()");
  return GetWindowPlacement_(hWnd, lpwndpl);
}

WINBOOL APIUser32::SetWindowPlacement (HWND hWnd, CONST WINDOWPLACEMENT * lpwndpl)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowPlacement()");
  return SetWindowPlacement_(hWnd, lpwndpl);
}

WINBOOL APIUser32::GetWindowDisplayAffinity (HWND hWnd, DWORD * pdwAffinity)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowDisplayAffinity()");
  return GetWindowDisplayAffinity_(hWnd, pdwAffinity);
}

WINBOOL APIUser32::SetWindowDisplayAffinity (HWND hWnd, DWORD dwAffinity)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowDisplayAffinity()");
  return SetWindowDisplayAffinity_(hWnd, dwAffinity);
}

HDWP APIUser32::BeginDeferWindowPos (int nNumWindows)
{
  logging::log("wrapper", logging::LogLevel::debug, "BeginDeferWindowPos()");
  return BeginDeferWindowPos_(nNumWindows);
}

HDWP APIUser32::DeferWindowPos (HDWP hWinPosInfo, HWND hWnd, HWND hWndInsertAfter, int x, int y, int cx, int cy, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DeferWindowPos()");
  return DeferWindowPos_(hWinPosInfo, hWnd, hWndInsertAfter, x, y, cx, cy, uFlags);
}

WINBOOL APIUser32::EndDeferWindowPos (HDWP hWinPosInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "EndDeferWindowPos()");
  return EndDeferWindowPos_(hWinPosInfo);
}

WINBOOL APIUser32::IsWindowVisible (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWindowVisible()");
  return IsWindowVisible_(hWnd);
}

WINBOOL APIUser32::IsIconic (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsIconic()");
  return IsIconic_(hWnd);
}

WINBOOL APIUser32::AnyPopup (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "AnyPopup()");
  return AnyPopup_();
}

WINBOOL APIUser32::BringWindowToTop (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "BringWindowToTop()");
  return BringWindowToTop_(hWnd);
}

WINBOOL APIUser32::IsZoomed (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsZoomed()");
  return IsZoomed_(hWnd);
}

HWND APIUser32::CreateDialogParamA (HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDialogParamA()");
  return CreateDialogParamA_(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

HWND APIUser32::CreateDialogParamW (HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDialogParamW()");
  return CreateDialogParamW_(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

HWND APIUser32::CreateDialogIndirectParamA (HINSTANCE hInstance, LPCDLGTEMPLATEA lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDialogIndirectParamA()");
  return CreateDialogIndirectParamA_(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

HWND APIUser32::CreateDialogIndirectParamW (HINSTANCE hInstance, LPCDLGTEMPLATEW lpTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateDialogIndirectParamW()");
  return CreateDialogIndirectParamW_(hInstance, lpTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

INT_PTR APIUser32::DialogBoxParamA (HINSTANCE hInstance, LPCSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DialogBoxParamA()");
  return DialogBoxParamA_(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

INT_PTR APIUser32::DialogBoxParamW (HINSTANCE hInstance, LPCWSTR lpTemplateName, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DialogBoxParamW()");
  return DialogBoxParamW_(hInstance, lpTemplateName, hWndParent, lpDialogFunc, dwInitParam);
}

INT_PTR APIUser32::DialogBoxIndirectParamA (HINSTANCE hInstance, LPCDLGTEMPLATEA hDialogTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DialogBoxIndirectParamA()");
  return DialogBoxIndirectParamA_(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

INT_PTR APIUser32::DialogBoxIndirectParamW (HINSTANCE hInstance, LPCDLGTEMPLATEW hDialogTemplate, HWND hWndParent, DLGPROC lpDialogFunc, LPARAM dwInitParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DialogBoxIndirectParamW()");
  return DialogBoxIndirectParamW_(hInstance, hDialogTemplate, hWndParent, lpDialogFunc, dwInitParam);
}

WINBOOL APIUser32::EndDialog (HWND hDlg, INT_PTR nResult)
{
  logging::log("wrapper", logging::LogLevel::debug, "EndDialog()");
  return EndDialog_(hDlg, nResult);
}

HWND APIUser32::GetDlgItem (HWND hDlg, int nIDDlgItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDlgItem()");
  return GetDlgItem_(hDlg, nIDDlgItem);
}

WINBOOL APIUser32::SetDlgItemInt (HWND hDlg, int nIDDlgItem, UINT uValue, WINBOOL bSigned)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDlgItemInt()");
  return SetDlgItemInt_(hDlg, nIDDlgItem, uValue, bSigned);
}

UINT APIUser32::GetDlgItemInt (HWND hDlg, int nIDDlgItem, WINBOOL * lpTranslated, WINBOOL bSigned)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDlgItemInt()");
  return GetDlgItemInt_(hDlg, nIDDlgItem, lpTranslated, bSigned);
}

WINBOOL APIUser32::SetDlgItemTextA (HWND hDlg, int nIDDlgItem, LPCSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDlgItemTextA()");
  return SetDlgItemTextA_(hDlg, nIDDlgItem, lpString);
}

WINBOOL APIUser32::SetDlgItemTextW (HWND hDlg, int nIDDlgItem, LPCWSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDlgItemTextW()");
  return SetDlgItemTextW_(hDlg, nIDDlgItem, lpString);
}

UINT APIUser32::GetDlgItemTextA (HWND hDlg, int nIDDlgItem, LPSTR lpString, int cchMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDlgItemTextA()");
  return GetDlgItemTextA_(hDlg, nIDDlgItem, lpString, cchMax);
}

UINT APIUser32::GetDlgItemTextW (HWND hDlg, int nIDDlgItem, LPWSTR lpString, int cchMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDlgItemTextW()");
  return GetDlgItemTextW_(hDlg, nIDDlgItem, lpString, cchMax);
}

WINBOOL APIUser32::CheckDlgButton (HWND hDlg, int nIDButton, UINT uCheck)
{
  logging::log("wrapper", logging::LogLevel::debug, "CheckDlgButton()");
  return CheckDlgButton_(hDlg, nIDButton, uCheck);
}

WINBOOL APIUser32::CheckRadioButton (HWND hDlg, int nIDFirstButton, int nIDLastButton, int nIDCheckButton)
{
  logging::log("wrapper", logging::LogLevel::debug, "CheckRadioButton()");
  return CheckRadioButton_(hDlg, nIDFirstButton, nIDLastButton, nIDCheckButton);
}

UINT APIUser32::IsDlgButtonChecked (HWND hDlg, int nIDButton)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsDlgButtonChecked()");
  return IsDlgButtonChecked_(hDlg, nIDButton);
}

LRESULT APIUser32::SendDlgItemMessageA (HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendDlgItemMessageA()");
  return SendDlgItemMessageA_(hDlg, nIDDlgItem, Msg, wParam, lParam);
}

LRESULT APIUser32::SendDlgItemMessageW (HWND hDlg, int nIDDlgItem, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendDlgItemMessageW()");
  return SendDlgItemMessageW_(hDlg, nIDDlgItem, Msg, wParam, lParam);
}

HWND APIUser32::GetNextDlgGroupItem (HWND hDlg, HWND hCtl, WINBOOL bPrevious)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetNextDlgGroupItem()");
  return GetNextDlgGroupItem_(hDlg, hCtl, bPrevious);
}

HWND APIUser32::GetNextDlgTabItem (HWND hDlg, HWND hCtl, WINBOOL bPrevious)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetNextDlgTabItem()");
  return GetNextDlgTabItem_(hDlg, hCtl, bPrevious);
}

int APIUser32::GetDlgCtrlID (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDlgCtrlID()");
  return GetDlgCtrlID_(hWnd);
}

LONG APIUser32::GetDialogBaseUnits (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDialogBaseUnits()");
  return GetDialogBaseUnits_();
}

LRESULT APIUser32::DefDlgProcA (HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefDlgProcA()");
  return DefDlgProcA_(hDlg, Msg, wParam, lParam);
}

LRESULT APIUser32::DefDlgProcW (HWND hDlg, UINT Msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefDlgProcW()");
  return DefDlgProcW_(hDlg, Msg, wParam, lParam);
}

WINBOOL APIUser32::CallMsgFilterA (LPMSG lpMsg, int nCode)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallMsgFilterA()");
  return CallMsgFilterA_(lpMsg, nCode);
}

WINBOOL APIUser32::CallMsgFilterW (LPMSG lpMsg, int nCode)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallMsgFilterW()");
  return CallMsgFilterW_(lpMsg, nCode);
}

WINBOOL APIUser32::OpenClipboard (HWND hWndNewOwner)
{
  logging::log("wrapper", logging::LogLevel::debug, "OpenClipboard()");
  return OpenClipboard_(hWndNewOwner);
}

WINBOOL APIUser32::CloseClipboard (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseClipboard()");
  return CloseClipboard_();
}

DWORD APIUser32::GetClipboardSequenceNumber (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardSequenceNumber()");
  return GetClipboardSequenceNumber_();
}

HWND APIUser32::GetClipboardOwner (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardOwner()");
  return GetClipboardOwner_();
}

HWND APIUser32::SetClipboardViewer (HWND hWndNewViewer)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClipboardViewer()");
  return SetClipboardViewer_(hWndNewViewer);
}

HWND APIUser32::GetClipboardViewer (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardViewer()");
  return GetClipboardViewer_();
}

WINBOOL APIUser32::ChangeClipboardChain (HWND hWndRemove, HWND hWndNewNext)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeClipboardChain()");
  return ChangeClipboardChain_(hWndRemove, hWndNewNext);
}

HANDLE APIUser32::SetClipboardData (UINT uFormat, HANDLE hMem)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClipboardData()");
  return SetClipboardData_(uFormat, hMem);
}

HANDLE APIUser32::GetClipboardData (UINT uFormat)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardData()");
  return GetClipboardData_(uFormat);
}

UINT APIUser32::RegisterClipboardFormatA (LPCSTR lpszFormat)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClipboardFormatA()");
  return RegisterClipboardFormatA_(lpszFormat);
}

UINT APIUser32::RegisterClipboardFormatW (LPCWSTR lpszFormat)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterClipboardFormatW()");
  return RegisterClipboardFormatW_(lpszFormat);
}

int APIUser32::CountClipboardFormats (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "CountClipboardFormats()");
  return CountClipboardFormats_();
}

UINT APIUser32::EnumClipboardFormats (UINT format)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumClipboardFormats()");
  return EnumClipboardFormats_(format);
}

int APIUser32::GetClipboardFormatNameA (UINT format, LPSTR lpszFormatName, int cchMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardFormatNameA()");
  return GetClipboardFormatNameA_(format, lpszFormatName, cchMaxCount);
}

int APIUser32::GetClipboardFormatNameW (UINT format, LPWSTR lpszFormatName, int cchMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipboardFormatNameW()");
  return GetClipboardFormatNameW_(format, lpszFormatName, cchMaxCount);
}

WINBOOL APIUser32::EmptyClipboard (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "EmptyClipboard()");
  return EmptyClipboard_();
}

WINBOOL APIUser32::IsClipboardFormatAvailable (UINT format)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsClipboardFormatAvailable()");
  return IsClipboardFormatAvailable_(format);
}

int APIUser32::GetPriorityClipboardFormat (UINT * paFormatPriorityList, int cFormats)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPriorityClipboardFormat()");
  return GetPriorityClipboardFormat_(paFormatPriorityList, cFormats);
}

HWND APIUser32::GetOpenClipboardWindow (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetOpenClipboardWindow()");
  return GetOpenClipboardWindow_();
}

WINBOOL APIUser32::AddClipboardFormatListener (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "AddClipboardFormatListener()");
  return AddClipboardFormatListener_(hwnd);
}

WINBOOL APIUser32::RemoveClipboardFormatListener (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "RemoveClipboardFormatListener()");
  return RemoveClipboardFormatListener_(hwnd);
}

WINBOOL APIUser32::GetUpdatedClipboardFormats (PUINT lpuiFormats, UINT cFormats, PUINT pcFormatsOut)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUpdatedClipboardFormats()");
  return GetUpdatedClipboardFormats_(lpuiFormats, cFormats, pcFormatsOut);
}

WINBOOL APIUser32::CharToOemA (LPCSTR lpszSrc, LPSTR lpszDst)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharToOemA()");
  return CharToOemA_(lpszSrc, lpszDst);
}

WINBOOL APIUser32::CharToOemW (LPCWSTR lpszSrc, LPSTR lpszDst)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharToOemW()");
  return CharToOemW_(lpszSrc, lpszDst);
}

WINBOOL APIUser32::OemToCharA (LPCSTR lpszSrc, LPSTR lpszDst)
{
  logging::log("wrapper", logging::LogLevel::debug, "OemToCharA()");
  return OemToCharA_(lpszSrc, lpszDst);
}

WINBOOL APIUser32::OemToCharW (LPCSTR lpszSrc, LPWSTR lpszDst)
{
  logging::log("wrapper", logging::LogLevel::debug, "OemToCharW()");
  return OemToCharW_(lpszSrc, lpszDst);
}

WINBOOL APIUser32::CharToOemBuffA (LPCSTR lpszSrc, LPSTR lpszDst, DWORD cchDstLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharToOemBuffA()");
  return CharToOemBuffA_(lpszSrc, lpszDst, cchDstLength);
}

WINBOOL APIUser32::CharToOemBuffW (LPCWSTR lpszSrc, LPSTR lpszDst, DWORD cchDstLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharToOemBuffW()");
  return CharToOemBuffW_(lpszSrc, lpszDst, cchDstLength);
}

WINBOOL APIUser32::OemToCharBuffA (LPCSTR lpszSrc, LPSTR lpszDst, DWORD cchDstLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "OemToCharBuffA()");
  return OemToCharBuffA_(lpszSrc, lpszDst, cchDstLength);
}

WINBOOL APIUser32::OemToCharBuffW (LPCSTR lpszSrc, LPWSTR lpszDst, DWORD cchDstLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "OemToCharBuffW()");
  return OemToCharBuffW_(lpszSrc, lpszDst, cchDstLength);
}

LPSTR APIUser32::CharUpperA (LPSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharUpperA()");
  return CharUpperA_(lpsz);
}

LPWSTR APIUser32::CharUpperW (LPWSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharUpperW()");
  return CharUpperW_(lpsz);
}

DWORD APIUser32::CharUpperBuffA (LPSTR lpsz, DWORD cchLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharUpperBuffA()");
  return CharUpperBuffA_(lpsz, cchLength);
}

DWORD APIUser32::CharUpperBuffW (LPWSTR lpsz, DWORD cchLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharUpperBuffW()");
  return CharUpperBuffW_(lpsz, cchLength);
}

LPSTR APIUser32::CharLowerA (LPSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharLowerA()");
  return CharLowerA_(lpsz);
}

LPWSTR APIUser32::CharLowerW (LPWSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharLowerW()");
  return CharLowerW_(lpsz);
}

DWORD APIUser32::CharLowerBuffA (LPSTR lpsz, DWORD cchLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharLowerBuffA()");
  return CharLowerBuffA_(lpsz, cchLength);
}

DWORD APIUser32::CharLowerBuffW (LPWSTR lpsz, DWORD cchLength)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharLowerBuffW()");
  return CharLowerBuffW_(lpsz, cchLength);
}

LPSTR APIUser32::CharNextA (LPCSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharNextA()");
  return CharNextA_(lpsz);
}

LPWSTR APIUser32::CharNextW (LPCWSTR lpsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharNextW()");
  return CharNextW_(lpsz);
}

LPSTR APIUser32::CharPrevA (LPCSTR lpszStart, LPCSTR lpszCurrent)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharPrevA()");
  return CharPrevA_(lpszStart, lpszCurrent);
}

LPWSTR APIUser32::CharPrevW (LPCWSTR lpszStart, LPCWSTR lpszCurrent)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharPrevW()");
  return CharPrevW_(lpszStart, lpszCurrent);
}

LPSTR APIUser32::CharNextExA (WORD CodePage, LPCSTR lpCurrentChar, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharNextExA()");
  return CharNextExA_(CodePage, lpCurrentChar, dwFlags);
}

LPSTR APIUser32::CharPrevExA (WORD CodePage, LPCSTR lpStart, LPCSTR lpCurrentChar, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharPrevExA()");
  return CharPrevExA_(CodePage, lpStart, lpCurrentChar, dwFlags);
}

WINBOOL APIUser32::IsCharAlphaA (CHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharAlphaA()");
  return IsCharAlphaA_(ch);
}

WINBOOL APIUser32::IsCharAlphaW (WCHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharAlphaW()");
  return IsCharAlphaW_(ch);
}

WINBOOL APIUser32::IsCharAlphaNumericA (CHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharAlphaNumericA()");
  return IsCharAlphaNumericA_(ch);
}

WINBOOL APIUser32::IsCharAlphaNumericW (WCHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharAlphaNumericW()");
  return IsCharAlphaNumericW_(ch);
}

WINBOOL APIUser32::IsCharUpperA (CHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharUpperA()");
  return IsCharUpperA_(ch);
}

WINBOOL APIUser32::IsCharUpperW (WCHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharUpperW()");
  return IsCharUpperW_(ch);
}

WINBOOL APIUser32::IsCharLowerA (CHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharLowerA()");
  return IsCharLowerA_(ch);
}

WINBOOL APIUser32::IsCharLowerW (WCHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsCharLowerW()");
  return IsCharLowerW_(ch);
}

HWND APIUser32::SetFocus (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetFocus()");
  return SetFocus_(hWnd);
}

HWND APIUser32::GetActiveWindow (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetActiveWindow()");
  return GetActiveWindow_();
}

HWND APIUser32::GetFocus (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetFocus()");
  return GetFocus_();
}

UINT APIUser32::GetKBCodePage (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKBCodePage()");
  return GetKBCodePage_();
}

SHORT APIUser32::GetKeyState (int nVirtKey)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyState()");
  return GetKeyState_(nVirtKey);
}

SHORT APIUser32::GetAsyncKeyState (int vKey)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAsyncKeyState()");
  return GetAsyncKeyState_(vKey);
}

WINBOOL APIUser32::GetKeyboardState (PBYTE lpKeyState)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardState()");
  return GetKeyboardState_(lpKeyState);
}

WINBOOL APIUser32::SetKeyboardState (LPBYTE lpKeyState)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetKeyboardState()");
  return SetKeyboardState_(lpKeyState);
}

int APIUser32::GetKeyNameTextA (LONG lParam, LPSTR lpString, int cchSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyNameTextA()");
  return GetKeyNameTextA_(lParam, lpString, cchSize);
}

int APIUser32::GetKeyNameTextW (LONG lParam, LPWSTR lpString, int cchSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyNameTextW()");
  return GetKeyNameTextW_(lParam, lpString, cchSize);
}

int APIUser32::GetKeyboardType (int nTypeFlag)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetKeyboardType()");
  return GetKeyboardType_(nTypeFlag);
}

int APIUser32::ToAscii (UINT uVirtKey, UINT uScanCode, CONST BYTE * lpKeyState, LPWORD lpChar, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ToAscii()");
  return ToAscii_(uVirtKey, uScanCode, lpKeyState, lpChar, uFlags);
}

int APIUser32::ToAsciiEx (UINT uVirtKey, UINT uScanCode, CONST BYTE * lpKeyState, LPWORD lpChar, UINT uFlags, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "ToAsciiEx()");
  return ToAsciiEx_(uVirtKey, uScanCode, lpKeyState, lpChar, uFlags, dwhkl);
}

int APIUser32::ToUnicode (UINT wVirtKey, UINT wScanCode, CONST BYTE * lpKeyState, LPWSTR pwszBuff, int cchBuff, UINT wFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ToUnicode()");
  return ToUnicode_(wVirtKey, wScanCode, lpKeyState, pwszBuff, cchBuff, wFlags);
}

DWORD APIUser32::OemKeyScan (WORD wOemChar)
{
  logging::log("wrapper", logging::LogLevel::debug, "OemKeyScan()");
  return OemKeyScan_(wOemChar);
}

SHORT APIUser32::VkKeyScanA (CHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "VkKeyScanA()");
  return VkKeyScanA_(ch);
}

SHORT APIUser32::VkKeyScanW (WCHAR ch)
{
  logging::log("wrapper", logging::LogLevel::debug, "VkKeyScanW()");
  return VkKeyScanW_(ch);
}

SHORT APIUser32::VkKeyScanExA (CHAR ch, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "VkKeyScanExA()");
  return VkKeyScanExA_(ch, dwhkl);
}

SHORT APIUser32::VkKeyScanExW (WCHAR ch, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "VkKeyScanExW()");
  return VkKeyScanExW_(ch, dwhkl);
}

VOID APIUser32::keybd_event (BYTE bVk, BYTE bScan, DWORD dwFlags, ULONG_PTR dwExtraInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "keybd_event()");
  keybd_event_(bVk, bScan, dwFlags, dwExtraInfo);
}

VOID APIUser32::mouse_event (DWORD dwFlags, DWORD dx, DWORD dy, DWORD dwData, ULONG_PTR dwExtraInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "mouse_event()");
  mouse_event_(dwFlags, dx, dy, dwData, dwExtraInfo);
}

UINT APIUser32::SendInput (UINT cInputs, LPINPUT pInputs, int cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendInput()");
  return SendInput_(cInputs, pInputs, cbSize);
}

WINBOOL APIUser32::GetTouchInputInfo (HTOUCHINPUT hTouchInput, UINT cInputs, PTOUCHINPUT pInputs, int cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTouchInputInfo()");
  return GetTouchInputInfo_(hTouchInput, cInputs, pInputs, cbSize);
}

WINBOOL APIUser32::CloseTouchInputHandle (HTOUCHINPUT hTouchInput)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseTouchInputHandle()");
  return CloseTouchInputHandle_(hTouchInput);
}

WINBOOL APIUser32::RegisterTouchWindow (HWND hwnd, ULONG ulFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterTouchWindow()");
  return RegisterTouchWindow_(hwnd, ulFlags);
}

WINBOOL APIUser32::UnregisterTouchWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterTouchWindow()");
  return UnregisterTouchWindow_(hwnd);
}

WINBOOL APIUser32::IsTouchWindow (HWND hwnd, PULONG pulFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsTouchWindow()");
  return IsTouchWindow_(hwnd, pulFlags);
}

WINBOOL APIUser32::InitializeTouchInjection (UINT32 maxCount, DWORD dwMode)
{
  logging::log("wrapper", logging::LogLevel::debug, "InitializeTouchInjection()");
  return InitializeTouchInjection_(maxCount, dwMode);
}

WINBOOL APIUser32::InjectTouchInput (UINT32 count, CONST POINTER_TOUCH_INFO * contacts)
{
  logging::log("wrapper", logging::LogLevel::debug, "InjectTouchInput()");
  return InjectTouchInput_(count, contacts);
}

WINBOOL APIUser32::GetPointerType (UINT32 pointerId, POINTER_INPUT_TYPE * pointerType)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerType()");
  return GetPointerType_(pointerId, pointerType);
}

WINBOOL APIUser32::GetPointerCursorId (UINT32 pointerId, UINT32 * cursorId)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerCursorId()");
  return GetPointerCursorId_(pointerId, cursorId);
}

WINBOOL APIUser32::GetPointerInfo (UINT32 pointerId, POINTER_INFO * pointerInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerInfo()");
  return GetPointerInfo_(pointerId, pointerInfo);
}

WINBOOL APIUser32::GetPointerInfoHistory (UINT32 pointerId, UINT32 * entriesCount, POINTER_INFO * pointerInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerInfoHistory()");
  return GetPointerInfoHistory_(pointerId, entriesCount, pointerInfo);
}

WINBOOL APIUser32::GetPointerFrameInfo (UINT32 pointerId, UINT32 * pointerCount, POINTER_INFO * pointerInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFrameInfo()");
  return GetPointerFrameInfo_(pointerId, pointerCount, pointerInfo);
}

WINBOOL APIUser32::GetPointerFrameInfoHistory (UINT32 pointerId, UINT32 * entriesCount, UINT32 * pointerCount, POINTER_INFO * pointerInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFrameInfoHistory()");
  return GetPointerFrameInfoHistory_(pointerId, entriesCount, pointerCount, pointerInfo);
}

WINBOOL APIUser32::GetPointerTouchInfo (UINT32 pointerId, POINTER_TOUCH_INFO * touchInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerTouchInfo()");
  return GetPointerTouchInfo_(pointerId, touchInfo);
}

WINBOOL APIUser32::GetPointerTouchInfoHistory (UINT32 pointerId, UINT32 * entriesCount, POINTER_TOUCH_INFO * touchInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerTouchInfoHistory()");
  return GetPointerTouchInfoHistory_(pointerId, entriesCount, touchInfo);
}

WINBOOL APIUser32::GetPointerFrameTouchInfo (UINT32 pointerId, UINT32 * pointerCount, POINTER_TOUCH_INFO * touchInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFrameTouchInfo()");
  return GetPointerFrameTouchInfo_(pointerId, pointerCount, touchInfo);
}

WINBOOL APIUser32::GetPointerFrameTouchInfoHistory (UINT32 pointerId, UINT32 * entriesCount, UINT32 * pointerCount, POINTER_TOUCH_INFO * touchInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFrameTouchInfoHistory()");
  return GetPointerFrameTouchInfoHistory_(pointerId, entriesCount, pointerCount, touchInfo);
}

WINBOOL APIUser32::GetPointerPenInfo (UINT32 pointerId, POINTER_PEN_INFO * penInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerPenInfo()");
  return GetPointerPenInfo_(pointerId, penInfo);
}

WINBOOL APIUser32::GetPointerPenInfoHistory (UINT32 pointerId, UINT32 * entriesCount, POINTER_PEN_INFO * penInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerPenInfoHistory()");
  return GetPointerPenInfoHistory_(pointerId, entriesCount, penInfo);
}

WINBOOL APIUser32::GetPointerFramePenInfo (UINT32 pointerId, UINT32 * pointerCount, POINTER_PEN_INFO * penInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFramePenInfo()");
  return GetPointerFramePenInfo_(pointerId, pointerCount, penInfo);
}

WINBOOL APIUser32::GetPointerFramePenInfoHistory (UINT32 pointerId, UINT32 * entriesCount, UINT32 * pointerCount, POINTER_PEN_INFO * penInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerFramePenInfoHistory()");
  return GetPointerFramePenInfoHistory_(pointerId, entriesCount, pointerCount, penInfo);
}

WINBOOL APIUser32::SkipPointerFrameMessages (UINT32 pointerId)
{
  logging::log("wrapper", logging::LogLevel::debug, "SkipPointerFrameMessages()");
  return SkipPointerFrameMessages_(pointerId);
}

WINBOOL APIUser32::RegisterPointerInputTarget (HWND hwnd, POINTER_INPUT_TYPE pointerType)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterPointerInputTarget()");
  return RegisterPointerInputTarget_(hwnd, pointerType);
}

WINBOOL APIUser32::UnregisterPointerInputTarget (HWND hwnd, POINTER_INPUT_TYPE pointerType)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterPointerInputTarget()");
  return UnregisterPointerInputTarget_(hwnd, pointerType);
}

WINBOOL APIUser32::EnableMouseInPointer (WINBOOL fEnable)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnableMouseInPointer()");
  return EnableMouseInPointer_(fEnable);
}

WINBOOL APIUser32::IsMouseInPointerEnabled (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsMouseInPointerEnabled()");
  return IsMouseInPointerEnabled_();
}

WINBOOL APIUser32::RegisterTouchHitTestingWindow (HWND hwnd, ULONG value)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterTouchHitTestingWindow()");
  return RegisterTouchHitTestingWindow_(hwnd, value);
}

WINBOOL APIUser32::EvaluateProximityToRect (const RECT * controlBoundingBox, const TOUCH_HIT_TESTING_INPUT * pHitTestingInput, TOUCH_HIT_TESTING_PROXIMITY_EVALUATION * pProximityEval)
{
  logging::log("wrapper", logging::LogLevel::debug, "EvaluateProximityToRect()");
  return EvaluateProximityToRect_(controlBoundingBox, pHitTestingInput, pProximityEval);
}

WINBOOL APIUser32::EvaluateProximityToPolygon (UINT32 numVertices, const POINT * controlPolygon, const TOUCH_HIT_TESTING_INPUT * pHitTestingInput, TOUCH_HIT_TESTING_PROXIMITY_EVALUATION * pProximityEval)
{
  logging::log("wrapper", logging::LogLevel::debug, "EvaluateProximityToPolygon()");
  return EvaluateProximityToPolygon_(numVertices, controlPolygon, pHitTestingInput, pProximityEval);
}

LRESULT APIUser32::PackTouchHitTestingProximityEvaluation (const TOUCH_HIT_TESTING_INPUT * pHitTestingInput, const TOUCH_HIT_TESTING_PROXIMITY_EVALUATION * pProximityEval)
{
  logging::log("wrapper", logging::LogLevel::debug, "PackTouchHitTestingProximityEvaluation()");
  return PackTouchHitTestingProximityEvaluation_(pHitTestingInput, pProximityEval);
}

WINBOOL APIUser32::GetWindowFeedbackSetting (HWND hwnd, FEEDBACK_TYPE feedback, DWORD dwFlags, UINT32 * pSize, VOID * config)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowFeedbackSetting()");
  return GetWindowFeedbackSetting_(hwnd, feedback, dwFlags, pSize, config);
}

WINBOOL APIUser32::SetWindowFeedbackSetting (HWND hwnd, FEEDBACK_TYPE feedback, DWORD dwFlags, UINT32 size, CONST VOID * configuration)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowFeedbackSetting()");
  return SetWindowFeedbackSetting_(hwnd, feedback, dwFlags, size, configuration);
}

WINBOOL APIUser32::GetLastInputInfo (PLASTINPUTINFO plii)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetLastInputInfo()");
  return GetLastInputInfo_(plii);
}

UINT APIUser32::MapVirtualKeyA (UINT uCode, UINT uMapType)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapVirtualKeyA()");
  return MapVirtualKeyA_(uCode, uMapType);
}

UINT APIUser32::MapVirtualKeyW (UINT uCode, UINT uMapType)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapVirtualKeyW()");
  return MapVirtualKeyW_(uCode, uMapType);
}

UINT APIUser32::MapVirtualKeyExA (UINT uCode, UINT uMapType, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapVirtualKeyExA()");
  return MapVirtualKeyExA_(uCode, uMapType, dwhkl);
}

UINT APIUser32::MapVirtualKeyExW (UINT uCode, UINT uMapType, HKL dwhkl)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapVirtualKeyExW()");
  return MapVirtualKeyExW_(uCode, uMapType, dwhkl);
}

WINBOOL APIUser32::GetInputState (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetInputState()");
  return GetInputState_();
}

DWORD APIUser32::GetQueueStatus (UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetQueueStatus()");
  return GetQueueStatus_(flags);
}

HWND APIUser32::GetCapture (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCapture()");
  return GetCapture_();
}

HWND APIUser32::SetCapture (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCapture()");
  return SetCapture_(hWnd);
}

WINBOOL APIUser32::ReleaseCapture (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "ReleaseCapture()");
  return ReleaseCapture_();
}

DWORD APIUser32::MsgWaitForMultipleObjects (DWORD nCount, CONST HANDLE * pHandles, WINBOOL fWaitAll, DWORD dwMilliseconds, DWORD dwWakeMask)
{
  logging::log("wrapper", logging::LogLevel::debug, "MsgWaitForMultipleObjects()");
  return MsgWaitForMultipleObjects_(nCount, pHandles, fWaitAll, dwMilliseconds, dwWakeMask);
}

DWORD APIUser32::MsgWaitForMultipleObjectsEx (DWORD nCount, CONST HANDLE * pHandles, DWORD dwMilliseconds, DWORD dwWakeMask, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "MsgWaitForMultipleObjectsEx()");
  return MsgWaitForMultipleObjectsEx_(nCount, pHandles, dwMilliseconds, dwWakeMask, dwFlags);
}

UINT_PTR APIUser32::SetTimer (HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetTimer()");
  return SetTimer_(hWnd, nIDEvent, uElapse, lpTimerFunc);
}

WINBOOL APIUser32::KillTimer (HWND hWnd, UINT_PTR uIDEvent)
{
  logging::log("wrapper", logging::LogLevel::debug, "KillTimer()");
  return KillTimer_(hWnd, uIDEvent);
}

WINBOOL APIUser32::IsWindowUnicode (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWindowUnicode()");
  return IsWindowUnicode_(hWnd);
}

WINBOOL APIUser32::EnableWindow (HWND hWnd, WINBOOL bEnable)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnableWindow()");
  return EnableWindow_(hWnd, bEnable);
}

WINBOOL APIUser32::IsWindowEnabled (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWindowEnabled()");
  return IsWindowEnabled_(hWnd);
}

HACCEL APIUser32::LoadAcceleratorsA (HINSTANCE hInstance, LPCSTR lpTableName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadAcceleratorsA()");
  return LoadAcceleratorsA_(hInstance, lpTableName);
}

HACCEL APIUser32::LoadAcceleratorsW (HINSTANCE hInstance, LPCWSTR lpTableName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadAcceleratorsW()");
  return LoadAcceleratorsW_(hInstance, lpTableName);
}

HACCEL APIUser32::CreateAcceleratorTableA (LPACCEL paccel, int cAccel)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateAcceleratorTableA()");
  return CreateAcceleratorTableA_(paccel, cAccel);
}

HACCEL APIUser32::CreateAcceleratorTableW (LPACCEL paccel, int cAccel)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateAcceleratorTableW()");
  return CreateAcceleratorTableW_(paccel, cAccel);
}

WINBOOL APIUser32::DestroyAcceleratorTable (HACCEL hAccel)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyAcceleratorTable()");
  return DestroyAcceleratorTable_(hAccel);
}

int APIUser32::CopyAcceleratorTableA (HACCEL hAccelSrc, LPACCEL lpAccelDst, int cAccelEntries)
{
  logging::log("wrapper", logging::LogLevel::debug, "CopyAcceleratorTableA()");
  return CopyAcceleratorTableA_(hAccelSrc, lpAccelDst, cAccelEntries);
}

int APIUser32::CopyAcceleratorTableW (HACCEL hAccelSrc, LPACCEL lpAccelDst, int cAccelEntries)
{
  logging::log("wrapper", logging::LogLevel::debug, "CopyAcceleratorTableW()");
  return CopyAcceleratorTableW_(hAccelSrc, lpAccelDst, cAccelEntries);
}

int APIUser32::TranslateAcceleratorA (HWND hWnd, HACCEL hAccTable, LPMSG lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "TranslateAcceleratorA()");
  return TranslateAcceleratorA_(hWnd, hAccTable, lpMsg);
}

int APIUser32::TranslateAcceleratorW (HWND hWnd, HACCEL hAccTable, LPMSG lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "TranslateAcceleratorW()");
  return TranslateAcceleratorW_(hWnd, hAccTable, lpMsg);
}

UINT_PTR APIUser32::SetCoalescableTimer (HWND hWnd, UINT_PTR nIDEvent, UINT uElapse, TIMERPROC lpTimerFunc, ULONG uToleranceDelay)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCoalescableTimer()");
  return SetCoalescableTimer_(hWnd, nIDEvent, uElapse, lpTimerFunc, uToleranceDelay);
}

int APIUser32::GetSystemMetrics (int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSystemMetrics()");
  return GetSystemMetrics_(nIndex);
}

HMENU APIUser32::LoadMenuA (HINSTANCE hInstance, LPCSTR lpMenuName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadMenuA()");
  return LoadMenuA_(hInstance, lpMenuName);
}

HMENU APIUser32::LoadMenuW (HINSTANCE hInstance, LPCWSTR lpMenuName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadMenuW()");
  return LoadMenuW_(hInstance, lpMenuName);
}

HMENU APIUser32::LoadMenuIndirectA (CONST MENUTEMPLATEA * lpMenuTemplate)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadMenuIndirectA()");
  return LoadMenuIndirectA_(lpMenuTemplate);
}

HMENU APIUser32::LoadMenuIndirectW (CONST MENUTEMPLATEW * lpMenuTemplate)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadMenuIndirectW()");
  return LoadMenuIndirectW_(lpMenuTemplate);
}

HMENU APIUser32::GetMenu (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenu()");
  return GetMenu_(hWnd);
}

WINBOOL APIUser32::SetMenu (HWND hWnd, HMENU hMenu)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenu()");
  return SetMenu_(hWnd, hMenu);
}

WINBOOL APIUser32::ChangeMenuA (HMENU hMenu, UINT cmd, LPCSTR lpszNewItem, UINT cmdInsert, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeMenuA()");
  return ChangeMenuA_(hMenu, cmd, lpszNewItem, cmdInsert, flags);
}

WINBOOL APIUser32::ChangeMenuW (HMENU hMenu, UINT cmd, LPCWSTR lpszNewItem, UINT cmdInsert, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeMenuW()");
  return ChangeMenuW_(hMenu, cmd, lpszNewItem, cmdInsert, flags);
}

WINBOOL APIUser32::HiliteMenuItem (HWND hWnd, HMENU hMenu, UINT uIDHiliteItem, UINT uHilite)
{
  logging::log("wrapper", logging::LogLevel::debug, "HiliteMenuItem()");
  return HiliteMenuItem_(hWnd, hMenu, uIDHiliteItem, uHilite);
}

int APIUser32::GetMenuStringA (HMENU hMenu, UINT uIDItem, LPSTR lpString, int cchMax, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuStringA()");
  return GetMenuStringA_(hMenu, uIDItem, lpString, cchMax, flags);
}

int APIUser32::GetMenuStringW (HMENU hMenu, UINT uIDItem, LPWSTR lpString, int cchMax, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuStringW()");
  return GetMenuStringW_(hMenu, uIDItem, lpString, cchMax, flags);
}

UINT APIUser32::GetMenuState (HMENU hMenu, UINT uId, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuState()");
  return GetMenuState_(hMenu, uId, uFlags);
}

WINBOOL APIUser32::DrawMenuBar (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawMenuBar()");
  return DrawMenuBar_(hWnd);
}

HMENU APIUser32::GetSystemMenu (HWND hWnd, WINBOOL bRevert)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSystemMenu()");
  return GetSystemMenu_(hWnd, bRevert);
}

HMENU APIUser32::CreateMenu (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateMenu()");
  return CreateMenu_();
}

HMENU APIUser32::CreatePopupMenu (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreatePopupMenu()");
  return CreatePopupMenu_();
}

WINBOOL APIUser32::DestroyMenu (HMENU hMenu)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyMenu()");
  return DestroyMenu_(hMenu);
}

DWORD APIUser32::CheckMenuItem (HMENU hMenu, UINT uIDCheckItem, UINT uCheck)
{
  logging::log("wrapper", logging::LogLevel::debug, "CheckMenuItem()");
  return CheckMenuItem_(hMenu, uIDCheckItem, uCheck);
}

WINBOOL APIUser32::EnableMenuItem (HMENU hMenu, UINT uIDEnableItem, UINT uEnable)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnableMenuItem()");
  return EnableMenuItem_(hMenu, uIDEnableItem, uEnable);
}

HMENU APIUser32::GetSubMenu (HMENU hMenu, int nPos)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSubMenu()");
  return GetSubMenu_(hMenu, nPos);
}

UINT APIUser32::GetMenuItemID (HMENU hMenu, int nPos)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuItemID()");
  return GetMenuItemID_(hMenu, nPos);
}

int APIUser32::GetMenuItemCount (HMENU hMenu)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuItemCount()");
  return GetMenuItemCount_(hMenu);
}

WINBOOL APIUser32::InsertMenuA (HMENU hMenu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "InsertMenuA()");
  return InsertMenuA_(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

WINBOOL APIUser32::InsertMenuW (HMENU hMenu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "InsertMenuW()");
  return InsertMenuW_(hMenu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

WINBOOL APIUser32::AppendMenuA (HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "AppendMenuA()");
  return AppendMenuA_(hMenu, uFlags, uIDNewItem, lpNewItem);
}

WINBOOL APIUser32::AppendMenuW (HMENU hMenu, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "AppendMenuW()");
  return AppendMenuW_(hMenu, uFlags, uIDNewItem, lpNewItem);
}

WINBOOL APIUser32::ModifyMenuA (HMENU hMnu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "ModifyMenuA()");
  return ModifyMenuA_(hMnu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

WINBOOL APIUser32::ModifyMenuW (HMENU hMnu, UINT uPosition, UINT uFlags, UINT_PTR uIDNewItem, LPCWSTR lpNewItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "ModifyMenuW()");
  return ModifyMenuW_(hMnu, uPosition, uFlags, uIDNewItem, lpNewItem);
}

WINBOOL APIUser32::RemoveMenu (HMENU hMenu, UINT uPosition, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RemoveMenu()");
  return RemoveMenu_(hMenu, uPosition, uFlags);
}

WINBOOL APIUser32::DeleteMenu (HMENU hMenu, UINT uPosition, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DeleteMenu()");
  return DeleteMenu_(hMenu, uPosition, uFlags);
}

WINBOOL APIUser32::SetMenuItemBitmaps (HMENU hMenu, UINT uPosition, UINT uFlags, HBITMAP hBitmapUnchecked, HBITMAP hBitmapChecked)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuItemBitmaps()");
  return SetMenuItemBitmaps_(hMenu, uPosition, uFlags, hBitmapUnchecked, hBitmapChecked);
}

LONG APIUser32::GetMenuCheckMarkDimensions (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuCheckMarkDimensions()");
  return GetMenuCheckMarkDimensions_();
}

WINBOOL APIUser32::TrackPopupMenu (HMENU hMenu, UINT uFlags, int x, int y, int nReserved, HWND hWnd, CONST RECT * prcRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "TrackPopupMenu()");
  return TrackPopupMenu_(hMenu, uFlags, x, y, nReserved, hWnd, prcRect);
}

WINBOOL APIUser32::TrackPopupMenuEx (HMENU arg0, UINT arg1, int arg2, int arg3, HWND arg4, LPTPMPARAMS arg5)
{
  logging::log("wrapper", logging::LogLevel::debug, "TrackPopupMenuEx()");
  return TrackPopupMenuEx_(arg0, arg1, arg2, arg3, arg4, arg5);
}

WINBOOL APIUser32::GetMenuInfo (HMENU arg0, LPMENUINFO arg1)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuInfo()");
  return GetMenuInfo_(arg0, arg1);
}

WINBOOL APIUser32::SetMenuInfo (HMENU arg0, LPCMENUINFO arg1)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuInfo()");
  return SetMenuInfo_(arg0, arg1);
}

WINBOOL APIUser32::EndMenu (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "EndMenu()");
  return EndMenu_();
}

WINBOOL APIUser32::CalculatePopupWindowPosition (const POINT * anchorPoint, const SIZE * windowSize, UINT flags, RECT * excludeRect, RECT * popupWindowPosition)
{
  logging::log("wrapper", logging::LogLevel::debug, "CalculatePopupWindowPosition()");
  return CalculatePopupWindowPosition_(anchorPoint, windowSize, flags, excludeRect, popupWindowPosition);
}

WINBOOL APIUser32::InsertMenuItemA (HMENU hmenu, UINT item, WINBOOL fByPosition, LPCMENUITEMINFOA lpmi)
{
  logging::log("wrapper", logging::LogLevel::debug, "InsertMenuItemA()");
  return InsertMenuItemA_(hmenu, item, fByPosition, lpmi);
}

WINBOOL APIUser32::InsertMenuItemW (HMENU hmenu, UINT item, WINBOOL fByPosition, LPCMENUITEMINFOW lpmi)
{
  logging::log("wrapper", logging::LogLevel::debug, "InsertMenuItemW()");
  return InsertMenuItemW_(hmenu, item, fByPosition, lpmi);
}

WINBOOL APIUser32::GetMenuItemInfoA (HMENU hmenu, UINT item, WINBOOL fByPosition, LPMENUITEMINFOA lpmii)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuItemInfoA()");
  return GetMenuItemInfoA_(hmenu, item, fByPosition, lpmii);
}

WINBOOL APIUser32::GetMenuItemInfoW (HMENU hmenu, UINT item, WINBOOL fByPosition, LPMENUITEMINFOW lpmii)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuItemInfoW()");
  return GetMenuItemInfoW_(hmenu, item, fByPosition, lpmii);
}

WINBOOL APIUser32::SetMenuItemInfoA (HMENU hmenu, UINT item, WINBOOL fByPositon, LPCMENUITEMINFOA lpmii)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuItemInfoA()");
  return SetMenuItemInfoA_(hmenu, item, fByPositon, lpmii);
}

WINBOOL APIUser32::SetMenuItemInfoW (HMENU hmenu, UINT item, WINBOOL fByPositon, LPCMENUITEMINFOW lpmii)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuItemInfoW()");
  return SetMenuItemInfoW_(hmenu, item, fByPositon, lpmii);
}

UINT APIUser32::GetMenuDefaultItem (HMENU hMenu, UINT fByPos, UINT gmdiFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuDefaultItem()");
  return GetMenuDefaultItem_(hMenu, fByPos, gmdiFlags);
}

WINBOOL APIUser32::SetMenuDefaultItem (HMENU hMenu, UINT uItem, UINT fByPos)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuDefaultItem()");
  return SetMenuDefaultItem_(hMenu, uItem, fByPos);
}

WINBOOL APIUser32::GetMenuItemRect (HWND hWnd, HMENU hMenu, UINT uItem, LPRECT lprcItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuItemRect()");
  return GetMenuItemRect_(hWnd, hMenu, uItem, lprcItem);
}

int APIUser32::MenuItemFromPoint (HWND hWnd, HMENU hMenu, POINT ptScreen)
{
  logging::log("wrapper", logging::LogLevel::debug, "MenuItemFromPoint()");
  return MenuItemFromPoint_(hWnd, hMenu, ptScreen);
}

DWORD APIUser32::DragObject (HWND hwndParent, HWND hwndFrom, UINT fmt, ULONG_PTR data, HCURSOR hcur)
{
  logging::log("wrapper", logging::LogLevel::debug, "DragObject()");
  return DragObject_(hwndParent, hwndFrom, fmt, data, hcur);
}

WINBOOL APIUser32::DragDetect (HWND hwnd, POINT pt)
{
  logging::log("wrapper", logging::LogLevel::debug, "DragDetect()");
  return DragDetect_(hwnd, pt);
}

WINBOOL APIUser32::DrawIcon (HDC hDC, int X, int Y, HICON hIcon)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawIcon()");
  return DrawIcon_(hDC, X, Y, hIcon);
}

int APIUser32::DrawTextA (HDC hdc, LPCSTR lpchText, int cchText, LPRECT lprc, UINT format)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawTextA()");
  return DrawTextA_(hdc, lpchText, cchText, lprc, format);
}

int APIUser32::DrawTextW (HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawTextW()");
  return DrawTextW_(hdc, lpchText, cchText, lprc, format);
}

int APIUser32::DrawTextExA (HDC hdc, LPSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawTextExA()");
  return DrawTextExA_(hdc, lpchText, cchText, lprc, format, lpdtp);
}

int APIUser32::DrawTextExW (HDC hdc, LPWSTR lpchText, int cchText, LPRECT lprc, UINT format, LPDRAWTEXTPARAMS lpdtp)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawTextExW()");
  return DrawTextExW_(hdc, lpchText, cchText, lprc, format, lpdtp);
}

WINBOOL APIUser32::GrayStringA (HDC hDC, HBRUSH hBrush, GRAYSTRINGPROC lpOutputFunc, LPARAM lpData, int nCount, int X, int Y, int nWidth, int nHeight)
{
  logging::log("wrapper", logging::LogLevel::debug, "GrayStringA()");
  return GrayStringA_(hDC, hBrush, lpOutputFunc, lpData, nCount, X, Y, nWidth, nHeight);
}

WINBOOL APIUser32::GrayStringW (HDC hDC, HBRUSH hBrush, GRAYSTRINGPROC lpOutputFunc, LPARAM lpData, int nCount, int X, int Y, int nWidth, int nHeight)
{
  logging::log("wrapper", logging::LogLevel::debug, "GrayStringW()");
  return GrayStringW_(hDC, hBrush, lpOutputFunc, lpData, nCount, X, Y, nWidth, nHeight);
}

WINBOOL APIUser32::DrawStateA (HDC hdc, HBRUSH hbrFore, DRAWSTATEPROC qfnCallBack, LPARAM lData, WPARAM wData, int x, int y, int cx, int cy, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawStateA()");
  return DrawStateA_(hdc, hbrFore, qfnCallBack, lData, wData, x, y, cx, cy, uFlags);
}

WINBOOL APIUser32::DrawStateW (HDC hdc, HBRUSH hbrFore, DRAWSTATEPROC qfnCallBack, LPARAM lData, WPARAM wData, int x, int y, int cx, int cy, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawStateW()");
  return DrawStateW_(hdc, hbrFore, qfnCallBack, lData, wData, x, y, cx, cy, uFlags);
}

LONG APIUser32::TabbedTextOutA (HDC hdc, int x, int y, LPCSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions, int nTabOrigin)
{
  logging::log("wrapper", logging::LogLevel::debug, "TabbedTextOutA()");
  return TabbedTextOutA_(hdc, x, y, lpString, chCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
}

LONG APIUser32::TabbedTextOutW (HDC hdc, int x, int y, LPCWSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions, int nTabOrigin)
{
  logging::log("wrapper", logging::LogLevel::debug, "TabbedTextOutW()");
  return TabbedTextOutW_(hdc, x, y, lpString, chCount, nTabPositions, lpnTabStopPositions, nTabOrigin);
}

DWORD APIUser32::GetTabbedTextExtentA (HDC hdc, LPCSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTabbedTextExtentA()");
  return GetTabbedTextExtentA_(hdc, lpString, chCount, nTabPositions, lpnTabStopPositions);
}

DWORD APIUser32::GetTabbedTextExtentW (HDC hdc, LPCWSTR lpString, int chCount, int nTabPositions, CONST INT * lpnTabStopPositions)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTabbedTextExtentW()");
  return GetTabbedTextExtentW_(hdc, lpString, chCount, nTabPositions, lpnTabStopPositions);
}

WINBOOL APIUser32::UpdateWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "UpdateWindow()");
  return UpdateWindow_(hWnd);
}

HWND APIUser32::SetActiveWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetActiveWindow()");
  return SetActiveWindow_(hWnd);
}

HWND APIUser32::GetForegroundWindow (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetForegroundWindow()");
  return GetForegroundWindow_();
}

WINBOOL APIUser32::PaintDesktop (HDC hdc)
{
  logging::log("wrapper", logging::LogLevel::debug, "PaintDesktop()");
  return PaintDesktop_(hdc);
}

VOID APIUser32::SwitchToThisWindow (HWND hwnd, WINBOOL fUnknown)
{
  logging::log("wrapper", logging::LogLevel::debug, "SwitchToThisWindow()");
  SwitchToThisWindow_(hwnd, fUnknown);
}

WINBOOL APIUser32::SetForegroundWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetForegroundWindow()");
  return SetForegroundWindow_(hWnd);
}

WINBOOL APIUser32::AllowSetForegroundWindow (DWORD dwProcessId)
{
  logging::log("wrapper", logging::LogLevel::debug, "AllowSetForegroundWindow()");
  return AllowSetForegroundWindow_(dwProcessId);
}

WINBOOL APIUser32::LockSetForegroundWindow (UINT uLockCode)
{
  logging::log("wrapper", logging::LogLevel::debug, "LockSetForegroundWindow()");
  return LockSetForegroundWindow_(uLockCode);
}

HWND APIUser32::WindowFromDC (HDC hDC)
{
  logging::log("wrapper", logging::LogLevel::debug, "WindowFromDC()");
  return WindowFromDC_(hDC);
}

HDC APIUser32::GetDC (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDC()");
  return GetDC_(hWnd);
}

HDC APIUser32::GetDCEx (HWND hWnd, HRGN hrgnClip, DWORD flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDCEx()");
  return GetDCEx_(hWnd, hrgnClip, flags);
}

HDC APIUser32::GetWindowDC (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowDC()");
  return GetWindowDC_(hWnd);
}

int APIUser32::ReleaseDC (HWND hWnd, HDC hDC)
{
  logging::log("wrapper", logging::LogLevel::debug, "ReleaseDC()");
  return ReleaseDC_(hWnd, hDC);
}

HDC APIUser32::BeginPaint (HWND hWnd, LPPAINTSTRUCT lpPaint)
{
  logging::log("wrapper", logging::LogLevel::debug, "BeginPaint()");
  return BeginPaint_(hWnd, lpPaint);
}

WINBOOL APIUser32::EndPaint (HWND hWnd, CONST PAINTSTRUCT * lpPaint)
{
  logging::log("wrapper", logging::LogLevel::debug, "EndPaint()");
  return EndPaint_(hWnd, lpPaint);
}

WINBOOL APIUser32::GetUpdateRect (HWND hWnd, LPRECT lpRect, WINBOOL bErase)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUpdateRect()");
  return GetUpdateRect_(hWnd, lpRect, bErase);
}

int APIUser32::GetUpdateRgn (HWND hWnd, HRGN hRgn, WINBOOL bErase)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetUpdateRgn()");
  return GetUpdateRgn_(hWnd, hRgn, bErase);
}

int APIUser32::SetWindowRgn (HWND hWnd, HRGN hRgn, WINBOOL bRedraw)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowRgn()");
  return SetWindowRgn_(hWnd, hRgn, bRedraw);
}

int APIUser32::GetWindowRgn (HWND hWnd, HRGN hRgn)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowRgn()");
  return GetWindowRgn_(hWnd, hRgn);
}

int APIUser32::GetWindowRgnBox (HWND hWnd, LPRECT lprc)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowRgnBox()");
  return GetWindowRgnBox_(hWnd, lprc);
}

int APIUser32::ExcludeUpdateRgn (HDC hDC, HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "ExcludeUpdateRgn()");
  return ExcludeUpdateRgn_(hDC, hWnd);
}

WINBOOL APIUser32::InvalidateRect (HWND hWnd, CONST RECT * lpRect, WINBOOL bErase)
{
  logging::log("wrapper", logging::LogLevel::debug, "InvalidateRect()");
  return InvalidateRect_(hWnd, lpRect, bErase);
}

WINBOOL APIUser32::ValidateRect (HWND hWnd, CONST RECT * lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "ValidateRect()");
  return ValidateRect_(hWnd, lpRect);
}

WINBOOL APIUser32::InvalidateRgn (HWND hWnd, HRGN hRgn, WINBOOL bErase)
{
  logging::log("wrapper", logging::LogLevel::debug, "InvalidateRgn()");
  return InvalidateRgn_(hWnd, hRgn, bErase);
}

WINBOOL APIUser32::ValidateRgn (HWND hWnd, HRGN hRgn)
{
  logging::log("wrapper", logging::LogLevel::debug, "ValidateRgn()");
  return ValidateRgn_(hWnd, hRgn);
}

WINBOOL APIUser32::RedrawWindow (HWND hWnd, CONST RECT * lprcUpdate, HRGN hrgnUpdate, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "RedrawWindow()");
  return RedrawWindow_(hWnd, lprcUpdate, hrgnUpdate, flags);
}

WINBOOL APIUser32::LockWindowUpdate (HWND hWndLock)
{
  logging::log("wrapper", logging::LogLevel::debug, "LockWindowUpdate()");
  return LockWindowUpdate_(hWndLock);
}

WINBOOL APIUser32::ScrollWindow (HWND hWnd, int XAmount, int YAmount, CONST RECT * lpRect, CONST RECT * lpClipRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollWindow()");
  return ScrollWindow_(hWnd, XAmount, YAmount, lpRect, lpClipRect);
}

WINBOOL APIUser32::ScrollDC (HDC hDC, int dx, int dy, CONST RECT * lprcScroll, CONST RECT * lprcClip, HRGN hrgnUpdate, LPRECT lprcUpdate)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollDC()");
  return ScrollDC_(hDC, dx, dy, lprcScroll, lprcClip, hrgnUpdate, lprcUpdate);
}

int APIUser32::ScrollWindowEx (HWND hWnd, int dx, int dy, CONST RECT * prcScroll, CONST RECT * prcClip, HRGN hrgnUpdate, LPRECT prcUpdate, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollWindowEx()");
  return ScrollWindowEx_(hWnd, dx, dy, prcScroll, prcClip, hrgnUpdate, prcUpdate, flags);
}

int APIUser32::SetScrollPos (HWND hWnd, int nBar, int nPos, WINBOOL bRedraw)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetScrollPos()");
  return SetScrollPos_(hWnd, nBar, nPos, bRedraw);
}

int APIUser32::GetScrollPos (HWND hWnd, int nBar)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetScrollPos()");
  return GetScrollPos_(hWnd, nBar);
}

WINBOOL APIUser32::SetScrollRange (HWND hWnd, int nBar, int nMinPos, int nMaxPos, WINBOOL bRedraw)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetScrollRange()");
  return SetScrollRange_(hWnd, nBar, nMinPos, nMaxPos, bRedraw);
}

WINBOOL APIUser32::GetScrollRange (HWND hWnd, int nBar, LPINT lpMinPos, LPINT lpMaxPos)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetScrollRange()");
  return GetScrollRange_(hWnd, nBar, lpMinPos, lpMaxPos);
}

WINBOOL APIUser32::ShowScrollBar (HWND hWnd, int wBar, WINBOOL bShow)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowScrollBar()");
  return ShowScrollBar_(hWnd, wBar, bShow);
}

WINBOOL APIUser32::EnableScrollBar (HWND hWnd, UINT wSBflags, UINT wArrows)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnableScrollBar()");
  return EnableScrollBar_(hWnd, wSBflags, wArrows);
}

WINBOOL APIUser32::SetPropA (HWND hWnd, LPCSTR lpString, HANDLE hData)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetPropA()");
  return SetPropA_(hWnd, lpString, hData);
}

WINBOOL APIUser32::SetPropW (HWND hWnd, LPCWSTR lpString, HANDLE hData)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetPropW()");
  return SetPropW_(hWnd, lpString, hData);
}

HANDLE APIUser32::GetPropA (HWND hWnd, LPCSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPropA()");
  return GetPropA_(hWnd, lpString);
}

HANDLE APIUser32::GetPropW (HWND hWnd, LPCWSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPropW()");
  return GetPropW_(hWnd, lpString);
}

HANDLE APIUser32::RemovePropA (HWND hWnd, LPCSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "RemovePropA()");
  return RemovePropA_(hWnd, lpString);
}

HANDLE APIUser32::RemovePropW (HWND hWnd, LPCWSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "RemovePropW()");
  return RemovePropW_(hWnd, lpString);
}

int APIUser32::EnumPropsExA (HWND hWnd, PROPENUMPROCEXA lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumPropsExA()");
  return EnumPropsExA_(hWnd, lpEnumFunc, lParam);
}

int APIUser32::EnumPropsExW (HWND hWnd, PROPENUMPROCEXW lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumPropsExW()");
  return EnumPropsExW_(hWnd, lpEnumFunc, lParam);
}

int APIUser32::EnumPropsA (HWND hWnd, PROPENUMPROCA lpEnumFunc)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumPropsA()");
  return EnumPropsA_(hWnd, lpEnumFunc);
}

int APIUser32::EnumPropsW (HWND hWnd, PROPENUMPROCW lpEnumFunc)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumPropsW()");
  return EnumPropsW_(hWnd, lpEnumFunc);
}

WINBOOL APIUser32::SetWindowTextA (HWND hWnd, LPCSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowTextA()");
  return SetWindowTextA_(hWnd, lpString);
}

WINBOOL APIUser32::SetWindowTextW (HWND hWnd, LPCWSTR lpString)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowTextW()");
  return SetWindowTextW_(hWnd, lpString);
}

int APIUser32::GetWindowTextA (HWND hWnd, LPSTR lpString, int nMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowTextA()");
  return GetWindowTextA_(hWnd, lpString, nMaxCount);
}

int APIUser32::GetWindowTextW (HWND hWnd, LPWSTR lpString, int nMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowTextW()");
  return GetWindowTextW_(hWnd, lpString, nMaxCount);
}

int APIUser32::GetWindowTextLengthA (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowTextLengthA()");
  return GetWindowTextLengthA_(hWnd);
}

int APIUser32::GetWindowTextLengthW (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowTextLengthW()");
  return GetWindowTextLengthW_(hWnd);
}

WINBOOL APIUser32::GetClientRect (HWND hWnd, LPRECT lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClientRect()");
  return GetClientRect_(hWnd, lpRect);
}

WINBOOL APIUser32::GetWindowRect (HWND hWnd, LPRECT lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowRect()");
  return GetWindowRect_(hWnd, lpRect);
}

WINBOOL APIUser32::AdjustWindowRect (LPRECT lpRect, DWORD dwStyle, WINBOOL bMenu)
{
  logging::log("wrapper", logging::LogLevel::debug, "AdjustWindowRect()");
  return AdjustWindowRect_(lpRect, dwStyle, bMenu);
}

WINBOOL APIUser32::AdjustWindowRectEx (LPRECT lpRect, DWORD dwStyle, WINBOOL bMenu, DWORD dwExStyle)
{
  logging::log("wrapper", logging::LogLevel::debug, "AdjustWindowRectEx()");
  return AdjustWindowRectEx_(lpRect, dwStyle, bMenu, dwExStyle);
}

WINBOOL APIUser32::SetWindowContextHelpId (HWND arg0, DWORD arg1)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowContextHelpId()");
  return SetWindowContextHelpId_(arg0, arg1);
}

DWORD APIUser32::GetWindowContextHelpId (HWND arg0)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowContextHelpId()");
  return GetWindowContextHelpId_(arg0);
}

WINBOOL APIUser32::SetMenuContextHelpId (HMENU arg0, DWORD arg1)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetMenuContextHelpId()");
  return SetMenuContextHelpId_(arg0, arg1);
}

DWORD APIUser32::GetMenuContextHelpId (HMENU arg0)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuContextHelpId()");
  return GetMenuContextHelpId_(arg0);
}

int APIUser32::MessageBoxA (HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxA()");
  return MessageBoxA_(hWnd, lpText, lpCaption, uType);
}

int APIUser32::MessageBoxW (HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxW()");
  return MessageBoxW_(hWnd, lpText, lpCaption, uType);
}

int APIUser32::MessageBoxExA (HWND hWnd, LPCSTR lpText, LPCSTR lpCaption, UINT uType, WORD wLanguageId)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxExA()");
  return MessageBoxExA_(hWnd, lpText, lpCaption, uType, wLanguageId);
}

int APIUser32::MessageBoxExW (HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType, WORD wLanguageId)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxExW()");
  return MessageBoxExW_(hWnd, lpText, lpCaption, uType, wLanguageId);
}

int APIUser32::MessageBoxIndirectA (CONST MSGBOXPARAMSA * lpmbp)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxIndirectA()");
  return MessageBoxIndirectA_(lpmbp);
}

int APIUser32::MessageBoxIndirectW (CONST MSGBOXPARAMSW * lpmbp)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBoxIndirectW()");
  return MessageBoxIndirectW_(lpmbp);
}

WINBOOL APIUser32::MessageBeep (UINT uType)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageBeep()");
  return MessageBeep_(uType);
}

int APIUser32::ShowCursor (WINBOOL bShow)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowCursor()");
  return ShowCursor_(bShow);
}

WINBOOL APIUser32::SetCursorPos (int X, int Y)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCursorPos()");
  return SetCursorPos_(X, Y);
}

HCURSOR APIUser32::SetCursor (HCURSOR hCursor)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCursor()");
  return SetCursor_(hCursor);
}

WINBOOL APIUser32::GetCursorPos (LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCursorPos()");
  return GetCursorPos_(lpPoint);
}

WINBOOL APIUser32::ClipCursor (CONST RECT * lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "ClipCursor()");
  return ClipCursor_(lpRect);
}

WINBOOL APIUser32::GetClipCursor (LPRECT lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClipCursor()");
  return GetClipCursor_(lpRect);
}

HCURSOR APIUser32::GetCursor (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCursor()");
  return GetCursor_();
}

WINBOOL APIUser32::CreateCaret (HWND hWnd, HBITMAP hBitmap, int nWidth, int nHeight)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateCaret()");
  return CreateCaret_(hWnd, hBitmap, nWidth, nHeight);
}

UINT APIUser32::GetCaretBlinkTime (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCaretBlinkTime()");
  return GetCaretBlinkTime_();
}

WINBOOL APIUser32::SetCaretBlinkTime (UINT uMSeconds)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCaretBlinkTime()");
  return SetCaretBlinkTime_(uMSeconds);
}

WINBOOL APIUser32::DestroyCaret (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyCaret()");
  return DestroyCaret_();
}

WINBOOL APIUser32::HideCaret (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "HideCaret()");
  return HideCaret_(hWnd);
}

WINBOOL APIUser32::ShowCaret (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShowCaret()");
  return ShowCaret_(hWnd);
}

WINBOOL APIUser32::SetCaretPos (int X, int Y)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetCaretPos()");
  return SetCaretPos_(X, Y);
}

WINBOOL APIUser32::GetCaretPos (LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCaretPos()");
  return GetCaretPos_(lpPoint);
}

WINBOOL APIUser32::ClientToScreen (HWND hWnd, LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "ClientToScreen()");
  return ClientToScreen_(hWnd, lpPoint);
}

WINBOOL APIUser32::ScreenToClient (HWND hWnd, LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScreenToClient()");
  return ScreenToClient_(hWnd, lpPoint);
}

int APIUser32::MapWindowPoints (HWND hWndFrom, HWND hWndTo, LPPOINT lpPoints, UINT cPoints)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapWindowPoints()");
  return MapWindowPoints_(hWndFrom, hWndTo, lpPoints, cPoints);
}

HWND APIUser32::WindowFromPoint (POINT Point)
{
  logging::log("wrapper", logging::LogLevel::debug, "WindowFromPoint()");
  return WindowFromPoint_(Point);
}

HWND APIUser32::ChildWindowFromPoint (HWND hWndParent, POINT Point)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChildWindowFromPoint()");
  return ChildWindowFromPoint_(hWndParent, Point);
}

HWND APIUser32::ChildWindowFromPointEx (HWND hwnd, POINT pt, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChildWindowFromPointEx()");
  return ChildWindowFromPointEx_(hwnd, pt, flags);
}

WINBOOL APIUser32::SetPhysicalCursorPos (int X, int Y)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetPhysicalCursorPos()");
  return SetPhysicalCursorPos_(X, Y);
}

WINBOOL APIUser32::GetPhysicalCursorPos (LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPhysicalCursorPos()");
  return GetPhysicalCursorPos_(lpPoint);
}

WINBOOL APIUser32::LogicalToPhysicalPoint (HWND hWnd, LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "LogicalToPhysicalPoint()");
  return LogicalToPhysicalPoint_(hWnd, lpPoint);
}

WINBOOL APIUser32::PhysicalToLogicalPoint (HWND hWnd, LPPOINT lpPoint)
{
  logging::log("wrapper", logging::LogLevel::debug, "PhysicalToLogicalPoint()");
  return PhysicalToLogicalPoint_(hWnd, lpPoint);
}

HWND APIUser32::WindowFromPhysicalPoint (POINT Point)
{
  logging::log("wrapper", logging::LogLevel::debug, "WindowFromPhysicalPoint()");
  return WindowFromPhysicalPoint_(Point);
}

DWORD APIUser32::GetSysColor (int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSysColor()");
  return GetSysColor_(nIndex);
}

HBRUSH APIUser32::GetSysColorBrush (int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSysColorBrush()");
  return GetSysColorBrush_(nIndex);
}

WINBOOL APIUser32::SetSysColors (int cElements, CONST INT * lpaElements, CONST COLORREF * lpaRgbValues)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetSysColors()");
  return SetSysColors_(cElements, lpaElements, lpaRgbValues);
}

WINBOOL APIUser32::DrawFocusRect (HDC hDC, CONST RECT * lprc)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawFocusRect()");
  return DrawFocusRect_(hDC, lprc);
}

int APIUser32::FillRect (HDC hDC, CONST RECT * lprc, HBRUSH hbr)
{
  logging::log("wrapper", logging::LogLevel::debug, "FillRect()");
  return FillRect_(hDC, lprc, hbr);
}

int APIUser32::FrameRect (HDC hDC, CONST RECT * lprc, HBRUSH hbr)
{
  logging::log("wrapper", logging::LogLevel::debug, "FrameRect()");
  return FrameRect_(hDC, lprc, hbr);
}

WINBOOL APIUser32::InvertRect (HDC hDC, CONST RECT * lprc)
{
  logging::log("wrapper", logging::LogLevel::debug, "InvertRect()");
  return InvertRect_(hDC, lprc);
}

WINBOOL APIUser32::SetRect (LPRECT lprc, int xLeft, int yTop, int xRight, int yBottom)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetRect()");
  return SetRect_(lprc, xLeft, yTop, xRight, yBottom);
}

WINBOOL APIUser32::SetRectEmpty (LPRECT lprc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetRectEmpty()");
  return SetRectEmpty_(lprc);
}

WINBOOL APIUser32::CopyRect (LPRECT lprcDst, CONST RECT * lprcSrc)
{
  logging::log("wrapper", logging::LogLevel::debug, "CopyRect()");
  return CopyRect_(lprcDst, lprcSrc);
}

WINBOOL APIUser32::InflateRect (LPRECT lprc, int dx, int dy)
{
  logging::log("wrapper", logging::LogLevel::debug, "InflateRect()");
  return InflateRect_(lprc, dx, dy);
}

WINBOOL APIUser32::IntersectRect (LPRECT lprcDst, CONST RECT * lprcSrc1, CONST RECT * lprcSrc2)
{
  logging::log("wrapper", logging::LogLevel::debug, "IntersectRect()");
  return IntersectRect_(lprcDst, lprcSrc1, lprcSrc2);
}

WINBOOL APIUser32::UnionRect (LPRECT lprcDst, CONST RECT * lprcSrc1, CONST RECT * lprcSrc2)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnionRect()");
  return UnionRect_(lprcDst, lprcSrc1, lprcSrc2);
}

WINBOOL APIUser32::SubtractRect (LPRECT lprcDst, CONST RECT * lprcSrc1, CONST RECT * lprcSrc2)
{
  logging::log("wrapper", logging::LogLevel::debug, "SubtractRect()");
  return SubtractRect_(lprcDst, lprcSrc1, lprcSrc2);
}

WINBOOL APIUser32::OffsetRect (LPRECT lprc, int dx, int dy)
{
  logging::log("wrapper", logging::LogLevel::debug, "OffsetRect()");
  return OffsetRect_(lprc, dx, dy);
}

WINBOOL APIUser32::IsRectEmpty (CONST RECT * lprc)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsRectEmpty()");
  return IsRectEmpty_(lprc);
}

WINBOOL APIUser32::EqualRect (CONST RECT * lprc1, CONST RECT * lprc2)
{
  logging::log("wrapper", logging::LogLevel::debug, "EqualRect()");
  return EqualRect_(lprc1, lprc2);
}

WINBOOL APIUser32::PtInRect (CONST RECT * lprc, POINT pt)
{
  logging::log("wrapper", logging::LogLevel::debug, "PtInRect()");
  return PtInRect_(lprc, pt);
}

WORD APIUser32::GetWindowWord (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowWord()");
  return GetWindowWord_(hWnd, nIndex);
}

WORD APIUser32::SetWindowWord (HWND hWnd, int nIndex, WORD wNewWord)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowWord()");
  return SetWindowWord_(hWnd, nIndex, wNewWord);
}

LONG APIUser32::GetWindowLongA (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowLongA()");
  return GetWindowLongA_(hWnd, nIndex);
}

LONG APIUser32::GetWindowLongW (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowLongW()");
  return GetWindowLongW_(hWnd, nIndex);
}

LONG APIUser32::SetWindowLongA (HWND hWnd, int nIndex, LONG dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowLongA()");
  return SetWindowLongA_(hWnd, nIndex, dwNewLong);
}

LONG APIUser32::SetWindowLongW (HWND hWnd, int nIndex, LONG dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowLongW()");
  return SetWindowLongW_(hWnd, nIndex, dwNewLong);
}

LONG_PTR APIUser32::GetWindowLongPtrA (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowLongPtrA()");
  return GetWindowLongPtrA_(hWnd, nIndex);
}

LONG_PTR APIUser32::GetWindowLongPtrW (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowLongPtrW()");
  return GetWindowLongPtrW_(hWnd, nIndex);
}

LONG_PTR APIUser32::SetWindowLongPtrA (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowLongPtrA()");
  return SetWindowLongPtrA_(hWnd, nIndex, dwNewLong);
}

LONG_PTR APIUser32::SetWindowLongPtrW (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowLongPtrW()");
  return SetWindowLongPtrW_(hWnd, nIndex, dwNewLong);
}

WORD APIUser32::GetClassWord (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassWord()");
  return GetClassWord_(hWnd, nIndex);
}

WORD APIUser32::SetClassWord (HWND hWnd, int nIndex, WORD wNewWord)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClassWord()");
  return SetClassWord_(hWnd, nIndex, wNewWord);
}

DWORD APIUser32::GetClassLongA (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassLongA()");
  return GetClassLongA_(hWnd, nIndex);
}

DWORD APIUser32::GetClassLongW (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassLongW()");
  return GetClassLongW_(hWnd, nIndex);
}

DWORD APIUser32::SetClassLongA (HWND hWnd, int nIndex, LONG dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClassLongA()");
  return SetClassLongA_(hWnd, nIndex, dwNewLong);
}

DWORD APIUser32::SetClassLongW (HWND hWnd, int nIndex, LONG dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClassLongW()");
  return SetClassLongW_(hWnd, nIndex, dwNewLong);
}

ULONG_PTR APIUser32::GetClassLongPtrA (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassLongPtrA()");
  return GetClassLongPtrA_(hWnd, nIndex);
}

ULONG_PTR APIUser32::GetClassLongPtrW (HWND hWnd, int nIndex)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassLongPtrW()");
  return GetClassLongPtrW_(hWnd, nIndex);
}

ULONG_PTR APIUser32::SetClassLongPtrA (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClassLongPtrA()");
  return SetClassLongPtrA_(hWnd, nIndex, dwNewLong);
}

ULONG_PTR APIUser32::SetClassLongPtrW (HWND hWnd, int nIndex, LONG_PTR dwNewLong)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetClassLongPtrW()");
  return SetClassLongPtrW_(hWnd, nIndex, dwNewLong);
}

WINBOOL APIUser32::GetProcessDefaultLayout (DWORD * pdwDefaultLayout)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetProcessDefaultLayout()");
  return GetProcessDefaultLayout_(pdwDefaultLayout);
}

WINBOOL APIUser32::SetProcessDefaultLayout (DWORD dwDefaultLayout)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProcessDefaultLayout()");
  return SetProcessDefaultLayout_(dwDefaultLayout);
}

HWND APIUser32::GetDesktopWindow (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDesktopWindow()");
  return GetDesktopWindow_();
}

HWND APIUser32::GetParent (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetParent()");
  return GetParent_(hWnd);
}

HWND APIUser32::SetParent (HWND hWndChild, HWND hWndNewParent)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetParent()");
  return SetParent_(hWndChild, hWndNewParent);
}

WINBOOL APIUser32::EnumChildWindows (HWND hWndParent, WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumChildWindows()");
  return EnumChildWindows_(hWndParent, lpEnumFunc, lParam);
}

HWND APIUser32::FindWindowA (LPCSTR lpClassName, LPCSTR lpWindowName)
{
  logging::log("wrapper", logging::LogLevel::debug, "FindWindowA()");
  return FindWindowA_(lpClassName, lpWindowName);
}

HWND APIUser32::FindWindowW (LPCWSTR lpClassName, LPCWSTR lpWindowName)
{
  logging::log("wrapper", logging::LogLevel::debug, "FindWindowW()");
  return FindWindowW_(lpClassName, lpWindowName);
}

HWND APIUser32::FindWindowExA (HWND hWndParent, HWND hWndChildAfter, LPCSTR lpszClass, LPCSTR lpszWindow)
{
  logging::log("wrapper", logging::LogLevel::debug, "FindWindowExA()");
  return FindWindowExA_(hWndParent, hWndChildAfter, lpszClass, lpszWindow);
}

HWND APIUser32::FindWindowExW (HWND hWndParent, HWND hWndChildAfter, LPCWSTR lpszClass, LPCWSTR lpszWindow)
{
  logging::log("wrapper", logging::LogLevel::debug, "FindWindowExW()");
  return FindWindowExW_(hWndParent, hWndChildAfter, lpszClass, lpszWindow);
}

HWND APIUser32::GetShellWindow (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetShellWindow()");
  return GetShellWindow_();
}

WINBOOL APIUser32::RegisterShellHookWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterShellHookWindow()");
  return RegisterShellHookWindow_(hwnd);
}

WINBOOL APIUser32::DeregisterShellHookWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DeregisterShellHookWindow()");
  return DeregisterShellHookWindow_(hwnd);
}

WINBOOL APIUser32::EnumWindows (WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumWindows()");
  return EnumWindows_(lpEnumFunc, lParam);
}

WINBOOL APIUser32::EnumThreadWindows (DWORD dwThreadId, WNDENUMPROC lpfn, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumThreadWindows()");
  return EnumThreadWindows_(dwThreadId, lpfn, lParam);
}

int APIUser32::GetClassNameA (HWND hWnd, LPSTR lpClassName, int nMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassNameA()");
  return GetClassNameA_(hWnd, lpClassName, nMaxCount);
}

int APIUser32::GetClassNameW (HWND hWnd, LPWSTR lpClassName, int nMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetClassNameW()");
  return GetClassNameW_(hWnd, lpClassName, nMaxCount);
}

HWND APIUser32::GetTopWindow (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTopWindow()");
  return GetTopWindow_(hWnd);
}

DWORD APIUser32::GetWindowThreadProcessId (HWND hWnd, LPDWORD lpdwProcessId)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowThreadProcessId()");
  return GetWindowThreadProcessId_(hWnd, lpdwProcessId);
}

WINBOOL APIUser32::IsGUIThread (WINBOOL bConvert)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsGUIThread()");
  return IsGUIThread_(bConvert);
}

HWND APIUser32::GetLastActivePopup (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetLastActivePopup()");
  return GetLastActivePopup_(hWnd);
}

HWND APIUser32::GetWindow (HWND hWnd, UINT uCmd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindow()");
  return GetWindow_(hWnd, uCmd);
}

#ifdef STRICT

HHOOK APIUser32::SetWindowsHookA (int nFilterType, HOOKPROC pfnFilterProc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookA()");
  return SetWindowsHookA_(nFilterType, pfnFilterProc);
}

HHOOK APIUser32::SetWindowsHookW (int nFilterType, HOOKPROC pfnFilterProc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookW()");
  return SetWindowsHookW_(nFilterType, pfnFilterProc);
}

#else

HOOKPROC APIUser32::SetWindowsHookA (int nFilterType, HOOKPROC pfnFilterProc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookA()");
  return SetWindowsHookA_(nFilterType, pfnFilterProc);
}

HOOKPROC APIUser32::SetWindowsHookW (int nFilterType, HOOKPROC pfnFilterProc)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookW()");
  return SetWindowsHookW_(nFilterType, pfnFilterProc);
}

#endif

WINBOOL APIUser32::UnhookWindowsHook (int nCode, HOOKPROC pfnFilterProc)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnhookWindowsHook()");
  return UnhookWindowsHook_(nCode, pfnFilterProc);
}

HHOOK APIUser32::SetWindowsHookExA (int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookExA()");
  return SetWindowsHookExA_(idHook, lpfn, hmod, dwThreadId);
}

HHOOK APIUser32::SetWindowsHookExW (int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowsHookExW()");
  return SetWindowsHookExW_(idHook, lpfn, hmod, dwThreadId);
}

WINBOOL APIUser32::UnhookWindowsHookEx (HHOOK hhk)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnhookWindowsHookEx()");
  return UnhookWindowsHookEx_(hhk);
}

LRESULT APIUser32::CallNextHookEx (HHOOK hhk, int nCode, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CallNextHookEx()");
  return CallNextHookEx_(hhk, nCode, wParam, lParam);
}

WINBOOL APIUser32::CheckMenuRadioItem (HMENU hmenu, UINT first, UINT last, UINT check, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CheckMenuRadioItem()");
  return CheckMenuRadioItem_(hmenu, first, last, check, flags);
}

HBITMAP APIUser32::LoadBitmapA (HINSTANCE hInstance, LPCSTR lpBitmapName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadBitmapA()");
  return LoadBitmapA_(hInstance, lpBitmapName);
}

HBITMAP APIUser32::LoadBitmapW (HINSTANCE hInstance, LPCWSTR lpBitmapName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadBitmapW()");
  return LoadBitmapW_(hInstance, lpBitmapName);
}

HCURSOR APIUser32::LoadCursorA (HINSTANCE hInstance, LPCSTR lpCursorName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadCursorA()");
  return LoadCursorA_(hInstance, lpCursorName);
}

HCURSOR APIUser32::LoadCursorW (HINSTANCE hInstance, LPCWSTR lpCursorName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadCursorW()");
  return LoadCursorW_(hInstance, lpCursorName);
}

HCURSOR APIUser32::LoadCursorFromFileA (LPCSTR lpFileName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadCursorFromFileA()");
  return LoadCursorFromFileA_(lpFileName);
}

HCURSOR APIUser32::LoadCursorFromFileW (LPCWSTR lpFileName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadCursorFromFileW()");
  return LoadCursorFromFileW_(lpFileName);
}

HCURSOR APIUser32::CreateCursor (HINSTANCE hInst, int xHotSpot, int yHotSpot, int nWidth, int nHeight, CONST VOID * pvANDPlane, CONST VOID * pvXORPlane)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateCursor()");
  return CreateCursor_(hInst, xHotSpot, yHotSpot, nWidth, nHeight, pvANDPlane, pvXORPlane);
}

WINBOOL APIUser32::DestroyCursor (HCURSOR hCursor)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyCursor()");
  return DestroyCursor_(hCursor);
}

WINBOOL APIUser32::SetSystemCursor (HCURSOR hcur, DWORD id)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetSystemCursor()");
  return SetSystemCursor_(hcur, id);
}

HICON APIUser32::LoadIconA (HINSTANCE hInstance, LPCSTR lpIconName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadIconA()");
  return LoadIconA_(hInstance, lpIconName);
}

HICON APIUser32::LoadIconW (HINSTANCE hInstance, LPCWSTR lpIconName)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadIconW()");
  return LoadIconW_(hInstance, lpIconName);
}

UINT APIUser32::PrivateExtractIconsA (LPCSTR szFileName, int nIconIndex, int cxIcon, int cyIcon, HICON * phicon, UINT * piconid, UINT nIcons, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "PrivateExtractIconsA()");
  return PrivateExtractIconsA_(szFileName, nIconIndex, cxIcon, cyIcon, phicon, piconid, nIcons, flags);
}

UINT APIUser32::PrivateExtractIconsW (LPCWSTR szFileName, int nIconIndex, int cxIcon, int cyIcon, HICON * phicon, UINT * piconid, UINT nIcons, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "PrivateExtractIconsW()");
  return PrivateExtractIconsW_(szFileName, nIconIndex, cxIcon, cyIcon, phicon, piconid, nIcons, flags);
}

HICON APIUser32::CreateIcon (HINSTANCE hInstance, int nWidth, int nHeight, BYTE cPlanes, BYTE cBitsPixel, CONST BYTE * lpbANDbits, CONST BYTE * lpbXORbits)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateIcon()");
  return CreateIcon_(hInstance, nWidth, nHeight, cPlanes, cBitsPixel, lpbANDbits, lpbXORbits);
}

WINBOOL APIUser32::DestroyIcon (HICON hIcon)
{
  logging::log("wrapper", logging::LogLevel::debug, "DestroyIcon()");
  return DestroyIcon_(hIcon);
}

int APIUser32::LookupIconIdFromDirectory (PBYTE presbits, WINBOOL fIcon)
{
  logging::log("wrapper", logging::LogLevel::debug, "LookupIconIdFromDirectory()");
  return LookupIconIdFromDirectory_(presbits, fIcon);
}

int APIUser32::LookupIconIdFromDirectoryEx (PBYTE presbits, WINBOOL fIcon, int cxDesired, int cyDesired, UINT Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "LookupIconIdFromDirectoryEx()");
  return LookupIconIdFromDirectoryEx_(presbits, fIcon, cxDesired, cyDesired, Flags);
}

HICON APIUser32::CreateIconFromResource (PBYTE presbits, DWORD dwResSize, WINBOOL fIcon, DWORD dwVer)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateIconFromResource()");
  return CreateIconFromResource_(presbits, dwResSize, fIcon, dwVer);
}

HICON APIUser32::CreateIconFromResourceEx (PBYTE presbits, DWORD dwResSize, WINBOOL fIcon, DWORD dwVer, int cxDesired, int cyDesired, UINT Flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateIconFromResourceEx()");
  return CreateIconFromResourceEx_(presbits, dwResSize, fIcon, dwVer, cxDesired, cyDesired, Flags);
}

HANDLE APIUser32::LoadImageA (HINSTANCE hInst, LPCSTR name, UINT type, int cx, int cy, UINT fuLoad)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadImageA()");
  return LoadImageA_(hInst, name, type, cx, cy, fuLoad);
}

HANDLE APIUser32::LoadImageW (HINSTANCE hInst, LPCWSTR name, UINT type, int cx, int cy, UINT fuLoad)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadImageW()");
  return LoadImageW_(hInst, name, type, cx, cy, fuLoad);
}

HANDLE APIUser32::CopyImage (HANDLE h, UINT type, int cx, int cy, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CopyImage()");
  return CopyImage_(h, type, cx, cy, flags);
}

WINBOOL APIUser32::DrawIconEx (HDC hdc, int xLeft, int yTop, HICON hIcon, int cxWidth, int cyWidth, UINT istepIfAniCur, HBRUSH hbrFlickerFreeDraw, UINT diFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawIconEx()");
  return DrawIconEx_(hdc, xLeft, yTop, hIcon, cxWidth, cyWidth, istepIfAniCur, hbrFlickerFreeDraw, diFlags);
}

HICON APIUser32::CreateIconIndirect (PICONINFO piconinfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateIconIndirect()");
  return CreateIconIndirect_(piconinfo);
}

HICON APIUser32::CopyIcon (HICON hIcon)
{
  logging::log("wrapper", logging::LogLevel::debug, "CopyIcon()");
  return CopyIcon_(hIcon);
}

WINBOOL APIUser32::GetIconInfo (HICON hIcon, PICONINFO piconinfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetIconInfo()");
  return GetIconInfo_(hIcon, piconinfo);
}

WINBOOL APIUser32::GetIconInfoExA (HICON hicon, PICONINFOEXA piconinfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetIconInfoExA()");
  return GetIconInfoExA_(hicon, piconinfo);
}

WINBOOL APIUser32::GetIconInfoExW (HICON hicon, PICONINFOEXW piconinfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetIconInfoExW()");
  return GetIconInfoExW_(hicon, piconinfo);
}

int APIUser32::LoadStringA (HINSTANCE hInstance, UINT uID, LPSTR lpBuffer, int cchBufferMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadStringA()");
  return LoadStringA_(hInstance, uID, lpBuffer, cchBufferMax);
}

int APIUser32::LoadStringW (HINSTANCE hInstance, UINT uID, LPWSTR lpBuffer, int cchBufferMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadStringW()");
  return LoadStringW_(hInstance, uID, lpBuffer, cchBufferMax);
}

WINBOOL APIUser32::IsDialogMessageA (HWND hDlg, LPMSG lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsDialogMessageA()");
  return IsDialogMessageA_(hDlg, lpMsg);
}

WINBOOL APIUser32::IsDialogMessageW (HWND hDlg, LPMSG lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsDialogMessageW()");
  return IsDialogMessageW_(hDlg, lpMsg);
}

WINBOOL APIUser32::MapDialogRect (HWND hDlg, LPRECT lpRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "MapDialogRect()");
  return MapDialogRect_(hDlg, lpRect);
}

int APIUser32::DlgDirListA (HWND hDlg, LPSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT uFileType)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirListA()");
  return DlgDirListA_(hDlg, lpPathSpec, nIDListBox, nIDStaticPath, uFileType);
}

int APIUser32::DlgDirListW (HWND hDlg, LPWSTR lpPathSpec, int nIDListBox, int nIDStaticPath, UINT uFileType)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirListW()");
  return DlgDirListW_(hDlg, lpPathSpec, nIDListBox, nIDStaticPath, uFileType);
}

WINBOOL APIUser32::DlgDirSelectExA (HWND hwndDlg, LPSTR lpString, int chCount, int idListBox)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirSelectExA()");
  return DlgDirSelectExA_(hwndDlg, lpString, chCount, idListBox);
}

WINBOOL APIUser32::DlgDirSelectExW (HWND hwndDlg, LPWSTR lpString, int chCount, int idListBox)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirSelectExW()");
  return DlgDirSelectExW_(hwndDlg, lpString, chCount, idListBox);
}

int APIUser32::DlgDirListComboBoxA (HWND hDlg, LPSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT uFiletype)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirListComboBoxA()");
  return DlgDirListComboBoxA_(hDlg, lpPathSpec, nIDComboBox, nIDStaticPath, uFiletype);
}

int APIUser32::DlgDirListComboBoxW (HWND hDlg, LPWSTR lpPathSpec, int nIDComboBox, int nIDStaticPath, UINT uFiletype)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirListComboBoxW()");
  return DlgDirListComboBoxW_(hDlg, lpPathSpec, nIDComboBox, nIDStaticPath, uFiletype);
}

WINBOOL APIUser32::DlgDirSelectComboBoxExA (HWND hwndDlg, LPSTR lpString, int cchOut, int idComboBox)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirSelectComboBoxExA()");
  return DlgDirSelectComboBoxExA_(hwndDlg, lpString, cchOut, idComboBox);
}

WINBOOL APIUser32::DlgDirSelectComboBoxExW (HWND hwndDlg, LPWSTR lpString, int cchOut, int idComboBox)
{
  logging::log("wrapper", logging::LogLevel::debug, "DlgDirSelectComboBoxExW()");
  return DlgDirSelectComboBoxExW_(hwndDlg, lpString, cchOut, idComboBox);
}

int APIUser32::SetScrollInfo (HWND hwnd, int nBar, LPCSCROLLINFO lpsi, WINBOOL redraw)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetScrollInfo()");
  return SetScrollInfo_(hwnd, nBar, lpsi, redraw);
}

WINBOOL APIUser32::GetScrollInfo (HWND hwnd, int nBar, LPSCROLLINFO lpsi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetScrollInfo()");
  return GetScrollInfo_(hwnd, nBar, lpsi);
}

LRESULT APIUser32::DefFrameProcA (HWND hWnd, HWND hWndMDIClient, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefFrameProcA()");
  return DefFrameProcA_(hWnd, hWndMDIClient, uMsg, wParam, lParam);
}

LRESULT APIUser32::DefFrameProcW (HWND hWnd, HWND hWndMDIClient, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefFrameProcW()");
  return DefFrameProcW_(hWnd, hWndMDIClient, uMsg, wParam, lParam);
}

LRESULT APIUser32::DefMDIChildProcA (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefMDIChildProcA()");
  return DefMDIChildProcA_(hWnd, uMsg, wParam, lParam);
}

LRESULT APIUser32::DefMDIChildProcW (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefMDIChildProcW()");
  return DefMDIChildProcW_(hWnd, uMsg, wParam, lParam);
}

WINBOOL APIUser32::TranslateMDISysAccel (HWND hWndClient, LPMSG lpMsg)
{
  logging::log("wrapper", logging::LogLevel::debug, "TranslateMDISysAccel()");
  return TranslateMDISysAccel_(hWndClient, lpMsg);
}

UINT APIUser32::ArrangeIconicWindows (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "ArrangeIconicWindows()");
  return ArrangeIconicWindows_(hWnd);
}

HWND APIUser32::CreateMDIWindowA (LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateMDIWindowA()");
  return CreateMDIWindowA_(lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hInstance, lParam);
}

HWND APIUser32::CreateMDIWindowW (LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HINSTANCE hInstance, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "CreateMDIWindowW()");
  return CreateMDIWindowW_(lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hInstance, lParam);
}

WORD APIUser32::TileWindows (HWND hwndParent, UINT wHow, CONST RECT * lpRect, UINT cKids, const HWND * lpKids)
{
  logging::log("wrapper", logging::LogLevel::debug, "TileWindows()");
  return TileWindows_(hwndParent, wHow, lpRect, cKids, lpKids);
}

WORD APIUser32::CascadeWindows (HWND hwndParent, UINT wHow, CONST RECT * lpRect, UINT cKids, const HWND * lpKids)
{
  logging::log("wrapper", logging::LogLevel::debug, "CascadeWindows()");
  return CascadeWindows_(hwndParent, wHow, lpRect, cKids, lpKids);
}

WINBOOL APIUser32::WinHelpA (HWND hWndMain, LPCSTR lpszHelp, UINT uCommand, ULONG_PTR dwData)
{
  logging::log("wrapper", logging::LogLevel::debug, "WinHelpA()");
  return WinHelpA_(hWndMain, lpszHelp, uCommand, dwData);
}

WINBOOL APIUser32::WinHelpW (HWND hWndMain, LPCWSTR lpszHelp, UINT uCommand, ULONG_PTR dwData)
{
  logging::log("wrapper", logging::LogLevel::debug, "WinHelpW()");
  return WinHelpW_(hWndMain, lpszHelp, uCommand, dwData);
}

DWORD APIUser32::GetGuiResources (HANDLE hProcess, DWORD uiFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetGuiResources()");
  return GetGuiResources_(hProcess, uiFlags);
}

LONG APIUser32::ChangeDisplaySettingsA (LPDEVMODEA lpDevMode, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeDisplaySettingsA()");
  return ChangeDisplaySettingsA_(lpDevMode, dwFlags);
}

LONG APIUser32::ChangeDisplaySettingsW (LPDEVMODEW lpDevMode, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeDisplaySettingsW()");
  return ChangeDisplaySettingsW_(lpDevMode, dwFlags);
}

LONG APIUser32::ChangeDisplaySettingsExA (LPCSTR lpszDeviceName, LPDEVMODEA lpDevMode, HWND hwnd, DWORD dwflags, LPVOID lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeDisplaySettingsExA()");
  return ChangeDisplaySettingsExA_(lpszDeviceName, lpDevMode, hwnd, dwflags, lParam);
}

LONG APIUser32::ChangeDisplaySettingsExW (LPCWSTR lpszDeviceName, LPDEVMODEW lpDevMode, HWND hwnd, DWORD dwflags, LPVOID lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeDisplaySettingsExW()");
  return ChangeDisplaySettingsExW_(lpszDeviceName, lpDevMode, hwnd, dwflags, lParam);
}

WINBOOL APIUser32::EnumDisplaySettingsA (LPCSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEA lpDevMode)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplaySettingsA()");
  return EnumDisplaySettingsA_(lpszDeviceName, iModeNum, lpDevMode);
}

WINBOOL APIUser32::EnumDisplaySettingsW (LPCWSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEW lpDevMode)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplaySettingsW()");
  return EnumDisplaySettingsW_(lpszDeviceName, iModeNum, lpDevMode);
}

WINBOOL APIUser32::EnumDisplaySettingsExA (LPCSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEA lpDevMode, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplaySettingsExA()");
  return EnumDisplaySettingsExA_(lpszDeviceName, iModeNum, lpDevMode, dwFlags);
}

WINBOOL APIUser32::EnumDisplaySettingsExW (LPCWSTR lpszDeviceName, DWORD iModeNum, LPDEVMODEW lpDevMode, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplaySettingsExW()");
  return EnumDisplaySettingsExW_(lpszDeviceName, iModeNum, lpDevMode, dwFlags);
}

WINBOOL APIUser32::EnumDisplayDevicesA (LPCSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEA lpDisplayDevice, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplayDevicesA()");
  return EnumDisplayDevicesA_(lpDevice, iDevNum, lpDisplayDevice, dwFlags);
}

WINBOOL APIUser32::EnumDisplayDevicesW (LPCWSTR lpDevice, DWORD iDevNum, PDISPLAY_DEVICEW lpDisplayDevice, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplayDevicesW()");
  return EnumDisplayDevicesW_(lpDevice, iDevNum, lpDisplayDevice, dwFlags);
}

LONG APIUser32::GetDisplayConfigBufferSizes (UINT32 flags, UINT32 * numPathArrayElements, UINT32 * numModeInfoArrayElements)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDisplayConfigBufferSizes()");
  return GetDisplayConfigBufferSizes_(flags, numPathArrayElements, numModeInfoArrayElements);
}

LONG APIUser32::SetDisplayConfig (UINT32 numPathArrayElements, DISPLAYCONFIG_PATH_INFO * pathArray, UINT32 numModeInfoArrayElements, DISPLAYCONFIG_MODE_INFO * modeInfoArray, UINT32 flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDisplayConfig()");
  return SetDisplayConfig_(numPathArrayElements, pathArray, numModeInfoArrayElements, modeInfoArray, flags);
}

LONG APIUser32::QueryDisplayConfig (UINT32 flags, UINT32 * numPathArrayElements, DISPLAYCONFIG_PATH_INFO * pathArray, UINT32 * numModeInfoArrayElements, DISPLAYCONFIG_MODE_INFO * modeInfoArray, DISPLAYCONFIG_TOPOLOGY_ID * currentTopologyId)
{
  logging::log("wrapper", logging::LogLevel::debug, "QueryDisplayConfig()");
  return QueryDisplayConfig_(flags, numPathArrayElements, pathArray, numModeInfoArrayElements, modeInfoArray, currentTopologyId);
}

LONG APIUser32::DisplayConfigGetDeviceInfo (DISPLAYCONFIG_DEVICE_INFO_HEADER * requestPacket)
{
  logging::log("wrapper", logging::LogLevel::debug, "DisplayConfigGetDeviceInfo()");
  return DisplayConfigGetDeviceInfo_(requestPacket);
}

LONG APIUser32::DisplayConfigSetDeviceInfo (DISPLAYCONFIG_DEVICE_INFO_HEADER * setPacket)
{
  logging::log("wrapper", logging::LogLevel::debug, "DisplayConfigSetDeviceInfo()");
  return DisplayConfigSetDeviceInfo_(setPacket);
}

WINBOOL APIUser32::SystemParametersInfoA (UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
  logging::log("wrapper", logging::LogLevel::debug, "SystemParametersInfoA()");
  return SystemParametersInfoA_(uiAction, uiParam, pvParam, fWinIni);
}

WINBOOL APIUser32::SystemParametersInfoW (UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni)
{
  logging::log("wrapper", logging::LogLevel::debug, "SystemParametersInfoW()");
  return SystemParametersInfoW_(uiAction, uiParam, pvParam, fWinIni);
}

VOID APIUser32::SetDebugErrorLevel (DWORD dwLevel)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDebugErrorLevel()");
  SetDebugErrorLevel_(dwLevel);
}

VOID APIUser32::SetLastErrorEx (DWORD dwErrCode, DWORD dwType)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetLastErrorEx()");
  SetLastErrorEx_(dwErrCode, dwType);
}

int APIUser32::InternalGetWindowText (HWND hWnd, LPWSTR pString, int cchMaxCount)
{
  logging::log("wrapper", logging::LogLevel::debug, "InternalGetWindowText()");
  return InternalGetWindowText_(hWnd, pString, cchMaxCount);
}

WINBOOL APIUser32::CancelShutdown (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "CancelShutdown()");
  return CancelShutdown_();
}

HMONITOR APIUser32::MonitorFromPoint (POINT pt, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "MonitorFromPoint()");
  return MonitorFromPoint_(pt, dwFlags);
}

HMONITOR APIUser32::MonitorFromRect (LPCRECT lprc, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "MonitorFromRect()");
  return MonitorFromRect_(lprc, dwFlags);
}

HMONITOR APIUser32::MonitorFromWindow (HWND hwnd, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "MonitorFromWindow()");
  return MonitorFromWindow_(hwnd, dwFlags);
}

WINBOOL APIUser32::EndTask (HWND hWnd, WINBOOL fShutDown, WINBOOL fForce)
{
  logging::log("wrapper", logging::LogLevel::debug, "EndTask()");
  return EndTask_(hWnd, fShutDown, fForce);
}

WINBOOL APIUser32::SoundSentry (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "SoundSentry()");
  return SoundSentry_();
}

WINBOOL APIUser32::GetMonitorInfoA (HMONITOR hMonitor, LPMONITORINFO lpmi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMonitorInfoA()");
  return GetMonitorInfoA_(hMonitor, lpmi);
}

WINBOOL APIUser32::GetMonitorInfoW (HMONITOR hMonitor, LPMONITORINFO lpmi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMonitorInfoW()");
  return GetMonitorInfoW_(hMonitor, lpmi);
}

WINBOOL APIUser32::EnumDisplayMonitors (HDC hdc, LPCRECT lprcClip, MONITORENUMPROC lpfnEnum, LPARAM dwData)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnumDisplayMonitors()");
  return EnumDisplayMonitors_(hdc, lprcClip, lpfnEnum, dwData);
}

VOID APIUser32::NotifyWinEvent (DWORD event, HWND hwnd, LONG idObject, LONG idChild)
{
  logging::log("wrapper", logging::LogLevel::debug, "NotifyWinEvent()");
  NotifyWinEvent_(event, hwnd, idObject, idChild);
}

HWINEVENTHOOK APIUser32::SetWinEventHook (DWORD eventMin, DWORD eventMax, HMODULE hmodWinEventProc, WINEVENTPROC pfnWinEventProc, DWORD idProcess, DWORD idThread, DWORD dwFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWinEventHook()");
  return SetWinEventHook_(eventMin, eventMax, hmodWinEventProc, pfnWinEventProc, idProcess, idThread, dwFlags);
}

WINBOOL APIUser32::IsWinEventHookInstalled (DWORD event)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWinEventHookInstalled()");
  return IsWinEventHookInstalled_(event);
}

WINBOOL APIUser32::UnhookWinEvent (HWINEVENTHOOK hWinEventHook)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnhookWinEvent()");
  return UnhookWinEvent_(hWinEventHook);
}

WINBOOL APIUser32::GetGUIThreadInfo (DWORD idThread, PGUITHREADINFO pgui)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetGUIThreadInfo()");
  return GetGUIThreadInfo_(idThread, pgui);
}

WINBOOL APIUser32::BlockInput (WINBOOL fBlockIt)
{
  logging::log("wrapper", logging::LogLevel::debug, "BlockInput()");
  return BlockInput_(fBlockIt);
}

UINT APIUser32::GetWindowModuleFileNameA (HWND hwnd, LPSTR pszFileName, UINT cchFileNameMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowModuleFileNameA()");
  return GetWindowModuleFileNameA_(hwnd, pszFileName, cchFileNameMax);
}

UINT APIUser32::GetWindowModuleFileNameW (HWND hwnd, LPWSTR pszFileName, UINT cchFileNameMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowModuleFileNameW()");
  return GetWindowModuleFileNameW_(hwnd, pszFileName, cchFileNameMax);
}

WINBOOL APIUser32::SetProcessDPIAware (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProcessDPIAware()");
  return SetProcessDPIAware_();
}

WINBOOL APIUser32::IsProcessDPIAware (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsProcessDPIAware()");
  return IsProcessDPIAware_();
}

WINBOOL APIUser32::GetCursorInfo (PCURSORINFO pci)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCursorInfo()");
  return GetCursorInfo_(pci);
}

WINBOOL APIUser32::GetWindowInfo (HWND hwnd, PWINDOWINFO pwi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowInfo()");
  return GetWindowInfo_(hwnd, pwi);
}

WINBOOL APIUser32::GetTitleBarInfo (HWND hwnd, PTITLEBARINFO pti)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTitleBarInfo()");
  return GetTitleBarInfo_(hwnd, pti);
}

WINBOOL APIUser32::GetMenuBarInfo (HWND hwnd, LONG idObject, LONG idItem, PMENUBARINFO pmbi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetMenuBarInfo()");
  return GetMenuBarInfo_(hwnd, idObject, idItem, pmbi);
}

WINBOOL APIUser32::GetScrollBarInfo (HWND hwnd, LONG idObject, PSCROLLBARINFO psbi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetScrollBarInfo()");
  return GetScrollBarInfo_(hwnd, idObject, psbi);
}

WINBOOL APIUser32::GetComboBoxInfo (HWND hwndCombo, PCOMBOBOXINFO pcbi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetComboBoxInfo()");
  return GetComboBoxInfo_(hwndCombo, pcbi);
}

HWND APIUser32::GetAncestor (HWND hwnd, UINT gaFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAncestor()");
  return GetAncestor_(hwnd, gaFlags);
}

HWND APIUser32::RealChildWindowFromPoint (HWND hwndParent, POINT ptParentClientCoords)
{
  logging::log("wrapper", logging::LogLevel::debug, "RealChildWindowFromPoint()");
  return RealChildWindowFromPoint_(hwndParent, ptParentClientCoords);
}

UINT APIUser32::RealGetWindowClassA (HWND hwnd, LPSTR ptszClassName, UINT cchClassNameMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "RealGetWindowClassA()");
  return RealGetWindowClassA_(hwnd, ptszClassName, cchClassNameMax);
}

UINT APIUser32::RealGetWindowClassW (HWND hwnd, LPWSTR ptszClassName, UINT cchClassNameMax)
{
  logging::log("wrapper", logging::LogLevel::debug, "RealGetWindowClassW()");
  return RealGetWindowClassW_(hwnd, ptszClassName, cchClassNameMax);
}

WINBOOL APIUser32::GetAltTabInfoA (HWND hwnd, int iItem, PALTTABINFO pati, LPSTR pszItemText, UINT cchItemText)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAltTabInfoA()");
  return GetAltTabInfoA_(hwnd, iItem, pati, pszItemText, cchItemText);
}

WINBOOL APIUser32::GetAltTabInfoW (HWND hwnd, int iItem, PALTTABINFO pati, LPWSTR pszItemText, UINT cchItemText)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAltTabInfoW()");
  return GetAltTabInfoW_(hwnd, iItem, pati, pszItemText, cchItemText);
}

DWORD APIUser32::GetListBoxInfo (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetListBoxInfo()");
  return GetListBoxInfo_(hwnd);
}

WINBOOL APIUser32::LockWorkStation (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "LockWorkStation()");
  return LockWorkStation_();
}

WINBOOL APIUser32::UserHandleGrantAccess (HANDLE hUserHandle, HANDLE hJob, WINBOOL bGrant)
{
  logging::log("wrapper", logging::LogLevel::debug, "UserHandleGrantAccess()");
  return UserHandleGrantAccess_(hUserHandle, hJob, bGrant);
}

UINT APIUser32::GetRawInputData (HRAWINPUT hRawInput, UINT uiCommand, LPVOID pData, PUINT pcbSize, UINT cbSizeHeader)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawInputData");
  return GetRawInputData_(hRawInput, uiCommand, pData, pcbSize, cbSizeHeader);
}

UINT APIUser32::GetRawInputDeviceInfoA (HANDLE hDevice, UINT uiCommand, LPVOID pData, PUINT pcbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawInputDeviceInfoA");
  return GetRawInputDeviceInfoA_(hDevice, uiCommand, pData, pcbSize);
}

UINT APIUser32::GetRawInputDeviceInfoW (HANDLE hDevice, UINT uiCommand, LPVOID pData, PUINT pcbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawInputDeviceInfoW");
  return GetRawInputDeviceInfoW_(hDevice, uiCommand, pData, pcbSize);
}

UINT APIUser32::GetRawInputBuffer (PRAWINPUT pData, PUINT pcbSize, UINT cbSizeHeader)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawInputBuffer");
  return GetRawInputBuffer_(pData, pcbSize, cbSizeHeader);
}

WINBOOL APIUser32::RegisterRawInputDevices (PCRAWINPUTDEVICE pRawInputDevices, UINT uiNumDevices, UINT cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterRawInputDevices");
  return RegisterRawInputDevices_(pRawInputDevices, uiNumDevices, cbSize);
}

UINT APIUser32::GetRegisteredRawInputDevices (PRAWINPUTDEVICE pRawInputDevices, PUINT puiNumDevices, UINT cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRegisteredRawInputDevices");
  return GetRegisteredRawInputDevices_(pRawInputDevices, puiNumDevices, cbSize);
}

UINT APIUser32::GetRawInputDeviceList (PRAWINPUTDEVICELIST pRawInputDeviceList, PUINT puiNumDevices, UINT cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "APIUser32::GetRawInputDeviceList()");
  return GetRawInputDeviceList_(pRawInputDeviceList, puiNumDevices, cbSize);
}

LRESULT APIUser32::DefRawInputProc (PRAWINPUT * paRawInput, INT nInput, UINT cbSizeHeader)
{
  logging::log("wrapper", logging::LogLevel::debug, "DefRawInputProc");
  return DefRawInputProc_(paRawInput, nInput, cbSizeHeader);
}

WINBOOL APIUser32::GetPointerDevices (UINT32 * deviceCount, POINTER_DEVICE_INFO * pointerDevices)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerDevices()");
  return GetPointerDevices_(deviceCount, pointerDevices);
}

WINBOOL APIUser32::GetPointerDevice (HANDLE device, POINTER_DEVICE_INFO * pointerDevice)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerDevice()");
  return GetPointerDevice_(device, pointerDevice);
}

WINBOOL APIUser32::GetPointerDeviceProperties (HANDLE device, UINT32 * propertyCount, POINTER_DEVICE_PROPERTY * pointerProperties)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerDeviceProperties()");
  return GetPointerDeviceProperties_(device, propertyCount, pointerProperties);
}

WINBOOL APIUser32::RegisterPointerDeviceNotifications (HWND window, WINBOOL notifyRange)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterPointerDeviceNotifications()");
  return RegisterPointerDeviceNotifications_(window, notifyRange);
}

WINBOOL APIUser32::GetPointerDeviceRects (HANDLE device, RECT * pointerDeviceRect, RECT * displayRect)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerDeviceRects()");
  return GetPointerDeviceRects_(device, pointerDeviceRect, displayRect);
}

WINBOOL APIUser32::GetPointerDeviceCursors (HANDLE device, UINT32 * cursorCount, POINTER_DEVICE_CURSOR_INFO * deviceCursors)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerDeviceCursors()");
  return GetPointerDeviceCursors_(device, cursorCount, deviceCursors);
}

WINBOOL APIUser32::GetRawPointerDeviceData (UINT32 pointerId, UINT32 historyCount, UINT32 propertiesCount, POINTER_DEVICE_PROPERTY * pProperties, LONG * pValues)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetRawPointerDeviceData()");
  return GetRawPointerDeviceData_(pointerId, historyCount, propertiesCount, pProperties, pValues);
}

WINBOOL APIUser32::ChangeWindowMessageFilter (UINT message, DWORD dwFlag)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeWindowMessageFilter()");
  return ChangeWindowMessageFilter_(message, dwFlag);
}

WINBOOL APIUser32::ChangeWindowMessageFilterEx (HWND hwnd, UINT message, DWORD action, PCHANGEFILTERSTRUCT pChangeFilterStruct)
{
  logging::log("wrapper", logging::LogLevel::debug, "ChangeWindowMessageFilterEx()");
  return ChangeWindowMessageFilterEx_(hwnd, message, action, pChangeFilterStruct);
}

WINBOOL APIUser32::GetGestureInfo (HGESTUREINFO hGestureInfo, PGESTUREINFO pGestureInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetGestureInfo()");
  return GetGestureInfo_(hGestureInfo, pGestureInfo);
}

WINBOOL APIUser32::GetGestureExtraArgs (HGESTUREINFO hGestureInfo, UINT cbExtraArgs, PBYTE pExtraArgs)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetGestureExtraArgs()");
  return GetGestureExtraArgs_(hGestureInfo, cbExtraArgs, pExtraArgs);
}

WINBOOL APIUser32::CloseGestureInfoHandle (HGESTUREINFO hGestureInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "CloseGestureInfoHandle()");
  return CloseGestureInfoHandle_(hGestureInfo);
}

WINBOOL APIUser32::SetGestureConfig (HWND hwnd, DWORD dwReserved, UINT cIDs, PGESTURECONFIG pGestureConfig, UINT cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetGestureConfig()");
  return SetGestureConfig_(hwnd, dwReserved, cIDs, pGestureConfig, cbSize);
}

WINBOOL APIUser32::GetGestureConfig (HWND hwnd, DWORD dwReserved, DWORD dwFlags, PUINT pcIDs, PGESTURECONFIG pGestureConfig, UINT cbSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetGestureConfig()");
  return GetGestureConfig_(hwnd, dwReserved, dwFlags, pcIDs, pGestureConfig, cbSize);
}

WINBOOL APIUser32::ShutdownBlockReasonCreate (HWND hWnd, LPCWSTR pwszReason)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShutdownBlockReasonCreate()");
  return ShutdownBlockReasonCreate_(hWnd, pwszReason);
}

WINBOOL APIUser32::ShutdownBlockReasonQuery (HWND hWnd, LPWSTR pwszBuff, DWORD * pcchBuff)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShutdownBlockReasonQuery()");
  return ShutdownBlockReasonQuery_(hWnd, pwszBuff, pcchBuff);
}

WINBOOL APIUser32::ShutdownBlockReasonDestroy (HWND hWnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "ShutdownBlockReasonDestroy()");
  return ShutdownBlockReasonDestroy_(hWnd);
}

WINBOOL APIUser32::GetCurrentInputMessageSource (INPUT_MESSAGE_SOURCE * inputMessageSource)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCurrentInputMessageSource()");
  return GetCurrentInputMessageSource_(inputMessageSource);
}

WINBOOL APIUser32::GetCIMSSM (INPUT_MESSAGE_SOURCE * inputMessageSource)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCIMSSM()");
  return GetCIMSSM_(inputMessageSource);
}

WINBOOL APIUser32::GetAutoRotationState (PAR_STATE pState)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAutoRotationState()");
  return GetAutoRotationState_(pState);
}

WINBOOL APIUser32::GetDisplayAutoRotationPreferences (ORIENTATION_PREFERENCE * pOrientation)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDisplayAutoRotationPreferences()");
  return GetDisplayAutoRotationPreferences_(pOrientation);
}

WINBOOL APIUser32::GetDisplayAutoRotationPreferencesByProcessId (DWORD dwProcessId, ORIENTATION_PREFERENCE * pOrientation, WINBOOL * fRotateScreen)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDisplayAutoRotationPreferencesByProcessId()");
  return GetDisplayAutoRotationPreferencesByProcessId_(dwProcessId, pOrientation, fRotateScreen);
}

WINBOOL APIUser32::SetDisplayAutoRotationPreferences (ORIENTATION_PREFERENCE orientation)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDisplayAutoRotationPreferences()");
  return SetDisplayAutoRotationPreferences_(orientation);
}

WINBOOL APIUser32::IsImmersiveProcess (HANDLE hProcess)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsImmersiveProcess()");
  return IsImmersiveProcess_(hProcess);
}

WINBOOL APIUser32::SetProcessRestrictionExemption (WINBOOL fEnableExemption)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProcessRestrictionExemption()");
  return SetProcessRestrictionExemption_(fEnableExemption);
}

WINBOOL APIUser32::GetPointerInputTransform (UINT32 pointerId, UINT32 historyCount, UINT32 * inputTransform)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetPointerInputTransform()");
  return GetPointerInputTransform_(pointerId, historyCount, inputTransform);
}

WINBOOL APIUser32::IsMousePointerEnabled (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsMousePointerEnabled()");
  return IsMousePointerEnabled_();
}

UINT_PTR APIUser32::SetSystemTimer (HWND hwnd, UINT_PTR id, UINT timeout, void * unknown)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetSystemTimer()");
  return SetSystemTimer_(hwnd, id, timeout, unknown);
}

DWORD APIUser32::CalcMenuBar (HWND hwnd, DWORD left, DWORD right, DWORD top, RECT * rect)
{
  logging::log("wrapper", logging::LogLevel::debug, "CalcMenuBar()");
  return CalcMenuBar_(hwnd, left, right, top, rect);
}

UINT APIUser32::WINNLSGetIMEHotkey (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "WINNLSGetIMEHotkey()");
  return WINNLSGetIMEHotkey_(hwnd);
}

HWND APIUser32::GetTaskmanWindow (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetTaskmanWindow()");
  return GetTaskmanWindow_();
}

BOOL APIUser32::DdeDisconnect (HCONV hConv)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeDisconnect()");
  return DdeDisconnect_(hConv);
}

HSZ APIUser32::DdeCreateStringHandleA (DWORD idInst, LPCSTR psz, INT codepage)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeCreateStringHandleA()");
  return DdeCreateStringHandleA_(idInst, psz, codepage);
}

BOOL APIUser32::SetProcessDpiAwarenessInternal (DPI_AWARENESS awareness)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProcessDpiAwarenessInternal()");
  return SetProcessDpiAwarenessInternal_(awareness);
}

BOOL APIUser32::SetDeskWallpaper (const char * filename)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetDeskWallpaper()");
  return SetDeskWallpaper_(filename);
}

NTSTATUS APIUser32::User32ImmTranslateMessage (void * args, ULONG size)
{
  logging::log("wrapper", logging::LogLevel::debug, "User32ImmTranslateMessage()");
  return User32ImmTranslateMessage_(args, size);
}

DWORD APIUser32::DdeGetData (HDDEDATA hData, LPBYTE pDst, DWORD cbMax, DWORD cbOff)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeGetData()");
  return DdeGetData_(hData, pDst, cbMax, cbOff);
}

DWORD_PTR APIUser32::SetSysColorsTemp (const COLORREF * pPens, const HBRUSH * pBrushes, DWORD_PTR n)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetSysColorsTemp()");
  return SetSysColorsTemp_(pPens, pBrushes, n);
}

LRESULT APIUser32::StaticWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "StaticWndProcW()");
  return StaticWndProcW_(hwnd, msg, wParam, lParam);
}

LPBYTE APIUser32::DdeAccessData (HDDEDATA hData, LPDWORD pcbDataSize)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeAccessData()");
  return DdeAccessData_(hData, pcbDataSize);
}

BOOL APIUser32::DdeUnaccessData (HDDEDATA hData)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeUnaccessData()");
  return DdeUnaccessData_(hData);
}

UINT APIUser32::DdeInitializeA (LPDWORD pidInst, PFNCALLBACK pfnCallback, DWORD afCmd, DWORD ulRes)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeInitializeA()");
  return DdeInitializeA_(pidInst, pfnCallback, afCmd, ulRes);
}

UINT APIUser32::DdeInitializeW (LPDWORD pidInst, PFNCALLBACK pfnCallback, DWORD afCmd, DWORD ulRes)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeInitializeW()");
  return DdeInitializeW_(pidInst, pfnCallback, afCmd, ulRes);
}

BOOL APIUser32::DdeUninitialize (DWORD idInst)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeUninitialize()");
  return DdeUninitialize_(idInst);
}

VOID APIUser32::LoadLocalFonts (VOID)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadLocalFonts()");
  LoadLocalFonts_();
}

LPSTR APIUser32::CharPrevExW (WORD codepage, LPCWSTR start, LPCWSTR ptr, DWORD flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharPrevExW()");
  return CharPrevExW_(codepage, start, ptr, flags);
}

HWND APIUser32::GetProgmanWindow (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetProgmanWindow()");
  return GetProgmanWindow_();
}

DPI_AWARENESS_CONTEXT APIUser32::SetThreadDpiAwarenessContext (DPI_AWARENESS_CONTEXT context)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetThreadDpiAwarenessContext()");
  return SetThreadDpiAwarenessContext_(context);
}

LPARAM APIUser32::PackDDElParam (UINT msg, UINT_PTR uiLo, UINT_PTR uiHi)
{
  logging::log("wrapper", logging::LogLevel::debug, "PackDDElParam()");
  return PackDDElParam_(msg, uiLo, uiHi);
}

BOOL APIUser32::DdeFreeDataHandle (HDDEDATA hData)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeFreeDataHandle()");
  return DdeFreeDataHandle_(hData);
}

BOOL APIUser32::AlignRects (LPRECT rect, DWORD b, DWORD c, DWORD d)
{
  logging::log("wrapper", logging::LogLevel::debug, "AlignRects()");
  return AlignRects_(rect, b, c, d);
}

DWORD APIUser32::DdeQueryStringW (DWORD idInst, HSZ hsz, LPWSTR psz, DWORD cchMax, INT iCodePage)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeQueryStringW()");
  return DdeQueryStringW_(idInst, hsz, psz, cchMax, iCodePage);
}

DWORD APIUser32::SetLogonNotifyWindow (HWINSTA hwinsta, HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetLogonNotifyWindow()");
  return SetLogonNotifyWindow_(hwinsta, hwnd);
}

HCURSOR APIUser32::GetCursorFrameInfo (HCURSOR handle, DWORD reserved, DWORD istep, DWORD * rate, DWORD * steps)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetCursorFrameInfo()");
  return GetCursorFrameInfo_(handle, reserved, istep, rate, steps);
}

DWORD APIUser32::DdeQueryStringA (DWORD idInst, HSZ hsz, LPSTR psz, DWORD cchMax, INT iCodePage)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeQueryStringA()");
  return DdeQueryStringA_(idInst, hsz, psz, cchMax, iCodePage);
}

BOOL APIUser32::DdeSetQualityOfService (HWND hwndClient, const SECURITY_QUALITY_OF_SERVICE * pqosNew, PSECURITY_QUALITY_OF_SERVICE pqosPrev)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeSetQualityOfService()");
  return DdeSetQualityOfService_(hwndClient, pqosNew, pqosPrev);
}

UINT APIUser32::DdeGetLastError (DWORD idInst)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeGetLastError()");
  return DdeGetLastError_(idInst);
}

LRESULT APIUser32::ComboWndProcA (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ComboWndProcA()");
  return ComboWndProcA_(hwnd, message, wParam, lParam);
}

BOOL APIUser32::DdeDisconnectList (HCONVLIST hConvList)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeDisconnectList()");
  return DdeDisconnectList_(hConvList);
}

LRESULT APIUser32::SendIMEMessageExA (HWND hwnd, LPARAM lparam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendIMEMessageExA()");
  return SendIMEMessageExA_(hwnd, lparam);
}

INT APIUser32::DdeCmpStringHandles (HSZ hsz1, HSZ hsz2)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeCmpStringHandles()");
  return DdeCmpStringHandles_(hsz1, hsz2);
}

DWORD APIUser32::RegisterTasklist (DWORD x)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterTasklist()");
  return RegisterTasklist_(x);
}

LRESULT APIUser32::IconTitleWndProc (HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "IconTitleWndProc()");
  return IconTitleWndProc_(hWnd, msg, wParam, lParam);
}

LRESULT APIUser32::SendIMEMessageExW (HWND hwnd, LPARAM lparam)
{
  logging::log("wrapper", logging::LogLevel::debug, "SendIMEMessageExW()");
  return SendIMEMessageExW_(hwnd, lparam);
}

LRESULT APIUser32::ComboWndProcW (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ComboWndProcW()");
  return ComboWndProcW_(hwnd, message, wParam, lParam);
}

HCONVLIST APIUser32::DdeConnectList (DWORD idInst, HSZ hszService, HSZ hszTopic, HCONVLIST hConvList, PCONVCONTEXT pCC)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeConnectList()");
  return DdeConnectList_(idInst, hszService, hszTopic, hConvList, pCC);
}

HCONV APIUser32::DdeQueryNextServer (HCONVLIST hConvList, HCONV hConvPrev)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeQueryNextServer()");
  return DdeQueryNextServer_(hConvList, hConvPrev);
}

BOOL APIUser32::RegisterUserApiHook (const struct user_api_hook * new_hook, struct user_api_hook * old_hook)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterUserApiHook()");
  return RegisterUserApiHook_(new_hook, old_hook);
}

void APIUser32::UnregisterUserApiHook (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnregisterUserApiHook()");
  UnregisterUserApiHook_();
}

LRESULT APIUser32::StaticWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "StaticWndProcA()");
  return StaticWndProcA_(hwnd, msg, wParam, lParam);
}

LRESULT APIUser32::MDIClientWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "MDIClientWndProcW()");
  return MDIClientWndProcW_(hwnd, msg, wParam, lParam);
}

BOOL APIUser32::DdeKeepStringHandle (DWORD idInst, HSZ hsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeKeepStringHandle()");
  return DdeKeepStringHandle_(idInst, hsz);
}

DWORD APIUser32::GetAppCompatFlags (HTASK hTask)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAppCompatFlags()");
  return GetAppCompatFlags_(hTask);
}

HWND APIUser32::SetProgmanWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetProgmanWindow()");
  return SetProgmanWindow_(hwnd);
}

BOOL APIUser32::DdeEnableCallback (DWORD idInst, HCONV hConv, UINT wCmd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeEnableCallback()");
  return DdeEnableCallback_(idInst, hConv, wCmd);
}

DPI_HOSTING_BEHAVIOR APIUser32::GetThreadDpiHostingBehavior (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetThreadDpiHostingBehavior()");
  return GetThreadDpiHostingBehavior_();
}

LRESULT APIUser32::MDIClientWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "MDIClientWndProcA()");
  return MDIClientWndProcA_(hwnd, msg, wParam, lParam);
}

LRESULT APIUser32::EditWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EditWndProcW()");
  return EditWndProcW_(hwnd, msg, wParam, lParam);
}

LRESULT APIUser32::ButtonWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ButtonWndProcW()");
  return ButtonWndProcW_(hwnd, msg, wParam, lParam);
}

HWND APIUser32::SetTaskmanWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetTaskmanWindow()");
  return SetTaskmanWindow_(hwnd);
}

BOOL APIUser32::DdeImpersonateClient (HCONV hConv)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeImpersonateClient()");
  return DdeImpersonateClient_(hConv);
}

UINT APIUser32::DdeQueryConvInfo (HCONV hConv, DWORD id, PCONVINFO lpConvInfo)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeQueryConvInfo()");
  return DdeQueryConvInfo_(hConv, id, lpConvInfo);
}

void APIUser32::CalcChildScroll (HWND hwnd, INT scroll)
{
  logging::log("wrapper", logging::LogLevel::debug, "CalcChildScroll()");
  CalcChildScroll_(hwnd, scroll);
}

HCONV APIUser32::DdeConnect (DWORD idInst, HSZ hszService, HSZ hszTopic, PCONVCONTEXT pCC)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeConnect()");
  return DdeConnect_(idInst, hszService, hszTopic, pCC);
}

HCONV APIUser32::DdeReconnect (HCONV hConv)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeReconnect()");
  return DdeReconnect_(hConv);
}

LPWSTR APIUser32::CharNextExW (WORD codepage, LPCWSTR ptr, DWORD flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CharNextExW()");
  return CharNextExW_(codepage, ptr, flags);
}

LRESULT APIUser32::EditWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "EditWndProcA()");
  return EditWndProcA_(hwnd, msg, wParam, lParam);
}

BOOL APIUser32::GetProcessDpiAwarenessInternal (HANDLE process, DPI_AWARENESS * awareness)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetProcessDpiAwarenessInternal()");
  return GetProcessDpiAwarenessInternal_(process, awareness);
}

void APIUser32::RegisterSystemThread (DWORD flags, DWORD reserved)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterSystemThread()");
  RegisterSystemThread_(flags, reserved);
}

BOOL APIUser32::SetWindowCompositionAttribute (HWND hwnd, WINDOWCOMPOSITIONATTRIBDATA const * pwcad)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowCompositionAttribute()");
  return SetWindowCompositionAttribute_(hwnd, pwcad);
}

HDDEDATA APIUser32::DdeClientTransaction (LPBYTE pData, DWORD cbData, HCONV hConv, HSZ hszItem, UINT wFmt, UINT wType, DWORD dwTimeout, LPDWORD pdwResult)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeClientTransaction()");
  return DdeClientTransaction_(pData, cbData, hConv, hszItem, wFmt, wType, dwTimeout, pdwResult);
}

BOOL APIUser32::DdeAbandonTransaction (DWORD idInst, HCONV hConv, DWORD idTransaction)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeAbandonTransaction()");
  return DdeAbandonTransaction_(idInst, hConv, idTransaction);
}

LRESULT APIUser32::ScrollBarWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollBarWndProcA()");
  return ScrollBarWndProcA_(hwnd, msg, wParam, lParam);
}

HKL APIUser32::LoadKeyboardLayoutEx (HKL layout, const WCHAR * name, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "LoadKeyboardLayoutEx()");
  return LoadKeyboardLayoutEx_(layout, name, flags);
}

int APIUser32::RegisterServicesProcess (DWORD ServicesProcessId)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterServicesProcess()");
  return RegisterServicesProcess_(ServicesProcessId);
}

HDDEDATA APIUser32::DdeCreateDataHandle (DWORD idInst, LPBYTE pSrc, DWORD cb, DWORD cbOff, HSZ hszItem, UINT wFmt, UINT afCmd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeCreateDataHandle()");
  return DdeCreateDataHandle_(idInst, pSrc, cb, cbOff, hszItem, wFmt, afCmd);
}

HDDEDATA APIUser32::DdeAddData (HDDEDATA hData, LPBYTE pSrc, DWORD cb, DWORD cbOff)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeAddData()");
  return DdeAddData_(hData, pSrc, cb, cbOff);
}

LRESULT APIUser32::ScrollBarWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollBarWndProcW()");
  return ScrollBarWndProcW_(hwnd, msg, wParam, lParam);
}

HDDEDATA APIUser32::DdeNameService (DWORD idInst, HSZ hsz1, HSZ hsz2, UINT afCmd)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeNameService()");
  return DdeNameService_(idInst, hsz1, hsz2, afCmd);
}

LRESULT APIUser32::ButtonWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ButtonWndProcA()");
  return ButtonWndProcA_(hwnd, msg, wParam, lParam);
}

INT APIUser32::GetSystemMetricsForDpi (INT index, UINT dpi)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetSystemMetricsForDpi()");
  return GetSystemMetricsForDpi_(index, dpi);
}

DPI_HOSTING_BEHAVIOR APIUser32::GetWindowDpiHostingBehavior (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowDpiHostingBehavior()");
  return GetWindowDpiHostingBehavior_(hwnd);
}

DWORD APIUser32::SetWindowStationUser (DWORD x1, DWORD x2)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetWindowStationUser()");
  return SetWindowStationUser_(x1, x2);
}

BOOL APIUser32::SystemParametersInfoForDpi (UINT action, UINT val, PVOID ptr, UINT winini, UINT dpi)
{
  logging::log("wrapper", logging::LogLevel::debug, "SystemParametersInfoForDpi()");
  return SystemParametersInfoForDpi_(action, val, ptr, winini, dpi);
}

LRESULT APIUser32::MessageWndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "MessageWndProc()");
  return MessageWndProc_(hwnd, message, wParam, lParam);
}

BOOL APIUser32::IsWindowRedirectedForPrint (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsWindowRedirectedForPrint()");
  return IsWindowRedirectedForPrint_(hwnd);
}

BOOL APIUser32::WINNLSGetEnableStatus (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "WINNLSGetEnableStatus()");
  return WINNLSGetEnableStatus_(hwnd);
}

BOOL APIUser32::KillSystemTimer (HWND hwnd, UINT_PTR id)
{
  logging::log("wrapper", logging::LogLevel::debug, "KillSystemTimer()");
  return KillSystemTimer_(hwnd, id);
}

HSZ APIUser32::DdeCreateStringHandleW (DWORD idInst, LPCWSTR psz, INT codepage)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeCreateStringHandleW()");
  return DdeCreateStringHandleW_(idInst, psz, codepage);
}

INT_PTR APIUser32::MDI_MoreWindowsDlgProc (HWND hDlg, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "MDI_MoreWindowsDlgProc()");
  return MDI_MoreWindowsDlgProc_(hDlg, iMsg, wParam, lParam);
}

BOOL APIUser32::WINNLSEnableIME (HWND hwnd, BOOL enable)
{
  logging::log("wrapper", logging::LogLevel::debug, "WINNLSEnableIME()");
  return WINNLSEnableIME_(hwnd, enable);
}

BOOL APIUser32::AdjustWindowRectExForDpi (LPRECT rect, DWORD style, BOOL menu, DWORD dwExStyle, UINT dpi)
{
  logging::log("wrapper", logging::LogLevel::debug, "AdjustWindowRectExForDpi()");
  return AdjustWindowRectExForDpi_(rect, style, menu, dwExStyle, dpi);
}

DPI_AWARENESS_CONTEXT APIUser32::GetThreadDpiAwarenessContext (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetThreadDpiAwarenessContext()");
  return GetThreadDpiAwarenessContext_();
}

BOOL APIUser32::DdeFreeStringHandle (DWORD idInst, HSZ hsz)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeFreeStringHandle()");
  return DdeFreeStringHandle_(idInst, hsz);
}

BOOL APIUser32::DrawCaptionTempA (HWND hwnd, HDC hdc, const RECT * rect, HFONT hFont, HICON hIcon, LPCSTR str, UINT uFlags)
{
  logging::log("wrapper", logging::LogLevel::debug, "DrawCaptionTempA()");
  return DrawCaptionTempA_(hwnd, hdc, rect, hFont, hIcon, str, uFlags);
}

WORD APIUser32::TileChildWindows (HWND parent, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "TileChildWindows()");
  return TileChildWindows_(parent, flags);
}

LPARAM APIUser32::ReuseDDElParam (LPARAM lParam, UINT msgIn, UINT msgOut, UINT_PTR uiLo, UINT_PTR uiHi)
{
  logging::log("wrapper", logging::LogLevel::debug, "ReuseDDElParam()");
  return ReuseDDElParam_(lParam, msgIn, msgOut, uiLo, uiHi);
}

BOOL APIUser32::ImpersonateDdeClientWindow (HWND hWndClient, HWND hWndServer)
{
  logging::log("wrapper", logging::LogLevel::debug, "ImpersonateDdeClientWindow()");
  return ImpersonateDdeClientWindow_(hWndClient, hWndServer);
}

UINT APIUser32::GetDpiForSystem (void)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDpiForSystem()");
  return GetDpiForSystem_();
}

BOOL APIUser32::User32InitializeImmEntryTable (DWORD magic)
{
  logging::log("wrapper", logging::LogLevel::debug, "User32InitializeImmEntryTable()");
  return User32InitializeImmEntryTable_(magic);
}

BOOL APIUser32::EnableNonClientDpiScaling (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "EnableNonClientDpiScaling()");
  return EnableNonClientDpiScaling_(hwnd);
}

BOOL APIUser32::ImmSetActiveContext (HWND arg0, HIMC arg1, BOOL arg2)
{
  logging::log("wrapper", logging::LogLevel::debug, "ImmSetActiveContext()");
  return ImmSetActiveContext_(arg0, arg1, arg2);
}

BOOL APIUser32::IsValidDpiAwarenessContext (DPI_AWARENESS_CONTEXT context)
{
  logging::log("wrapper", logging::LogLevel::debug, "IsValidDpiAwarenessContext()");
  return IsValidDpiAwarenessContext_(context);
}

void APIUser32::ScrollChildren (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ScrollChildren()");
  ScrollChildren_(hWnd, uMsg, wParam, lParam);
}

WORD APIUser32::CascadeChildWindows (HWND parent, UINT flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "CascadeChildWindows()");
  return CascadeChildWindows_(parent, flags);
}

DPI_AWARENESS_CONTEXT APIUser32::GetWindowDpiAwarenessContext (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetWindowDpiAwarenessContext()");
  return GetWindowDpiAwarenessContext_(hwnd);
}

HDEVNOTIFY APIUser32::I_ScRegisterDeviceNotification (DEVICE_NOTIFICATION_DETAILS * details, LPVOID filter, DWORD flags)
{
  logging::log("wrapper", logging::LogLevel::debug, "I_ScRegisterDeviceNotification()");
  return I_ScRegisterDeviceNotification_(details, filter, flags);
}

BOOL APIUser32::I_ScUnregisterDeviceNotification (HDEVNOTIFY handle)
{
  logging::log("wrapper", logging::LogLevel::debug, "I_ScUnregisterDeviceNotification()");
  return I_ScUnregisterDeviceNotification_(handle);
}

BOOL APIUser32::DdeSetUserHandle (HCONV hConv, DWORD id, DWORD hUser)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdeSetUserHandle()");
  return DdeSetUserHandle_(hConv, id, hUser);
}

BOOL APIUser32::DdePostAdvise (DWORD idInst, HSZ hszTopic, HSZ hszItem)
{
  logging::log("wrapper", logging::LogLevel::debug, "DdePostAdvise()");
  return DdePostAdvise_(idInst, hszTopic, hszItem);
}

DWORD APIUser32::GetAppCompatFlags2 (HTASK hTask)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAppCompatFlags2()");
  return GetAppCompatFlags2_(hTask);
}

BOOL APIUser32::AreDpiAwarenessContextsEqual (DPI_AWARENESS_CONTEXT ctx1, DPI_AWARENESS_CONTEXT ctx2)
{
  logging::log("wrapper", logging::LogLevel::debug, "AreDpiAwarenessContextsEqual()");
  return AreDpiAwarenessContextsEqual_(ctx1, ctx2);
}

DPI_AWARENESS APIUser32::GetAwarenessFromDpiAwarenessContext (DPI_AWARENESS_CONTEXT context)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetAwarenessFromDpiAwarenessContext()");
  return GetAwarenessFromDpiAwarenessContext_(context);
}

BOOL APIUser32::SetShellWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetShellWindow()");
  return SetShellWindow_(hwnd);
}

LRESULT APIUser32::ImeWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ImeWndProcW()");
  return ImeWndProcW_(hwnd, msg, wParam, lParam);
}

UINT APIUser32::GetDpiForWindow (HWND hwnd)
{
  logging::log("wrapper", logging::LogLevel::debug, "GetDpiForWindow()");
  return GetDpiForWindow_(hwnd);
}

BOOL APIUser32::UnpackDDElParam (UINT msg, LPARAM lParam, PUINT_PTR puiLo, PUINT_PTR puiHi)
{
  logging::log("wrapper", logging::LogLevel::debug, "UnpackDDElParam()");
  return UnpackDDElParam_(msg, lParam, puiLo, puiHi);
}

BOOL APIUser32::FreeDDElParam (UINT msg, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "FreeDDElParam()");
  return FreeDDElParam_(msg, lParam);
}

void APIUser32::UserRegisterWowHandlers (const struct wow_handlers16 * new_, struct wow_handlers32 * orig)
{
  logging::log("wrapper", logging::LogLevel::debug, "UserRegisterWowHandlers()");
  UserRegisterWowHandlers_(new_, orig);
}

LRESULT APIUser32::ImeWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ImeWndProcA()");
  return ImeWndProcA_(hwnd, msg, wParam, lParam);
}

LRESULT APIUser32::ListBoxWndProcW (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ListBoxWndProcW()");
  return ListBoxWndProcW_(hwnd, msg, wParam, lParam);
}

LRESULT APIUser32::ListBoxWndProcA (HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  logging::log("wrapper", logging::LogLevel::debug, "ListBoxWndProcA()");
  return ListBoxWndProcA_(hwnd, msg, wParam, lParam);
}

DPI_HOSTING_BEHAVIOR APIUser32::SetThreadDpiHostingBehavior (DPI_HOSTING_BEHAVIOR value)
{
  logging::log("wrapper", logging::LogLevel::debug, "SetThreadDpiHostingBehavior()");
  return SetThreadDpiHostingBehavior_(value);
}

DWORD APIUser32::RegisterLogonProcess (HANDLE hprocess, BOOL x)
{
  logging::log("wrapper", logging::LogLevel::debug, "RegisterLogonProcess()");
  return RegisterLogonProcess_(hprocess, x);
}


FARPROC APIUser32::GetProcAddress_(HMODULE hModule, LPCSTR lpProcName)
{
  auto r = GetProcAddress(hModule, lpProcName);
  char buf[100];
  std::snprintf(buf, sizeof(buf), "0x%X", r);
  logging::log("init", logging::LogLevel::debug, lpProcName, " ", buf);
  return r;
}


APIUser32::APIUser32(std::string const & dllPath)
{
  logging::log("init", logging::LogLevel::debug, "APIUser32::APIUser32()");

  std::string dllPath2;
  if (dllPath.empty())
  {
    CHAR szPath[MAX_PATH];
    if (!GetSystemDirectory(szPath, sizeof(szPath)))
      throw std::runtime_error("Failed to get system directory path");
    strcat(szPath, "\\user32.dll");
    dllPath2 = szPath;
  }
  else
    dllPath2 = dllPath;
  
  logging::log("init", logging::LogLevel::debug, "APIUser32::APIUser32(): dllPath: ", dllPath, "; dllPath2: ", dllPath2);

  HMODULE hModule = LoadLibrary(dllPath2.c_str());
  if (!hModule)
  {
    std::stringstream ss;
    ss << "Failed to load dll from: " << dllPath2;
    throw std::runtime_error(ss.str());
  }
  logging::log("init", logging::LogLevel::debug, "APIUser32::APIUser32(): hModule: ", hModule);

  wvsprintfA_ = reinterpret_cast<decltype(wvsprintfA_)>(GetProcAddress_(hModule,"wvsprintfA"));
  wvsprintfW_ = reinterpret_cast<decltype(wvsprintfW_)>(GetProcAddress_(hModule,"wvsprintfW"));
  LoadKeyboardLayoutA_ = reinterpret_cast<decltype(LoadKeyboardLayoutA_)>(GetProcAddress_(hModule,"LoadKeyboardLayoutA"));
  LoadKeyboardLayoutW_ = reinterpret_cast<decltype(LoadKeyboardLayoutW_)>(GetProcAddress_(hModule,"LoadKeyboardLayoutW"));
  ActivateKeyboardLayout_ = reinterpret_cast<decltype(ActivateKeyboardLayout_)>(GetProcAddress_(hModule,"ActivateKeyboardLayout"));
  ToUnicodeEx_ = reinterpret_cast<decltype(ToUnicodeEx_)>(GetProcAddress_(hModule,"ToUnicodeEx"));
  UnloadKeyboardLayout_ = reinterpret_cast<decltype(UnloadKeyboardLayout_)>(GetProcAddress_(hModule,"UnloadKeyboardLayout"));
  GetKeyboardLayoutNameA_ = reinterpret_cast<decltype(GetKeyboardLayoutNameA_)>(GetProcAddress_(hModule,"GetKeyboardLayoutNameA"));
  GetKeyboardLayoutNameW_ = reinterpret_cast<decltype(GetKeyboardLayoutNameW_)>(GetProcAddress_(hModule,"GetKeyboardLayoutNameW"));
  GetKeyboardLayoutList_ = reinterpret_cast<decltype(GetKeyboardLayoutList_)>(GetProcAddress_(hModule,"GetKeyboardLayoutList"));
  GetKeyboardLayout_ = reinterpret_cast<decltype(GetKeyboardLayout_)>(GetProcAddress_(hModule,"GetKeyboardLayout"));
  GetMouseMovePointsEx_ = reinterpret_cast<decltype(GetMouseMovePointsEx_)>(GetProcAddress_(hModule,"GetMouseMovePointsEx"));
  CreateDesktopA_ = reinterpret_cast<decltype(CreateDesktopA_)>(GetProcAddress_(hModule,"CreateDesktopA"));
  CreateDesktopW_ = reinterpret_cast<decltype(CreateDesktopW_)>(GetProcAddress_(hModule,"CreateDesktopW"));
  CreateDesktopExA_ = reinterpret_cast<decltype(CreateDesktopExA_)>(GetProcAddress_(hModule,"CreateDesktopExA"));
  CreateDesktopExW_ = reinterpret_cast<decltype(CreateDesktopExW_)>(GetProcAddress_(hModule,"CreateDesktopExW"));
  OpenDesktopA_ = reinterpret_cast<decltype(OpenDesktopA_)>(GetProcAddress_(hModule,"OpenDesktopA"));
  OpenDesktopW_ = reinterpret_cast<decltype(OpenDesktopW_)>(GetProcAddress_(hModule,"OpenDesktopW"));
  OpenInputDesktop_ = reinterpret_cast<decltype(OpenInputDesktop_)>(GetProcAddress_(hModule,"OpenInputDesktop"));
  EnumDesktopsA_ = reinterpret_cast<decltype(EnumDesktopsA_)>(GetProcAddress_(hModule,"EnumDesktopsA"));
  EnumDesktopsW_ = reinterpret_cast<decltype(EnumDesktopsW_)>(GetProcAddress_(hModule,"EnumDesktopsW"));
  EnumDesktopWindows_ = reinterpret_cast<decltype(EnumDesktopWindows_)>(GetProcAddress_(hModule,"EnumDesktopWindows"));
  SwitchDesktop_ = reinterpret_cast<decltype(SwitchDesktop_)>(GetProcAddress_(hModule,"SwitchDesktop"));
  SetThreadDesktop_ = reinterpret_cast<decltype(SetThreadDesktop_)>(GetProcAddress_(hModule,"SetThreadDesktop"));
  CloseDesktop_ = reinterpret_cast<decltype(CloseDesktop_)>(GetProcAddress_(hModule,"CloseDesktop"));
  GetThreadDesktop_ = reinterpret_cast<decltype(GetThreadDesktop_)>(GetProcAddress_(hModule,"GetThreadDesktop"));
  CreateWindowStationA_ = reinterpret_cast<decltype(CreateWindowStationA_)>(GetProcAddress_(hModule,"CreateWindowStationA"));
  CreateWindowStationW_ = reinterpret_cast<decltype(CreateWindowStationW_)>(GetProcAddress_(hModule,"CreateWindowStationW"));
  OpenWindowStationA_ = reinterpret_cast<decltype(OpenWindowStationA_)>(GetProcAddress_(hModule,"OpenWindowStationA"));
  OpenWindowStationW_ = reinterpret_cast<decltype(OpenWindowStationW_)>(GetProcAddress_(hModule,"OpenWindowStationW"));
  EnumWindowStationsA_ = reinterpret_cast<decltype(EnumWindowStationsA_)>(GetProcAddress_(hModule,"EnumWindowStationsA"));
  EnumWindowStationsW_ = reinterpret_cast<decltype(EnumWindowStationsW_)>(GetProcAddress_(hModule,"EnumWindowStationsW"));
  CloseWindowStation_ = reinterpret_cast<decltype(CloseWindowStation_)>(GetProcAddress_(hModule,"CloseWindowStation"));
  SetProcessWindowStation_ = reinterpret_cast<decltype(SetProcessWindowStation_)>(GetProcAddress_(hModule,"SetProcessWindowStation"));
  GetProcessWindowStation_ = reinterpret_cast<decltype(GetProcessWindowStation_)>(GetProcAddress_(hModule,"GetProcessWindowStation"));
  SetUserObjectSecurity_ = reinterpret_cast<decltype(SetUserObjectSecurity_)>(GetProcAddress_(hModule,"SetUserObjectSecurity"));
  GetUserObjectSecurity_ = reinterpret_cast<decltype(GetUserObjectSecurity_)>(GetProcAddress_(hModule,"GetUserObjectSecurity"));
  GetUserObjectInformationA_ = reinterpret_cast<decltype(GetUserObjectInformationA_)>(GetProcAddress_(hModule,"GetUserObjectInformationA"));
  GetUserObjectInformationW_ = reinterpret_cast<decltype(GetUserObjectInformationW_)>(GetProcAddress_(hModule,"GetUserObjectInformationW"));
  SetUserObjectInformationA_ = reinterpret_cast<decltype(SetUserObjectInformationA_)>(GetProcAddress_(hModule,"SetUserObjectInformationA"));
  SetUserObjectInformationW_ = reinterpret_cast<decltype(SetUserObjectInformationW_)>(GetProcAddress_(hModule,"SetUserObjectInformationW"));
  IsHungAppWindow_ = reinterpret_cast<decltype(IsHungAppWindow_)>(GetProcAddress_(hModule,"IsHungAppWindow"));
  DisableProcessWindowsGhosting_ = reinterpret_cast<decltype(DisableProcessWindowsGhosting_)>(GetProcAddress_(hModule,"DisableProcessWindowsGhosting"));
  RegisterWindowMessageA_ = reinterpret_cast<decltype(RegisterWindowMessageA_)>(GetProcAddress_(hModule,"RegisterWindowMessageA"));
  RegisterWindowMessageW_ = reinterpret_cast<decltype(RegisterWindowMessageW_)>(GetProcAddress_(hModule,"RegisterWindowMessageW"));
  TrackMouseEvent_ = reinterpret_cast<decltype(TrackMouseEvent_)>(GetProcAddress_(hModule,"TrackMouseEvent"));
  DrawEdge_ = reinterpret_cast<decltype(DrawEdge_)>(GetProcAddress_(hModule,"DrawEdge"));
  DrawFrameControl_ = reinterpret_cast<decltype(DrawFrameControl_)>(GetProcAddress_(hModule,"DrawFrameControl"));
  DrawCaption_ = reinterpret_cast<decltype(DrawCaption_)>(GetProcAddress_(hModule,"DrawCaption"));
  DrawAnimatedRects_ = reinterpret_cast<decltype(DrawAnimatedRects_)>(GetProcAddress_(hModule,"DrawAnimatedRects"));
  GetMessageA_ = reinterpret_cast<decltype(GetMessageA_)>(GetProcAddress_(hModule,"GetMessageA"));
  GetMessageW_ = reinterpret_cast<decltype(GetMessageW_)>(GetProcAddress_(hModule,"GetMessageW"));
  TranslateMessage_ = reinterpret_cast<decltype(TranslateMessage_)>(GetProcAddress_(hModule,"TranslateMessage"));
  DispatchMessageA_ = reinterpret_cast<decltype(DispatchMessageA_)>(GetProcAddress_(hModule,"DispatchMessageA"));
  DispatchMessageW_ = reinterpret_cast<decltype(DispatchMessageW_)>(GetProcAddress_(hModule,"DispatchMessageW"));
  SetMessageQueue_ = reinterpret_cast<decltype(SetMessageQueue_)>(GetProcAddress_(hModule,"SetMessageQueue"));
  PeekMessageA_ = reinterpret_cast<decltype(PeekMessageA_)>(GetProcAddress_(hModule,"PeekMessageA"));
  PeekMessageW_ = reinterpret_cast<decltype(PeekMessageW_)>(GetProcAddress_(hModule,"PeekMessageW"));
  RegisterHotKey_ = reinterpret_cast<decltype(RegisterHotKey_)>(GetProcAddress_(hModule,"RegisterHotKey"));
  UnregisterHotKey_ = reinterpret_cast<decltype(UnregisterHotKey_)>(GetProcAddress_(hModule,"UnregisterHotKey"));
  ExitWindowsEx_ = reinterpret_cast<decltype(ExitWindowsEx_)>(GetProcAddress_(hModule,"ExitWindowsEx"));
  SwapMouseButton_ = reinterpret_cast<decltype(SwapMouseButton_)>(GetProcAddress_(hModule,"SwapMouseButton"));
  GetMessagePos_ = reinterpret_cast<decltype(GetMessagePos_)>(GetProcAddress_(hModule,"GetMessagePos"));
  GetMessageTime_ = reinterpret_cast<decltype(GetMessageTime_)>(GetProcAddress_(hModule,"GetMessageTime"));
  GetMessageExtraInfo_ = reinterpret_cast<decltype(GetMessageExtraInfo_)>(GetProcAddress_(hModule,"GetMessageExtraInfo"));
  GetUnpredictedMessagePos_ = reinterpret_cast<decltype(GetUnpredictedMessagePos_)>(GetProcAddress_(hModule,"GetUnpredictedMessagePos"));
  IsWow64Message_ = reinterpret_cast<decltype(IsWow64Message_)>(GetProcAddress_(hModule,"IsWow64Message"));
  SetMessageExtraInfo_ = reinterpret_cast<decltype(SetMessageExtraInfo_)>(GetProcAddress_(hModule,"SetMessageExtraInfo"));
  SendMessageA_ = reinterpret_cast<decltype(SendMessageA_)>(GetProcAddress_(hModule,"SendMessageA"));
  SendMessageW_ = reinterpret_cast<decltype(SendMessageW_)>(GetProcAddress_(hModule,"SendMessageW"));
  SendMessageTimeoutA_ = reinterpret_cast<decltype(SendMessageTimeoutA_)>(GetProcAddress_(hModule,"SendMessageTimeoutA"));
  SendMessageTimeoutW_ = reinterpret_cast<decltype(SendMessageTimeoutW_)>(GetProcAddress_(hModule,"SendMessageTimeoutW"));
  SendNotifyMessageA_ = reinterpret_cast<decltype(SendNotifyMessageA_)>(GetProcAddress_(hModule,"SendNotifyMessageA"));
  SendNotifyMessageW_ = reinterpret_cast<decltype(SendNotifyMessageW_)>(GetProcAddress_(hModule,"SendNotifyMessageW"));
  SendMessageCallbackA_ = reinterpret_cast<decltype(SendMessageCallbackA_)>(GetProcAddress_(hModule,"SendMessageCallbackA"));
  SendMessageCallbackW_ = reinterpret_cast<decltype(SendMessageCallbackW_)>(GetProcAddress_(hModule,"SendMessageCallbackW"));
  BroadcastSystemMessageExA_ = reinterpret_cast<decltype(BroadcastSystemMessageExA_)>(GetProcAddress_(hModule,"BroadcastSystemMessageExA"));
  BroadcastSystemMessageExW_ = reinterpret_cast<decltype(BroadcastSystemMessageExW_)>(GetProcAddress_(hModule,"BroadcastSystemMessageExW"));
  BroadcastSystemMessageA_ = reinterpret_cast<decltype(BroadcastSystemMessageA_)>(GetProcAddress_(hModule,"BroadcastSystemMessageA"));
  BroadcastSystemMessageW_ = reinterpret_cast<decltype(BroadcastSystemMessageW_)>(GetProcAddress_(hModule,"BroadcastSystemMessageW"));
  RegisterPowerSettingNotification_ = reinterpret_cast<decltype(RegisterPowerSettingNotification_)>(GetProcAddress_(hModule,"RegisterPowerSettingNotification"));
  UnregisterPowerSettingNotification_ = reinterpret_cast<decltype(UnregisterPowerSettingNotification_)>(GetProcAddress_(hModule,"UnregisterPowerSettingNotification"));
  RegisterSuspendResumeNotification_ = reinterpret_cast<decltype(RegisterSuspendResumeNotification_)>(GetProcAddress_(hModule,"RegisterSuspendResumeNotification"));
  UnregisterSuspendResumeNotification_ = reinterpret_cast<decltype(UnregisterSuspendResumeNotification_)>(GetProcAddress_(hModule,"UnregisterSuspendResumeNotification"));
  PostMessageA_ = reinterpret_cast<decltype(PostMessageA_)>(GetProcAddress_(hModule,"PostMessageA"));
  PostMessageW_ = reinterpret_cast<decltype(PostMessageW_)>(GetProcAddress_(hModule,"PostMessageW"));
  PostThreadMessageA_ = reinterpret_cast<decltype(PostThreadMessageA_)>(GetProcAddress_(hModule,"PostThreadMessageA"));
  PostThreadMessageW_ = reinterpret_cast<decltype(PostThreadMessageW_)>(GetProcAddress_(hModule,"PostThreadMessageW"));
  AttachThreadInput_ = reinterpret_cast<decltype(AttachThreadInput_)>(GetProcAddress_(hModule,"AttachThreadInput"));
  ReplyMessage_ = reinterpret_cast<decltype(ReplyMessage_)>(GetProcAddress_(hModule,"ReplyMessage"));
  WaitMessage_ = reinterpret_cast<decltype(WaitMessage_)>(GetProcAddress_(hModule,"WaitMessage"));
  WaitForInputIdle_ = reinterpret_cast<decltype(WaitForInputIdle_)>(GetProcAddress_(hModule,"WaitForInputIdle"));
  DefWindowProcA_ = reinterpret_cast<decltype(DefWindowProcA_)>(GetProcAddress_(hModule,"DefWindowProcA"));
  DefWindowProcW_ = reinterpret_cast<decltype(DefWindowProcW_)>(GetProcAddress_(hModule,"DefWindowProcW"));
  PostQuitMessage_ = reinterpret_cast<decltype(PostQuitMessage_)>(GetProcAddress_(hModule,"PostQuitMessage"));
  InSendMessage_ = reinterpret_cast<decltype(InSendMessage_)>(GetProcAddress_(hModule,"InSendMessage"));
  InSendMessageEx_ = reinterpret_cast<decltype(InSendMessageEx_)>(GetProcAddress_(hModule,"InSendMessageEx"));
  GetDoubleClickTime_ = reinterpret_cast<decltype(GetDoubleClickTime_)>(GetProcAddress_(hModule,"GetDoubleClickTime"));
  SetDoubleClickTime_ = reinterpret_cast<decltype(SetDoubleClickTime_)>(GetProcAddress_(hModule,"SetDoubleClickTime"));
  RegisterClassA_ = reinterpret_cast<decltype(RegisterClassA_)>(GetProcAddress_(hModule,"RegisterClassA"));
  RegisterClassW_ = reinterpret_cast<decltype(RegisterClassW_)>(GetProcAddress_(hModule,"RegisterClassW"));
  UnregisterClassA_ = reinterpret_cast<decltype(UnregisterClassA_)>(GetProcAddress_(hModule,"UnregisterClassA"));
  UnregisterClassW_ = reinterpret_cast<decltype(UnregisterClassW_)>(GetProcAddress_(hModule,"UnregisterClassW"));
  GetClassInfoA_ = reinterpret_cast<decltype(GetClassInfoA_)>(GetProcAddress_(hModule,"GetClassInfoA"));
  GetClassInfoW_ = reinterpret_cast<decltype(GetClassInfoW_)>(GetProcAddress_(hModule,"GetClassInfoW"));
  RegisterClassExA_ = reinterpret_cast<decltype(RegisterClassExA_)>(GetProcAddress_(hModule,"RegisterClassExA"));
  RegisterClassExW_ = reinterpret_cast<decltype(RegisterClassExW_)>(GetProcAddress_(hModule,"RegisterClassExW"));
  GetClassInfoExA_ = reinterpret_cast<decltype(GetClassInfoExA_)>(GetProcAddress_(hModule,"GetClassInfoExA"));
  GetClassInfoExW_ = reinterpret_cast<decltype(GetClassInfoExW_)>(GetProcAddress_(hModule,"GetClassInfoExW"));
  CallWindowProcA_ = reinterpret_cast<decltype(CallWindowProcA_)>(GetProcAddress_(hModule,"CallWindowProcA"));
  CallWindowProcW_ = reinterpret_cast<decltype(CallWindowProcW_)>(GetProcAddress_(hModule,"CallWindowProcW"));
  RegisterDeviceNotificationA_ = reinterpret_cast<decltype(RegisterDeviceNotificationA_)>(GetProcAddress_(hModule,"RegisterDeviceNotificationA"));
  RegisterDeviceNotificationW_ = reinterpret_cast<decltype(RegisterDeviceNotificationW_)>(GetProcAddress_(hModule,"RegisterDeviceNotificationW"));
  UnregisterDeviceNotification_ = reinterpret_cast<decltype(UnregisterDeviceNotification_)>(GetProcAddress_(hModule,"UnregisterDeviceNotification"));
  CreateWindowExA_ = reinterpret_cast<decltype(CreateWindowExA_)>(GetProcAddress_(hModule,"CreateWindowExA"));
  CreateWindowExW_ = reinterpret_cast<decltype(CreateWindowExW_)>(GetProcAddress_(hModule,"CreateWindowExW"));
  IsWindow_ = reinterpret_cast<decltype(IsWindow_)>(GetProcAddress_(hModule,"IsWindow"));
  IsMenu_ = reinterpret_cast<decltype(IsMenu_)>(GetProcAddress_(hModule,"IsMenu"));
  IsChild_ = reinterpret_cast<decltype(IsChild_)>(GetProcAddress_(hModule,"IsChild"));
  DestroyWindow_ = reinterpret_cast<decltype(DestroyWindow_)>(GetProcAddress_(hModule,"DestroyWindow"));
  ShowWindow_ = reinterpret_cast<decltype(ShowWindow_)>(GetProcAddress_(hModule,"ShowWindow"));
  AnimateWindow_ = reinterpret_cast<decltype(AnimateWindow_)>(GetProcAddress_(hModule,"AnimateWindow"));
  UpdateLayeredWindow_ = reinterpret_cast<decltype(UpdateLayeredWindow_)>(GetProcAddress_(hModule,"UpdateLayeredWindow"));
  UpdateLayeredWindowIndirect_ = reinterpret_cast<decltype(UpdateLayeredWindowIndirect_)>(GetProcAddress_(hModule,"UpdateLayeredWindowIndirect"));
  GetLayeredWindowAttributes_ = reinterpret_cast<decltype(GetLayeredWindowAttributes_)>(GetProcAddress_(hModule,"GetLayeredWindowAttributes"));
  PrintWindow_ = reinterpret_cast<decltype(PrintWindow_)>(GetProcAddress_(hModule,"PrintWindow"));
  SetLayeredWindowAttributes_ = reinterpret_cast<decltype(SetLayeredWindowAttributes_)>(GetProcAddress_(hModule,"SetLayeredWindowAttributes"));
  ShowWindowAsync_ = reinterpret_cast<decltype(ShowWindowAsync_)>(GetProcAddress_(hModule,"ShowWindowAsync"));
  FlashWindow_ = reinterpret_cast<decltype(FlashWindow_)>(GetProcAddress_(hModule,"FlashWindow"));
  FlashWindowEx_ = reinterpret_cast<decltype(FlashWindowEx_)>(GetProcAddress_(hModule,"FlashWindowEx"));
  ShowOwnedPopups_ = reinterpret_cast<decltype(ShowOwnedPopups_)>(GetProcAddress_(hModule,"ShowOwnedPopups"));
  OpenIcon_ = reinterpret_cast<decltype(OpenIcon_)>(GetProcAddress_(hModule,"OpenIcon"));
  CloseWindow_ = reinterpret_cast<decltype(CloseWindow_)>(GetProcAddress_(hModule,"CloseWindow"));
  MoveWindow_ = reinterpret_cast<decltype(MoveWindow_)>(GetProcAddress_(hModule,"MoveWindow"));
  SetWindowPos_ = reinterpret_cast<decltype(SetWindowPos_)>(GetProcAddress_(hModule,"SetWindowPos"));
  GetWindowPlacement_ = reinterpret_cast<decltype(GetWindowPlacement_)>(GetProcAddress_(hModule,"GetWindowPlacement"));
  SetWindowPlacement_ = reinterpret_cast<decltype(SetWindowPlacement_)>(GetProcAddress_(hModule,"SetWindowPlacement"));
  GetWindowDisplayAffinity_ = reinterpret_cast<decltype(GetWindowDisplayAffinity_)>(GetProcAddress_(hModule,"GetWindowDisplayAffinity"));
  SetWindowDisplayAffinity_ = reinterpret_cast<decltype(SetWindowDisplayAffinity_)>(GetProcAddress_(hModule,"SetWindowDisplayAffinity"));
  BeginDeferWindowPos_ = reinterpret_cast<decltype(BeginDeferWindowPos_)>(GetProcAddress_(hModule,"BeginDeferWindowPos"));
  DeferWindowPos_ = reinterpret_cast<decltype(DeferWindowPos_)>(GetProcAddress_(hModule,"DeferWindowPos"));
  EndDeferWindowPos_ = reinterpret_cast<decltype(EndDeferWindowPos_)>(GetProcAddress_(hModule,"EndDeferWindowPos"));
  IsWindowVisible_ = reinterpret_cast<decltype(IsWindowVisible_)>(GetProcAddress_(hModule,"IsWindowVisible"));
  IsIconic_ = reinterpret_cast<decltype(IsIconic_)>(GetProcAddress_(hModule,"IsIconic"));
  AnyPopup_ = reinterpret_cast<decltype(AnyPopup_)>(GetProcAddress_(hModule,"AnyPopup"));
  BringWindowToTop_ = reinterpret_cast<decltype(BringWindowToTop_)>(GetProcAddress_(hModule,"BringWindowToTop"));
  IsZoomed_ = reinterpret_cast<decltype(IsZoomed_)>(GetProcAddress_(hModule,"IsZoomed"));
  CreateDialogParamA_ = reinterpret_cast<decltype(CreateDialogParamA_)>(GetProcAddress_(hModule,"CreateDialogParamA"));
  CreateDialogParamW_ = reinterpret_cast<decltype(CreateDialogParamW_)>(GetProcAddress_(hModule,"CreateDialogParamW"));
  CreateDialogIndirectParamA_ = reinterpret_cast<decltype(CreateDialogIndirectParamA_)>(GetProcAddress_(hModule,"CreateDialogIndirectParamA"));
  CreateDialogIndirectParamW_ = reinterpret_cast<decltype(CreateDialogIndirectParamW_)>(GetProcAddress_(hModule,"CreateDialogIndirectParamW"));
  DialogBoxParamA_ = reinterpret_cast<decltype(DialogBoxParamA_)>(GetProcAddress_(hModule,"DialogBoxParamA"));
  DialogBoxParamW_ = reinterpret_cast<decltype(DialogBoxParamW_)>(GetProcAddress_(hModule,"DialogBoxParamW"));
  DialogBoxIndirectParamA_ = reinterpret_cast<decltype(DialogBoxIndirectParamA_)>(GetProcAddress_(hModule,"DialogBoxIndirectParamA"));
  DialogBoxIndirectParamW_ = reinterpret_cast<decltype(DialogBoxIndirectParamW_)>(GetProcAddress_(hModule,"DialogBoxIndirectParamW"));
  EndDialog_ = reinterpret_cast<decltype(EndDialog_)>(GetProcAddress_(hModule,"EndDialog"));
  GetDlgItem_ = reinterpret_cast<decltype(GetDlgItem_)>(GetProcAddress_(hModule,"GetDlgItem"));
  SetDlgItemInt_ = reinterpret_cast<decltype(SetDlgItemInt_)>(GetProcAddress_(hModule,"SetDlgItemInt"));
  GetDlgItemInt_ = reinterpret_cast<decltype(GetDlgItemInt_)>(GetProcAddress_(hModule,"GetDlgItemInt"));
  SetDlgItemTextA_ = reinterpret_cast<decltype(SetDlgItemTextA_)>(GetProcAddress_(hModule,"SetDlgItemTextA"));
  SetDlgItemTextW_ = reinterpret_cast<decltype(SetDlgItemTextW_)>(GetProcAddress_(hModule,"SetDlgItemTextW"));
  GetDlgItemTextA_ = reinterpret_cast<decltype(GetDlgItemTextA_)>(GetProcAddress_(hModule,"GetDlgItemTextA"));
  GetDlgItemTextW_ = reinterpret_cast<decltype(GetDlgItemTextW_)>(GetProcAddress_(hModule,"GetDlgItemTextW"));
  CheckDlgButton_ = reinterpret_cast<decltype(CheckDlgButton_)>(GetProcAddress_(hModule,"CheckDlgButton"));
  CheckRadioButton_ = reinterpret_cast<decltype(CheckRadioButton_)>(GetProcAddress_(hModule,"CheckRadioButton"));
  IsDlgButtonChecked_ = reinterpret_cast<decltype(IsDlgButtonChecked_)>(GetProcAddress_(hModule,"IsDlgButtonChecked"));
  SendDlgItemMessageA_ = reinterpret_cast<decltype(SendDlgItemMessageA_)>(GetProcAddress_(hModule,"SendDlgItemMessageA"));
  SendDlgItemMessageW_ = reinterpret_cast<decltype(SendDlgItemMessageW_)>(GetProcAddress_(hModule,"SendDlgItemMessageW"));
  GetNextDlgGroupItem_ = reinterpret_cast<decltype(GetNextDlgGroupItem_)>(GetProcAddress_(hModule,"GetNextDlgGroupItem"));
  GetNextDlgTabItem_ = reinterpret_cast<decltype(GetNextDlgTabItem_)>(GetProcAddress_(hModule,"GetNextDlgTabItem"));
  GetDlgCtrlID_ = reinterpret_cast<decltype(GetDlgCtrlID_)>(GetProcAddress_(hModule,"GetDlgCtrlID"));
  GetDialogBaseUnits_ = reinterpret_cast<decltype(GetDialogBaseUnits_)>(GetProcAddress_(hModule,"GetDialogBaseUnits"));
  DefDlgProcA_ = reinterpret_cast<decltype(DefDlgProcA_)>(GetProcAddress_(hModule,"DefDlgProcA"));
  DefDlgProcW_ = reinterpret_cast<decltype(DefDlgProcW_)>(GetProcAddress_(hModule,"DefDlgProcW"));
  CallMsgFilterA_ = reinterpret_cast<decltype(CallMsgFilterA_)>(GetProcAddress_(hModule,"CallMsgFilterA"));
  CallMsgFilterW_ = reinterpret_cast<decltype(CallMsgFilterW_)>(GetProcAddress_(hModule,"CallMsgFilterW"));
  OpenClipboard_ = reinterpret_cast<decltype(OpenClipboard_)>(GetProcAddress_(hModule,"OpenClipboard"));
  CloseClipboard_ = reinterpret_cast<decltype(CloseClipboard_)>(GetProcAddress_(hModule,"CloseClipboard"));
  GetClipboardSequenceNumber_ = reinterpret_cast<decltype(GetClipboardSequenceNumber_)>(GetProcAddress_(hModule,"GetClipboardSequenceNumber"));
  GetClipboardOwner_ = reinterpret_cast<decltype(GetClipboardOwner_)>(GetProcAddress_(hModule,"GetClipboardOwner"));
  SetClipboardViewer_ = reinterpret_cast<decltype(SetClipboardViewer_)>(GetProcAddress_(hModule,"SetClipboardViewer"));
  GetClipboardViewer_ = reinterpret_cast<decltype(GetClipboardViewer_)>(GetProcAddress_(hModule,"GetClipboardViewer"));
  ChangeClipboardChain_ = reinterpret_cast<decltype(ChangeClipboardChain_)>(GetProcAddress_(hModule,"ChangeClipboardChain"));
  SetClipboardData_ = reinterpret_cast<decltype(SetClipboardData_)>(GetProcAddress_(hModule,"SetClipboardData"));
  GetClipboardData_ = reinterpret_cast<decltype(GetClipboardData_)>(GetProcAddress_(hModule,"GetClipboardData"));
  RegisterClipboardFormatA_ = reinterpret_cast<decltype(RegisterClipboardFormatA_)>(GetProcAddress_(hModule,"RegisterClipboardFormatA"));
  RegisterClipboardFormatW_ = reinterpret_cast<decltype(RegisterClipboardFormatW_)>(GetProcAddress_(hModule,"RegisterClipboardFormatW"));
  CountClipboardFormats_ = reinterpret_cast<decltype(CountClipboardFormats_)>(GetProcAddress_(hModule,"CountClipboardFormats"));
  EnumClipboardFormats_ = reinterpret_cast<decltype(EnumClipboardFormats_)>(GetProcAddress_(hModule,"EnumClipboardFormats"));
  GetClipboardFormatNameA_ = reinterpret_cast<decltype(GetClipboardFormatNameA_)>(GetProcAddress_(hModule,"GetClipboardFormatNameA"));
  GetClipboardFormatNameW_ = reinterpret_cast<decltype(GetClipboardFormatNameW_)>(GetProcAddress_(hModule,"GetClipboardFormatNameW"));
  EmptyClipboard_ = reinterpret_cast<decltype(EmptyClipboard_)>(GetProcAddress_(hModule,"EmptyClipboard"));
  IsClipboardFormatAvailable_ = reinterpret_cast<decltype(IsClipboardFormatAvailable_)>(GetProcAddress_(hModule,"IsClipboardFormatAvailable"));
  GetPriorityClipboardFormat_ = reinterpret_cast<decltype(GetPriorityClipboardFormat_)>(GetProcAddress_(hModule,"GetPriorityClipboardFormat"));
  GetOpenClipboardWindow_ = reinterpret_cast<decltype(GetOpenClipboardWindow_)>(GetProcAddress_(hModule,"GetOpenClipboardWindow"));
  AddClipboardFormatListener_ = reinterpret_cast<decltype(AddClipboardFormatListener_)>(GetProcAddress_(hModule,"AddClipboardFormatListener"));
  RemoveClipboardFormatListener_ = reinterpret_cast<decltype(RemoveClipboardFormatListener_)>(GetProcAddress_(hModule,"RemoveClipboardFormatListener"));
  GetUpdatedClipboardFormats_ = reinterpret_cast<decltype(GetUpdatedClipboardFormats_)>(GetProcAddress_(hModule,"GetUpdatedClipboardFormats"));
  CharToOemA_ = reinterpret_cast<decltype(CharToOemA_)>(GetProcAddress_(hModule,"CharToOemA"));
  CharToOemW_ = reinterpret_cast<decltype(CharToOemW_)>(GetProcAddress_(hModule,"CharToOemW"));
  OemToCharA_ = reinterpret_cast<decltype(OemToCharA_)>(GetProcAddress_(hModule,"OemToCharA"));
  OemToCharW_ = reinterpret_cast<decltype(OemToCharW_)>(GetProcAddress_(hModule,"OemToCharW"));
  CharToOemBuffA_ = reinterpret_cast<decltype(CharToOemBuffA_)>(GetProcAddress_(hModule,"CharToOemBuffA"));
  CharToOemBuffW_ = reinterpret_cast<decltype(CharToOemBuffW_)>(GetProcAddress_(hModule,"CharToOemBuffW"));
  OemToCharBuffA_ = reinterpret_cast<decltype(OemToCharBuffA_)>(GetProcAddress_(hModule,"OemToCharBuffA"));
  OemToCharBuffW_ = reinterpret_cast<decltype(OemToCharBuffW_)>(GetProcAddress_(hModule,"OemToCharBuffW"));
  CharUpperA_ = reinterpret_cast<decltype(CharUpperA_)>(GetProcAddress_(hModule,"CharUpperA"));
  CharUpperW_ = reinterpret_cast<decltype(CharUpperW_)>(GetProcAddress_(hModule,"CharUpperW"));
  CharUpperBuffA_ = reinterpret_cast<decltype(CharUpperBuffA_)>(GetProcAddress_(hModule,"CharUpperBuffA"));
  CharUpperBuffW_ = reinterpret_cast<decltype(CharUpperBuffW_)>(GetProcAddress_(hModule,"CharUpperBuffW"));
  CharLowerA_ = reinterpret_cast<decltype(CharLowerA_)>(GetProcAddress_(hModule,"CharLowerA"));
  CharLowerW_ = reinterpret_cast<decltype(CharLowerW_)>(GetProcAddress_(hModule,"CharLowerW"));
  CharLowerBuffA_ = reinterpret_cast<decltype(CharLowerBuffA_)>(GetProcAddress_(hModule,"CharLowerBuffA"));
  CharLowerBuffW_ = reinterpret_cast<decltype(CharLowerBuffW_)>(GetProcAddress_(hModule,"CharLowerBuffW"));
  CharNextA_ = reinterpret_cast<decltype(CharNextA_)>(GetProcAddress_(hModule,"CharNextA"));
  CharNextW_ = reinterpret_cast<decltype(CharNextW_)>(GetProcAddress_(hModule,"CharNextW"));
  CharPrevA_ = reinterpret_cast<decltype(CharPrevA_)>(GetProcAddress_(hModule,"CharPrevA"));
  CharPrevW_ = reinterpret_cast<decltype(CharPrevW_)>(GetProcAddress_(hModule,"CharPrevW"));
  CharNextExA_ = reinterpret_cast<decltype(CharNextExA_)>(GetProcAddress_(hModule,"CharNextExA"));
  CharPrevExA_ = reinterpret_cast<decltype(CharPrevExA_)>(GetProcAddress_(hModule,"CharPrevExA"));
  IsCharAlphaA_ = reinterpret_cast<decltype(IsCharAlphaA_)>(GetProcAddress_(hModule,"IsCharAlphaA"));
  IsCharAlphaW_ = reinterpret_cast<decltype(IsCharAlphaW_)>(GetProcAddress_(hModule,"IsCharAlphaW"));
  IsCharAlphaNumericA_ = reinterpret_cast<decltype(IsCharAlphaNumericA_)>(GetProcAddress_(hModule,"IsCharAlphaNumericA"));
  IsCharAlphaNumericW_ = reinterpret_cast<decltype(IsCharAlphaNumericW_)>(GetProcAddress_(hModule,"IsCharAlphaNumericW"));
  IsCharUpperA_ = reinterpret_cast<decltype(IsCharUpperA_)>(GetProcAddress_(hModule,"IsCharUpperA"));
  IsCharUpperW_ = reinterpret_cast<decltype(IsCharUpperW_)>(GetProcAddress_(hModule,"IsCharUpperW"));
  IsCharLowerA_ = reinterpret_cast<decltype(IsCharLowerA_)>(GetProcAddress_(hModule,"IsCharLowerA"));
  IsCharLowerW_ = reinterpret_cast<decltype(IsCharLowerW_)>(GetProcAddress_(hModule,"IsCharLowerW"));
  SetFocus_ = reinterpret_cast<decltype(SetFocus_)>(GetProcAddress_(hModule,"SetFocus"));
  GetActiveWindow_ = reinterpret_cast<decltype(GetActiveWindow_)>(GetProcAddress_(hModule,"GetActiveWindow"));
  GetFocus_ = reinterpret_cast<decltype(GetFocus_)>(GetProcAddress_(hModule,"GetFocus"));
  GetKBCodePage_ = reinterpret_cast<decltype(GetKBCodePage_)>(GetProcAddress_(hModule,"GetKBCodePage"));
  GetKeyState_ = reinterpret_cast<decltype(GetKeyState_)>(GetProcAddress_(hModule,"GetKeyState"));
  GetAsyncKeyState_ = reinterpret_cast<decltype(GetAsyncKeyState_)>(GetProcAddress_(hModule,"GetAsyncKeyState"));
  GetKeyboardState_ = reinterpret_cast<decltype(GetKeyboardState_)>(GetProcAddress_(hModule,"GetKeyboardState"));
  SetKeyboardState_ = reinterpret_cast<decltype(SetKeyboardState_)>(GetProcAddress_(hModule,"SetKeyboardState"));
  GetKeyNameTextA_ = reinterpret_cast<decltype(GetKeyNameTextA_)>(GetProcAddress_(hModule,"GetKeyNameTextA"));
  GetKeyNameTextW_ = reinterpret_cast<decltype(GetKeyNameTextW_)>(GetProcAddress_(hModule,"GetKeyNameTextW"));
  GetKeyboardType_ = reinterpret_cast<decltype(GetKeyboardType_)>(GetProcAddress_(hModule,"GetKeyboardType"));
  ToAscii_ = reinterpret_cast<decltype(ToAscii_)>(GetProcAddress_(hModule,"ToAscii"));
  ToAsciiEx_ = reinterpret_cast<decltype(ToAsciiEx_)>(GetProcAddress_(hModule,"ToAsciiEx"));
  ToUnicode_ = reinterpret_cast<decltype(ToUnicode_)>(GetProcAddress_(hModule,"ToUnicode"));
  OemKeyScan_ = reinterpret_cast<decltype(OemKeyScan_)>(GetProcAddress_(hModule,"OemKeyScan"));
  VkKeyScanA_ = reinterpret_cast<decltype(VkKeyScanA_)>(GetProcAddress_(hModule,"VkKeyScanA"));
  VkKeyScanW_ = reinterpret_cast<decltype(VkKeyScanW_)>(GetProcAddress_(hModule,"VkKeyScanW"));
  VkKeyScanExA_ = reinterpret_cast<decltype(VkKeyScanExA_)>(GetProcAddress_(hModule,"VkKeyScanExA"));
  VkKeyScanExW_ = reinterpret_cast<decltype(VkKeyScanExW_)>(GetProcAddress_(hModule,"VkKeyScanExW"));
  keybd_event_ = reinterpret_cast<decltype(keybd_event_)>(GetProcAddress_(hModule,"keybd_event"));
  mouse_event_ = reinterpret_cast<decltype(mouse_event_)>(GetProcAddress_(hModule,"mouse_event"));
  SendInput_ = reinterpret_cast<decltype(SendInput_)>(GetProcAddress_(hModule,"SendInput"));
  GetTouchInputInfo_ = reinterpret_cast<decltype(GetTouchInputInfo_)>(GetProcAddress_(hModule,"GetTouchInputInfo"));
  CloseTouchInputHandle_ = reinterpret_cast<decltype(CloseTouchInputHandle_)>(GetProcAddress_(hModule,"CloseTouchInputHandle"));
  RegisterTouchWindow_ = reinterpret_cast<decltype(RegisterTouchWindow_)>(GetProcAddress_(hModule,"RegisterTouchWindow"));
  UnregisterTouchWindow_ = reinterpret_cast<decltype(UnregisterTouchWindow_)>(GetProcAddress_(hModule,"UnregisterTouchWindow"));
  IsTouchWindow_ = reinterpret_cast<decltype(IsTouchWindow_)>(GetProcAddress_(hModule,"IsTouchWindow"));
  InitializeTouchInjection_ = reinterpret_cast<decltype(InitializeTouchInjection_)>(GetProcAddress_(hModule,"InitializeTouchInjection"));
  InjectTouchInput_ = reinterpret_cast<decltype(InjectTouchInput_)>(GetProcAddress_(hModule,"InjectTouchInput"));
  GetPointerType_ = reinterpret_cast<decltype(GetPointerType_)>(GetProcAddress_(hModule,"GetPointerType"));
  GetPointerCursorId_ = reinterpret_cast<decltype(GetPointerCursorId_)>(GetProcAddress_(hModule,"GetPointerCursorId"));
  GetPointerInfo_ = reinterpret_cast<decltype(GetPointerInfo_)>(GetProcAddress_(hModule,"GetPointerInfo"));
  GetPointerInfoHistory_ = reinterpret_cast<decltype(GetPointerInfoHistory_)>(GetProcAddress_(hModule,"GetPointerInfoHistory"));
  GetPointerFrameInfo_ = reinterpret_cast<decltype(GetPointerFrameInfo_)>(GetProcAddress_(hModule,"GetPointerFrameInfo"));
  GetPointerFrameInfoHistory_ = reinterpret_cast<decltype(GetPointerFrameInfoHistory_)>(GetProcAddress_(hModule,"GetPointerFrameInfoHistory"));
  GetPointerTouchInfo_ = reinterpret_cast<decltype(GetPointerTouchInfo_)>(GetProcAddress_(hModule,"GetPointerTouchInfo"));
  GetPointerTouchInfoHistory_ = reinterpret_cast<decltype(GetPointerTouchInfoHistory_)>(GetProcAddress_(hModule,"GetPointerTouchInfoHistory"));
  GetPointerFrameTouchInfo_ = reinterpret_cast<decltype(GetPointerFrameTouchInfo_)>(GetProcAddress_(hModule,"GetPointerFrameTouchInfo"));
  GetPointerFrameTouchInfoHistory_ = reinterpret_cast<decltype(GetPointerFrameTouchInfoHistory_)>(GetProcAddress_(hModule,"GetPointerFrameTouchInfoHistory"));
  GetPointerPenInfo_ = reinterpret_cast<decltype(GetPointerPenInfo_)>(GetProcAddress_(hModule,"GetPointerPenInfo"));
  GetPointerPenInfoHistory_ = reinterpret_cast<decltype(GetPointerPenInfoHistory_)>(GetProcAddress_(hModule,"GetPointerPenInfoHistory"));
  GetPointerFramePenInfo_ = reinterpret_cast<decltype(GetPointerFramePenInfo_)>(GetProcAddress_(hModule,"GetPointerFramePenInfo"));
  GetPointerFramePenInfoHistory_ = reinterpret_cast<decltype(GetPointerFramePenInfoHistory_)>(GetProcAddress_(hModule,"GetPointerFramePenInfoHistory"));
  SkipPointerFrameMessages_ = reinterpret_cast<decltype(SkipPointerFrameMessages_)>(GetProcAddress_(hModule,"SkipPointerFrameMessages"));
  RegisterPointerInputTarget_ = reinterpret_cast<decltype(RegisterPointerInputTarget_)>(GetProcAddress_(hModule,"RegisterPointerInputTarget"));
  UnregisterPointerInputTarget_ = reinterpret_cast<decltype(UnregisterPointerInputTarget_)>(GetProcAddress_(hModule,"UnregisterPointerInputTarget"));
  EnableMouseInPointer_ = reinterpret_cast<decltype(EnableMouseInPointer_)>(GetProcAddress_(hModule,"EnableMouseInPointer"));
  IsMouseInPointerEnabled_ = reinterpret_cast<decltype(IsMouseInPointerEnabled_)>(GetProcAddress_(hModule,"IsMouseInPointerEnabled"));
  RegisterTouchHitTestingWindow_ = reinterpret_cast<decltype(RegisterTouchHitTestingWindow_)>(GetProcAddress_(hModule,"RegisterTouchHitTestingWindow"));
  EvaluateProximityToRect_ = reinterpret_cast<decltype(EvaluateProximityToRect_)>(GetProcAddress_(hModule,"EvaluateProximityToRect"));
  EvaluateProximityToPolygon_ = reinterpret_cast<decltype(EvaluateProximityToPolygon_)>(GetProcAddress_(hModule,"EvaluateProximityToPolygon"));
  PackTouchHitTestingProximityEvaluation_ = reinterpret_cast<decltype(PackTouchHitTestingProximityEvaluation_)>(GetProcAddress_(hModule,"PackTouchHitTestingProximityEvaluation"));
  GetWindowFeedbackSetting_ = reinterpret_cast<decltype(GetWindowFeedbackSetting_)>(GetProcAddress_(hModule,"GetWindowFeedbackSetting"));
  SetWindowFeedbackSetting_ = reinterpret_cast<decltype(SetWindowFeedbackSetting_)>(GetProcAddress_(hModule,"SetWindowFeedbackSetting"));
  GetLastInputInfo_ = reinterpret_cast<decltype(GetLastInputInfo_)>(GetProcAddress_(hModule,"GetLastInputInfo"));
  MapVirtualKeyA_ = reinterpret_cast<decltype(MapVirtualKeyA_)>(GetProcAddress_(hModule,"MapVirtualKeyA"));
  MapVirtualKeyW_ = reinterpret_cast<decltype(MapVirtualKeyW_)>(GetProcAddress_(hModule,"MapVirtualKeyW"));
  MapVirtualKeyExA_ = reinterpret_cast<decltype(MapVirtualKeyExA_)>(GetProcAddress_(hModule,"MapVirtualKeyExA"));
  MapVirtualKeyExW_ = reinterpret_cast<decltype(MapVirtualKeyExW_)>(GetProcAddress_(hModule,"MapVirtualKeyExW"));
  GetInputState_ = reinterpret_cast<decltype(GetInputState_)>(GetProcAddress_(hModule,"GetInputState"));
  GetQueueStatus_ = reinterpret_cast<decltype(GetQueueStatus_)>(GetProcAddress_(hModule,"GetQueueStatus"));
  GetCapture_ = reinterpret_cast<decltype(GetCapture_)>(GetProcAddress_(hModule,"GetCapture"));
  SetCapture_ = reinterpret_cast<decltype(SetCapture_)>(GetProcAddress_(hModule,"SetCapture"));
  ReleaseCapture_ = reinterpret_cast<decltype(ReleaseCapture_)>(GetProcAddress_(hModule,"ReleaseCapture"));
  MsgWaitForMultipleObjects_ = reinterpret_cast<decltype(MsgWaitForMultipleObjects_)>(GetProcAddress_(hModule,"MsgWaitForMultipleObjects"));
  MsgWaitForMultipleObjectsEx_ = reinterpret_cast<decltype(MsgWaitForMultipleObjectsEx_)>(GetProcAddress_(hModule,"MsgWaitForMultipleObjectsEx"));
  SetTimer_ = reinterpret_cast<decltype(SetTimer_)>(GetProcAddress_(hModule,"SetTimer"));
  KillTimer_ = reinterpret_cast<decltype(KillTimer_)>(GetProcAddress_(hModule,"KillTimer"));
  IsWindowUnicode_ = reinterpret_cast<decltype(IsWindowUnicode_)>(GetProcAddress_(hModule,"IsWindowUnicode"));
  EnableWindow_ = reinterpret_cast<decltype(EnableWindow_)>(GetProcAddress_(hModule,"EnableWindow"));
  IsWindowEnabled_ = reinterpret_cast<decltype(IsWindowEnabled_)>(GetProcAddress_(hModule,"IsWindowEnabled"));
  LoadAcceleratorsA_ = reinterpret_cast<decltype(LoadAcceleratorsA_)>(GetProcAddress_(hModule,"LoadAcceleratorsA"));
  LoadAcceleratorsW_ = reinterpret_cast<decltype(LoadAcceleratorsW_)>(GetProcAddress_(hModule,"LoadAcceleratorsW"));
  CreateAcceleratorTableA_ = reinterpret_cast<decltype(CreateAcceleratorTableA_)>(GetProcAddress_(hModule,"CreateAcceleratorTableA"));
  CreateAcceleratorTableW_ = reinterpret_cast<decltype(CreateAcceleratorTableW_)>(GetProcAddress_(hModule,"CreateAcceleratorTableW"));
  DestroyAcceleratorTable_ = reinterpret_cast<decltype(DestroyAcceleratorTable_)>(GetProcAddress_(hModule,"DestroyAcceleratorTable"));
  CopyAcceleratorTableA_ = reinterpret_cast<decltype(CopyAcceleratorTableA_)>(GetProcAddress_(hModule,"CopyAcceleratorTableA"));
  CopyAcceleratorTableW_ = reinterpret_cast<decltype(CopyAcceleratorTableW_)>(GetProcAddress_(hModule,"CopyAcceleratorTableW"));
  TranslateAcceleratorA_ = reinterpret_cast<decltype(TranslateAcceleratorA_)>(GetProcAddress_(hModule,"TranslateAcceleratorA"));
  TranslateAcceleratorW_ = reinterpret_cast<decltype(TranslateAcceleratorW_)>(GetProcAddress_(hModule,"TranslateAcceleratorW"));
  SetCoalescableTimer_ = reinterpret_cast<decltype(SetCoalescableTimer_)>(GetProcAddress_(hModule,"SetCoalescableTimer"));
  GetSystemMetrics_ = reinterpret_cast<decltype(GetSystemMetrics_)>(GetProcAddress_(hModule,"GetSystemMetrics"));
  LoadMenuA_ = reinterpret_cast<decltype(LoadMenuA_)>(GetProcAddress_(hModule,"LoadMenuA"));
  LoadMenuW_ = reinterpret_cast<decltype(LoadMenuW_)>(GetProcAddress_(hModule,"LoadMenuW"));
  LoadMenuIndirectA_ = reinterpret_cast<decltype(LoadMenuIndirectA_)>(GetProcAddress_(hModule,"LoadMenuIndirectA"));
  LoadMenuIndirectW_ = reinterpret_cast<decltype(LoadMenuIndirectW_)>(GetProcAddress_(hModule,"LoadMenuIndirectW"));
  GetMenu_ = reinterpret_cast<decltype(GetMenu_)>(GetProcAddress_(hModule,"GetMenu"));
  SetMenu_ = reinterpret_cast<decltype(SetMenu_)>(GetProcAddress_(hModule,"SetMenu"));
  ChangeMenuA_ = reinterpret_cast<decltype(ChangeMenuA_)>(GetProcAddress_(hModule,"ChangeMenuA"));
  ChangeMenuW_ = reinterpret_cast<decltype(ChangeMenuW_)>(GetProcAddress_(hModule,"ChangeMenuW"));
  HiliteMenuItem_ = reinterpret_cast<decltype(HiliteMenuItem_)>(GetProcAddress_(hModule,"HiliteMenuItem"));
  GetMenuStringA_ = reinterpret_cast<decltype(GetMenuStringA_)>(GetProcAddress_(hModule,"GetMenuStringA"));
  GetMenuStringW_ = reinterpret_cast<decltype(GetMenuStringW_)>(GetProcAddress_(hModule,"GetMenuStringW"));
  GetMenuState_ = reinterpret_cast<decltype(GetMenuState_)>(GetProcAddress_(hModule,"GetMenuState"));
  DrawMenuBar_ = reinterpret_cast<decltype(DrawMenuBar_)>(GetProcAddress_(hModule,"DrawMenuBar"));
  GetSystemMenu_ = reinterpret_cast<decltype(GetSystemMenu_)>(GetProcAddress_(hModule,"GetSystemMenu"));
  CreateMenu_ = reinterpret_cast<decltype(CreateMenu_)>(GetProcAddress_(hModule,"CreateMenu"));
  CreatePopupMenu_ = reinterpret_cast<decltype(CreatePopupMenu_)>(GetProcAddress_(hModule,"CreatePopupMenu"));
  DestroyMenu_ = reinterpret_cast<decltype(DestroyMenu_)>(GetProcAddress_(hModule,"DestroyMenu"));
  CheckMenuItem_ = reinterpret_cast<decltype(CheckMenuItem_)>(GetProcAddress_(hModule,"CheckMenuItem"));
  EnableMenuItem_ = reinterpret_cast<decltype(EnableMenuItem_)>(GetProcAddress_(hModule,"EnableMenuItem"));
  GetSubMenu_ = reinterpret_cast<decltype(GetSubMenu_)>(GetProcAddress_(hModule,"GetSubMenu"));
  GetMenuItemID_ = reinterpret_cast<decltype(GetMenuItemID_)>(GetProcAddress_(hModule,"GetMenuItemID"));
  GetMenuItemCount_ = reinterpret_cast<decltype(GetMenuItemCount_)>(GetProcAddress_(hModule,"GetMenuItemCount"));
  InsertMenuA_ = reinterpret_cast<decltype(InsertMenuA_)>(GetProcAddress_(hModule,"InsertMenuA"));
  InsertMenuW_ = reinterpret_cast<decltype(InsertMenuW_)>(GetProcAddress_(hModule,"InsertMenuW"));
  AppendMenuA_ = reinterpret_cast<decltype(AppendMenuA_)>(GetProcAddress_(hModule,"AppendMenuA"));
  AppendMenuW_ = reinterpret_cast<decltype(AppendMenuW_)>(GetProcAddress_(hModule,"AppendMenuW"));
  ModifyMenuA_ = reinterpret_cast<decltype(ModifyMenuA_)>(GetProcAddress_(hModule,"ModifyMenuA"));
  ModifyMenuW_ = reinterpret_cast<decltype(ModifyMenuW_)>(GetProcAddress_(hModule,"ModifyMenuW"));
  RemoveMenu_ = reinterpret_cast<decltype(RemoveMenu_)>(GetProcAddress_(hModule,"RemoveMenu"));
  DeleteMenu_ = reinterpret_cast<decltype(DeleteMenu_)>(GetProcAddress_(hModule,"DeleteMenu"));
  SetMenuItemBitmaps_ = reinterpret_cast<decltype(SetMenuItemBitmaps_)>(GetProcAddress_(hModule,"SetMenuItemBitmaps"));
  GetMenuCheckMarkDimensions_ = reinterpret_cast<decltype(GetMenuCheckMarkDimensions_)>(GetProcAddress_(hModule,"GetMenuCheckMarkDimensions"));
  TrackPopupMenu_ = reinterpret_cast<decltype(TrackPopupMenu_)>(GetProcAddress_(hModule,"TrackPopupMenu"));
  TrackPopupMenuEx_ = reinterpret_cast<decltype(TrackPopupMenuEx_)>(GetProcAddress_(hModule,"TrackPopupMenuEx"));
  GetMenuInfo_ = reinterpret_cast<decltype(GetMenuInfo_)>(GetProcAddress_(hModule,"GetMenuInfo"));
  SetMenuInfo_ = reinterpret_cast<decltype(SetMenuInfo_)>(GetProcAddress_(hModule,"SetMenuInfo"));
  EndMenu_ = reinterpret_cast<decltype(EndMenu_)>(GetProcAddress_(hModule,"EndMenu"));
  CalculatePopupWindowPosition_ = reinterpret_cast<decltype(CalculatePopupWindowPosition_)>(GetProcAddress_(hModule,"CalculatePopupWindowPosition"));
  InsertMenuItemA_ = reinterpret_cast<decltype(InsertMenuItemA_)>(GetProcAddress_(hModule,"InsertMenuItemA"));
  InsertMenuItemW_ = reinterpret_cast<decltype(InsertMenuItemW_)>(GetProcAddress_(hModule,"InsertMenuItemW"));
  GetMenuItemInfoA_ = reinterpret_cast<decltype(GetMenuItemInfoA_)>(GetProcAddress_(hModule,"GetMenuItemInfoA"));
  GetMenuItemInfoW_ = reinterpret_cast<decltype(GetMenuItemInfoW_)>(GetProcAddress_(hModule,"GetMenuItemInfoW"));
  SetMenuItemInfoA_ = reinterpret_cast<decltype(SetMenuItemInfoA_)>(GetProcAddress_(hModule,"SetMenuItemInfoA"));
  SetMenuItemInfoW_ = reinterpret_cast<decltype(SetMenuItemInfoW_)>(GetProcAddress_(hModule,"SetMenuItemInfoW"));
  GetMenuDefaultItem_ = reinterpret_cast<decltype(GetMenuDefaultItem_)>(GetProcAddress_(hModule,"GetMenuDefaultItem"));
  SetMenuDefaultItem_ = reinterpret_cast<decltype(SetMenuDefaultItem_)>(GetProcAddress_(hModule,"SetMenuDefaultItem"));
  GetMenuItemRect_ = reinterpret_cast<decltype(GetMenuItemRect_)>(GetProcAddress_(hModule,"GetMenuItemRect"));
  MenuItemFromPoint_ = reinterpret_cast<decltype(MenuItemFromPoint_)>(GetProcAddress_(hModule,"MenuItemFromPoint"));
  DragObject_ = reinterpret_cast<decltype(DragObject_)>(GetProcAddress_(hModule,"DragObject"));
  DragDetect_ = reinterpret_cast<decltype(DragDetect_)>(GetProcAddress_(hModule,"DragDetect"));
  DrawIcon_ = reinterpret_cast<decltype(DrawIcon_)>(GetProcAddress_(hModule,"DrawIcon"));
  DrawTextA_ = reinterpret_cast<decltype(DrawTextA_)>(GetProcAddress_(hModule,"DrawTextA"));
  DrawTextW_ = reinterpret_cast<decltype(DrawTextW_)>(GetProcAddress_(hModule,"DrawTextW"));
  DrawTextExA_ = reinterpret_cast<decltype(DrawTextExA_)>(GetProcAddress_(hModule,"DrawTextExA"));
  DrawTextExW_ = reinterpret_cast<decltype(DrawTextExW_)>(GetProcAddress_(hModule,"DrawTextExW"));
  GrayStringA_ = reinterpret_cast<decltype(GrayStringA_)>(GetProcAddress_(hModule,"GrayStringA"));
  GrayStringW_ = reinterpret_cast<decltype(GrayStringW_)>(GetProcAddress_(hModule,"GrayStringW"));
  DrawStateA_ = reinterpret_cast<decltype(DrawStateA_)>(GetProcAddress_(hModule,"DrawStateA"));
  DrawStateW_ = reinterpret_cast<decltype(DrawStateW_)>(GetProcAddress_(hModule,"DrawStateW"));
  TabbedTextOutA_ = reinterpret_cast<decltype(TabbedTextOutA_)>(GetProcAddress_(hModule,"TabbedTextOutA"));
  TabbedTextOutW_ = reinterpret_cast<decltype(TabbedTextOutW_)>(GetProcAddress_(hModule,"TabbedTextOutW"));
  GetTabbedTextExtentA_ = reinterpret_cast<decltype(GetTabbedTextExtentA_)>(GetProcAddress_(hModule,"GetTabbedTextExtentA"));
  GetTabbedTextExtentW_ = reinterpret_cast<decltype(GetTabbedTextExtentW_)>(GetProcAddress_(hModule,"GetTabbedTextExtentW"));
  UpdateWindow_ = reinterpret_cast<decltype(UpdateWindow_)>(GetProcAddress_(hModule,"UpdateWindow"));
  SetActiveWindow_ = reinterpret_cast<decltype(SetActiveWindow_)>(GetProcAddress_(hModule,"SetActiveWindow"));
  GetForegroundWindow_ = reinterpret_cast<decltype(GetForegroundWindow_)>(GetProcAddress_(hModule,"GetForegroundWindow"));
  PaintDesktop_ = reinterpret_cast<decltype(PaintDesktop_)>(GetProcAddress_(hModule,"PaintDesktop"));
  SwitchToThisWindow_ = reinterpret_cast<decltype(SwitchToThisWindow_)>(GetProcAddress_(hModule,"SwitchToThisWindow"));
  SetForegroundWindow_ = reinterpret_cast<decltype(SetForegroundWindow_)>(GetProcAddress_(hModule,"SetForegroundWindow"));
  AllowSetForegroundWindow_ = reinterpret_cast<decltype(AllowSetForegroundWindow_)>(GetProcAddress_(hModule,"AllowSetForegroundWindow"));
  LockSetForegroundWindow_ = reinterpret_cast<decltype(LockSetForegroundWindow_)>(GetProcAddress_(hModule,"LockSetForegroundWindow"));
  WindowFromDC_ = reinterpret_cast<decltype(WindowFromDC_)>(GetProcAddress_(hModule,"WindowFromDC"));
  GetDC_ = reinterpret_cast<decltype(GetDC_)>(GetProcAddress_(hModule,"GetDC"));
  GetDCEx_ = reinterpret_cast<decltype(GetDCEx_)>(GetProcAddress_(hModule,"GetDCEx"));
  GetWindowDC_ = reinterpret_cast<decltype(GetWindowDC_)>(GetProcAddress_(hModule,"GetWindowDC"));
  ReleaseDC_ = reinterpret_cast<decltype(ReleaseDC_)>(GetProcAddress_(hModule,"ReleaseDC"));
  BeginPaint_ = reinterpret_cast<decltype(BeginPaint_)>(GetProcAddress_(hModule,"BeginPaint"));
  EndPaint_ = reinterpret_cast<decltype(EndPaint_)>(GetProcAddress_(hModule,"EndPaint"));
  GetUpdateRect_ = reinterpret_cast<decltype(GetUpdateRect_)>(GetProcAddress_(hModule,"GetUpdateRect"));
  GetUpdateRgn_ = reinterpret_cast<decltype(GetUpdateRgn_)>(GetProcAddress_(hModule,"GetUpdateRgn"));
  SetWindowRgn_ = reinterpret_cast<decltype(SetWindowRgn_)>(GetProcAddress_(hModule,"SetWindowRgn"));
  GetWindowRgn_ = reinterpret_cast<decltype(GetWindowRgn_)>(GetProcAddress_(hModule,"GetWindowRgn"));
  GetWindowRgnBox_ = reinterpret_cast<decltype(GetWindowRgnBox_)>(GetProcAddress_(hModule,"GetWindowRgnBox"));
  ExcludeUpdateRgn_ = reinterpret_cast<decltype(ExcludeUpdateRgn_)>(GetProcAddress_(hModule,"ExcludeUpdateRgn"));
  InvalidateRect_ = reinterpret_cast<decltype(InvalidateRect_)>(GetProcAddress_(hModule,"InvalidateRect"));
  ValidateRect_ = reinterpret_cast<decltype(ValidateRect_)>(GetProcAddress_(hModule,"ValidateRect"));
  InvalidateRgn_ = reinterpret_cast<decltype(InvalidateRgn_)>(GetProcAddress_(hModule,"InvalidateRgn"));
  ValidateRgn_ = reinterpret_cast<decltype(ValidateRgn_)>(GetProcAddress_(hModule,"ValidateRgn"));
  RedrawWindow_ = reinterpret_cast<decltype(RedrawWindow_)>(GetProcAddress_(hModule,"RedrawWindow"));
  LockWindowUpdate_ = reinterpret_cast<decltype(LockWindowUpdate_)>(GetProcAddress_(hModule,"LockWindowUpdate"));
  ScrollWindow_ = reinterpret_cast<decltype(ScrollWindow_)>(GetProcAddress_(hModule,"ScrollWindow"));
  ScrollDC_ = reinterpret_cast<decltype(ScrollDC_)>(GetProcAddress_(hModule,"ScrollDC"));
  ScrollWindowEx_ = reinterpret_cast<decltype(ScrollWindowEx_)>(GetProcAddress_(hModule,"ScrollWindowEx"));
  SetScrollPos_ = reinterpret_cast<decltype(SetScrollPos_)>(GetProcAddress_(hModule,"SetScrollPos"));
  GetScrollPos_ = reinterpret_cast<decltype(GetScrollPos_)>(GetProcAddress_(hModule,"GetScrollPos"));
  SetScrollRange_ = reinterpret_cast<decltype(SetScrollRange_)>(GetProcAddress_(hModule,"SetScrollRange"));
  GetScrollRange_ = reinterpret_cast<decltype(GetScrollRange_)>(GetProcAddress_(hModule,"GetScrollRange"));
  ShowScrollBar_ = reinterpret_cast<decltype(ShowScrollBar_)>(GetProcAddress_(hModule,"ShowScrollBar"));
  EnableScrollBar_ = reinterpret_cast<decltype(EnableScrollBar_)>(GetProcAddress_(hModule,"EnableScrollBar"));
  SetPropA_ = reinterpret_cast<decltype(SetPropA_)>(GetProcAddress_(hModule,"SetPropA"));
  SetPropW_ = reinterpret_cast<decltype(SetPropW_)>(GetProcAddress_(hModule,"SetPropW"));
  GetPropA_ = reinterpret_cast<decltype(GetPropA_)>(GetProcAddress_(hModule,"GetPropA"));
  GetPropW_ = reinterpret_cast<decltype(GetPropW_)>(GetProcAddress_(hModule,"GetPropW"));
  RemovePropA_ = reinterpret_cast<decltype(RemovePropA_)>(GetProcAddress_(hModule,"RemovePropA"));
  RemovePropW_ = reinterpret_cast<decltype(RemovePropW_)>(GetProcAddress_(hModule,"RemovePropW"));
  EnumPropsExA_ = reinterpret_cast<decltype(EnumPropsExA_)>(GetProcAddress_(hModule,"EnumPropsExA"));
  EnumPropsExW_ = reinterpret_cast<decltype(EnumPropsExW_)>(GetProcAddress_(hModule,"EnumPropsExW"));
  EnumPropsA_ = reinterpret_cast<decltype(EnumPropsA_)>(GetProcAddress_(hModule,"EnumPropsA"));
  EnumPropsW_ = reinterpret_cast<decltype(EnumPropsW_)>(GetProcAddress_(hModule,"EnumPropsW"));
  SetWindowTextA_ = reinterpret_cast<decltype(SetWindowTextA_)>(GetProcAddress_(hModule,"SetWindowTextA"));
  SetWindowTextW_ = reinterpret_cast<decltype(SetWindowTextW_)>(GetProcAddress_(hModule,"SetWindowTextW"));
  GetWindowTextA_ = reinterpret_cast<decltype(GetWindowTextA_)>(GetProcAddress_(hModule,"GetWindowTextA"));
  GetWindowTextW_ = reinterpret_cast<decltype(GetWindowTextW_)>(GetProcAddress_(hModule,"GetWindowTextW"));
  GetWindowTextLengthA_ = reinterpret_cast<decltype(GetWindowTextLengthA_)>(GetProcAddress_(hModule,"GetWindowTextLengthA"));
  GetWindowTextLengthW_ = reinterpret_cast<decltype(GetWindowTextLengthW_)>(GetProcAddress_(hModule,"GetWindowTextLengthW"));
  GetClientRect_ = reinterpret_cast<decltype(GetClientRect_)>(GetProcAddress_(hModule,"GetClientRect"));
  GetWindowRect_ = reinterpret_cast<decltype(GetWindowRect_)>(GetProcAddress_(hModule,"GetWindowRect"));
  AdjustWindowRect_ = reinterpret_cast<decltype(AdjustWindowRect_)>(GetProcAddress_(hModule,"AdjustWindowRect"));
  AdjustWindowRectEx_ = reinterpret_cast<decltype(AdjustWindowRectEx_)>(GetProcAddress_(hModule,"AdjustWindowRectEx"));
  SetWindowContextHelpId_ = reinterpret_cast<decltype(SetWindowContextHelpId_)>(GetProcAddress_(hModule,"SetWindowContextHelpId"));
  GetWindowContextHelpId_ = reinterpret_cast<decltype(GetWindowContextHelpId_)>(GetProcAddress_(hModule,"GetWindowContextHelpId"));
  SetMenuContextHelpId_ = reinterpret_cast<decltype(SetMenuContextHelpId_)>(GetProcAddress_(hModule,"SetMenuContextHelpId"));
  GetMenuContextHelpId_ = reinterpret_cast<decltype(GetMenuContextHelpId_)>(GetProcAddress_(hModule,"GetMenuContextHelpId"));
  MessageBoxA_ = reinterpret_cast<decltype(MessageBoxA_)>(GetProcAddress_(hModule,"MessageBoxA"));
  MessageBoxW_ = reinterpret_cast<decltype(MessageBoxW_)>(GetProcAddress_(hModule,"MessageBoxW"));
  MessageBoxExA_ = reinterpret_cast<decltype(MessageBoxExA_)>(GetProcAddress_(hModule,"MessageBoxExA"));
  MessageBoxExW_ = reinterpret_cast<decltype(MessageBoxExW_)>(GetProcAddress_(hModule,"MessageBoxExW"));
  MessageBoxIndirectA_ = reinterpret_cast<decltype(MessageBoxIndirectA_)>(GetProcAddress_(hModule,"MessageBoxIndirectA"));
  MessageBoxIndirectW_ = reinterpret_cast<decltype(MessageBoxIndirectW_)>(GetProcAddress_(hModule,"MessageBoxIndirectW"));
  MessageBeep_ = reinterpret_cast<decltype(MessageBeep_)>(GetProcAddress_(hModule,"MessageBeep"));
  ShowCursor_ = reinterpret_cast<decltype(ShowCursor_)>(GetProcAddress_(hModule,"ShowCursor"));
  SetCursorPos_ = reinterpret_cast<decltype(SetCursorPos_)>(GetProcAddress_(hModule,"SetCursorPos"));
  SetCursor_ = reinterpret_cast<decltype(SetCursor_)>(GetProcAddress_(hModule,"SetCursor"));
  GetCursorPos_ = reinterpret_cast<decltype(GetCursorPos_)>(GetProcAddress_(hModule,"GetCursorPos"));
  ClipCursor_ = reinterpret_cast<decltype(ClipCursor_)>(GetProcAddress_(hModule,"ClipCursor"));
  GetClipCursor_ = reinterpret_cast<decltype(GetClipCursor_)>(GetProcAddress_(hModule,"GetClipCursor"));
  GetCursor_ = reinterpret_cast<decltype(GetCursor_)>(GetProcAddress_(hModule,"GetCursor"));
  CreateCaret_ = reinterpret_cast<decltype(CreateCaret_)>(GetProcAddress_(hModule,"CreateCaret"));
  GetCaretBlinkTime_ = reinterpret_cast<decltype(GetCaretBlinkTime_)>(GetProcAddress_(hModule,"GetCaretBlinkTime"));
  SetCaretBlinkTime_ = reinterpret_cast<decltype(SetCaretBlinkTime_)>(GetProcAddress_(hModule,"SetCaretBlinkTime"));
  DestroyCaret_ = reinterpret_cast<decltype(DestroyCaret_)>(GetProcAddress_(hModule,"DestroyCaret"));
  HideCaret_ = reinterpret_cast<decltype(HideCaret_)>(GetProcAddress_(hModule,"HideCaret"));
  ShowCaret_ = reinterpret_cast<decltype(ShowCaret_)>(GetProcAddress_(hModule,"ShowCaret"));
  SetCaretPos_ = reinterpret_cast<decltype(SetCaretPos_)>(GetProcAddress_(hModule,"SetCaretPos"));
  GetCaretPos_ = reinterpret_cast<decltype(GetCaretPos_)>(GetProcAddress_(hModule,"GetCaretPos"));
  ClientToScreen_ = reinterpret_cast<decltype(ClientToScreen_)>(GetProcAddress_(hModule,"ClientToScreen"));
  ScreenToClient_ = reinterpret_cast<decltype(ScreenToClient_)>(GetProcAddress_(hModule,"ScreenToClient"));
  MapWindowPoints_ = reinterpret_cast<decltype(MapWindowPoints_)>(GetProcAddress_(hModule,"MapWindowPoints"));
  WindowFromPoint_ = reinterpret_cast<decltype(WindowFromPoint_)>(GetProcAddress_(hModule,"WindowFromPoint"));
  ChildWindowFromPoint_ = reinterpret_cast<decltype(ChildWindowFromPoint_)>(GetProcAddress_(hModule,"ChildWindowFromPoint"));
  ChildWindowFromPointEx_ = reinterpret_cast<decltype(ChildWindowFromPointEx_)>(GetProcAddress_(hModule,"ChildWindowFromPointEx"));
  SetPhysicalCursorPos_ = reinterpret_cast<decltype(SetPhysicalCursorPos_)>(GetProcAddress_(hModule,"SetPhysicalCursorPos"));
  GetPhysicalCursorPos_ = reinterpret_cast<decltype(GetPhysicalCursorPos_)>(GetProcAddress_(hModule,"GetPhysicalCursorPos"));
  LogicalToPhysicalPoint_ = reinterpret_cast<decltype(LogicalToPhysicalPoint_)>(GetProcAddress_(hModule,"LogicalToPhysicalPoint"));
  PhysicalToLogicalPoint_ = reinterpret_cast<decltype(PhysicalToLogicalPoint_)>(GetProcAddress_(hModule,"PhysicalToLogicalPoint"));
  WindowFromPhysicalPoint_ = reinterpret_cast<decltype(WindowFromPhysicalPoint_)>(GetProcAddress_(hModule,"WindowFromPhysicalPoint"));
  GetSysColor_ = reinterpret_cast<decltype(GetSysColor_)>(GetProcAddress_(hModule,"GetSysColor"));
  GetSysColorBrush_ = reinterpret_cast<decltype(GetSysColorBrush_)>(GetProcAddress_(hModule,"GetSysColorBrush"));
  SetSysColors_ = reinterpret_cast<decltype(SetSysColors_)>(GetProcAddress_(hModule,"SetSysColors"));
  DrawFocusRect_ = reinterpret_cast<decltype(DrawFocusRect_)>(GetProcAddress_(hModule,"DrawFocusRect"));
  FillRect_ = reinterpret_cast<decltype(FillRect_)>(GetProcAddress_(hModule,"FillRect"));
  FrameRect_ = reinterpret_cast<decltype(FrameRect_)>(GetProcAddress_(hModule,"FrameRect"));
  InvertRect_ = reinterpret_cast<decltype(InvertRect_)>(GetProcAddress_(hModule,"InvertRect"));
  SetRect_ = reinterpret_cast<decltype(SetRect_)>(GetProcAddress_(hModule,"SetRect"));
  SetRectEmpty_ = reinterpret_cast<decltype(SetRectEmpty_)>(GetProcAddress_(hModule,"SetRectEmpty"));
  CopyRect_ = reinterpret_cast<decltype(CopyRect_)>(GetProcAddress_(hModule,"CopyRect"));
  InflateRect_ = reinterpret_cast<decltype(InflateRect_)>(GetProcAddress_(hModule,"InflateRect"));
  IntersectRect_ = reinterpret_cast<decltype(IntersectRect_)>(GetProcAddress_(hModule,"IntersectRect"));
  UnionRect_ = reinterpret_cast<decltype(UnionRect_)>(GetProcAddress_(hModule,"UnionRect"));
  SubtractRect_ = reinterpret_cast<decltype(SubtractRect_)>(GetProcAddress_(hModule,"SubtractRect"));
  OffsetRect_ = reinterpret_cast<decltype(OffsetRect_)>(GetProcAddress_(hModule,"OffsetRect"));
  IsRectEmpty_ = reinterpret_cast<decltype(IsRectEmpty_)>(GetProcAddress_(hModule,"IsRectEmpty"));
  EqualRect_ = reinterpret_cast<decltype(EqualRect_)>(GetProcAddress_(hModule,"EqualRect"));
  PtInRect_ = reinterpret_cast<decltype(PtInRect_)>(GetProcAddress_(hModule,"PtInRect"));
  GetWindowWord_ = reinterpret_cast<decltype(GetWindowWord_)>(GetProcAddress_(hModule,"GetWindowWord"));
  SetWindowWord_ = reinterpret_cast<decltype(SetWindowWord_)>(GetProcAddress_(hModule,"SetWindowWord"));
  GetWindowLongA_ = reinterpret_cast<decltype(GetWindowLongA_)>(GetProcAddress_(hModule,"GetWindowLongA"));
  GetWindowLongW_ = reinterpret_cast<decltype(GetWindowLongW_)>(GetProcAddress_(hModule,"GetWindowLongW"));
  SetWindowLongA_ = reinterpret_cast<decltype(SetWindowLongA_)>(GetProcAddress_(hModule,"SetWindowLongA"));
  SetWindowLongW_ = reinterpret_cast<decltype(SetWindowLongW_)>(GetProcAddress_(hModule,"SetWindowLongW"));
  GetWindowLongPtrA_ = reinterpret_cast<decltype(GetWindowLongPtrA_)>(GetProcAddress_(hModule,"GetWindowLongPtrA"));
  GetWindowLongPtrW_ = reinterpret_cast<decltype(GetWindowLongPtrW_)>(GetProcAddress_(hModule,"GetWindowLongPtrW"));
  SetWindowLongPtrA_ = reinterpret_cast<decltype(SetWindowLongPtrA_)>(GetProcAddress_(hModule,"SetWindowLongPtrA"));
  SetWindowLongPtrW_ = reinterpret_cast<decltype(SetWindowLongPtrW_)>(GetProcAddress_(hModule,"SetWindowLongPtrW"));
  GetClassWord_ = reinterpret_cast<decltype(GetClassWord_)>(GetProcAddress_(hModule,"GetClassWord"));
  SetClassWord_ = reinterpret_cast<decltype(SetClassWord_)>(GetProcAddress_(hModule,"SetClassWord"));
  GetClassLongA_ = reinterpret_cast<decltype(GetClassLongA_)>(GetProcAddress_(hModule,"GetClassLongA"));
  GetClassLongW_ = reinterpret_cast<decltype(GetClassLongW_)>(GetProcAddress_(hModule,"GetClassLongW"));
  SetClassLongA_ = reinterpret_cast<decltype(SetClassLongA_)>(GetProcAddress_(hModule,"SetClassLongA"));
  SetClassLongW_ = reinterpret_cast<decltype(SetClassLongW_)>(GetProcAddress_(hModule,"SetClassLongW"));
  GetClassLongPtrA_ = reinterpret_cast<decltype(GetClassLongPtrA_)>(GetProcAddress_(hModule,"GetClassLongPtrA"));
  GetClassLongPtrW_ = reinterpret_cast<decltype(GetClassLongPtrW_)>(GetProcAddress_(hModule,"GetClassLongPtrW"));
  SetClassLongPtrA_ = reinterpret_cast<decltype(SetClassLongPtrA_)>(GetProcAddress_(hModule,"SetClassLongPtrA"));
  SetClassLongPtrW_ = reinterpret_cast<decltype(SetClassLongPtrW_)>(GetProcAddress_(hModule,"SetClassLongPtrW"));
  GetProcessDefaultLayout_ = reinterpret_cast<decltype(GetProcessDefaultLayout_)>(GetProcAddress_(hModule,"GetProcessDefaultLayout"));
  SetProcessDefaultLayout_ = reinterpret_cast<decltype(SetProcessDefaultLayout_)>(GetProcAddress_(hModule,"SetProcessDefaultLayout"));
  GetDesktopWindow_ = reinterpret_cast<decltype(GetDesktopWindow_)>(GetProcAddress_(hModule,"GetDesktopWindow"));
  GetParent_ = reinterpret_cast<decltype(GetParent_)>(GetProcAddress_(hModule,"GetParent"));
  SetParent_ = reinterpret_cast<decltype(SetParent_)>(GetProcAddress_(hModule,"SetParent"));
  EnumChildWindows_ = reinterpret_cast<decltype(EnumChildWindows_)>(GetProcAddress_(hModule,"EnumChildWindows"));
  FindWindowA_ = reinterpret_cast<decltype(FindWindowA_)>(GetProcAddress_(hModule,"FindWindowA"));
  FindWindowW_ = reinterpret_cast<decltype(FindWindowW_)>(GetProcAddress_(hModule,"FindWindowW"));
  FindWindowExA_ = reinterpret_cast<decltype(FindWindowExA_)>(GetProcAddress_(hModule,"FindWindowExA"));
  FindWindowExW_ = reinterpret_cast<decltype(FindWindowExW_)>(GetProcAddress_(hModule,"FindWindowExW"));
  GetShellWindow_ = reinterpret_cast<decltype(GetShellWindow_)>(GetProcAddress_(hModule,"GetShellWindow"));
  RegisterShellHookWindow_ = reinterpret_cast<decltype(RegisterShellHookWindow_)>(GetProcAddress_(hModule,"RegisterShellHookWindow"));
  DeregisterShellHookWindow_ = reinterpret_cast<decltype(DeregisterShellHookWindow_)>(GetProcAddress_(hModule,"DeregisterShellHookWindow"));
  EnumWindows_ = reinterpret_cast<decltype(EnumWindows_)>(GetProcAddress_(hModule,"EnumWindows"));
  EnumThreadWindows_ = reinterpret_cast<decltype(EnumThreadWindows_)>(GetProcAddress_(hModule,"EnumThreadWindows"));
  GetClassNameA_ = reinterpret_cast<decltype(GetClassNameA_)>(GetProcAddress_(hModule,"GetClassNameA"));
  GetClassNameW_ = reinterpret_cast<decltype(GetClassNameW_)>(GetProcAddress_(hModule,"GetClassNameW"));
  GetTopWindow_ = reinterpret_cast<decltype(GetTopWindow_)>(GetProcAddress_(hModule,"GetTopWindow"));
  GetWindowThreadProcessId_ = reinterpret_cast<decltype(GetWindowThreadProcessId_)>(GetProcAddress_(hModule,"GetWindowThreadProcessId"));
  IsGUIThread_ = reinterpret_cast<decltype(IsGUIThread_)>(GetProcAddress_(hModule,"IsGUIThread"));
  GetLastActivePopup_ = reinterpret_cast<decltype(GetLastActivePopup_)>(GetProcAddress_(hModule,"GetLastActivePopup"));
  GetWindow_ = reinterpret_cast<decltype(GetWindow_)>(GetProcAddress_(hModule,"GetWindow"));
  SetWindowsHookA_ = reinterpret_cast<decltype(SetWindowsHookA_)>(GetProcAddress_(hModule,"SetWindowsHookA"));
  SetWindowsHookW_ = reinterpret_cast<decltype(SetWindowsHookW_)>(GetProcAddress_(hModule,"SetWindowsHookW"));
  UnhookWindowsHook_ = reinterpret_cast<decltype(UnhookWindowsHook_)>(GetProcAddress_(hModule,"UnhookWindowsHook"));
  SetWindowsHookExA_ = reinterpret_cast<decltype(SetWindowsHookExA_)>(GetProcAddress_(hModule,"SetWindowsHookExA"));
  SetWindowsHookExW_ = reinterpret_cast<decltype(SetWindowsHookExW_)>(GetProcAddress_(hModule,"SetWindowsHookExW"));
  UnhookWindowsHookEx_ = reinterpret_cast<decltype(UnhookWindowsHookEx_)>(GetProcAddress_(hModule,"UnhookWindowsHookEx"));
  CallNextHookEx_ = reinterpret_cast<decltype(CallNextHookEx_)>(GetProcAddress_(hModule,"CallNextHookEx"));
  CheckMenuRadioItem_ = reinterpret_cast<decltype(CheckMenuRadioItem_)>(GetProcAddress_(hModule,"CheckMenuRadioItem"));
  LoadBitmapA_ = reinterpret_cast<decltype(LoadBitmapA_)>(GetProcAddress_(hModule,"LoadBitmapA"));
  LoadBitmapW_ = reinterpret_cast<decltype(LoadBitmapW_)>(GetProcAddress_(hModule,"LoadBitmapW"));
  LoadCursorA_ = reinterpret_cast<decltype(LoadCursorA_)>(GetProcAddress_(hModule,"LoadCursorA"));
  LoadCursorW_ = reinterpret_cast<decltype(LoadCursorW_)>(GetProcAddress_(hModule,"LoadCursorW"));
  LoadCursorFromFileA_ = reinterpret_cast<decltype(LoadCursorFromFileA_)>(GetProcAddress_(hModule,"LoadCursorFromFileA"));
  LoadCursorFromFileW_ = reinterpret_cast<decltype(LoadCursorFromFileW_)>(GetProcAddress_(hModule,"LoadCursorFromFileW"));
  CreateCursor_ = reinterpret_cast<decltype(CreateCursor_)>(GetProcAddress_(hModule,"CreateCursor"));
  DestroyCursor_ = reinterpret_cast<decltype(DestroyCursor_)>(GetProcAddress_(hModule,"DestroyCursor"));
  SetSystemCursor_ = reinterpret_cast<decltype(SetSystemCursor_)>(GetProcAddress_(hModule,"SetSystemCursor"));
  LoadIconA_ = reinterpret_cast<decltype(LoadIconA_)>(GetProcAddress_(hModule,"LoadIconA"));
  LoadIconW_ = reinterpret_cast<decltype(LoadIconW_)>(GetProcAddress_(hModule,"LoadIconW"));
  PrivateExtractIconsA_ = reinterpret_cast<decltype(PrivateExtractIconsA_)>(GetProcAddress_(hModule,"PrivateExtractIconsA"));
  PrivateExtractIconsW_ = reinterpret_cast<decltype(PrivateExtractIconsW_)>(GetProcAddress_(hModule,"PrivateExtractIconsW"));
  CreateIcon_ = reinterpret_cast<decltype(CreateIcon_)>(GetProcAddress_(hModule,"CreateIcon"));
  DestroyIcon_ = reinterpret_cast<decltype(DestroyIcon_)>(GetProcAddress_(hModule,"DestroyIcon"));
  LookupIconIdFromDirectory_ = reinterpret_cast<decltype(LookupIconIdFromDirectory_)>(GetProcAddress_(hModule,"LookupIconIdFromDirectory"));
  LookupIconIdFromDirectoryEx_ = reinterpret_cast<decltype(LookupIconIdFromDirectoryEx_)>(GetProcAddress_(hModule,"LookupIconIdFromDirectoryEx"));
  CreateIconFromResource_ = reinterpret_cast<decltype(CreateIconFromResource_)>(GetProcAddress_(hModule,"CreateIconFromResource"));
  CreateIconFromResourceEx_ = reinterpret_cast<decltype(CreateIconFromResourceEx_)>(GetProcAddress_(hModule,"CreateIconFromResourceEx"));
  LoadImageA_ = reinterpret_cast<decltype(LoadImageA_)>(GetProcAddress_(hModule,"LoadImageA"));
  LoadImageW_ = reinterpret_cast<decltype(LoadImageW_)>(GetProcAddress_(hModule,"LoadImageW"));
  CopyImage_ = reinterpret_cast<decltype(CopyImage_)>(GetProcAddress_(hModule,"CopyImage"));
  DrawIconEx_ = reinterpret_cast<decltype(DrawIconEx_)>(GetProcAddress_(hModule,"DrawIconEx"));
  CreateIconIndirect_ = reinterpret_cast<decltype(CreateIconIndirect_)>(GetProcAddress_(hModule,"CreateIconIndirect"));
  CopyIcon_ = reinterpret_cast<decltype(CopyIcon_)>(GetProcAddress_(hModule,"CopyIcon"));
  GetIconInfo_ = reinterpret_cast<decltype(GetIconInfo_)>(GetProcAddress_(hModule,"GetIconInfo"));
  GetIconInfoExA_ = reinterpret_cast<decltype(GetIconInfoExA_)>(GetProcAddress_(hModule,"GetIconInfoExA"));
  GetIconInfoExW_ = reinterpret_cast<decltype(GetIconInfoExW_)>(GetProcAddress_(hModule,"GetIconInfoExW"));
  LoadStringA_ = reinterpret_cast<decltype(LoadStringA_)>(GetProcAddress_(hModule,"LoadStringA"));
  LoadStringW_ = reinterpret_cast<decltype(LoadStringW_)>(GetProcAddress_(hModule,"LoadStringW"));
  IsDialogMessageA_ = reinterpret_cast<decltype(IsDialogMessageA_)>(GetProcAddress_(hModule,"IsDialogMessageA"));
  IsDialogMessageW_ = reinterpret_cast<decltype(IsDialogMessageW_)>(GetProcAddress_(hModule,"IsDialogMessageW"));
  MapDialogRect_ = reinterpret_cast<decltype(MapDialogRect_)>(GetProcAddress_(hModule,"MapDialogRect"));
  DlgDirListA_ = reinterpret_cast<decltype(DlgDirListA_)>(GetProcAddress_(hModule,"DlgDirListA"));
  DlgDirListW_ = reinterpret_cast<decltype(DlgDirListW_)>(GetProcAddress_(hModule,"DlgDirListW"));
  DlgDirSelectExA_ = reinterpret_cast<decltype(DlgDirSelectExA_)>(GetProcAddress_(hModule,"DlgDirSelectExA"));
  DlgDirSelectExW_ = reinterpret_cast<decltype(DlgDirSelectExW_)>(GetProcAddress_(hModule,"DlgDirSelectExW"));
  DlgDirListComboBoxA_ = reinterpret_cast<decltype(DlgDirListComboBoxA_)>(GetProcAddress_(hModule,"DlgDirListComboBoxA"));
  DlgDirListComboBoxW_ = reinterpret_cast<decltype(DlgDirListComboBoxW_)>(GetProcAddress_(hModule,"DlgDirListComboBoxW"));
  DlgDirSelectComboBoxExA_ = reinterpret_cast<decltype(DlgDirSelectComboBoxExA_)>(GetProcAddress_(hModule,"DlgDirSelectComboBoxExA"));
  DlgDirSelectComboBoxExW_ = reinterpret_cast<decltype(DlgDirSelectComboBoxExW_)>(GetProcAddress_(hModule,"DlgDirSelectComboBoxExW"));
  SetScrollInfo_ = reinterpret_cast<decltype(SetScrollInfo_)>(GetProcAddress_(hModule,"SetScrollInfo"));
  GetScrollInfo_ = reinterpret_cast<decltype(GetScrollInfo_)>(GetProcAddress_(hModule,"GetScrollInfo"));
  DefFrameProcA_ = reinterpret_cast<decltype(DefFrameProcA_)>(GetProcAddress_(hModule,"DefFrameProcA"));
  DefFrameProcW_ = reinterpret_cast<decltype(DefFrameProcW_)>(GetProcAddress_(hModule,"DefFrameProcW"));
  DefMDIChildProcA_ = reinterpret_cast<decltype(DefMDIChildProcA_)>(GetProcAddress_(hModule,"DefMDIChildProcA"));
  DefMDIChildProcW_ = reinterpret_cast<decltype(DefMDIChildProcW_)>(GetProcAddress_(hModule,"DefMDIChildProcW"));
  TranslateMDISysAccel_ = reinterpret_cast<decltype(TranslateMDISysAccel_)>(GetProcAddress_(hModule,"TranslateMDISysAccel"));
  ArrangeIconicWindows_ = reinterpret_cast<decltype(ArrangeIconicWindows_)>(GetProcAddress_(hModule,"ArrangeIconicWindows"));
  CreateMDIWindowA_ = reinterpret_cast<decltype(CreateMDIWindowA_)>(GetProcAddress_(hModule,"CreateMDIWindowA"));
  CreateMDIWindowW_ = reinterpret_cast<decltype(CreateMDIWindowW_)>(GetProcAddress_(hModule,"CreateMDIWindowW"));
  TileWindows_ = reinterpret_cast<decltype(TileWindows_)>(GetProcAddress_(hModule,"TileWindows"));
  CascadeWindows_ = reinterpret_cast<decltype(CascadeWindows_)>(GetProcAddress_(hModule,"CascadeWindows"));
  WinHelpA_ = reinterpret_cast<decltype(WinHelpA_)>(GetProcAddress_(hModule,"WinHelpA"));
  WinHelpW_ = reinterpret_cast<decltype(WinHelpW_)>(GetProcAddress_(hModule,"WinHelpW"));
  GetGuiResources_ = reinterpret_cast<decltype(GetGuiResources_)>(GetProcAddress_(hModule,"GetGuiResources"));
  ChangeDisplaySettingsA_ = reinterpret_cast<decltype(ChangeDisplaySettingsA_)>(GetProcAddress_(hModule,"ChangeDisplaySettingsA"));
  ChangeDisplaySettingsW_ = reinterpret_cast<decltype(ChangeDisplaySettingsW_)>(GetProcAddress_(hModule,"ChangeDisplaySettingsW"));
  ChangeDisplaySettingsExA_ = reinterpret_cast<decltype(ChangeDisplaySettingsExA_)>(GetProcAddress_(hModule,"ChangeDisplaySettingsExA"));
  ChangeDisplaySettingsExW_ = reinterpret_cast<decltype(ChangeDisplaySettingsExW_)>(GetProcAddress_(hModule,"ChangeDisplaySettingsExW"));
  EnumDisplaySettingsA_ = reinterpret_cast<decltype(EnumDisplaySettingsA_)>(GetProcAddress_(hModule,"EnumDisplaySettingsA"));
  EnumDisplaySettingsW_ = reinterpret_cast<decltype(EnumDisplaySettingsW_)>(GetProcAddress_(hModule,"EnumDisplaySettingsW"));
  EnumDisplaySettingsExA_ = reinterpret_cast<decltype(EnumDisplaySettingsExA_)>(GetProcAddress_(hModule,"EnumDisplaySettingsExA"));
  EnumDisplaySettingsExW_ = reinterpret_cast<decltype(EnumDisplaySettingsExW_)>(GetProcAddress_(hModule,"EnumDisplaySettingsExW"));
  EnumDisplayDevicesA_ = reinterpret_cast<decltype(EnumDisplayDevicesA_)>(GetProcAddress_(hModule,"EnumDisplayDevicesA"));
  EnumDisplayDevicesW_ = reinterpret_cast<decltype(EnumDisplayDevicesW_)>(GetProcAddress_(hModule,"EnumDisplayDevicesW"));
  GetDisplayConfigBufferSizes_ = reinterpret_cast<decltype(GetDisplayConfigBufferSizes_)>(GetProcAddress_(hModule,"GetDisplayConfigBufferSizes"));
  SetDisplayConfig_ = reinterpret_cast<decltype(SetDisplayConfig_)>(GetProcAddress_(hModule,"SetDisplayConfig"));
  QueryDisplayConfig_ = reinterpret_cast<decltype(QueryDisplayConfig_)>(GetProcAddress_(hModule,"QueryDisplayConfig"));
  DisplayConfigGetDeviceInfo_ = reinterpret_cast<decltype(DisplayConfigGetDeviceInfo_)>(GetProcAddress_(hModule,"DisplayConfigGetDeviceInfo"));
  DisplayConfigSetDeviceInfo_ = reinterpret_cast<decltype(DisplayConfigSetDeviceInfo_)>(GetProcAddress_(hModule,"DisplayConfigSetDeviceInfo"));
  SystemParametersInfoA_ = reinterpret_cast<decltype(SystemParametersInfoA_)>(GetProcAddress_(hModule,"SystemParametersInfoA"));
  SystemParametersInfoW_ = reinterpret_cast<decltype(SystemParametersInfoW_)>(GetProcAddress_(hModule,"SystemParametersInfoW"));
  SetDebugErrorLevel_ = reinterpret_cast<decltype(SetDebugErrorLevel_)>(GetProcAddress_(hModule,"SetDebugErrorLevel"));
  SetLastErrorEx_ = reinterpret_cast<decltype(SetLastErrorEx_)>(GetProcAddress_(hModule,"SetLastErrorEx"));
  InternalGetWindowText_ = reinterpret_cast<decltype(InternalGetWindowText_)>(GetProcAddress_(hModule,"InternalGetWindowText"));
  CancelShutdown_ = reinterpret_cast<decltype(CancelShutdown_)>(GetProcAddress_(hModule,"CancelShutdown"));
  MonitorFromPoint_ = reinterpret_cast<decltype(MonitorFromPoint_)>(GetProcAddress_(hModule,"MonitorFromPoint"));
  MonitorFromRect_ = reinterpret_cast<decltype(MonitorFromRect_)>(GetProcAddress_(hModule,"MonitorFromRect"));
  MonitorFromWindow_ = reinterpret_cast<decltype(MonitorFromWindow_)>(GetProcAddress_(hModule,"MonitorFromWindow"));
  EndTask_ = reinterpret_cast<decltype(EndTask_)>(GetProcAddress_(hModule,"EndTask"));
  SoundSentry_ = reinterpret_cast<decltype(SoundSentry_)>(GetProcAddress_(hModule,"SoundSentry"));
  GetMonitorInfoA_ = reinterpret_cast<decltype(GetMonitorInfoA_)>(GetProcAddress_(hModule,"GetMonitorInfoA"));
  GetMonitorInfoW_ = reinterpret_cast<decltype(GetMonitorInfoW_)>(GetProcAddress_(hModule,"GetMonitorInfoW"));
  EnumDisplayMonitors_ = reinterpret_cast<decltype(EnumDisplayMonitors_)>(GetProcAddress_(hModule,"EnumDisplayMonitors"));
  NotifyWinEvent_ = reinterpret_cast<decltype(NotifyWinEvent_)>(GetProcAddress_(hModule,"NotifyWinEvent"));
  SetWinEventHook_ = reinterpret_cast<decltype(SetWinEventHook_)>(GetProcAddress_(hModule,"SetWinEventHook"));
  IsWinEventHookInstalled_ = reinterpret_cast<decltype(IsWinEventHookInstalled_)>(GetProcAddress_(hModule,"IsWinEventHookInstalled"));
  UnhookWinEvent_ = reinterpret_cast<decltype(UnhookWinEvent_)>(GetProcAddress_(hModule,"UnhookWinEvent"));
  GetGUIThreadInfo_ = reinterpret_cast<decltype(GetGUIThreadInfo_)>(GetProcAddress_(hModule,"GetGUIThreadInfo"));
  BlockInput_ = reinterpret_cast<decltype(BlockInput_)>(GetProcAddress_(hModule,"BlockInput"));
  GetWindowModuleFileNameA_ = reinterpret_cast<decltype(GetWindowModuleFileNameA_)>(GetProcAddress_(hModule,"GetWindowModuleFileNameA"));
  GetWindowModuleFileNameW_ = reinterpret_cast<decltype(GetWindowModuleFileNameW_)>(GetProcAddress_(hModule,"GetWindowModuleFileNameW"));
  SetProcessDPIAware_ = reinterpret_cast<decltype(SetProcessDPIAware_)>(GetProcAddress_(hModule,"SetProcessDPIAware"));
  IsProcessDPIAware_ = reinterpret_cast<decltype(IsProcessDPIAware_)>(GetProcAddress_(hModule,"IsProcessDPIAware"));
  GetCursorInfo_ = reinterpret_cast<decltype(GetCursorInfo_)>(GetProcAddress_(hModule,"GetCursorInfo"));
  GetWindowInfo_ = reinterpret_cast<decltype(GetWindowInfo_)>(GetProcAddress_(hModule,"GetWindowInfo"));
  GetTitleBarInfo_ = reinterpret_cast<decltype(GetTitleBarInfo_)>(GetProcAddress_(hModule,"GetTitleBarInfo"));
  GetMenuBarInfo_ = reinterpret_cast<decltype(GetMenuBarInfo_)>(GetProcAddress_(hModule,"GetMenuBarInfo"));
  GetScrollBarInfo_ = reinterpret_cast<decltype(GetScrollBarInfo_)>(GetProcAddress_(hModule,"GetScrollBarInfo"));
  GetComboBoxInfo_ = reinterpret_cast<decltype(GetComboBoxInfo_)>(GetProcAddress_(hModule,"GetComboBoxInfo"));
  GetAncestor_ = reinterpret_cast<decltype(GetAncestor_)>(GetProcAddress_(hModule,"GetAncestor"));
  RealChildWindowFromPoint_ = reinterpret_cast<decltype(RealChildWindowFromPoint_)>(GetProcAddress_(hModule,"RealChildWindowFromPoint"));
  RealGetWindowClassA_ = reinterpret_cast<decltype(RealGetWindowClassA_)>(GetProcAddress_(hModule,"RealGetWindowClassA"));
  RealGetWindowClassW_ = reinterpret_cast<decltype(RealGetWindowClassW_)>(GetProcAddress_(hModule,"RealGetWindowClassW"));
  GetAltTabInfoA_ = reinterpret_cast<decltype(GetAltTabInfoA_)>(GetProcAddress_(hModule,"GetAltTabInfoA"));
  GetAltTabInfoW_ = reinterpret_cast<decltype(GetAltTabInfoW_)>(GetProcAddress_(hModule,"GetAltTabInfoW"));
  GetListBoxInfo_ = reinterpret_cast<decltype(GetListBoxInfo_)>(GetProcAddress_(hModule,"GetListBoxInfo"));
  LockWorkStation_ = reinterpret_cast<decltype(LockWorkStation_)>(GetProcAddress_(hModule,"LockWorkStation"));
  UserHandleGrantAccess_ = reinterpret_cast<decltype(UserHandleGrantAccess_)>(GetProcAddress_(hModule,"UserHandleGrantAccess"));
  GetRawInputData_ = reinterpret_cast<decltype(GetRawInputData_)>(GetProcAddress_(hModule,"GetRawInputData"));
  GetRawInputDeviceInfoA_ = reinterpret_cast<decltype(GetRawInputDeviceInfoA_)>(GetProcAddress_(hModule,"GetRawInputDeviceInfoA"));
  GetRawInputDeviceInfoW_ = reinterpret_cast<decltype(GetRawInputDeviceInfoW_)>(GetProcAddress_(hModule,"GetRawInputDeviceInfoW"));
  GetRawInputBuffer_ = reinterpret_cast<decltype(GetRawInputBuffer_)>(GetProcAddress_(hModule,"GetRawInputBuffer"));
  RegisterRawInputDevices_ = reinterpret_cast<decltype(RegisterRawInputDevices_)>(GetProcAddress_(hModule,"RegisterRawInputDevices"));
  GetRegisteredRawInputDevices_ = reinterpret_cast<decltype(GetRegisteredRawInputDevices_)>(GetProcAddress_(hModule,"GetRegisteredRawInputDevices"));
  GetRawInputDeviceList_ = reinterpret_cast<decltype(GetRawInputDeviceList_)>(GetProcAddress_(hModule,"GetRawInputDeviceList"));
  DefRawInputProc_ = reinterpret_cast<decltype(DefRawInputProc_)>(GetProcAddress_(hModule,"DefRawInputProc"));
  GetPointerDevices_ = reinterpret_cast<decltype(GetPointerDevices_)>(GetProcAddress_(hModule,"GetPointerDevices"));
  GetPointerDevice_ = reinterpret_cast<decltype(GetPointerDevice_)>(GetProcAddress_(hModule,"GetPointerDevice"));
  GetPointerDeviceProperties_ = reinterpret_cast<decltype(GetPointerDeviceProperties_)>(GetProcAddress_(hModule,"GetPointerDeviceProperties"));
  RegisterPointerDeviceNotifications_ = reinterpret_cast<decltype(RegisterPointerDeviceNotifications_)>(GetProcAddress_(hModule,"RegisterPointerDeviceNotifications"));
  GetPointerDeviceRects_ = reinterpret_cast<decltype(GetPointerDeviceRects_)>(GetProcAddress_(hModule,"GetPointerDeviceRects"));
  GetPointerDeviceCursors_ = reinterpret_cast<decltype(GetPointerDeviceCursors_)>(GetProcAddress_(hModule,"GetPointerDeviceCursors"));
  GetRawPointerDeviceData_ = reinterpret_cast<decltype(GetRawPointerDeviceData_)>(GetProcAddress_(hModule,"GetRawPointerDeviceData"));
  ChangeWindowMessageFilter_ = reinterpret_cast<decltype(ChangeWindowMessageFilter_)>(GetProcAddress_(hModule,"ChangeWindowMessageFilter"));
  ChangeWindowMessageFilterEx_ = reinterpret_cast<decltype(ChangeWindowMessageFilterEx_)>(GetProcAddress_(hModule,"ChangeWindowMessageFilterEx"));
  GetGestureInfo_ = reinterpret_cast<decltype(GetGestureInfo_)>(GetProcAddress_(hModule,"GetGestureInfo"));
  GetGestureExtraArgs_ = reinterpret_cast<decltype(GetGestureExtraArgs_)>(GetProcAddress_(hModule,"GetGestureExtraArgs"));
  CloseGestureInfoHandle_ = reinterpret_cast<decltype(CloseGestureInfoHandle_)>(GetProcAddress_(hModule,"CloseGestureInfoHandle"));
  SetGestureConfig_ = reinterpret_cast<decltype(SetGestureConfig_)>(GetProcAddress_(hModule,"SetGestureConfig"));
  GetGestureConfig_ = reinterpret_cast<decltype(GetGestureConfig_)>(GetProcAddress_(hModule,"GetGestureConfig"));
  ShutdownBlockReasonCreate_ = reinterpret_cast<decltype(ShutdownBlockReasonCreate_)>(GetProcAddress_(hModule,"ShutdownBlockReasonCreate"));
  ShutdownBlockReasonQuery_ = reinterpret_cast<decltype(ShutdownBlockReasonQuery_)>(GetProcAddress_(hModule,"ShutdownBlockReasonQuery"));
  ShutdownBlockReasonDestroy_ = reinterpret_cast<decltype(ShutdownBlockReasonDestroy_)>(GetProcAddress_(hModule,"ShutdownBlockReasonDestroy"));
  GetCurrentInputMessageSource_ = reinterpret_cast<decltype(GetCurrentInputMessageSource_)>(GetProcAddress_(hModule,"GetCurrentInputMessageSource"));
  GetCIMSSM_ = reinterpret_cast<decltype(GetCIMSSM_)>(GetProcAddress_(hModule,"GetCIMSSM"));
  GetAutoRotationState_ = reinterpret_cast<decltype(GetAutoRotationState_)>(GetProcAddress_(hModule,"GetAutoRotationState"));
  GetDisplayAutoRotationPreferences_ = reinterpret_cast<decltype(GetDisplayAutoRotationPreferences_)>(GetProcAddress_(hModule,"GetDisplayAutoRotationPreferences"));
  GetDisplayAutoRotationPreferencesByProcessId_ = reinterpret_cast<decltype(GetDisplayAutoRotationPreferencesByProcessId_)>(GetProcAddress_(hModule,"GetDisplayAutoRotationPreferencesByProcessId"));
  SetDisplayAutoRotationPreferences_ = reinterpret_cast<decltype(SetDisplayAutoRotationPreferences_)>(GetProcAddress_(hModule,"SetDisplayAutoRotationPreferences"));
  IsImmersiveProcess_ = reinterpret_cast<decltype(IsImmersiveProcess_)>(GetProcAddress_(hModule,"IsImmersiveProcess"));
  SetProcessRestrictionExemption_ = reinterpret_cast<decltype(SetProcessRestrictionExemption_)>(GetProcAddress_(hModule,"SetProcessRestrictionExemption"));
  GetPointerInputTransform_ = reinterpret_cast<decltype(GetPointerInputTransform_)>(GetProcAddress_(hModule,"GetPointerInputTransform"));
  IsMousePointerEnabled_ = reinterpret_cast<decltype(IsMousePointerEnabled_)>(GetProcAddress_(hModule,"IsMousePointerEnabled"));

  SetSystemTimer_ = reinterpret_cast<decltype(SetSystemTimer_)>(GetProcAddress_(hModule,"SetSystemTimer"));
  CalcMenuBar_ = reinterpret_cast<decltype(CalcMenuBar_)>(GetProcAddress_(hModule,"CalcMenuBar"));
  WINNLSGetIMEHotkey_ = reinterpret_cast<decltype(WINNLSGetIMEHotkey_)>(GetProcAddress_(hModule,"WINNLSGetIMEHotkey"));
  GetTaskmanWindow_ = reinterpret_cast<decltype(GetTaskmanWindow_)>(GetProcAddress_(hModule,"GetTaskmanWindow"));
  DdeDisconnect_ = reinterpret_cast<decltype(DdeDisconnect_)>(GetProcAddress_(hModule,"DdeDisconnect"));
  DdeCreateStringHandleA_ = reinterpret_cast<decltype(DdeCreateStringHandleA_)>(GetProcAddress_(hModule,"DdeCreateStringHandleA"));
  SetProcessDpiAwarenessInternal_ = reinterpret_cast<decltype(SetProcessDpiAwarenessInternal_)>(GetProcAddress_(hModule,"SetProcessDpiAwarenessInternal"));
  SetDeskWallpaper_ = reinterpret_cast<decltype(SetDeskWallpaper_)>(GetProcAddress_(hModule,"SetDeskWallpaper"));
  User32ImmTranslateMessage_ = reinterpret_cast<decltype(User32ImmTranslateMessage_)>(GetProcAddress_(hModule,"User32ImmTranslateMessage"));
  DdeGetData_ = reinterpret_cast<decltype(DdeGetData_)>(GetProcAddress_(hModule,"DdeGetData"));
  SetSysColorsTemp_ = reinterpret_cast<decltype(SetSysColorsTemp_)>(GetProcAddress_(hModule,"SetSysColorsTemp"));
  StaticWndProcW_ = reinterpret_cast<decltype(StaticWndProcW_)>(GetProcAddress_(hModule,"StaticWndProcW"));
  DdeAccessData_ = reinterpret_cast<decltype(DdeAccessData_)>(GetProcAddress_(hModule,"DdeAccessData"));
  DdeUnaccessData_ = reinterpret_cast<decltype(DdeUnaccessData_)>(GetProcAddress_(hModule,"DdeUnaccessData"));
  DdeInitializeA_ = reinterpret_cast<decltype(DdeInitializeA_)>(GetProcAddress_(hModule,"DdeInitializeA"));
  DdeInitializeW_ = reinterpret_cast<decltype(DdeInitializeW_)>(GetProcAddress_(hModule,"DdeInitializeW"));
  DdeUninitialize_ = reinterpret_cast<decltype(DdeUninitialize_)>(GetProcAddress_(hModule,"DdeUninitialize"));
  LoadLocalFonts_ = reinterpret_cast<decltype(LoadLocalFonts_)>(GetProcAddress_(hModule,"LoadLocalFonts"));
  CharPrevExW_ = reinterpret_cast<decltype(CharPrevExW_)>(GetProcAddress_(hModule,"CharPrevExW"));
  GetProgmanWindow_ = reinterpret_cast<decltype(GetProgmanWindow_)>(GetProcAddress_(hModule,"GetProgmanWindow"));
  SetThreadDpiAwarenessContext_ = reinterpret_cast<decltype(SetThreadDpiAwarenessContext_)>(GetProcAddress_(hModule,"SetThreadDpiAwarenessContext"));
  PackDDElParam_ = reinterpret_cast<decltype(PackDDElParam_)>(GetProcAddress_(hModule,"PackDDElParam"));
  DdeFreeDataHandle_ = reinterpret_cast<decltype(DdeFreeDataHandle_)>(GetProcAddress_(hModule,"DdeFreeDataHandle"));
  AlignRects_ = reinterpret_cast<decltype(AlignRects_)>(GetProcAddress_(hModule,"AlignRects"));
  DdeQueryStringW_ = reinterpret_cast<decltype(DdeQueryStringW_)>(GetProcAddress_(hModule,"DdeQueryStringW"));
  SetLogonNotifyWindow_ = reinterpret_cast<decltype(SetLogonNotifyWindow_)>(GetProcAddress_(hModule,"SetLogonNotifyWindow"));
  GetCursorFrameInfo_ = reinterpret_cast<decltype(GetCursorFrameInfo_)>(GetProcAddress_(hModule,"GetCursorFrameInfo"));
  DdeQueryStringA_ = reinterpret_cast<decltype(DdeQueryStringA_)>(GetProcAddress_(hModule,"DdeQueryStringA"));
  DdeSetQualityOfService_ = reinterpret_cast<decltype(DdeSetQualityOfService_)>(GetProcAddress_(hModule,"DdeSetQualityOfService"));
  DdeGetLastError_ = reinterpret_cast<decltype(DdeGetLastError_)>(GetProcAddress_(hModule,"DdeGetLastError"));
  ComboWndProcA_ = reinterpret_cast<decltype(ComboWndProcA_)>(GetProcAddress_(hModule,"ComboWndProcA"));
  DdeDisconnectList_ = reinterpret_cast<decltype(DdeDisconnectList_)>(GetProcAddress_(hModule,"DdeDisconnectList"));
  SendIMEMessageExA_ = reinterpret_cast<decltype(SendIMEMessageExA_)>(GetProcAddress_(hModule,"SendIMEMessageExA"));
  DdeCmpStringHandles_ = reinterpret_cast<decltype(DdeCmpStringHandles_)>(GetProcAddress_(hModule,"DdeCmpStringHandles"));
  RegisterTasklist_ = reinterpret_cast<decltype(RegisterTasklist_)>(GetProcAddress_(hModule,"RegisterTasklist"));
  IconTitleWndProc_ = reinterpret_cast<decltype(IconTitleWndProc_)>(GetProcAddress_(hModule,"IconTitleWndProc"));
  SendIMEMessageExW_ = reinterpret_cast<decltype(SendIMEMessageExW_)>(GetProcAddress_(hModule,"SendIMEMessageExW"));
  ComboWndProcW_ = reinterpret_cast<decltype(ComboWndProcW_)>(GetProcAddress_(hModule,"ComboWndProcW"));
  DdeConnectList_ = reinterpret_cast<decltype(DdeConnectList_)>(GetProcAddress_(hModule,"DdeConnectList"));
  DdeQueryNextServer_ = reinterpret_cast<decltype(DdeQueryNextServer_)>(GetProcAddress_(hModule,"DdeQueryNextServer"));
  RegisterUserApiHook_ = reinterpret_cast<decltype(RegisterUserApiHook_)>(GetProcAddress_(hModule,"RegisterUserApiHook"));
  UnregisterUserApiHook_ = reinterpret_cast<decltype(UnregisterUserApiHook_)>(GetProcAddress_(hModule,"UnregisterUserApiHook"));
  StaticWndProcA_ = reinterpret_cast<decltype(StaticWndProcA_)>(GetProcAddress_(hModule,"StaticWndProcA"));
  MDIClientWndProcW_ = reinterpret_cast<decltype(MDIClientWndProcW_)>(GetProcAddress_(hModule,"MDIClientWndProcW"));
  DdeKeepStringHandle_ = reinterpret_cast<decltype(DdeKeepStringHandle_)>(GetProcAddress_(hModule,"DdeKeepStringHandle"));
  GetAppCompatFlags_ = reinterpret_cast<decltype(GetAppCompatFlags_)>(GetProcAddress_(hModule,"GetAppCompatFlags"));
  SetProgmanWindow_ = reinterpret_cast<decltype(SetProgmanWindow_)>(GetProcAddress_(hModule,"SetProgmanWindow"));
  DdeEnableCallback_ = reinterpret_cast<decltype(DdeEnableCallback_)>(GetProcAddress_(hModule,"DdeEnableCallback"));
  GetThreadDpiHostingBehavior_ = reinterpret_cast<decltype(GetThreadDpiHostingBehavior_)>(GetProcAddress_(hModule,"GetThreadDpiHostingBehavior"));
  MDIClientWndProcA_ = reinterpret_cast<decltype(MDIClientWndProcA_)>(GetProcAddress_(hModule,"MDIClientWndProcA"));
  EditWndProcW_ = reinterpret_cast<decltype(EditWndProcW_)>(GetProcAddress_(hModule,"EditWndProcW"));
  ButtonWndProcW_ = reinterpret_cast<decltype(ButtonWndProcW_)>(GetProcAddress_(hModule,"ButtonWndProcW"));
  SetTaskmanWindow_ = reinterpret_cast<decltype(SetTaskmanWindow_)>(GetProcAddress_(hModule,"SetTaskmanWindow"));
  DdeImpersonateClient_ = reinterpret_cast<decltype(DdeImpersonateClient_)>(GetProcAddress_(hModule,"DdeImpersonateClient"));
  DdeQueryConvInfo_ = reinterpret_cast<decltype(DdeQueryConvInfo_)>(GetProcAddress_(hModule,"DdeQueryConvInfo"));
  CalcChildScroll_ = reinterpret_cast<decltype(CalcChildScroll_)>(GetProcAddress_(hModule,"CalcChildScroll"));
  DdeConnect_ = reinterpret_cast<decltype(DdeConnect_)>(GetProcAddress_(hModule,"DdeConnect"));
  DdeReconnect_ = reinterpret_cast<decltype(DdeReconnect_)>(GetProcAddress_(hModule,"DdeReconnect"));
  CharNextExW_ = reinterpret_cast<decltype(CharNextExW_)>(GetProcAddress_(hModule,"CharNextExW"));
  EditWndProcA_ = reinterpret_cast<decltype(EditWndProcA_)>(GetProcAddress_(hModule,"EditWndProcA"));
  GetProcessDpiAwarenessInternal_ = reinterpret_cast<decltype(GetProcessDpiAwarenessInternal_)>(GetProcAddress_(hModule,"GetProcessDpiAwarenessInternal"));
  RegisterSystemThread_ = reinterpret_cast<decltype(RegisterSystemThread_)>(GetProcAddress_(hModule,"RegisterSystemThread"));
  SetWindowCompositionAttribute_ = reinterpret_cast<decltype(SetWindowCompositionAttribute_)>(GetProcAddress_(hModule,"SetWindowCompositionAttribute"));
  DdeClientTransaction_ = reinterpret_cast<decltype(DdeClientTransaction_)>(GetProcAddress_(hModule,"DdeClientTransaction"));
  DdeAbandonTransaction_ = reinterpret_cast<decltype(DdeAbandonTransaction_)>(GetProcAddress_(hModule,"DdeAbandonTransaction"));
  ScrollBarWndProcA_ = reinterpret_cast<decltype(ScrollBarWndProcA_)>(GetProcAddress_(hModule,"ScrollBarWndProcA"));
  LoadKeyboardLayoutEx_ = reinterpret_cast<decltype(LoadKeyboardLayoutEx_)>(GetProcAddress_(hModule,"LoadKeyboardLayoutEx"));
  RegisterServicesProcess_ = reinterpret_cast<decltype(RegisterServicesProcess_)>(GetProcAddress_(hModule,"RegisterServicesProcess"));
  DdeCreateDataHandle_ = reinterpret_cast<decltype(DdeCreateDataHandle_)>(GetProcAddress_(hModule,"DdeCreateDataHandle"));
  DdeAddData_ = reinterpret_cast<decltype(DdeAddData_)>(GetProcAddress_(hModule,"DdeAddData"));
  ScrollBarWndProcW_ = reinterpret_cast<decltype(ScrollBarWndProcW_)>(GetProcAddress_(hModule,"ScrollBarWndProcW"));
  DdeNameService_ = reinterpret_cast<decltype(DdeNameService_)>(GetProcAddress_(hModule,"DdeNameService"));
  ButtonWndProcA_ = reinterpret_cast<decltype(ButtonWndProcA_)>(GetProcAddress_(hModule,"ButtonWndProcA"));
  GetSystemMetricsForDpi_ = reinterpret_cast<decltype(GetSystemMetricsForDpi_)>(GetProcAddress_(hModule,"GetSystemMetricsForDpi"));
  GetWindowDpiHostingBehavior_ = reinterpret_cast<decltype(GetWindowDpiHostingBehavior_)>(GetProcAddress_(hModule,"GetWindowDpiHostingBehavior"));
  SetWindowStationUser_ = reinterpret_cast<decltype(SetWindowStationUser_)>(GetProcAddress_(hModule,"SetWindowStationUser"));
  SystemParametersInfoForDpi_ = reinterpret_cast<decltype(SystemParametersInfoForDpi_)>(GetProcAddress_(hModule,"SystemParametersInfoForDpi"));
  MessageWndProc_ = reinterpret_cast<decltype(MessageWndProc_)>(GetProcAddress_(hModule,"MessageWndProc"));
  IsWindowRedirectedForPrint_ = reinterpret_cast<decltype(IsWindowRedirectedForPrint_)>(GetProcAddress_(hModule,"IsWindowRedirectedForPrint"));
  WINNLSGetEnableStatus_ = reinterpret_cast<decltype(WINNLSGetEnableStatus_)>(GetProcAddress_(hModule,"WINNLSGetEnableStatus"));
  KillSystemTimer_ = reinterpret_cast<decltype(KillSystemTimer_)>(GetProcAddress_(hModule,"KillSystemTimer"));
  DdeCreateStringHandleW_ = reinterpret_cast<decltype(DdeCreateStringHandleW_)>(GetProcAddress_(hModule,"DdeCreateStringHandleW"));
  MDI_MoreWindowsDlgProc_ = reinterpret_cast<decltype(MDI_MoreWindowsDlgProc_)>(GetProcAddress_(hModule,"MDI_MoreWindowsDlgProc"));
  WINNLSEnableIME_ = reinterpret_cast<decltype(WINNLSEnableIME_)>(GetProcAddress_(hModule,"WINNLSEnableIME"));
  AdjustWindowRectExForDpi_ = reinterpret_cast<decltype(AdjustWindowRectExForDpi_)>(GetProcAddress_(hModule,"AdjustWindowRectExForDpi"));
  GetThreadDpiAwarenessContext_ = reinterpret_cast<decltype(GetThreadDpiAwarenessContext_)>(GetProcAddress_(hModule,"GetThreadDpiAwarenessContext"));
  DdeFreeStringHandle_ = reinterpret_cast<decltype(DdeFreeStringHandle_)>(GetProcAddress_(hModule,"DdeFreeStringHandle"));
  DrawCaptionTempA_ = reinterpret_cast<decltype(DrawCaptionTempA_)>(GetProcAddress_(hModule,"DrawCaptionTempA"));
  TileChildWindows_ = reinterpret_cast<decltype(TileChildWindows_)>(GetProcAddress_(hModule,"TileChildWindows"));
  ReuseDDElParam_ = reinterpret_cast<decltype(ReuseDDElParam_)>(GetProcAddress_(hModule,"ReuseDDElParam"));
  ImpersonateDdeClientWindow_ = reinterpret_cast<decltype(ImpersonateDdeClientWindow_)>(GetProcAddress_(hModule,"ImpersonateDdeClientWindow"));
  GetDpiForSystem_ = reinterpret_cast<decltype(GetDpiForSystem_)>(GetProcAddress_(hModule,"GetDpiForSystem"));
  User32InitializeImmEntryTable_ = reinterpret_cast<decltype(User32InitializeImmEntryTable_)>(GetProcAddress_(hModule,"User32InitializeImmEntryTable"));
  EnableNonClientDpiScaling_ = reinterpret_cast<decltype(EnableNonClientDpiScaling_)>(GetProcAddress_(hModule,"EnableNonClientDpiScaling"));
  ImmSetActiveContext_ = reinterpret_cast<decltype(ImmSetActiveContext_)>(GetProcAddress_(hModule,"ImmSetActiveContext"));
  IsValidDpiAwarenessContext_ = reinterpret_cast<decltype(IsValidDpiAwarenessContext_)>(GetProcAddress_(hModule,"IsValidDpiAwarenessContext"));
  ScrollChildren_ = reinterpret_cast<decltype(ScrollChildren_)>(GetProcAddress_(hModule,"ScrollChildren"));
  CascadeChildWindows_ = reinterpret_cast<decltype(CascadeChildWindows_)>(GetProcAddress_(hModule,"CascadeChildWindows"));
  GetWindowDpiAwarenessContext_ = reinterpret_cast<decltype(GetWindowDpiAwarenessContext_)>(GetProcAddress_(hModule,"GetWindowDpiAwarenessContext"));
  I_ScRegisterDeviceNotification_ = reinterpret_cast<decltype(I_ScRegisterDeviceNotification_)>(GetProcAddress_(hModule,"I_ScRegisterDeviceNotification"));
  I_ScUnregisterDeviceNotification_ = reinterpret_cast<decltype(I_ScUnregisterDeviceNotification_)>(GetProcAddress_(hModule,"I_ScUnregisterDeviceNotification"));
  DdeSetUserHandle_ = reinterpret_cast<decltype(DdeSetUserHandle_)>(GetProcAddress_(hModule,"DdeSetUserHandle"));
  DdePostAdvise_ = reinterpret_cast<decltype(DdePostAdvise_)>(GetProcAddress_(hModule,"DdePostAdvise"));
  GetAppCompatFlags2_ = reinterpret_cast<decltype(GetAppCompatFlags2_)>(GetProcAddress_(hModule,"GetAppCompatFlags2"));
  AreDpiAwarenessContextsEqual_ = reinterpret_cast<decltype(AreDpiAwarenessContextsEqual_)>(GetProcAddress_(hModule,"AreDpiAwarenessContextsEqual"));
  GetAwarenessFromDpiAwarenessContext_ = reinterpret_cast<decltype(GetAwarenessFromDpiAwarenessContext_)>(GetProcAddress_(hModule,"GetAwarenessFromDpiAwarenessContext"));
  SetShellWindow_ = reinterpret_cast<decltype(SetShellWindow_)>(GetProcAddress_(hModule,"SetShellWindow"));
  ImeWndProcW_ = reinterpret_cast<decltype(ImeWndProcW_)>(GetProcAddress_(hModule,"ImeWndProcW"));
  GetDpiForWindow_ = reinterpret_cast<decltype(GetDpiForWindow_)>(GetProcAddress_(hModule,"GetDpiForWindow"));
  UnpackDDElParam_ = reinterpret_cast<decltype(UnpackDDElParam_)>(GetProcAddress_(hModule,"UnpackDDElParam"));
  FreeDDElParam_ = reinterpret_cast<decltype(FreeDDElParam_)>(GetProcAddress_(hModule,"FreeDDElParam"));
  UserRegisterWowHandlers_ = reinterpret_cast<decltype(UserRegisterWowHandlers_)>(GetProcAddress_(hModule,"UserRegisterWowHandlers"));
  ImeWndProcA_ = reinterpret_cast<decltype(ImeWndProcA_)>(GetProcAddress_(hModule,"ImeWndProcA"));
  ListBoxWndProcW_ = reinterpret_cast<decltype(ListBoxWndProcW_)>(GetProcAddress_(hModule,"ListBoxWndProcW"));
  ListBoxWndProcA_ = reinterpret_cast<decltype(ListBoxWndProcA_)>(GetProcAddress_(hModule,"ListBoxWndProcA"));
  SetThreadDpiHostingBehavior_ = reinterpret_cast<decltype(SetThreadDpiHostingBehavior_)>(GetProcAddress_(hModule,"SetThreadDpiHostingBehavior"));
  RegisterLogonProcess_ = reinterpret_cast<decltype(RegisterLogonProcess_)>(GetProcAddress_(hModule,"RegisterLogonProcess"));

  logging::log("init", logging::LogLevel::debug, "APIUser32::APIUser32() exit");
} 

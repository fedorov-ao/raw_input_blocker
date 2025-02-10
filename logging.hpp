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

#ifndef LOGGING_HPP
#define LOGGING_HPP

#include "util.hpp"

#include <string>
#include <vector>
#include <functional>
#include <memory>
#include <ctime>

/* Logging */
namespace logging
{

enum class LogLevel : int { notset=0, trace=1, debug=2, info=3, error=4 };

char const * ll2n(LogLevel level);
LogLevel n2ll(char const * name);
LogLevel n2ll(std::string const & name);

inline std::ostream & operator<<(std::ostream & os, LogLevel logLevel)
{
  return os << ll2n(logLevel);
}

struct LogMessage
{
  std::string source;
  LogLevel level;
  std::time_t time;
  std::string msg;

  LogMessage(std::string const & source, LogLevel level, std::time_t const & time, std::string const & msg);
};

class LogPrinter
{
public:
  virtual void print(LogMessage const & lm) const =0;

  virtual ~LogPrinter() {}
};

class StreamLogPrinter : public LogPrinter
{
public:
  typedef std::function<std::string(LogMessage const &)> formatter_t;
  typedef std::function<std::ostream&()> stream_holder_t;

  virtual void print(LogMessage const & lm) const;

  StreamLogPrinter(formatter_t const & formatter, stream_holder_t const & streamHolder);

private:
  formatter_t formatter_;
  stream_holder_t streamHolder_;
};

class Logger
{
public:
  template <typename... T>
  void log(char const * source, LogLevel level, const T&... t)
  {
    if (static_cast<int>(level) < static_cast<int>(level_))
      return;
    auto const msg = stream_to_str(t...);
    auto const time = std::time(nullptr);
    LogMessage const lm (source, level, time, msg);
    log(lm);
  }

  void log(LogMessage const & lm);

  void set_level(LogLevel level);
  LogLevel get_level() const;

  void add_printer(std::shared_ptr<LogPrinter> const & spPrinter);

  Logger(LogLevel level=LogLevel::notset);

private:
  LogLevel level_;
  std::vector<std::shared_ptr<LogPrinter> > printers_;
};

Logger & root_logger();

template <typename... T>
void log(char const * source, LogLevel level, const T&... t)
{
  root_logger().log(source, level, t...);
}

} //logging

#endif 

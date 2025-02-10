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

#include "logging.hpp"
#include <cstdlib>
#include <cstring>

namespace logging
{

static struct { char const * name; LogLevel level; } g_logLevelNames[] = {
  { "NOTSET", LogLevel::notset },
  { "TRACE", LogLevel::trace },
  { "DEBUG", LogLevel::debug },
  { "INFO", LogLevel::info },
  { "ERROR", LogLevel::error }
};

char const * ll2n(LogLevel level)
{
  for (auto const & p : g_logLevelNames)
    if (p.level == level) 
      return p.name;
  return "";
}

LogLevel n2ll(char const * name)
{
  for (auto const & p : g_logLevelNames)
    if (std::strcmp(p.name, name) == 0) 
      return p.level;
  return LogLevel::notset;
}

LogLevel n2ll(std::string const & name)
{
  return n2ll(name.c_str());
}

LogMessage::LogMessage(std::string const & source, LogLevel level, std::time_t const & time, std::string const & msg)
  : source(source), level(level), time(time), msg(msg)
{}

void StreamLogPrinter::print(LogMessage const & lm) const
{
  auto const msg = formatter_(lm);
  streamHolder_() << msg << std::endl;
}

StreamLogPrinter::StreamLogPrinter(formatter_t const & formatter, stream_holder_t const & streamHolder)
  : formatter_(formatter), streamHolder_(streamHolder)
{}

void Logger::log(LogMessage const & lm)
{
  if (static_cast<int>(lm.level) < static_cast<int>(level_))
    return;
  for (auto const & sp : printers_)
    sp->print(lm);
}

void Logger::set_level(LogLevel level)
{
  level_ = level;
}

LogLevel Logger::get_level() const
{
  return level_;
}

void Logger::add_printer(std::shared_ptr<LogPrinter> const & spPrinter)
{
  if (spPrinter == nullptr)
    throw std::runtime_error("Log message printer ptr is NULL");
  printers_.push_back(spPrinter);
}

Logger::Logger(LogLevel level)
  : level_(level), printers_()
{}

Logger & root_logger()
{
  static Logger logger;
  return logger;
}

} //logging

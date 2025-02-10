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

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include "nlohmann/json.hpp"
#include <string>

namespace config
{

typedef nlohmann::json config_t;
typedef nlohmann::json::out_of_range out_of_range;


template <class R, class C, class K>
R get(C const & config, K&& key)
try {
  return config.at(key).template get<R>();
} catch (nlohmann::json::out_of_range const & e)
{
  logging::log("util", logging::LogLevel::error, e.what(), "; key: ", key, "; config: ", config);
  throw;
}


template <class C, class K>
C const & get(C const & config, K&& key)
try {
  return config.at(key);
} catch (nlohmann::json::out_of_range const & e)
{
  logging::log("util", logging::LogLevel::error, e.what(), "; key: ", key, "; config: ", config);
  throw;
}


template <class R, class C, class K>
R get_d(C const & config, K&& key, R&& dfault)
try {
  return config.at(key).template get<R>();
} catch (nlohmann::json::out_of_range const & e)
{
  return dfault;
}


/* json does not like single backslashes in strings, so can either use forward slashes or double backslashes. */
template <class C, class K>
std::string get_escaped_string(C const & config, K&& key)
{
  auto s = get<std::string>(config, key);
  std::replace(s.begin(), s.end(), '/', '\\');
  return s;
};


template <class C, class K, class D>
std::string get_escaped_string_d(C const & config, K&& key, D&& dfault)
{
  auto s = get_d<std::string>(config, key, dfault);
  std::replace(s.begin(), s.end(), '/', '\\');
  return s;
}

}//config

#endif

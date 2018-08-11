/* XMRig
 * Copyright 2014      imonero <https://github.com/global-blockchain>
 * Copyright 2016-2017 XMRig       <admin@imonero.org>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef WIN32
#   include <winsock2.h>
#   include <windows.h>
#endif


#include "common/log/BasicLog.h"
#include "common/log/Log.h"


BasicLog::BasicLog()
{
}


void BasicLog::message(Level level, const char* fmt, va_list args)
{
    time_t now = time(nullptr);
    tm stime;

#   ifdef _WIN32
    localtime_s(&stime, &now);
#   else
    localtime_r(&now, &stime);
#   endif

    snprintf(m_fmt, sizeof(m_fmt) - 1, "[%d-%02d-%02d %02d:%02d:%02d]%s %s%s",
             stime.tm_year + 1900,
             stime.tm_mon + 1,
             stime.tm_mday,
             stime.tm_hour,
             stime.tm_min,
             stime.tm_sec,
             Log::colorByLevel(level, false),
             fmt,
             Log::endl(false)
        );

    print(args);
}


void BasicLog::text(const char* fmt, va_list args)
{
    snprintf(m_fmt, sizeof(m_fmt) - 1, "%s%s", fmt, Log::endl(false));

    print(args);
}


void BasicLog::print(va_list args)
{
    if (vsnprintf(m_buf, sizeof(m_buf) - 1, m_fmt, args) <= 0) {
        return;
    }

    fputs(m_buf, stdout);
    fflush(stdout);
}

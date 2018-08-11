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

#ifndef __ILOGBACKEND_H__
#define __ILOGBACKEND_H__


#include <stdarg.h>
#include <stddef.h>


class ILogBackend
{
public:
    enum Level {
        ERR,
        WARNING,
        NOTICE,
        INFO,
        DEBUG
    };

#   ifdef APP_DEBUG
    constexpr static const size_t kBufferSize = 1024;
#   else
    constexpr static const size_t kBufferSize = 512;
#   endif

    virtual ~ILogBackend() {}

    virtual void message(Level level, const char* fmt, va_list args) = 0;
    virtual void text(const char* fmt, va_list args)                 = 0;
};


#endif // __ILOGBACKEND_H__

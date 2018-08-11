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

#ifndef __BASICLOG_H__
#define __BASICLOG_H__


#include <uv.h>


#include "common/interfaces/ILogBackend.h"


namespace xmrig {
    class Controller;
}


class BasicLog : public ILogBackend
{
public:
    BasicLog();

    void message(Level level, const char *fmt, va_list args) override;
    void text(const char *fmt, va_list args) override;

private:
    bool isWritable() const;
    void print(va_list args);

    char m_buf[kBufferSize];
    char m_fmt[256];
};

#endif /* __BASICLOG_H__ */

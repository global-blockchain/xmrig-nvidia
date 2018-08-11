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

#ifndef __SYSLOG_H__
#define __SYSLOG_H__


#include "common/interfaces/ILogBackend.h"


class SysLog : public ILogBackend
{
public:
    SysLog();

    void message(Level level, const char *fmt, va_list args) override;
    void text(const char *fmt, va_list args) override;
};

#endif /* __SYSLOG_BACKEND_H__ */

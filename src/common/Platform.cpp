/* XMRig
 * Copyright 2014      imonero <https://github.com/global-blockchain>
 * Copyright 2016-2017 XMRig       <admin@imonero.org>
 *
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


#include <string.h>
#include <uv.h>


#include "Platform.h"


char Platform::m_defaultConfigName[520] = { 0 };
xmrig::c_str Platform::m_userAgent;


const char *Platform::defaultConfigName()
{
    size_t size = 520;

    if (*m_defaultConfigName) {
        return m_defaultConfigName;
    }

    if (uv_exepath(m_defaultConfigName, &size) < 0) {
        return nullptr;
    }

    if (size < 500) {
#       ifdef WIN32
        char *p = strrchr(m_defaultConfigName, '\\');
#       else
        char *p = strrchr(m_defaultConfigName, '/');
#       endif

        if (p) {
            strcpy(p + 1, "config.json");
            return m_defaultConfigName;
        }
    }

    *m_defaultConfigName = '\0';
    return nullptr;
}

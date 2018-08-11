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

#ifndef __HTTPBODY_H__
#define __HTTPBODY_H__


#include <string.h>


namespace xmrig {


class HttpBody
{
public:
    inline HttpBody() :
        m_pos(0)
    {}


    inline bool write(const char *data, size_t size)
    {
        if (size > (sizeof(m_data) - m_pos - 1)) {
            return false;
        }

        memcpy(m_data + m_pos, data, size);

        m_pos += size;
        m_data[m_pos] = '\0';

        return true;
    }


    inline const char *data() const { return m_data; }

private:
    char m_data[32768];
    size_t m_pos;
};


} /* namespace xmrig */


#endif /* __HTTPBODY_H__ */

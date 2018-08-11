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

#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__


#include <chrono>


namespace xmrig {


int64_t currentMSecsSinceEpoch()
{
    using namespace std::chrono;
    if (high_resolution_clock::is_steady) {
        return time_point_cast<milliseconds>(high_resolution_clock::now()).time_since_epoch().count();
    }

    return time_point_cast<milliseconds>(steady_clock::now()).time_since_epoch().count();
}


} /* namespace xmrig */

#endif /* __TIMESTAMP_H__ */

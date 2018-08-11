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

#ifndef __ITHREAD_H__
#define __ITHREAD_H__


#include <stdint.h>


#include "common/xmrig.h"
#include "rapidjson/fwd.h"


namespace xmrig {


class IThread
{
public:
    enum Type {
        CPU,
        OpenCL,
        CUDA
    };

    enum Multiway {
        SingleWay = 1,
        DoubleWay,
        TripleWay,
        QuadWay,
        PentaWay
    };

    virtual ~IThread() {}

    virtual Algo algorithm() const                                    = 0;
    virtual int priority() const                                      = 0;
    virtual int64_t affinity() const                                  = 0;
    virtual Multiway multiway() const                                 = 0;
    virtual rapidjson::Value toConfig(rapidjson::Document &doc) const = 0;
    virtual size_t index() const                                      = 0;
    virtual Type type() const                                         = 0;

#   ifndef XMRIG_NO_API
    virtual rapidjson::Value toAPI(rapidjson::Document &doc) const = 0;
#   endif
};


} /* namespace xmrig */


#endif // __ITHREAD_H__

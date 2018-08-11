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

#ifndef __CONFIGCREATOR_H__
#define __CONFIGCREATOR_H__


#include "common/interfaces/IConfigCreator.h"
#include "core/Config.h"


namespace xmrig {


class IConfig;


class ConfigCreator : public IConfigCreator
{
public:
    inline IConfig *create() const override
    {
        return new Config();
    }
};


} /* namespace xmrig */


#endif // __CONFIGCREATOR_H__

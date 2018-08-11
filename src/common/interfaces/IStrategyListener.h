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

#ifndef __ISTRATEGYLISTENER_H__
#define __ISTRATEGYLISTENER_H__


#include <stdint.h>


class Client;
class IStrategy;
class Job;
class SubmitResult;


class IStrategyListener
{
public:
    virtual ~IStrategyListener() {}

    virtual void onActive(IStrategy *strategy, Client *client)                                                        = 0;
    virtual void onJob(IStrategy *strategy, Client *client, const Job &job)                                           = 0;
    virtual void onPause(IStrategy *strategy)                                                                         = 0;
    virtual void onResultAccepted(IStrategy *strategy, Client *client, const SubmitResult &result, const char *error) = 0;
};


#endif // __ISTRATEGYLISTENER_H__

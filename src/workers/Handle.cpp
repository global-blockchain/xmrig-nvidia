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


#include "workers/Handle.h"


Handle::Handle(size_t threadId, xmrig::IThread *config, uint32_t offset, size_t totalWays) :
    m_worker(nullptr),
    m_threadId(threadId),
    m_totalWays(totalWays),
    m_offset(offset),
    m_config(config)
{
}


void Handle::join()
{
    uv_thread_join(&m_thread);
}


void Handle::start(void (*callback) (void *))
{
    uv_thread_create(&m_thread, callback, this);
}

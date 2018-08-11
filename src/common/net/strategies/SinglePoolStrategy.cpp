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


#include "common/interfaces/IStrategyListener.h"
#include "common/net/Client.h"
#include "common/net/strategies/SinglePoolStrategy.h"
#include "common/Platform.h"


SinglePoolStrategy::SinglePoolStrategy(const Pool &pool, int retryPause, int retries, IStrategyListener *listener, bool quiet) :
    m_active(false),
    m_listener(listener)
{
    m_client = new Client(0, Platform::userAgent(), this);
    m_client->setPool(pool);
    m_client->setRetries(retries);
    m_client->setRetryPause(retryPause * 1000);
    m_client->setQuiet(quiet);
}


SinglePoolStrategy::~SinglePoolStrategy()
{
    m_client->deleteLater();
}


int64_t SinglePoolStrategy::submit(const JobResult &result)
{
    return m_client->submit(result);
}


void SinglePoolStrategy::connect()
{
    m_client->connect();
}


void SinglePoolStrategy::resume()
{
    if (!isActive()) {
        return;
    }

    m_listener->onJob(this, m_client, m_client->job());
}


void SinglePoolStrategy::stop()
{
    m_client->disconnect();
}


void SinglePoolStrategy::tick(uint64_t now)
{
    m_client->tick(now);
}


void SinglePoolStrategy::onClose(Client *client, int failures)
{
    if (!isActive()) {
        return;
    }

    m_active = false;
    m_listener->onPause(this);
}


void SinglePoolStrategy::onJobReceived(Client *client, const Job &job)
{
    m_listener->onJob(this, client, job);
}


void SinglePoolStrategy::onLoginSuccess(Client *client)
{
    m_active = true;
    m_listener->onActive(this, client);
}


void SinglePoolStrategy::onResultAccepted(Client *client, const SubmitResult &result, const char *error)
{
    m_listener->onResultAccepted(this, client, result, error);
}

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


#include <microhttpd.h>
#include <string.h>


#include "api/Api.h"
#include "common/api/Httpd.h"
#include "common/api/HttpReply.h"
#include "common/api/HttpRequest.h"
#include "common/log/Log.h"


Httpd::Httpd(int port, const char *accessToken, bool IPv6, bool restricted) :
    m_idle(true),
    m_IPv6(IPv6),
    m_restricted(restricted),
    m_accessToken(accessToken ? strdup(accessToken) : nullptr),
    m_port(port),
    m_daemon(nullptr)
{
    uv_timer_init(uv_default_loop(), &m_timer);
    m_timer.data = this;
}


Httpd::~Httpd()
{
    uv_timer_stop(&m_timer);

    if (m_daemon) {
        MHD_stop_daemon(m_daemon);
    }

    delete m_accessToken;
}


bool Httpd::start()
{
    if (!m_port) {
        return false;
    }

    unsigned int flags = 0;
#   if MHD_VERSION >= 0x00093500
    if (m_IPv6 && MHD_is_feature_supported(MHD_FEATURE_IPv6)) {
        flags |= MHD_USE_DUAL_STACK;
    }

    if (MHD_is_feature_supported(MHD_FEATURE_EPOLL)) {
        flags |= MHD_USE_EPOLL_LINUX_ONLY;
    }
#   endif

    m_daemon = MHD_start_daemon(flags, m_port, nullptr, nullptr, &Httpd::handler, this, MHD_OPTION_END);
    if (!m_daemon) {
        LOG_ERR("HTTP Daemon failed to start.");
        return false;
    }

#   if MHD_VERSION >= 0x00093900
    uv_timer_start(&m_timer, Httpd::onTimer, kIdleInterval, kIdleInterval);
#   else
    uv_timer_start(&m_timer, Httpd::onTimer, kActiveInterval, kActiveInterval);
#   endif

    return true;
}


int Httpd::process(xmrig::HttpRequest &req)
{
    xmrig::HttpReply reply;
    if (!req.process(m_accessToken, m_restricted, reply)) {
        return req.end(reply);
    }

    if (!req.isFulfilled()) {
        return MHD_YES;
    }

    Api::exec(req, reply);

    return req.end(reply);
}


void Httpd::run()
{
    MHD_run(m_daemon);

#   if MHD_VERSION >= 0x00093900
    const MHD_DaemonInfo *info = MHD_get_daemon_info(m_daemon, MHD_DAEMON_INFO_CURRENT_CONNECTIONS);
    if (m_idle && info->num_connections) {
        uv_timer_set_repeat(&m_timer, kActiveInterval);
        m_idle = false;
    }
    else if (!m_idle && !info->num_connections) {
        uv_timer_set_repeat(&m_timer, kIdleInterval);
        m_idle = true;
    }
#   endif
}


int Httpd::handler(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *uploadData, size_t *uploadSize, void **con_cls)
{
    xmrig::HttpRequest req(connection, url, method, uploadData, uploadSize, con_cls);

    if (req.method() == xmrig::HttpRequest::Options) {
        return req.end(MHD_HTTP_OK, nullptr);
    }

    if (req.method() == xmrig::HttpRequest::Unsupported) {
        return req.end(MHD_HTTP_METHOD_NOT_ALLOWED, nullptr);
    }

    return static_cast<Httpd*>(cls)->process(req);
}


void Httpd::onTimer(uv_timer_t *handle)
{
    static_cast<Httpd*>(handle->data)->run();
}

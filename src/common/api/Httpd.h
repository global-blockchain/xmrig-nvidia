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

#ifndef __HTTPD_H__
#define __HTTPD_H__


#include <uv.h>


struct MHD_Connection;
struct MHD_Daemon;
struct MHD_Response;


class UploadCtx;


namespace xmrig {
    class HttpRequest;
}


class Httpd
{
public:
    Httpd(int port, const char *accessToken, bool IPv6, bool restricted);
    ~Httpd();
    bool start();

private:
    constexpr static const int kIdleInterval   = 200;
    constexpr static const int kActiveInterval = 25;

    int process(xmrig::HttpRequest &req);
    void run();

    static int handler(void *cls, MHD_Connection *connection, const char *url, const char *method, const char *version, const char *uploadData, size_t *uploadSize, void **con_cls);
    static void onTimer(uv_timer_t *handle);

    bool m_idle;
    bool m_IPv6;
    bool m_restricted;
    const char *m_accessToken;
    const int m_port;
    MHD_Daemon *m_daemon;
    uv_timer_t m_timer;
};

#endif /* __HTTPD_H__ */

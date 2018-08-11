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


#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "common/log/FileLog.h"
#include "common/log/Log.h"
#include "core/Config.h"
#include "core/Controller.h"


FileLog::FileLog(xmrig::Controller *controller, const char *fileName) :
    m_controller(controller)
{
    uv_fs_t req;
    m_file = uv_fs_open(uv_default_loop(), &req, fileName, O_CREAT | O_APPEND | O_WRONLY, 0644, nullptr);
    uv_fs_req_cleanup(&req);
}


void FileLog::message(Level level, const char* fmt, va_list args)
{
    if (m_file < 0) {
        return;
    }

    time_t now = time(nullptr);
    tm stime;

#   ifdef _WIN32
    localtime_s(&stime, &now);
#   else
    localtime_r(&now, &stime);
#   endif

    const bool isColors = m_controller->config()->isColors();

    snprintf(m_fmt, sizeof(m_fmt) - 1, "[%d-%02d-%02d %02d:%02d:%02d]%s %s%s",
             stime.tm_year + 1900,
             stime.tm_mon + 1,
             stime.tm_mday,
             stime.tm_hour,
             stime.tm_min,
             stime.tm_sec,
             Log::colorByLevel(level, isColors),
             fmt,
             Log::endl(isColors)
        );

    char *buf = new char[kBufferSize];
    const int size = vsnprintf(buf, kBufferSize - 1, m_fmt, args);

    write(buf, size);
}


void FileLog::text(const char* fmt, va_list args)
{
    message(INFO, fmt, args);
}


void FileLog::onWrite(uv_fs_t *req)
{
    delete [] static_cast<char *>(req->data);

    uv_fs_req_cleanup(req);
    delete req;
}


void FileLog::write(char *data, size_t size)
{
    uv_buf_t buf = uv_buf_init(data, (unsigned int) size);
    uv_fs_t *req = new uv_fs_t;
    req->data = buf.base;

    uv_fs_write(uv_default_loop(), req, m_file, &buf, 1, -1, FileLog::onWrite);
}

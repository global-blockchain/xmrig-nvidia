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


#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>


#include "App.h"
#include "common/log/Log.h"
#include "core/Config.h"
#include "core/Controller.h"


void App::background()
{
    signal(SIGPIPE, SIG_IGN);

    if (!m_controller->config()->isBackground()) {
        return;
    }

    int i = fork();
    if (i < 0) {
        exit(1);
    }

    if (i > 0) {
        exit(0);
    }

    i = setsid();

    if (i < 0) {
        LOG_ERR("setsid() failed (errno = %d)", errno);
    }

    i = chdir("/");
    if (i < 0) {
        LOG_ERR("chdir() failed (errno = %d)", errno);
    }
}

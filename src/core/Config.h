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

#ifndef XMRIG_CONFIG_H
#define XMRIG_CONFIG_H


#include <stdint.h>
#include <vector>


#include "common/config/CommonConfig.h"
#include "common/xmrig.h"
#include "nvidia/CudaCLI.h"
#include "rapidjson/fwd.h"


namespace xmrig {


class ConfigLoader;
class IThread;
class IWatcherListener;


class Config : public CommonConfig
{
public:
    Config();

    bool reload(const char *json);

    void getJSON(rapidjson::Document &doc) const override;

    inline bool isShouldSave() const                     { return m_shouldSave; }
    inline const std::vector<IThread *> &threads() const { return m_threads; }
    inline int maxGpuThreads() const                     { return m_maxGpuThreads; }

    static Config *load(int argc, char **argv, IWatcherListener *listener);

protected:
    bool finalize() override;
    bool parseString(int key, const char *arg) override;
    bool parseUint64(int key, uint64_t arg) override;
    void parseJSON(const rapidjson::Document &doc) override;

private:
    void parseThread(const rapidjson::Value &object);

    bool m_autoConf;
    bool m_shouldSave;
    CudaCLI m_cudaCLI;
    int m_maxGpuThreads;
    int m_maxGpuUsage;
    std::vector<IThread *> m_threads;
};


} /* namespace xmrig */

#endif /* XMRIG_CONFIG_H */

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

#ifndef __HASHRATE_H__
#define __HASHRATE_H__


#include <stdint.h>
#include <uv.h>


namespace xmrig {
    class Controller;
}


class Hashrate
{
public:
    enum Intervals {
        ShortInterval  = 10000,
        MediumInterval = 60000,
        LargeInterval  = 900000
    };

    Hashrate(size_t threads, xmrig::Controller *controller);
    double calc(size_t ms) const;
    double calc(size_t threadId, size_t ms) const;
    void add(size_t threadId, uint64_t count, uint64_t timestamp);
    void print() const;
    void stop();
    void updateHighest();

    inline double highest() const { return m_highest; }
    inline size_t threads() const { return m_threads; }

    static const char *format(double h, char *buf, size_t size);

private:
    static void onReport(uv_timer_t *handle);

    constexpr static size_t kBucketSize = 2 << 11;
    constexpr static size_t kBucketMask = kBucketSize - 1;

    double m_highest;
    size_t m_threads;
    uint32_t* m_top;
    uint64_t** m_counts;
    uint64_t** m_timestamps;
    uv_timer_t m_timer;
    xmrig::Controller *m_controller;
};


#endif /* __HASHRATE_H__ */

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

#ifndef XMRIG_CPU_H
#define XMRIG_CPU_H


#include <stdint.h>


class Cpu
{
public:
    enum Flags {
        X86_64 = 1,
        AES    = 2,
        BMI2   = 4
    };

    static size_t optimalThreadsCount(size_t size, int maxCpuUsage);
    static void init();

    static inline bool hasAES()       { return (m_flags & AES) != 0; }
    static inline bool isX64()        { return (m_flags & X86_64) != 0; }
    static inline const char *brand() { return m_brand; }
    static inline int cores()         { return m_totalCores; }
    static inline int l2()            { return m_l2_cache; }
    static inline int l3()            { return m_l3_cache; }
    static inline int sockets()       { return m_sockets; }
    static inline size_t threads()    { return m_totalThreads; }

private:
    static void initCommon();

    static bool m_l2_exclusive;
    static char m_brand[64];
    static int m_flags;
    static int m_l2_cache;
    static int m_l3_cache;
    static int m_sockets;
    static int m_totalCores;
    static size_t m_totalThreads;
};


#endif /* XMRIG_CPU_H */

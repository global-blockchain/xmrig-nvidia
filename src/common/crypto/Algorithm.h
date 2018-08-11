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

#ifndef __ALGORITHM_H__
#define __ALGORITHM_H__


#include <vector>


#include "common/xmrig.h"


namespace xmrig {


class Algorithm
{
public:
    inline Algorithm() :
        m_algo(INVALID_ALGO),
        m_variant(VARIANT_AUTO)
    {}

    inline Algorithm(Algo algo, Variant variant) :
        m_variant(variant)
    {
        setAlgo(algo);
    }

    inline Algorithm(const char *algo)
    {
        parseAlgorithm(algo);
    }

    bool isEqual(const Algorithm &other) const { return m_algo == other.m_algo && m_variant == other.m_variant; }
    inline Algo algo() const                   { return m_algo; }
    inline const char *name() const            { return name(false); }
    inline const char *shortName() const       { return name(true); }
    inline Variant variant() const             { return m_variant; }
    inline void setVariant(Variant variant)    { m_variant = variant; }

    inline bool operator!=(const Algorithm &other) const  { return !isEqual(other); }
    inline bool operator==(const Algorithm &other) const  { return isEqual(other); }

    bool isValid() const;
    const char *variantName() const;
    void parseAlgorithm(const char *algo);
    void parseVariant(const char *variant);
    void parseVariant(int variant);
    void setAlgo(Algo algo);

#   ifdef XMRIG_PROXY_PROJECT
    void parseXmrStakAlgorithm(const char *algo);
#   endif

private:
    const char *name(bool shortName) const;

    Algo m_algo;
    Variant m_variant;
};


typedef std::vector<xmrig::Algorithm> Algorithms;


} /* namespace xmrig */

#endif /* __ALGORITHM_H__ */

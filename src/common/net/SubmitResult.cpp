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


#include <uv.h>


#include "common/net/SubmitResult.h"


SubmitResult::SubmitResult(int64_t seq, uint32_t diff, uint64_t actualDiff, int64_t reqId) :
    reqId(reqId),
    seq(seq),
    diff(diff),
    actualDiff(actualDiff),
    elapsed(0)
{
    start = uv_hrtime();
}


void SubmitResult::done()
{
    elapsed = (uv_hrtime() - start) / 1000000;
}

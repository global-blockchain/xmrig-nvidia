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


#pragma once

#include <stdint.h>


#include "../common/xmrig.h"


typedef struct {
    int device_id;
    const char *device_name;
    int device_arch[2];
    int device_mpcount;
    int device_blocks;
    int device_threads;
    int device_bfactor;
    int device_bsleep;
    int device_clockRate;
    int device_memoryClockRate;
    uint32_t device_pciBusID;
    uint32_t device_pciDeviceID;
    uint32_t device_pciDomainID;
    uint32_t syncMode;

    uint32_t *d_input;
    uint32_t inputlen;
    uint32_t *d_result_count;
    uint32_t *d_result_nonce;
    uint32_t *d_long_state;
    uint32_t *d_ctx_state;
    uint32_t *d_ctx_state2;
    uint32_t *d_ctx_a;
    uint32_t *d_ctx_b;
    uint32_t *d_ctx_key1;
    uint32_t *d_ctx_key2;
    uint32_t *d_ctx_text;
    uint32_t *d_tweak1_2;
} nvid_ctx;


int cuda_get_devicecount();
int cuda_get_runtime_version();
int cuda_get_deviceinfo(nvid_ctx *ctx, xmrig::Algo algo);
int cryptonight_gpu_init(nvid_ctx *ctx, xmrig::Algo algo);
void cryptonight_extra_cpu_set_data(nvid_ctx *ctx, const void *data, size_t len);
void cryptonight_extra_cpu_prepare(nvid_ctx* ctx, uint32_t startNonce, xmrig::Algo algo);
void cryptonight_gpu_hash(nvid_ctx *ctx, xmrig::Algo algo, xmrig::Variant variant, uint32_t startNonce);
void cryptonight_extra_cpu_final(nvid_ctx* ctx, uint32_t startNonce, uint64_t target, uint32_t* rescount, uint32_t *resnonce, xmrig::Algo algo);

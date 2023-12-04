// Copyright 2019 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef SRC_C_UTIL_TIME_H_
#define SRC_C_UTIL_TIME_H_

#ifdef __cplusplus
extern "C"
{
#endif // ifdef __cplusplus

#include <uxr/client/visibility.h>
#include <stdint.h>

#ifdef UCLIENT_PLATFORM_RTTHREAD
#include <time.h>
#include <stdio.h>
#include <rtthread.h>
#endif

static inline int64_t uxr_convert_to_nanos(
        int32_t sec,
        uint32_t nsec)
{
#ifdef UCLIENT_PLATFORM_RTTHREAD
    uint64_t now_ms = (uint64_t)rt_tick_get_millisecond();
    return now_ms * 1000000;
#else
    return ((int64_t)sec * 1000000000) + nsec;
#endif
}

#ifdef __cplusplus
}
#endif // ifdef __cplusplus

#endif // SRC_C_UTIL_TIME_H_

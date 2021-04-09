/*
 * @file PlatformInfo.cpp
 * @brief PlatformInfo class is a wrapper for hs_platform_info_t.
 * @author Ludvik Jerabek
 * @version 1.0 04/08/2021
 *
 * MIT License
 *
 * Copyright (c) 2021 Ludvik Jerabek
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "Exceptions.h"
#include "PlatformInfo.h"

namespace HyperScan {
    PlatformInfo::PlatformInfo() : _info({0}) {
        hs_error_t err = hs_populate_platform(&_info);
        if (err != HS_SUCCESS)
            throw PlatformInfoException("Failed to populate platform", err);
    }

    PlatformInfo::PlatformInfo(unsigned long long int features, unsigned long long int reserved1,
                               unsigned long long int reserved2, unsigned int tune) : _info({0}) {
        _info.cpu_features = features;
        _info.reserved1 = reserved1;
        _info.reserved2 = reserved2;
        _info.tune = tune;
    }

    void PlatformInfo::Reset() {
        hs_error_t err = hs_populate_platform(&_info);
        if (err != HS_SUCCESS)
            throw PlatformInfoException("Failed to populate platform", err);
    }

    unsigned long long int PlatformInfo::GetCpuFeatures() const { return _info.cpu_features; }

    unsigned long long int PlatformInfo::GetReserved1() const { return _info.reserved1; }

    unsigned long long int PlatformInfo::GetReserved2() const { return _info.reserved2; }

    unsigned int PlatformInfo::GetTune() const { return _info.tune; }

    void PlatformInfo::SetCpuFeatures(unsigned long long int features) { _info.cpu_features = features; }

    void PlatformInfo::SetReserved1(unsigned long long int reserved) { _info.reserved1 = reserved; }

    void PlatformInfo::SetReserved2(unsigned long long int reserved) { _info.reserved2 = reserved; }

    void PlatformInfo::SetTune(unsigned int tune) { _info.tune = tune; }
}
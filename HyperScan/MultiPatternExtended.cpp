/*
 * @file MultiPatternExtended.cpp
 * @brief MultiPatternExtended class is used to define sets of regex patterns and to crate the associated database for scanning.
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

#include "MultiPatternExtended.h"
#include "BlockDatabase.h"
#include "VectorDatabase.h"
#include "StreamDatabase.h"
#include "ExtendedExpressionContext.h"
#include "PlatformInfo.h"

namespace HyperScan {
    void MultiPatternExtended::AddPattern(const std::string &pattern, unsigned int flags, unsigned int identifier) {
        _patterns.push_back(pattern);
        _flags.push_back(flags);
        _ids.push_back(identifier);
        _exts.push_back(nullptr);
    }
    void MultiPatternExtended::AddPattern(const std::string &pattern, unsigned int flags, unsigned int identifier, const ExtendedExpressionContext &ext) {
        _patterns.push_back(pattern);
        _flags.push_back(flags);
        _ids.push_back(identifier);
        _exts.push_back(std::make_unique<hs_expr_ext_t>(ext._ext));
    }
    void MultiPatternExtended::Clear() {
        _flags.clear();
        _ids.clear();
        _patterns.clear();
        _exts.clear();
    }
    BlockDatabase MultiPatternExtended::GetBlockDatabase() {
        return BlockDatabase(*this);
    }
    VectorDatabase MultiPatternExtended::GetVectorDatabase() {
        return VectorDatabase(*this);
    }
    StreamDatabase MultiPatternExtended::GetStreamDatabase(StreamDatabase::Horizon horizon) {
        return StreamDatabase(*this, horizon);
    }
    BlockDatabase MultiPatternExtended::GetBlockDatabase(const PlatformInfo &pi) {
        return BlockDatabase(*this, pi);
    }
    VectorDatabase MultiPatternExtended::GetVectorDatabase(const PlatformInfo &pi) {
        return VectorDatabase(*this, pi);
    }
    StreamDatabase MultiPatternExtended::GetStreamDatabase(const PlatformInfo &pi, StreamDatabase::Horizon horizon) {
        return StreamDatabase(*this, pi, horizon);
    }
}
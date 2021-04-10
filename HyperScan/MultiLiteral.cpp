/*
 * @file MultiLiteral.cpp
 * @brief MultiLiteral class is used to define sets of literals and to crate the associated database for scanning.
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

#include "MultiLiteral.h"
#include "BlockDatabase.h"
#include "VectorDatabase.h"
#include "StreamDatabase.h"
#include "PlatformInfo.h"

namespace HyperScan {
    void MultiLiteral::AddLiteral(const std::vector<char> &literal, unsigned int flags, unsigned int identifier) {
        _literals.push_back(literal);
        _flags.push_back(flags);
        _ids.push_back(identifier);
    }
    void MultiLiteral::Clear() {
        _flags.clear();
        _ids.clear();
        _literals.clear();
    }
    BlockDatabase MultiLiteral::GetBlockDatabase(Database::Horizon horizon) { return BlockDatabase(*this, horizon); }
    VectorDatabase MultiLiteral::GetVectorDatabase(Database::Horizon horizon) { return VectorDatabase(*this, horizon); }
    StreamDatabase MultiLiteral::GetStreamDatabase(Database::Horizon horizon) { return StreamDatabase(*this, horizon); }
    BlockDatabase MultiLiteral::GetBlockDatabase(const PlatformInfo &pi, Database::Horizon horizon) {
        return BlockDatabase(*this, pi, horizon);
    }
    VectorDatabase MultiLiteral::GetVectorDatabase(const PlatformInfo &pi, Database::Horizon horizon) {
        return VectorDatabase(*this, pi, horizon);
    }
    StreamDatabase MultiLiteral::GetStreamDatabase(const PlatformInfo &pi, Database::Horizon horizon) {
        return StreamDatabase(*this, pi, horizon);
    }
}
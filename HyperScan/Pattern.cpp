/*
 * @file Pattern.cpp
 * @brief Pattern class is used to define a single regex pattern and to crate the associated database for scanning.
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


#include "Pattern.h"
#include <utility>
#include "BlockDatabase.h"
#include "VectorDatabase.h"
#include "StreamDatabase.h"
#include "ExpressionInfo.h"
#include "PlatformInfo.h"

 namespace HyperScan {
    Pattern::Pattern() : _flags(0) , _id(0) {}
    Pattern::Pattern(std::string  pattern, unsigned int flags , unsigned int id) : _pattern(std::move(pattern)), _flags(flags) , _id(id) {}
    Pattern::Pattern(std::string  pattern, unsigned int flags) : _pattern(std::move(pattern)), _flags(flags) , _id(0) {}
    std::string Pattern::GetPattern() const { return _pattern; }
    void Pattern::SetPattern(const std::string& pattern) { _pattern = pattern; }
    unsigned int Pattern::GetFlags() const { return _flags; }
    void Pattern::SetFlags(unsigned int flags) { _flags = flags; }
    unsigned int Pattern::GetId() const { return _id; }
    void Pattern::SetId(unsigned int id) { _id = id; }
    ExpressionInfo Pattern::GetExpressionInfo(){ return ExpressionInfo(*this); }
    ExpressionInfo Pattern::GetExpressionInfo(const ExtendedExpressionContext& ext){ return ExpressionInfo(*this , ext); }
    BlockDatabase Pattern::GetBlockDatabase( Database::Horizon horizon ){ return BlockDatabase(*this, horizon ); }
    VectorDatabase Pattern::GetVectorDatabase( Database::Horizon horizon ){ return VectorDatabase(*this, horizon ); }
    StreamDatabase Pattern::GetStreamDatabase( Database::Horizon horizon ){ return StreamDatabase(*this, horizon );}
    BlockDatabase Pattern::GetBlockDatabase(const PlatformInfo& pi, Database::Horizon horizon){ return BlockDatabase(*this , pi, horizon ); }
    VectorDatabase Pattern::GetVectorDatabase(const PlatformInfo& pi, Database::Horizon horizon){ return VectorDatabase(*this , pi, horizon ); }
    StreamDatabase Pattern::GetStreamDatabase(const PlatformInfo& pi, Database::Horizon horizon){ return StreamDatabase(*this, pi, horizon );}
}
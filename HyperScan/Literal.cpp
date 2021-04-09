/*
 * @file Literal.cpp
 * @brief Literal class is used to define literals and to crate the associated database for scanning.
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

#include "Literal.h"

#include <utility>
#include "BlockDatabase.h"
#include "VectoredDatabase.h"
#include "StreamDatabase.h"
#include "PlatformInfo.h"

namespace HyperScan {
    Literal::Literal() : _flags(0) , _id(0) {}
    Literal::Literal(std::vector<char> literal, unsigned int flags) : _literal(std::move(literal)), _flags(flags) , _id(0) {}
    Literal::Literal(std::vector<char> literal, unsigned int flags, unsigned int id) : _literal(std::move(literal)), _flags(flags) , _id(id) {}
    std::vector<char> Literal::GetLiteral() const { return _literal; }
    void Literal::SetLiteral(const std::vector<char>& literal) { _literal = literal; }
    unsigned int Literal::GetFlags() const { return _flags; }
    void Literal::SetFlags(unsigned int flags) { _flags = flags; }
    unsigned int Literal::GetId() const { return _id; }
    void Literal::SetId(unsigned int id) { _id = id; }
    BlockDatabase Literal::GetBlockDatabase(){ return BlockDatabase(*this); }
    VectoredDatabase Literal::GetVectoredDatabase(){ return VectoredDatabase(*this); }
    StreamDatabase Literal::GetStreamDatabase(){ return StreamDatabase(*this);}
    BlockDatabase Literal::GetBlockDatabase(const PlatformInfo& pi){ return BlockDatabase(*this , pi); }
    VectoredDatabase Literal::GetVectoredDatabase(const PlatformInfo& pi){ return VectoredDatabase(*this , pi); }
    StreamDatabase Literal::GetStreamDatabase(const PlatformInfo& pi){ return StreamDatabase(*this, pi);}
}
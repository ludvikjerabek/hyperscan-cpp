/*
 * @file VectoredDatabase.h
 * @brief Derived from Database class provides VectoredDatabase functions for HyperScan
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


#ifndef _HYPERSCAN_VECTOREDDATABASE_H
#define _HYPERSCAN_VECTOREDDATABASE_H

#include "Database.h"
#include <memory>

namespace HyperScan {
    class VectoredDatabase final : public Database {
        public:
        explicit VectoredDatabase(const MultiPattern& mp) : Database(mp,Database::VECTORED) {};
        explicit VectoredDatabase(const MultiPattern& mp, const PlatformInfo& pi ) : Database(mp, Database::VECTORED, pi) {};
        explicit VectoredDatabase(const MultiPatternExtended& mpe) : Database(mpe,Database::VECTORED) {};
        explicit VectoredDatabase(const MultiPatternExtended& mpe, const PlatformInfo& pi ) : Database(mpe, Database::VECTORED, pi) {};
        explicit VectoredDatabase(const MultiLiteral& ml) : Database(ml,Database::VECTORED) {};
        explicit VectoredDatabase(const MultiLiteral& ml, const PlatformInfo& pi ) : Database(ml, Database::VECTORED, pi) {};
        explicit VectoredDatabase(const Pattern& sp) : Database(sp,Database::VECTORED) {};
        explicit VectoredDatabase(const Pattern& sp, const PlatformInfo& pi ) : Database(sp, Database::VECTORED, pi) {};
        explicit VectoredDatabase(const Literal& sl) : Database(sl,Database::VECTORED) {};
        explicit VectoredDatabase(const Literal& sl, const PlatformInfo& pi ) : Database(sl, Database::VECTORED, pi) {};
        VectoredDatabase() = delete;
        VectoredDatabase (const VectoredDatabase& db) = delete;
        VectoredDatabase& operator= (const VectoredDatabase& db) = delete;
        VectoredDatabase(VectoredDatabase&& db) = default;
        VectoredDatabase& operator=(VectoredDatabase&& db) = default;
        ~VectoredDatabase() = default;
    };
}

#endif //_HYPERSCAN_VECTOREDDATABASE_H

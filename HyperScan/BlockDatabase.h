/*
 * @file BlockDatabase.h
 * @brief Derived from Database class provides BlockDatabase functions for HyperScan
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

#ifndef _HYPERSCAN_BLOCKDATABASE_H
#define _HYPERSCAN_BLOCKDATABASE_H

#include "Database.h"

namespace HyperScan {
    class BlockDatabase final : public Database {
        public:
        explicit BlockDatabase(const MultiPattern& mp, Horizon horizon = Horizon::NONE) : Database(mp,Database::BLOCK,horizon) {};
        explicit BlockDatabase(const MultiPattern& mp, const PlatformInfo& pi, Horizon horizon = Horizon::NONE ) : Database(mp, Database::BLOCK, pi, horizon) {};
        explicit BlockDatabase(const MultiPatternExtended& mpe, Horizon horizon = Horizon::NONE ) : Database(mpe,Database::BLOCK, horizon) {};
        explicit BlockDatabase(const MultiPatternExtended& mpe, const PlatformInfo& pi, Horizon horizon = Horizon::NONE  ) : Database(mpe, Database::BLOCK, pi, horizon) {};
        explicit BlockDatabase(const MultiLiteral& ml, Horizon horizon = Horizon::NONE ) : Database(ml,Database::BLOCK,horizon) {};
        explicit BlockDatabase(const MultiLiteral& ml, const PlatformInfo& pi, Horizon horizon = Horizon::NONE ) : Database(ml, Database::BLOCK, pi, horizon) {};
        explicit BlockDatabase(const Pattern& sp, Horizon horizon = Horizon::NONE ) : Database(sp,Database::BLOCK, horizon) {};
        explicit BlockDatabase(const Pattern& sp, const PlatformInfo& pi, Horizon horizon = Horizon::NONE  ) : Database(sp, Database::BLOCK, pi, horizon) {};
        explicit BlockDatabase(const Literal& sl, Horizon horizon = Horizon::NONE ) : Database(sl,Database::BLOCK, horizon) {};
        explicit BlockDatabase(const Literal& sl, const PlatformInfo& pi, Horizon horizon = Horizon::NONE  ) : Database(sl, Database::BLOCK, pi, horizon) {};

        BlockDatabase() = delete;
        BlockDatabase (const BlockDatabase& db) = delete;
        BlockDatabase& operator= (const BlockDatabase& db) = delete;
        BlockDatabase(BlockDatabase&& db) = default;
        BlockDatabase& operator=(BlockDatabase&& db) = default;
        ~BlockDatabase() = default;
    };
}

#endif //BLPARSER_BLOCKDATABASE_H

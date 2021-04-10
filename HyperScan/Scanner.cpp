/*
 * @file VectorScanner.cpp
 * @brief VectorScanner class currently provides static functions but may become an object in the future. Provides the hs_scan_vector functionality.
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

#include "Scanner.h"
#include "VectorDatabase.h"
#include "BlockDatabase.h"
#include "Stream.h"
#include "Scratch.h"

namespace HyperScan {
    hs_error_t Scanner::Scan(VectorDatabase &db, Scratch &scratch, IMatcher &matcher, const std::vector<std::vector<char>> &blocks) {
        // TODO: Limits exist on unsigned int vs size_t should address this.
        unsigned int size = blocks.size();
        std::vector<const char *> b;
        std::vector<unsigned int> s;
        for (const auto &block : blocks) {
            b.push_back(block.data());
            s.push_back(block.size());
        }
        return hs_scan_vector(db._db.get(), b.data(), s.data(), size, 0, scratch._scratch.get(), IScanner::match_event, &matcher);
    }
    hs_error_t Scanner::Scan(VectorDatabase &db, Scratch &scratch, IMatcher &matcher, const std::vector<std::string> &blocks) {
        // TODO: Limits exist on unsigned int vs size_t should address this.
        unsigned int size = blocks.size();
        std::vector<const char *> b;
        std::vector<unsigned int> s;
        for (const auto &block : blocks) {
            b.push_back(block.data());
            s.push_back(block.size());
        }
        return hs_scan_vector(db._db.get(), b.data(), s.data(), size, 0, scratch._scratch.get(), IScanner::match_event, &matcher);
    }
    hs_error_t Scanner::Scan(BlockDatabase &db, Scratch &scratch, IMatcher &matcher, const std::vector<char> &data) {
        return hs_scan(db._db.get(), data.data(), data.size(), 0, scratch._scratch.get(), IScanner::match_event, &matcher);
    }
    hs_error_t Scanner::Scan(BlockDatabase &db, Scratch &scratch, IMatcher &matcher, const std::string &data) {
        return hs_scan(db._db.get(), data.data(), data.size(), 0, scratch._scratch.get(), IScanner::match_event, &matcher);
    }
    hs_error_t Scanner::Scan(BlockDatabase &db, Scratch &scratch, IMatcher &matcher, const char *buffer, unsigned int length) {
        return hs_scan(db._db.get(), buffer, length, 0, scratch._scratch.get(), IScanner::match_event, &matcher);
    }
    hs_error_t Scanner::Scan(Stream &stream, Scratch &scratch, IMatcher &matcher, const std::vector<char> &data) {
        return hs_scan_stream(stream._stream.get(), data.data(), data.size(), 0, scratch._scratch.get(), IScanner::match_event, &matcher);
    }
    hs_error_t Scanner::Scan(Stream &stream, Scratch &scratch, IMatcher &matcher, const std::string &data) {
        return hs_scan_stream(stream._stream.get(), data.data(), data.size(), 0, scratch._scratch.get(), IScanner::match_event, &matcher);
    }
    hs_error_t Scanner::Scan(Stream &stream, Scratch &scratch, IMatcher &matcher, const char *data, unsigned int length) {
        return hs_scan_stream(stream._stream.get(), data, length, 0, scratch._scratch.get(), IScanner::match_event, &matcher);
    }
}
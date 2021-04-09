/*
 * @file StreamScanner.h
 * @brief StreamScanner class wraps hs_stream_t and implements IScanner for hs_scan_stream
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

#ifndef _HYPERSCAN_STREAMSCANNER_H
#define _HYPERSCAN_STREAMSCANNER_H

#include <hs/hs.h>
#include <string>
#include <vector>
#include <memory>
#include "IScanner.h"

namespace HyperScan {
    class Database;
    class Scratch;
    class StreamDatabase;
    class StreamScanner : public IScanner {
    public:
        StreamScanner() = delete;
        StreamScanner( const StreamScanner& ) = delete;
        StreamScanner& operator=( const StreamScanner& ) = delete;
        StreamScanner(StreamDatabase &db, Scratch &scratch, IMatcher &matcher);
        ~StreamScanner();
    public:
        hs_error_t Scan(const std::vector<char>& data);
        hs_error_t Scan(const std::string& data);
        hs_error_t Scan(const char *data, unsigned int length);
        hs_error_t Reset();
        hs_error_t Close();
        hs_error_t Open();
    private:
        hs_stream_t* _stream;
        Database* _db;
        Scratch* _scratch;
        IMatcher* _matcher;
    };
}

#endif //_HYPERSCAN_STREAMSCANNER_H

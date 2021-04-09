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

#include "StreamScanner.h"
#include "StreamDatabase.h"
#include "Scratch.h"

namespace HyperScan{
    StreamScanner::StreamScanner(StreamDatabase &db, Scratch &scratch, IMatcher &matcher) : _stream(nullptr) , _db(&db) , _scratch(&scratch), _matcher(&matcher) {}
    StreamScanner::~StreamScanner(){
        if( _stream )
            hs_close_stream(_stream,_scratch->_scratch.get(),IScanner::match_event,_matcher);
    }
    hs_error_t StreamScanner::Scan(const std::vector<char>& data) {
        return hs_scan_stream(_stream, data.data(), data.size(), 0, _scratch->_scratch.get(), IScanner::match_event, _matcher);
    }
    hs_error_t StreamScanner::Scan(const std::string& data) {
        return hs_scan_stream(_stream, data.data(), data.size(), 0, _scratch->_scratch.get(), IScanner::match_event, _matcher);
    }
    hs_error_t StreamScanner::Scan(const char* data, unsigned int length) {
        return hs_scan_stream(_stream, data, length, 0, _scratch->_scratch.get(), IScanner::match_event, _matcher);
    }
    hs_error_t StreamScanner::Reset() {
        return hs_reset_stream(_stream,0,_scratch->_scratch.get(),IScanner::match_event,_matcher);
    }
    hs_error_t StreamScanner::Close() {
        hs_error_t error = HS_SUCCESS;
        if( _stream != nullptr ) {
            error = hs_close_stream(_stream, _scratch->_scratch.get(), IScanner::match_event, _matcher);
            if( error == HS_SUCCESS )
                _stream = nullptr;
        }
        return error;
    }
    hs_error_t StreamScanner::Open() {
        hs_error_t error = HS_SUCCESS;
        if( _stream == nullptr ) {
            error = hs_open_stream(_db->_db.get(), 0, &_stream);
        }
        return error;
    }
}
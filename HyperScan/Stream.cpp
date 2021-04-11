/*
 * @file Stream.h
 * @brief Stream class wraps hs_stream_t
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
#include "Stream.h"
#include "StreamDatabase.h"
#include "Scratch.h"

namespace HyperScan {
    Stream::Stream(hs_stream_t *stream) : _stream(stream) {}
    Stream::Stream() : _stream(nullptr) {}
    void Stream::Open(StreamDatabase &db) {
        hs_stream_t *stream = nullptr;
        hs_error_t hs_code = hs_open_stream(db._db.get(), 0, &stream);
        _stream.reset(stream);
        if (hs_code != HS_SUCCESS)
            throw StreamException("Failed to hs_open_stream failed", hs_code);
    }
    void Stream::Close() {
        _stream.reset();
    }
    void Stream::Close(const Scratch& scratch) {
        hs_stream_t* stream = _stream.release();
        hs_close_stream(stream, scratch._scratch.get(), nullptr, nullptr);
    }
    void Stream::Close(const Scratch& scratch, IMatcher &matcher) {
        hs_stream_t* stream = _stream.release();
        hs_close_stream(stream, scratch._scratch.get(), IScanner::match_event, &matcher);
    }
    Stream Stream::Clone() {
        if (!_stream)
            throw StreamException("Failed to clone, stream isn't opened", HS_INVALID);
        hs_stream_t *stream = nullptr;
        hs_error_t hs_code = hs_copy_stream(&stream,_stream.get());
        Stream s(stream);
        if (hs_code != HS_SUCCESS)
            throw StreamException("Failed to hs_copy_stream failed", hs_code);
        return s;
    }
    void Stream::Reset() {
        hs_reset_stream(_stream.get(), 0, nullptr, nullptr, nullptr);
    }
    void Stream::Reset(const Scratch& scratch) {
        hs_reset_stream(_stream.get(), 0,  scratch._scratch.get(), nullptr, nullptr);
    }
    void Stream::Reset(const Scratch& scratch, IMatcher &matcher) {
        hs_stream_t* stream = _stream.release();
        hs_reset_stream(_stream.get(), 0,  scratch._scratch.get(), IScanner::match_event, &matcher);
    }
}


/*
 * @file ExtendedExpressionContext.cpp
 * @brief Wrapper for hs_expr_ext_t to provided extended expression info
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

#include "ExtendedExpressionContext.h"

namespace HyperScan {
    ExtendedExpressionContext::ExtendedExpressionContext() : _ext({0}) {}
    unsigned long long ExtendedExpressionContext::GetFlags() const { return _ext.flags; }
    unsigned long long ExtendedExpressionContext::GetMinOffset() const { return _ext.min_offset; }
    unsigned long long ExtendedExpressionContext::GetMaxOffset() const { return _ext.max_offset; }
    unsigned long long ExtendedExpressionContext::GetMinLength() const { return _ext.min_length; }
    unsigned ExtendedExpressionContext::GetEditDistance() const { return _ext.edit_distance; }
    unsigned ExtendedExpressionContext::GetHammingDistanced() const { return _ext.hamming_distance; }
    void ExtendedExpressionContext::SetMinOffset(unsigned long long min_offset) {
        _ext.flags |= HS_EXT_FLAG_MIN_OFFSET;
        _ext.min_offset = min_offset;
    }
    void ExtendedExpressionContext::SetMaxOffset(unsigned long long max_offset) {
        _ext.flags |= HS_EXT_FLAG_MAX_OFFSET;
        _ext.max_offset = max_offset;
    }
    void ExtendedExpressionContext::SetMinLength(unsigned long long min_length) {
        _ext.flags |= HS_EXT_FLAG_MIN_LENGTH;
        _ext.min_length = min_length;
    }
    void ExtendedExpressionContext::SetEditDistance(unsigned edit_distance) {
        _ext.flags |= HS_EXT_FLAG_EDIT_DISTANCE;
        _ext.edit_distance = edit_distance;
    }
    void ExtendedExpressionContext::SetHammingDistanced(unsigned hamming_distance) {
        _ext.flags |= HS_EXT_FLAG_HAMMING_DISTANCE;
        _ext.hamming_distance = hamming_distance;
    }
    void ExtendedExpressionContext::ClearMinOffset() {
        _ext.flags &= ~(HS_EXT_FLAG_MIN_OFFSET);
        _ext.min_offset = 0;
    }
    void ExtendedExpressionContext::ClearMaxOffset() {
        _ext.flags &= ~(HS_EXT_FLAG_MAX_OFFSET);
        _ext.max_offset = 0;
    }
    void ExtendedExpressionContext::ClearMinLength() {
        _ext.flags &= ~(HS_EXT_FLAG_MIN_LENGTH);
        _ext.min_length = 0;
    }
    void ExtendedExpressionContext::ClearEditDistance() {
        _ext.flags &= ~(HS_EXT_FLAG_EDIT_DISTANCE);
        _ext.edit_distance = 0;
    }
    void ExtendedExpressionContext::ClearHammingDistanced() {
        _ext.flags &= ~(HS_EXT_FLAG_HAMMING_DISTANCE);
        _ext.hamming_distance = 0;
    }
    bool ExtendedExpressionContext::IsSetMinOffset() const {
        return (_ext.flags & HS_EXT_FLAG_MIN_OFFSET);
    }
    bool ExtendedExpressionContext::IsSetMaxOffset() const {
        return (_ext.flags & HS_EXT_FLAG_MAX_OFFSET);
    }
    bool ExtendedExpressionContext::IsSetMinLength() const {
        return (_ext.flags & HS_EXT_FLAG_MIN_LENGTH);
    }
    bool ExtendedExpressionContext::IsSetEditDistance() const {
        return (_ext.flags & HS_EXT_FLAG_EDIT_DISTANCE);
    }
    bool ExtendedExpressionContext::IsSetHammingDistanced() const {
        return (_ext.flags & HS_EXT_FLAG_HAMMING_DISTANCE);
    }
}



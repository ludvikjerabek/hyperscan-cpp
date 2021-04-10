/*
 * @file ExpressionInfo.cpp
 * @brief Wrapper for hs_expr_info_t to provides expression info
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

#include "ExpressionInfo.h"
#include "Exceptions.h"
#include "Pattern.h"
#include "ExtendedExpressionContext.h"

namespace HyperScan {
    ExpressionInfo::ExpressionInfo(const std::string &pattern, unsigned int flags) : _info(nullptr) {
        hs_compile_error_t *error = nullptr;
        hs_expr_info_t *info;
        hs_error_t hs_code = hs_expression_info(pattern.c_str(), flags, &info, &error);
        _info.reset(info);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_expression_info failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw ExpressionInfoException(e, hs_error, hs_code);
        }
    }
    ExpressionInfo::ExpressionInfo(const std::string &pattern, unsigned int flags, const ExtendedExpressionContext &ext) : _info(nullptr) {
        hs_compile_error_t *error = nullptr;
        hs_expr_info_t *info;
        hs_error_t hs_code = hs_expression_ext_info(pattern.c_str(), flags, &ext._ext, &info, &error);
        _info.reset(info);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_expression_info failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw ExpressionInfoException(e, hs_error, hs_code);
        }
    }
    ExpressionInfo::ExpressionInfo(const Pattern &sp) : _info(nullptr) {
        hs_compile_error_t *error = nullptr;
        hs_expr_info_t *info;
        hs_error_t hs_code = hs_expression_info(sp._pattern.c_str(), sp._flags, &info, &error);
        _info.reset(info);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_expression_info failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw ExpressionInfoException(e, hs_error, hs_code);
        }
    }
    ExpressionInfo::ExpressionInfo(const Pattern &sp, const ExtendedExpressionContext &ext) : _info(nullptr) {
        hs_compile_error_t *error = nullptr;
        hs_expr_info_t *info;
        hs_error_t hs_code = hs_expression_ext_info(sp._pattern.c_str(), sp._flags, &ext._ext, &info, &error);
        _info.reset(info);
        if (hs_code != HS_SUCCESS) {
            std::string e = "Call to hs_expression_info failed";
            int hs_error = 0;
            if (error) {
                e = error->message;
                hs_error = error->expression;
                hs_free_compile_error(error);
            }
            throw ExpressionInfoException(e, hs_error, hs_code);
        }
    }
    char ExpressionInfo::GetMatchesAtEod() const {
        if (!_info)
            throw ExpressionInfoException("Invalid hs_expr_info_t* is null", 0, 0);
        return _info->matches_at_eod;
    }
    char ExpressionInfo::GetMatchesOnlyAtEod() const {
        if (!_info)
            throw ExpressionInfoException("Invalid hs_expr_info_t* is null", 0, 0);
        return _info->matches_only_at_eod;
    }
    unsigned int ExpressionInfo::GetMaxWidth() const {
        if (!_info)
            throw ExpressionInfoException("Invalid hs_expr_info_t* is null", 0, 0);
        return _info->max_width;
    }
    unsigned int ExpressionInfo::GetMinWidth() const {
        if (!_info)
            throw ExpressionInfoException("Invalid hs_expr_info_t* is null", 0, 0);
        return _info->min_width;
    }
    char ExpressionInfo::GetUnorderedMatches() const {
        if (!_info)
            throw ExpressionInfoException("Invalid hs_expr_info_t* is null", 0, 0);
        return _info->unordered_matches;
    }
}
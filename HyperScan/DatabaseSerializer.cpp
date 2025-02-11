/*
 * @file Database.h
 * @brief Database base class. Wrapper for hs_database_t for HyperScan. This class should not be constructed directly.
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

#include <variant>
#include "DatabaseSerializer.h"
#include "Exceptions.h"
#include "BlockDatabase.h"
#include "StreamDatabase.h"
#include "VectorDatabase.h"
#include "Database.h"


namespace HyperScan {
std::vector<char> Serialize(const Database& db)
{
	char* data = nullptr;
	size_t size = 0;
	hs_error_t hs_code = hs_serialize_database(db._db.get(), &data, &size);

	if (hs_code!=HS_SUCCESS) {
		std::string e = "Call to hs_serialize_database failed to serialize database.";
		int hs_error = 0;
		throw DatabaseSerializerException(e, hs_error, hs_code);
	}

	std::vector<char> buffer(data, data+size);
	free(data);

	return buffer;
}

Database Deserialize(std::vector<char> data)
{
	char *info = nullptr;

	hs_error_t hs_code = hs_serialized_database_info(data.data(),data.size(),&info);

	if (hs_code!=HS_SUCCESS) {
		std::string e = "Call to hs_serialized_database_info failed to query database info.";
		int hs_error = 0;
		throw DatabaseSerializerException(e, hs_error, hs_code);
	}

}
}
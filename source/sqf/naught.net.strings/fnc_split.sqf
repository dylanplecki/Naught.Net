/*
	This file is part of Naught.Net.

	Copyright © 2013 Dylan Plecki <dylanplecki@gmail.com>
	All rights reserved.

	Naught.Net is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	Naught.Net is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "script_component.hpp"

SCRIPT(escapeString);
ASSERT_PASSED_ARRAY;
REQUIRED_PARAMS(2);

private ["_string", "_delimeter"];
_string		= _this select 0;
_delimeter	= _this select 1;
_stringArr	= toArray(_string);
_delimArr	= toArray(_delimeter);
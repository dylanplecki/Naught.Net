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

SCRIPT(hashString);
ASSERT_PASSED_ARRAY;
REQUIRED_PARAMS(1);

private ["_string", "_hashType", "_function", "_return"];
_string		= _this select 0;
_hashType	= PARAM_DEFAULT(1,2);
_return		= "";

_function = switch (_hashType) do {
	case 0: {"HashMD2"};
	case 1: {"HashMD4"};
	case 2: {"HashMD5"};
	case 3: {"HashSHA1"};
	case 4: {"HashSHA256"};
	default {"HashMD5"};
};

if (_function != "") then {
	_return = [_function, _string] call COMMONFUNC(callExtensionWrapper);
};

_return
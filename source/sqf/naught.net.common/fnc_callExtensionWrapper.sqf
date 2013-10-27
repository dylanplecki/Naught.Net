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

SCRIPT(callExtensionWrapper);
ASSERT_PASSED_ARRAY;

#define MESSAGE_TYPES [RETURN_ERROR, RETURN_TRUNCATED, RETURN_HANDLE, RETURN_NULL]

private ["_return"];
_return = _this call COMMONFUNC(callExtension);

if ((toArray(_return) select 0) == (toArray(RETURN_GENERIC) select 0)) then { // Possible Message from Extension
	private ["_message"];
	_message = [_return, PARAM_DELIMETER] call CBA_fnc_split;
	switch (_message select 0) do {
		case RETURN_ERROR: {
			_return = false;
			ERROR("Naught.Net CallExtension Wrapper", _message select 1);
		};
		case RETURN_TRUNCATED: {
			_return = [parseNumber(_message select 1), parseNumber(_message select 2)] call COMMONFUNC(getTruncatedResult);
		};
		case RETURN_HANDLE: {
			_return = parseNumber(_message select 1);
		};
		case RETURN_NULL: {
			_return = nil;
		};
	};
};

_return
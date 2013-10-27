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

SCRIPT(concatenateArgs);
ASSERT_PASSED_ARRAY;

private ["_function", "_parameters", "_return"];
_function		= _this select 0;
_parameters		= PARAM_DEFAULT(1, []);
_return			= "";

if ( !IS_TYPE(_parameters, "ARRAY") ) then {
	_parameters = [_parameters];
};

if ((count _parameters) > 0) then {
	private ["_temp"];
	_temp = "";
	for "_i" from 0 to ((count _parameters) - 1) do {
		private ["_string"];
		_string = format["%1", (_parameters select _i)];
		if (_string != "") then {
			if (_temp != "") then {_temp = _temp + PARAM_DELIMETER};
			_temp = _temp + ([_string, PARAM_DELIMETER, "-"] call CBA_fnc_replace);
		};
	};
	_parameters = _temp;
} else {
	_parameters = "";
};

if (_parameters != "") then {
	_return = _function + FUNC_DELIMETER + _parameters;
} else {
	_return = _function;
};

_return
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

// ["protocol://address.domain:port", {return = _this;}(, timeOutInt, "PostData")] call NDT_fnc_newConnectionHandler;

SCRIPT(newConnectionHandler);
ASSERT_PASSED_ARRAY;
REQUIRED_PARAMS(2);

private ["_address", "_code", "_params", "_scriptHandle"];
_address	= _this select 0;
_code		= _this select 1;
_params		= [_address];

if ((count _this) > 2) then {_params set [1, parseNumber(str(_this select 2))]}; // Force Number (default 0 - no timeout)
if ((count _this) > 3) then {_params set [2, (_this select 3)]};

_scriptHandle = ["Download", _params, _code] call COMMONFUNC(newReturnHandler);

_scriptHandle
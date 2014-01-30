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

SCRIPT(newReturnHandler);
ASSERT_PASSED_ARRAY;
REQUIRED_PARAMS(3);

private ["_handle"];
_handle = _this spawn {
	private ["_params", "_return"];
	_function	= _this select 0;
	_params		= _this select 1;
	_code		= _this select 2;
	
	_return = [_function, _params] call COMMONFUNC(callExtensionWrapper);
	
	//TRACE_3("Naught.Net Return Handler: Break Point 1", _gvar, _params, _return);
	
	if ( IS_TYPE(_code, "STRING") ) then {
		_code = compile _code;
	};
	
	if ( IS_TYPE(_return, "SCALAR") ) then {
		private ["_rHandle"];
		_rHandle = _return;
		waitUntil {
			_return = ["ReturnData", _rHandle] call COMMONFUNC(callExtensionWrapper);
			!(isNil "_return");
		};
		//TRACE_2("Naught.Net Return Handler: Break Point 2", _rHandle, _return);
	};
	
	_return call _code;
};

_handle
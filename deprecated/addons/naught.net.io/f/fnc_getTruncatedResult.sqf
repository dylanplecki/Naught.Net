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

SCRIPT(getTruncatedResult);
ASSERT_PASSED_ARRAY;

private ["_resultHandle", "_chunks", "_return"];
_resultHandle	= _this select 0;
_chunks			= _this select 1;
_return			= "";

for "_chunk" from 1 to _chunks do {
	_result = ["GetResultChunk", [_resultHandle, _chunk]] call COMMONFUNC(callExtensionWrapper);
	if ( IS_TYPE(_result, "STRING") ) then {
		_return = _return + _result;
	};
};

_return
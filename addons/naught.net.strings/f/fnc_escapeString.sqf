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
REQUIRED_PARAMS(1);

#define ESCAPED_CHARACTERS \
	[ \
		["!", "%21"], ["#", "%23"], ["$", "%24"], ["&", "%26"], ["'", "%27"], ["(", "%28"], \
		[")", "%29"], ["*", "%2A"], ["+", "%2B"], [",", "%2C"], ["/", "%2F"], [":", "%3A"], \
		[";", "%3B"], ["=", "%3D"], ["?", "%3F"], ["@", "%40"], ["[", "%5B"], ["]", "%5D"], \
		[" ", "%20"], ["%", "%25"], ["-", "%2D"], [".", "%2E"], ["<", "%3C"], [">", "%3E"], \
		["\", "%5C"], ["^", "%5E"], ["_", "%5F"], ["`", "%60"], ["{", "%7B"], ["|", "%7C"], \
		["}", "%7D"], ["~", "%7E"], ["""", "%22"], ["\n", "%0D%0A"] \
	] \

private ["_stringArr", "_return"];
_stringArr	= toArray(_this select 0);
_return		= [];

for "_i" from 0 to ((count _stringArr) - 1) do {
	private ["_char", "_escaped"];
	_char		= _stringArr select _i;
	_escaped	= false;
	
	{
		if (_char == (toArray(_x select 0) select 0)) exitWith {
			_return = _return + toArray(_x select 1);
			_escaped = true;
		};
	} forEach ESCAPED_CHARACTERS;
	
	if (!_escaped) then {
		_return = _return + [_char];
	};
};

toString(_return);
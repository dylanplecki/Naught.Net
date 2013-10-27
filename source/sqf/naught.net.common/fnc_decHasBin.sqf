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

private ["_decimal", "_binary", "_return"];

_decimal	= _this select 0;
_binary		= _this select 1;
_return		= false;

if (_binary != 0) then {
	if (_decimal == _binary) then {_return = true};
	if (_decimal > _binary) then {
		if (((log(_binary) / log(2)) % 1) == 0) then {
			if (floor((_decimal / _binary) % 2) == 1) then {
				_return = true;
			};
		} else {
			if (((_binary % 1) == 0) && ((_decimal % 1) == 0)) then {
				private ["_i"];
				_i = 0;
				_return = true;
				while {_binary > 0} do {
					if (((_binary mod 2) == 1) && ((_decimal mod 2) != 1)) exitWith {_return = false};
					_binary = floor(_binary / 2);
					_decimal = floor(_decimal / 2);
					_i = _i + 1;
				};
			};
		};
	};
};

_return

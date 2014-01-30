
/*
	Section: Strings Library
	Author(s): Naught
	Version: 1.0
	
	License:
		Copyright © 2014 Dylan Plecki. All rights reserved.
		Except where otherwise noted, this work is licensed under CC BY-NC-ND 4.0,
		available for reference at <http://creativecommons.org/licenses/by-nc-nd/4.0/>.
*/

/*
	Group: Functions
*/

NDT_fnc_concatenateArgs = {
	private ["_arguments", "_delimeter", "_return"];
	_arguments = [_this, 0] call NDT_fnc_param;
	_delimeter = [_this, 1, "@"] call NDT_fnc_param;
	_return = "";
	if (typeName(_arguments) != "ARRAY") then {_arguments = [_arguments]};
	{ // forEach
		if (_forEachIndex > 0) then {_return = _return + _delimeter};
		_return = _return + (if (typeName(_x) == "STRING") then {_x} else {str(_x)});
	} forEach _arguments;
	_return
};

NDT_fnc_padString = {
	private ["_value", "_length", "_padding", "_direction", "_padCount"];
	_value = toArray([_this, 0] call NDT_fnc_param);
	_length = [_this, 1] call NDT_fnc_param;
	_padding = toArray([_this, 2, " "] call NDT_fnc_param) select 0;
	_direction = [_this, 3, 0] call NDT_fnc_param; // Negative left, positive right
	_padCount = _length - (count _value);
	if (_padCount != 0) then {
		private ["_tempPad"];
		_tempPad = [];
		for "_i" from 1 to abs(_padCount) do {
			_tempPad set [count _tempPad, _padding];
		};
		switch (true) do {
			case (_padCount > 0): { // Append right
				_value = _value + _tempPad;
			};
			case (_padCount < 0): { // Insert left
				_value = _tempPad + _value;
			};
		};
	};
	toString(_value);
};

NDT_fnc_trimString = {
	
};
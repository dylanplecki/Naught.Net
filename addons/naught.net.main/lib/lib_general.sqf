
/*
	Section: General Library
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

/*
	Function: NDT_fnc_param
	Author(s): Naught
	
	Description:
		Selects passed parameters based on index,
		type, and length. Supports default options.
	
	Parameter(s):
		0: Reference Parameter Array [ARRAY]
		1: Reference Parameter Index [SCALAR]
		2: Default Value [ANY] (Optional)
		3: Value Types List [ARRAY] (Optional)
		4: Parameter Array Length [SCALAR] (Optional)
	
	Example(s):
		_var = [_this, 0] call NDT_fnc_param;
		_obj = [_this, 1, player, ["OBJECT"]] call NDT_fnc_param;
		_pos = [_this, 2, [0,0,0], ["ARRAY"], 3] call NDT_fnc_param;
*/

NDT_fnc_param = {
	private ["_paramArr", "_index", "_thisCount", "_value"];
	_paramArr = _this select 0;
	_index = _this select 1;
	_thisCount = count _this;
	_value = nil;
	if ((count _paramArr) > _index) then {
		_value = _paramArr select _index;
	};
	if (_thisCount > 2) then { // Do Parameter Checks
		private ["_default"];
		_default = _this select 2;
		if (isNil "_value") then { // Set Default
			_value = _default;
		} else {
			if ((_thisCount > 3) &&
				{!(typeName(_value) in (_this select 3))}
			) then { // Check Types
				["NDT_fnc_param", "NOTICE", format["Invalid parameter '%1' (@%2) passed to function expecting type set '%3'.", _value, _index, (_this select 3)], __FILE__, __LINE__] call NDT_fnc_log;
				_value = _default;
			};
			if ((typeName(_value) == "ARRAY") &&
				{_thisCount > 4} &&
				{(count _value) != (_this select 4)}
			) then { // Check Array Length
				["NDT_fnc_param", "NOTICE", format["Invalid parameter '%1' (@%2) passed to function expecting array of length '%3'.", _value, _index, (_this select 4)], __FILE__, __LINE__] call NDT_fnc_log;
				_value = _default;
			};
		};
	};
	_value
};
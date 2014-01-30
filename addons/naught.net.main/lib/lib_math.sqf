
/*
	Section: Math Library
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

NDT_fnc_testBinString = {
	private ["_binString", "_binIndex"];
	_binString = [_this, 0] call NDT_fnc_param;
	_binIndex = [_this, 1] call NDT_fnc_param;
	(toArray(_binString) select _binIndex) == 31; // 1 (string) == 1 (unicode)
};
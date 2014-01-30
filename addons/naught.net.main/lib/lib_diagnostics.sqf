
/*
	Section: Diagnostics Library
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

NDT_fnc_log = {
	private ["_comp", "_level", "_message", "_file", "_line"];
	_comp = [_this, 0, "Naught.Net"] call NDT_fnc_param;
	_level = [_this, 1, "INFO"] call NDT_fnc_param;
	_message = [_this, 2, ""] call NDT_fnc_param;
	_file = [_this, 3, "N/A"] call NDT_fnc_param;
	_line = [_this, 4, 0] call NDT_fnc_param;
	diag_log text format["LOG: [ L: %1 | C: %2 | DTT: %3 | T: %4 | M: %5 | I: %6 | F: ""%7"":%8 ] %9",
		_level,
		_comp,
		diag_tickTime,
		time,
		missionName,
		worldName,
		_file,
		_line,
		_message
	];
};
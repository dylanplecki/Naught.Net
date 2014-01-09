/* Load All Naught.Net Init Commands */
private ["_initCfg"];
_initCfg = configFile >> "Naught_Net" >> "Init";
for "_i" from 0 to ((count _initCfg) - 1) do {
	private ["_root", "_cmds"];
	_root = _initCfg select _i;
	_cmds = [_root];
	if (isClass(_root)) then {
		{ // forEach
			if (_x select 0) then {
				_cmds set [(count _cmds), (_root >> (_x select 1))];
			};
		} forEach [
			[isServer, "init_server"],
			[isDedicated, "init_dedicated"],
			[(!hasInterface && !isDedicated), "init_hc"],
			[(!isDedicated), "init_client"],
			[true, "init"]
		];
	};
	{ // forEach
		if (isText(_x)) then {
			call compile _x;
		};
	} forEach _cmds;
};
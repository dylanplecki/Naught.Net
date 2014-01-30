
/*
	Section: Extensions Library
	Author(s): Naught
	Version: 1.0
	
	License:
		Copyright © 2014 Dylan Plecki. All rights reserved.
		Except where otherwise noted, this work is licensed under CC BY-NC-ND 4.0,
		available for reference at <http://creativecommons.org/licenses/by-nc-nd/4.0/>.
*/

/*
	Group: Definitions
*/

#define DLL_NAME "Naught.Net"
#define ARGUMENT_DELIM "~"
#define PACKET_FLAG_LEN 16
#define PACKET_IDEN_LEN 5
#define PACKET_ADDR_LEN 32
#define PACKET_FLAG_START 0
#define PACKET_IDEN_START (PACKET_FLAG_START + PACKET_FLAG_LEN)
#define PACKET_ADDR_START (PACKET_IDEN_START + PACKET_IDEN_LEN)
#define PACKET_CONT_START (PACKET_ADDR_START + PACKET_ADDR_LEN)

/*
	Group: Functions
*/

NDT_fnc_encryptPacket = {
	private ["_address", "_arguments", "_packetId", "_packetFlags"];
	_address = [([_this, 0] call NDT_fnc_param), PACKET_ADDR_LEN, ' ', 1] call NDT_fnc_padString;
	_arguments = [([_this, 1, []] call NDT_fnc_param), ARGUMENT_DELIM] call NDT_fnc_concatenateArgs;
	_packetId = [([_this, 2, 0] call NDT_fnc_param), PACKET_IDEN_LEN, '0', -1] call NDT_fnc_padString;
	_packetFlags = [([_this, 3, ""] call NDT_fnc_param), PACKET_FLAG_LEN, '0', 1] call NDT_fnc_padString;
	_packetFlags + _packetId + _address + _arguments;
};

NDT_fnc_decryptPacket = {
	private ["_packet"];
	_packet = toArray([_this, 0] call NDT_fnc_param);
	_flags = [];
	_id = [];
	_address = [];
	_content = [];
	{ // forEach
		switch (true) do {
			case (_forEachIndex < PACKET_IDEN_START): {_flags set [count _flags, _x]};
			case (_forEachIndex < PACKET_ADDR_START): {_id set [count _id, _x]};
			case (_forEachIndex < PACKET_CONT_START): {_address set [count _address, _x]};
			default {_content set [count _content, _x]};
		};
	} forEach _packet;
	[toString(_flags), parseNumber(toString(_id)), toString(_address), toString(_content)];
};

NDT_fnc_callExtension = {
	private ["_packet", "_result", "_flags"];
	_packet = _this call NDT_fnc_encryptPacket;
	_result = [DLL_NAME callExtension _packet] call NDT_fnc_decryptPacket;
	_flags = _result select 0;
	switch (true) do { // Return values
		case ([_flags, FLAG_ERROR] call NDT_fnc_testBinString): { // Error, return nil with diag_log error
			["NDT_fnc_callExtension", "ERROR", ((_result select 3) + " | Packet Dump: " + _packet), __FILE__, __LINE__] call NDT_fnc_log;
			nil;
		};
		case ([_flags, FLAG_ASYNC] call NDT_fnc_testBinString): { // Asynchronous handler, return package ID
			_result select 1;
		};
		case ([_flags, FLAG_MULTI_PART] call NDT_fnc_testBinString): { // Multi-part file, gather parts and return content
			
		};
		case ([_flags, FLAG_OUT_OF_BOUNDS] call NDT_fnc_testBinString): { // Out-Of-Bounds, return nil without error
			nil;
		};
		default { // Good call, return content
			_result select 3;
		};
	};
};
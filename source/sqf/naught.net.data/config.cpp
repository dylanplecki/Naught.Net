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

class Naught_Net; // External Class Reference

class CfgPatches {
	class Naught_Net_Data {
		units[] = {};
		requiredVersion = 1;
		requiredAddons[] = {"Naught_Net_Main", "Naught_Net_Common"};
		version = VERSION;
		author[] = {"Naught"};
	};
};

class CfgPatches {
	class Naught_Net_IO : Naught_Net {
		requiredAddons[] = {"Naught_Net_Main", "Naught_Net_Common", "Naught_Net_Strings"};
	};
};

class CfgFunctions {
	class NDT {
		class Data {
			class parseXML {
				description = "Create a new connection handler to connect to a server/program and call handler code. Param 0: Address [String] (""protocol://address.domain:port""); Param 1: Handler Code [Code] (Passes download return as _this); Param 2: TimeOut Seconds [Int] (Optional); Param 3: Post Data [String] (Optional). Return: Handle to Asynchronous Code [Script].";
				file = QUOTE(PATHTOF(fnc_parseXML.sqf));
			};
		};
	};
};
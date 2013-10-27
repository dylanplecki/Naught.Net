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

class CfgPatches {
	class naught_net_common {
		units[] = {};
		requiredVersion = 1;
		requiredAddons[] = { "naught_net_main" };
		version = VERSION;
		author[] = {"Naught"};
		authorUrl = "http://unitedoperations.net";
	};
};

class CfgFunctions {
	class NDT {
		class Common {
			class getVersion {
				description = "Get version of the Naught.Net extension (Naught.Net.dll). Return: Version [String] (empty if unloaded).";
				file = QUOTE(PATHTOF(fnc_getVersion.sqf));
			};
		};
	};
};

class Extended_PreInit_EventHandlers {
	naught_net_common_preInit = "[] execVM ""x\Naught.Net\addons\naught.net.common\XEH_preInit.sqf"";";
};
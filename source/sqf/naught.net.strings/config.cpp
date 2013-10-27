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
	class naught_net_strings {
		units[] = {};
		requiredVersion = 1;
		requiredAddons[] = { "naught_net_main", "naught_net_common" };
		version = VERSION;
		author[] = {"Naught"};
		authorUrl = "http://unitedoperations.net";
	};
};

class CfgFunctions {
	class NDT {
		class Strings {
			class hashString {
				description = "Hash a string. Hash Types are: 0=MD2, 1=MD4, 2=MD5, 3=SHA1, 4=SHA256. Param 0: Text [String]; Param 1: Hash Type [Integer] (Optional). Return: Hash [String].";
				file = QUOTE(PATHTOF(fnc_hashString.sqf));
			};
			class regexMatch {
				description = "Check if text matches a given regular expression. Param 0: Text [String]; Param 1: Regex [String]. Return: Encapsulated Boolean [String] (ie. ""true"").";
				file = QUOTE(PATHTOF(fnc_regexMatch.sqf));
			};
			class regexSearch {
				description = "Search text for characters matching a regular expression. Param 0: Text [String]; Param 1: Regex [String]; Param 2: Max Iterations [Int] (Optional). Return: Encapsulated Array [String] (ie. ""[['match1'], ['subMatch1', 'subMatch2']]"").";
				file = QUOTE(PATHTOF(fnc_regexSearch.sqf));
			};
			class regexReplace {
				description = "Replace all characters matching a regular expression. Param 0: Text [String]; Param 1: Regex [String]; Param 2: Replace With [String]. Return: New Text [String].";
				file = QUOTE(PATHTOF(fnc_regexReplace.sqf));
			};
			class escapeString {
				description = "Escape a string (URL | URI | GET_DATA | POST-DATA) for web using percent (URL) encoding on reserved characters. You should not escape an entire URL. Param 0: Text [String]. Return: Escaped Text [String].";
				file = QUOTE(PATHTOF(fnc_escapeString.sqf));
			};
		};
	};
};
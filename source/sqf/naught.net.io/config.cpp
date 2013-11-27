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

class Naught_Net { // External Class Reference
	class Registry {
		class DllExtension {
			dllName = "Naught.Net";
			class Delimiters {
				function = "#";
				parameter = "~";
				returnValue = "!";
			};
			class Messages {
				error = "NAUGHT_NET_ERROR";
				truncated = "NAUGHT_NET_TRUNC";
				handle = "NAUGHT_NET_HANDL";
				null = "NAUGHT_NET__NULL";
			};
		};
	};
};

class CfgPatches {
	class Naught_Net_IO : Naught_Net {
		requiredAddons[] = {"Naught_Net_Main", "Naught_Net_Common", "Naught_Net_Strings"};
	};
};
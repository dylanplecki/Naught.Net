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

class Naught_Net
{
	/* General Information */
	name = "Naught.Net";
	dir = "@Naught.Net";
	version = 1.0.1.1;
	author[] = {"Naught"};
	authorUrl = "http://github.com/dylanplecki/Naught.Net";
	
	/* Requirements */
	requiredAddons[] = {};
	requiredVersion = 1;
	
	/* Includes */
	units[] = {};
	weapons[] = {};
	
	/* Display */
	hideName = "false";
	hidePicture = "false";
	picture = "\x\Naught.Net\addons\naught.net.main\rsc\images\Naught_Net.png";
	
	/* Extra */
	actionName = "Website";
	action = "http://github.com/dylanplecki/Naught.Net";
	description = "Issues: http://github.com/dylanplecki/Naught.Net/issues<br />Documentation: http://github.com/dylanplecki/Naught.Net/wiki";
	
	/* Registry: Static Definitions */
	class Registry {};
};

class CfgPatches {
	class Naught_Net_Main : Naught_Net {};
};

class CfgMods {
	class Naught_Net_Mod : Naught_Net {};
};
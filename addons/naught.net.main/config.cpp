
class Naught_Net
{
	/* General Information */
	name = "Naught.Net";
	dir = "@Naught.Net";
	author[] = {"Naught"};
	authorUrl = "http://github.com/dylanplecki/Naught.Net";
	
	/* Versioning */
	version = 2.0.0.1;
	versionStr = "2.0.0.1";
	versionAr[] = {2,0,0,1};
	
	/* Requirements */
	requiredAddons[] = {};
	requiredVersion = 1.0;
	
	/* Includes */
	units[] = {};
	weapons[] = {};
	
	/* Display */
	hideName = "false";
	hidePicture = "false";
	picture = "\naught.net.main\rsc\images\Naught_Net.png";
	
	/* Extra */
	actionName = "Website";
	action = "http://github.com/dylanplecki/Naught.Net";
	description = "Issues: http://github.com/dylanplecki/Naught.Net/issues<br />Documentation: http://github.com/dylanplecki/Naught.Net/wiki";
	
	/* Registry: Static Definitions */
	class Registry {
		
	};
	
	/* Functions */
	class Functions {
		tag = "NDT";
		init = "\naught.net.main\init.sqf";
	};
};

class CfgPatches {
	class Naught_Net_Main : Naught_Net {};
};

class CfgMods {
	class Naught_Net_Mod : Naught_Net {};
};

class CfgFunctions {
	class Naught_Net_Functions : Naught_Net {};
};
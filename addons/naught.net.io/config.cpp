
class Naught_Net { // External Class Reference
	class Init {
		class IO_Init {
			init = "call compile preProcessFileLineNumbers '\x\Naught.Net\addons\naught.net.io\init.sqf'";
		};
	};
};

class CfgPatches {
	class Naught_Net_IO : Naught_Net {
		requiredAddons[] = {"Naught_Net_Main"};
	};
};
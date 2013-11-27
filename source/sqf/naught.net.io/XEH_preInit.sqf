#include "script_component.hpp"

SCRIPT(XEH_preInit);

ADDON = false;

_fnc_sendError = {
	ERROR("Naught.Net Extension PreInit", _this);
	uiSleep 2;
	hint _this;
	player sideChat _this;
};

/* Prep Functions */
PREPCOMMON(callExtensionWrapper);
PREPCOMMON(newReturnHandler);
PREP(callExtension);
PREP(concatenateArgs);
PREP(getTruncatedResult);
PREP(testExtension);

/* Initialize Extension */
private ["_null"];
_null = EXTENSION_NAME callExtension "Initialization";

/* Check Version & Status */
private ["_version"];
waitUntil {!isNil "NDT_fnc_getVersion"};
_version = call NDT_fnc_getVersion;
if (_version != "") then {
	GVARMAIN(extension_loaded) = true;
	if (_version != (QUOTE(PLATFORM) + " " + QUOTE(VERSION))) then {
		(format["ERROR: The Naught.Net extension version is mismatched! Addon: %1. Extension: %2.", QUOTE(VERSION), _version]) spawn _fnc_sendError;
	};
} else {
	("ERROR: The Naught.Net extension is not loaded!") spawn _fnc_sendError;
};

ADDON = true;
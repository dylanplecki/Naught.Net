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
PREPCOMMON(callExtension);
PREPCOMMON(callExtensionWrapper);
PREPCOMMON(concatenateArgs);
PREPCOMMON(decHasBin);
PREPCOMMON(getTruncatedResult);
PREPCOMMON(log);
PREPCOMMON(newReturnHandler);
PREPCOMMON(testExtension);

/* Logging Values */
GVARMAIN(LOG_NONE)		= DEBUG_LEVEL_NONE;		// None
GVARMAIN(LOG_CRIT)		= DEBUG_LEVEL_CRIT;		// Critical
GVARMAIN(LOG_ERROR)		= DEBUG_LEVEL_ERROR;	// Error
GVARMAIN(LOG_WARN)		= DEBUG_LEVEL_WARN;		// Warning
GVARMAIN(LOG_NOTICE)	= DEBUG_LEVEL_NOTICE;	// Notice
GVARMAIN(LOG_INFO)		= DEBUG_LEVEL_INFO;		// Info
GVARMAIN(LOG_ALL)		= DEBUG_LEVEL_ALL;		// All

/* Set to Default Logging Level */
GVARMAIN(LOG_LEVEL)		= DEBUG_LEVEL_DEFAULT;	// Global Default

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
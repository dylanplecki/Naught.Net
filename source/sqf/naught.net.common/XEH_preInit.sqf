#include "script_component.hpp"

SCRIPT(XEH_preInit);

ADDON = false;

/* Prep Functions */
PREPCOMMON(checkPath);
PREPCOMMON(decHasBin);
PREPCOMMON(log);

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

ADDON = true;
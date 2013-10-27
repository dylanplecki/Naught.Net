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

///////////////////
/* Custom Macros */
///////////////////

#define PATHTO_SYS(var1,var2,var3)		MAINPREFIX\PREFIX_DIR\SUBPREFIX\PREFIX_CAT.##var2\##var3.sqf
#define PATHTOF_SYS(var1,var2,var3)		MAINPREFIX\PREFIX_DIR\SUBPREFIX\PREFIX_CAT.##var2\##var3
#define PATHTOF2_SYS(var1,var2,var3)	MAINPREFIX\PREFIX_DIR\SUBPREFIX\PREFIX_CAT.##var2\##var3

///////////////////////
/* CBA Common Macros */
///////////////////////

#include "\x\cba\addons\main\script_macros_common.hpp"

/////////////////
/* Tree Macros */
/////////////////

#define MACRO_ARRAY_1(v1) [v1]
#define MACRO_ARRAY_2(v1,v2) [v1,v2]
#define MACRO_ARRAY_3(v1,v2,v3) [v1,v2,v3]
#define MACRO_ARRAY_4(v1,v2,v3,v4) [v1,v2,v3,v4]
#define MACRO_ARRAY_5(v1,v2,v3,v4,v5) [v1,v2,v3,v4,v5]
#define MACRO_ARRAY_6(v1,v2,v3,v4,v5,v6) [v1,v2,v3,v4,v5,v6]
#define MACRO_ARRAY_7(v1,v2,v3,v4,v5,v6,v7) [v1,v2,v3,v4,v5,v6,v7]
#define MACRO_ARRAY_8(v1,v2,v3,v4,v5,v6,v7,v8) [v1,v2,v3,v4,v5,v6,v7,v8]
#define MACRO_ARRAY_9(v1,v2,v3,v4,v5,v6,v7,v8,v9) [v1,v2,v3,v4,v5,v6,v7,v8,v9]

////////////////////
/* Logging Macros */
////////////////////

#define DEBUG_LOG(lvl, cmp, txt, pms)	[lvl, cmp, txt, pms, THIS_FILE_, __LINE__] call COMMONFUNC(log)
#define CRIT(comp,text)					DEBUG_LOG(DEBUG_LEVEL_CRIT, comp, text, [])
#define ERROR(comp,text)				DEBUG_LOG(DEBUG_LEVEL_ERROR, comp, text, [])
#define WARN(comp,text)					DEBUG_LOG(DEBUG_LEVEL_WARN, comp, text, [])
#define LOG(comp,text)					DEBUG_LOG(DEBUG_LEVEL_NOTICE, comp, text, [])
#define INFO(comp,text)					DEBUG_LOG(DEBUG_LEVEL_INFO, comp, text, [])

/////////////////////////////
/* Debugging [Tree] Macros */
/////////////////////////////

#ifndef PRODUCTION_ENVIRONMENT
	#define TRACE_1(cmp,v1) \
		[DEBUG_LEVEL_INFO, cmp, "TRACE: %1", MACRO_ARRAY_1(v1), THIS_FILE_, __LINE__] call COMMONFUNC(log)

	#define TRACE_2(cmp,v1,v2) \
		[DEBUG_LEVEL_INFO, cmp, "TRACE: %1 | %2", MACRO_ARRAY_2(v1,v2), THIS_FILE_, __LINE__] call COMMONFUNC(log)

	#define TRACE_3(cmp,v1,v2,v3) \
		[DEBUG_LEVEL_INFO, cmp, "TRACE: %1 | %2 | %3", MACRO_ARRAY_3(v1,v2,v3), THIS_FILE_, __LINE__] call COMMONFUNC(log)

	#define TRACE_4(cmp,v1,v2,v3,v4) \
		[DEBUG_LEVEL_INFO, cmp, "TRACE: %1 | %2 | %3 | %4", MACRO_ARRAY_4(v1,v2,v3,v4), THIS_FILE_, __LINE__] call COMMONFUNC(log)

	#define TRACE_5(cmp,v1,v2,v3,v4,v5) \
		[DEBUG_LEVEL_INFO, cmp, "TRACE: %1 | %2 | %3 | %4 | %5", MACRO_ARRAY_5(v1,v2,v3,v4,v5), THIS_FILE_, __LINE__] call COMMONFUNC(log)
		
	#define TRACE_6(cmp,v1,v2,v3,v4,v5,v6) \
		[DEBUG_LEVEL_INFO, cmp, "TRACE: %1 | %2 | %3 | %4 | %5 | %6", MACRO_ARRAY_5(v1,v2,v3,v4,v5,v6), THIS_FILE_, __LINE__] call COMMONFUNC(log)
		
	#define TRACE_7(cmp,v1,v2,v3,v4,v5,v6,v7) \
		[DEBUG_LEVEL_INFO, cmp, "TRACE: %1 | %2 | %3 | %4 | %5 | %6 | %7", MACRO_ARRAY_5(v1,v2,v3,v4,v5,v6,v7), THIS_FILE_, __LINE__] call COMMONFUNC(log)
		
	#define TRACE_8(cmp,v1,v2,v3,v4,v5,v6,v7,v8) \
		[DEBUG_LEVEL_INFO, cmp, "TRACE: %1 | %2 | %3 | %4 | %5 | %6 | %7 | %8", MACRO_ARRAY_5(v1,v2,v3,v4,v5,v6,v7,v8), THIS_FILE_, __LINE__] call COMMONFUNC(log)
		
	#define TRACE_9(cmp,v1,v2,v3,v4,v5,v6,v7,v8,v9) \
		[DEBUG_LEVEL_INFO, cmp, "TRACE: %1 | %2 | %3 | %4 | %5 | %6 | %7 | %8 | %9", MACRO_ARRAY_5(v1,v2,v3,v4,v5,v6,v7,v8,v9), THIS_FILE_, __LINE__] call COMMONFUNC(log)
#endif

////////////////////
/* General Macros */
////////////////////

#define IS_TYPE(var,type)				(typeName(var) == type)
#define REQUIRED_PARAMS(number)			if ((count _this) < number) exitWith {ERROR("A script was not passed its required parameters. Params = " + str(_this))}
#define ASSERT_PASSED_ARRAY				if (typeName(_this) != typeName([])) then {_this = [_this]}
#define ASSERT_VARIABLE(var1,message)	if (isNil QUOTE(var1)) exitWith {ERROR(message); hint message;}
#define PARAM_DEFAULT(index,dft)		if ((count _this) > index) then {_this select index} else {dft}

///////////////////////////
/* Addon-Specific Macros */
///////////////////////////

#define ASSERT_EXTENSION_LOADED			ASSERT_VARIABLE(GVARMAIN(extension_loaded),"Naught.Net extension (Naught.Net.dll) not loaded! Cannot execute function.")

////////////////
/* Pseudonyms */
////////////////

#define PREPCOMMON(var1)				PREPMAIN(var1)
#define COMMONFUNC(var1)				FUNCMAIN(var1)
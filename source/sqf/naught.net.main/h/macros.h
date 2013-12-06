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

//////////////////
/* Basic Macros */
//////////////////

#define QUOTE(var1) #var1
#define DOUBLES(var1,var2) ##var1##_##var2
#define TRIPLES(var1,var2,var3) ##var1##_##var2##_##var3
#define QUADS(var1,var2,var3,var4) ##var1##_##var2##_##var3##_##var4

//////////////////////
/* Directory Macros */
//////////////////////

#define LOADFILE(path) (loadFile path)
#define PREPROCESS(path) (preProcessFile path)
#define PREPROCESSLN(path) (preProcessFileLineNumbers path)

#define COMPILE(path) (compile PREPROCESSLN(path))
#define CALL_FILE(path) call COMPILE(path)
#define SPAWN_FILE(path) spawn COMPILE(path)

///////////////////
/* Custom Macros */
///////////////////

#define IS_TYPE(var,type) (typeName(var) == type)

#define PARAM_DEFAULT(index,dft) if ((count _this) > index) then {_this select index} else {dft}

#define ASSERT_THIS if (isNil "_this") then {_this = []}
#define ASSERT_PASSED_ARRAY if (typeName(_this) != "ARRAY") then {_this = [_this]}

// These will actually error-out of the script
#define ASSERT_VARIABLE(var1,message) if (isNil QUOTE(var1)) exitWith {ERROR(message); hint message;}
#define ASSERT_REQUIRED_PARAMS(number) if ((count _this) < number) exitWith {ERROR("A script was not passed its required parameters. Params = " + str(_this))}

////////////////
/* CBA Macros */
////////////////

/* -------------------------------------------
Group: Debugging
------------------------------------------- */

#define LOG_FUNCTION BIS_fnc_logFormat

/* -------------------------------------------
Macros: DEBUG_MODE_x
	Managing debugging based on debug level.

	According to the *highest* level of debugging that has been defined *before* script_macros_common.hpp is included,
	only the appropriate debugging commands will be functional. With no level explicitely defined, assume DEBUG_MODE_NORMAL.

	DEBUG_MODE_FULL - Full debugging output.
	DEBUG_MODE_NORMAL - All debugging except <TRACE_n()> and <LOG()> (Default setting if none specified).
	DEBUG_MODE_MINIMAL - Only <ERROR()> and <ERROR_WITH_TITLE()> enabled.

Examples:
	In order to turn on full debugging for a single file,
	(begin example)
		// Top of individual script file.
		#define DEBUG_MODE_FULL
		#include "script_component.hpp"
	(end)

	In order to force minimal debugging for a single component,
	(begin example)
		// Top of addons\<component>\script_component.hpp
		// Ensure that any FULL and NORMAL setting from the individual files are undefined and MINIMAL is set.
		#ifdef DEBUG_MODE_FULL
		#undef DEBUG_MODE_FULL
		#endif
		#ifdef DEBUG_MODE_NORMAL
		#undef DEBUG_MODE_NORMAL
		#endif
		#ifndef DEBUG_MODE_MINIMAL
		#define DEBUG_MODE_MINIMAL
		#endif
		#include "script_macros.hpp"
	(end)

	In order to turn on full debugging for a whole addon,
	(begin example)
		// Top of addons\main\script_macros.hpp
		#ifndef DEBUG_MODE_FULL
		#define DEBUG_MODE_FULL
		#endif
		#include "\x\cba\addons\main\script_macros_common.hpp"
	(end)

Author:
	Spooner
------------------------------------------- */

// If DEBUG_MODE_FULL, then also enable DEBUG_MODE_NORMAL.
#ifdef DEBUG_MODE_FULL
	#define DEBUG_MODE_NORMAL
#endif

// If DEBUG_MODE_NORMAL, then also enable DEBUG_MODE_MINIMAL.
#ifdef DEBUG_MODE_NORMAL
	#define DEBUG_MODE_MINIMAL
#endif

// If no debug modes specified, use DEBUG_MODE_NORMAL (+ DEBUG_MODE_MINIMAL).
#ifndef DEBUG_MODE_MINIMAL
	#define DEBUG_MODE_NORMAL
	#define DEBUG_MODE_MINIMAL
#endif

#ifdef THIS_FILE
	#define THIS_FILE_ 'THIS_FILE'
#else
	#define THIS_FILE_ __FILE__
#endif

/* -------------------------------------------
Macro: LOG()
	Log a timestamped message into the RPT log.

	Only run if <DEBUG_MODE_FULL> or higher is defined.

Parameters:
	MESSAGE - Message to record [String]

Example:
	(begin example)
		LOG("Initiated clog-dancing simulator.");
	(end)

Author:
	Spooner
------------------------------------------- */
#ifdef DEBUG_MODE_FULL
	#define LOG(MESSAGE) ([MESSAGE, THIS_FILE_, __LINE__] call LOG_FUNCTION)
#else
	#define LOG(MESSAGE) // disabled
#endif

/* -------------------------------------------
Macro: WARNING()
	Record a timestamped, non-critical error in the RPT log.

	Only run if <DEBUG_MODE_NORMAL> or higher is defined.

Parameters:
	MESSAGE - Message to record [String]

Example:
	(begin example)
		WARNING("This function has been deprecated. Please don't use it in future!");
	(end)

Author:
	Spooner
------------------------------------------- */
#ifdef DEBUG_MODE_NORMAL
	#define WARNING(MESSAGE) ([('WARNING: ' + MESSAGE), THIS_FILE_, __LINE__] call LOG_FUNCTION)
#else
	#define WARNING(MESSAGE) // disabled
#endif

/* -------------------------------------------
Macro: ERROR()
	Record a timestamped, critical error in the RPT log.

	The heading is "ERROR" (use <ERROR_WITH_TITLE()> for a specific title).

	TODO: Popup an error dialog & throw an exception.

Parameters:
	MESSAGE -  Message to record [String]

Example:
	(begin example)
		ERROR("Value not found","value of frog not found in config ...yada...yada...");
	(end)

Author:
	Spooner
------------------------------------------- */
#define ERROR(MESSAGE) \
	([('ERROR: ' + MESSAGE), THIS_FILE_, __LINE__] call LOG_FUNCTION)

/* -------------------------------------------
Macro: ERROR_WITH_TITLE()
	Record a timestamped, critical error in the RPT log.

	The title can be specified (in <ERROR()> the heading is always just "ERROR")
	Newlines (\n) in the MESSAGE will be put on separate lines.

	TODO: Popup an error dialog & throw an exception.

Parameters:
	TITLE - Title of error message [String]
	MESSAGE -  Body of error message [String]

Example:
	(begin example)
		ERROR_WITH_TITLE("Value not found","Value of frog not found in config ...yada...yada...");
	(end)

Author:
	Spooner
------------------------------------------- */
#define ERROR_WITH_TITLE(TITLE,MESSAGE) \
	([(TITLE + ': ' + MESSAGE), THIS_FILE_, __LINE__] call LOG_FUNCTION)

/* -------------------------------------------
Macros: TRACE_n()
	Log a message and 1-8 variables to the RPT log.

	Only run if <DEBUG_MODE_FULL> is defined.

	TRACE_1(MESSAGE,A) - Log 1 variable.
	TRACE_2(MESSAGE,A,B) - Log 2 variables.
	TRACE_3(MESSAGE,A,B,C) - Log 3 variables.
	TRACE_4(MESSAGE,A,B,C,D) - Log 4 variables.
	TRACE_5(MESSAGE,A,B,C,D,E) - Log 5 variables.
	TRACE_6(MESSAGE,A,B,C,D,E,F) - Log 6 variables.
	TRACE_7(MESSAGE,A,B,C,D,E,F,G) - Log 7 variables.
	TRACE_8(MESSAGE,A,B,C,D,E,F,G,H) - Log 8 variables.
	TRACE_9(MESSAGE,A,B,C,D,E,F,G,H,I) - Log 9 variables.

Parameters:
	MESSAGE -  Message to add to the trace [String]
	A..H - Variable names to log values of [Any]

Example:
	(begin example)
		TRACE_3("After takeoff",_vehicle player,getPos (_vehicle player), getPosASL (_vehicle player));
	(end)

Author:
	Spooner
------------------------------------------- */
#ifdef DEBUG_MODE_FULL

#define TRACE_1(MESSAGE,A) \
	([(MESSAGE + ': A=%3'), THIS_FILE_, __LINE__, A] call LOG_FUNCTION)

#define TRACE_2(MESSAGE,A,B) \
	([(MESSAGE + ': A=%3, B=%4'), THIS_FILE_, __LINE__, A,B] call LOG_FUNCTION)

#define TRACE_3(MESSAGE,A,B,C) \
	([(MESSAGE + ': A=%3, B=%4, C=%5'), THIS_FILE_, __LINE__, A,B,C] call LOG_FUNCTION)

#define TRACE_4(MESSAGE,A,B,C,D) \
	([(MESSAGE + ': A=%3, B=%4, C=%5, D=%6'), THIS_FILE_, __LINE__, A,B,C,D] call LOG_FUNCTION)

#define TRACE_5(MESSAGE,A,B,C,D,E) \
	([(MESSAGE + ': A=%3, B=%4, C=%5, D=%6, E=%7'), THIS_FILE_, __LINE__, A,B,C,D,E] call LOG_FUNCTION)

#define TRACE_6(MESSAGE,A,B,C,D,E,F) \
	([(MESSAGE + ': A=%3, B=%4, C=%5, D=%6, E=%7, F=%8'), THIS_FILE_, __LINE__, A,B,C,D,E,F] call LOG_FUNCTION)

#define TRACE_7(MESSAGE,A,B,C,D,E,F,G) \
	([(MESSAGE + ': A=%3, B=%4, C=%5, D=%6, E=%7, F=%8, G=%9'), THIS_FILE_, __LINE__, A,B,C,D,E,F,G] call LOG_FUNCTION)

#define TRACE_8(MESSAGE,A,B,C,D,E,F,G,H) \
	([(MESSAGE + ': A=%3, B=%4, C=%5, D=%6, E=%7, F=%8, G=%9, H=%10'), THIS_FILE_, __LINE__, A,B,C,D,E,F,G,H] call LOG_FUNCTION)

#define TRACE_9(MESSAGE,A,B,C,D,E,F,G,H,I) \
	([(MESSAGE + ': A=%3, B=%4, C=%5, D=%6, E=%7, F=%8, G=%9, H=%10, I=%11'), THIS_FILE_, __LINE__, A,B,C,D,E,F,G,H,I] call LOG_FUNCTION)

#else

#define TRACE_1(MESSAGE,A) // disabled
#define TRACE_2(MESSAGE,A,B) // disabled
#define TRACE_3(MESSAGE,A,B,C) // disabled
#define TRACE_4(MESSAGE,A,B,C,D) // disabled
#define TRACE_5(MESSAGE,A,B,C,D,E) // disabled
#define TRACE_6(MESSAGE,A,B,C,D,E,F) // disabled
#define TRACE_7(MESSAGE,A,B,C,D,E,F,G) // disabled
#define TRACE_8(MESSAGE,A,B,C,D,E,F,G,H) // disabled
#define TRACE_9(MESSAGE,A,B,C,D,E,F,G,H,I) // disabled

#endif

/* -------------------------------------------
Group: General
------------------------------------------- */

/* -------------------------------------------
Macro: INC()

Description:
	Increase a number by one.

Parameters:
	VAR - Variable to increment [Number]

Example:
	(begin example)
	_counter = 0;
	INC(_counter);
	// _counter => 1
	(end)

Author:
	Spooner
------------------------------------------- */
#define INC(var) (var = (var) + 1)

/* -------------------------------------------
Macro: DEC()

Description:
	Decrease a number by one.

Parameters:
	VAR - Variable to decrement [Number]

Example:
	(begin example)
	_counter = 99;
	DEC(_counter);
	// _counter => 98
	(end)

Author:
	Spooner
------------------------------------------- */
#define DEC(var) (var = (var) - 1)

/* -------------------------------------------
Macro: ADD()

Description:
	Add a value to a variable. Variable and value should be both Numbers or both Strings.

Parameters:
	VAR - Variable to add to [Number or String]
	VALUE - Value to add [Number or String]

Examples:
	(begin example)
		_counter = 2;
		ADD(_counter,3);
		// _counter => 5
	(end)
	(begin example)
		_str = "hello";
		ADD(_str," ");
		ADD(_str,"Fred");
		// _str => "hello Fred"
	(end)

Author:
	Sickboy
------------------------------------------- */
#define ADD(var1,var2) (var1 = (var1) + (var2))

/* -------------------------------------------
Macro: SUB()

Description:
	Subtract a value from a number variable. VAR and VALUE should both be Numbers.

Parameters:
	VAR - Variable to subtract from [Number]
	VALUE - Value to subtract [Number]

Examples:
	(begin example)
		_numChickens = 2;
		SUB(_numChickens,3);
		// _numChickens => -1
	(end)
------------------------------------------- */
#define SUB(var1,var2) (var1 = (var1) - (var2))

/* -------------------------------------------
Macro: REM()

Description:
	Remove an element from an array each time it occurs.

	This recreates the entire array, so use BIS_fnc_removeIndex if modification of the original array is required
	or if only one of the elements that matches ELEMENT needs to be removed.

Parameters:
	ARRAY - Array to modify [Array]
	ELEMENT - Element to remove [Any]

Examples:
	(begin example)
		_array = [1, 2, 3, 4, 3, 8];
		REM(_array,3);
		// _array = [1, 2, 4, 8];
	(end)

Author:
	Spooner
------------------------------------------- */
#define REM(var1,var2) SUB(var1,[var2])

/* -------------------------------------------
Macro: PUSH()

Description:
	Appends a single value onto the end of an ARRAY. Change is made to the ARRAY itself, not creating a new array.

Parameters:
	ARRAY - Array to push element onto [Array]
	ELEMENT - Element to push [Any]

Examples:
	(begin example)
		_fish = ["blue", "green", "smelly"];
		PUSH(_fish,"monkey-flavoured");
		// _fish => ["blue", "green", "smelly", "monkey-flavoured"]
	(end)

Author:
	Spooner
------------------------------------------- */
#define PUSH(var1,var2) (var1 set [(count var1), var2])

/* -------------------------------------------
Macro: RETNIL()
	If a variable is undefined, return the value nil. Otherwise, return the
	variable itself.

Parameters:
	VARIABLE - the variable to check

Example:
	(begin example)
		// _var is undefined
		hintSilent format ["_var=%1", RETNIL(_var) ]; // "_var=any"
	(end example)

Author:
	Alef (see CBA issue #8514)
------------------------------------------- */
#define RETNIL(VARIABLE) (if (isNil{VARIABLE}) then {nil} else {VARIABLE})

/* -------------------------------------------
Macro: ISNILS()

Description:
	Sets a variable with a value, but only if it is undefined.

Parameters:
	VARIABLE - Variable to set [Any, not nil]
	DEFAULT_VALUE - Value to set VARIABLE to if it is undefined [Any, not nil]

Examples:
	(begin example)
		// _fish is undefined
		ISNILS(_fish,0);
		// _fish => 0
	(end)
	(begin example)
		_fish = 12;
		// ...later...
		ISNILS(_fish,0);
		// _fish => 12
	(end)

Author:
	Sickboy
------------------------------------------- */
#define ISNILS(VARIABLE,DEFAULT_VALUE) (if (isNil #VARIABLE) then { ##VARIABLE = ##DEFAULT_VALUE })

/* -------------------------------------------
Macros: ARG_#()
	Select from list of array arguments

Parameters:
	VARIABLE(1-8) - elements for the list

Author:
	Rommel
------------------------------------------- */
#define ARG_1(A,B) ((A) select (B))
#define ARG_2(A,B,C) (ARG_1(ARG_1(A,B),C))
#define ARG_3(A,B,C,D) (ARG_1(ARG_2(A,B,C),D))
#define ARG_4(A,B,C,D,E) (ARG_1(ARG_3(A,B,C,D),E))
#define ARG_5(A,B,C,D,E,F) (ARG_1(ARG_4(A,B,C,D,E),F))
#define ARG_6(A,B,C,D,E,F,G) (ARG_1(ARG_5(A,B,C,D,E,F),G))
#define ARG_7(A,B,C,D,E,F,G,H) (ARG_1(ARG_6(A,B,C,D,E,E,F,G),H))
#define ARG_8(A,B,C,D,E,F,G,H,I) (ARG_1(ARG_7(A,B,C,D,E,E,F,G,H),I))

/* -------------------------------------------
Macros: IS_x()
	Checking the data types of variables.

	IS_ARRAY() - Array
	IS_BOOL() - Boolean
	IS_BOOLEAN() - UI display handle(synonym for <IS_BOOL()>)
	IS_CODE() - Code block (i.e a compiled function)
	IS_CONFIG() - Configuration
	IS_CONTROL() - UI control handle.
	IS_DISPLAY() - UI display handle.
	IS_FUNCTION() - A compiled function (synonym for <IS_CODE()>)
	IS_GROUP() - Group.
	IS_INTEGER() - Is a number a whole number?
	IS_LOCATION() - World location.
	IS_NUMBER() - A floating point number (synonym for <IS_SCALAR()>)
	IS_OBJECT() - World object.
	IS_SCALAR() - Floating point number.
	IS_SCRIPT() - A script handle (as returned by execVM and spawn commands).
	IS_SIDE() - Game side.
	IS_STRING() - World object.
	IS_TEXT() - Structured text.

Parameters:
	VARIABLE - Variable to check if it is of a particular type [Any, not nil]

Author:
	Spooner
------------------------------------------- */
#define IS_META_SYS(VAR,TYPE) (if (isNil {VAR}) then { false } else { (typeName (VAR)) == TYPE })
#define IS_ARRAY(VAR)    IS_META_SYS(VAR,"ARRAY")
#define IS_BOOL(VAR)     IS_META_SYS(VAR,"BOOL")
#define IS_CODE(VAR)     IS_META_SYS(VAR,"CODE")
#define IS_CONFIG(VAR)   IS_META_SYS(VAR,"CONFIG")
#define IS_CONTROL(VAR)  IS_META_SYS(VAR,"CONTROL")
#define IS_DISPLAY(VAR)  IS_META_SYS(VAR,"DISPLAY")
#define IS_GROUP(VAR)    IS_META_SYS(VAR,"GROUP")
#define IS_OBJECT(VAR)   IS_META_SYS(VAR,"OBJECT")
#define IS_SCALAR(VAR)   IS_META_SYS(VAR,"SCALAR")
#define IS_SCRIPT(VAR)   IS_META_SYS(VAR,"SCRIPT")
#define IS_SIDE(VAR)     IS_META_SYS(VAR,"SIDE")
#define IS_STRING(VAR)   IS_META_SYS(VAR,"STRING")
#define IS_TEXT(VAR)     IS_META_SYS(VAR,"TEXT")
#define IS_LOCATION(VAR) IS_META_SYS(VAR,"LOCATION")

// Pseudonyms
#define IS_BOOLEAN(VAR)  IS_BOOL(VAR)
#define IS_FUNCTION(VAR) IS_CODE(VAR)
#define IS_INTEGER(VAR)  (if ( IS_SCALAR(VAR) ) then { (floor(VAR) == (VAR)) } else { false })
#define IS_NUMBER(VAR)   IS_SCALAR(VAR)

/* -------------------------------------------
Macros: EXPLODE_n()
	Splitting an ARRAY into a number of variables (A, B, C, etc).

	Note that this NOT does make the created variables private.
	_PVT variants do.

	EXPLODE_1(ARRAY,A,B) - Split a 1-element array into separate variable.
	EXPLODE_2(ARRAY,A,B) - Split a 2-element array into separate variables.
	EXPLODE_3(ARRAY,A,B,C) - Split a 3-element array into separate variables.
	EXPLODE_4(ARRAY,A,B,C,D) - Split a 4-element array into separate variables.
	EXPLODE_5(ARRAY,A,B,C,D,E) - Split a 5-element array into separate variables.
	EXPLODE_6(ARRAY,A,B,C,D,E,F) - Split a 6-element array into separate variables.
	EXPLODE_7(ARRAY,A,B,C,D,E,F,G) - Split a 7-element array into separate variables.
	EXPLODE_8(ARRAY,A,B,C,D,E,F,G,H) - Split a 8-element array into separate variables.
	EXPLODE_9(ARRAY,A,B,C,D,E,F,G,H,I) - Split a 9-element array into separate variables.

Parameters:
	ARRAY - Array to read from [Array]
	A..H - Names of variables to set from array [Identifier]

Example:
	(begin example)
		_array = ["fred", 156.8, 120.9];
		EXPLODE_3(_array,_name_height,_weight);
	(end)

Author:
	Spooner
------------------------------------------- */
#define EXPLODE_1_SYS(ARRAY,A) A = if (IS_ARRAY((ARRAY))) then { (ARRAY) select 0 } else { ARRAY }
#define EXPLODE_1(ARRAY,A) EXPLODE_1_SYS(ARRAY,A); TRACE_1("EXPLODE_1, " + QUOTE(ARRAY),A)
#define EXPLODE_1_PVT(ARRAY,A) \
	private #A; \
	EXPLODE_1(ARRAY,A)

#define EXPLODE_2_SYS(ARRAY,A,B) EXPLODE_1_SYS(ARRAY,A); B = (ARRAY) select 1
#define EXPLODE_2(ARRAY,A,B) EXPLODE_2_SYS(ARRAY,A,B); TRACE_2("EXPLODE_2, " + QUOTE(ARRAY),A,B)
#define EXPLODE_2_PVT(ARRAY,A,B) \
	private [#A,#B]; \
	EXPLODE_2(ARRAY,A,B)

#define EXPLODE_3_SYS(ARRAY,A,B,C) EXPLODE_2_SYS(ARRAY,A,B); C = (ARRAY) select 2
#define EXPLODE_3(ARRAY,A,B,C) EXPLODE_3_SYS(ARRAY,A,B,C); TRACE_3("EXPLODE_3, " + QUOTE(ARRAY),A,B,C)
#define EXPLODE_3_PVT(ARRAY,A,B,C) \
	private [#A,#B,#C]; \
	EXPLODE_3(ARRAY,A,B,C)
	
#define EXPLODE_4_SYS(ARRAY,A,B,C,D) EXPLODE_3_SYS(ARRAY,A,B,C); D = (ARRAY) select 3
#define EXPLODE_4(ARRAY,A,B,C,D) EXPLODE_4_SYS(ARRAY,A,B,C,D); TRACE_4("EXPLODE_4, " + QUOTE(ARRAY),A,B,C,D)
#define EXPLODE_4_PVT(ARRAY,A,B,C,D) \
	private [#A,#B,#C,#D]; \
	EXPLODE_4(ARRAY,A,B,C,D)

#define EXPLODE_5_SYS(ARRAY,A,B,C,D,E) EXPLODE_4_SYS(ARRAY,A,B,C,D); E = (ARRAY) select 4
#define EXPLODE_5(ARRAY,A,B,C,D,E) EXPLODE_5_SYS(ARRAY,A,B,C,D,E); TRACE_5("EXPLODE_5, " + QUOTE(ARRAY),A,B,C,D,E)
#define EXPLODE_5_PVT(ARRAY,A,B,C,D,E) \
	private [#A,#B,#C,#D,#E]; \
	EXPLODE_5(ARRAY,A,B,C,D,E)

#define EXPLODE_6_SYS(ARRAY,A,B,C,D,E,F) EXPLODE_5_SYS(ARRAY,A,B,C,D,E); F = (ARRAY) select 5
#define EXPLODE_6(ARRAY,A,B,C,D,E,F) EXPLODE_6_SYS(ARRAY,A,B,C,D,E,F); TRACE_6("EXPLODE_6, " + QUOTE(ARRAY),A,B,C,D,E,F)
#define EXPLODE_6_PVT(ARRAY,A,B,C,D,E,F) \
	private [#A,#B,#C,#D,#E,#F]; \
	EXPLODE_6(ARRAY,A,B,C,D,E,F)

#define EXPLODE_7_SYS(ARRAY,A,B,C,D,E,F,G) EXPLODE_6_SYS(ARRAY,A,B,C,D,E,F); G = (ARRAY) select 6
#define EXPLODE_7(ARRAY,A,B,C,D,E,F,G) EXPLODE_7_SYS(ARRAY,A,B,C,D,E,F,G); TRACE_7("EXPLODE_7, " + QUOTE(ARRAY),A,B,C,D,E,F,G)
#define EXPLODE_7_PVT(ARRAY,A,B,C,D,E,F,G) \
	private [#A,#B,#C,#D,#E,#F,#G]; \
	EXPLODE_7(ARRAY,A,B,C,D,E,F,G)

#define EXPLODE_8_SYS(ARRAY,A,B,C,D,E,F,G,H) EXPLODE_7_SYS(ARRAY,A,B,C,D,E,F,G); H = (ARRAY) select 7
#define EXPLODE_8(ARRAY,A,B,C,D,E,F,G,H) EXPLODE_8_SYS(ARRAY,A,B,C,D,E,F,G,H); TRACE_8("EXPLODE_8, " + QUOTE(ARRAY),A,B,C,D,E,F,G,H)
#define EXPLODE_8_PVT(ARRAY,A,B,C,D,E,F,G,H) \
	private [#A,#B,#C,#D,#E,#F,#G,#H]; \
	EXPLODE_8(ARRAY,A,B,C,D,E,F,G,H)

#define EXPLODE_9_SYS(ARRAY,A,B,C,D,E,F,G,H,I) EXPLODE_8_SYS(ARRAY,A,B,C,D,E,F,G,H); I = (ARRAY) select 8
#define EXPLODE_9(ARRAY,A,B,C,D,E,F,G,H,I) EXPLODE_9_SYS(ARRAY,A,B,C,D,E,F,G,H,I); TRACE_9("EXPLODE_9, " + QUOTE(ARRAY),A,B,C,D,E,F,G,H,I)
#define EXPLODE_9_PVT(ARRAY,A,B,C,D,E,F,G,H,I) \
	private [#A,#B,#C,#D,#E,#F,#G,#H,#I]; \
	EXPLODE_9(ARRAY,A,B,C,D,E,F,G,H,I)

/* -------------------------------------------
Macros: PARAMS_n()
	Setting variables based on parameters passed to a function.

	Each parameter is defines as private and set to the appropriate value from _this.

	PARAMS_1(A) - Get 1 parameter from the _this array (or _this if it's not an array).
	PARAMS_2(A,B) - Get 2 parameters from the _this array.
	PARAMS_3(A,B,C) - Get 3 parameters from the _this array.
	PARAMS_4(A,B,C,D) - Get 4 parameters from the _this array.
	PARAMS_5(A,B,C,D,E) - Get 5 parameters from the _this array.
	PARAMS_6(A,B,C,D,E,F) - Get 6 parameters from the _this array.
	PARAMS_7(A,B,C,D,E,F,G) - Get 7 parameters from the _this array.
	PARAMS_8(A,B,C,D,E,F,G,H) - Get 8 parameters from the _this array.

Parameters:
	A..H - Name of variable to read from _this [Identifier]

Example:
	A function called like this:
	(begin example)
		[_name,_address,_telephone] call recordPersonalDetails;
	(end)
	expects 3 parameters and those variables could be initialised at the start of the function definition with:
	(begin example)
		recordPersonalDetails = {
			PARAMS_3(_name,_address,_telephone);
			// Rest of function follows...
		};
	(end)

Author:
	Spooner
------------------------------------------- */
#define PARAMS_1(A) EXPLODE_1_PVT(_this,A)
#define PARAMS_2(A,B) EXPLODE_2_PVT(_this,A,B)
#define PARAMS_3(A,B,C) EXPLODE_3_PVT(_this,A,B,C)
#define PARAMS_4(A,B,C,D) EXPLODE_4_PVT(_this,A,B,C,D)
#define PARAMS_5(A,B,C,D,E) EXPLODE_5_PVT(_this,A,B,C,D,E)
#define PARAMS_6(A,B,C,D,E,F) EXPLODE_6_PVT(_this,A,B,C,D,E,F)
#define PARAMS_7(A,B,C,D,E,F,G) EXPLODE_7_PVT(_this,A,B,C,D,E,F,G)
#define PARAMS_8(A,B,C,D,E,F,G,H) EXPLODE_8_PVT(_this,A,B,C,D,E,F,G,H)
#define PARAMS_9(A,B,C,D,E,F,G,H,I) EXPLODE_9_PVT(_this,A,B,C,D,E,F,G,H,I)

/* -------------------------------------------
Group: Assertions
------------------------------------------- */

#define ASSERTION_ERROR(MESSAGE) ERROR_WITH_TITLE("Assertion failed!",MESSAGE)

/* -------------------------------------------
Macro: ASSERT_TRUE()
	Asserts that a CONDITION is true. When an assertion fails, an error is raised with the given MESSAGE.

Parameters:
	CONDITION - Condition to assert as true [Boolean]
	MESSSAGE - Message to display if (A OPERATOR B) is false [String]

Example:
	(begin example)
		ASSERT_TRUE(_frogIsDead,"The frog is alive");
	(end)

Author:
	Spooner
------------------------------------------- */
#define ASSERT_TRUE(CONDITION,MESSAGE) \
	if (not (CONDITION)) then \
	{ \
		ASSERTION_ERROR('Assertion (CONDITION) failed!\n\n' + (MESSAGE)); \
	}

/* -------------------------------------------
Macro: ASSERT_FALSE()
	Asserts that a CONDITION is false. When an assertion fails, an error is raised with the given MESSAGE.

Parameters:
	CONDITION - Condition to assert as false [Boolean]
	MESSSAGE - Message to display if (A OPERATOR B) is true [String]

Example:
	(begin example)
		ASSERT_FALSE(_frogIsDead,"The frog died");
	(end)

Author:
	Spooner
------------------------------------------- */
#define ASSERT_FALSE(CONDITION,MESSAGE) \
	if (CONDITION) then \
	{ \
		ASSERTION_ERROR('Assertion (not (CONDITION)) failed!\n\n' + (MESSAGE)) \
	}

/* -------------------------------------------
Macro: ASSERT_OP()
	Asserts that (A OPERATOR B) is true. When an assertion fails, an error is raised with the given MESSAGE.

Parameters:
	A - First value [Any]
	OPERATOR - Binary operator to use [Operator]
	B - Second value [Any]
	MESSSAGE - Message to display if (A OPERATOR B)  is false. [String]

Example:
	(begin example)
		ASSERT_OP(_fish,>,5,"Too few fish!");
	(end)

Author:
	Spooner
------------------------------------------- */
#define ASSERT_OP(A,OPERATOR,B,MESSAGE) \
	if (not ((A) OPERATOR (B))) then \
	{ \
		ASSERTION_ERROR('Assertion (A OPERATOR B) failed!\n' + 'A: ' + (str (A)) + '\n' + 'B: ' + (str (B)) + "\n\n" + (MESSAGE)); \
	}

/* -------------------------------------------
Macro: ASSERT_DEFINED()
	Asserts that a VARIABLE is defined. When an assertion fails, an error is raised with the given MESSAGE..

Parameters:
	VARIABLE - Variable to test if defined [String or Function].
	MESSAGE - Message to display if variable is undefined [String].

Examples:
	(begin example)
		ASSERT_DEFINED("_anUndefinedVar","Too few fish!");
		ASSERT_DEFINED({ obj getVariable "anUndefinedVar" },"Too many fish!");
	(end)

Author:
	Spooner
------------------------------------------- */
#define ASSERT_DEFINED(VARIABLE,MESSAGE) \
	if (isNil VARIABLE) then \
	{ \
		ASSERTION_ERROR('Assertion (VARIABLE is defined) failed!\n\n' + (MESSAGE)); \
	}

/* -------------------------------------------
Group: Managing Deprecation
------------------------------------------- */

/* -------------------------------------------
Macro: DEPRECATE_SYS()
	Allow deprecation of a function that has been renamed.

	Replaces an old OLD_FUNCTION (which will have PREFIX_ prepended) with a NEW_FUNCTION
	(PREFIX_ prepended) with the intention that the old function will be disabled in the future.

	Shows a warning in RPT each time the deprecated function is used, but runs the new function.

Parameters:
	OLD_FUNCTION - Full name of old function [Identifier for function that does not exist any more]
	NEW_FUNCTION - Full name of new function [Function]

Example:
	(begin example)
		// After renaming CBA_fnc_frog as CBA_fnc_fish
		DEPRECATE_SYS(CBA_fnc_frog,CBA_fnc_fish);
	(end)

Author:
	Sickboy
------------------------------------------- */
#define DEPRECATE_SYS(OLD_FUNCTION,NEW_FUNCTION) \
	OLD_FUNCTION = { \
		WARNING('Deprecated function used: OLD_FUNCTION (new: NEW_FUNCTION) in THIS_FILE_'); \
		if (isNil "_this") then { call NEW_FUNCTION } else { _this call NEW_FUNCTION }; \
	}

/* -------------------------------------------
Macro: DEPRECATE()
	Allow deprecation of a function, in the current component, that has been renamed.

	Replaces an OLD_FUNCTION (which will have PREFIX_ prepended) with a NEW_FUNCTION
	(PREFIX_ prepended) with the intention that the old function will be disabled in the future.

	Shows a warning in RPT each time the deprecated function is used, but runs the new function.

Parameters:
	OLD_FUNCTION - Name of old function, assuming PREFIX [Identifier for function that does not exist any more]
	NEW_FUNCTION - Name of new function, assuming PREFIX [Function]

Example:
	(begin example)
		// After renaming CBA_fnc_frog as CBA_fnc_fish
		DEPRECATE(fnc_frog,fnc_fish);
	(end)

Author:
	Sickboy
------------------------------------------- */
#define DEPRECATE(OLD_FUNCTION,NEW_FUNCTION) \
	DEPRECATE_SYS(DOUBLES(PREFIX,OLD_FUNCTION),DOUBLES(PREFIX,NEW_FUNCTION))

/* -------------------------------------------
Macro: OBSOLETE_SYS()
	Replace a function that has become obsolete.

	Replace an obsolete OLD_FUNCTION with a simple COMMAND_FUNCTION, with the intention that anyone
	using the function should replace it with the simple command, since the function will be disabled in the future.

	Shows a warning in RPT each time the deprecated function is used, and runs the command function.

Parameters:
	OLD_FUNCTION - Full name of old function [Identifier for function that does not exist any more]
	COMMAND_CODE - Code to replace the old function [Function]

Example:
	(begin example)
		// In Arma2, currentWeapon command made the CBA_fMyWeapon function obsolete:
		OBSOLETE_SYS(CBA_fMyWeapon,{ currentWeapon player });
	(end)

Author:
	Spooner
------------------------------------------- */
#define OBSOLETE_SYS(OLD_FUNCTION,COMMAND_CODE) \
	OLD_FUNCTION = { \
		WARNING('Obsolete function used: (use: OLD_FUNCTION) in THIS_FILE_'); \
		if (isNil "_this") then { call COMMAND_CODE } else { _this call COMMAND_CODE }; \
	}

/* -------------------------------------------
Macro: OBSOLETE()
	Replace a function, in the current component, that has become obsolete.

	Replace an obsolete OLD_FUNCTION (which will have PREFIX_ prepended) with a simple
	COMMAND_CODE, with the intention that anyone using the function should replace it with the simple
	command.

	Shows a warning in RPT each time the deprecated function is used.

Parameters:
	OLD_FUNCTION - Name of old function, assuming PREFIX [Identifier for function that does not exist any more]
	COMMAND_CODE - Code to replace the old function [Function]

Example:
	(begin example)
		// In Arma2, currentWeapon command made the CBA_fMyWeapon function obsolete:
		OBSOLETE(fMyWeapon,{ currentWeapon player });
	(end)

Author:
	Spooner
------------------------------------------- */
#define OBSOLETE(OLD_FUNCTION,COMMAND_CODE) \
	OBSOLETE_SYS(DOUBLES(PREFIX,OLD_FUNCTION),COMMAND_CODE)
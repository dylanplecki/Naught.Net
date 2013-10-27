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

///////////////////////////
/* General Addon Options */
///////////////////////////

#define MAINPREFIX x
#define SUBPREFIX addons
#define PREFIX NDT
#define	PREFIX_DIR Naught.Net
#define	PREFIX_CAT naught.net

////////////////
/* Versioning */
////////////////

#define PRODUCTION_ENVIRONMENT

#define PLATFORM Windows

#define MAJOR 1
#define MINOR 0
#define PATCHLVL 1
#define BUILD 1

#define VERSION MAJOR.MINOR.PATCHLVL.BUILD
#define VERSION_AR MAJOR,MINOR,PATCHLVL,BUILD

#define REQUIRED_VERSION 1.0

//////////////////////////////////
/* Naught.Net Extension Options */
//////////////////////////////////

#define EXTENSION_NAME		"Naught.Net"

#define FUNC_DELIMETER		"#"
#define PARAM_DELIMETER		"~"
#define RETURN_GENERIC		"#!"

#define RETURN_ERROR		(RETURN_GENERIC + "NAUGHT_NET_ERROR")
#define RETURN_TRUNCATED	(RETURN_GENERIC + "NAUGHT_NET_TRUNC")
#define RETURN_HANDLE		(RETURN_GENERIC + "NAUGHT_NET_HANDL")
#define RETURN_NULL			(RETURN_GENERIC + "NAUGHT_NET__NULL")

//////////////////
/* Debug Levels */
//////////////////

#define DEBUG_LEVEL_NONE		0	// None
#define DEBUG_LEVEL_CRIT		1	// Critical
#define DEBUG_LEVEL_ERROR		2	// Error
#define DEBUG_LEVEL_WARN		4	// Warning
#define DEBUG_LEVEL_NOTICE		8	// Notice
#define DEBUG_LEVEL_INFO		16	// Info
#define DEBUG_LEVEL_ALL			31	// All

#ifdef PRODUCTION_ENVIRONMENT
	#define DEBUG_LEVEL_DEFAULT		(DEBUG_LEVEL_ALL - DEBUG_LEVEL_INFO)
#else
	#define DEBUG_LEVEL_DEFAULT		(DEBUG_LEVEL_ALL)
#endif
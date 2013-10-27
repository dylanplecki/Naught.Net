=====================================
Naught.Net
Version: 1.0.0.1
Release date: 10/7/2013
Author(s): Naught
Multiplayer compatible: Yes
=====================================

An unofficial addon for the PC game "Arma" by Bohemia Interactive.


=====================================
DESCRIPTION
=====================================

An extension-based (.dll) addon that extends the functionality of the Real Virtuality engine
with multiple features accessed via an extensive API detailed in the <FUNCTION INDEX> below.


=====================================
REQUIREMENTS
=====================================

Arma 2 - Version [1.11] - Bohemia Interactive
Arma 2: Operation Arrowhead - Version [1.62] - Bohemia Interactive
Arma 3 - Version [1.00] - Bohemia Interactive
CBA - Version b190 - CBA Team


=====================================
FUNCTION INDEX
=====================================

NOTE: All extension returns of the return data-type [Return] consist of either a string of the return data [String] on success,
an extension-internal handle [Int] on multi-threaded applications (although by using the below functions this should not be
returned), an error [Boolean false] on an extension-internal error, or a null data-type [Nil] on a null (or empty) return.
Data checks should be mandatory after a call to one of these functions.

NOTICE: All tilde (~) characters sent to the extension WILL BE REPLACED by the minus (-) character prior to the transfer.

----------------
COMMON FUNCTIONS
----------------

NDT_fnc_getVersion
	Description:
		Get version of the Naught.Net extension (Naught.Net.dll).
	Parameters:
		None
	Return:
		Version [Return] (empty string if extension is unloaded).
	Example:
		_version = [] call NDT_fnc_getVersion;

----------------
STRING FUNCTIONS
----------------

NDT_fnc_hashString
	Description:
		Hash a string. Hash Types are: 0=MD2, 1=MD4, 2=MD5, 3=SHA1, 4=SHA256.
	Parameters:
		0: Text [String],
		1: Hash Type [Integer] (Optional).
	Return:
		Hash [Return].
	Example:
		_hash = ["hash this string", 3] call NDT_fnc_hashString;

NDT_fnc_regexMatch
	Description:
		Check if text matches a given regular expression.
	Parameters:
		0: Text [String],
		1: Regex [String].
	Return:
		Encapsulated Boolean [Return] (ie. "true").
	Example:
		_encapBool = ["subject", "(sub)(.*)"] call NDT_fnc_regexMatch;

NDT_fnc_regexSearch
	Description:
		Search text for characters matching a regular expression.
	Parameters:
		0: Text [String],
		1: Regex [String],
		2: Max Iterations [Int] (Optional).
	Return:
		Encapsulated Array [Return] (ie. "[['match1'], ['subMatch1', 'subMatch2']]").
	Example:
		_encapArray = ["this subject, that submarine, every subsequence", "\\b(sub)([^ ]*)", 2] call NDT_fnc_regexSearch;

NDT_fnc_regexReplace
	Description:
		Replace all characters matching a regular expression.
	Parameters:
		0: Text [String],
		1: Regex [String],
		2: Replace With [String] (Reference http://www.cplusplus.com/reference/regex/match_replace/).
	Return:
		New Text [Return].
	Example:
		_newText = ["there is a subsequence in the string", "\\b(sub)([^ ]*)", "sub-$2"] call NDT_fnc_regexReplace;

-----------------
NETWORK FUNCTIONS
-----------------

NDT_fnc_newDownloadHandler
	Description:
		Create a new download handler to download a file and call code.
	Parameters:
		0: Address [String] ("protocol://address.domain:port"),
		1: Handler Code [Code] (Passes download return as _this [Return]),
		2: TimeOut Seconds [Int] (Optional),
		3: Post Data [String] (Optional).
	Return:
		Handle to Asynchronous (Spawned) Code [Script].
	Example:
		_scriptHandle = ["https://www.google.com", {dl_data = _this;}, 30, "request=search"] call NDT_fnc_newDownloadHandler;


=====================================
KNOWN ISSUES
=====================================

None.

 
=====================================
VERSION HISTORY
=====================================

Version 1.0.0.1
	- Initial Release
 

=====================================
LICENSE
=====================================

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


=====================================
CONTACT DETAILS
=====================================
 
Dylan Plecki (Naught) can be contacted either through the UnitedOperations.Net forums as <Naught> or via email at <dylanplecki@gmail.com>


Naught.Net
==========

An extension-based addon for the Real Virtuality Simulation Engine

==========

About Naught.Net

What is Naught.Net?
  Naught.Net is an extension-based (.dll) addon that extends the functionality of the Real Virtuality simulation engine with multiple features accessed via an extensive API.

What features does Naught.Net offer?
  Naught.Net offers many features, currently allowing for hashing (MD2, MD4, MD5, SHA1, and SHA256), regular expressions (regex-based matching, searching, and replacing), and file-downloading (this is handler-based and completely multi-threaded).

How does file-downloading in Naught.Net work?
  Naught.Net uses handle-based multithreading to download files from local and remote networks. This works by requesting a file and downloading it asynchronously from the main Arma process while the SQF engine continually asks (per-frame) the extension if the download has finished. Once done, the extension will return the file (up to 1MB in size using truncating and chunking techniques; this is the limit due to security issues, so it may be increased later) as a [perfectly safe] string to the SQF engine which will then call the supplied handler code, passing the file as the primary _this variable.

==========

Technical Specifications

- Multi-threaded handler-based support.
- Chunking and truncating for nearly unlimited inter-communication (Extension to Arma) bandwidth.
- Max concurrent threads: 10.
- Max Download bandwidth per thread: 1 MB, Max Upload bandwidth per thread: 512 KB.
- Download support for HTTP (POST & GET), HTTPS (POST & GET), FTP (untested), SSH (untested), and more.
- [ALPHA] XML string parsing to SQF array.

==========

Extended SQF-based documentation can be found in the source code (@Naught.Net\docs\README.txt) or
at the Bohemia Interactive Forums at http://forums.bistudio.com/showthread.php?166534-Naught-Net

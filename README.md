# NanoCrypt
A fast in-place file encryption tool implemented without 3rd-party libraries 

Copyright (c) 2017 [Tony Wu], All Right Reserved

License: GNU GPL v3.0

Version 0.2

This tool encrypts a specified file in-place, using RC4-drop3072 with 256-bit keys. Key stretching is provided by PBKDF2-HMAC-SHA512 with 2^18 iterations. 16 bytes of a random salt will be appended to the end of the encrypted file.

If compiled using g++ -O3, speeds exceeding 250 MB/s can be achieved on a ULV Kaby Lake i7 and SSD.

usage: NanoCryptCore file key

usage: SaltMaster flag file salt

Use NanoCrypt.py (Python3) to use this tool in an interactive manner. NanoCrypt.py derives keys, generates salts, and automatically invokes NanoCrypt's C++ sub-tools to complete the encryption process.

To use the sub-tools manually, note:

Key must be a hexadecimal string of length 64 (32-bytes/256-bit). Ensure it comes from a properly salted key derivation function. Salt must be a hexadecimal string of length 32 (16-bytes/128-bit). SaltMaster can be used to add/remove salts from newly encrypted/decrypted files. Flags are "add" or "remove".

# NanoCrypt
A fast in-place file encryption tool implemented without 3rd-party libraries 

Copyright (c) 2017 [Tony Wu], All Right Reserved

License: GNU GPL v3.0

This tool encrypts a specified file in-place, using RC4-drop3072 with 256-bit keys. If compiled using g++ -O3, speeds exceeding 250 MB/s can be achieved.

usage: NanoCryptCore file key

Key must be a hexadecimal string of length 64 (32-bytes/256-bit). Ensure it comes from a properly salted key derivation function.

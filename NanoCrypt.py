#-----------------------------------------------------------------------------
# NanoCrypt v0.1
# 
# NanoCrypt.py
# 
# Repo: https://github.com/TonyWu386/NanoCrypt
# 
# License: GNU GPL v3.0
#
# Copyright (c) 2017 [Tony Wu], All Right Reserved
#-----------------------------------------------------------------------------

from os import urandom
from hashlib import pbkdf2_hmac
from subprocess import call
from binascii import hexlify


if __name__ == "__main__":

    fileName = input("File:")

    passphrase = bytes(input("Passphrase:"), encoding="ascii")

    if (len(passphrase) < 8):
        print("Passphrase is too short")
        quit()

    salt = bytes(urandom(16))
    
    key = pbkdf2_hmac("sha512", passphrase, salt, 262144, 32)

    returnCode = call(["./NanoCryptCore", fileName, hexlify(key)])

    if (returnCode != 0):
        print("Encryption failed")
        quit()
    else:
        print("Encryption successful")
        returnCode = call(["./SaltMaster", "add", fileName, hexlify(salt)])

        if (returnCode != 0):
            print("Salt appending failed")
            quit()
        else:
            print("Salt appending successful")

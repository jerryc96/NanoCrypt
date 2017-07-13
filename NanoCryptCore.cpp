/* 
 * NanoCrypt v0.1
 * 
 * NanoCryptCore.cpp
 * 
 * Repo: https://github.com/TonyWu386/NanoCrypt
 * 
 * License: GNU GPL v3.0
 * 
 * Copyright (c) 2017 [Tony Wu], All Right Reserved
 */

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string.h>

using namespace std;

class CryptoCore
{
  private:
  array<unsigned char, 256> ksa(unsigned char * key);
  array<unsigned char, 256> mS;
  short mi;
  short mj;

  public:
  unsigned char prga();
  void printState();

  CryptoCore(unsigned char * key)
  {
    mi = 0;
    mj = 0;
    mS = ksa(key);
  }
};

array<unsigned char, 256> CryptoCore::ksa(unsigned char * key)
{
  array<unsigned char, 256> S;

  for (short i = 0; i < 256; i++)
  {
    S[i] = i;
  }

  short j = 0;
  for (short i = 0; i < 256; i++)
  {
    j = (j + S[i] + key[i % 32]) % 256;
    swap(S[i], S[j]);
  }

  return S;
}


unsigned char CryptoCore::prga()
{
  mi = (mi + 1) % 256;
  mj = (mj + mS[mi]) % 256;
  swap(mS[mi], mS[mj]);

  return mS[(mS[mi] + mS[mj]) % 256];
}


void CryptoCore::printState()
{
  cout << "[";
  for (short i = 0; i < 256; i++)
  {
    cout << (int)(mS[i]) << ",";
  }
  cout << "]" << endl;
}


int main( int argc, char *argv[])
{
  if ( argc != 3)
  {
    cout << "usage: arc4pp file key" << endl;
    return 1;
  }
  
  if (strlen(argv[2]) != 64)
  {
    cout << "key is wrong size: " << strlen(argv[2]) << endl;
    return 1;
  }

  fstream toEncrypt(argv[1], ios::binary|ios::out|ios::in|ios::ate);
  
  if (toEncrypt.fail())
  {
    cout << "cannot open file: " << argv[1] << endl;
    return 1;
  }

  unsigned char key[32];

  //Convert the key from hexstring to char array
  char *pos = argv[2];
  for(short i = 0; i < 32; i++) {
    sscanf(pos, "%2hhx", &key[i]);
    pos += 2;
  }

  CryptoCore core = CryptoCore(key);

  //Drop the first 3072-bytes to prevent FMS attacks
  for (short i = 0; i < 3072; i++)
  {
    core.prga();
  }
  
  //Start encrypting file  
  int fileSize = toEncrypt.tellg();
  int bufferSize = 4096;
  int marker = 0;

  while (marker < fileSize)
  {
    char* buffer = new char [bufferSize];
    
    toEncrypt.seekp(marker, ios::beg);
    toEncrypt.read(buffer, bufferSize);
    
    for (short i = 0; i < bufferSize; i++)
    {
      buffer[i] = buffer[i] ^ core.prga();
    }
    
    toEncrypt.seekp(marker, ios::beg);
    toEncrypt.write(buffer, bufferSize);
    
    marker += bufferSize;
    
    if ((fileSize - marker) < bufferSize)
    {
      bufferSize = fileSize - marker;
    }
  }
  
  return 0;
}

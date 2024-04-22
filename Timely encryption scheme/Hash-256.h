#ifndef HASH_256_H
#define HASH_256_H
#include <sha.h>
#include <hex.h>
#include <iostream>
#include <string>

using namespace std;
using namespace CryptoPP;

string hash_256(string message);

#endif // !HASH_256_H


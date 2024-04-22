#ifndef RSA_H
#define RSA_H
#include <cryptlib.h>
#include <rsa.h>
#include <osrng.h>
#include <files.h>
#include <filters.h>
#include <string>
#include "get_Key.h"
using namespace std;
using namespace CryptoPP;


void Generate_Key();
string RSA_encrypt(string message);
string RSA_decrypt(string message);
#endif // !RSA_H


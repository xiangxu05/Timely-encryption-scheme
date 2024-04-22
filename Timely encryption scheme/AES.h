#ifndef AES_H
#define AES_H
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <modes.h>
#include <files.h>
#include <ctime>
#include <aes.h>
#include <vector>
#include <sstream>
#include "get_Key.h"
#include "Hash-256.h"
#include "RSA.h"


using namespace std;
using namespace CryptoPP;

//Key_Information AES_encrypt(string Time, string inputFile, string encryptedFile);
string AES_encrypt(string lalontute, string range, string plainText, int endTime, int startTime = -1);
string AES_decrypt(string encryptedFile, string decryptedFile);
void deleteFile(string Filename);
#endif
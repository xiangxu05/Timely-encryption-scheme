#include "Hash-256.h"
string hash_256(string message) {
    
    SHA256 sha256;
    byte digest[SHA256::DIGESTSIZE];
    sha256.CalculateDigest(digest, (const byte*)message.c_str(), message.length());
    size_t digestSize = sizeof(digest);
    string hashString(reinterpret_cast<char*>(digest), digestSize);

	return hashString;
};
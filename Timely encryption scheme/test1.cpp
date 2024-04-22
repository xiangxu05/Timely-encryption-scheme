//#include <iostream>
//#include <fstream>
//#include <modes.h>
//#include <files.h>
//#include <aes.h>
//#include "get_Key.h"
//#include "AES.h"
//#include "Hash-256.h"
//
//using namespace std;
//using namespace CryptoPP;
//
//int main() {
//
//    string Time;
//    string inputFile = "1.txt";
//    string encryptedFile = "2.txt";
//    string decryptedFile = "3.txt";
//
//    cout << "输入要加密的期限（秒）：" << endl;
//    cin >> Time;
//
//    Key_Lifespan encryption = AES_encrypt(Time, inputFile, encryptedFile);
//    cin >> Time;
//    AES_decrypt(encryption, encryptedFile, decryptedFile);
//
//
//    return 0;
//}

#include "AES.h"
#include "random.h"

string AES_encrypt(string lalontute,string range, string plainText, int endTime, int startTime ) {
    
    //获取随机数
    string random_key = get_Random();

    //创建AES密钥
    Key_Information encryption;
    bitset<32> bTimestamp(Timestamp());
    if (startTime < 0) {
        startTime = static_cast<int>(bTimestamp.to_ulong());
    }
    int Time = endTime - startTime;
    if (Time > 1073741824)
    {
        Time = 1073741824;
    }
    bitset<32> Timestamp(startTime);//获取32位长的二进制起始时间

    vector<std::string> parts;
    istringstream ss(lalontute);
    string part;
    while (std::getline(ss, part, ',')) {
        parts.push_back(part);
    }
    encryption = encrypt_Key(Time, Timestamp, stoi(parts[0]) + 90, stoi(parts[1]) + 180, stoi(range));
    //加密过程
    SecByteBlock aesKey1(reinterpret_cast<const byte*>(hash_256(encryption.Key + hash_256(random_key)).c_str()), 32);
    SecByteBlock iv(reinterpret_cast<const byte*>(&encryption.Lifespan), sizeof(int));

    //设置AES加密器和解密器
    ECB_Mode<AES>::Encryption aesEncryptor;
    aesEncryptor.SetKey(aesKey1, aesKey1.size());

    //加密信息流
    string cipherText;
    StringSource(plainText, true,
        new StreamTransformationFilter(aesEncryptor,
            new StringSink(cipherText)
        )
    );

    //签名信息
    string RSA_Curtime_cipherText = RSA_encrypt(to_string(encryption.curtime));
    string RSA_Lifespan_cipherText = RSA_encrypt(to_string(encryption.Lifespan));
    string RSA_Random_cipherText = RSA_encrypt(random_key);
    string RSA_startTime_cipherText = RSA_encrypt(to_string(startTime));
    string RSA_LaRange_cipherText = RSA_encrypt(to_string(encryption.LaRange));
    string RSA_BLaRange_cipherText = RSA_encrypt(to_string(encryption.BLaRange));
    string RSA_LoRange_cipherText = RSA_encrypt(to_string(encryption.LoRange));
    string RSA_BLoRange_cipherText = RSA_encrypt(to_string(encryption.BLoRange));
    string RSA_flag_cipherText = RSA_encrypt(to_string(encryption.flag));
    
    //合并签名与密文
    cipherText = RSA_Curtime_cipherText + RSA_Lifespan_cipherText
        + RSA_Random_cipherText+ RSA_startTime_cipherText
        + RSA_LaRange_cipherText + RSA_BLaRange_cipherText + RSA_LoRange_cipherText + RSA_BLoRange_cipherText 
        + RSA_flag_cipherText +cipherText;

    cout << "File encrypted successfully." << endl;

    return cipherText;

}
//Key_Information AES_encrypt(string Time, string inputFile, string encryptedFile) {
//        
//
//    string random_key = get_Random();
//
//    ifstream inFile(inputFile, ios::binary);
//    string plainText((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
//    inFile.close();
//
//    // 创建 AES 密钥
//    Key_Information encryption;
//    encryption = encrypt_Key(stoi(Time));
//    SecByteBlock aesKey1(reinterpret_cast<const byte*>(hash_256(encryption.Key+ hash_256(random_key)).c_str()), 32);
//    SecByteBlock iv(reinterpret_cast<const byte*>(&encryption.Lifespan), sizeof(int));
//    //cout << encryption.curtime << "||" << encryption.Lifespan << endl;
//
//    // 设置 AES 加密器和解密器
//    /*CBC_Mode<AES>::Encryption aesEncryptor;
//    aesEncryptor.SetKeyWithIV(aesKey1, aesKey1.size(), iv);*/
//    ECB_Mode<AES>::Encryption aesEncryptor;
//    aesEncryptor.SetKey(aesKey1, aesKey1.size());
//
//    // 加密并写入加密后的文件
//    string cipherText;
//    StringSource(plainText, true,
//        new StreamTransformationFilter(aesEncryptor,
//            new StringSink(cipherText)
//        )
//    );
//
//    //期限加密操作,string类长度为40,curtime为2
//    string RSA_Curtime_cipherText;
//    string RSA_Lifespan_cipherText;
//    RSA_Curtime_cipherText = RSA_encrypt(to_string(encryption.curtime));
//    RSA_Lifespan_cipherText = RSA_encrypt(to_string(encryption.Lifespan));
//    string RSA_Random_cipherText = RSA_encrypt(random_key);
//
//    //将签名与密文保存
//    ofstream signedFile("Signed_"+inputFile, std::ios::binary);
//    signedFile << RSA_Curtime_cipherText;
//    signedFile << RSA_Lifespan_cipherText;
//    signedFile << RSA_Random_cipherText;
//    signedFile << cipherText;
//        
//
//    signedFile.close();
//    /*ofstream encryptedOut(encryptedFile, ios::binary);
//    encryptedOut.write(cipherText.c_str(), cipherText.size());
//    encryptedOut.close();*/
//
//    cout << "File encrypted successfully." << endl;
//    return encryption;
//
//}

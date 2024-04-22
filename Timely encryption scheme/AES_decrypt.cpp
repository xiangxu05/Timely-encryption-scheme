#include "AES.h"

string AES_decrypt(string encryptedFile, string decryptedFile) {

    Key_Information encryption;

    // 打开加密后的文件，进行解密操作
    ifstream encryptedIn(encryptedFile, ios::binary);
    string encryptedText((istreambuf_iterator<char>(encryptedIn)), istreambuf_iterator<char>());
    encryptedIn.close();

    // 拆分内容
    size_t split= 256;
    string RSA_Curtime_cipherText = encryptedText.substr(0,split);
    string RSA_Lifespan_cipherText = encryptedText.substr(split,split);
    string RSA_Random_cipherText = encryptedText.substr(2*split, split);
    string RSA_startTime_cipherText = encryptedText.substr(3 * split, split);
    string RSA_LaRange_cipherText = encryptedText.substr(4 * split, split);
    string RSA_BLaRange_cipherText = encryptedText.substr(5 * split, split);
    string RSA_LoRange_cipherText = encryptedText.substr(6 * split, split);
    string RSA_BLoRange_cipherText = encryptedText.substr(7 * split, split);
    string RSA_flag_cipherText = encryptedText.substr(8 * split, split);
    string cipherText = encryptedText.substr(9 * split);

    RSA_Curtime_cipherText = RSA_decrypt(RSA_Curtime_cipherText);
    RSA_Lifespan_cipherText = RSA_decrypt(RSA_Lifespan_cipherText);
    RSA_Random_cipherText = RSA_decrypt(RSA_Random_cipherText);
    RSA_startTime_cipherText = RSA_decrypt(RSA_startTime_cipherText);
    RSA_LaRange_cipherText = RSA_decrypt(RSA_LaRange_cipherText);
    RSA_BLaRange_cipherText = RSA_decrypt(RSA_BLaRange_cipherText);
    RSA_LoRange_cipherText = RSA_decrypt(RSA_LoRange_cipherText);
    RSA_BLoRange_cipherText = RSA_decrypt(RSA_BLoRange_cipherText);
    RSA_flag_cipherText = RSA_decrypt(RSA_flag_cipherText);
    encryption.curtime = stoi(RSA_Curtime_cipherText);
    encryption.Lifespan = stoi(RSA_Lifespan_cipherText);
    encryption.LaRange = stoi(RSA_LaRange_cipherText);
    encryption.BLaRange = stoi(RSA_BLaRange_cipherText);
    encryption.LoRange = stoi(RSA_LoRange_cipherText);
    encryption.BLoRange = stoi(RSA_BLoRange_cipherText);
    encryption.flag = stoi(RSA_flag_cipherText);

    if (Timestamp() - stoi(RSA_startTime_cipherText) < 0) {
        throw std::runtime_error("还未到解密时间");
    }
    // 创建密钥 
    SecByteBlock aesKey2(reinterpret_cast<const byte*>(hash_256(decrypt_Key(encryption)+ hash_256(RSA_Random_cipherText)).c_str()), 32);
    /*SecByteBlock iv(reinterpret_cast<const byte*>(&encryption.Lifespan), 128);*/
    SecByteBlock iv(reinterpret_cast<const byte*>(&encryption.Lifespan), sizeof(int));
    /*CBC_Mode<AES>::Decryption aesDecryptor;
    aesDecryptor.SetKeyWithIV(aesKey2, aesKey2.size(), iv);*/
    ECB_Mode<AES>::Decryption aesDecryptor;
    aesDecryptor.SetKey(aesKey2, aesKey2.size());

    // 解密并写入解密文件
    string decryptedText;
    StringSource(cipherText, true,
        new StreamTransformationFilter(aesDecryptor,
            new StringSink(decryptedText)
        )
    );

    cout << "File decrypted successfully." << endl;

    return decryptedText;
}
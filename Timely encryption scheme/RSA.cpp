#include "RSA.h"



void Generate_Key() {
    // 1. 生成密钥对
    AutoSeededRandomPool rng;
    InvertibleRSAFunction privateKeyParameters;
    privateKeyParameters.GenerateRandomWithKeySize(rng, 2048); // 2048位密钥长度
    RSA::PrivateKey privateKey(privateKeyParameters);
    RSA::PublicKey publicKey;
    publicKey.AssignFrom(privateKey);

    // 2. 保存私钥到文件
    ByteQueue privateKeyBytes;
    privateKey.Save(privateKeyBytes);
    FileSink privateKeyFile("private_key.pem");
    privateKeyBytes.CopyTo(privateKeyFile);
    privateKeyFile.MessageEnd();

    // 3. 保存公钥到文件
    ByteQueue publicKeyBytes;
    publicKey.Save(publicKeyBytes);
    FileSink publicKeyFile("public_key.pem");
    publicKeyBytes.CopyTo(publicKeyFile);
    publicKeyFile.MessageEnd();
};

string RSA_encrypt(string message) {
    AutoSeededRandomPool rng;
    RSA::PublicKey publicKey;

    // 从文件中加载公钥
    ByteQueue publicKeyBytes;
    FileSource publicKeyFile("public_key.pem", true);
    publicKeyFile.TransferTo(publicKeyBytes);
    publicKeyBytes.MessageEnd();
    publicKey.Load(publicKeyBytes);

    RSAES_OAEP_SHA_Encryptor encryptor(publicKey);

    //使用加密器加密数据
    string cipherText;

    StringSource(message, true,
        new PK_EncryptorFilter(rng, encryptor,
            new StringSink(cipherText)));

    return cipherText;
};

//string RSA_encrypt(Key_Information message) {
//    AutoSeededRandomPool rng;
//    RSA::PublicKey publicKey;
//
//    // 从文件中加载公钥
//    ByteQueue publicKeyBytes;
//    FileSource publicKeyFile("public_key.pem", true);
//    publicKeyFile.TransferTo(publicKeyBytes);
//    publicKeyBytes.MessageEnd();
//    publicKey.Load(publicKeyBytes);
//
//    RSAES_OAEP_SHA_Encryptor encryptor(publicKey);
//    
//    //明文格式转换
//    string TimeSpan;
//    TimeSpan = to_string(message.curtime) + " " + to_string(message.Lifespan);
//
//    //使用加密器加密数据
//    string cipherText;
//    string cipherText1;
//    string cipherText2;
//
//    /*StringSource(TimeSpan, true,
//        new PK_EncryptorFilter(rng, encryptor,
//            new StringSink(cipherText)));*/
//    StringSource(to_string(message.curtime), true,
//        new PK_EncryptorFilter(rng, encryptor,
//            new StringSink(cipherText1)));
//    StringSource(to_string(message.Lifespan), true,
//        new PK_EncryptorFilter(rng, encryptor,
//            new StringSink(cipherText2)));
//    cipherText = cipherText1 + cipherText2;
//
//    return cipherText;
//    //// 保存加密后的数据到文件
//    //FileSink cipherFile("encrypted.bin");
//    //cipherFile.Put(reinterpret_cast<const byte*>(cipherText.data()), cipherText.size());
//
//};

string RSA_decrypt(string message) {
    AutoSeededRandomPool rng;
    RSA::PrivateKey privateKey;

    // 从文件中加载私钥
    ByteQueue privateKeyBytes;
    FileSource privateKeyFile("private_key.pem", true);
    privateKeyFile.TransferTo(privateKeyBytes);
    privateKeyBytes.MessageEnd();
    privateKey.Load(privateKeyBytes);

    RSAES_OAEP_SHA_Decryptor decryptor(privateKey);


    // 使用解密器解密数据
    string recoveredText;
    StringSource(message, true,
        new PK_DecryptorFilter(rng, decryptor,
            new StringSink(recoveredText)));

    return recoveredText;
    //// 保存解密后的数据到文件
    //FileSink recoveredFile("recovered.txt");
    //recoveredFile.Put(reinterpret_cast<const byte*>(recoveredText.data()), recoveredText.size());
}
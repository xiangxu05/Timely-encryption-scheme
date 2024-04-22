#include <iostream>
#include <fstream>
#include <modes.h>
#include <files.h>
#include <aes.h>
#include <chrono>
#include <thread>
#include <conio.h>
#include "get_Key.h"
#include "AES.h"
#include "Hash-256.h"

using namespace std;
using namespace CryptoPP;

string getRange() {
    string range;
    cout << "Enter limited range(>0):";
    cin >> range;
    try {
        if (stoi(range) < 0) {
            cout << "Invalide range!" << endl;
            range = getRange();
        }
    }
    catch (const exception& e) {
        cout << "Invalide range!" << endl;
        range = getRange();
    }
    return range;
}
int main() {
    while (true) {
        int choice;
        char from[11], to[11];
        getSecond Time;
        string encryption;//存储密文
        string decryption;//存储明文
        string inputFile;
        string encryptedFile;
        string decryptedFile;
        string location, range;
        try {
            while (true) {
#ifdef _WIN32
                system("cls"); // For Windows
#else
                system("clear"); // For Linux
#endif
                cout << "Options:" << endl;
                cout << "1. Generate Private_Public Key" << endl;
                cout << "2. Encrypt File" << endl;
                cout << "3. Decrypt File" << endl;
                cout << "4. Exit" << endl;
                cout << "Enter your choice (1-4): ";

                cin >> choice;

                switch (choice) {
                case 1: //生成公私钥对
                {Generate_Key();
                cout << "The key was generated!(private_key.pem public_key.pem)" << endl;
                cout << "press anykey to continue." << endl;
                _getch();
                break; }
                case 2: //加密选项
                {cout << "Please ensure the public_key.pem is in your folder." << endl;
                cout << "Enter the start time period(year-month-day,eg:2023-11-01):" << endl;
                cin >> from;
                cout << "Enter the end time period(year-month-day,eg:2023-11-10):" << endl;
                cin >> to;
                Time = get_Second(from, to);
                if ((Time.tosecond - Time.fromsecond) < 0) {
                    cout << "Error: invalid input time!";
                    cout << "press anykey to continue." << endl;
                    _getch();
                    break;
                }
                cout << "Enter target location(eg:40.1,150.5) :" << endl;
                cin >> location;
                range = getRange();
                cout << "Enter the inputFile name:" << endl;
                cin >> inputFile;
                ifstream inFile(inputFile, ios::binary);
                string plainText((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
                inFile.close();
                encryption = AES_encrypt(location, range, plainText, Time.tosecond, Time.fromsecond);
                //encryption = AES_encrypt(to_string(Time), inputFile, encryptedFile);
                ofstream signedFile("Signed_" + inputFile, ios::binary);
                signedFile << encryption;
                signedFile.close();
                cout << "press anykey to continue." << endl;
                _getch();
                break; }
                case 3: //解密选项
                {cout << "Please ensure the private_key.pem is in your folder." << endl;
                cout << "Enter the encryptedFile name:" << endl;
                cin >> encryptedFile;
                decryption= AES_decrypt(encryptedFile, decryptedFile);
                ofstream decryptedOut("decrypted_" + encryptedFile, ios::binary);
                decryptedOut.write(decryption.c_str(), decryption.size());
                decryptedOut.close();
                string startFile = "start .\\decrypted_" + encryptedFile;
                system(startFile.c_str());
                string Filepath = ".\\decrypted_" + encryptedFile;
                cout << "press anykey to continue." << endl;
                
                _getch();

                deleteFile(startFile);

                break; }
                case 4: //退出
                {std::cout << "Exiting..." << std::endl;
                this_thread::sleep_for(chrono::seconds(2));
                return 0; }
                default:
                {std::cout << "Invalid choice. Please enter a valid option." << std::endl; }
                }
            }
        }
        catch (const exception& e) {
            cout << "\n------------------------------------------------" << endl;
            cout << "            Wrong time or location!" << endl;
            cout << "------------------------------------------------" << endl;
            cout << "press anykey to continue." << endl;

            _getch();
        }
    }
    return 0;
}

#ifndef GET_KEY_H
#define GET_KEY_H
#include <ctime>
#include <bitset>
#include <string>
#include <cstdio>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>

using namespace std;

struct Key_Information {
    string Key;//密钥
    int Lifespan;//有效时间期限
    int curtime ;//原始时间期限占的位数
    int LaRange;//有效维度距离
    int BLaRange;//原始维度距离占的位数
    int LoRange;//有效精度距离
    int BLoRange;//原始精度距离占的位数
    int flag;
};
struct getSecond {
    int tosecond;
    int fromsecond;
};

time_t Timestamp();

string BinaryToDecimal(const string& binary_string);

int binary_bits_required(int value);

string remove_binary_suffix(const string& binary_string, int num_bits);

bitset<32> getBitsFromEnd(const bitset<32>& binaryBits, int numBits);

bitset<32> getBitsFromStart(const bitset<32>& binaryBits, int numBits);

Key_Information encrypt_Key(int Time, bitset<32> bTimestamp,
    int Latitute, int Longitute, int range);

string decrypt_Key(Key_Information Time);

time_t convert_Time(int year, int month, int day);

getSecond get_Second(const char* from, const char* to);
#endif
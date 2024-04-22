#include "get_Key.h"


time_t Timestamp() {//获得当前时间戳
    time_t currentTime = time(nullptr);
    return currentTime;
}

string BinaryToDecimal(const string& binary_string) {//二进制十进制转换
    int decimal_value = bitset<32>(binary_string).to_ulong();
    return to_string(decimal_value);
}

int binary_bits_required(int value) {//输入的数值，需要多少位二进制容纳
    if (value == 0) {
        return 1;
    }
    else {
        int bits = 0;
        while (value > 0) {
            value >>= 1;
            bits++;
        }
        return bits;
    }
}

string remove_binary_suffix(const string& binary_string, int num_bits) {//移除后面不需要的二进制位
    return binary_string.substr(0, binary_string.size() - num_bits);
}

bitset<32> getBitsFromEnd(const bitset<32>& binaryBits, int numBits) {//获取后半部分的二进制位
    bitset<32> mask((1 << numBits) - 1);
    return binaryBits & mask;
}

bitset<32> getBitsFromStart(const bitset<32>& binaryBits, int numBits) {//获取前半部分的二进制位
    bitset<32> mask((1 << numBits) - 1);
    return (binaryBits >> (32 - numBits)) & mask;
}

Key_Information encrypt_Key(int Time, bitset<32> bTimestamp,
    int Latitute, int Longitute, int range){//加密密钥获取
    Key_Information Num;//存储密钥相关信息

    //以下是关于时间的处理
    int lifeSpan = binary_bits_required(Time);
    int curTime = getBitsFromEnd(bTimestamp, lifeSpan).to_ulong();
    bTimestamp = (bitset <32>(getBitsFromStart(bTimestamp, 32 - lifeSpan).to_ulong() - 1) << lifeSpan);
    Num.Key = bTimestamp.to_string();
    Num.Lifespan = Time + curTime + 1;
    Num.curtime = lifeSpan;
    
    //以下是关于距离的处理
    
        //以下是关于纬度的处理
    int range1 = range;
    Latitute -= range1;
    range1 = range1 * 2;
    if (Latitute < 0) {
        range1 += Latitute;
        Latitute = 0;
    }
    if (Latitute + range1 > 180) {
        range1 = 180 - Latitute;
    }
    Latitute *= 100000; range1 *= 100000;
    bitset<32> Latitute_Binary = bitset<32>(Latitute);
    int BLarange = binary_bits_required(range1);
    int Larange = getBitsFromEnd(Latitute_Binary, BLarange).to_ulong();
    Latitute_Binary = (bitset<32>(getBitsFromStart(Latitute_Binary, 32 - BLarange).to_ulong() - 1) << BLarange);
    Num.Key += Latitute_Binary.to_string();
    Num.BLaRange = BLarange;
    Num.LaRange = range1 + Larange + 1;
        //以下是关于经度的处理
    int flag = 0;
    int range2 = range;
    Longitute -= range2;
    range2 = range2 * 2;
    if (Longitute < 0) {
        Longitute += 360;
        flag = 1;
    }
    if (Longitute + range2 > 360) {
        flag = 1;
    }
    Longitute *= 100000; range2 *= 100000;
    bitset<32> Longitute_Binary = bitset<32>(Longitute);
    int BLorange = binary_bits_required(range2);
    int Lorange = getBitsFromEnd(Longitute_Binary, BLorange).to_ulong();
    Longitute_Binary = (bitset<32>(getBitsFromStart(Longitute_Binary, 32 - BLorange).to_ulong() - 1) << BLorange);
    Num.Key += Longitute_Binary.to_string();
    Num.BLoRange = BLorange;
    Num.LoRange = range2 + Lorange + 1;
    Num.flag = flag;
    return Num;
}

string decrypt_Key(Key_Information Time) {//解密密钥获取
    string key;

    //获取时间密钥
    int stamp = Timestamp() - Time.Lifespan;
    bitset<32> bTimestamp(stamp);
    bTimestamp = (bitset <32>(getBitsFromStart(bTimestamp, 32 - Time.curtime).to_ulong()) << Time.curtime);
    
    //获取当前经纬度
    int Latitute = 20;
    int Longitute = 20;

    //获取空间密钥
    Latitute = (Latitute+90)*100000-Time.LaRange; Longitute = (Longitute+180)*100000-Time.LoRange;
    bitset<32> Latitute_Binary = bitset<32>(Latitute);
    Latitute_Binary = (bitset<32>(getBitsFromStart(Latitute_Binary, 32 - Time.BLaRange).to_ulong()) << Time.BLaRange);
    bitset<32> Longitute_Binary = bitset<32>(Longitute);
    Longitute_Binary = (bitset<32>(getBitsFromStart(Longitute_Binary, 32 - Time.BLoRange).to_ulong()) << Time.BLoRange);

    key = bTimestamp.to_string() + Latitute_Binary.to_string() + Longitute_Binary.to_string();

    return key;
}

time_t convert_Time(int year, int month, int day) {//时间换算成时间戳
    tm info = { 0 };
    info.tm_year = year - 1900;
    info.tm_mon = month - 1;
    info.tm_mday = day;
    return mktime(&info);
}

getSecond get_Second(const char* from, const char* to) {//时间戳换算成秒
    int year, month, day;
    getSecond second;
    second.fromsecond = -1;
    second.tosecond = -1;
    if (sscanf_s(from, "%d-%d-%d", &year, &month, &day) < 0) {
        return second;
    }
    second.fromsecond = static_cast<int>(convert_Time(year, month, day));
    if (sscanf_s(to, "%d-%d-%d", &year, &month, &day) < 0) {
        return second;
    };
    second.tosecond = static_cast<int>(convert_Time(year, month, day));
    return second;
}

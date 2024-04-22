//#include <bitset>
//#include <iostream>
//#include <string>
//
//using namespace std;
//std::bitset<32> decimalToBinary(int decimalNumber) {
//    // 使用 std::bitset 构造函数将整数转换为二进制表示
//    return std::bitset<32>(decimalNumber);
//}
//string getRange() {
//    string range;
//    cout << "Enter limited range(centimeter>0):" ;
//    cin >> range;
//    try {
//        if (stoi(range) < 0) {
//            cout << "Invalide range!" << endl;
//            range = getRange();
//        }
//    }
//    catch (const exception& e) {
//        cout << "Invalide range!" << endl;
//        range = getRange();
//    }
//    return range;
//}
//
//int main() {
//    // 示例：将十进制数 42 转换为二进制
//    int decimalNumber = 42;
//    string range;
//    std::bitset<32> binaryRepresentation = decimalToBinary(decimalNumber);
//
//    // 输出结果
//    std::cout << "Decimal: " << decimalNumber << std::endl;
//    std::cout << "Binary:  " << binaryRepresentation << std::endl;
//    range = getRange();
//    cout << range << endl;
//    return 0;
//}

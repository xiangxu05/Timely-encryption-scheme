#include "random.h"

string get_Random() {
	random_device rd;
	mt19937 gen(rd());
	string random_string(16, ' ');
	uniform_int_distribution<int> dist(0, 9);

	// 生成128位长的随机数  
	for (int i = 0; i < 16; ++i) {
		random_string[i] = '0' + dist(gen); // 将生成的随机整数转换为对应的数字字符  
	}
	random_string.resize(128);

	return random_string;
}
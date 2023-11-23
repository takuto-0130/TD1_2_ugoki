#include "Util.h"
#include <Novice.h>

// 指定した範囲の乱数を生成する関数
int Random(int min, int max) {
	int range = max - min + 1;

	return rand() % range + min;
}

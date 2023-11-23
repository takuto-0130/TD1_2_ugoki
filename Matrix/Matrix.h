#pragma once
#include "Vector2.h"
#define _USE_MATH_DEFINES
#include <math.h>

// 2x2の行列
struct Matrix2x2 {
	float m[2][2];
};

// ベクトルと行列の積を求める関数
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix);

// 回転行列の作成関数
Matrix2x2 MakeRotateMatrix(float theta);

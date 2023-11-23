#include "Matrix.h"

Vector2 Multiply(Vector2 vector, Matrix2x2 matrix)
{
	Vector2 result;
	result.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]);
	result.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]);

	return result;
}

Matrix2x2 MakeRotateMatrix(float theta)
{
	Matrix2x2 result;
	result.m[0][0] = cosf(theta);
	result.m[0][1] = sinf(theta);

	result.m[1][0] = -sinf(theta);
	result.m[1][1] = cosf(theta);

	return result;
}

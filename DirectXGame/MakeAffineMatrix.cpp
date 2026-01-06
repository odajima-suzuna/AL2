#include "MakeAffineMatrix.h"

KamataEngine::Matrix4x4 MakeAffineMatrix(KamataEngine::Vector3 rotate, KamataEngine::Vector3 scale, KamataEngine::Vector3 translate) {

	// 回転行列の作成
	KamataEngine::Matrix4x4 rotateMatrix;
	rotateMatrix.m[0][0] = cosf(rotate.y) * cosf(rotate.z);
	rotateMatrix.m[0][1] = -(cosf(rotate.y))*sinf(rotate.z);
	rotateMatrix.m[0][2] = sinf(rotate.y);
	rotateMatrix.m[0][3] = 0.0f;

	rotateMatrix.m[1][0] = cosf(rotate.x) * sinf(rotate.z) + sinf(rotate.x) * sinf(rotate.y) * cosf(rotate.z);
	rotateMatrix.m[1][1] = cosf(rotate.x) * cosf(rotate.z) - sinf(rotate.x) * sinf(rotate.y) * sinf(rotate.z);
	rotateMatrix.m[1][2] = -(sinf(rotate.x))*cosf(rotate.y);
	rotateMatrix.m[1][3] = 0.0f;

	rotateMatrix.m[2][0] = sinf(rotate.x) * sinf(rotate.z) - cosf(rotate.x) * sinf(rotate.y) * cosf(rotate.z);
	rotateMatrix.m[2][1] = sinf(rotate.x) * cosf(rotate.z) + cosf(rotate.x) * sinf(rotate.y) * sinf(rotate.z);
	rotateMatrix.m[2][2] = cosf(rotate.x) * cosf(rotate.y);
	rotateMatrix.m[2][3] = 0.0f;

	rotateMatrix.m[3][0] = 0.0f;
	rotateMatrix.m[3][1] = 0.0f;
	rotateMatrix.m[3][2] = 0.0f;
	rotateMatrix.m[3][3] = 1.0f;

	// アフィン行列の作成
	KamataEngine::Matrix4x4 affineMatrix;
	affineMatrix.m[0][0] = scale.x * rotateMatrix.m[0][0];
	affineMatrix.m[0][1] = scale.x * rotateMatrix.m[0][1];
	affineMatrix.m[0][2] = scale.x * rotateMatrix.m[0][2];
	affineMatrix.m[0][3] = 0.0f;

	affineMatrix.m[1][0] = scale.y * rotateMatrix.m[1][0];
	affineMatrix.m[1][1] = scale.y * rotateMatrix.m[1][1];
	affineMatrix.m[1][2] = scale.y * rotateMatrix.m[1][2];
	affineMatrix.m[1][3] = 0.0f;

	affineMatrix.m[2][0] = scale.z * rotateMatrix.m[2][0];
	affineMatrix.m[2][1] = scale.z * rotateMatrix.m[2][1];
	affineMatrix.m[2][2] = scale.z * rotateMatrix.m[2][2];
	affineMatrix.m[2][3] = 0.0f;

	affineMatrix.m[3][0] = translate.x;
	affineMatrix.m[3][1] = translate.y;
	affineMatrix.m[3][2] = translate.z;
	affineMatrix.m[3][3] = 1.0f;

	return affineMatrix;
}
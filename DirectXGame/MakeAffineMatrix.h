#pragma once
#include "KamataEngine.h"

// アフィン行列の作成
KamataEngine::Matrix4x4 MakeAffineMatrix(KamataEngine::Vector3 rotate, KamataEngine::Vector3 scale, KamataEngine::Vector3 translate);
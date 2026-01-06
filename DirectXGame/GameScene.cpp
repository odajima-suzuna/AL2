#include "GameScene.h"
#include "2d/ImGuiManager.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {

	// 3Dモデルの解放
	delete model_;

#ifdef _DEBUG

	// デバッグ用カメラの解放
	delete debugCamera_;

#endif // _DEBUG

	// ブロック用ワールド行列の解放
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();
}

void GameScene::Initialize() {

	// 3Dモデル生成
	model_ = Model::Create();

	// ワールド行列初期化
	worldTransform_.Initialize();

	// カメラ初期化
	camera_.Initialize();

#ifdef _DEBUG

	// デバッグ用カメラ生成
	debugCamera_ = new DebugCamera(1280, 720);

#endif // _DEBUG

	// 要素数
	const uint32_t kNumBlockVirtical = 10;
	const uint32_t kNumBlockHorizontal = 20;

	// ブロック1個の横幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	// 配列の要素数を変更
	// 列数を指定(縦)
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		// 列ごとの要素数を指定(横)
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			worldTransformBlocks_[i][j] = new KamataEngine::WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * j * 2;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * i;
		}
	}
}

void GameScene::Update() {

	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}

			// アフィン変換行列の作成
			Matrix4x4 affineMatrix = MakeAffineMatrix(worldTransformBlock->rotation_, worldTransformBlock->scale_, worldTransformBlock->translation_);

			worldTransformBlock->matWorld_ = affineMatrix;

			worldTransformBlock->TransferMatrix();
		}
	}

#ifdef _DEBUG

	// デバッグ用カメラの起動
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}

	if (isDebugCameraActive_) {

		// デバッグ用カメラ更新処理
		debugCamera_->Update();

		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;

		camera_.TransferMatrix();

	} else {
		camera_.UpdateMatrix();
	}

#endif // DEBUG
}

void GameScene::Draw() {

	// 3Dモデル描画開始
	Model::PreDraw();

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}

			model_->Draw(*worldTransformBlock, camera_);
		}
	}

	// 3Dモデル描画終了
	Model::PostDraw();
}

KamataEngine::Matrix4x4 GameScene::Multiply(KamataEngine::Matrix4x4 a, KamataEngine::Matrix4x4 b) {
	Matrix4x4 result;

	for (uint32_t i = 0; i < 4; i++) {
		for (uint32_t j = 0; j < 4; j++) {
			result.m[i][j] = 0.0f;
			for (uint32_t k = 0; k < 4; k++) {
				result.m[i][j] += a.m[i][k] * b.m[k][j];
			}
		}
	}

	return result;
}

KamataEngine::Matrix4x4 GameScene::MakeAffineMatrix(KamataEngine::Vector3 rotate, KamataEngine::Vector3 scale, KamataEngine::Vector3 translate) {

	// 回転行列の作成
	Matrix4x4 rotateMatrix;
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
	Matrix4x4 affineMatrix;
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
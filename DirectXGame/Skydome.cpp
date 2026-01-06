#include "Skydome.h"

Skydome::Skydome() {

}

Skydome::~Skydome() {

}

void Skydome::Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera) {
	
	// NULLチェック
	assert(model);
	assert(camera);

	// 引数をメンバ変数に記録
	model_ = model;
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

void Skydome::Update() {

	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.rotation_, worldTransform_.scale_, worldTransform_.translation_);

	worldTransform_.TransferMatrix();
}

void Skydome::Draw() {

	// 3Dモデル描画
	model_->Draw(worldTransform_, *camera_);
}
#include "Player.h"

Player::Player() {

}

Player::~Player() {

}

void Player::Initialize(KamataEngine::Model* model, uint32_t textureHandle,KamataEngine::Camera*camera) {

	// NULLチェック
	assert(model);
	assert(camera);

	// 引数をメンバ変数に代入
	model_ = model;
	grHandlePlayer_ = textureHandle;
	camera_ = camera;

	// ワールド行列初期化
	worldTransform_.Initialize();
}

void Player::Update() {

	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Player::Draw() {

	// 3Dモデルの描画
	model_->Draw(worldTransform_, *camera_,grHandlePlayer_);
}
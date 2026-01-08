#define NOMINMAX
#include "CameraController.h"
#include "Lerp.h"
#include "Player.h"
#include <KamataEngine.h>

using namespace KamataEngine;

CameraController::CameraController() {}

CameraController::~CameraController() {}

void CameraController::Initialize(Camera* camera) {
	// カメラの生成
	camera_ = camera;

	// カメラの初期化
	camera_->Initialize();

	// 移動範囲の指定
	SetMovaleArea({11.0f, 88.0f, 6.0f, 100.0f});
}

void CameraController::Update(Vector3 targetVelocity) {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	// カメラの座標を計算
	targetPosition_.x = targetWorldTransform.translation_.x + targetOffset_.x+targetVelocity.x*kVelocityBias;
	targetPosition_.y = targetWorldTransform.translation_.y + targetOffset_.y+targetVelocity.y * kVelocityBias;
	targetPosition_.z = targetWorldTransform.translation_.z + targetOffset_.z+targetVelocity.z * kVelocityBias;

	// カメラを追従
	camera_->translation_ = Lerp(camera_->translation_, targetPosition_, kInterpolationRate);

	// 追従対象が画面外に出ないように補正
	camera_->translation_.x = std::max(camera_->translation_.x, targetPosition_.x + margin.left);
	camera_->translation_.x = std::min(camera_->translation_.x, targetPosition_.x + margin.right);
	camera_->translation_.y = std::max(camera_->translation_.y, targetPosition_.y + margin.bottom);
	camera_->translation_.y = std::min(camera_->translation_.y, targetPosition_.y + margin.top);

	// 移動範囲制限
	camera_->translation_.x = std::max(camera_->translation_.x, movableArea_.left);
	camera_->translation_.x = std::min(camera_->translation_.x, movableArea_.right);
	camera_->translation_.y = std::max(camera_->translation_.y, movableArea_.bottom);
	camera_->translation_.y = std::min(camera_->translation_.y, movableArea_.top);

	// 行列を更新
	camera_->UpdateMatrix();
}

void CameraController::Reset() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	// カメラの座標を計算
	camera_->translation_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	camera_->translation_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	camera_->translation_.z = targetWorldTransform.translation_.z + targetOffset_.z;
}
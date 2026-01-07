#define NOMINMAX
#include "Player.h"
#include "algorithm"
#include "numbers"

using namespace KamataEngine;

Player::Player() {}

Player::~Player() {}

void Player::Initialize(Model* model, Camera* camera, const Vector3& position) {

	// NULLチェック
	assert(model);
	assert(camera);

	// 引数をメンバ変数に記録
	model_ = model;
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.rotation_.y = -std::numbers::pi_v<float> / 2.0f;
}

void Player::Update() {

	if (onGround_) {
		// 移動入力
		if (Input::GetInstance()->PushKey(DIK_D) || Input::GetInstance()->PushKey(DIK_A)) {

			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_D)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x += kAcceleration;

				// 方向制御
				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			} else if (Input::GetInstance()->PushKey(DIK_A)) {
				// 右移動中の左入力
				if (velocity_.x > 0.0f) {
					velocity_.x *= (1.0f - kAttenuation);
				}
				acceleration.x -= kAcceleration;

				// 方向制御
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			}

			// 加減速
			velocity_.x += acceleration.x;
			velocity_.y += acceleration.y;
			velocity_.z += acceleration.z;

			// 速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

		} else {

			// 非入力時は移動減衰をかける
			velocity_.x *= (1.0f - kAttenuation);
		}

		// ジャンプ
		if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
			velocity_.y += kJumpAcceleration;
		}

	} else {
		//落下速度
		velocity_.y += -kGravityAcceleration;

		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	// 移動
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;
	worldTransform_.translation_.z += velocity_.z;

	// 着地フラグ
	bool landing = false;

	// 地面との当たり判定
	if (velocity_.y < 0.0f) {
		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;
		}
	}

	// 接地判定
	if (onGround_) {
		// ジャンプ開始
		if (velocity_.y > 0.0f) {
			onGround_ = false;
		}
	} else {
		// 着地
		if (landing) {
			// めり込み排斥
			worldTransform_.translation_.y = 1.0f;

			//速度減退
			velocity_.x *= (1.0f - kAttenuation);

			//下方向速度をリセット
			velocity_.y = 0.0f;

			// 接地状態に移行
			onGround_ = true;
		}
	}

	// 旋回制御
	if (turnTimer_ > 0.0f) {

		turnTimer_ -= 1.0f / 60.0f;

		// 角度のテーブル
		float destinationRotateYTable[]{
		    std::numbers::pi_v<float> * 3.0f / 2.0f,
		    std::numbers::pi_v<float> / 2.0f,
		};
		// 角度を取得
		float destinationRotationY = destinationRotateYTable[static_cast<uint32_t>(lrDirection_)];

		// イージング用のtを取得
		float t = 1.0f - (turnTimer_ / kTimeTurn);
		float easedT = 1.0f - powf(1.0f - t, 4.0f);

		// 角度を設定
		worldTransform_.rotation_.y = (1.0f-easedT) * turnFirstRotationY_ + easedT* destinationRotationY;
	}

	// 行列の更新
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.rotation_, worldTransform_.scale_, worldTransform_.translation_);
	worldTransform_.TransferMatrix();
}

void Player::Draw() {

	// 3Dモデル描画
	model_->Draw(worldTransform_, *camera_);
}
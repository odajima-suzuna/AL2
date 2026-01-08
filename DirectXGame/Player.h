#pragma once
#include "KamataEngine.h"
#include "MakeAffineMatrix.h"

// 加速度
static inline const float kAcceleration = 0.01f;

// 減速量
static inline const float kAttenuation = 0.1f;

// 速度上限
static inline const float kLimitRunSpeed = 0.3f;

//自機の向き
enum class LRDirection {
	kRight, // 右
	kLeft,  // 左
};

// 旋回時間
static inline const float kTimeTurn = 0.3f;

// 重力加速度
static inline const float kGravityAcceleration = 2.0f/60.0f;

// 最大落下速度
static inline const float kLimitFallSpeed = 100.0f;

// ジャンプ初速
static inline const float kJumpAcceleration = 27.0f/60.0f;

class Player {
public:  /*public変数*/
private: /*private変数*/
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// 速度
	KamataEngine::Vector3 velocity_ = {};

	// 向き
	LRDirection lrDirection_ = LRDirection::kRight;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;

	// 旋回タイマー
	float turnTimer_ = 0.0f;

	// 接地フラグ
	bool onGround_ = true;

public: /*public関数*/
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// ゲッター ======================================================================================

	const KamataEngine::WorldTransform& GetWorldTransform() { return worldTransform_; }

	const KamataEngine::Vector3& GetVelocity() const { return velocity_; }


private: /*private関数*/
};

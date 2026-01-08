#pragma once
#include "KamataEngine.h"

class Player;

class CameraController {
public:  /*public変数*/
private: /*private変数*/
	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// 追従対象
	Player* target_ = nullptr;

	//追従対象とカメラの座標の差
	KamataEngine::Vector3 targetOffset_ = {0.0f, 0.0f, -15.0f};

	// 矩形
	struct Rect {
		float left = 0.0f;
		float right = 1.0f;
		float bottom = 0.0f;
		float top = 1.0f;
	};

	// カメラ移動範囲
	Rect movableArea_ = {0.0f, 100.0f, 0.0f, 100.0f};

	// カメラの目標座標
	KamataEngine::Vector3 targetPosition_;

	// 座標変換割合
	static inline const float kInterpolationRate = 0.1f;

	// 速度掛け率
	static inline const float kVelocityBias = 20.0f;

	// 追従対象の各方向へのカメラ移動範囲
	static inline const Rect margin = {-40.0f, 40.0f, -30.0f, 30.0f};

public:  /*public関数*/
	/// <summary>
	/// コンストラクタ
	/// </summary>
	CameraController();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~CameraController();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(KamataEngine::Camera*camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update(KamataEngine::Vector3 targetVelocity);

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

	// セッター ======================================================================================
	
	/// <summary>
	/// 追従対象の設定
	/// </summary>
	void SetTarGet(Player* target) { target_ = target; }

	void SetMovaleArea(Rect area) { movableArea_ = area; }

private: /*private関数*/
};
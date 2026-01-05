#pragma once
#include "KamataEngine.h"

class Player {
private: /*private変数*/

	// ワールド行列
	KamataEngine::WorldTransform worldTransform_;

	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;

	// 画像ハンドル
	uint32_t grHandlePlayer_ = 0u;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

public:  /*public関数*/

	Player();
	~Player();
	
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	/// <param name="camera">カメラ</param>
	void Initialize(KamataEngine::Model*model,uint32_t textureHandle,KamataEngine::Camera *camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	// ゲッター

	// セッター

private: /*private関数*/

};
#pragma once
#include <KamataEngine.h>

class GameScene {
public:  /*public変数*/

private: /*private変数*/

	// 画像ハンドル
	uint32_t grHandleSushi_ = 0;

	// 音声ハンドル
	uint32_t seHandleMokugyo = 0;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;

	// ワールド行列
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// デバッグ用カメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

public:  /*public関数*/

	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

	// 初期化
	void Initialize();

	// 更新処理
	void Update();

	// 描画処理
	void Draw();

private: /*private関数*/

};
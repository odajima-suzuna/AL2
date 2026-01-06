#pragma once
#include <KamataEngine.h>

class GameScene {
public:  /*public変数*/
private: /*private変数*/
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;

	// ワールド行列
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

#ifdef _DEBUG

	// デバッグ用カメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;

#endif // _DEBUG

public: /*public関数*/
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
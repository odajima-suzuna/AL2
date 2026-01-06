#pragma once
#include <KamataEngine.h>
#include "Skydome.h"
#include "Player.h"

class GameScene {
public:  /*public変数*/
private: /*private変数*/

	// カメラ
	KamataEngine::Camera camera_;

#ifdef _DEBUG

	// デバッグ用カメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;
	bool isDebugCameraActive_ = false;

#endif // _DEBUG

	// ブロック用ワールド行列
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	// ブロック3Dモデル
	KamataEngine::Model* modelBlock_ = nullptr;

	// 天球
	Skydome* skydome = nullptr;

	// 天球3Dモデル
	KamataEngine::Model* modelSkydome_ = nullptr;

	// 自機
	Player* player_ = nullptr;

	// 自機3Dモデル
	KamataEngine::Model* modelPlayer_ = nullptr;

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
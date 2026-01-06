#pragma once
#include <KamataEngine.h>
#include <vector>

class GameScene {
public:  /*public変数*/
private: /*private変数*/
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;

	// ワールド行列
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// ブロック用ワールド行列
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

#ifdef _DEBUG

	// デバッグ用カメラ
	bool isDebugCameraActive_ = false;
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

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
	// 行列の掛け算
	KamataEngine::Matrix4x4 Multiply(KamataEngine::Matrix4x4 a, KamataEngine::Matrix4x4 b);

	// アフィン行列の作成
	KamataEngine::Matrix4x4 MakeAffineMatrix(KamataEngine::Vector3 rotate, KamataEngine::Vector3 scale, KamataEngine::Vector3 translate);
};
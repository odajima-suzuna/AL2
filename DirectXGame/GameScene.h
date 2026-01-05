#pragma once
#include <KamataEngine.h>
#include "Player.h"

class GameScene {
public:  /*public変数*/

private: /*private変数*/
	
	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;

	// 画像ハンドル
	uint32_t grHandlePlayer_ = 0u;

	// カメラ
	KamataEngine::Camera camera_;

	// 自機
	Player* player_ = nullptr;

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
#include "GameScene.h"
#include "2d/ImGuiManager.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {

	// 3Dモデルの解放
	delete model_;

#ifdef _DEBUG

	// デバッグ用カメラの解放
	delete debugCamera_;

#endif // _DEBUG
}

void GameScene::Initialize() {

	// 3Dモデル生成
	model_ = Model::Create();

	// ワールド行列初期化
	worldTransform_.Initialize();

	// カメラ初期化
	camera_.Initialize();

#ifdef _DEBUG

	// デバッグ用カメラ生成
	debugCamera_ = new DebugCamera(1280, 720);

#endif // _DEBUG
}

void GameScene::Update() {

#ifdef _DEBUG

	// デバッグ用カメラの起動
	if (Input::GetInstance()->TriggerKey(DIK_RETURN)) {
		isDebugCameraActive_ = !isDebugCameraActive_;
	}

	if (isDebugCameraActive_) {

		// デバッグ用カメラ更新処理
		debugCamera_->Update();

		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;

		camera_.TransferMatrix();

	} else {
		camera_.UpdateMatrix();
	}

#endif // DEBUG
}

void GameScene::Draw() {

	// 3Dモデル描画開始
	Model::PreDraw();

	// 3Dモデル描画
	model_->Draw(worldTransform_, camera_);

	// 3Dモデル描画終了
	Model::PostDraw();
}
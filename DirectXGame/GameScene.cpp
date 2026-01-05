#include "GameScene.h"
using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {

	// 3Dモデルの解放
	delete model_;
	model_ = nullptr;

	// 自機の解放
	delete player_;
	player_ = nullptr;
}

void GameScene::Initialize() {

	// 3Dモデル生成
	model_ = Model::Create();

	// 画像読み込み
	grHandlePlayer_ = TextureManager::Load("./Resources/Images/sushi.png");

	// カメラ初期化
	camera_.Initialize();

	// 自機の生成
	player_ = new Player();

	// 自機の初期化
	player_->Initialize(model_,grHandlePlayer_,&camera_);
}

void GameScene::Update() {

	// 自機の更新
	player_->Update();
}

void GameScene::Draw() {

	// 3Dモデル描画開始
	Model::PreDraw();

	// 自機の描画
	player_->Draw();

	// 3Dモデル描画終了
	Model::PostDraw();
}
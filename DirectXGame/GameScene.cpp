#include "GameScene.h"
#include "2d/ImGuiManager.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {

#ifdef _DEBUG

	// デバッグ用カメラの解放
	delete debugCamera_;
	debugCamera_ = nullptr;

#endif // _DEBUG

	// ブロック用ワールド行列の解放
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}
	worldTransformBlocks_.clear();

	// ブロック3Dモデルの解放
	delete modelBlock_;
	modelBlock_ = nullptr;

	// マップチップフィールドの解放
	delete mapChipField_;
	mapChipField_ = nullptr;

	// 天球の解放
	delete skydome;
	skydome = nullptr;

	// 天球3Dモデルの解放
	delete modelSkydome_;
	modelSkydome_ = nullptr;

	// 自機の解放
	delete player_;
	player_ = nullptr;

	// 自機3Dモデルの解放
	delete modelPlayer_;
	modelPlayer_ = nullptr;
}

void GameScene::Initialize() {

	// カメラ初期化
	camera_.farZ = 800.0f;
	camera_.Initialize();

#ifdef _DEBUG

	// デバッグ用カメラ生成
	debugCamera_ = new DebugCamera(1280, 720);
	debugCamera_->SetFarZ(800.0f);

#endif // _DEBUG

	// マップチップフィールドの生成
	mapChipField_ = new MapChipField();

	// マップチップファイルの読み込み
	mapChipField_->LoadMapChipCsv("Resources/blocks.csv");

	// ブロックの生成、初期化
	GenerateBlocks();

	// ブロック3Dモデル生成
	modelBlock_ = Model::CreateFromOBJ("block", true);

	// 天球の生成
	skydome = new Skydome();

	// 天球の3Dモデル生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// 天球の初期化
	skydome->Initialize(modelSkydome_, &camera_);

	// 自機の生成
	player_ = new Player();

	// 自機の3Dモデル生成
	modelPlayer_ = Model::CreateFromOBJ("player", true);

	// 自機の初期化
	player_->Initialize(modelPlayer_,&camera_);
}

void GameScene::Update() {

	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}

			// ワールド行列の更新
			worldTransformBlock->matWorld_ = MakeAffineMatrix(worldTransformBlock->rotation_, worldTransformBlock->scale_, worldTransformBlock->translation_);

			// 転送
			worldTransformBlock->TransferMatrix();
		}
	}

	// 天球の更新
	skydome->Update();

	// 自機の更新
	player_->Update();

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

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			if (!worldTransformBlock) {
				continue;
			}

			modelBlock_->Draw(*worldTransformBlock, camera_);
		}
	}

	// 自機の描画
	player_->Draw();

	// 天球の描画
	skydome->Draw();

	// 3Dモデル描画終了
	Model::PostDraw();
}

void GameScene::GenerateBlocks() {

	// 要素数
	const uint32_t kNumBlockVirtical = mapChipField_->GetNumBlockVirtical();
	const uint32_t kNumBlockHorizontal = mapChipField_->GetNumBlockHorizontal();

	// 要素数を変更
	// 列数を指定(縦)
	worldTransformBlocks_.resize(kNumBlockVirtical);
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		// 列ごとの要素数を指定(横)
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				worldTransformBlocks_[i][j] = new KamataEngine::WorldTransform();
				worldTransformBlocks_[i][j]->Initialize();
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}
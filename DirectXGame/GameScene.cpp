#include "GameScene.h"
#include "2d/ImGuiManager.h"

using namespace KamataEngine;

GameScene::GameScene() {}

GameScene::~GameScene() {

	// スプライトの解放
	delete sprite_;

	// 3Dモデルの解放
	delete model_;

	// デバッグ用カメラの解放
	delete debugCamera_;
}

void GameScene::Initialize() {

	// 画像読み込み
	grHandleSushi_ = TextureManager::Load("./Resources/Images/sushi.png");

	// SE読み込み
	seHandleMokugyo = Audio::GetInstance()->LoadWave("./Resources/mokugyo.wav");

	// スプライト生成
	sprite_ = Sprite::Create(grHandleSushi_, {50.0f, 50.0f});

	// 3Dモデル生成
	model_ = Model::Create();

	// ワールド行列初期化
	worldTransform_.Initialize();

	// カメラ初期化
	camera_.Initialize();

	// ライン描画が参照するカメラを指定
	PrimitiveDrawer::GetInstance()->SetCamera(&camera_);

	// デバッグ用カメラ生成
	debugCamera_ = new DebugCamera(1280, 720);

	// 軸方向の表示を有効化
	AxisIndicator::GetInstance()->SetVisible(true);

	// 軸方向表示が参照するビュープロジェクションを指定
	AxisIndicator::GetInstance()->SetTargetCamera(&debugCamera_->GetCamera());
}

void GameScene::Update() {

	// スプライトの現在座標を取得
	Vector2 position = sprite_->GetPosition();

	// 座標を{ 2,1 }移動
	position.x += 2.0f;
	position.y += 1.0f;

	// 移動した結果を反映
	sprite_->SetPosition(position);

	// スペースキーでSE木魚再生
	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {
		Audio::GetInstance()->PlayWave(seHandleMokugyo, false, 1.0f);
	}

#ifdef _DEBUG

	// デバッグ用カメラ更新処理
	debugCamera_->Update();

	// ImGui受付開始
	ImGui::Begin("Debug1");

	// デバッグ用テキスト表示
	ImGui::Text("sushi syouhi kigen %d.%d.%d", 2025, 12, 15);

	// ImGui受付終了
	ImGui::End();

#endif // DEBUG
}

void GameScene::Draw() {

	// スプライト描画開始
	Sprite::PreDraw();

	// スプライト描画
	// sprite_->Draw();

	// スプライト描画終了
	Sprite::PostDraw();

	// 3Dモデル描画開始
	Model::PreDraw();

	// 3Dモデル描画
	model_->Draw(worldTransform_, debugCamera_->GetCamera(), grHandleSushi_);

	// 3Dモデル描画終了
	Model::PostDraw();

	// ラインを描画
	PrimitiveDrawer::GetInstance()->DrawLine3d({0.0f, 0.0f, 0.0f}, {0.0f, 10.0f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f});
}
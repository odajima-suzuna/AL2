#include <Windows.h>
#include <kamataEngine.h>
#include "GameScene.h"

using namespace KamataEngine;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	
	// エンジン初期化
	KamataEngine::Initialize(L"LC1A_04_オダジマ_スズナ_");

	// DirectXCommonインスタンス取得
	DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	// ImGuiManagerインスタンス取得
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();

	// ゲームシーンインスタンス生成
	GameScene* gameScene = new GameScene();

	// ゲームシーン初期化.
	gameScene->Initialize();

	// メインループ
	while (true) {

		// エンジン更新
		if (KamataEngine::Update()) {
			break;
		}

		// ===============================================
		// 更新処理
		// ===============================================
		
		// ImGui受付開始
		imguiManager->Begin();

		// ゲームシーン更新
		gameScene->Update();

		// imGui受付終了
		imguiManager->End();

		// ===============================================
		// 描画処理
		// ===============================================

		// 描画開始
		dxCommon->PreDraw();

		// ゲームシーン描画
		gameScene->Draw();

		// 軸表示描画
		AxisIndicator::GetInstance()->Draw();

		// ImGui描画
		imguiManager->Draw();

		// 描画終了
		dxCommon->PostDraw();
	}

	// ゲームシーンの解放
	delete gameScene;
	gameScene = nullptr;

	// エンジンの終了処理
	KamataEngine::Finalize();

	return 0;
}

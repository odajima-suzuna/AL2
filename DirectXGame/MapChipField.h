#pragma once
#include "KamataEngine.h"

enum class MapChipType {
	kBlank, // 空白
	kBlock, // ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {
public: /*public変数*/
private: /*private変数*/
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	// ブロックの個数
	static inline const uint32_t kNumBlockVirtical = 20;
	static inline const uint32_t kNumBlockHorizontal = 100;

	// マップチップデータ
	MapChipData mapChipData_;

public: /*public関数*/
	/// <summary>
	/// コンストラクタ
	/// </summary>
	MapChipField();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~MapChipField();

	/// <summary>
	/// マップチップデータファイルの読み込み
	/// </summary>
	/// <param name="filePath">ファイルパス</param>
	void LoadMapChipCsv(const std::string& filePath);

	// ゲッター ======================================================================================

	/// <summary>
	/// マップチップ種別の取得
	/// </summary>
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	/// <summary>
	/// マップチップ座標の取得
	/// </summary>
	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);

	/// <summary>
	/// 要素数を取得
	/// </summary>
	const uint32_t GetNumBlockVirtical() const { return kNumBlockVirtical; }
	
	/// <summary>
	/// 要素数を取得
	/// </summary>
	const uint32_t GetNumBlockHorizontal() const { return kNumBlockHorizontal; }

private: /*private関数*/
	/// <summary>
	/// マップチップデータをリセット
	/// </summary>
	void ResetMapChipData();
};
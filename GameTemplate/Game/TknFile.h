#pragma once
class TknFile
{
public:
	/// @brief tknファイルのヘッダー
	struct StHeader
	{
		/// @brief セルの数
		std::uint32_t numCell;
	};


	struct StCell {
		/// @brief セルの頂点
		Vector3 vertexPosition[3] = { g_vec3Zero,g_vec3Zero,g_vec3Zero };
		/// @brief セルの法線
		Vector3 normal = g_vec3Zero;
		/// @brief 隣接セルの番号
		std::int32_t linkCellNo[3];
	};

	/// @brief tknファイルをロードする
	/// @param filePath tknファイルのファイルパス
	/// @return trueでロード成功 falseでロード失敗
	bool Load(const char* filePath);

	int GetNumCell() const
	{
		return m_header.numCell;
	}

	const StCell& GetCell(int cellNo) const
	{
		return m_cellArray.at(cellNo);
	}

private:
	StHeader m_header;
	std::vector<StCell> m_cellArray;
};


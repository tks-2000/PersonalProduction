#pragma once
class TknFile
{
public:
	/// @brief tkn�t�@�C���̃w�b�_�[
	struct StHeader
	{
		/// @brief �Z���̐�
		std::uint32_t numCell;
	};


	struct StCell {
		/// @brief �Z���̒��_
		Vector3 vertexPosition[3] = { g_vec3Zero,g_vec3Zero,g_vec3Zero };
		/// @brief �Z���̖@��
		Vector3 normal = g_vec3Zero;
		/// @brief �אڃZ���̔ԍ�
		std::int32_t linkCellNo[3];
	};

	/// @brief tkn�t�@�C�������[�h����
	/// @param filePath tkn�t�@�C���̃t�@�C���p�X
	/// @return true�Ń��[�h���� false�Ń��[�h���s
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


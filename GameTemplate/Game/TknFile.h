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


	struct SCell {
		/// @brief �Z���̒��_
		Vector3 vertexPosition[3];
		/// @brief �Z���̖@��
		Vector3 normal;
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

	const SCell& GetCell(int cellNo) const
	{
		return m_cellArray.at(cellNo);
	}

private:
	StHeader m_header;
	std::vector<SCell> m_cellArray;
};


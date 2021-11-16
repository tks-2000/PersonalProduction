#pragma once
#include "Cell.h"
#include "BSP.h"

class TknFile;
namespace nsAI {

	class Cell;

	/// @brief �i�r�Q�[�V�������b�V����ǂݍ��ރN���X
	class NaviMesh
	{
	public:
		/// @brief tkn�t�@�C������i�r�Q�[�V�������b�V�����\�z����
		/// @param tknFilePath 
		void Init(const char* tknFilePath);

		/// @brief �w�肵�����W�ɍł��߂��Z������������
		/// @param pos 
		/// @return 
		const Cell& FindNearestCell(const Vector3& pos) const;

		/// @brief �Z���̐����擾
		/// @return 
		int GetNumCell() const
		{
			return static_cast<int>(m_cellArray.size());
		}

		/// @brief �Z�����擾
		/// @param cellNo 
		/// @return 
		const Cell& GetCell(int cellNo) const
		{
			return m_cellArray.at(cellNo);
		}

	private:
		std::vector<Cell> m_cellArray;
		BSP m_cellCenterPosBSP;
	};

}
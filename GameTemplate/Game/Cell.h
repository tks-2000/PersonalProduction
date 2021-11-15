#pragma once

class TknFile;

namespace nsAI {
	class Cell
	{
	public:

		/// @brief ���_���W��ݒ�
		/// @param vertNo 
		/// @param pos 
		void SetVertexPosition(int vertNo, const Vector3& pos)
		{
			m_vertexPosition[vertNo] = pos;
		}

		/// @brief �@����ݒ�
		/// @param normal �ݒ肷��@��
		void SetNormal(const Vector3& normal)
		{
			m_normal = normal;
		}

		/// @brief �אڃZ������ݒ�
		/// @param linkNo �אڔԍ� (0�`2)
		/// @param linkCell �אڃZ��
		void SetLinkCell(int linkNo, Cell* linkCell) {
			m_linkCell[linkNo] = linkCell;
				
		}

		/// @brief �Z���̒��S���W��ݒ�
		/// @param centerPos �ݒ肷�钆�S���W
		void SetCenterPosition(const Vector3& centerPos)
		{
			m_centerPos = centerPos;
		}
		
		/// @brief �Z���̒��S���W�����
		/// @return �Z���̒��S���W
		const Vector3& GetCenterPosition()const
		{
			return m_centerPos;
		}

		/// @brief �Z���ԍ���ݒ�
		/// @param no �ݒ肷��ԍ�
		void SetCellNo(int no)
		{
			m_no = no;
		}

		/// @brief �Z���ԍ������
		/// @return �Z���ԍ�
		int GetCellNo() const
		{
			return m_no;
		}

		/// @brief �אڃZ�����擾
		/// @param linkCellNo �אڃZ���ԍ�
		/// @return 
		Cell* GetLinkCell(int linkCellNo)const
		{
			return m_linkCell[linkCellNo];
		}

		/// @brief �Z���̒��_���W�����
		/// @param vertNo ���_�ԍ�
		/// @return ���_���W
		const Vector3& GetVertexPosition(int vertNo) const
		{
			return m_vertexPosition[vertNo];
		}

	private:
		Vector3 m_vertexPosition[3];
		Vector3 m_normal;
		Vector3 m_centerPos;
		Cell* m_linkCell[3] = { nullptr };
		int m_no = 0;
	};

}
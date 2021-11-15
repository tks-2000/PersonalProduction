#pragma once
class BSP
{
private:
	/// @brief ����
	struct StPlane {
		Vector3 normal = g_vec3Zero;
		float distance;
	};
public:
	/// @brief BSP�c���[�̗v�f�̎��
	enum EnEntityType {
		enEntityType_Node,
		enEntityType_Leaf,
		enEntityType_LeafList
	};

	/// @brief BSP�c���[�̗v�f
	struct StEntity {
		int type = enEntityType_Node;
	};

	using StEntityPtr = std::shared_ptr<StEntity>;

	/// @brief �m�[�h
	struct StNode : public StEntity
	{
		StPlane plane;
		StEntityPtr rightEntity;
		StEntityPtr leftEntity;
		Vector3 centerPos;
		std::vector<StEntityPtr> leafArray;
	};

	/// @brief ���[�t
	struct StLeaf : public StEntity
	{
		Vector3 position;
		void* extraData;
	};

	/// @brief ���[�t�̃��X�g
	struct StLeafList : public StEntity {
		std::vector<StEntityPtr> leafList;
	};

private:
	StEntityPtr m_rootNode = nullptr;
	std::vector<StEntityPtr> m_leafArray;
public:
	/// @brief ���[�t��ǉ�
	/// @param position 
	/// @param extraData 
	void AddLeaf(const Vector3& position, void* extraData)
	{
		auto newEntity = std::make_shared<StLeaf>();
		m_leafArray.emplace_back(newEntity);
		StLeaf* leaf = static_cast<StLeaf*>(newEntity.get());
		leaf->position = position;
		leaf->extraData = extraData;
		leaf->type = enEntityType_Leaf;

	}

	/// @brief BVH���\�z
	void Build();

	/// @brief BSP�c���[��T�����ă��[�t�ɓ��B����ƁA�����Ŏw�肳�ꂽ�R�[���o�b�N�֐����Ă΂�܂��B
	/// @param pos ���W
	/// @param onEndWalk �T�����I���������ɌĂ΂�鏈��
	void WalkTree(const Vector3& pos, std::function<void(StLeaf* leaf)> onEndWalk) const;
private:

	/// @brief ���ʂŃ��[�t�m�[�h�𕪊����Ă���
	void SplitLeafArray(
		std::vector<StEntityPtr>& leftLeafArray,
		std::vector<StEntityPtr>& rightLeafArray,
		const StPlane& plane,
		const std::vector<StEntityPtr>& leafArray
	);

	void CalcSplitPlaneFromCovarianceMatrix(
		StPlane& plane,
		float covarianceMatrix[3][3],
		const Vector3& centerPos,
		const std::vector<StEntityPtr>& leafArray
	);

	/// @brief ���[�t�m�[�h�̔z�񂩂狤���U�s����v�Z����
	/// @param covarianceMatrix �����U�s��̌v�Z��
	/// @param leafArray ���[�t�m�[�h�̔z��
	/// @param centerPos ���[�t�m�[�h�̒��S���W
	void CalcCovarianceMatrixFromLeafNodeList(
		float covarianceMatrix[3][3],
		const std::vector<StEntityPtr>& leafArray,
		const Vector3& centerPos
	);

	/// @brief ���[�t�̃��X�g���璆�S���W���v�Z����
	/// @param leafArray 
	/// @return 
	Vector3 CalcCenterPositionFromLeafList(
		const std::vector<StEntityPtr>& leafArray
	);

	/// @brief �V����BSP�c���[�̗v�f���쐬����
	/// @param leafArray 
	/// @return 
	StEntityPtr CreateBSPTreeEntity(const std::vector<StEntityPtr>& leafArray);

	/// @brief BSP�c���[��LeafList�v�f���쐬����
	/// @param leafArray 
	/// @return 
	StEntityPtr CreateBSPTreeEntity_LeafList(const std::vector<StEntityPtr>& leafArray);

	void WalkTree(StEntityPtr entity, const Vector3& pos, std::function<void(StLeaf* leaf)> onEndWalk) const;
};


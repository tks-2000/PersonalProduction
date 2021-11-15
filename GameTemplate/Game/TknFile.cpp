#include "stdafx.h"
#include "TknFile.h"


bool TknFile::Load(const char* filePath)
{
	auto fp = fopen(filePath, "rb");
	if (fp == nullptr) {
		//�t�@�C���I�[�v�����s
		return false;
	}
	//�w�b�_�[�����[�h
	fread(&m_header, sizeof(m_header), 1, fp);

	//�Z���̔z����m��
	m_cellArray.resize(m_header.numCell);

	//�Z���̏������[�h
	fread(&m_cellArray.front(), sizeof(SCell) * m_header.numCell, 1, fp);

	//�t�@�C�������
	fclose(fp);
}
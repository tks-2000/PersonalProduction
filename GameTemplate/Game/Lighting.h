#pragma once
#include "math.h"
#include "stdafx.h"
#include "DirectionLight.h"
#include "PointLight.h"
#include "SpotLight.h"

namespace render {
	namespace light {
		/// @brief �f�B���N�V�������C�g�̐�
		static const int DIRECTION_LIGHT_SUM = 4;
		/// @brief �|�C���g���C�g�̐�
		static const int POINT_LIGHT_SUM = 5;
		/// @brief �X�|�b�g���C�g�̐�
		static const int SPOT_LIGHT_SUM = 4;


		/// @brief �f�B���N�V�������C�g�\����
		//struct DirectionLight
		//{
		//	Vector3 direction = Vector3::Zero;	//���C�g�̕���
		//	float pad0 = 0.0f;					//�p�f�B���O
		//	Vector3 color = Vector3::Zero;		//���C�g�̃J���[
		//	float pad1 = 0.0f;					//�p�f�B���O

		//};

		/// @brief �|�C���g���C�g�\����
		//struct PointLight
		//{
		//	Vector3 position = Vector3::Zero;	//�ʒu
		//	float pad0 = 0.0f;					//�p�f�B���O
		//	Vector3 color = Vector3::Zero;		//�J���[
		//	float Range = 0.0f;					//�e���͈�

		//};

		/// @brief �X�|�b�g���C�g�\����
		//struct SpotLight
		//{
		//	Vector3 position = Vector3::Zero;	//�ʒu
		//	float pad0 = 0.0f;					//�p�f�B���O
		//	Vector3 color = Vector3::Zero;		//�J���[
		//	float Range = 0.0f;					//�e���͈�
		//	Vector3 direction = Vector3::Zero;	//�ˏo����
		//	float angle = 0.0f;					//�ˏo�p�x

		//};

		/// @brief �������C�g�\����
		struct HemiSphereLight
		{
			Vector3 groundColor = Vector3::Zero;	//�n�ʐF
			float pad0 = 0.0f;						//�p�f�B���O
			Vector3 skyColor = Vector3::Zero;		//�V���F
			float pad1 = 0.0f;						//�p�f�B���O
			Vector3 groundNormal = Vector3::Zero;	//�n�ʂ̖@��
			float pad2 = 0.0f;						//�p�f�B���O
		};

		/// @brief ���C�g�S�Ă̍\����
		struct Light
		{
			StDirectionLight directionLight[DIRECTION_LIGHT_SUM];			//�f�B���N�V�������C�g
			StPointLight pointLight[POINT_LIGHT_SUM];					//�|�C���g���C�g
			StSpotLight spotLight[SPOT_LIGHT_SUM];					//�X�|�b�g���C�g
			HemiSphereLight hemiSphereLight;		//�������C�g
			Vector3 eyePos = Vector3::Zero;			//���_�̈ʒu
			float pad4 = 0.0f;						//�p�f�B���O
			Vector3 ambientlight = Vector3::Zero;	//����
			float pad5 = 0.0f;
		};

		/// @brief ���C�e�B���O���s���N���X
		class Lighting : public IGameObject
		{
		public:
			Lighting();
			~Lighting();
			bool Start();
			void Update();

			void Init();
			void Execution();


			Light& GetLight() { return m_light; }

			/// @brief ���C�g�̍\���̂����
			/// @return ���C�g�\���̂̃A�h���X
			Light* GetLightAddress() { return &m_light; }

			void SetAmbientLight(const Vector3& color) { m_light.ambientlight = color; }

			/// @brief �f�B���N�V�������C�g�̕��������
			/// @return �f�B���N�V�������C�g�̕���
			Vector3 GetDirectionLightDirection() { return m_light.directionLight[0].direction; }

			/// @brief �f�B���N�V�������C�g�̕�����ݒ�
			/// @param dirLigVec �f�B���N�V�������C�g�ɐݒ肷�����
			void SetDirectionLightDirection(const int num, const Vector3& dirLigVec) { m_directionLight[num].SetDirection(dirLigVec); }

			/// @brief �f�B���N�V�������C�g�̃J���[��ݒ�
			/// @param color �f�B���N�V�������C�g�ɐݒ肷��J���[
			void SetDirectionLightColor(const int num, const Vector3& color) { m_directionLight[num].SetColor(color); }

			void SetDirectionLightRotation(const int num, const Vector3& axis, const float angle) { m_directionLight[num].SetRotation(axis, angle); }

			void StopDirectionLightRotation(const int num) { m_directionLight[num].StopRotation(); }


			/// @brief �|�C���g���C�g�̍��W�����
			/// @return �|�C���g���C�g�̍��W
			Vector3 GetPointLightPos(int num) { return m_light.pointLight[num].position; }

			/// @brief �|�C���g���C�g�̍��W��ݒ�
			/// @param pos �|�C���g���C�g�ɐݒ肷����W
			void SetPointLighitPos(const int num, const Vector3& pos) { m_pointLight[num].SetPosition(pos); }

			/// @brief �|�C���g���C�g�̃J���[��ݒ�
			/// @param color �|�C���g���C�g�ɐݒ肷����W
			void SetPointLightColor(const int num, const Vector3& color) { m_pointLight[num].SetColor(color); }

			/// @brief �|�C���g���C�g�̉e���͈͂�ݒ�
			/// @param num �ݒ肵�����|�C���g���C�g�̔ԍ�
			/// @param range �|�C���g���C�g�ɐݒ肷��e���͈�
			void SetPointLightRange(const int num, const float range) { m_pointLight[num].SetRange(range); }

			void SetPointLightBlinking(const int num, const float interval) { m_pointLight[num].SetBlinking(interval); }

			void StartPointLightBlinking(const int num) { m_pointLight[num].StartBlinking(); }

			void StopPointLightBlinking(const int num) { m_pointLight[num].StopBlinking(); }

			void SetPointLightGradation(const int num, std::vector<Vector3>& colors, const float speed) { m_pointLight[num].SetGradation(colors, speed); }

			void StartPointLightGradation(const int num) { m_pointLight[num].StartGradation(); }

			void StopPointLightGradation(const int num) { m_pointLight[num].StopGradation(); }
			/// @brief �X�|�b�g���C�g�̍��W�����
			/// @param num ���肷��X�|�b�g���C�g�̔ԍ�
			/// @return �X�|�b�g���C�g�̍��W
			const Vector3& GetSpotLightPos(int num) { return m_light.spotLight[num].position; }

			/// @brief �X�|�b�g���C�g�̍��W��ݒ�
			/// @param num �ݒ肵�����X�|�b�g���C�g�̔ԍ�
			/// @param pos �X�|�b�g���C�g�ɐݒ肷����W
			void SetSpotLightPos(const int num, const Vector3& pos) { m_spotLight[num].SetPosition(pos); }

			void SetSpotLightTarget(const int num, const Vector3& target) { m_spotLight[num].SetTarget(target); }

			/// @brief �X�|�b�g���C�g�̃J���[��ݒ�
			/// @param num �ݒ肵�����X�|�b�g���C�g�̔ԍ�
			/// @param color �X�|�b�g���C�g�ɐݒ肷��J���[
			void SetSpotLightColor(const int num, const Vector3& color) { m_spotLight[num].SetColor(color); }

			void SetSpotLightRange(const int num, const float range) { m_spotLight[num].SetRange(range); }

			
			/// @brief �X�|�b�g���C�g�̕�����ݒ�
			/// @param num �ݒ肵�����X�|�b�g���C�g�̔ԍ�
			/// @param dir �X�|�b�g���C�g�ɐݒ肷�����
			void SetSpotLightDirection(const int num, const Vector3& dir) { m_spotLight[num].SetDirection(dir); }

			void SetSpotLightAngle(const int num, const float angle) { m_spotLight[num].SetAngle(angle); }

			/// @brief �������C�g�̏�����
			void InitHemiSphereLight();

			void SetHemiSphereLifhtGroundColor(const Vector3& groundColor) { m_light.hemiSphereLight.groundColor = groundColor; }

			void SetHemiSphereLifhtSkyColor(const Vector3& skyColor) { m_light.hemiSphereLight.skyColor = skyColor; }

		private:
			//�������t���O
			bool m_isInitd = false;

			/// @brief ���C�e�B���O�S�Ẵf�[�^
			Light m_light;

			DirectionLight m_directionLight[DIRECTION_LIGHT_SUM];

			PointLight m_pointLight[POINT_LIGHT_SUM];

			SpotLight m_spotLight[SPOT_LIGHT_SUM];
		};
	}
}

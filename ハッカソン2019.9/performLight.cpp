//=============================================================================
//
// �X�|�b�g���C�g/�|�C���g���C�g���� [performLight.cpp]
// Author : ���R���
//
//=============================================================================
#include "performLight.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// ���C�g�N���X�̃R���X�g���N�^
//=============================================================================
CPerformLight::CPerformLight()
{
	// �l�̃N���A
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));	// ���C�g���N���A����
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu���N���A
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPerformLight::~CPerformLight()
{
}

//=============================================================================
// ���C�g�̐�������
//=============================================================================
CPerformLight *CPerformLight::Create(D3DXVECTOR3 pos, TYPE type)
{
	CPerformLight *pPerformLight = NULL;

	if (pPerformLight == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pPerformLight = new CPerformLight;

		if (pPerformLight != NULL)
		{
			pPerformLight->m_pos = pos;
			pPerformLight->m_type = type;

			pPerformLight->Init();
		}
	}

	return pPerformLight;
}

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void CPerformLight::Init(void)
{
	D3DXVECTOR3 vecDir;

	// �f�o�C�X�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���C�g���N���A����
	ZeroMemory(&m_light, sizeof(D3DLIGHT9));

	// ���C�g�̎�ނ�ݒ�
	switch (m_type)
	{
		// �|�C���g���C�g
	case TYPE_POINT:
		m_light.Type = D3DLIGHT_POINT;
		break;

		// �X�|�b�g���C�g
	case TYPE_SPOT:
		m_light.Type = D3DLIGHT_SPOT;
		break;
	}

	// ���C�g�����˂���f�B�t���[�Y�F��ݒ�
	m_light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �X�y�L�����[�F(�P�����ʂ��o������)??
	m_light.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//����(����������Ȃ������֊ԐړI�ɓ�������̋���)??
	m_light.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �����̈ʒu��ݒ�
	m_light.Position = m_pos;

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vecDir, &vecDir);		//���K���ɂ���
	m_light.Direction = vecDir;

	// �����̗L��������ݒ�
	m_light.Range = 500.0f;

	// �悭�킩��񂯂ǊJ���҂̑�����1.0f��ݒ肵�Ă�炵��
	m_light.Falloff = 1.0f;

	//���C�g�̋��x(1��2��0.0f�ɂ��邱�ƂŌ������Ȃ����ɂȂ�)
	m_light.Attenuation0 = 1.0f;
	m_light.Attenuation1 = 0.0f;
	m_light.Attenuation2 = 0.0f;

	//�����R�[���i�悭����������ꏊ�j
	m_light.Theta = D3DXToRadian(30.0f);

	//�O���R�[���i�኱����������ꏊ�j
	m_light.Phi = D3DXToRadian(50.0f);

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &m_light);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, true);
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void CPerformLight::Uninit(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void CPerformLight::Update(void)
{
}
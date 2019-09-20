//=============================================================================
//
// ���C�g���� [light.cpp]
// Author : ���R���
//
//=============================================================================
#include "light.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
D3DLIGHT9 CLight::m_light[MAX_LIGHT] = {};

//=============================================================================
// ���C�g�N���X�̃R���X�g���N�^
//=============================================================================
CLight::CLight()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CLight::~CLight()
{
}

//=============================================================================
// ���C�g�̏���������
//=============================================================================
void CLight::Init(void)
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

	for (int nCntLight = 0; nCntLight < MAX_LIGHT; nCntLight++)
	{
		// ���C�g���N���A����
		ZeroMemory(&m_light[nCntLight], sizeof(D3DLIGHT9));
	}

	// ���C�g�̎�ނ�ݒ�
	m_light[0].Type = D3DLIGHT_DIRECTIONAL;
	m_light[1].Type = D3DLIGHT_DIRECTIONAL;
	m_light[2].Type = D3DLIGHT_DIRECTIONAL;

	// ���C�g�̊g�U����ݒ�
	m_light[0].Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_light[1].Diffuse = D3DXCOLOR(0.65f, 0.65f, 0.65f, 1.0f);
	m_light[2].Diffuse = D3DXCOLOR(0.15f, 0.15f, 0.15f, 1.0f);

	// ���C�g�̕����̐ݒ�
	vecDir = D3DXVECTOR3(0.2f, -0.8f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[0].Direction = vecDir;

	vecDir = D3DXVECTOR3(-0.2f, 0.8f, -0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[1].Direction = vecDir;

	vecDir = D3DXVECTOR3(0.9f, -0.1f, 0.4f);
	D3DXVec3Normalize(&vecDir, &vecDir);		// ���K������
	m_light[2].Direction = vecDir;

	// ���C�g��ݒ肷��
	pDevice->SetLight(0, &m_light[0]);
	pDevice->SetLight(1, &m_light[1]);
	pDevice->SetLight(2, &m_light[2]);

	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
}

//=============================================================================
// ���C�g�̏I������
//=============================================================================
void CLight::Uninit(void)
{
}

//=============================================================================
// ���C�g�̍X�V����
//=============================================================================
void CLight::Update(void)
{
}

//=============================================================================
// ���C�g�̎擾����
//=============================================================================
D3DLIGHT9 CLight::GetLight(int nIndex)
{
	return m_light[nIndex];
}
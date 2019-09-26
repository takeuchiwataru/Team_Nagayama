//=============================================================================
//
// �p�[�e�B�N���̏��� [particleX.cpp]
// Author : ���R���
//
//=============================================================================
#include "particleX.h"
#include "manager.h"
#include "renderer.h"
#include "resource.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 *CParticleX::m_pTexture = 0;			// �e�N�X�`�����

//=============================================================================
// �p�[�e�B�N���̐�������
//=============================================================================
CParticleX *CParticleX::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 move, int nLife, PARTICLE_TYPE type)
{
	CParticleX *pParticle = NULL;

	if (pParticle == NULL)
	{
		// �p�[�e�B�N���N���X�̐���
		pParticle = new CParticleX;

		if (pParticle != NULL)
		{
			pParticle->SetPosition(pos);					// �ʒu�̐ݒ�
			pParticle->m_move = move;						// �ړ��ʂ̐ݒ�
			pParticle->m_nLife = nLife;						// ���C�t�̐ݒ�
			pParticle->BindModel(CResource::GetBuffMat(CResource::MODEL_DEBRIS), CResource::GetNumMat(CResource::MODEL_DEBRIS), CResource::GetMesh(CResource::MODEL_DEBRIS));
			pParticle->BindMat(m_pTexture);
			pParticle->Init();								// ����������
			pParticle->SetRot(rot);							// ��]�̐ݒ�
			pParticle->m_ParticleType = type;				// ��ނ̐ݒ�
		}
	}
	return pParticle;
}

//=============================================================================
// �p�[�e�B�N���N���X�̃R���X�g���N�^
//=============================================================================
CParticleX::CParticleX() : CSceneX(PARTICLE_PRIORITY)
{
	// �l���N���A
	m_nLife = 0;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorld);		// ���[���h�}�g���b�N�X
	m_ParticleType = TYPE_NORMAL;
}

//=============================================================================
// �p�[�e�B�N���N���X�̃f�X�g���N�^
//=============================================================================
CParticleX::~CParticleX()
{
}

//=============================================================================
// �p�[�e�B�N���̏���������
//=============================================================================
HRESULT CParticleX::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PARTICLE);

	// ����������
	CSceneX::Init();

	// �^�C�v�̏����ݒ�
	m_ParticleType = TYPE_NORMAL;

	return S_OK;
}

//=============================================================================
// �p�[�e�B�N���̏I������
//=============================================================================
void CParticleX::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CSceneX::Uninit();
}

//=============================================================================
// �p�[�e�B�N���̍X�V����
//=============================================================================
void CParticleX::Update(void)
{
	// �ʒu���擾
	D3DXVECTOR3 pos;
	pos = CSceneX::GetPosition();
	
	pos -= m_move;
	m_nLife--;

	switch (m_ParticleType)
	{
		// �ʏ���
	case TYPE_NORMAL:
		break;
		// �㏸���
	case TYPE_UP:
		// �d�͌��Z
		m_move.y -= cosf(D3DX_PI * 0.0f) * 0.5f;
		break;
		// ���~���
	case TYPE_DOWN:
		// �d�͉��Z
		m_move.y += cosf(D3DX_PI * 0.0f) * 0.5f;
		break;
	}

	// �ʒu�̐ݒ�
	CSceneX::SetPosition(pos);

	if (m_nLife <= 0)
	{
		// ����
		Uninit();
	}
}

//=============================================================================
// �p�[�e�B�N���̕`�揈��
//=============================================================================
void CParticleX::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�@���̎������K��	�J�n
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CSceneX::Draw();

	// ���_�@���̎������K��	�I��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//=============================================================================
// �u���b�N�̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CParticleX::LoadMat(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}


	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

										// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)CResource::GetBuffMat(CResource::MODEL_DEBRIS)->GetBufferPointer();

	// �}�e���A���̐����e�N�X�`����������̂𓮓I�Ɋm��
	m_pTexture = new LPDIRECT3DTEXTURE9[CResource::GetNumMat(CResource::MODEL_DEBRIS)];

	for (int nCntMat = 0; nCntMat < (int)CResource::GetNumMat(CResource::MODEL_DEBRIS); nCntMat++)
	{
		// �����O�ɋ�ɂ���
		m_pTexture[nCntMat] = NULL;

		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// �e�N�X�`���̐���
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntMat]);
		}
	}

	return S_OK;
}

//=============================================================================
// �u���b�N�̃��f���������
//=============================================================================
void CParticleX::UnloadMat(void)
{
	if (m_pTexture != NULL)
	{// �e�N�X�`���̃|�C���^��NULL�`�F�b�N(��)
		for (int nCntMat = 0; nCntMat < (int)CResource::GetNumMat(CResource::MODEL_DEBRIS); nCntMat++)
		{
			if (m_pTexture[nCntMat] != NULL)
			{// �|�C���^�̒���NULL�`�F�b�N(�Ƌ�)
				m_pTexture[nCntMat]->Release();
				m_pTexture[nCntMat] = NULL;
			}
		}

		// �������̊J��(���)
		delete[] m_pTexture;
		// NULL�ɂ���(�X�n)
		m_pTexture = NULL;
	}
}
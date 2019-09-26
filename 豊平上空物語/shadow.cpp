//=============================================================================
//
// �e�̏���
// Author : ���R���
//
//=============================================================================
#include "shadow.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "scene.h"
#include "player.h"
#include "mask.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MODEL_SHADOW			"data\\MODEL\\shadow000.x"	//�e�N�X�`���̃t�@�C����

//--------------------------------------------
//�ÓI�����o�ϐ��錾
//--------------------------------------------
LPDIRECT3DTEXTURE9			CShadow::m_pTexture = NULL;
LPD3DXMESH CShadow::m_pMesh = NULL;			// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CShadow::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD CShadow::m_nNumMat = 0;				// �}�e���A�����̐�

//--------------------------------------------
//�V�[��3D�N���X �R���X�g���N�^
//--------------------------------------------
CShadow::CShadow() : CSceneX(SHADOW_PRIORITY)
{
	m_pos = D3DXVECTOR3(0, 0, 0);			//�ʒu
	m_rot = D3DXVECTOR3(0, 0, 0);		//����
	D3DXMatrixIdentity(&m_mtxWorld);	//���[���h�}�g���b�N�X
}

//--------------------------------------------
//�V�[��3D�N���X �f�X�g���N�^
//--------------------------------------------
CShadow::~CShadow()
{
}

//=============================================================================
// ��������
//=============================================================================
CShadow *CShadow::Create(D3DXVECTOR3 pos)
{
	CShadow *pShadow = NULL;

	if (pShadow == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pShadow = new CShadow;

		if (pShadow != NULL)
		{
			pShadow->m_pos = pos;
			pShadow->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pShadow->Init(); 
		}
	}

	return pShadow;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CShadow::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CSceneX::Init();

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_SHADOW);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CShadow::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CShadow::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CShadow::Draw(void)
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

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, true);	// �X�e���V���e�X�g��L���ɂ���

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);	// �����Ă��Ȃ���Ԃɂ���

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_ALWAYS);			// �X�e���V���̑ΏۂƂȂ���̂�S���L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_ZERO);						// �X�e���V���e�X�g�����i / Z�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_INCR);						// �X�e���V���e�X�g�����i / Z�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);						// �X�e���V���e�X�g���s���i

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);				// �J�����O�\

	// �`�揈��
	CSceneX::Draw();

	pDevice->SetRenderState(D3DRS_STENCILREF, 1);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// �X�e���V���̑ΏۂƂȂ���̂�1�ɂȂ��Ă�����̂�L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);						// �X�e���V���e�X�g�����i / Z�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_ZERO);						// �X�e���V���e�X�g�����i / Z�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_ZERO);						// �X�e���V���e�X�g���s���i

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O��

	// �`�揈��
	CSceneX::Draw();

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000f);	// �����Ă����Ԃɂ���

	pDevice->SetRenderState(D3DRS_STENCILREF, 2);
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// �X�e���V���̑ΏۂƂȂ���̂�2�ɂȂ��Ă�����̂�L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);						// �X�e���V���e�X�g�����i / Z�e�X�g���i
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);						// �X�e���V���e�X�g�����i / Z�e�X�g�s���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);						// �X�e���V���e�X�g���s���i

	// �}�X�N�̎擾
	CMask *pMask;
	pMask = CManager::GetMask();

	pMask->Draw();

	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_STENCILENABLE, false);	// �X�e���V���e�X�g�𖳌��ɂ���
}

//=============================================================================
// �ʒu�ݒ菈��
//=============================================================================
void CShadow::SetPos(D3DXVECTOR3 pos)
{
	CSceneX::SetPosition(pos);
}

//=============================================================================
// �e�N�X�`�����[�h����
//=============================================================================
HRESULT CShadow::Load(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_SHADOW,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}
//=============================================================================
// �e�N�X�`���j������
//=============================================================================
void CShadow::UnLoad(void)
{
	// ���b�V���̊J��
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// �}�e���A���̊J��
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}
//=============================================================================
//
// �S���ڍ����� [fullMeguro.cpp]
// Author : ���R���
//
//=============================================================================
#include "fullMeguro.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "resource.h"
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ROTATION_SPEED	(0.05f)					// �R�C���̉�]�X�s�[�h

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CFullMeguro::m_nNumCoin = 0;			// �R�C���̐�

//=============================================================================
// �R�C���N���X�̃R���X�g���N�^
//=============================================================================
CFullMeguro::CFullMeguro() : CSceneX(COIN_PRIORITY)
{
	// �l���N���A
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorld);		// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFullMeguro::~CFullMeguro()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CFullMeguro *CFullMeguro::Create(D3DXVECTOR3 pos)
{
	CFullMeguro *pCoin = NULL;

	if (pCoin == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pCoin = new CFullMeguro;

		if (pCoin != NULL)
		{
			pCoin->SetPosition(pos);
			pCoin->BindModel(CResource::GetBuffMat(CResource::MODEL_MEGURO), CResource::GetNumMat(CResource::MODEL_MEGURO), CResource::GetMesh(CResource::MODEL_MEGURO));
			pCoin->Init();

			m_nNumCoin++;
		}
	}

	return pCoin;
}

//=============================================================================
// �R�C������������
//=============================================================================
HRESULT CFullMeguro::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_COIN);

	// ����������
	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// �R�C���I������
//=============================================================================
void CFullMeguro::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �R�C���X�V����
//=============================================================================
void CFullMeguro::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	//CPlayer *pPlayer = NULL;
	//pPlayer = CGame::GetPlayer();

	//// �Q�[���̃��[�h���擾
	//CManager::MODE mode;
	//mode = CManager::GetMode();

	// �ʒu���擾
	m_pos = CSceneX::GetPosition();

	//m_rot.y += ROTATION_SPEED;

	//if (m_rot.y > D3DX_PI)
	//{
	//	m_rot.y -= D3DX_PI * 2.0f;
	//}
	//if (m_rot.y < -D3DX_PI)
	//{
	//	m_rot.y += D3DX_PI * 2.0f;
	//}

	//if (pPlayer->GetMove().y >= 0.0f)
	//{
	//	m_pos.y -= 0.0f;
	//}
	//else if (pPlayer->GetMove().y < -15.0f)
	//{
	//	m_pos.y += pPlayer->GetMove().y + 10.0f;
	//}

	//SetRot(m_rot);

	SetPosition(m_pos);

#ifdef _DEBUG
	CDebugProc::Print("cf", "�ڍ��̈ʒu : ", m_pos.x);
#endif
}

//=============================================================================
// �R�C���`�揈��
//=============================================================================
void CFullMeguro::Draw(void)
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
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CFullMeguro::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CFullMeguro::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �R�C���̐��̎擾
//=============================================================================
int CFullMeguro::GetNumCoin(void)
{
	return m_nNumCoin;
}

//=============================================================================
// �R�C���̐��̐ݒ�
//=============================================================================
void CFullMeguro::SetNumCoin(int nNumCoin)
{
	m_nNumCoin = nNumCoin;
}
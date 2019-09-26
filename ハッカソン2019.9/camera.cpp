//=============================================================================
//
// �J�������� [camera.cpp]
// Author : ���R���
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "player.h"
#include "game.h"
#include "coin.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define CAMERA_SPEED	(4.0f)
#define GEM_TIMER		(100)
#define GEM_V			(D3DXVECTOR3(1160.0f, 100.0f, 1000.0f))	// ��΂̃J�����̈ʒu
#define GEM_R			(D3DXVECTOR3(1160.0f, 20.0f, 720.0f))	// ��΂̃J�����̈ʒu
#define DEST_R			(20.0f)	// �����_�̂���
#define DEST_R_Y		(40.0f)	// �����_�̂���

//*****************************************************************************
// �ÓI�����o�ϐ��錾
//*****************************************************************************

//=============================================================================
// �J�����N���X�̃R���X�g���N�^
//=============================================================================
CCamera::CCamera()
{
	m_posV = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̎��_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̒����_
	m_recU = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̌���
	m_fLength = 0.0f;
	m_nGemTimer = 0;
	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCamera::~CCamera()
{
}

//=============================================================================
// �J�����̏���������
//=============================================================================
void CCamera::Init(void)
{
	m_posV = D3DXVECTOR3(0.0f, 120.0f, -220.0f);	// ���_
	m_posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����_
	m_posVDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̎��_
	m_posRDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̒����_
	m_recU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړI�̌���
	m_DiffAngle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fLength = sqrtf((m_posV.x - m_posR.x) * (m_posV.x - m_posR.x) + (m_posV.z - m_posR.z) * (m_posV.z - m_posR.z));
	m_nGemTimer = 0;

	CManager::MODE mode;
	mode = CManager::GetMode();


	m_posV = D3DXVECTOR3(0.0f, 70000.0f, -400.0f);	// ���_
	m_posR = D3DXVECTOR3(0.0f, 69950.0f, 0.0f);		// �����_

}

//=============================================================================
// �J�����̏I������
//=============================================================================
void CCamera::Uninit(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void CCamera::Update(void)
{
	CManager::MODE mode;
	mode = CManager::GetMode();

	/*CPlayer *pPlayer;
	mode = CManager::GetMode();*/

	if (mode == CManager::MODE_GAME || mode == CManager::MODE_TUTORIAL)
	{
		PlayerCamera();

		/*if()*/
	}

	if (mode == CManager::MODE_TITLE)
	{
		m_posV = D3DXVECTOR3(700.0f, -100.0f, -1500.0f);	// ���_
		m_posR = D3DXVECTOR3(700.0f, -100.0f, 0.0f);		// �����_
	}
	if (mode == CManager::MODE_RANKING)
	{
		m_posV = D3DXVECTOR3(1010.0f, -330.0f, -1600.0f);	// ���_
		m_posR = D3DXVECTOR3(1010.0f, -330.0f, -100.0f);		// �����_
	}
	if (mode == CManager::MODE_GAMECLEAR || mode == CManager::MODE_GAMEOVER)
	{
		m_posV = D3DXVECTOR3(1010.0f, -330.0f, -2500.0f);	// ���_
		m_posR = D3DXVECTOR3(1010.0f, -330.0f, -1000.0f);		// �����_
	}
#ifdef _DEBUG
	CDebugProc::Print("cfccfccfc", "posV     : x", m_posV.x, "f", "   y", m_posV.y, "f", " z", m_posV.z, "f");
	CDebugProc::Print("cfccfccfc", "posR     : x", m_posR.x, "f", "   y", m_posR.y, "f", " z", m_posR.z, "f");
#endif
}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void CCamera::SetCamera(void)
{
	// �f�o�C�X�̎擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X���쐬
	D3DXMatrixPerspectiveFovLH(&m_mtxProjection,
		D3DXToRadian(45.0f),						// ����p
		(float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,	// ��ʔ䗦	
		100.0f,										// �J��������̋����i��O�j
		10000.0f);									// �J��������̋����i���j

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_mtxProjection);

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxView);

	// �r���[�}�g���b�N�X���쐬
	D3DXMatrixLookAtLH(&m_mtxView,
		&m_posV,
		&m_posR,
		&m_recU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &m_mtxView);
}

//=============================================================================
// �p�x�̐ݒ�
//=============================================================================
void CCamera::SetAngle(void)
{
	if (m_DiffAngle.y > D3DX_PI)
	{
		m_DiffAngle.y -= D3DX_PI * 2.0f;
	}
	if (m_DiffAngle.y < -D3DX_PI)
	{
		m_DiffAngle.y += D3DX_PI * 2.0f;
	}
	//
	m_rot.y += m_DiffAngle.y * 0.2f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//=============================================================================
// �v���C���[�Ǐ]����
//=============================================================================
void CCamera::PlayerCamera(void)
{
	CScene *pScene = NULL;

	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �擪�̃I�u�W�F�N�g���擾(���f���̗D�揇�ʂ�1������A1�ɂ���I�u�W�F�N�g�����ׂČ���)
	pScene = CScene::GetTop(PLAYER_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
			 // �f�o�b�N�p
#if 0
#endif
#if 1
				m_posRDest.y = (((CPlayer*)pScene)->GetPos().y + 50.0f) - sinf(((CPlayer*)pScene)->GetRot().x) * DEST_R_Y;
				//
				m_posVDest.y = ((CPlayer*)pScene)->GetPos().y - sinf(m_rot.x) * m_fLength + 50.0f;

				//����
				m_posR.y += (m_posRDest.y - m_posR.y) * 0.2f + ((CPlayer*)pScene)->GetMove().y - 20.0f;

				m_posV.y = m_posR.y + sinf(D3DX_PI + m_rot.x) * m_fLength + 100.0f;

				// ���͏����擾
				CInputJoypad *pInputJoypad;
				pInputJoypad = CManager::GetInputJoypad();

				// ���͏����擾
				CInputKeyboard *pInputKeyboard;
				pInputKeyboard = CManager::GetInputKeyboard();

				//�����̊���
				m_DiffAngle.y = m_rotDest.y - m_rot.y;

				//�p�x�̐ݒ�
				SetAngle();
#endif
			}
		}

		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}
}

//=============================================================================
// �����̎擾
//=============================================================================
D3DXVECTOR3 CCamera::GetRot(void)
{
	return m_rot;
}
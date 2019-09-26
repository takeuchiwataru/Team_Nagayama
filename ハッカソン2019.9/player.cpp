//=============================================================================
//
// �v���C���[���� [player.cpp]
// Author : ���R���
//
//=============================================================================
#include "player.h"
#include "input.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "game.h"
#include "tutorial.h"
#include "goal.h"
#include "particle2D.h"
#include "particle3D.h"
#include "particleX.h"
#include "coin.h"
#include "score.h"
#include "field.h"
#include "sound.h"
#include "light.h"
#include "life.h"
#include "shadow.h"
#include "text.h"
#include "resource.h"
#include "health.h"
#include "onararemain.h"
#include "BAnimation.h"
#include "obstacle.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPD3DXMESH CPlayer::m_apMesh[MAX_PLAYER] = {};			// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CPlayer::m_apBuffMat[MAX_PLAYER] = {};	// �}�e���A�����ւ̃|�C���^
DWORD CPlayer::m_anNumMat[MAX_PLAYER] = {};				// �}�e���A�����̐�
CPlayer::STATE CPlayer::m_State = CPlayer::STATE_NORMAL;
bool CPlayer::m_bGoal = false;
bool CPlayer::m_bGameOver = false;
int CPlayer::m_nNumBlock = 0;
CShadow *CPlayer::m_pShadow = NULL;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MOVE_PLAYER				(6.0f)									//�v���C���[�ړ���
#define MOVE_INERTIA			(1.0f)									//�v���C���[�̊���
#define PLAYER_COLLISION		(D3DXVECTOR3(15.0f, 65.0f, 15.0f))		//�v���C���[�̓����蔻��
#define ITEM_COLLISION			(40.0f)									//�A�C�e���̓����蔻��
#define IRONBLOCK_COLLISION		(45.0f)									//�S�̃u���b�N�̓����蔻��
#define WOODLOCK_COLLISION		(70.0f)									//�؂̃u���b�N�̓����蔻��
#define POS_HAND				(D3DXVECTOR3(m_apModel[3]->GetMtxWorld()._41, m_apModel[3]->GetMtxWorld()._42, m_apModel[3]->GetMtxWorld()._43))	//��̈ʒu
#define POS_BODY				(D3DXVECTOR3(m_apModel[0]->GetMtxWorld()._41, m_apModel[0]->GetMtxWorld()._42, m_apModel[0]->GetMtxWorld()._43))	//�̂̈ʒu
#define ATTACK_KEY				(2)										//�����蔻���K��������L�[
#define BLOCK_SIZE				(50.0f)									// �u���b�N�̑傫��
#define BLOCKPOS_SIZE			(25.0f)									// �u���b�N��u���ꏊ�̑傫��
#define BLOCK_RANGE				(65.0f)									// �v���C���[�ƃu���b�N�̋���
#define BLOCK_DECREASE			(30)
#define LIFE					(3)										// �̗�
#define SCORE_COIN				(100)									// �R�C���l�����̃X�R�A
#define SCORE_GEM				(10000)									// ��Ίl�����̃X�R�A
#define PLAYER_FALL				(150.0f)								// �����锻��
#define PLAYER_WALK				(0.25f)									// �����Ă鑬���̍Œ�l
#define JUMP					(9.0f)									// �W�����v��
#define GRAVITY					(0.4f)									// �d��
#define RESPAWN_POS				(D3DXVECTOR3(80.0f, 40.0f, 250.0f))		// ���X�|�[���ʒu
#define BLOCK_PARTICLE_POS		(D3DXVECTOR3(m_SetBlockPos.x, m_SetBlockPos.y - 20.0f, m_SetBlockPos.z))	// �u���b�N�o���̃p�[�e�B�N���̈ʒu
#define BLOCK_PARTICLE_SIZE		(5.0f)	// �u���b�N�o���̃p�[�e�B�N���̃T�C�Y
#define BLOCK_PARTICLE_LIFE		(20)								// �u���b�N�o���̃p�[�e�B�N���̏o������
#define WALK_PARTICLE_TIME		(20)								// ���������̓y�����ł�t���[��
#define WALK_PARTICLE_COLOR		(D3DXCOLOR(0.8f, 0.5f, 0.2f, 1.0f))	// ���������̓y�����ł�F
#define WALK_PARTICLE_SIZE		(10.0f)								// ���������̓y�����ł�T�C�Y
#define WALK_PARTICLE_LIFE		(10)								// ���������̓y�����ł�o������
#define BREAK_PARTICLE_NUM		(80)								// �u���b�N��j�󂵂��Ƃ��̃p�[�e�B�N����
#define BREAK_PARTICLE_TIME		(20)								// �u���b�N��j�󂵂��Ƃ��̃p�[�e�B�N���o������
#define IRON_PARTICLE_NUM		(50)								// �S�u���b�N��j�󂵂��Ƃ��̃p�[�e�B�N����
#define IRON_PARTICLE_SIZE		(3.0f)								// �S�u���b�N��j�󂵂��Ƃ��̃p�[�e�B�N���T�C�Y
#define IRON_PARTICLE_LIFE		(15)								// �S�u���b�N��j�󂵂��Ƃ��̃p�[�e�B�N���o������
#define WOOD_PARTICLE_NUM		(90)								// �؃u���b�N��j�󂵂��Ƃ��̃p�[�e�B�N����
#define WOOD_PARTICLE_LIFE		(20)								// �؃u���b�N��j�󂵂��Ƃ��̃p�[�e�B�N���o������
#define COIN_PARTICLE_NUM		(50)								// �R�C�����l�������Ƃ��̃p�[�e�B�N����
#define COIN_PARTICLE_SIZE		(3.0f)								// �R�C�����l�������Ƃ��̃p�[�e�B�N���T�C�Y
#define COIN_PARTICLE_LIFE		(15)								// �R�C�����l�������Ƃ��̃p�[�e�B�N���o������
#define GEM_PARTICLE_NUM		(80)								// ��΂��l�������Ƃ��̃p�[�e�B�N����
#define GEM_PARTICLE_SIZE		(5.0f)								// ��΂��l�������Ƃ��̃p�[�e�B�N���T�C�Y
#define GEM_PARTICLE_LIFE		(15)								// ��΂��l�������Ƃ��̃p�[�e�B�N���o������
#define WATER_PARTICLE_NUM		(6)									// ���ɗ������Ƃ��̃p�[�e�B�N����
#define WATER_PARTICLE_COLOR	(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f))	// ���ɗ������Ƃ��̃p�[�e�B�N���̐F
#define WATER_PARTICLE_SIZE		(5.0f)								// ���ɗ������Ƃ��̃p�[�e�B�N���̃T�C�Y
#define WATER_PARTICLE_LIFE		(10)								// ���ɗ������Ƃ��̃p�[�e�B�N���̏o������
#define CUT_LIFE				(1)									// �e�����������Ƃ��Ɍ��炷�̗�
#define COLLISION_BULLET		(60)								// �e�������锻��
#define INVINCIBLE_TIME			(120)								// ���G����
#define ONARAREMAIN (3)
#define INVINCIBLE_TIME			(90)								// ���G����

//=============================================================================
// �O���[�o���ϐ��錾
//=============================================================================
int g_nNumModel = 0;
char g_aFilenameModel[MAX_PLAYER][256];

//=============================================================================
// �v���C���[�N���X�̃R���X�g���N�^
//=============================================================================
CPlayer::CPlayer() : CScene(PLAYER_PRIORITY)
{
	// �l���N���A
	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		m_apModel[nCntModel] = NULL;
		m_aPosOffset[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aVtxMin[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aVtxMax[nCntModel] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int nCntMotionInfo = 0; nCntMotionInfo < STATE_MAX; nCntMotionInfo++)
	{
		m_aMotionInfo[nCntMotionInfo].nNumKey = 0;
		m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].nFrame = 0;
		for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
		{
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fPosX = 0.0f;
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fPosY = 0.0f;
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fPosZ = 0.0f;
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fRotX = 0.0f;
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fRotY = 0.0f;
			m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntMotionInfo].aKey[nCntModel].fRotZ = 0.0f;
		}
	}
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ���
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_BlockPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �u���b�N�̈ʒu
	m_SetBlockPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ݒu����u���b�N�̈ʒu
	m_pKeyInfo = NULL;
	m_nKey = 0;
	m_nCountMotion = 0;
	m_WalkTimer = 0;
	m_nLife = 0;
	m_nBulletTimer = 0;
	m_nDisTimer = 0;
	m_nOnaraRemain = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPlayer::~CPlayer()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos)
{
	CPlayer *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pPlayer = new CPlayer;

		if (pPlayer != NULL)
		{
			pPlayer->Init();
			pPlayer->m_pos = pos;
		}
	}

	return pPlayer;
}

//=============================================================================
// �v���C���[����������
//=============================================================================
HRESULT CPlayer::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PLAYER);

	// �e�L�X�g����v���C���[�̏���ǂݍ���
	LoadMotion();

	// ���_���̍ő�l�ƍŏ��l��ݒ�
	SetVtx();

	// �l�̏�����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	m_BlockPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDestAngle = 0;
	m_fDiffAngle = 0;
	m_bRTriangle = false;					// �E�ɂ��邩�ǂ���
	m_nKey = 0;
	m_nCountMotion = 0;
	g_nNumModel = 0;
	m_bLand = false;
	m_bGoal = false;
	m_bGameOver = false;
	m_bPolygonLand = false;
	m_bIronSound = false;
	m_bWaterSound = true;
	m_bAttackSound = true;
	m_nNumBlock = 0;
	m_WalkTimer = 0;
	m_nLife = LIFE;
	m_bBulletHit = false;
	m_nBulletTimer = 0;
	m_nDisTimer = 0;
	m_nOnaraRemain = ONARAREMAIN;

	// �u���b�N�̈ʒu��ۑ�
	m_BlockPos = D3DXVECTOR3((sinf(m_rot.y + D3DX_PI) * BLOCK_RANGE) + m_pos.x, m_pos.y, (cosf(m_rot.y + D3DX_PI) * BLOCK_RANGE) + m_pos.z);

	// �}�X�ڂ��Ƃɐݒu
	m_SetBlockPos.x = (float)(round(m_BlockPos.x / BLOCK_SIZE) * BLOCK_SIZE);
	m_SetBlockPos.y = (float)(round(m_BlockPos.y / BLOCK_SIZE) * BLOCK_SIZE);
	m_SetBlockPos.z = (float)(round(m_BlockPos.z / BLOCK_SIZE) * BLOCK_SIZE);

	//CBlock::Create(D3DXVECTOR3(m_SetBlockPos.x, m_SetBlockPos.y, m_SetBlockPos.z), CBlock::STATE_PLAYER);

	return S_OK;
}

//=============================================================================
// �v���C���[�I������
//=============================================================================
void CPlayer::Uninit(void)
{
	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		if (m_apModel[nCntModel] != NULL)
		{
			m_apModel[nCntModel]->Uninit();

			// ���������J��
			delete m_apModel[nCntModel];
			m_apModel[nCntModel] = NULL;
		}

		// ���b�V���̊J��
		if (m_apMesh[nCntModel] != NULL)
		{
			m_apMesh[nCntModel] = NULL;
		}

		// �}�e���A���̊J��
		if (m_apBuffMat[nCntModel] != NULL)
		{
			m_apBuffMat[nCntModel] = NULL;
		}
	}
	m_pShadow = NULL;
	// �v���C���[���̂̉��
	Release();
}

//=============================================================================
// �v���C���[�X�V����
//=============================================================================
void CPlayer::Update(void)
{
	// �v���C���[�̓���
	Move();

	CollisonAll();

	Life();

	Health();

	OnaraRemain();

	// ���[�V����
	UpdateMotion();

#ifdef _DEBUG
	CDebugProc::Print("cfccfccfc", "�v���C���[�̈ʒu : x", m_pos.x, "f", "   y", m_pos.y, "f", "  z", m_pos.z, "f");
	CDebugProc::Print("cn", "�ݒu�����u���b�N�̐� : ", m_nNumBlock);
	CDebugProc::Print("n", m_nKey);
	CDebugProc::Print("n", m_aMotionInfo[m_State].nNumKey);
	CDebugProc::Print("nc", m_nCountMotion, " / 60");
	CDebugProc::Print("cf", "move.y : ", m_move.y);

	if (m_bLand == true)
	{
		CDebugProc::Print("c", "����Ă���");
	}
	else
	{
		CDebugProc::Print("c", "����Ă��Ȃ�");
	}

	if (m_bJump == true)
	{
		CDebugProc::Print("c", "���ł�");
	}
	else
	{
		CDebugProc::Print("c", "���łȂ�");
	}

	if (m_bPolygonLand == true)
	{
		CDebugProc::Print("c", "�|���S������Ă���");
	}
	else
	{
		CDebugProc::Print("c", "�|���S������Ă��Ȃ�");
	}
	CDebugProc::Print("cn", "m_nOnara : ", m_nOnaraRemain);
	CDebugProc::Print("cfccfccfc", "vtxMax : x", m_aVtxMax[3].x, "f", "   y", m_aVtxMax[3].y, "f", "  z", m_aVtxMax[3].z, "f");
	CDebugProc::Print("cfccfccfc", "vtxMin : x", m_aVtxMin[3].x, "f", "   y", m_aVtxMin[3].y, "f", "  z", m_aVtxMin[3].z, "f");
	CDebugProc::Print("cfccfccfc", "offset : x", m_apModel[3]->GetMtxWorld()._41, "f", "   y", m_apModel[3]->GetMtxWorld()._42, "f", "  z", m_apModel[3]->GetMtxWorld()._43, "f");
#endif
}

//=============================================================================
// �v���C���[�`�揈��
//=============================================================================
void CPlayer::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	if (m_bBulletHit == false)
	{
		for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
		{
			if (m_apModel[nCntModel] != NULL)
			{
				// ���f���`�揈��
				m_apModel[nCntModel]->Draw();
			}
		}
	}
	else
	{
		m_nDisTimer++;

		if (m_nDisTimer % 5 == 0)
		{
			for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
			{
				if (m_apModel[nCntModel] != NULL)
				{
					// ���f���`�揈��
					m_apModel[nCntModel]->Draw();
				}
			}
		}
	}
}

//=============================================================================
// �v���C���[����������
//=============================================================================
void CPlayer::Move(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ���͏����擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// �J�����擾
	CCamera *pCamera;
	pCamera = CManager::GetCamera();

	// �J�����̌������擾
	D3DXVECTOR3 cameraRot;
	cameraRot = pCamera->GetRot();

	// ���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �O�̃t���[���̈ʒu���
	m_posOld = m_pos;

	//=====================================================
	// �ړ�
	//=====================================================
	float fMovePlayer = MOVE_PLAYER;	// �v���C���[�̈ړ��ʂ�ݒ�

	fMovePlayer = MOVE_PLAYER;

	// �W���C�p�b�g
	if (pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LS_UP) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LS_DOWN) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LS_RIGHT) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LS_LEFT) == true)
	{// ���X�e�B�b�N
		m_move.x -= sinf(cameraRot.y - pInputJoypad->GetLeftAxiz()) * (fMovePlayer * 1.0f);
		m_move.z -= cosf(cameraRot.y - pInputJoypad->GetLeftAxiz()) * (fMovePlayer * 1.0f);

		m_fDestAngle = cameraRot.y - pInputJoypad->GetLeftAxiz();
	}

	if (pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_UP) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_DOWN) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_RIGHT) == true ||
		pInputJoypad->GetPress(CInputJoypad::DIJS_BUTTON_LEFT) == true)
	{// �\���L�[
		m_move.x += sinf(cameraRot.y + pInputJoypad->GetRadian()) * (fMovePlayer * 1.0f);
		m_move.z += cosf(cameraRot.y + pInputJoypad->GetRadian()) * (fMovePlayer * 1.0f);

		m_fDestAngle = cameraRot.y + pInputJoypad->GetRadian() - D3DX_PI;
	}

	//�C�ӂ̃L�[��
	if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		//���f���̈ړ�	���f���̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
		m_move.x -= sinf(cameraRot.y + D3DX_PI * 0.5f) * fMovePlayer;
		m_move.z -= cosf(cameraRot.y + D3DX_PI * 0.5f) * fMovePlayer;
		m_fDestAngle = (cameraRot.y + D3DX_PI * 0.5f);

	}
	//�C�ӂ̃L�[��
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		//���f���̈ړ�	���f���̈ړ�����p�x(�J�����̌��� + �p�x) * �ړ���
			m_move.x -= sinf(cameraRot.y - D3DX_PI * 0.5f) * fMovePlayer;
			m_move.z -= cosf(cameraRot.y - D3DX_PI * 0.5f) * fMovePlayer;
			m_fDestAngle = (cameraRot.y - D3DX_PI * 0.5f);
	}
	/*if (pInputKeyboard->GetPress(DIK_W) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
	{
		m_pos.y += 20.0f;
	}
	if (pInputKeyboard->GetPress(DIK_S) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
	{
		m_pos.y -= 20.0f;
	}*/

	//�����̊���
	m_fDiffAngle = m_fDestAngle - m_rot.y;

	//�p�x�̐ݒ�
	if (m_fDiffAngle > D3DX_PI)
	{
		m_fDiffAngle -= D3DX_PI* 2.0f;
	}
	if (m_fDiffAngle < -D3DX_PI)
	{
		m_fDiffAngle += D3DX_PI* 2.0f;
	}

	m_rot.y += m_fDiffAngle * 0.1f;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI* 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI* 2.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_W) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_A) == true)
	{
		m_move.y = 0.0f;

		pSound->PlaySound(CSound::SOUND_LABEL_SE_JUMP);

		// �v���C���[���W�����v���
		m_bJump = true;
		// �W�����v��
		m_move.y -= (cosf(D3DX_PI * 1.0f) * JUMP);
		// �L�[�ƃt���[����0�ɂ���
		m_nKey = 0;
		m_nCountMotion = 0;

		CBAnimation::Create(D3DXVECTOR3(m_pos.x, m_pos.y - 80.0f, m_pos.z), D3DXCOLOR(1.0f, 0.8f, 0.0f, 1.0f), 50.0f, 50.0f, (1.0f / 6.0f), 1.0f, 1.0f, 6, 1, 0, 0, CResource::TEXTURE_HE);
	}

	if (m_move.x < PLAYER_WALK && m_move.x > -PLAYER_WALK && m_move.z < PLAYER_WALK && m_move.z > -PLAYER_WALK && m_bJump == false && m_State != STATE_BLOCK && m_State != STATE_BREAK && m_State != STATE_UPBREAK && m_State != STATE_LAND)
	{
		if (m_State == STATE_WALK)
		{
			// �L�[�ƃt���[����0�ɂ���
			m_nKey = 0;
			m_nCountMotion = 0;
		}

		// �ҋ@���
		m_State = STATE_NORMAL;
	}
	else if (m_move.x >= PLAYER_WALK || m_move.x <= -PLAYER_WALK || m_move.z >= PLAYER_WALK || m_move.z <= -PLAYER_WALK && m_bJump == false)
	{
		if (m_bJump == false)
		{
			// ���s���
			m_State = STATE_WALK;
		}
	}

	if (m_State == STATE_LAND)
	{
		if (m_nKey == 1)
		{
			m_State = STATE_NORMAL;
		}
	}

	Action();

	// �ʒu�X�V
	m_pos.x += m_move.x;
	m_pos.z += m_move.z;
	m_pos.y += m_move.y;

	//����
	m_move.x += (0.0f - m_move.x) * MOVE_INERTIA;
	m_move.z += (0.0f - m_move.z) * MOVE_INERTIA;

#if(1)
	// �d�͉��Z
	if (m_move.y > -30.0f)
	{
		m_move.y -= cosf(D3DX_PI * 0.0f) * GRAVITY;
	}
#endif
}

//=============================================================================
// �v���C���[����������
//=============================================================================
void CPlayer::Action(void)
{
	
}

//=============================================================================
// �u���b�N�̈ʒu
//=============================================================================
void CPlayer::SetBlock(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ���͏����擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// �u���b�N�̈ʒu��ۑ� 
	m_BlockPos = D3DXVECTOR3((sinf(m_rot.y + D3DX_PI) * BLOCK_RANGE) + m_pos.x, m_pos.y, (cosf(m_rot.y + D3DX_PI) * BLOCK_RANGE) + m_pos.z);

	// �}�X�ڂ��Ƃɐݒu
	m_SetBlockPos.x = (float)(round(m_BlockPos.x / BLOCK_SIZE) * BLOCK_SIZE);
	m_SetBlockPos.y = (float)(round(m_BlockPos.y / BLOCK_SIZE) * BLOCK_SIZE);
	m_SetBlockPos.z = (float)(round(m_BlockPos.z / BLOCK_SIZE) * BLOCK_SIZE);
}

//=============================================================================
// ���f���Ƃ̓����蔻��̏���
//=============================================================================
void CPlayer::CollisonModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius)
{

}

//=============================================================================
// �S�[���Ƃ̓����蔻��̏���
//=============================================================================
void CPlayer::CollisionGoal(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius)
{
	CScene *pScene = NULL;

	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(GOAL_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_GOAL)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				m_bGoal = ((CGoal*)pScene)->Collision(pos, posOld, move, radius);
			}
		}

		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}
}

//=============================================================================
// �R�C���̓����蔻��
//=============================================================================
void CPlayer::CollisonCoin(D3DXVECTOR3 *pos, float fRadius)
{
	// ���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	CScene *pScene = NULL;

	// �擪�̃I�u�W�F�N�g���擾(���f���̗D�揇�ʂ�3������A3�ɂ���I�u�W�F�N�g�����ׂČ���)
	pScene = CScene::GetTop(COIN_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_COIN)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				bool bHit = ((CCoin*)pScene)->Collision(pos, fRadius);

				if (((CCoin*)pScene)->Collision(pos, fRadius) == true)
				{
					pSound->PlaySound(CSound::SOUND_LABEL_SE_COIN);

					// �R�C���폜
					((CCoin*)pScene)->Uninit();

					// ������R�C�����J�E���g����
					int nNumCoin = ((CCoin*)pScene)->GetNumCoin();

					nNumCoin--;
					

					// �u���b�N�̐��擾
					CScore *pScore = NULL;

					// ���Ȃ�c�@�̎擾
					COnaraRemain *pOnaraRemain = NULL;

					if (mode == CManager::MODE_GAME)
					{
						pScore = CGame::GetScore();

						pOnaraRemain = CGame::GetOnaraRemain();
					}
					else if (mode == CManager::MODE_TUTORIAL)
					{
						pScore = CTutorial::GetScore();
					}

					pScore->AddScore(SCORE_COIN);

					if (m_nOnaraRemain < ONARAREMAIN)
					{
						m_nOnaraRemain++;

						pOnaraRemain->AddOnaraRemain(1);
					}

					for (int nCntParticle = 0; nCntParticle < COIN_PARTICLE_NUM; nCntParticle++)
					{
						CParticle3D::Create(D3DXVECTOR3(((CCoin*)pScene)->GetPos().x, ((CCoin*)pScene)->GetPos().y + 10.0f, ((CCoin*)pScene)->GetPos().z),
							D3DXVECTOR3(sinf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1))),
							D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f),
							COIN_PARTICLE_SIZE,
							COIN_PARTICLE_SIZE,
							COIN_PARTICLE_LIFE,
							CParticle3D::TYPE_NORMAL,
							CResource::TEXTURE_PARTICLE2D);
					}

					((CCoin*)pScene)->SetNumCoin(nNumCoin);
				}
			}
		}

		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}
}

//=============================================================================
// ���Ƃ̓����蔻��̏���
//=============================================================================
void CPlayer::CollisionField(void)
{
	CScene *pScene = NULL;

	// �擪�̃I�u�W�F�N�g���擾(���b�V���t�B�[���h�̗D�揇�ʂ�3������A3�ɂ���I�u�W�F�N�g�����ׂČ���)
	pScene = CScene::GetTop(MESHFIELD_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_MESHFIELD)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				float fHeight = ((CMeshField*)pScene)->GetHeight(m_pos);
				
				if (m_bJump == false)
				{
					// ���Ƃ̓����蔻��
					if (((CMeshField*)pScene)->GetLand() == false)
					{// �v���C���[��y���W���n�ʂ��������Ƃ�
						m_move.y -= cosf(D3DX_PI * 0.0f) * GRAVITY;	// �d�͉��Z
					}
					else if(((CMeshField*)pScene)->GetLand() == true && m_pos.y > fHeight - PLAYER_FALL)
					{// �v���C���[��y���W���n�ʂ����Ⴂ�Ƃ�
						m_move.y = 0.0f;							// y���̈ړ��ʂ�0�ɂ���
						m_pos.y = fHeight;							// y���W��n�ʂ̍����ɂ���
						m_bJump = false;
					}
				}
				else
				{
					// �W�����v��Ԃ�
					m_State = STATE_JUMP;
					if (m_pos.y <= fHeight)
					{// �v���C���[��y���W���n�ʂ����Ⴂ�Ƃ�
						// �W�����v���Ă��Ȃ���Ԃɂ���
						m_bJump = false;
					}
				}

#ifdef _DEBUG
				if (((CMeshField*)pScene)->GetLand() == true)
				{
					CDebugProc::Print("c", "������Ă���");
				}
				else
				{
					CDebugProc::Print("c", "������Ă��Ȃ�");
				}

				

#endif
			}
		}

		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}
}

//=============================================================================
// �|���S���Ƃ̓����蔻��̏���
//=============================================================================
void CPlayer::CollisonPolygon(D3DXVECTOR3 *pos, D3DXVECTOR3 fRadius)
{
	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	CScene *pScene = NULL;

	// �擪�̃I�u�W�F�N�g���擾(���b�V���t�B�[���h�̗D�揇�ʂ�3������A3�ɂ���I�u�W�F�N�g�����ׂČ���)
	pScene = CScene::GetTop(POLYGON_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_FIELD)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				float fHeight = ((CPolygon*)pScene)->GetHeight(m_pos);
				bool bLand = ((CPolygon*)pScene)->ColLand(pos, fRadius);


				if (m_bJump == false)
				{
					if (bLand == true && m_pos.y <= fHeight)
					{// �v���C���[��y���W���n�ʂ����Ⴂ�Ƃ�
						m_move.y = 0.0f;							// y���̈ړ��ʂ�0�ɂ���
						m_pos.y = fHeight;							// y���W��n�ʂ̍����ɂ���
						m_bJump = false;
						m_bPolygonLand = true;

						if (m_State == STATE_WALK)
						{
							m_WalkTimer++;

							if (m_WalkTimer >= WALK_PARTICLE_TIME)
							{
								CParticle3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z),
									D3DXVECTOR3(sinf(PARTICLE_ROT), cosf(PARTICLE_ROT), cosf(-m_rot.y)),
									WALK_PARTICLE_COLOR,
									WALK_PARTICLE_SIZE,
									WALK_PARTICLE_SIZE,
									WALK_PARTICLE_LIFE,
									CParticle3D::TYPE_UP,
									CResource::TEXTURE_CLOUD);
								m_WalkTimer = 0;
							}
						}
					}
					else if (m_pos.y > fHeight)
					{
						m_bPolygonLand = false;
					}
				}
				else
				{
					// �W�����v��Ԃ�
					m_State = STATE_JUMP;
					if (m_pos.y <= fHeight)
					{// �v���C���[��y���W���n�ʂ����Ⴂ�Ƃ�
					 // �W�����v���Ă��Ȃ���Ԃɂ���
						m_bJump = false;

						// �L�[�ƃt���[����0�ɂ���
						m_nKey = 0;
						m_nCountMotion = 0;
						m_State = STATE_LAND;
					}
				}
			}
		}

		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}

	// ���ɗ��������̔���
	pScene = NULL;

	// �擪�̃I�u�W�F�N�g���擾
	pScene = CScene::GetTop(SCENE3D_PRIORITY);

	while (pScene != NULL)
	{
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_SCENE3D)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				float fHeight = ((CScene3D*)pScene)->GetHeight(m_pos);
				bool bLand = ((CScene3D*)pScene)->ColLand(pos, fRadius);

				if (bLand == true && m_pos.y > -PLAYER_FALL)
				{
					if (m_bWaterSound == true)
					{
						pSound->PlaySound(CSound::SOUND_LABEL_SE_WATER);
						m_bWaterSound = false;
					}
					
					for (int nCntParticle = 0; nCntParticle < WATER_PARTICLE_NUM; nCntParticle++)
					{
						CParticle3D::Create(D3DXVECTOR3(m_pos.x, 0.0f, m_pos.z),
							D3DXVECTOR3(sinf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1))),
							WATER_PARTICLE_COLOR,
							WATER_PARTICLE_SIZE,
							WATER_PARTICLE_SIZE,
							WATER_PARTICLE_LIFE,
							CParticle3D::TYPE_UP,
							CResource::TEXTURE_PARTICLE2D);
					}
				}
			}
		}

		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}
}

//=============================================================================
// ���_���W�̐ݒ菈��
//=============================================================================
void CPlayer::SetVtx(void)
{
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	D3DXVECTOR3 vtx;
	int nNumVtx;	//���_��
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{// �p�[�c���J��Ԃ�
		// ���_�����擾
		nNumVtx = m_apMesh[nCntModel]->GetNumVertices();
		// ���_�t�H�[�}�b�g�̃T�C�Y���擾
		sizeFvF = D3DXGetFVFVertexSize(m_apMesh[nCntModel]->GetFVF());

		// ���_�̍ŏ��l�ƍő�l����
		m_aVtxMin[nCntModel] = D3DXVECTOR3(10000, 10000, 10000);
		m_aVtxMax[nCntModel] = D3DXVECTOR3(-10000, -10000, -10000);

		//���_�o�b�t�@�����b�N
		m_apMesh[nCntModel]->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{//���_���W�̑��
			vtx = *(D3DXVECTOR3*)pVtxBuff;

			if (m_aVtxMin[nCntModel].x > vtx.x)
			{
				m_aVtxMin[nCntModel].x = vtx.x;
			}
			if (m_aVtxMin[nCntModel].y > vtx.y)
			{
				m_aVtxMin[nCntModel].y = vtx.y;
			}
			if (m_aVtxMin[nCntModel].z > vtx.z)
			{
				m_aVtxMin[nCntModel].z = vtx.z;
			}

			if (m_aVtxMax[nCntModel].x < vtx.x)
			{
				m_aVtxMax[nCntModel].x = vtx.x;
			}
			if (m_aVtxMax[nCntModel].y < vtx.y)
			{
				m_aVtxMax[nCntModel].y = vtx.y;
			}
			if (m_aVtxMax[nCntModel].z < vtx.z)
			{
				m_aVtxMax[nCntModel].z = vtx.z;
			}

			//�T�C�Y���|�C���^��i�߂�
			pVtxBuff += sizeFvF;
		}
		//���_�o�b�t�@���A�����b�N
		m_apMesh[nCntModel]->UnlockVertexBuffer();
	}
}

//=============================================================================
// ���[�V��������
//=============================================================================
void CPlayer::UpdateMotion(void)
{
	KEY *pKey, *pKeyNext;
	float fRateMotion;
	float fDiffMotion;
	D3DXVECTOR3 modelRot;
	D3DXVECTOR3 modelPos;

	for (int nCntModel = 0; nCntModel < MAX_PLAYER; nCntModel++)
	{
		if (m_apModel[nCntModel] != NULL)
		{
			// ���݂̃L�[���擾
			pKey = &m_aMotionInfo[m_State].aKeyInfo[m_nKey].aKey[nCntModel];

			// ���̃L�[���擾
			pKeyNext = &m_aMotionInfo[m_State].aKeyInfo[(m_nKey + 1) % m_aMotionInfo[m_State].nNumKey].aKey[nCntModel];

			// ���݂̃L�[�Ǝ��̃L�[�ւ̍Đ��t���[�����ɂ����郂�[�V�����J�E���^�[�̑��Βl���Z�o
			fRateMotion = (float)m_nCountMotion / (float)m_aMotionInfo[m_State].aKeyInfo[m_nKey].nFrame;

			//========================================
			// x�̌���
			//========================================
			// ���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pKeyNext->fRotX - pKey->fRotX;

			// ���Βl�ƍ������g���Ċe�v�f�̒l���Z�o����
			modelRot.x = pKey->fRotX + (fDiffMotion * fRateMotion);

			//========================================
			// y�̌���
			//========================================
			// ���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pKeyNext->fRotY - pKey->fRotY;

			// ���Βl�ƍ������g���Ċe�v�f�̒l���Z�o����
			modelRot.y = pKey->fRotY + (fDiffMotion * fRateMotion);

			//========================================
			// z�̌���
			//========================================
			// ���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pKeyNext->fRotZ - pKey->fRotZ;

			// ���Βl�ƍ������g���Ċe�v�f�̒l���Z�o����
			modelRot.z = pKey->fRotZ + (fDiffMotion * fRateMotion);

			//========================================
			// x�̈ʒu
			//========================================
			// ���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pKeyNext->fPosX - pKey->fPosX;

			// ���Βl�ƍ������g���Ċe�v�f�̒l���Z�o����
			modelPos.x = pKey->fPosX + (fDiffMotion * fRateMotion);

			//========================================
			// y�̈ʒu
			//========================================
			// ���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pKeyNext->fPosY - pKey->fPosY;

			// ���Βl�ƍ������g���Ċe�v�f�̒l���Z�o����
			modelPos.y = pKey->fPosY + (fDiffMotion * fRateMotion);

			//========================================
			// z�̈ʒu
			//========================================
			// ���݂̃L�[�Ǝ��̃L�[�̊e�v�f�̍������Z�o
			fDiffMotion = pKeyNext->fPosZ - pKey->fPosZ;

			// ���Βl�ƍ������g���Ċe�v�f�̒l���Z�o����
			modelPos.z = pKey->fPosZ + (fDiffMotion * fRateMotion);

			// �ʒu��ݒ�
			m_apModel[nCntModel]->SetPos(m_aPosOffset[nCntModel] + modelPos);
			// ������ݒ�
			m_apModel[nCntModel]->SetRot(modelRot);
		}
	}

	
	if (m_aMotionInfo[m_State].bLoop == true)
	{// ���[�v���郂�[�V����
		m_nCountMotion++;
		if (m_nCountMotion >= m_aMotionInfo[m_State].aKeyInfo[m_nKey].nFrame)
		{
			if (m_nKey >= m_aMotionInfo[m_State].nNumKey - 1)
			{
				m_nKey = 0;
			}
			else
			{
				m_nKey++;
			}

			m_nCountMotion = 0;
		}
	}
	else
	{// ���[�v���Ȃ����[�V����
		if (m_nKey < m_aMotionInfo[m_State].nNumKey - 1)
		{
		
			m_nCountMotion++;

			if (m_nCountMotion >= m_aMotionInfo[m_State].aKeyInfo[m_nKey].nFrame)
			{
				m_nCountMotion = 0;

				if (m_nKey <= m_aMotionInfo[m_State].nNumKey - 1)
				{
					m_nKey++;	// �L�[����i�߂�
				}
			}
			
		}
	}
}

//=============================================================================
// ���[�V�����̃��[�h����
//=============================================================================
void CPlayer::LoadMotion(void)
{
	D3DXVECTOR3 pos[MAX_PLAYER];
	D3DXVECTOR3 rot[MAX_PLAYER];
	int nWord;
	int nIdx;
	int nParent[MAX_PLAYER];
	int nLoop;
	int nCntMotionInfo = 0;

	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	CText *pText;
	pText = CManager::GetText();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	FILE *pFile;

	pFile = fopen(MOTION_FILENAME, "r");

	if (pFile != NULL)
	{
		char *pStrCur;		// ������̐擪�ւ̃|�C���^
		char aLine[256];	// ������ǂݍ��ݗp�i1�s���j
		char aStr[256];		// �����񔲂��o���p
		int nCntModel = 0;

		while (1)
		{
			pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
			pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
			strcpy(&aStr[0], pStrCur);

			if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
			{
				// 1�s�ǂݍ���
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
				pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�

				strcpy(&aStr[0], pStrCur);
			}
			if (memcmp(&aStr[0], NUMMODEL, strlen(NUMMODEL)) == 0)
			{
				pStrCur += strlen(NUMMODEL);	// ���o��

				g_nNumModel = atoi(pStrCur);	// �������l�ɕϊ�

				for (int nCntModel = 0; nCntModel < g_nNumModel; nCntModel++)
				{// ���f���̓ǂݍ���
					pStrCur = pText->ReadLine(pFile, &aLine[0]);
					pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
					strcpy(&aStr[0], pStrCur);

					if (memcmp(&aStr[0], MODEL_FILE, strlen(MODEL_FILE)) == 0)
					{
						pStrCur += strlen(MODEL_FILE);

						strcpy(&aStr[0], pStrCur);

						// �R�����g������
						int nNullNum = pText->PopString(pStrCur, &aStr[0]);
						strcpy(&aStr[0], pStrCur);
						aStr[nNullNum - 1] = '\0';

						strcpy(&g_aFilenameModel[nCntModel][0], aStr);	//

						D3DXLoadMeshFromX(&g_aFilenameModel[nCntModel][0],
							D3DXMESH_SYSTEMMEM,
							pDevice,
							NULL,
							&m_apBuffMat[nCntModel],
							NULL,
							&m_anNumMat[nCntModel],
							&m_apMesh[nCntModel]);
					}
				}
			}
			else if (memcmp(&aStr[0], CHARACTER_SET, strlen(CHARACTER_SET)) == 0)
			{// �L�����N�^�[���f���̐ݒ�

					// 1�s�ǂݍ���
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
				pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�

				strcpy(&aStr[0], pStrCur);

				if (memcmp(&aStr[0], NUM_PARTS, strlen(NUM_PARTS)) == 0)
				{
					pStrCur += strlen(NUM_PARTS);	// ���o��

					m_nNumParts = atoi(pStrCur);

					pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
					pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�

					strcpy(&aStr[0], pStrCur);
				}

				for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
				{

					if (memcmp(&aStr[0], PARTSSET, strlen(PARTSSET)) == 0)
					{

						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
						pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�

						strcpy(&aStr[0], pStrCur);

						if (memcmp(&aStr[0], INDEX, strlen(INDEX)) == 0)
						{// �C���f�b�N�X
							pStrCur += strlen(INDEX);
							nIdx = atoi(pStrCur);

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
							pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�

							strcpy(&aStr[0], pStrCur);
						}
						if (memcmp(&aStr[0], PARENT, strlen(PARENT)) == 0)
						{// �e
							pStrCur += strlen(PARENT);	// ���o��

							nParent[nIdx] = atoi(pStrCur);	// aStr[0]�ɉ����������Ă��邩���m���߂�

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
							pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�

							strcpy(&aStr[0], pStrCur);
						}
						if (memcmp(&aStr[0], POS, strlen(POS)) == 0)
						{// �ʒu
							pStrCur += strlen(POS);	// ���o��

							// float�ɕϊ����đ��
							pos[nIdx].x = (float)atof(pStrCur);

							// aStr[0]�ɉ����������Ă��邩���m���߂�
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// ���܂Ői�߂�
							pStrCur += nWord;

							// float�ɕϊ����đ��
							pos[nIdx].y = (float)atof(pStrCur);

							// aStr[0]�ɉ����������Ă��邩���m���߂�
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// ���܂Ői�߂�
							pStrCur += nWord;

							// float�ɕϊ����đ��
							pos[nIdx].z = (float)atof(pStrCur);

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
							pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�

							strcpy(&aStr[0], pStrCur);
						}
						if (memcmp(&aStr[0], ROT, strlen(ROT)) == 0)
						{// ����
							pStrCur += strlen(ROT);	// ���o��

							// float�ɕϊ����đ��
							rot[nIdx].x = (float)atof(pStrCur);

							// aStr[0]�ɉ����������Ă��邩���m���߂�
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// ���܂Ői�߂�
							pStrCur += nWord;

							// float�ɕϊ����đ��
							rot[nIdx].y = (float)atof(pStrCur);

							// aStr[0]�ɉ����������Ă��邩���m���߂�
							nWord = pText->PopString(pStrCur, &aStr[0]);

							// ���܂Ői�߂�
							pStrCur += nWord;

							// float�ɕϊ����đ��
							rot[nIdx].z = (float)atof(pStrCur);

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
							pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�

							strcpy(&aStr[0], pStrCur);
						}
						if (memcmp(&aStr[0], END_PARTSSET, strlen(END_PARTSSET)) == 0)
						{
							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
							pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�

							strcpy(&aStr[0], pStrCur);
						}

						if (nParent[nIdx] == -1)
						{
							m_apModel[0] = CModel::Create(D3DXVECTOR3(m_pos.x + pos[nIdx].x, m_pos.y + pos[nIdx].y, m_pos.z + pos[nIdx].z), m_rot);
							m_apModel[0]->BindModel(m_apBuffMat[nIdx], m_anNumMat[nIdx], m_apMesh[nIdx]);
							m_apModel[0]->SetParent(NULL);
							// �I�t�Z�b�g�ɑ��
							m_aPosOffset[0] = m_apModel[0]->GetPos();
						}
						else if (nParent[nIdx] > -1)
						{
							// ���f�����쐬
							m_apModel[nIdx] =
								CModel::Create(D3DXVECTOR3(m_pos.x + pos[nIdx].x, m_pos.y + pos[nIdx].y, m_pos.z + pos[nIdx].z), rot[nIdx]);
							m_apModel[nIdx]->BindModel(m_apBuffMat[nIdx], m_anNumMat[nIdx], m_apMesh[nIdx]);
							m_apModel[nIdx]->SetParent(m_apModel[nParent[nIdx]]);

							// �I�t�Z�b�g�ɑ��
							m_aPosOffset[nIdx] = m_apModel[nIdx]->GetPos();
						}
					}
				}
			}
			else if (memcmp(&aStr[0], END_CHARACTER_SET, strlen(END_CHARACTER_SET)) == 0)
			{
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
				pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�

				strcpy(&aStr[0], pStrCur);
			}
			else if (memcmp(&aStr[0], MOTIONSET, strlen(MOTIONSET)) == 0)
			{// �L�����N�^�[���[�V�����̐ݒ�
				while (1)
				{
					pStrCur = pText->ReadLine(pFile, &aLine[0]);
					pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
					strcpy(&aStr[0], pStrCur);

					if (memcmp(&aStr[0], LOOP, strlen(LOOP)) == 0)
					{
						pStrCur += strlen(LOOP);	// ���o��

						nLoop = atoi(pStrCur);

						if (nLoop == 0)
						{
							m_aMotionInfo[nCntMotionInfo].bLoop = false;
						}
						else if (nLoop == 1)
						{
							m_aMotionInfo[nCntMotionInfo].bLoop = true;
						}
					}
					else if (memcmp(&aStr[0], NUM_KEY, strlen(NUM_KEY)) == 0)
					{
						pStrCur += strlen(NUM_KEY);	// ���o��

						m_aMotionInfo[nCntMotionInfo].nNumKey = atoi(pStrCur);

						pStrCur = pText->ReadLine(pFile, &aLine[0]);
						pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
						strcpy(&aStr[0], pStrCur);

						for (int nCntKeySet = 0; nCntKeySet < m_aMotionInfo[nCntMotionInfo].nNumKey; nCntKeySet++)
						{
							if (memcmp(&aStr[0], KEYSET, strlen(KEYSET)) == 0)
							{// �L�[�ݒ�̎n�܂�
								pStrCur = pText->ReadLine(pFile, &aLine[0]);
								pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
								strcpy(&aStr[0], pStrCur);
								if (memcmp(&aStr[0], FRAME, strlen(FRAME)) == 0)
								{// �t���[����ǂݍ���
									pStrCur += strlen(FRAME);	// ���o��

									m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].nFrame = atoi(pStrCur);
								}

								pStrCur = pText->ReadLine(pFile, &aLine[0]);
								pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
								strcpy(&aStr[0], pStrCur);

								for (int nCntParts = 0; nCntParts < m_nNumParts; nCntParts++)
								{
									if (memcmp(&aStr[0], "KEY", strlen("KEY")) == 0)
									{// �L�[��ǂݍ���
										pStrCur = pText->ReadLine(pFile, &aLine[0]);
										pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
										strcpy(&aStr[0], pStrCur);

										if (memcmp(&aStr[0], POS, strlen(POS)) == 0)
										{// �ʒu
											pStrCur += strlen(POS);	// ���o��

											// float�ɕϊ����đ��
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fPosX = (float)atof(pStrCur);

											// aStr[0]�ɉ����������Ă��邩���m���߂�
											nWord = pText->PopString(pStrCur, &aStr[0]);

											// ���܂Ői�߂�
											pStrCur += nWord;

											// float�ɕϊ����đ��
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fPosY = (float)atof(pStrCur);

											// aStr[0]�ɉ����������Ă��邩���m���߂�
											nWord = pText->PopString(pStrCur, &aStr[0]);

											// ���܂Ői�߂�
											pStrCur += nWord;

											// float�ɕϊ����đ��
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fPosZ = (float)atof(pStrCur);

											pStrCur = pText->ReadLine(pFile, &aLine[0]);
											pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
											strcpy(&aStr[0], pStrCur);
										}
										if (memcmp(&aStr[0], ROT, strlen(ROT)) == 0)
										{// ����
											pStrCur += strlen(ROT);	// ���o��

											// float�ɕϊ����đ��
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fRotX = (float)atof(pStrCur);

											// aStr[0]�ɉ����������Ă��邩���m���߂�
											nWord = pText->PopString(pStrCur, &aStr[0]);

											// ���܂Ői�߂�
											pStrCur += nWord;

											// float�ɕϊ����đ��
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fRotY = (float)atof(pStrCur);

											// aStr[0]�ɉ����������Ă��邩���m���߂�
											nWord = pText->PopString(pStrCur, &aStr[0]);

											// ���܂Ői�߂�
											pStrCur += nWord;

											// float�ɕϊ����đ��
											m_aMotionInfo[nCntMotionInfo].aKeyInfo[nCntKeySet].aKey[nCntParts].fRotZ = (float)atof(pStrCur);

											pStrCur = pText->ReadLine(pFile, &aLine[0]);
											pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
											strcpy(&aStr[0], pStrCur);

										}
										if (memcmp(&aStr[0], "END_KEY", strlen("END_KEY")) == 0)
										{
											pStrCur = pText->ReadLine(pFile, &aLine[0]);
											pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
											strcpy(&aStr[0], pStrCur);
										}

									}

								}
							}
							if (memcmp(&aStr[0], END_KEYSET, strlen(END_KEYSET)) == 0)
							{// �L�[�ݒ�̏I���
								pStrCur = pText->ReadLine(pFile, &aLine[0]);
								pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
								strcpy(&aStr[0], pStrCur);
							}
						}
					}
					if (memcmp(&aStr[0], END_MOTIONSET, strlen(END_MOTIONSET)) == 0)
					{
						m_pKeyInfo = &m_aMotionInfo[nCntMotionInfo].aKeyInfo[0];
						nCntMotionInfo++;
						break;
					}
				}
			}
			else if(memcmp(&aStr[0], "END_SCRIPT", strlen("END_SCRIPT")) == 0)
			{
				break;
			}
		}

		fclose(pFile);
	}
}

//=============================================================================
// �S�Ă̓����蔻��
//=============================================================================
void CPlayer::CollisonAll(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ���͏����擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// ���f���Ƃ̓����蔻��
	CollisonModel(&m_pos, &D3DXVECTOR3(m_posOld.x, m_posOld.y + 1.0f, m_posOld.z), &m_move, PLAYER_COLLISION);

	// �S�[���Ƃ̓����蔻��
	CollisionGoal(&m_pos, &m_posOld, &m_move, PLAYER_COLLISION);

	// �R�C���Ƃ̓����蔻��
	CollisonCoin(&POS_BODY, ITEM_COLLISION);

	// �|���S���Ƃ̓����蔻��
	CollisonPolygon(&m_pos, PLAYER_COLLISION);

	if (pInputKeyboard->GetPress(DIK_9) && pInputKeyboard->GetPress(DIK_0) == true)
	{
		// �R�C���Ƃ̓����蔻��
		CollisonCoin(&POS_BODY, ITEM_COLLISION * 100.0f);
	}

	// �e�Ƃ̓����蔻��
	if (m_bBulletHit == false)
	{
		CollisonObstacle(&m_pos, COLLISION_BULLET);
	}
	else
	{
		m_nBulletTimer++;

		if (m_nBulletTimer > INVINCIBLE_TIME)
		{
			m_bBulletHit = false;
			// �J�E���^�[�����Z�b�g
			m_nBulletTimer = 0;
			m_nDisTimer = 0;
		}
	}
}

//=============================================================================
// �c�@����
//=============================================================================
void CPlayer::Life(void)
{
	// ���[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// �c�@�擾
	CLife *pLife = NULL;

	if (mode == CManager::MODE_TUTORIAL)
	{
		pLife = CTutorial::GetLife();
	}
	else if (mode == CManager::MODE_GAME)
	{
		pLife = CGame::GetLife();
	}

}

//=============================================================================
// �̗͏���
//=============================================================================
void CPlayer::Health(void)
{
	// ���[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// �̗͎擾
	CHealth *pHealth = NULL;

	// �c�@�擾
	CLife *pLife = NULL;


	if (mode == CManager::MODE_TUTORIAL)
	{
		pLife = CTutorial::GetLife();
		pHealth = CTutorial::GetHealth();
	}
	else if (mode == CManager::MODE_GAME)
	{
		pLife = CGame::GetLife();
		pHealth = CGame::GetHealth();
	}

	if (pHealth->GetHealth() <= 0)
	{
		m_bGameOver = true;	// �Q�[���I�[�o�[�ɂ���
	}
}
//=============================================================================
// ���Ȃ�c�@����
//=============================================================================
void CPlayer::OnaraRemain(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ���[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// ���Ȃ�c�@�擾
	COnaraRemain *pOnaraRemain = NULL;

	if (mode == CManager::MODE_GAME)
	{
		pOnaraRemain = CGame::GetOnaraRemain();

	}

	if (mode == CManager::MODE_GAME)
	{
		if (pInputKeyboard->GetTrigger(DIK_W) == true)
		{// W���������炨�Ȃ�c�@�����炷

			if (m_nOnaraRemain > 0)
			{
				m_nOnaraRemain--;

				pOnaraRemain->AddOnaraRemain(-1);
			}
		}


	
	}
}

	//if (mode == CManager::MODE_TUTORIAL)
	//{
	//	if (m_pos.y <= -PLAYER_FALL)
	//	{// �����痎������
	//		m_bGameOver = true;	// �Q�[���I�[�o�[�ɂ���
	//	}
	//}

//=============================================================================
// �E���ɂ��邩�ǂ������擾
//=============================================================================
bool CPlayer::GetRTriangle(void)
{
	return m_bRTriangle;
}

//=============================================================================
// �v���C���[�̈ʒu���擾���鏈��
//=============================================================================
D3DXVECTOR3 CPlayer::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 1�t���[���O�̃v���C���[�̈ʒu���擾���鏈��
//=============================================================================
D3DXVECTOR3 *CPlayer::GetPosOld(void)
{
	return &m_posOld;
}

//=============================================================================
// �v���C���[�̈ړ��ʂ��擾���鏈��
//=============================================================================
D3DXVECTOR3 CPlayer::GetMove(void)
{
	return m_move;
}

//=============================================================================
// �v���C���[���W�����v���Ă��邩�ǂ�����ݒ肷�鏈��
//=============================================================================
void CPlayer::SetJump(bool bJump)
{
	m_bJump = bJump;
}

//=============================================================================
// �v���C���[���W�����v���Ă��邩�ǂ������擾���鏈��
//=============================================================================
bool CPlayer::GetJump(void)
{
	return m_bJump;
}

//=============================================================================
// �v���C���[�̏�Ԃ�ݒ�
//=============================================================================
void CPlayer::SetState(STATE state)
{
	m_State = state;
}

//=============================================================================
// �v���C���[�̌������擾���鏈��
//=============================================================================
D3DXVECTOR3 CPlayer::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �v���C���[���S�[�����Ă��邩���擾���鏈��
//=============================================================================
bool CPlayer::GetGoal(void)
{
	return m_bGoal;
}

//=============================================================================
// �v���C���[���Q�[���I�[�o�[�����擾���鏈��
//=============================================================================
bool CPlayer::GetGameOver(void)
{
	return m_bGameOver;
}

//=============================================================================
// �u���b�N�̈ʒu���擾���鏈��
//=============================================================================
D3DXVECTOR3 CPlayer::GetBlockPos(void)
{
	return m_SetBlockPos;
}

//=============================================================================
// �e�Ƃ̓����蔻��̏���
//=============================================================================
void CPlayer::CollisonObstacle(D3DXVECTOR3 *pos, float fRadius)
{
	// ���[�h�̎擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// �̗͂��擾
	CHealth *pHealth = NULL;

	pHealth = CGame::GetHealth();
	

	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	CScene *pScene = NULL;

	// �擪�̃I�u�W�F�N�g���擾(���b�V���t�B�[���h�̗D�揇�ʂ�3������A3�ɂ���I�u�W�F�N�g�����ׂČ���)
	pScene = CScene::GetTop(BULLET_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_BULLET)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
				if (m_bBulletHit == false)
				{
					if (((CObstacle*)pScene)->CollisionPlayer(pos, fRadius) == true)
					{
						pHealth->CutHealth(CUT_LIFE);
						m_bBulletHit = true;
					}
				}
			}
		}

		// ���̃V�[���ɐi�߂�
		pScene = pSceneNext;
	}
}
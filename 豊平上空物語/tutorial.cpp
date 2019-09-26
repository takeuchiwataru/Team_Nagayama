//=============================================================================
//
// �`���[�g���A������ [tutorial.cpp]
// Author : ���R���
//
//=============================================================================
#include "tutorial.h"
#include "main.h"
#include "player.h"
#include "scene2D.h"
#include "input.h"
#include "fade.h"
#include "meshCylinder.h"
#include "manager.h"
#include "field.h"
#include "score.h"
#include "particle2D.h"
#include "particle3D.h"
#include "particleX.h"
#include "goal.h"
#include "pressAnyButton.h"
#include "sound.h"
#include "number.h"
#include "text.h"
#include "resource.h"
#include "health.h"
#include "tutoriallogo.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScore *CTutorial::m_pScore = NULL;
CNumBlock *CTutorial::m_pNumBlock = NULL;
CLife *CTutorial::m_pLife = NULL;
CHealth *CTutorial::m_pHealth = NULL;

//=============================================================================
// �`���[�g���A���̐�������
//=============================================================================
CTutorial *CTutorial::Create()
{
	CTutorial *pTutorial = NULL;

	if (pTutorial == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pTutorial = new CTutorial;

		if (pTutorial != NULL)
		{
			pTutorial->Init();
		}
	}

	return pTutorial;
}

//=============================================================================
// �`���[�g���A���̃R���X�g���N�^
//=============================================================================
CTutorial::CTutorial()
{
}

//=============================================================================
// �`���[�g���A���̃f�X�g���N�^
//=============================================================================
CTutorial::~CTutorial()
{
}

//=============================================================================
// �Q�[������������
//=============================================================================
HRESULT CTutorial::Init(void)
{
	//// �e�N�X�`����ǂݍ���

	//// ���f����ǂݍ���
	//// �p�[�e�B�N���̃��f���̃��[�h
	//CParticleX::LoadMat();

	//// �v���C���[�̐���
	//CPlayer::Create(D3DXVECTOR3(0.0f, 50.0f, 220.0f));

	//if (m_pScore == NULL)
	//{
	//	// �X�R�A�̐���
	//	m_pScore = CScore::Create(D3DXVECTOR3(800.0f, 70.0f, 0.0f), 37.0f, 60.0f);
	//}

	//if (m_pLife == NULL)
	//{
	//	// �u���b�N�̐��̐���
	//	m_pLife = CLife::Create(D3DXVECTOR3(260.0f, 75.0f, 0.0f), 40.0f);
	//}

	//CreateSceneObj();
	CTutorialLogo::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), SCREEN_WIDTH, SCREEN_HEIGHT, CResource::TEXTURE_TUTORIALLOGO);

	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, 650.0f, 0.0f), 150.0f, 100.0f, CResource::TEXTURE_ENTER);

	return S_OK;
}

//=============================================================================
// �`���[�g���A���I������
//=============================================================================
void CTutorial::Uninit(void)
{
	// �p�[�e�B�N��
	CParticleX::UnloadMat();

	// ������ɂ���
	m_pScore = NULL;
	m_pNumBlock = NULL;
	m_pLife = NULL;
	m_pHealth = NULL;

	// �S�ẴI�u�W�F�N�g�����
	CScene::ReleseAll();
}

//=============================================================================
// �`���[�g���A���X�V����
//=============================================================================
void CTutorial::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ���͏����擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �t�F�[�h�擾
	CFade *pFade = CManager::GetFade();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}

	// �f�o�b�N�p
	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_TITLE, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_2) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_TUTORIAL, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_3) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_4) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAMECLEAR, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_5) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_GAMEOVER, CFade::FADE_OUT);
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_6) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// ���肵���Ƃ���SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			// �t�F�[�h�����擾
			pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
		}
	}
}

//=============================================================================
// �`���[�g���A���`�揈��
//=============================================================================
void CTutorial::Draw(void)
{
}

//=============================================================================
//  ���̑��I�u�W�F�N�g�̐���
//=============================================================================
void CTutorial::CreateSceneObj(void)
{
	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 500.0f, 650.0f, 0.0f), 150.0f, 100.0f, CResource::TEXTURE_ENTER);

	// ���b�V���V�����_�[�̐���
	CMeshCylinder::Create(D3DXVECTOR3(0.0f, 1500.0f, 0.0f), 3000.0f, 30.0f);

	// ���|���S���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 1600.0f), 1000.0f, 4000.0f, 40.0f, 10.0f);
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 220.0f), 300.0f, 4000.0f, 20.0f, 1.0f);

	// �S�[���̐���
	CGoal::Create(D3DXVECTOR3(0.0f, 0.0f, 1800.0f));

	// �w�i���S�̐���
	m_pHealth = CHealth::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 450.0f, 150.0f, 0.0f), 90.0f, 40.0f);
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore *CTutorial::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// �u���b�N�̐��̎擾
//=============================================================================
CNumBlock *CTutorial::GetNumBlock(void)
{
	return m_pNumBlock;
}

//=============================================================================
// �c�@�̎擾
//=============================================================================
CLife *CTutorial::GetLife(void)
{
	return m_pLife;
}
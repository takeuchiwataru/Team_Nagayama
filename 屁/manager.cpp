//=============================================================================
//
// �}�l�[�W������ [manager.cpp]
// Author : ���R���
//
//=============================================================================
#include "manager.h"
#include "main.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "billboard.h"
#include "renderer.h"
#include "input.h"
#include "debugProc.h"
#include "game.h"
#include "title.h"
#include "tutorial.h"
#include "gameclear.h"
#include "gameover.h"
#include "ranking.h"
#include "fade.h"
#include "light.h"
#include "camera.h"
#include "number.h"
#include "sound.h"
#include "shadow.h"
#include "mask.h"
#include "text.h"
#include "resource.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CManager::MODE CManager::m_mode = CManager::MODE_NONE;
CRenderer *CManager::m_pRenderer = NULL;
CInputKeyboard *CManager::m_pInputKeyboard = NULL;
CInputJoypad *CManager::m_pInputJoypad = NULL;
CDebugProc *CManager::m_pDebugProc = NULL;
CGame *CManager::m_pGame = NULL;
CTitle *CManager::m_pTitle = NULL;
CTutorial *CManager::m_pTutorial = NULL;
CGameClear *CManager::m_pGameClear = NULL;
CGameOver *CManager::m_pGameOver = NULL;
CRanking *CManager::m_pRanking = NULL;
CFade *CManager::m_pFade = NULL;
CLight *CManager::m_pLight = NULL;
CCamera *CManager::m_pCamera = NULL;
int CManager::m_aScore[MAX_RANKING] = {};
int CManager::m_nScore = 0;
int CManager::m_nUpdateScore = 0;
CSound *CManager::m_pSound = NULL;
CMask *CManager::m_pMask = NULL;
CText *CManager::m_pText = NULL;

//=============================================================================
// �}�l�[�W���N���X�̃R���X�g���N�^
//=============================================================================
CManager::CManager()
{
	m_fData = 0.0f;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CManager::~CManager()
{
}

//=============================================================================
// �}�l�[�W������������
//=============================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �ŏ��̉��
	//m_mode = MODE_GAMEOVER;
	//m_mode = MODE_GAME;
	//m_mode = MODE_GAME;
	//m_mode = MODE_TITLE;
	m_mode = MODE_RANKING;;

	m_fData = 0.0f;

	int nScore = 10000;

	for (int nCnt = 0; nCnt < MAX_RANKING; nCnt++)
	{
		m_aScore[nCnt] = nScore;
		nScore -= 1000;
	}

	m_nUpdateScore = 0;

	if (m_pRenderer == NULL)
	{
		// �����_�����O�N���X�̐���
		m_pRenderer = new CRenderer;

		if (m_pRenderer != NULL)
		{
			// ����������
			if (FAILED(m_pRenderer->Init(hWnd, bWindow)))
			{
				return -1;
			}
		}
	}

	if (m_pInputKeyboard == NULL)
	{
		// ���̓N���X�̐���
		m_pInputKeyboard = new CInputKeyboard;

		if (m_pInputKeyboard != NULL)
		{
			m_pInputKeyboard->Init(hInstance, hWnd);
		}
	}

	if (m_pInputJoypad == NULL)
	{
		// ���̓N���X�̐���
		m_pInputJoypad = new CInputJoypad;

		if (m_pInputJoypad != NULL)
		{
			m_pInputJoypad->Init(hInstance, hWnd);
		}
	}

	if (m_pCamera == NULL)
	{
		// �J�����N���X�̐���
		m_pCamera = new CCamera;

		if (m_pCamera != NULL)
		{
			m_pCamera->Init();
		}
	}

	if (m_pFade == NULL)
	{
		m_pFade = CFade::Create();
	}

	if (m_pMask == NULL)
	{
		m_pMask = CMask::Create();
	}

	if (m_pLight == NULL)
	{
		// ���C�g�N���X�̐���
		m_pLight = new CLight;

		if (m_pLight != NULL)
		{
			m_pLight->Init();
		}
	}

	if (m_pText == NULL)
	{
		// ���C�g�N���X�̐���
		m_pText = new CText;
	}

#ifdef _DEBUG
	if (m_pDebugProc == NULL)
	{
		// �f�o�b�N�\���N���X�̐���
		m_pDebugProc = new CDebugProc;

		if (m_pDebugProc != NULL)
		{
			m_pDebugProc->Init();
		}
	}
#endif

	if (m_pSound == NULL)
	{
		// �T�E���h�N���X�̐���
		m_pSound = new CSound;

		if (m_pSound != NULL)
		{
			m_pSound->InitSound(hWnd);
		}
	}

	CShadow::Load();

	CResource::LoadModel();
	CResource::LoadTex();

	// ���[�h�ؑ�
	SetMode(m_mode);

	return S_OK;
}

//=============================================================================
// �}�l�[�W���I������
//=============================================================================
void CManager::Uninit(void)
{
	CShadow::UnLoad();

	if (m_pFade != NULL)
	{// �t�F�[�h�̏I��
		m_pFade->Uninit();
		delete m_pFade;
		m_pFade = NULL;
	}

	if (m_pRenderer != NULL)
	{// �����_�����O�N���X�̔j��
		// �I������
		m_pRenderer->Uninit();

		// ���������J��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	if (m_pCamera != NULL)
	{// �J�����N���X�̔j��
	 // �I������
		m_pCamera->Uninit();

		// ���������J��
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if (m_pLight != NULL)
	{// ���C�g�N���X�̔j��
	 // �I������
		m_pLight->Uninit();

		// ���������J��
		delete m_pLight;
		m_pLight = NULL;
	}

	if (m_pInputKeyboard != NULL)
	{// �����_�����O�N���X�̔j��
		 // �I������
		m_pInputKeyboard->Uninit();

		// ���������J��
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	if (m_pInputJoypad != NULL)
	{// ���̓N���X�̔j��
	 // �I������
		m_pInputJoypad->Uninit();

		// ���������J��
		delete m_pInputJoypad;
		m_pInputJoypad = NULL;
	}

	if (m_pSound != NULL)
	{// ���̓N���X�̔j��
	 // �I������
		m_pSound->UninitSound();

		// ���������J��
		delete m_pSound;
		m_pSound = NULL;
	}

	if (m_pMask != NULL)
	{// �e�̏I��
		m_pMask->Uninit();
		delete m_pMask;
		m_pMask = NULL;
	}

	if (m_pText != NULL)
	{// �e�̏I��
		delete m_pText;
		m_pText = NULL;
	}

	switch (m_mode)
	{
		// �^�C�g����ʏI������
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pTitle->Uninit();

			// ���������J��
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
		// �`���[�g���A����ʏI������
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pTutorial->Uninit();

			// ���������J��
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
		// �Q�[����ʏI������
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pGame->Uninit();

			// ���������J��
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
		// �Q�[���N���A��ʏI������
	case MODE_GAMECLEAR:
		if (m_pGameClear != NULL)
		{
			m_pGameClear->Uninit();

			// ���������J��
			delete m_pGameClear;
			m_pGameClear = NULL;
		}
		break;
		// �Q�[���I�[�o�[��ʏI������
	case MODE_GAMEOVER:
		if (m_pGameOver != NULL)
		{
			m_pGameOver->Uninit();

			// ���������J��
			delete m_pGameOver;
			m_pGameOver = NULL;
		}
		break;
		// �����L���O��ʏI������
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_nUpdateScore = 0;
			m_pRanking->Uninit();

			// ���������J��
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	}

#ifdef _DEBUG
	if (m_pDebugProc != NULL)
	{// �f�o�b�N�\���N���X�̔j��
		// �I������
		m_pDebugProc->Uninit();

		// ���������J��
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}
#endif

	CResource::UnloadModel();
	CResource::UnloadTex();

	// �S�ẴI�u�W�F�N�g�����
	CScene::ReleseAll();
}

//=============================================================================
// �}�l�[�W���X�V����
//=============================================================================
void CManager::Update(void)
{
#ifdef _DEBUG
	// �f�o�b�N�\��������
	CDebugProc::ReleseStr();
#endif

	if (m_pRenderer != NULL)
	{// �����_���[�X�V����
		m_pRenderer->Update();
	}

	if (m_pCamera != NULL)
	{// �J�����X�V����
		m_pCamera->Update();
	}

	if (m_pLight != NULL)
	{// ���C�g�X�V����
		m_pLight->Update();
	}

	if (m_pInputKeyboard != NULL)
	{// �L�[�{�[�h���͍X�V����
		m_pInputKeyboard->Update();
	}

	if (m_pInputJoypad != NULL)
	{// �L�[�{�[�h���͍X�V����
		m_pInputJoypad->Update();
	}

	if (m_pFade != NULL)
	{// �L�[�{�[�h���͍X�V����
		m_pFade->Update();
	}

	switch (m_mode)
	{
		// �^�C�g����ʍX�V����
	case MODE_TITLE:
#ifdef _DEBUG
		CDebugProc::Print("c", "�^�C�g��");
#endif
		m_pTitle->Update();
		break;
		// �`���[�g���A����ʍX�V����
	case MODE_TUTORIAL:
#ifdef _DEBUG
		CDebugProc::Print("c", "�`���[�g���A��");
#endif
		m_pTutorial->Update();
		break;
		// �Q�[����ʍX�V����
	case MODE_GAME:
#ifdef _DEBUG
		CDebugProc::Print("c", "�Q�[��");
#endif
		m_pGame->Update();
		break;
		// �Q�[���N���A��ʍX�V����
	case MODE_GAMECLEAR:
#ifdef _DEBUG
		CDebugProc::Print("c", "�Q�[���N���A");
#endif
		m_pGameClear->Update();
		break;
		// �Q�[���I�[�o�[��ʍX�V����
	case MODE_GAMEOVER:
#ifdef _DEBUG
		CDebugProc::Print("c", "�Q�[���I�[�o�[");
#endif
		m_pGameOver->Update();
		break;
		// �����L���O��ʏI������
	case MODE_RANKING:
#ifdef _DEBUG
		CDebugProc::Print("c", "�����L���O");
#endif
		m_pRanking->Update();
		break;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CManager::Draw(void)
{
	if (m_pCamera != NULL)
	{// �J������ݒ�
		m_pCamera->SetCamera();
	}

	if (m_pRenderer != NULL)
	{// �����_���[�`�揈��
		m_pRenderer->Draw();
	}

	switch (m_mode)
	{
		// �^�C�g����ʕ`�揈��
	case MODE_TITLE:
		m_pTitle->Draw();
		break;
		// �^�C�g����ʕ`�揈��
	case MODE_TUTORIAL:
		m_pTutorial->Draw();
		break;
		// �Q�[����ʕ`�揈��
	case MODE_GAME:
		m_pGame->Draw();
		break;
		// �Q�[���N���A��ʕ`�揈��
	case MODE_GAMECLEAR:
		m_pGameClear->Draw();
		break;
		// �Q�[���I�[�o�[��ʕ`�揈��
	case MODE_GAMEOVER:
		m_pGameOver->Draw();
		break;
		// �����L���O��ʕ`�揈��
	case MODE_RANKING:
		m_pRanking->Draw();
		break;
	}
}

//=============================================================================
// �f�o�C�X�̐ݒ�
//=============================================================================
void CManager::SetMode(MODE mode)
{
	switch (m_mode)
	{
		// �^�C�g����ʏI������
	case MODE_TITLE:
		if (m_pTitle != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TITLE);

			m_pTitle->Uninit();

			// ���������J��
			delete m_pTitle;
			m_pTitle = NULL;
		}
		break;
		// �`���[�g���A����ʏI������
	case MODE_TUTORIAL:
		if (m_pTutorial != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL0);
			m_pTutorial->Uninit();

			// ���������J��
			delete m_pTutorial;
			m_pTutorial = NULL;
		}
		break;
		// �Q�[����ʏI������
	case MODE_GAME:
		if (m_pGame != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_TUTORIAL);
			m_pGame->Uninit();

			// ���������J��
			delete m_pGame;
			m_pGame = NULL;
		}
		break;
		// �Q�[���N���A��ʏI������
	case MODE_GAMECLEAR:
		if (m_pGameClear != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_RESULTCLEAR);
			m_pGameClear->Uninit();

			// ���������J��
			delete m_pGameClear;
			m_pGameClear = NULL;
		}
		break;
		// �Q�[���I�[�o�[��ʏI������
	case MODE_GAMEOVER:
		if (m_pGameOver != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_RESULTOVER);
			m_pGameOver->Uninit();

			// ���������J��
			delete m_pGameOver;
			m_pGameOver = NULL;
		}
		break;
		// �����L���O��ʏI������
	case MODE_RANKING:
		if (m_pRanking != NULL)
		{
			m_pSound->StopSound(CSound::SOUND_LABEL_BGM_RANKING);
			m_nUpdateScore = 0;
			m_pRanking->Uninit();

			// ���������J��
			delete m_pRanking;
			m_pRanking = NULL;
		}
		break;
	}

	switch (mode)
	{
		// �^�C�g����ʏ���������
	case MODE_TITLE:
		if (m_pTitle == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// �Q�[���𐶐�
			m_pTitle = CTitle::Create();
			m_nUpdateScore = MAX_RANKING + 1;
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
		}
		break;
		// �^�C�g����ʏ���������
	case MODE_TUTORIAL:
		if (m_pTutorial == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// �Q�[���𐶐�
			m_pTutorial = CTutorial::Create();
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		}
		break;
		// �Q�[����ʏ���������
	case MODE_GAME:
		if (m_pGame == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// �Q�[���𐶐�
			m_pGame = CGame::Create();
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TUTORIAL);
		}
		break;
		// �Q�[���N���A��ʏ���������
	case MODE_GAMECLEAR:
		if (m_pGameClear == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// �Q�[���𐶐�
			m_pGameClear = CGameClear::Create();
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULTCLEAR);
		}
		break;

		// �Q�[���N���A��ʏ���������
	case MODE_GAMEOVER:
		if (m_pGameOver == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// �Q�[���𐶐�
			m_pGameOver = CGameOver::Create();
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RESULTOVER);
		}
		break;
		// �����L���O��ʏ���������
	case MODE_RANKING:
		if (m_pRanking == NULL)
		{
			if (m_pCamera != NULL)
			{
				m_pCamera->Init();
			}
			// �Q�[���𐶐�
			m_pRanking = CRanking::Create();
			m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RANKING);
		}
		break;
	}
	m_mode = mode;
}

//=============================================================================
// �����_���[�̎擾
//=============================================================================
CFade *CManager::GetFade(void)
{
	return m_pFade;
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}

//=============================================================================
// �����_���[�̎擾
//=============================================================================
CRenderer *CManager::GetRenderer(void)
{
	return m_pRenderer;
}

//=============================================================================
// ���͏��̎擾
//=============================================================================
CInputKeyboard *CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}

//=============================================================================
// ���͏��̎擾
//=============================================================================
CInputJoypad *CManager::GetInputJoypad(void)
{
	return m_pInputJoypad;
}

//=============================================================================
// �J�����̎擾
//=============================================================================
CCamera *CManager::GetCamera(void)
{
	return m_pCamera;
}

//=============================================================================
// �����L���O�̎擾
//=============================================================================
int CManager::GetRanking(int nIdx)
{
	return m_aScore[nIdx];
}

//=============================================================================
// �����L���O�X�R�A�̎擾
//=============================================================================
void CManager::GetRankingScore(int nScore)
{
	int nData = 0;
	int nUpdateScore = 0;

	if (m_aScore[MAX_RANKING - 1] <= nScore)
	{
		m_aScore[MAX_RANKING - 1] = nScore;
		nUpdateScore = nScore;
	}
	else
	{
		m_nUpdateScore = MAX_RANKING + 1;
	}

	for (int nCntData = 0; nCntData < MAX_RANKING; nCntData++)
	{// �傫�������ёւ�
		for (int nCntNumber = 0; nCntNumber < MAX_RANKING - 1; nCntNumber++)
		{
			if (m_aScore[nCntNumber] < m_aScore[nCntNumber + 1])
			{
				nData = m_aScore[nCntNumber];
				m_aScore[nCntNumber] = m_aScore[nCntNumber + 1];
				m_aScore[nCntNumber + 1] = nData;
			}
		}

		if (m_aScore[nCntData] == nUpdateScore)
		{
			m_nUpdateScore = nCntData;
		}
	}
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
void CManager::GetScore(int nScore)
{
	m_nScore = nScore;
}

//=============================================================================
// �X�R�A�̐ݒ�
//=============================================================================
int CManager::SetScore(void)
{
	return m_nScore;
}

//=============================================================================
// �X�R�A�̃��Z�b�g
//=============================================================================
void CManager::ReleaseScore(void)
{
	m_nScore = 0;
}

//=============================================================================
// �A�b�v�f�[�g�X�R�A�̎擾
//=============================================================================
int CManager::GetUpdateScore(void)
{
	return m_nUpdateScore;
}

//=============================================================================
// ���y���̎擾
//=============================================================================
CSound *CManager::GetSound(void)
{
	return m_pSound;
}

//=============================================================================
// �}�X�N�̎擾
//=============================================================================
CMask *CManager::GetMask(void)
{
	return m_pMask;
}

//=============================================================================
// �e�L�X�g�ǂݍ��݃N���X�̎擾
//=============================================================================
CText *CManager::GetText(void)
{
	return m_pText;
}
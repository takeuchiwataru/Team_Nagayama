//=============================================================================
//
// �Q�[���I�[�o�[�̏��� [gameover.cpp]
// Author : ���R���
//
//=============================================================================
#include "gameover.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "meshCylinder.h"
#include "sound.h"
#include "particleX.h"
#include "score.h"
#include "pressAnyButton.h"
#include "number.h"
#include "text.h"
#include "resource.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CBlock *CGameOver::m_pBlock[MAX_BLOCK] = {};
CScore *CGameOver::m_pScore = NULL;

//=============================================================================
// �Q�[���I�[�o�[�N���X�̃R���X�g���N�^
//=============================================================================
CGameOver::CGameOver()
{
	// �l���N���A
	m_nNumModel = 0;
	m_nBlockTimer = 0;
	m_bSetBlock = true;
	m_nCntBlock = 0;
	m_nScore = 0;
	m_nCntScore = 0;
}

//=============================================================================
// �Q�[���I�[�o�[�̐�������
//=============================================================================
CGameOver *CGameOver::Create()
{
	CGameOver *pGameOver = NULL;

	if (pGameOver == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pGameOver = new CGameOver;

		if (pGameOver != NULL)
		{
			pGameOver->Init();
		}
	}
	return pGameOver;
}

//=============================================================================
// �Q�[���I�[�o�[�N���X�̃f�X�g���N�^
//=============================================================================
CGameOver::~CGameOver()
{
}

//=============================================================================
// �Q�[���I�[�o�[�̏���������
//=============================================================================
HRESULT CGameOver::Init(void)
{
	// �l�̏�����
	m_nCntTimer = 0;

	m_nNumModel = 0;
	m_nBlockTimer = 0;
	m_bSetBlock = true;
	m_nCntBlock = 0;
	m_nScore = 0;
	m_nCntScore = 0;

	// �p�[�e�B�N���̃��f���̃��[�h
	CParticleX::LoadMat();

	//LoadCharFall();

	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), 200.0f, 170.0f, CResource::TEXTURE_ANYBUTTON);

	if (m_pScore == NULL)
	{
		int nScore = 0;

		nScore = CManager::SetScore();

		m_pScore = CScore::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 + 280.0f, SCREEN_HEIGHT / 2 + 70.0f, 0.0f), 70.0f, 120.0f);
		m_pScore->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

		m_pScore->AddScore(nScore);
	}

	int nCnt = 0;
	

	// ���b�V���V�����_�[�̐���
	CMeshCylinder::Create(D3DXVECTOR3(700.0f, 1700.0f, 0.0f), 2000.0, 30.0f);

	return S_OK;
}

//=============================================================================
// �Q�[���I�[�o�[�̏I������
//=============================================================================
void CGameOver::Uninit(void)
{
	// �p�[�e�B�N��
	CParticleX::UnloadMat();

	m_pScore = NULL;

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK + 1; nCntBlock++)
	{
		m_pBlock[nCntBlock] = NULL;
	}

	// �S�ẴI�u�W�F�N�g�����
	CScene::ReleseAll();
}

//=============================================================================
// �Q�[���I�[�o�[�̍X�V����
//=============================================================================
void CGameOver::Update(void)
{
	CManager::MODE mode;
	mode = CManager::GetMode();

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

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true || pInputJoypad->GetAnyButton(0) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// ���肵���Ƃ���SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			CManager::ReleaseScore();
			pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
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
}

//=============================================================================
// �Q�[���I�[�o�[�̕`�揈��
//=============================================================================
void CGameOver::Draw(void)
{
}

//=============================================================================
// ���f���̃��[�h
//=============================================================================
void CGameOver::LoadCharFall()
{
	//FILE *pFile = NULL;

	//CManager::MODE mode;
	//mode = CManager::GetMode();

	//CText *pText;
	//pText = CManager::GetText();

	//int nCharType = 0;

	//pFile = fopen(OBJECT_FILE_GAMEOVER, "r");

	//if (pFile != NULL)
	//{
	//	char *pStrCur;		// ������̐擪�ւ̃|�C���^
	//	char aLine[256];	// ������ǂݍ��ݗp�i1�s���j
	//	char aStr[256];		// �����񔲂��o���p

	//	pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
	//	pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
	//	strcpy(&aStr[0], pStrCur);

	//	if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
	//	{
	//		while (1)
	//		{
	//			pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
	//			pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
	//			strcpy(&aStr[0], pStrCur);


	//			if (memcmp(&aStr[0], "NUM_MODEL =", strlen("NUM_MODEL =")) == 0)
	//			{
	//				pStrCur += strlen("NUM_MODEL =");	// ���o��

	//				m_nNumModel = atoi(pStrCur);	// �������l�ɕϊ�


	//				for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	//				{
	//					pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
	//					pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
	//					strcpy(&aStr[0], pStrCur);

	//					D3DXVECTOR3 pos;
	//					D3DXVECTOR3 rot;

	//					if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
	//					{// �ʒu
	//						pStrCur += strlen("POS =");	// ���o��
	//						int nWord;

	//						// float�ɕϊ����đ��
	//						pos.x = (float)atof(pStrCur);

	//						// aStr[0]�ɉ����������Ă��邩���m���߂�
	//						nWord = pText->PopString(pStrCur, &aStr[0]);

	//						// ���܂Ői�߂�
	//						pStrCur += nWord;

	//						// float�ɕϊ����đ��
	//						pos.y = (float)atof(pStrCur);

	//						// aStr[0]�ɉ����������Ă��邩���m���߂�
	//						nWord = pText->PopString(pStrCur, &aStr[0]);

	//						// ���܂Ői�߂�
	//						pStrCur += nWord;

	//						// float�ɕϊ����đ��
	//						pos.z = (float)atof(pStrCur);
	//					}

	//					pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
	//					pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
	//					strcpy(&aStr[0], pStrCur);

	//					if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
	//					{// �ʒu
	//						pStrCur += strlen("ROT =");	// ���o��

	//						int nWord;

	//						// float�ɕϊ����đ��
	//						rot.x = (float)atof(pStrCur);

	//						// aStr[0]�ɉ����������Ă��邩���m���߂�
	//						nWord = pText->PopString(pStrCur, &aStr[0]);

	//						// ���܂Ői�߂�
	//						pStrCur += nWord;

	//						// float�ɕϊ����đ��
	//						rot.y = (float)atof(pStrCur);

	//						// aStr[0]�ɉ����������Ă��邩���m���߂�
	//						nWord = pText->PopString(pStrCur, &aStr[0]);

	//						// ���܂Ői�߂�
	//						pStrCur += nWord;

	//						// float�ɕϊ����đ��
	//						rot.z = (float)atof(pStrCur);
	//					}

	//					// �ʒu������Ă���
	//					m_BlockPpos[nCntModel] = pos;

	//					
	//				}
	//			}

	//			if (memcmp(&aStr[0], "ENDSCRIPT", strlen("ENDSCRIPT")) == 0)
	//			{
	//				break;
	//			}
	//		}
	//	}
	//	fclose(pFile);
	//}
}

//=============================================================================
// �u���b�N
//=============================================================================
void CGameOver::Block()
{
	
}
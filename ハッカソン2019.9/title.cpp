//=============================================================================
//
// �^�C�g���̏��� [title.cpp]
// Author : ���R���
//
//=============================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "fade.h"
#include "scene2D.h"
#include "player.h"
#include "particleX.h"
#include "meshCylinder.h"
#include "sound.h"
#include "field.h"
#include "pressAnyButton.h"
#include "text.h"
#include "resource.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CBlock *CTitle::m_pBlock[225] = {};

//=============================================================================
// �^�C�g���N���X�̃R���X�g���N�^
//=============================================================================
CTitle::CTitle()
{
	// �l���N���A
	//m_nCntTimer = 0;

	for (int nCntPos = 0; nCntPos < 220; nCntPos++)
	{
		m_BlockPpos[nCntPos] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	m_nBlockTimer = 0;
	m_nCntBlock = 0;
	m_nBlock = 0;
	m_nCntFrame = 0;
	m_nCntTimer = 0;
	m_bSetBlock = true;
}

//=============================================================================
// �^�C�g���̐�������
//=============================================================================
CTitle *CTitle::Create()
{
	CTitle *pTitle = NULL;

	if (pTitle == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pTitle = new CTitle;

		if (pTitle != NULL)
		{
			pTitle->Init();
		}
	}
	return pTitle;
}

//=============================================================================
// �^�C�g���N���X�̃f�X�g���N�^
//=============================================================================
CTitle::~CTitle()
{
}

//=============================================================================
// �^�C�g���̏���������
//=============================================================================
HRESULT CTitle::Init()
{
	// �l��������
	//m_nCntTimer = 0;

	m_nBlockTimer = 0;
	m_nCntBlock = 0;
	m_nBlock = 50;
	m_nCntFrame = 0;
	m_nCntTimer = 0;
	m_bSetBlock = true;

	// �p�[�e�B�N���̃}�e���A���̃��[�h
	CParticleX::LoadMat();

	CPressAnyButton::Create(D3DXVECTOR3(SCREEN_WIDTH / 2, 650.0f, 0.0f), 200.0f, 170.0f, CResource::TEXTURE_ANYBUTTON);

	// ���b�V���V�����_�[�̐���
	CMeshCylinder::Create(D3DXVECTOR3(700.0f, 1700.0f, 0.0f), 1500.0, 30.0f);


	LoadMap();

	return S_OK;
}

//=============================================================================
// �^�C�g���̏I������
//=============================================================================
void CTitle::Uninit(void)
{
	// ���f���ƃ}�e���A���̏������
	// �p�[�e�B�N��
	CParticleX::UnloadMat();

	for (int nCntBlock = 0; nCntBlock < 225; nCntBlock++)
	{
		m_pBlock[nCntBlock] = NULL;
	}

	// �S�ẴI�u�W�F�N�g�����
	CScene::ReleseAll();
}

//=============================================================================
// �^�C�g���̍X�V����
//=============================================================================
void CTitle::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �t�F�[�h�擾
	CFade *pFade = CManager::GetFade();

	// ���͏����擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true  || pInputJoypad->GetAnyButton(0) == true)
	{
		if (CFade::GetFade() == CFade::FADE_NONE)
		{
			// ���肵���Ƃ���SE
			pSound->PlaySound(CSound::SOUND_LABEL_SE_ENTER);
			pFade->SetFade(CManager::MODE_TUTORIAL, CFade::FADE_OUT);
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

	m_nCntTimer++;

	if (m_nCntTimer >= 1000)
	{
		pFade->SetFade(CManager::MODE_RANKING, CFade::FADE_OUT);
		m_nCntTimer = 0;
	}
	//pFade->SetFade(CManager::MODE_TUTORIAL, CFade::FADE_OUT);
}

//=============================================================================
// �^�C�g���̕`�揈��
//=============================================================================
void CTitle::Draw(void)
{
}

//=============================================================================
// ���f���̃��[�h
//=============================================================================
void CTitle::LoadMap()
{
	//FILE *pFile = NULL;

	//CManager::MODE mode;
	//mode = CManager::GetMode();

	//CText *pText;
	//pText = CManager::GetText();

	//int nNumModel = 0;
	//
	//pFile = fopen(OBJECT_FILE_TITLE, "r");

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

	//				nNumModel = atoi(pStrCur);	// �������l�ɕϊ�
	//			}

	//			if (memcmp(&aStr[0], "MODEL INFO", strlen("MODEL INFO")) == 0)
	//			{
	//				for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
	//				{
	//					pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
	//					pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
	//					strcpy(&aStr[0], pStrCur);

	//					int nCntTimer = 0;

	//					if (memcmp(&aStr[0], "ModelType", strlen("ModelType")) == 0)
	//					{
	//						pStrCur += strlen("ModelType");	// ���o��

	//						int nType = atoi(pStrCur);	// �������l�ɕϊ�

	//						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
	//						pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
	//						strcpy(&aStr[0], pStrCur);

	//						D3DXVECTOR3 pos;
	//						D3DXVECTOR3 rot;

	//						if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
	//						{// �ʒu
	//							pStrCur += strlen("POS =");	// ���o��
	//							int nWord;

	//							// float�ɕϊ����đ��
	//							pos.x = (float)atof(pStrCur);

	//							// aStr[0]�ɉ����������Ă��邩���m���߂�
	//							nWord = pText->PopString(pStrCur, &aStr[0]);

	//							// ���܂Ői�߂�
	//							pStrCur += nWord;

	//							// float�ɕϊ����đ��
	//							pos.y = (float)atof(pStrCur);

	//							// aStr[0]�ɉ����������Ă��邩���m���߂�
	//							nWord = pText->PopString(pStrCur, &aStr[0]);

	//							// ���܂Ői�߂�
	//							pStrCur += nWord;

	//							// float�ɕϊ����đ��
	//							pos.z = (float)atof(pStrCur);
	//						}

	//						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
	//						pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
	//						strcpy(&aStr[0], pStrCur);

	//						if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
	//						{// ����
	//							pStrCur += strlen("ROT =");	// ���o��

	//							int nWord;

	//							// float�ɕϊ����đ��
	//							rot.x = (float)atof(pStrCur);

	//							// aStr[0]�ɉ����������Ă��邩���m���߂�
	//							nWord = pText->PopString(pStrCur, &aStr[0]);

	//							// ���܂Ői�߂�
	//							pStrCur += nWord;

	//							// float�ɕϊ����đ��
	//							rot.y = (float)atof(pStrCur);

	//							// aStr[0]�ɉ����������Ă��邩���m���߂�
	//							nWord = pText->PopString(pStrCur, &aStr[0]);

	//							// ���܂Ői�߂�
	//							pStrCur += nWord;

	//							// float�ɕϊ����đ��
	//							rot.z = (float)atof(pStrCur);
	//						}

	//						// �ʒu������Ă���
	//						m_BlockPpos[nCntModel].x = pos.x;
	//						m_BlockPpos[nCntModel].y = pos.y;
	//						m_BlockPpos[nCntModel].z = pos.z;
	//					}
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
// �u���b�N�̈ʒu���擾���鏈��
//=============================================================================
D3DXVECTOR3 CTitle::GetBlockPos(int nCntBlock)
{
	return m_BlockPpos[nCntBlock];
}
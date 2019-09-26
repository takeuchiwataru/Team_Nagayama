//=============================================================================
//
// �Q�[������ [game.cpp]
// Author : ���R���
//
//=============================================================================
#include "game.h"
#include "manager.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "billboard.h"
#include "input.h"
#include "debugProc.h"
#include "player.h"
#include "scene.h"
#include "camera.h"
#include "meshCylinder.h"
#include "fade.h"
#include "goal.h"
#include "pause.h"
#include "score.h"
#include "particle2D.h"
#include "particle3D.h"
#include "particleX.h"
#include "polygon.h"
#include "coin.h"
#include "field.h"
#include "number.h"
#include "life.h"
#include "text.h"
#include "health.h"
#include "obstacle.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define COIN_FILE_GAME	"data\\TEXT\\modelCoin.txt"			// �ݒu�������f���������o���e�L�X�g
#define SCORE_POS		(D3DXVECTOR3(800.0f, 70.0f, 0.0f))	// �X�R�A�̈ʒu
#define SCORE_HEIGHT	(37.0f)								// �X�R�A�̃T�C�Y
#define SCORE_WIDTH		(60.0f)								// �X�R�A�̃T�C�Y
#define NUMBLOCK_POS	(D3DXVECTOR3(1170.0f, 70.0f, 0.0f))	// �u���b�N�̌��̈ʒu
#define NUMBLOCK_SIZE	(37.0f)								// �u���b�N�̌��̃T�C�Y
#define NUMCOIN_POS	(D3DXVECTOR3(1170.0f, 200.0f, 0.0f))	// �R�C���̌��̈ʒu
#define NUMCOIN_SIZE	(37.0f)								// �R�C���̌��̃T�C�Y
#define NUMBLOCKLOGO_POS	(D3DXVECTOR3(1030.0f, 70.0f, 0.0f))	// �u���b�N�̌����S�̈ʒu
#define NUMBLOCKLOGO_WIDTH	(50.0f)								// �u���b�N�̌����S�̃T�C�Y
#define NUMBLOCKLOGO_HEIGHT	(30.0f)								// �u���b�N�̌����S�̃T�C�Y
#define LIFE_POS		(D3DXVECTOR3(260.0f, 75.0f, 0.0f))	// ���C�t�̈ʒu
#define LIFE_SIZE		(40.0f)								// ���C�t�̃T�C�Y
#define PLAYERCROSS_POS	(D3DXVECTOR3(150.0f, 70.0f, 0.0f))	// �c�@���S�̈ʒu
#define PLAYERCROSS_WIDTH	(70.0f)							// �c�@���S�̃T�C�Y
#define PLAYERCROSS_HEIGHT	(50.0f)							// �c�@���S�̃T�C�Y

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CScore *CGame::m_pScore = NULL;
CNumBlock *CGame::m_pNumBlock = NULL;
CLife *CGame::m_pLife = NULL;
CHealth *CGame::m_pHealth = NULL;
CPlayer *CGame::m_pPlayer = NULL;

//=============================================================================
// �Q�[���N���X�̃R���X�g���N�^
//=============================================================================
CGame::CGame()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CGame::~CGame()
{
}

//=============================================================================
// �Q�[���̐�������
//=============================================================================
CGame *CGame::Create()
{
	CGame *pGame = NULL;

	if (pGame == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pGame = new CGame;

		if (pGame != NULL)
		{
			pGame->Init();
		}
	}

	return pGame;
}

//=============================================================================
// �Q�[������������
//=============================================================================
HRESULT CGame::Init(void)
{
	LoadMat();

	// �J�����擾
	CCamera *pCamera;
	pCamera = CManager::GetCamera();

	pCamera->Init();

	// �v���C���[�̐���
	if (m_pPlayer == NULL)
	{
		m_pPlayer = CPlayer::Create(D3DXVECTOR3(0.0f, 70000.0f, 250.0f));
		//CPlayer::Create(D3DXVECTOR3(80.0f, 50.0f, 250.0f));
	}

	BlockCreate();
	FieldCreate();

	if (m_pScore == NULL)
	{
		// �X�R�A�̐���
		m_pScore = CScore::Create(SCORE_POS, SCORE_HEIGHT, SCORE_WIDTH);
	}

	if (m_pLife == NULL)
	{
		// ���C�t�̐���
		m_pLife = CLife::Create(LIFE_POS, LIFE_SIZE);
	}

	// �w�i���S�̐���
	m_pHealth = CHealth::Create(D3DXVECTOR3(SCREEN_WIDTH / 2 - 450.0f, 150.0f, 0.0f), 90.0f, 40.0f);

	return S_OK;
}

//=============================================================================
// �Q�[���I������
//=============================================================================
void CGame::Uninit(void)
{
	CCoin::SetNumCoin(0);

	// �}�e���A���̉��
	UnLoadMat();

	// ������ɂ���
	m_pScore = NULL;
	m_pNumBlock = NULL;
	m_pLife = NULL;
	m_pHealth = NULL;
	m_pPlayer = NULL;

	// �S�ẴI�u�W�F�N�g�����
	CScene::ReleseAll();
}

//=============================================================================
// �Q�[���X�V����
//=============================================================================
void CGame::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �t�F�[�h�擾
	CFade *pFade = CManager::GetFade();

	//if (CPlayer::GetGoal() == true)
	//{// �S�[��������
	//	if (CFade::GetFade() == CFade::FADE_NONE)
	//	{// �Q�[���N���A�ɑJ��
	//		CManager::GetRankingScore(m_pScore->GetScore());
	//		CManager::GetScore(m_pScore->GetScore());

	//		pFade->SetFade(CManager::MODE_GAMECLEAR, CFade::FADE_OUT);
	//	}
	//}
	//else if (CPlayer::GetGameOver() == true)
	//{
	//	if (CFade::GetFade() == CFade::FADE_NONE)
	//	{// �Q�[���I�[�o�[�ɑJ��
	//		CManager::GetRankingScore(m_pScore->GetScore());
	//		CManager::GetScore(m_pScore->GetScore());
	//		pFade->SetFade(CManager::MODE_GAMEOVER, CFade::FADE_OUT);
	//	}
	//}

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
// �`�揈��
//=============================================================================
void CGame::Draw(void)
{

}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
CScore *CGame::GetScore(void)
{
	return m_pScore;
}

//=============================================================================
// �u���b�N�̐��̎擾
//=============================================================================
CNumBlock *CGame::GetNumBlock(void)
{
	return m_pNumBlock;
}

//=============================================================================
// �c�@�̎擾
//=============================================================================
CLife *CGame::GetLife(void)
{
	return m_pLife;
}

//=============================================================================
// ���f���̃��[�h
//=============================================================================
void CGame::LoadCoin()
{
	FILE *pFile = NULL;

	CManager::MODE mode;
	mode = CManager::GetMode();

	CText *pText;
	pText = CManager::GetText();

	int nNumModel = 0;

	pFile = fopen(COIN_FILE_GAME, "r");

	if (pFile != NULL)
	{
		char *pStrCur;		// ������̐擪�ւ̃|�C���^
		char aLine[256];	// ������ǂݍ��ݗp�i1�s���j
		char aStr[256];		// �����񔲂��o���p

		pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
		pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
		strcpy(&aStr[0], pStrCur);

		if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
		{
			while (1)
			{
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
				pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
				strcpy(&aStr[0], pStrCur);

				if (memcmp(&aStr[0], "NUM_MODEL =", strlen("NUM_MODEL =")) == 0)
				{
					pStrCur += strlen("NUM_MODEL =");	// ���o��

					nNumModel = atoi(pStrCur);	// �������l�ɕϊ�
				}

				if (memcmp(&aStr[0], "MODEL INFO", strlen("MODEL INFO")) == 0)
				{
					for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
					{
						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
						pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
						strcpy(&aStr[0], pStrCur);

						int nCntTimer = 0;

						if (memcmp(&aStr[0], "ModelType", strlen("ModelType")) == 0)
						{
							pStrCur += strlen("ModelType");	// ���o��

							int nType = atoi(pStrCur);	// �������l�ɕϊ�

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
							pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
							strcpy(&aStr[0], pStrCur);

							D3DXVECTOR3 pos;
							D3DXVECTOR3 rot;

							if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
							{// �ʒu
								pStrCur += strlen("POS =");	// ���o��
								int nWord;

								// float�ɕϊ����đ��
								pos.x = (float)atof(pStrCur);

								// aStr[0]�ɉ����������Ă��邩���m���߂�
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// ���܂Ői�߂�
								pStrCur += nWord;

								// float�ɕϊ����đ��
								pos.y = (float)atof(pStrCur);

								// aStr[0]�ɉ����������Ă��邩���m���߂�
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// ���܂Ői�߂�
								pStrCur += nWord;

								// float�ɕϊ����đ��
								pos.z = (float)atof(pStrCur);
							}

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
							pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
							strcpy(&aStr[0], pStrCur);

							if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
							{// �ʒu
								pStrCur += strlen("ROT =");	// ���o��

								int nWord;

								// float�ɕϊ����đ��
								rot.x = (float)atof(pStrCur);

								// aStr[0]�ɉ����������Ă��邩���m���߂�
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// ���܂Ői�߂�
								pStrCur += nWord;

								// float�ɕϊ����đ��
								rot.y = (float)atof(pStrCur);

								// aStr[0]�ɉ����������Ă��邩���m���߂�
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// ���܂Ői�߂�
								pStrCur += nWord;

								// float�ɕϊ����đ��
								rot.z = (float)atof(pStrCur);
							}

							// �R�C������
							CCoin::Create(pos);
						}
					}
				}

				if (memcmp(&aStr[0], "ENDSCRIPT", strlen("ENDSCRIPT")) == 0)
				{
					break;
				}
			}
		}
		fclose(pFile);
	}
}

//=============================================================================
// �}�e���A���̃��[�h
//=============================================================================
void CGame::LoadMat()
{
	CParticleX::LoadMat();
}

//=============================================================================
// �}�e���A���̊J��
//=============================================================================
void CGame::UnLoadMat()
{
	CParticleX::UnloadMat();
}

//=============================================================================
// �u���b�N�̐���
//=============================================================================
void CGame::BlockCreate()
{
}

//=============================================================================
// �t�B�[���h�̐���
//=============================================================================
void CGame::FieldCreate()
{
	// ���b�V���t�B�[���h�̐���
	//CMeshField::Create(D3DXVECTOR3(-200.0f, -1.5f, 1700.0f));

	for (int nCntMesh = 1; nCntMesh < 13; nCntMesh++)
	{// ���b�V���V�����_�[�̐���
		CMeshCylinder::Create(D3DXVECTOR3(-150.0f, 6000.0f * nCntMesh, 500.0f), 2000.0f, 30.0f);
	}

	// �S�[���̐���
	CGoal::Create(D3DXVECTOR3(1166.0f, 0.0f, 533.0f));

	// ���|���S���̐���
	CFeild::Create(D3DXVECTOR3(0.0f, 0.5f, 220.0f), 700.0f, 700.0f, 10.0f, 10.0f);
	CFeild::Create(D3DXVECTOR3(30.0f, 0.5f, 1430.0f), 300.0f, 300.0f, 5.0f, 5.0f);
	CFeild::Create(D3DXVECTOR3(1050.0f, 0.4f, 1200.0f), 500.0f, 500.0f, 8.0f, 8.0f);
	CFeild::Create(D3DXVECTOR3(450.0f, 0.5f, 1000.0f), 90.0f, 270.0f, 5.0f, 5.0f);
	CFeild::Create(D3DXVECTOR3(1000.0f, 0.5f, 200.0f), 300.0f, 300.0f, 5.0f, 5.0f);
	CFeild::Create(D3DXVECTOR3(1200.0f, 0.5f, 600.0f), 200.0f, 200.0f, 5.0f, 5.0f);

	// ��
	CScene3D::Create(D3DXVECTOR3(550.0f, 0.0f, 700.0f), 700.0f, 700.0f, 1.0f, 1.0f);

	// �R�C������
	CCoin::Create(D3DXVECTOR3(0.0f, 68500.0f, 250.0f));
	CCoin::Create(D3DXVECTOR3(0.0f, 68000.0f, 250.0f));
	CCoin::Create(D3DXVECTOR3(0.0f, 67500.0f, 250.0f));

	CCoin::Create(D3DXVECTOR3(-200.0f, 65000.0f, 250.0f));
	CCoin::Create(D3DXVECTOR3(-200.0f, 64500.0f, 250.0f));
	CCoin::Create(D3DXVECTOR3(-200.0f, 64000.0f, 250.0f));
}
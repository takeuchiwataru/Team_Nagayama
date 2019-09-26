//=============================================================================
//
// ���Ȃ�c�@���� [onararemain.cpp]
// Author : ���R���
//
//=============================================================================
#include "onararemain.h"
#include "manager.h"
#include "number.h"
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_ONARAREMAIN	(3)	//���C�t�̏����l

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
//int CLife::m_nScore = 0;
//CNumber *CLife::m_apLife[MAX_NUMLIFE] = {};

//=============================================================================
// �X�R�A�̐�������
//=============================================================================
COnaraRemain *COnaraRemain::Create(D3DXVECTOR3 pos, float fSize)
{
	COnaraRemain *pLife = NULL;

	if (pLife == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pLife = new COnaraRemain;

		if (pLife != NULL)
		{
			pLife->m_pos = pos;
			pLife->m_fSize = fSize;
			pLife->Init();
		}
	}

	return pLife;
}

//=============================================================================
// �X�R�A�N���X�̃R���X�g���N�^
//=============================================================================
COnaraRemain::COnaraRemain(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	for (int nCntScore = 0; nCntScore < MAX_NUMLIFE; nCntScore++)
	{
		m_apLife[nCntScore] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumLife = 0;
}

//=============================================================================
// �X�R�A�N���X�̃f�X�g���N�^
//=============================================================================
COnaraRemain::~COnaraRemain()
{
}

//=============================================================================
// �X�R�A�̏���������
//=============================================================================
HRESULT COnaraRemain::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_SCORE);

	for (int nCntScore = 0; nCntScore < MAX_NUMLIFE; nCntScore++)
	{
		m_apLife[nCntScore] = CNumber::Create(D3DXVECTOR3(m_pos.x - nCntScore * 60, m_pos.y, 0.0f), m_fSize);
	}

	m_nNumLife = 0;

	AddOnaraRemain(MAX_ONARAREMAIN);

	return S_OK;
}

//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void COnaraRemain::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < MAX_NUMLIFE; nCntBg++)
	{
		if (m_apLife[nCntBg] != NULL)
		{
			m_apLife[nCntBg]->Uninit();

			// ���������J��
			delete m_apLife[nCntBg];
			m_apLife[nCntBg] = NULL;
		}
	}

	// �X�R�A���̂̉��
	Release();
}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void COnaraRemain::Update(void)
{

}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void COnaraRemain::Draw(void)
{
	for (int nCntBg = 0; nCntBg < MAX_NUMLIFE; nCntBg++)
	{
		if (m_apLife[nCntBg] != NULL)
		{
			m_apLife[nCntBg]->Draw();
		}
	}
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void COnaraRemain::AddOnaraRemain(int nValue)
{
	int nAnswer = 1;
	int nCntScore;
	int nScore;

	m_nNumLife += nValue;


	for (nCntScore = 0; nCntScore < MAX_NUMLIFE; nCntScore++)
	{
		// �X�R�A��\�����邽�߂̌v�Z
		nScore = m_nNumLife % (nAnswer * 10) / nAnswer;

		m_apLife[nCntScore]->SetNumber(nScore);

		nAnswer *= 10;
	}

}

//=============================================================================
// �X�R�A�̐ݒ菈��
//=============================================================================
void COnaraRemain::SetLife(int nScore)
{
	m_nNumLife = nScore;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int COnaraRemain::GetLife(void)
{
	return m_nNumLife;
}

//=============================================================================
// �X�R�A�̐F�̐ݒ菈��
//=============================================================================
void COnaraRemain::SetColor(D3DXCOLOR color)
{
	for (int nCntScore = 0; nCntScore < MAX_NUMLIFE; nCntScore++)
	{
		m_apLife[nCntScore]->SetColor(color);
	}
}
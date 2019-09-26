//=============================================================================
//
// �X�R�A���� [score.cpp]
// Author : ���R���
//
//=============================================================================
#include "score.h"
#include "manager.h"
#include "number.h"
#include "scene2D.h"

//=============================================================================
// �X�R�A�̐�������
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, float fSize, float fWidth)
{
	CScore *pNumber = NULL;

	if (pNumber == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pNumber = new CScore;

		if (pNumber != NULL)
		{
			pNumber->m_pos = pos;
			pNumber->m_fSize = fSize;
			pNumber->m_fWidth = fWidth;
			pNumber->Init();
		}
	}

	return pNumber;
}

//=============================================================================
// �X�R�A�N���X�̃R���X�g���N�^
//=============================================================================
CScore::CScore(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore] = NULL;
	}
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nScore = 0;
	m_fWidth = 0.0f;
	m_fSize = 0.0f;
}

//=============================================================================
// �X�R�A�N���X�̃f�X�g���N�^
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// �X�R�A�̏���������
//=============================================================================
HRESULT CScore::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_SCORE);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore] = CNumber::Create(D3DXVECTOR3(m_pos.x - nCntScore * m_fWidth, m_pos.y, 0.0f), m_fSize);
	}

	m_nScore = 0;

	return S_OK;
}

//=============================================================================
// �X�R�A�̏I������
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < MAX_SCORE; nCntBg++)
	{
		if (m_apNumber[nCntBg] != NULL)
		{
			m_apNumber[nCntBg]->Uninit();

			// ���������J��
			delete m_apNumber[nCntBg];
			m_apNumber[nCntBg] = NULL;
		}
	}

	// �X�R�A���̂̉��
	Release();
}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CScore::Update(void)
{
	
}

//=============================================================================
// �X�R�A�̍X�V����
//=============================================================================
void CScore::Draw(void)
{
	for (int nCntBg = 0; nCntBg < MAX_SCORE; nCntBg++)
	{
		if (m_apNumber[nCntBg] != NULL)
		{
			m_apNumber[nCntBg]->Draw();
		}
	}
}

//=============================================================================
// �X�R�A�̉��Z
//=============================================================================
void CScore::AddScore(int nValue)
{
	int nAnswer = 1;
	int nCntScore;
	int nScore;

	m_nScore += nValue;

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		// �X�R�A��\�����邽�߂̌v�Z
		nScore = m_nScore % (nAnswer * 10) / nAnswer;

		m_apNumber[nCntScore]->SetNumber(nScore);

		nAnswer *= 10;
	}

}

//=============================================================================
// �X�R�A�̐ݒ菈��
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//=============================================================================
// �X�R�A�̎擾
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//=============================================================================
// �X�R�A�̐F�̐ݒ菈��
//=============================================================================
void CScore::SetColor(D3DXCOLOR color)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore]->SetColor(color);
	}
}
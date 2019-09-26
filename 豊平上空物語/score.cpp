//=============================================================================
//
// スコア処理 [score.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "score.h"
#include "manager.h"
#include "number.h"
#include "scene2D.h"

//=============================================================================
// スコアの生成処理
//=============================================================================
CScore *CScore::Create(D3DXVECTOR3 pos, float fSize, float fWidth)
{
	CScore *pNumber = NULL;

	if (pNumber == NULL)
	{
		// オブジェクトクラスの生成
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
// スコアクラスのコンストラクタ
//=============================================================================
CScore::CScore(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
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
// スコアクラスのデストラクタ
//=============================================================================
CScore::~CScore()
{
}

//=============================================================================
// スコアの初期化処理
//=============================================================================
HRESULT CScore::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_SCORE);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore] = CNumber::Create(D3DXVECTOR3(m_pos.x - nCntScore * m_fWidth, m_pos.y, 0.0f), m_fSize);
	}

	m_nScore = 0;

	return S_OK;
}

//=============================================================================
// スコアの終了処理
//=============================================================================
void CScore::Uninit(void)
{
	for (int nCntBg = 0; nCntBg < MAX_SCORE; nCntBg++)
	{
		if (m_apNumber[nCntBg] != NULL)
		{
			m_apNumber[nCntBg]->Uninit();

			// メモリを開放
			delete m_apNumber[nCntBg];
			m_apNumber[nCntBg] = NULL;
		}
	}

	// スコア自体の解放
	Release();
}

//=============================================================================
// スコアの更新処理
//=============================================================================
void CScore::Update(void)
{
	
}

//=============================================================================
// スコアの更新処理
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
// スコアの加算
//=============================================================================
void CScore::AddScore(int nValue)
{
	int nAnswer = 1;
	int nCntScore;
	int nScore;

	m_nScore += nValue;

	for (nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		// スコアを表示するための計算
		nScore = m_nScore % (nAnswer * 10) / nAnswer;

		m_apNumber[nCntScore]->SetNumber(nScore);

		nAnswer *= 10;
	}

}

//=============================================================================
// スコアの設定処理
//=============================================================================
void CScore::SetScore(int nScore)
{
	m_nScore = nScore;
}

//=============================================================================
// スコアの取得
//=============================================================================
int CScore::GetScore(void)
{
	return m_nScore;
}

//=============================================================================
// スコアの色の設定処理
//=============================================================================
void CScore::SetColor(D3DXCOLOR color)
{
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		m_apNumber[nCntScore]->SetColor(color);
	}
}
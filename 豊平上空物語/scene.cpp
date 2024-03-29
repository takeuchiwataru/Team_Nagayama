//=============================================================================
//
// シーン処理 [scene.h]
// Author : 長山拓実
//
//=============================================================================
#include "scene.h"
#include "scene2D.h"
#include "debugProc.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
int CScene::m_nNumAll = 0;
int CScene::m_nNumPriority[NUM_PRIORITY] = {};
CScene *CScene::m_apTop[NUM_PRIORITY] = {};
CScene *CScene::m_apCur[NUM_PRIORITY] = {};

//=============================================================================
// シーンクラスのコンストラクタ
//=============================================================================
CScene::CScene(int nPriority, OBJTYPE objType)
{
	// 値のクリア
	m_nID = 0;
	m_pPrev = NULL;
	m_pNext = NULL;
	m_bDeath = false;
	
	if (m_apCur[nPriority] == NULL)
	{// カレントがNULLなら現在の位置が先頭
		m_apTop[nPriority] = this;
	}
	else
	{// カレントがNULLじゃなかったら
	 // 前回のSceneのm_pNextに今作ったSceneを入れる
		m_apCur[nPriority]->m_pNext = this;
	}

	m_pPrev = m_apCur[nPriority];	// 今作ったSceneのm_pPrevに前回のSceneを入れる
	m_pNext = NULL;					// 次のシーンはまだ作られていないからNULL
	m_apCur[nPriority] = this;		// カレントの位置を今作ったSceneに移動する
	m_nPriority = nPriority;		// プライオリティを保存
	m_objType = objType;			// オブジェクトの種類を保存
	m_nNumPriority[nPriority]++;

}

//=============================================================================
// デストラクタ
//=============================================================================
CScene::~CScene()
{
}

//=============================================================================
// 全てのオブジェクトの解放処理
//=============================================================================
void CScene::ReleseAll(void)
 {
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// 優先順位の数分繰り返す
		// 先頭を取得する
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{// 空になるまでアップデートする
		 // Updateの最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->m_pNext;

			// 更新
			pScene->Uninit();

			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// 優先順位の数分繰り返す
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{
			// Updateの最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				// フラグが立っているオブジェクトを消していく
				pScene->DeleteAll();
			}

			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// 全てのオブジェクトの更新処理
//=============================================================================
void CScene::UpdeteAll(void)
{
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// 優先順位の数分繰り返す
		// 先頭を取得する
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{// 空になるまでアップデートする

			// Updateの最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->m_pNext;

			// 更新
			pScene->Update();

			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// 優先順位の数分繰り返す
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{
			// Updateの最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				// フラグが立っているオブジェクトを消していく
				pScene->DeleteAll();
			}

			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}

#ifdef _DEBUG
	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// 優先順位の数分繰り返す
		// デバック表示の更新
		CDebugProc::Print("ncn", nCntPriority, " : ", m_nNumPriority[nCntPriority]);
	}
#endif
}

//=============================================================================
// 全てのオブジェクトの描画処理
//=============================================================================
void CScene::DrawAll(void)
{
	CScene *pScene = NULL;

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// 優先順位の数分繰り返す
		// 先頭の場所を取得
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{// 空になるまで描画する
			// Drawの最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->m_pNext;

			// 描画
			pScene->Draw();

			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}

	for (int nCntPriority = 0; nCntPriority < NUM_PRIORITY; nCntPriority++)
	{// 優先順位の数分繰り返す
		pScene = m_apTop[nCntPriority];

		while (pScene != NULL)
		{
			// Updateの最中に消える可能性があるから先に記録しておく
			CScene *pSceneNext = pScene->m_pNext;

			if (pScene->m_bDeath == true)
			{
				// フラグが立っているオブジェクトを消していく
				pScene->DeleteAll();
			}

			// 次のシーンに進める
			pScene = pSceneNext;
		}
	}
}

//=============================================================================
// オブジェクトの解放処理
//=============================================================================
void CScene::Release(void)
{
	// 死亡フラグを立てる
	m_bDeath = true;
}

//=============================================================================
// フラグが立ったオブジェクトの解放処理
//=============================================================================
void CScene::DeleteAll(void)
{
	int nPriority;
	nPriority = m_nPriority;

	// 消えるオブジェクトの前がいるかどうか
	if (m_pPrev == NULL)
	{// 前がいない時
	 // 先頭を次にずらす
		m_apTop[nPriority] = m_pNext;
	}
	else
	{// 前がいる時
	 // 前のオブジェクトにある自分の情報を次のオブジェクトに渡す
		m_pPrev->m_pNext = m_pNext;
	}

	// 消えるオブジェクトの次がいるかどうか
	if (m_pNext == NULL)
	{// 次がいない時
	 // 現在（最後尾）のオブジェクトを前のオブジェクトに渡す
		m_apCur[nPriority] = m_pPrev;
	}
	else
	{// 次がいる時
	 // 次にいるオブジェクトにある自分の情報を前のオブジェクトに渡す
		m_pNext->m_pPrev = m_pPrev;
	}

	// 自分を消す
	delete this;

	m_nNumPriority[nPriority]--;
}

//=============================================================================
// オブジェクトの種類の設定
//=============================================================================
void CScene::SetObjType(OBJTYPE objType)
{
	m_objType = objType;
}

//=============================================================================
// オブジェクトの種類の取得
//=============================================================================
CScene::OBJTYPE CScene::GetObjType(void)
{
	return m_objType;
}

//=============================================================================
// 優先順位の取得
//=============================================================================
int CScene::GetPriority(void)
{
	return m_nPriority;
}

//=============================================================================
// 優先順位の設定
//=============================================================================
void CScene::SetPriority(int nPriority)
{
	m_nPriority = nPriority;
}

//=============================================================================
// 先頭のオブジェクトを取得
//=============================================================================
CScene *CScene::GetTop(int nPriority)
{
	return m_apTop[nPriority];
}

//=============================================================================
// 次のオブジェクトのポインタを取得
//=============================================================================
CScene *CScene::GetNext(void)
{
	return m_pNext;
}

//=============================================================================
// 死亡フラグを取得
//=============================================================================
bool CScene::GetDeath(void)
{
	return m_bDeath;
}
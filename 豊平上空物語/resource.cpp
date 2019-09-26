//=============================================================================
//
// 素材管理処理 [resource.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "resource.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "debugProc.h"
#include "manager.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 *CResource::m_pTexture = NULL;
LPD3DXMESH *CResource::m_pMesh = NULL;			// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER *CResource::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD *CResource::m_nNumMat = 0;				// マテリアル情報の数

// ヘッダの順番と同じにする
const char *CResource::m_apModelFilename[] =
{// モデル
	"data\\MODEL\\woodBox.x",			// プレイヤーが出すブロック
	"data\\MODEL\\woodBox001.x",		// 木ブロックのモデル名
	"data\\MODEL\\ironBox.x",			// 鉄ブロックのモデル名
	"data\\MODEL\\woodDebris.x",		// ブロックの破片のモデル名
	"data\\MODEL\\coin.x",				// コインのモデル名
	"data\\MODEL\\gem.x",				// 宝石のモデル名
	"data\\MODEL\\OBJECT\\pebble.x",	// 小石のモデル名
	"data\\MODEL\\goal.x",				// ゴールのモデル名
	"data\\MODEL\\OBJECT\\obstacle.x",	// 障害物のモデル名
	"data\\MODEL\\OBJECT\\bullet.x",	// 弾のモデル名
	"data\\MODEL\\fullMegro.x",			// 全裸目黒のモデル名
};

// ヘッダの順番と同じにする
const char *CResource::m_apTexFilename[] =
{// テクスチャ
	"data/TEXTURE/UI/PressAnyButton.png",	// プレスエニーボタンロゴのテクスチャ名
	"data/TEXTURE/UI/enter.png"	,			// エンターボタンロゴのテクスチャ名
	"data\\TEXTURE\\soil001.jpg",			// 地面のテクスチャ名
	"data/TEXTURE/effect000.jpg",			// エフェクトのテクスチャ名
	"data/TEXTURE/cloud.png",				// 煙エフェクトのテクスチャ名
	"data/TEXTURE/logoBack001.png",			// 背景ロゴのテクスチャ名
	"data/TEXTURE/UI/SCORE.png",			// スコアロゴのテクスチャ名
	"data/TEXTURE/UI/BLOCK.png",			// ブロックロゴのテクスチャ名
	"data/TEXTURE/UI/LIFE.png",				// 残機ロゴのテクスチャ名
	"data/TEXTURE/UI/blockCross.png",		// ブロックの個数ロゴのテクスチャ名
	"data/TEXTURE/UI/playerCross.png",		// プレイヤーの残機ロゴのテクスチャ名
	"data\\TEXTURE\\TUTORIAL\\move.png",	// 移動方法のテクスチャ名
	"data\\TEXTURE\\TUTORIAL\\jump.png",	// ジャンプ方法のテクスチャ名
	"data\\TEXTURE\\TUTORIAL\\set.png",		// 設置方法のテクスチャ名
	"data\\TEXTURE\\TUTORIAL\\destroy.png",	// 破壊方法のテクスチャ名
	"data\\TEXTURE\\TUTORIAL\\end.png",		// 終了のテクスチャ名
	"data/TEXTURE/number_02.png",			// スコアのテクスチャ名
	"data/TEXTURE/bullet000.png",				// 弾のテクスチャ名
	"data\\TEXTURE\\life000.png",			// 体力のモデル名
	"data\\TEXTURE\\TITLE\\title001.png",	// タイトルロゴ名
	"data\\TEXTURE\\tutorial.png",		// チュートリアルロゴ名
	"data\\TEXTURE\\bullet000.png",	// おなら残機名
	"data\\TEXTURE\\Animation_おなら.png",		// 屁のアニメーション
	"data\\TEXTURE\\RESULT\\gameclear.png",		// 屁のアニメーション
	"data\\TEXTURE\\RESULT\\gameover.png",		// 屁のアニメーション
	"data\\TEXTURE\\rankinglogo.png",			// ランキングロゴ
	"data\\TEXTURE\\rankingrank.png",	// ランキングランク
	"data\\TEXTURE\\onara_counter.png",
};

//=============================================================================
// コンストラクタ
//=============================================================================
CResource::CResource()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CResource::~CResource()
{
}

//=============================================================================
// テクスチャ読み込み処理
//=============================================================================
HRESULT CResource::LoadModel(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	if (m_pMesh != NULL)
	{
		// メモリを解放する
		delete[] m_pMesh;
		m_pMesh = NULL;
	}

	if (m_pBuffMat != NULL)
	{
		// メモリを解放する
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		// メモリを解放する
		delete[] m_nNumMat;
		m_nNumMat = NULL;
	}

	int nModelData = (sizeof m_apModelFilename);
	int nModelSize = (sizeof m_apModelFilename[0]);
	int nNumModel = nModelData / nModelSize;

	// 動的に確保
	m_pMesh = new LPD3DXMESH[nNumModel];
	m_pBuffMat = new LPD3DXBUFFER[nNumModel];
	m_nNumMat = new DWORD[nNumModel];

	for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
	{
		D3DXLoadMeshFromX(m_apModelFilename[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCntModel],
			NULL,
			&m_nNumMat[nCntModel],
			&m_pMesh[nCntModel]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ解放処理
//=============================================================================
void CResource::UnloadModel(void)
{
	if (m_pBuffMat != NULL)
	{
		// メモリを解放する
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		// メモリを解放する
		delete[] m_nNumMat;
		m_nNumMat = NULL;
	}

	if (m_pMesh != NULL)
	{
		// メモリを解放する
		delete[] m_pMesh;
		m_pMesh = NULL;
	}
}

//=============================================================================
// テクスチャ読み込み処理
//=============================================================================
HRESULT CResource::LoadTex(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	if (m_pTexture != NULL)
	{
		// メモリを解放する
		delete[] m_pTexture;
		m_pTexture = NULL;
	}

	int nTexData = (sizeof m_apTexFilename);
	int nTexSize = (sizeof m_apTexFilename[0]);
	int nNumTex = nTexData / nTexSize;

	// テクスチャの数を動的に確保
	m_pTexture = new LPDIRECT3DTEXTURE9[nNumTex];

	for (int nCntTex = 0; nCntTex < nNumTex; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice, m_apTexFilename[nCntTex], &m_pTexture[nCntTex]);
	}

	return S_OK;
}

//=============================================================================
// テクスチャ解放処理
//=============================================================================
void CResource::UnloadTex(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		// メモリを解放する
		delete[] m_pTexture;
		m_pTexture = NULL;
	}
}

//=============================================================================
// テクスチャ取得
//=============================================================================
LPDIRECT3DTEXTURE9 CResource::GetTexture(int nIdx)
{
	return m_pTexture[nIdx];
}

//=============================================================================
// メッシュ取得
//=============================================================================
LPD3DXMESH CResource::GetMesh(int nIdx)
{
	return m_pMesh[nIdx];
}

//=============================================================================
// マテリアル情報取得
//=============================================================================
LPD3DXBUFFER CResource::GetBuffMat(int nIdx)
{
	return m_pBuffMat[nIdx];
}

//=============================================================================
// マテリアル情報の数取得
//=============================================================================
DWORD CResource::GetNumMat(int nIdx)
{
	return m_nNumMat[nIdx];
}
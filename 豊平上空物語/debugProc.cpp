//=============================================================================
//
// デバック表示処理 [debugProc.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "debugProc.h"
#include "manager.h"
#include "renderer.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[1024] = {};

//=============================================================================
// デバック表示クラスのコンストラクタ
//=============================================================================
CDebugProc::CDebugProc()
{
}

//=============================================================================
// デストラクタ
//=============================================================================
CDebugProc::~CDebugProc()
{
}

//=============================================================================
// デバック表示の初期化処理
//=============================================================================
void CDebugProc::Init(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// デバッグ情報表示用フォントの生成
	D3DXCreateFont(pDevice, 18, 0, 0, 0, FALSE, SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "Terminal", &m_pFont);

}

//=============================================================================
// デバック表示の終了処理
//=============================================================================
void CDebugProc::Uninit(void)
{
	// デバッグ情報表示用フォントの破棄
	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}
}

//=============================================================================
// デバック表示の表示処理
//=============================================================================
void CDebugProc::Print(char *fmt, ...)
{
	int nNum = 0;
	double fNum = 0.0f;
	char cNum[1024];

	// 任意個の引数を１個の変数に変換
	va_list ap;

	// 可変長引数を１個の変数にまとめる
	va_start(ap, fmt);

	while (*fmt)
	{
		switch (*fmt)
		{
		case 'c':	// char型
			strcat(m_aStr, va_arg(ap, char*));	// リストの中のキャラ型を取り出して、m_aStrに入れる
			break;

		case 'n':	// int型
			nNum = va_arg(ap, int);		// リストの中のint型数字を引き出す

			sprintf(cNum, "%d", nNum);	// %dに入るint型をcNumのキャラ型に入れる

			strcat(m_aStr, cNum);		// 文字のデータにint型の数字を入れる

			break;

		case 'f':	// float型
			fNum = va_arg(ap, double);		// リストの中のfloat型数字を引き出す

			sprintf(cNum, "%.1f", fNum);	// %.1fに入るfloat型をcNumのキャラ型に入れる

			strcat(m_aStr, cNum);			// 文字のデータにfloat型の数字を入れる

			break;
		}

		fmt++;	// フォーマットの文字を１文字進める
	}


	strcat(m_aStr, "\n");

	va_end(ap);
}

//=============================================================================
// デバック表示の削除処理
//=============================================================================
void CDebugProc::ReleseStr(void)
{
	for (int nCntStr = 0; nCntStr < 1024; nCntStr++)
	{
		if (m_aStr[nCntStr] != NULL)
		{
			m_aStr[nCntStr] = NULL;
		}
	}
}

//=============================================================================
// デバック表示の表示処理
//=============================================================================
void CDebugProc::Draw(void)
{
	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	// テキスト描画
	m_pFont->DrawText(NULL, m_aStr, -1, &rect, DT_LEFT, D3DCOLOR_ARGB(0xff, 0xff, 0xff, 0xff));
}
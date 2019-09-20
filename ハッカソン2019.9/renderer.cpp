//=============================================================================
//
// レンダリング処理 [renderer.h]
// Author : 長山拓実
//
//=============================================================================
#include "renderer.h"
#include "main.h"
#include "scene.h"
#include "debugProc.h"
#include "manager.h"
#include "fade.h"
#include "input.h"
#include "pause.h"
#include "sound.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
CPause *CRenderer::m_pPause = NULL;

//=============================================================================
// レンダリングクラスのコンストラクタ
//=============================================================================
CRenderer::CRenderer()
{
	// 値をクリア
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
//#ifdef _DEBUG
//	m_pFont = NULL;
//#endif
}

//=============================================================================
// デストラクタ
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3Dオブジェクトの作成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ワークをゼロクリア
	d3dpp.BackBufferCount			 = 1;							// バックバッファの数
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;				// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;				// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// カラーモードの指定
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D24S8;				// // depthを24bitステンシルを8bit
	d3dpp.Windowed					 = bWindow;						// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// リフレッシュレート
	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル

	// デバイスの生成
	// ディスプレイアダプタを表すためのデバイスを作成
	// 描画と頂点処理をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// 上記の設定が失敗したら
		// 描画をハードウェアで行い、頂点処理はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// 描画と頂点処理をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// 生成失敗
				return E_FAIL;
			}
		}
	}

	// レンダーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(U値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// テクスチャアドレッシング方法(V値)を設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// テクスチャ縮小フィルタモードを設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// テクスチャ拡大フィルタモードを設定

	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	m_bPause = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
	// デバイスの破棄
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3Dオブジェクトの破棄
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void CRenderer::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// 入力情報を取得
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// ポーズのモードを取得
	CPause::MODE mode;
	mode = CPause::GetMode();

	// プレイ中のモードを取得
	CManager::MODE modeManager;
	modeManager = CManager::GetMode();

	// 音楽情報を取得
	CSound *pSound;
	pSound = CManager::GetSound();

	// フェード取得
	CFade *pFade = CManager::GetFade();

	if (modeManager == CManager::MODE_GAME)
	{
		if (pFade->GetFade() == CFade::FADE_NONE)
		{// フェードしていなかったらポーズを押せる
			if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
			{// ポーズON/OFF
				pSound->PlaySound(CSound::SOUND_LABEL_SE_PAUSE);
				m_bPause = m_bPause ? false : true;

				if (m_bPause == true)
				{
					if (m_pPause == NULL)
					{
						m_pPause = CPause::Create();
					}
				}
				else
				{
					if (m_pPause != NULL)
					{// ポーズクラスの破棄
					 // 終了処理
						m_pPause->Uninit();

						// メモリを開放
						m_pPause = NULL;
					}
				}

			}
		}
		if (m_bPause == false)
		{
			CScene::UpdeteAll();
		}
		else
		{
			if (m_pPause != NULL)
			{// ポーズクラスの更新
				m_pPause->Update();
			}

			// 決定
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
			{
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECTENTER);
				int nSelect;
				nSelect = m_pPause->GetSelect();

				if (nSelect == 0)
				{// コンティニュー
					mode = CPause::MODE_CONTINUE;
				}
				else if (nSelect == 1)
				{// リトライ
					mode = CPause::MODE_RETRY;
				}
				else if (nSelect == 2)
				{//	クイット
					mode = CPause::MODE_QUIT;
				}

				switch (mode)
				{
				case CPause::MODE_CONTINUE:
					break;
				case CPause::MODE_RETRY:
					// リトライ
					pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
					break;
				case CPause::MODE_QUIT:
					// クイット
					pFade->SetFade(CManager::MODE_TITLE, CFade::FADE_OUT);
					break;

				}
				m_bPause = m_bPause ? false : true;
				if (m_pPause != NULL)
				{
					m_pPause->Uninit();
					m_pPause = NULL;
				}
			}
		}
	}
	else
	{
		CScene::UpdeteAll();
	}

#ifdef _DEBUG
	// デバック表示の更新
	CDebugProc::Print("cn", "FPS:", GetFPS());

	if (pInputKeyboard->GetTrigger(DIK_F1) == true)
	{
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, 2);
	}
	if (pInputKeyboard->GetTrigger(DIK_F2) == true)
	{
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, 0);
	}
#endif
}

//=============================================================================
// 描画処理
//=============================================================================
void CRenderer::Draw(void)
{
	// バックバッファ＆Ｚバッファのクリア
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	// Direct3Dによる描画の開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene::DrawAll();
#ifdef _DEBUG
		// FPS表示
		CDebugProc::Draw();
#endif

		CFade *pFade = CManager::GetFade();

		if (pFade != NULL)
		{
			pFade->Draw();
		}

		// Direct3Dによる描画の終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
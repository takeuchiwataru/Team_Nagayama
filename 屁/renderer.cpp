//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : ���R���
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
// �ÓI�����o�ϐ��錾
//=============================================================================
CPause *CRenderer::m_pPause = NULL;

//=============================================================================
// �����_�����O�N���X�̃R���X�g���N�^
//=============================================================================
CRenderer::CRenderer()
{
	// �l���N���A
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
//#ifdef _DEBUG
//	m_pFont = NULL;
//#endif
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CRenderer::~CRenderer()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CRenderer::Init(HWND hWnd, bool bWindow)
{
	D3DPRESENT_PARAMETERS d3dpp;
	D3DDISPLAYMODE d3ddm;

	// Direct3D�I�u�W�F�N�g�̍쐬
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferCount			 = 1;							// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth			 = SCREEN_WIDTH;				// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight			 = SCREEN_HEIGHT;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat			 = d3ddm.Format;				// �J���[���[�h�̎w��
	d3dpp.SwapEffect				 = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.EnableAutoDepthStencil	 = TRUE;						// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat	 = D3DFMT_D24S8;				// // depth��24bit�X�e���V����8bit
	d3dpp.Windowed					 = bWindow;						// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g
	d3dpp.PresentationInterval		 = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// �f�o�C�X�̐���
	// �f�B�X�v���C�A�_�v�^��\�����߂̃f�o�C�X���쐬
	// �`��ƒ��_�������n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice)))
	{
		// ��L�̐ݒ肪���s������
		// �`����n�[�h�E�F�A�ōs���A���_������CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// �`��ƒ��_������CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF, hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp, &m_pD3DDevice)))
			{
				// �������s
				return E_FAIL;
			}
		}
	}

	// �����_�[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(U�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);	// �e�N�X�`���A�h���b�V���O���@(V�l)��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);	// �e�N�X�`���g��t�B���^���[�h��ݒ�

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	m_bPause = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CRenderer::Uninit(void)
{
	// �f�o�C�X�̔j��
	if (m_pD3DDevice != NULL)
	{
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CRenderer::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ���͏����擾
	CInputJoypad *pInputJoypad;
	pInputJoypad = CManager::GetInputJoypad();

	// �|�[�Y�̃��[�h���擾
	CPause::MODE mode;
	mode = CPause::GetMode();

	// �v���C���̃��[�h���擾
	CManager::MODE modeManager;
	modeManager = CManager::GetMode();

	// ���y�����擾
	CSound *pSound;
	pSound = CManager::GetSound();

	// �t�F�[�h�擾
	CFade *pFade = CManager::GetFade();

	if (modeManager == CManager::MODE_GAME)
	{
		if (pFade->GetFade() == CFade::FADE_NONE)
		{// �t�F�[�h���Ă��Ȃ�������|�[�Y��������
			if (pInputKeyboard->GetTrigger(DIK_P) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
			{// �|�[�YON/OFF
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
					{// �|�[�Y�N���X�̔j��
					 // �I������
						m_pPause->Uninit();

						// ���������J��
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
			{// �|�[�Y�N���X�̍X�V
				m_pPause->Update();
			}

			// ����
			if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_B) == true)
			{
				pSound->PlaySound(CSound::SOUND_LABEL_SE_SELECTENTER);
				int nSelect;
				nSelect = m_pPause->GetSelect();

				if (nSelect == 0)
				{// �R���e�B�j���[
					mode = CPause::MODE_CONTINUE;
				}
				else if (nSelect == 1)
				{// ���g���C
					mode = CPause::MODE_RETRY;
				}
				else if (nSelect == 2)
				{//	�N�C�b�g
					mode = CPause::MODE_QUIT;
				}

				switch (mode)
				{
				case CPause::MODE_CONTINUE:
					break;
				case CPause::MODE_RETRY:
					// ���g���C
					pFade->SetFade(CManager::MODE_GAME, CFade::FADE_OUT);
					break;
				case CPause::MODE_QUIT:
					// �N�C�b�g
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
	// �f�o�b�N�\���̍X�V
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
// �`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@���y�o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0,
		NULL,
		(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL),
		D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	// Direct3D�ɂ��`��̊J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		CScene::DrawAll();
#ifdef _DEBUG
		// FPS�\��
		CDebugProc::Draw();
#endif

		CFade *pFade = CManager::GetFade();

		if (pFade != NULL)
		{
			pFade->Draw();
		}

		// Direct3D�ɂ��`��̏I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

//=============================================================================
// �f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
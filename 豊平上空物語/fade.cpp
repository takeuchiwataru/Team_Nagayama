//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
// Author : ���R���
//
//=============================================================================
#include "fade.h"
#include "scene2D.h"
#include "scene.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_POS_X			(0)				// �t�F�[�h�̍���X���W
#define FADE_POS_Y			(0)				// �t�F�[�h�̍���Y���W
#define FADE_WIDTH			(SCREEN_WIDTH)	// �t�F�[�h�̕�
#define FADE_HEIGHT			(SCREEN_HEIGHT)	// �t�F�[�h�̍���
#define FADE_SPEED			(0.02f)			// �t�F�[�h�̑���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
CFade::FADE CFade::m_fade = CFade::FADE_NONE;
CManager::MODE CFade::m_modeNext = CManager::MODE_NONE;
D3DXCOLOR CFade::m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// ������ʁi�����j�ɂ��Ă���

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFade::CFade()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFade::~CFade()
{
}

//=============================================================================
// �t�F�[�h�̐�������
//=============================================================================
CFade *CFade::Create(void)
{
	CFade *pFade = NULL;

	if (pFade == NULL)
	{
		// �t�F�[�h�N���X�̐���
		pFade = new CFade;

		if (pFade != NULL)
		{
			pFade->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
		}

	}
	return pFade;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CFade::Init(D3DXVECTOR3 pos)
{
	// �l�̏�����
	m_fade = FADE_NONE;	// �t�F�[�h�A�E�g��Ԃ�
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// ������ʁi�s�����j�ɂ��Ă���

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			// ���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(pos.x - SCREEN_WIDTH, pos.y - SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + SCREEN_WIDTH, pos.y - SCREEN_HEIGHT, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - SCREEN_WIDTH, pos.y + SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + SCREEN_WIDTH, pos.y + SCREEN_HEIGHT, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CFade::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CFade::Update(void)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)	// �t�F�[�h�C�����
		{
			m_colorFade.a -= FADE_SPEED;	// ��ʂ𓧖��ɂ��Ă���
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fade = FADE_NONE;	// �������Ă��Ȃ���Ԃ�
			}
		}
		else if (m_fade == FADE_OUT)	// �t�F�[�h�A�E�g���
		{
			m_colorFade.a += FADE_SPEED;	// ��ʂ�s�����ɂ��Ă���
			if (m_colorFade.a >= 1.0f)
			{
				m_colorFade.a = 1.0f;
				m_fade = FADE_IN;	// �t�F�[�h�C����Ԃ�	

				// ���[�h�̐ݒ�
				CManager::SetMode(m_modeNext);
			}
		}
	}
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void CFade::Draw(void)
{
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �t�F�[�h�̏�Ԃ̎擾
//=============================================================================
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}

//=============================================================================
// �t�F�[�h�̏�Ԃ̐ݒ�
//=============================================================================
void CFade::SetFade(CManager::MODE modeNext, FADE fade)
{
	if (m_fade == FADE_NONE)
	{
		m_fade = FADE_OUT;
		m_modeNext = modeNext;

		m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);

		if (fade == FADE_IN)
		{
			m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.8f);
		}
	}
	
}
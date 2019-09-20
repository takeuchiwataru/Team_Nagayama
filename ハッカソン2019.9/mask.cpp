//=============================================================================
//
// �}�X�N���� [mask.cpp]
// Author : ���R���
//
//=============================================================================
#include "mask.h"
#include "scene2D.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define FADE_POS_X			(0)								// �t�F�[�h�̍���X���W
#define FADE_POS_Y			(0)								// �t�F�[�h�̍���Y���W
#define FADE_WIDTH			(SCREEN_WIDTH)					// �t�F�[�h�̕�
#define FADE_HEIGHT			(SCREEN_HEIGHT)					// �t�F�[�h�̍���

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CMask::CMask()
{
	// �l���N���A
	//m_pTexture = NULL;
	//m_modeNext = CManager::MODE_NONE;
	//m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);	// ������ʁi�����j�ɂ��Ă���
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMask::~CMask()
{
}

//=============================================================================
// �t�F�[�h�̐�������
//=============================================================================
CMask *CMask::Create(void)
{
	CMask *pFade = NULL;

	if (pFade == NULL)
	{
		// �t�F�[�h�N���X�̐���
		pFade = new CMask;

		if (pFade != NULL)
		{
			pFade->Init(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f));
			//pFade->m_fade = FADE_OUT;	// �t�F�[�h�A�E�g��Ԃ�
			//pFade->m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// ������ʁi�����j�ɂ��Ă���
		}

	}
	return pFade;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMask::Init(D3DXVECTOR3 pos)
{
	// �l�̏�����

														// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	//D3DXCreateTextureFromFile(pDevice, PLAYER_NAME, &m_pTexture);

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
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.3f);

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
void CMask::Uninit(void)
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
void CMask::Update(void)
{

}

//=============================================================================
// �^�C�g�����
//=============================================================================
void CMask::Draw(void)
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
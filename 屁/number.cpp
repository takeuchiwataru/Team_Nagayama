//=============================================================================
//
// �i���o�[���� [number.cpp]
// Author : ���R���
//
//=============================================================================
#include "number.h"
#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "resource.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �i���o�[�̐�������
//=============================================================================
CNumber *CNumber::Create(D3DXVECTOR3 pos, float fSize)
{
	CNumber *pNumber = NULL;

	if (pNumber == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pNumber = new CNumber;

		if (pNumber != NULL)
		{
			pNumber->Init(pos, fSize);
		}
	}

	return pNumber;
}

//=============================================================================
// �i���o�[�N���X�̃R���X�g���N�^
//=============================================================================
CNumber::CNumber()
{
	// �l���N���A
	m_pVtxBuff = NULL;
}

//=============================================================================
// �i���o�[�N���X�̃f�X�g���N�^
//=============================================================================
CNumber::~CNumber()
{
}

//=============================================================================
// �i���o�[����������
//=============================================================================
HRESULT CNumber::Init(D3DXVECTOR3 pos, float fSize)
{
	// �|���S���̈ʒu��ݒ�
	// �ʒu���擾
	D3DXVECTOR3 posNumber;
	posNumber = pos;

	// �T�C�Y���擾
	float fNumSize;
	fNumSize = fSize;

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

	pVtx[0].pos = D3DXVECTOR3(posNumber.x - fNumSize, posNumber.y - fNumSize, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(posNumber.x + fNumSize, posNumber.y - fNumSize, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(posNumber.x - fNumSize, posNumber.y + fNumSize, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(posNumber.x + fNumSize, posNumber.y + fNumSize, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.5f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f, 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �i���o�[�I������
//=============================================================================
void CNumber::Uninit(void)
{
	// ���_�o�b�t�@�̔j��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//=============================================================================
// �i���o�[�X�V����
//=============================================================================
void CNumber::Update(void)
{

}

//=============================================================================
// �i���o�[�`�揈��
//=============================================================================
void CNumber::Draw(void)
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
	pDevice->SetTexture(0, CResource::GetTexture(CResource::TEXTURE_NUMBER));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// �i���o�[�ݒ菈��
//=============================================================================
void CNumber::SetNumber(int nNumber)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (nNumber * 0.1f), 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.1f + (nNumber * 0.1f), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f + (nNumber * 0.1f), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (nNumber * 0.1f), 1.0f);

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �F�̐ݒ菈��
//=============================================================================
void CNumber::SetColor(D3DXCOLOR color)
{
	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].col = color;
	pVtx[1].col = color;
	pVtx[2].col = color;
	pVtx[3].col = color;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}
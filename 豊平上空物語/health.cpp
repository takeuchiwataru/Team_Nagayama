//=============================================================================
//
// �̗͂̏��� [health.cpp]
// Author : ���R���
//
//=============================================================================
#include "health.h"
#include "renderer.h"
#include "resource.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_HEALTH	(3)

//=============================================================================
// �̗͂̐�������
//=============================================================================
CHealth *CHealth::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CHealth *pHealth = NULL;

	if (pHealth == NULL)
	{
		// �̗̓N���X�̐���
		pHealth = new CHealth;

		if (pHealth != NULL)
		{
			pHealth->SetPosition(pos);
			pHealth->SetWidth(fWidth);
			pHealth->SetHeight(fHeight);
			pHealth->Init();
			pHealth->BindTexture(CResource::GetTexture(CResource::TEXTURE_HEALTH));
		}
	}

	return pHealth;
}

//=============================================================================
// �̗̓N���X�̃R���X�g���N�^
//=============================================================================
CHealth::CHealth() : CScene2D(HEALTH_PRIORITY)
{
	// �l���N���A
	m_nHealth = 0;
}

//=============================================================================
// �̗̓N���X�̃f�X�g���N�^
//=============================================================================
CHealth::~CHealth()
{
}

//=============================================================================
// �̗͏���������
//=============================================================================
HRESULT CHealth::Init(void)
{
	// 2D�|���S������������
	CScene2D::Init();

	m_nHealth = MAX_HEALTH;

	return S_OK;
}

//=============================================================================
// �̗͏I������
//=============================================================================
void CHealth::Uninit(void)
{
	// 2D�|���S���I������
	CScene2D::Uninit();
}

//=============================================================================
// �̗͍X�V����
//=============================================================================
void CHealth::Update(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	pVtxBuff = CScene2D::GetVtxBuff();

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_nHealth == 3)
	{
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		// ���_����ݒ�
		pVtx[0].pos = D3DXVECTOR3(CScene2D::GetPosition().x - 90.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(CScene2D::GetPosition().x + 90.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(CScene2D::GetPosition().x - 90.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(CScene2D::GetPosition().x + 90.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
	}
	else if (m_nHealth == 2)
	{
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f * (2.0f / 3.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f * (2.0f / 3.0f), 1.0f);
		// ���_����ݒ�
		pVtx[0].pos = D3DXVECTOR3(CScene2D::GetPosition().x - (90.0f * (2.0f / 3.0f)) - 30.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(CScene2D::GetPosition().x + (90.0f * (2.0f / 3.0f)) - 30.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(CScene2D::GetPosition().x - (90.0f * (2.0f / 3.0f)) - 30.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(CScene2D::GetPosition().x + (90.0f * (2.0f / 3.0f)) - 30.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
	}
	else if (m_nHealth == 1)
	{
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f * (1.0f / 3.0f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f* (1.0f / 3.0f), 1.0f);
		// ���_����ݒ�
		pVtx[0].pos = D3DXVECTOR3(CScene2D::GetPosition().x - (90.0f * (1.0f / 3.0f)) - 60.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(CScene2D::GetPosition().x + (90.0f * (1.0f / 3.0f)) - 60.0f, CScene2D::GetPosition().y - 40.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(CScene2D::GetPosition().x - (90.0f * (1.0f / 3.0f)) - 60.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(CScene2D::GetPosition().x + (90.0f * (1.0f / 3.0f)) - 60.0f, CScene2D::GetPosition().y + 40.0f, 0.0f);
	}
	else if (m_nHealth <= 0)
	{
		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);
	}

	// ���_�o�b�t�@���A�����b�N
	pVtxBuff->Unlock();

	CScene2D::SetVtxBuff(pVtxBuff);
}

//=============================================================================
// �̗͕`�揈��
//=============================================================================
void CHealth::Draw(void)
{
	// 2D�|���S���`�揈��
	CScene2D::Draw();
}

//=============================================================================
// �̗͌�������
//=============================================================================
void CHealth::CutHealth(int nHealth)
{
	m_nHealth -= nHealth;
}
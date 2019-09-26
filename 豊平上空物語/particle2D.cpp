//=============================================================================
//
// �p�[�e�B�N���̏��� [particle2D.cpp]
// Author : ���R���
//
//=============================================================================
#include "particle2D.h"
#include "manager.h"
#include "renderer.h"
#include "resource.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �G�t�F�N�g�̐�������
//=============================================================================
CParticle2D *CParticle2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight)
 {
	CParticle2D *pParticle = NULL;

	if (pParticle == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pParticle = new CParticle2D;

		if (pParticle != NULL)
		{
			pParticle->Init();
			pParticle->SetCol(col);
			pParticle->SetPosition(pos);
			pParticle->m_move = move;
			pParticle->SetWidth(fWidth);
			pParticle->SetHeight(fHeight);
			pParticle->BindTexture(CResource::GetTexture(CResource::TEXTURE_PARTICLE2D));
		}
	}
	return pParticle;
}

//=============================================================================
// �G�t�F�N�g�N���X�̃R���X�g���N�^
//=============================================================================
CParticle2D::CParticle2D(int nPriority, OBJTYPE objType)
{
	// �l���N���A
	m_nLife = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �G�t�F�N�g�N���X�̃f�X�g���N�^
//=============================================================================
CParticle2D::~CParticle2D()
{
}

//=============================================================================
// �G�t�F�N�g�̏���������
//=============================================================================
HRESULT CParticle2D::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CScene2D::Init();

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PARTICLE);

	// �l��������
	m_nLife = 10;

	return S_OK;
}

//=============================================================================
// �G�t�F�N�g�̏I������
//=============================================================================
void CParticle2D::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CScene2D::Uninit();
}

//=============================================================================
// �G�t�F�N�g�̍X�V����
//=============================================================================
void CParticle2D::Update(void)
{
	// �T�C�Y���擾
	float fWidth = CScene2D::GetWidth();

	// �T�C�Y���擾
	float fHeight = CScene2D::GetHeight();

	// �ʒu���擾
	D3DXVECTOR3 pos;
	pos = CScene2D::GetPosition();

	// ���_�o�b�t�@���擾
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;
	VtxBuff = CScene2D::GetVtxBuff();

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ��莞�Ԍo��
	m_nLife--;

	if (m_nLife <= 0)
	{
		// ����
		Uninit();
	}

	fWidth -= 1.0f;
	fHeight -= 1.0f;

	if (fWidth <= 0 && fHeight <= 0)
	{
		fWidth = 0.0f;
		fHeight = 0.0f;
	}

	pos -= m_move;

	// ���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(pos.x - fWidth, pos.y - fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(pos.x + fWidth, pos.y - fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(pos.x - fWidth, pos.y + fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(pos.x + fWidth, pos.y + fHeight, 0.0f);

	// ���_�o�b�t�@���A�����b�N
	VtxBuff->Unlock();

	// �ʒu�̐ݒ�
	CScene2D::SetPosition(pos);

	// ���̐ݒ�
	CScene2D::SetWidth(fWidth);

	// �����̐ݒ�
	CScene2D::SetHeight(fHeight);

	// ���_�o�b�t�@�̐ݒ�
	CScene2D::SetVtxBuff(VtxBuff);
}

//=============================================================================
// �G�t�F�N�g�̕`�揈��
//=============================================================================
void CParticle2D::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���u�����f�B���O�����Z�����ɐݒ�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// 2D�I�u�W�F�N�g�`�揈��
	CScene2D::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}
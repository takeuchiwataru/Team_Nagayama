//=============================================================================
//
// �p�[�e�B�N���̏��� [particle3D.cpp]
// Author : ���R���
//
//=============================================================================
#include "particle3D.h"
#include "manager.h"
#include "renderer.h"
#include "resource.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PARTICLE3D_GRAVITY	(0.5f)	// �d��

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �p�[�e�B�N���̐�������
//=============================================================================
CParticle3D *CParticle3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col, float fWidth, float fHeight, int nLife, PARTICLE_TYPE type, int nTexture)
{
	CParticle3D *pParticle = NULL;

	if (pParticle == NULL)
	{
		// �p�[�e�B�N���N���X�̐���
		pParticle = new CParticle3D;

		if (pParticle != NULL)
		{
			pParticle->SetPosition(pos);					// �ʒu�̐ݒ�
			pParticle->m_move = move;						// �ړ��ʂ̐ݒ�
			pParticle->SetWidth(fWidth);					// ���̐ݒ�
			pParticle->SetHeight(fHeight);					// �����̐ݒ�
			pParticle->m_nLife = nLife;						// ���C�t�̐ݒ�
			pParticle->Init();								// ����������
			pParticle->BindTexture(CResource::GetTexture(nTexture));
			pParticle->m_ParticleType = type;				// ��ނ̐ݒ�
			pParticle->SetCol(col);							// �F�̐ݒ�
		}
	}
	return pParticle;
}

//=============================================================================
// �p�[�e�B�N���N���X�̃R���X�g���N�^
//=============================================================================
CParticle3D::CParticle3D() : CBillboard(PARTICLE_PRIORITY)
{
	// �l���N���A
	m_nLife = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ParticleType = TYPE_NORMAL;
}

//=============================================================================
// �p�[�e�B�N���N���X�̃f�X�g���N�^
//=============================================================================
CParticle3D::~CParticle3D()
{
}

//=============================================================================
// �p�[�e�B�N���̏���������
//=============================================================================
HRESULT CParticle3D::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CBillboard::Init();

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_PARTICLE);

	// �^�C�v�̏����ݒ�
	m_ParticleType = TYPE_NORMAL;

	return S_OK;
}

//=============================================================================
// �p�[�e�B�N���̏I������
//=============================================================================
void CParticle3D::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CBillboard::Uninit();
}

//=============================================================================
// �p�[�e�B�N���̍X�V����
//=============================================================================
void CParticle3D::Update(void)
{
	// �T�C�Y���擾
	float fWidth = CBillboard::GetWidth();

	// �T�C�Y���擾
	float fHeight = CBillboard::GetHeight();

	// �ʒu���擾
	D3DXVECTOR3 pos;
	pos = CBillboard::GetPosition();

	// ���_�o�b�t�@���擾
	LPDIRECT3DVERTEXBUFFER9 VtxBuff;
	VtxBuff = CBillboard::GetVtxBuff();

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ��莞�Ԍo��
	m_nLife--;

	fWidth -= 0.1f;
	fHeight -= 0.1f;

	if (fWidth <= 0 && fHeight <= 0)
	{
		fWidth = 0.0f;
		fHeight = 0.0f;
	}

	// ���_���W�̍X�V
	pVtx[0].pos = D3DXVECTOR3(-fWidth, fHeight, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(fWidth, fHeight, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-fWidth, -fHeight, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(fWidth, -fHeight, 0.0f);

	pos -= m_move;

	switch (m_ParticleType)
	{
		// �ʏ���
	case TYPE_NORMAL:
		break;
		// �㏸���
	case TYPE_UP:
		// �d�͌��Z
		m_move.y -= cosf(D3DX_PI * 0.0f) * PARTICLE3D_GRAVITY;
		break;
		// ���~���
	case TYPE_DOWN:
		// �d�͉��Z
		m_move.y += cosf(D3DX_PI * 0.0f) * PARTICLE3D_GRAVITY;
		break;
	}

	// ���_�o�b�t�@���A�����b�N
	VtxBuff->Unlock();

	// �ʒu�̐ݒ�
	CBillboard::SetPosition(pos);

	// ��]�̐ݒ�
	CBillboard::SetRot(m_rot);

	// ���̐ݒ�
	CBillboard::SetWidth(fWidth);

	// �����̐ݒ�
	CBillboard::SetHeight(fHeight);

	if (m_nLife <= 0)
	{
		// ����
		Uninit();
	}
}

//=============================================================================
// �p�[�e�B�N���̕`�揈��
//=============================================================================
void CParticle3D::Draw(void)
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

	// �[�x�o�b�t�@��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// 2D�I�u�W�F�N�g�`�揈��
	CBillboard::Draw();

	// ���u�����f�B���O�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �[�x�o�b�t�@�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}
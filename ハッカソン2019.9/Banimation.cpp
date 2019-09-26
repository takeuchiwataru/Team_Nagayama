//=============================================================================
//
// �A�j���[�V�����̏��� [animation.cpp]
// Author : ���R�@���
//
//=============================================================================
#include "main.h"
#include "Banimation.h"
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"
#include "debugProc.h"
#include "resource.h"
#include "player.h"
#include "game.h"
#include "tutorial.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************


//=============================================================================
//	�R���X�g���N�^
//=============================================================================
CBAnimation::CBAnimation() : CBillboard(4, CBillboard::OBJTYPE_EFFECT)
{
	m_fUV_U = 0.0f;
	m_fUV_V = 0.0f;
	m_nLife = 0;
	m_nDrawType = 0;
	m_nCounterAnim = 0;
	m_fCntSpeed = 0.0f;
	m_nPatternAnim = 0;
	m_nTypePlayer = 0;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
CBAnimation::~CBAnimation()
{

}

//=============================================================================
// �A�j���[�V�����̏���������
//=============================================================================
HRESULT CBAnimation::Init(D3DXVECTOR3 pos, D3DXCOLOR col, float fHeight, float fWidth, float fUV_U, float fUV_V, float fCntSpeed, int nTotalAnim,
	int nRoop,int nDrawType,int nTypePlayer,int nTexType)
{
	m_nTexType = nTexType; 
	//�F����
	m_col = col;
	CBillboard::SetHeight(fHeight);
	CBillboard::SetWidth(fWidth);

	//������
	CBillboard::Init();
	CBillboard::SetPosition(pos);

	//�e�N�X�`���̓\��t��
	CBillboard::BindTexture(CResource::GetTexture(m_nTexType));
	CBillboard::SetCol(m_col);

	//UV�̒l����
	m_fUV_U = fUV_U;
	m_fUV_V = fUV_V;

	//�A�j���[�V�����̐ݒ�
	CBillboard::SetAnimation(0, m_fUV_U, m_fUV_V);

	//�A�j���[�V�����̑���
	m_fCntSpeed = fCntSpeed;

	//�A�j���[�V�����̍��v����
	m_nTotalAnim = nTotalAnim;

	//�A�j���[�V�������[�v���邩���Ȃ���
	m_nRoop = nRoop;

	//�`��^�C�v
	m_nDrawType = nDrawType;

	//1P��2P��
	m_nTypePlayer = nTypePlayer;

	m_bUse = true;
	m_bDestroy = false;

	return S_OK;
}

//=============================================================================
// �A�j���[�V�����̏I������
//=============================================================================
void CBAnimation::Uninit(void)
{
	//�I������
	CBillboard::Uninit();
}

//=============================================================================
// �A�j���[�V�����̍X�V����
//=============================================================================
void CBAnimation::Update(void)
{
	CPlayer *pPlayer = NULL;
	pPlayer = CGame::GetPlayer();

	
		D3DXVECTOR3 pos;
		if (pPlayer != NULL)
		{
			pos = pPlayer->GetPos();
		}

		if (m_nRoop == 0)
		{//���[�v����

		 //�A�j���[�V������i�߂�X�V����
			UpdateAnim();
		}
		else if (m_nRoop == 1)
		{//���[�v���Ȃ�

		 //���������炷
			m_nLife--;

			//�����x�����炷
			m_col.a -= 0.009f;

			if (m_bUse == true)
			{
				//�A�j���[�V������i�߂�X�V����
				UpdateAnim();
			}

			if (m_nTotalAnim - 1 == m_nPatternAnim)
			{//�A�j���[�V�������~�߂�
				m_bUse = false;
			}
			//�F�̒l���X�V����
			SetCol(m_col);
		}

		//�F��0.0f�ɂȂ�����
		if (m_col.a <= 0.0f)
		{
			//�j���t���O��������
			m_bDestroy = true;
		}

		if (m_bDestroy == true)
		{
			//�e�N�X�`����j��
			Uninit();
		}

		if (m_nTypePlayer == 0)
		{
			CBillboard::SetPosition(D3DXVECTOR3(pos.x + 0.0f, pos.y, pos.z - 15.0f));
		}

		//�e�N�X�`���̔j���t���O
		m_bDestroy = false;
}

//=============================================================================
// �A�j���[�V������i�߂�X�V����
//=============================================================================
void CBAnimation::UpdateAnim(void)
{
	//�A�j���[�V�����̃J�E���^�[��i�߂�
	m_nCounterAnim++;

	if ((m_nCounterAnim % (int)m_fCntSpeed) == 0)
	{
		//�p�^�[���X�V
		m_nPatternAnim = (m_nPatternAnim + 1) % m_nTotalAnim;

		//�A�j���[�V�����̐ݒ�
		CBillboard::SetAnimation(m_nPatternAnim, m_fUV_U, m_fUV_V);
	}
}

//=============================================================================
//�A�j���[�V�����̕`�揈��
//=============================================================================
void CBAnimation::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X���擾
	CManager Manager;
	pDevice = Manager.GetRenderer()->GetDevice();

	if (m_nDrawType == 0)
	{
		//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_ALPHAREF, 500);
		pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		// ���u�����f�B���O�����Z�����ɐݒ�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

		//�`�揈��
		CBillboard::Draw();

		// ���u�����f�B���O�����ɖ߂�
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

		//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	}
	else
	{
		//�`�揈��
		CBillboard::Draw();
	}
}

//=============================================================================
// �A�j���[�V�����̐�������
//=============================================================================
CBAnimation *CBAnimation::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float fHeight, float fWidth, float fUV_U, float fUV_V, float fCntSpeed, int nTotalAnim, int nRoop,int nDrawType,int nTypePlayer,int nTexType)
{
	CBAnimation *pBAnimation = {};

	if (pBAnimation == NULL)
	{//NULL��������

	 //�������̓��I�m��
		pBAnimation = new CBAnimation;

		if (pBAnimation != NULL)
		{
			// �|���S���̏���������
			pBAnimation->Init(pos, col, fWidth, fHeight, fUV_U, fUV_V, fCntSpeed, nTotalAnim, nRoop, nDrawType,nTypePlayer,nTexType);
		}
		else
		{
			MessageBox(0, "NULL�ł���", "�x��", MB_OK);
		}
	}
	else
	{
		MessageBox(0, "NULL����Ȃ��ł�", "�x��", MB_OK);
	}

	return pBAnimation;
}
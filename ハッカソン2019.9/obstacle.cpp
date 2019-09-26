//=============================================================================
//
// �|���S������ [Bullet.cpp]
// Author : ���R���
//
//=============================================================================
#include "obstacle.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "resource.h"
#include "particleX.h"
#include "player.h"
#include "game.h"
#include "tutorial.h"
#include "shadow.h"
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PARTICLE_NUM		(80)	// �u���b�N��j�󂵂��Ƃ��̃p�[�e�B�N����
#define PARTICLE_TIME		(20)	// �u���b�N��j�󂵂��Ƃ��̃p�[�e�B�N���o������
#define COLLISION_BLOCK		(40)	// �u���b�N�Ƃ̓����蔻��
#define BULLET_LIFE			(40)	// �e�̏o������

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================

//=============================================================================
// �v���C���[�N���X�̃R���X�g���N�^
//=============================================================================
CObstacle::CObstacle() : CSceneX(BULLET_PRIORITY)
{
	// �l���N���A
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = 0;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObstacle::~CObstacle()
{
}

//=============================================================================
// �e�̐�������
//=============================================================================
CObstacle *CObstacle::Create(D3DXVECTOR3 pos, D3DXVECTOR3 move, D3DXCOLOR col)
{
	CObstacle *pBullet = NULL;

	if (pBullet == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pBullet = new CObstacle;

		if (pBullet != NULL)
		{
			pBullet->m_pos = pos;
			pBullet->BindModel(CResource::GetBuffMat(CResource::MODEL_BULLET), CResource::GetNumMat(CResource::MODEL_BULLET), CResource::GetMesh(CResource::MODEL_BULLET));
			pBullet->Init();
			pBullet->m_move = move;
			pBullet->m_col = col;
		}
	}
	return pBullet;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CObstacle::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_BULLET);

	CSceneX::Init();

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_nLife = BULLET_LIFE;
	m_bHit = true;
	m_bDestroy = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObstacle::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObstacle::Update(void)
{
#ifdef _DEBUG
	//CDebugProc::Print("cfccfccfc", "BulletPos : x", pos.x, "f", "   y", pos.y, "f", "  z", pos.z, "f");
#endif
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObstacle::Draw(void)
{
	// 2D�I�u�W�F�N�g�`�揈��
	CSceneX::Draw();

	D3DXMATRIX mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

										// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//================================================================
	// �e�̐ݒ�
	//================================================================
	D3DXMATRIX mtxShadow;		// �V���h�E�}�g���b�N�X
	D3DXPLANE planeField;
	D3DXVECTOR4 vecLight;
	D3DXVECTOR3 pos, normal;

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���C�g�𖳌��ɂ���
	pDevice->LightEnable(0, FALSE);
	pDevice->LightEnable(1, FALSE);
	pDevice->LightEnable(2, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// �V���h�E�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxShadow);

	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// ���C�g�̕����̐ݒ�
	vecLight = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f);

	// �ʒu��ݒ�
	pos = D3DXVECTOR3(0.0f, 0.6f, 0.0f);

	// �n�ʂ̖@����ݒ�
	normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// �ʒu�Ɩ@�����|�����킹�Ėʂ����
	D3DXPlaneFromPointNormal(&planeField, &pos, &normal);

	// ���C�g�̕����ƖʂŃV���h�E�}�g���b�N�X��ݒ�
	D3DXMatrixShadow(&mtxShadow, &vecLight, &planeField);

	// ���[���h�}�g���b�N�X�Ɗ|�����킹��
	D3DXMatrixMultiply(&mtxShadow, &m_mtxWorld, &mtxShadow);

	// �V���h�E�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)CResource::GetBuffMat(CResource::MODEL_BULLET)->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)CResource::GetNumMat(CResource::MODEL_BULLET); nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// ���f��(�p�[�c)�̕`��
		CResource::GetMesh(CResource::MODEL_BULLET)->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
	// ���C�g��L���ɂ���
	pDevice->LightEnable(0, TRUE);
	pDevice->LightEnable(1, TRUE);
	pDevice->LightEnable(2, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	//�����_�[�X�e�C�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//=============================================================================
// �v���C���[�Ƃ̓����蔻�菈��
//=============================================================================
bool CObstacle::CollisionPlayer(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;

	// ���S�ƒ��S�̍������߂�
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - m_pos.x, pos->y - m_pos.y + 50.0f, pos->z - m_pos.z);

	// ���S���璆�S�̃x�N�g���̒������Z�o
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius && fLength < fRadius && fLength < fRadius)
	{// ���������a�̘a��菬������Γ������Ă���
		bHit = true;
		m_bDestroy = true;
	}

	return bHit;	// �u���b�N�ɓ������Ă��邩�ǂ�����Ԃ�
}
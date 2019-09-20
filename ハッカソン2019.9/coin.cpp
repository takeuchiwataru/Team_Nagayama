//=============================================================================
//
// �R�C������ [coin.cpp]
// Author : ���R���
//
//=============================================================================
#include "coin.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "resource.h"
#include "light.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define ROTATION_SPEED	(0.05f)					// �R�C���̉�]�X�s�[�h

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
int CCoin::m_nNumCoin = 0;			// �R�C���̐�

//=============================================================================
// �R�C���N���X�̃R���X�g���N�^
//=============================================================================
CCoin::CCoin() : CSceneX(COIN_PRIORITY)
{
	// �l���N���A
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMatrixIdentity(&m_mtxWorld);		// ���[���h�}�g���b�N�X
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CCoin::~CCoin()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CCoin *CCoin::Create(D3DXVECTOR3 pos)
{
	CCoin *pCoin = NULL;

	if (pCoin == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pCoin = new CCoin;

		if (pCoin != NULL)
		{
			pCoin->SetPosition(pos);
			pCoin->BindModel(CResource::GetBuffMat(CResource::MODEL_COIN), CResource::GetNumMat(CResource::MODEL_COIN), CResource::GetMesh(CResource::MODEL_COIN));
			pCoin->Init();

			m_nNumCoin++;
		}
	}

	return pCoin;
}

//=============================================================================
// �R�C������������
//=============================================================================
HRESULT CCoin::Init(void)
{
	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_COIN);

	// ����������
	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// �R�C���I������
//=============================================================================
void CCoin::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// �R�C���X�V����
//=============================================================================
void CCoin::Update(void)
{
	// ���͏����擾
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// �Q�[���̃��[�h���擾
	CManager::MODE mode;
	mode = CManager::GetMode();

	// �ʒu���擾
	m_pos = CSceneX::GetPosition();

	m_rot.y += ROTATION_SPEED;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
	
	SetRot(m_rot);
	
	SetPosition(m_pos);

#ifdef _DEBUG
	//CDebugProc::Print("cn", "�R�C���̐� : ", m_nNumCoin);
#endif
}

//=============================================================================
// �R�C���`�揈��
//=============================================================================
void CCoin::Draw(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�@���̎������K��	�J�n
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CSceneX::Draw();

	// ���_�@���̎������K��	�I��
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);

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
	vecLight = D3DXVECTOR4(-CLight::GetLight(0).Direction.x, -CLight::GetLight(0).Direction.y, -CLight::GetLight(0).Direction.z, 0.0f);

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
	pMat = (D3DXMATERIAL*)CResource::GetBuffMat(CResource::MODEL_COIN)->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)CResource::GetNumMat(CResource::MODEL_COIN); nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);

		// ���f��(�p�[�c)�̕`��
		CResource::GetMesh(CResource::MODEL_COIN)->DrawSubset(nCntMat);
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
// �R�C���Ƃ̓����蔻�菈��
//=============================================================================
bool CCoin::Collision(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// �������Ă��Ȃ����

	// ���S�ƒ��S�̍������߂�
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - CSceneX::GetPosition().x, pos->y - CSceneX::GetPosition().y - 20.0f, pos->z - CSceneX::GetPosition().z);

	// ���S���璆�S�̃x�N�g���̒������Z�o
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius + m_VtxMax.x && fLength < fRadius + m_VtxMax.y && fLength < fRadius + m_VtxMax.z)
	{// ���������a�̘a��菬������Γ������Ă���
		bHit = true;
	}

	return bHit;	// �R�C���ɓ������Ă��邩�ǂ�����Ԃ�
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CCoin::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CCoin::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �R�C���̐��̎擾
//=============================================================================
int CCoin::GetNumCoin(void)
{
	return m_nNumCoin;
}

//=============================================================================
// �R�C���̐��̐ݒ�
//=============================================================================
void CCoin::SetNumCoin(int nNumCoin)
{
	m_nNumCoin = nNumCoin;
}
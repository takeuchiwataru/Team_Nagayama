//=============================================================================
//
// 3D���f������ [sceneX.cpp]
// Author : ���R���
//
//=============================================================================
#include "sceneX.h"
#include "input.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "light.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define SCENEX_SIZE	(2.0f)	// �T�C�Y�̒���

//=============================================================================
// 3D���f���N���X�̃R���X�g���N�^
//=============================================================================
CSceneX::CSceneX(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	m_pTexture = NULL;						// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	m_pMesh = NULL;							// ���b�V�����i���_���j�ւ̃|�C���^
	m_pBuffMat = NULL;						// �}�e���A�����ւ̃|�C���^
	m_nNumMat = 0;							// �}�e���A�����̐�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CSceneX::~CSceneX()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CSceneX *CSceneX::Create(D3DXVECTOR3 pos)
{
	CSceneX *pSceneX = NULL;

	if (pSceneX == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pSceneX = new CSceneX;

		if (pSceneX != NULL)
		{
			pSceneX->m_pos = pos;
			pSceneX->Init();
		}
	}

	return pSceneX;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CSceneX::Init(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_���W�̐ݒ�
	SetVtx();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CSceneX::Uninit(void)
{
	// ���f�����̂̉��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CSceneX::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CSceneX::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxScale;				// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;						// ���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	CManager::MODE mode;
	mode = CManager::GetMode();

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (pMat[nCntMat].pTextureFilename != NULL)
		{// �}�e���A���Ƀe�N�X�`�����������ꍇ
			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, m_pTexture[nCntMat]);
		}
		else
		{// �}�e���A���Ƀe�N�X�`�������������ꍇ
			pDevice->SetTexture(0, NULL);
		}

		// ���f��(�p�[�c)�̕`��
		m_pMesh->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CSceneX::GetPosition(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CSceneX::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �����̎擾
//=============================================================================
D3DXVECTOR3 CSceneX::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �����̐ݒ�
//=============================================================================
void CSceneX::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// ���_���̍ő�l�̎擾
//=============================================================================
D3DXVECTOR3 CSceneX::GetVtxMax(void)
{
	return m_VtxMax;
}

//=============================================================================
// ���_���̍ő�l�̐ݒ�
//=============================================================================
void CSceneX::SetVtxMax(D3DXVECTOR3 VtxMax)
{
	m_VtxMax = VtxMax;
}

//=============================================================================
// ���_���̍ŏ��l�̎擾
//=============================================================================
D3DXVECTOR3 CSceneX::GetVtxMin(void)
{
	return m_VtxMin;
}

//=============================================================================
// ���_���̍ŏ��l�̐ݒ�
//=============================================================================
void CSceneX::SetVtxMin(D3DXVECTOR3 VtxMin)
{
	m_VtxMin = VtxMin;
}

//=============================================================================
// ���[���h�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX CSceneX::GetMtxWorld(void)
{
	return m_mtxWorld;
}

//=============================================================================
// ���[���h�}�g���b�N�X�̐ݒ�
//=============================================================================
void CSceneX::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}

//=============================================================================
// ���f�������蓖�Ă�
//=============================================================================
void CSceneX::BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh)
{
	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
	m_pMesh = pMesh;
}

//=============================================================================
// �e�N�X�`���}�e���A�������蓖�Ă�
//=============================================================================
void CSceneX::BindMat(LPDIRECT3DTEXTURE9 *pTexture)
{
	m_pTexture = pTexture;
}

//=============================================================================
// ���_���W�̐ݒ菈��
//=============================================================================
void CSceneX::SetVtx(void)
{
	DWORD sizeFvF;	//���_�t�H�[�}�b�g�̃T�C�Y
	D3DXVECTOR3 vtx;
	int nNumVtx;	//���_��
	BYTE *pVtxBuff;	//���_�o�b�t�@�ւ̃|�C���^

	// ���_�����擾
	nNumVtx = m_pMesh->GetNumVertices();
	// ���_�t�H�[�}�b�g�̃T�C�Y���擾
	sizeFvF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// ���_�̍ŏ��l�ƍő�l����
	m_VtxMin = D3DXVECTOR3(10000, 10000, 10000);
	m_VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

	//���_�o�b�t�@�����b�N
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{//���_���W�̑��
		vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (m_VtxMin.x > vtx.x)
		{
			m_VtxMin.x = vtx.x;
		}
		if (m_VtxMin.y > vtx.y)
		{
			m_VtxMin.y = vtx.y;
		}
		if (m_VtxMin.z > vtx.z)
		{
			m_VtxMin.z = vtx.z;
		}

		if (m_VtxMax.x < vtx.x)
		{
			m_VtxMax.x = vtx.x;
		}
		if (m_VtxMax.y < vtx.y)
		{
			m_VtxMax.y = vtx.y;
		}
		if (m_VtxMax.z < vtx.z)
		{
			m_VtxMax.z = vtx.z;
		}

		//�T�C�Y���|�C���^��i�߂�
		pVtxBuff += sizeFvF;
	}
	//���_�o�b�t�@���A�����b�N
	m_pMesh->UnlockVertexBuffer();
}

//=============================================================================
// �u���b�N�Ƃ̓����蔻�菈��
//=============================================================================
bool CSceneX::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius)
{
	bool bLand = false;	// ����Ă��Ȃ����

	D3DXVECTOR3 ScaleVtxMax;
	D3DXVECTOR3 ScaleVtxMin;

	// �g��𔽉f
	ScaleVtxMax.x = m_VtxMax.x * m_mtxWorld._11;
	ScaleVtxMax.y = m_VtxMax.y * m_mtxWorld._22;
	ScaleVtxMax.z = m_VtxMax.z * m_mtxWorld._33;
	ScaleVtxMin.x = m_VtxMin.x * m_mtxWorld._11;
	ScaleVtxMin.y = m_VtxMin.y * m_mtxWorld._22;
	ScaleVtxMin.z = m_VtxMin.z * m_mtxWorld._33;

	if (pos->y <= m_pos.y + ScaleVtxMax.y - SCENEX_SIZE && pos->y + radius.y >= m_pos.y + ScaleVtxMax.y - SCENEX_SIZE
		|| pos->y + radius.y >= m_pos.y + ScaleVtxMin.y && pos->y <= m_pos.y + ScaleVtxMin.y
		|| pos->y + radius.y <= m_pos.y + ScaleVtxMax.y - SCENEX_SIZE && pos->y >= m_pos.y + ScaleVtxMin.y)
	{// y�͈̔͂̒�
		if (pos->z - radius.z <= m_pos.z + ScaleVtxMax.z && pos->z + radius.z >= m_pos.z + ScaleVtxMin.z)
		{// z�͈̔͂̒�
			if (posOld->x + radius.x <= m_pos.x + ScaleVtxMin.x
				&& pos->x + radius.x > m_pos.x + ScaleVtxMin.x)
			{// X���W�̒��ɍ����������
				pos->x = posOld->x;
				move->x = 0.0f;
			}
			else if (posOld->x - radius.x >= m_pos.x + ScaleVtxMax.x
				&& pos->x - radius.x < m_pos.x + ScaleVtxMax.x)
			{// X���W�̒��ɉE���������
				pos->x = posOld->x;
				move->x = 0.0f;
			}
		}
		if (pos->x - radius.x <= m_pos.x + ScaleVtxMax.x && pos->x + radius.x >= m_pos.x + ScaleVtxMin.x)
		{// x�͈̔͂̒�
			if (posOld->z + radius.z <= m_pos.z + ScaleVtxMin.z
				&& pos->z + radius.z > m_pos.z + ScaleVtxMin.z)
			{// Z���W�̒��Ɏ�O���������
				pos->z = posOld->z;
				move->z = 0.0f;
			}
			else if (posOld->z - radius.z >= m_pos.z + ScaleVtxMax.z
				&& pos->z - radius.z < m_pos.z + ScaleVtxMax.z)
			{// Z���W�̒��Ɍ�납�������
				pos->z = posOld->z;
				move->z = 0.0f;
			}
		}
	}

	if (pos->x - radius.x < m_pos.x + ScaleVtxMax.x - SCENEX_SIZE && pos->x + radius.x > m_pos.x + ScaleVtxMin.x + SCENEX_SIZE
		&& pos->z - radius.z <= m_pos.z + ScaleVtxMax.z - SCENEX_SIZE && pos->z + radius.z >= m_pos.z + ScaleVtxMin.z + SCENEX_SIZE)
	{// ��Q���̓����ɏ����
		if (posOld->y >= m_pos.y + ScaleVtxMax.y && pos->y < m_pos.y + ScaleVtxMax.y
			|| pos->y <= m_pos.y + ScaleVtxMax.y && posOld->y > m_pos.y + ScaleVtxMax.y)
		{// �ォ��u���b�N�ɓ��������Ƃ�
			bLand = true;  // ����������Ԃ�
			pos->y = m_pos.y + ScaleVtxMax.y;
			move->y = 0.0f;  // �ړ��ʂ��Ȃ���
		}

		if (posOld->y + radius.y < m_pos.y + ScaleVtxMin.y && pos->y + radius.y >= m_pos.y + ScaleVtxMin.y
			|| pos->y + radius.y > m_pos.y + ScaleVtxMin.y && posOld->y + radius.y <= m_pos.y + ScaleVtxMin.y)
		{// ������u���b�N�ɓ��������Ƃ�
			pos->y = posOld->y;
			move->y = 0.0f;  // �ړ��ʂ��Ȃ���
		}
	}

	return bLand;	// �u���b�N�ɏ���Ă��邩�ǂ�����Ԃ�
}
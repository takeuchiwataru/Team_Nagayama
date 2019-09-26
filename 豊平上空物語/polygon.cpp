//=============================================================================
//
// 3D�|���S������ [polygon.cpp]
// Author : ���R���
//
//=============================================================================
#include "polygon.h"
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "player.h"
#include "game.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define ALPHA_REF		(150)
#define POLYGON_SIZE	(2.0f)	// ����

//=============================================================================
// 3D�|���S���N���X�̃R���X�g���N�^
//=============================================================================
CPolygon::CPolygon(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	m_pTexture = NULL;						// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����

	for (int nCntNor = 0; nCntNor < NUM_VTX; nCntNor++)
	{
		m_aVec[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �@��
		m_aPos[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �@��
		m_aNor[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �@��
	}

	m_fDepth = 0.0f;		// ���s
	m_fWifth = 0.0f;		// ��

	m_fTextureU = 0.0f;					// �e�N�X�`��������
	m_fTextureV = 0.0f;					// �e�N�X�`��������
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CPolygon::~CPolygon()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CPolygon *CPolygon::Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV)
{
	CPolygon *pScene3D = NULL;

	if (pScene3D == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pScene3D = new CPolygon;

		if (pScene3D != NULL)
		{
			pScene3D->m_fDepth = fDepth;
			pScene3D->m_fWifth = fWifth;
			pScene3D->m_fTextureU = fTextureU;
			pScene3D->m_fTextureV = fTextureV;
			pScene3D->Init();
			pScene3D->m_pos = pos;
		}
	}

	return pScene3D;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CPolygon::Init(void)
{
	// �|���S���̏���ݒ�
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntNor = 0; nCntNor < NUM_VTX; nCntNor++)
	{
		m_aVec[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �@��
		m_aPos[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �@��
		m_aNor[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �@��
	}

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_fWifth, 0.0f, m_fDepth);
	pVtx[1].pos = D3DXVECTOR3(m_fWifth, 0.0f, m_fDepth);
	pVtx[2].pos = D3DXVECTOR3(-m_fWifth, 0.0f, -m_fDepth);
	pVtx[3].pos = D3DXVECTOR3(m_fWifth, 0.0f, -m_fDepth);

	// �@���̐ݒ�
	// �x�N�g�������߂�
	m_aVec[0] = pVtx[2].pos - pVtx[3].pos;
	m_aVec[1] = pVtx[1].pos - pVtx[3].pos;
	m_aVec[2] = pVtx[1].pos - pVtx[0].pos;
	m_aVec[3] = pVtx[2].pos - pVtx[0].pos;

	// �O�ς��g���Ė@�������߂�
	D3DXVec3Cross(&m_aNor[0], &m_aVec[0], &m_aVec[1]);
	D3DXVec3Cross(&m_aNor[1], &m_aVec[2], &m_aVec[3]);

	// ���K������
	D3DXVec3Normalize(&m_aNor[0], &m_aNor[0]);
	D3DXVec3Normalize(&m_aNor[1], &m_aNor[1]);

	// �@���̐ݒ�
	pVtx[0].nor = m_aNor[1];
	pVtx[1].nor = (m_aNor[0] + m_aNor[1]) / 2;
	pVtx[2].nor = (m_aNor[0] + m_aNor[1]) / 2;
	pVtx[3].nor = m_aNor[0];

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f * m_fTextureU, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * m_fTextureV);
	pVtx[3].tex = D3DXVECTOR2(1.0f * m_fTextureU, 1.0f * m_fTextureV);

	for (int nCntPos = 0; nCntPos < NUM_VTX; nCntPos++)
	{
		m_aPos[nCntPos] = pVtx[nCntPos].pos;
		m_aNor[nCntPos] = pVtx[nCntPos].nor;
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CPolygon::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �I�u�W�F�N�g�̉��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CPolygon::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void CPolygon::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

									// �f�o�C�X���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	//�A���t�@�e�X�g(�����F��`�悵�Ȃ��悤��)
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, ALPHA_REF);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//�����_�[�X�e�[�g�̐ݒ�����ɖ߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

//=============================================================================
// �@�����擾
//=============================================================================
D3DXVECTOR3 CPolygon::GetNor(int nIdx)
{
	D3DXVECTOR3 vecA[2];
	return m_aNor[nIdx];
}

//=============================================================================
// ���L�e�N�X�`�������蓖�Ă�
//=============================================================================
void CPolygon::BindTexture(LPDIRECT3DTEXTURE9 Texture)
{
	m_pTexture = Texture;
}

//=============================================================================
// �F�̐ݒ�
//=============================================================================
void CPolygon::SetCol(D3DXCOLOR col)
{
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	// ���_�o�b�t�@���A�����b�N
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �傫���̐ݒ�
//=============================================================================
void CPolygon::SetDepth(float fDepth)
{
	m_fDepth = fDepth;
}

//=============================================================================
// �傫���̐ݒ�
//=============================================================================
void CPolygon::SetWidth(float fWidth)
{
	m_fWifth = fWidth;
}

//=============================================================================
// �e�N�X�`���̕������̐ݒ�
//=============================================================================
void CPolygon::SetTextureU(float fTextureU)
{
	m_fTextureU = fTextureU;
}

//=============================================================================
// �e�N�X�`���̕������̐ݒ�
//=============================================================================
void CPolygon::SetTextureV(float fTextureV)
{
	m_fTextureV = fTextureV;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
D3DXVECTOR3 CPolygon::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CPolygon::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �����̐ݒ�
//=============================================================================
void CPolygon::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// �������擾
//============================================================================
float CPolygon::GetHeight(D3DXVECTOR3 pos)
{
	CScene *pScene = NULL;

	// �擪�̃I�u�W�F�N�g���擾(���f���̗D�揇�ʂ�1������A1�ɂ���I�u�W�F�N�g�����ׂČ���)
	pScene = CScene::GetTop(PLAYER_PRIORITY);

	while (pScene != NULL)
	{// �D�揇�ʂ�3�̃I�u�W�F�N�g��1��1�m���߂�
	 // �����̍Œ��ɏ�����\�������邩���ɋL�^���Ă���
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// ���S�t���O�������Ă��Ȃ�����
			if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
			{// �I�u�W�F�N�g�̎�ނ��m���߂�
			 // �E���̎O�p�ɂ��邩�ǂ������擾
				bool bRTriangle;
				bRTriangle = ((CPlayer*)pScene)->GetRTriangle();

				if (bRTriangle == true)
				{
					pos.y = (((m_aNor[0].x * (pos.x - m_aPos[0].x) + m_aNor[0].z * (pos.z - m_aPos[0].z)) / -m_aNor[0].y) + m_aPos[0].y);
				}
				else
				{
					pos.y = (((m_aNor[3].x * (pos.x - m_aPos[3].x) + m_aNor[3].z * (pos.z - m_aPos[3].z)) / -m_aNor[3].y) + m_aPos[3].y);
				}
			}

			// ���̃V�[���ɐi�߂�
			pScene = pSceneNext;
		}
	}

	return pos.y;
}

//=============================================================================
// �����蔻��
//=============================================================================
bool CPolygon::ColLand(D3DXVECTOR3 *pos, D3DXVECTOR3 radius)
{
	bool bLand = false;	// ����Ă��Ȃ����

	if (pos->x - radius.x < m_pos.x + m_fWifth - POLYGON_SIZE && pos->x + radius.x > m_pos.x - m_fWifth + POLYGON_SIZE
		&& pos->z - radius.z <= m_pos.z + m_fDepth - POLYGON_SIZE && pos->z + radius.z >= m_pos.z - m_fDepth + POLYGON_SIZE)
	{// ��Q���̓����ɏ����
		if (pos->y >= m_pos.y - PLAYER_HEIGHT)
		{// �ォ��u���b�N�ɓ��������Ƃ�
			bLand = true;  // ����������Ԃ�
		}
	}

	return bLand;	// �u���b�N�ɏ���Ă��邩�ǂ�����Ԃ�
}
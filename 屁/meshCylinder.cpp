//=============================================================================
//
// �~���̃|���S������ [meshCylinder.cpp]
// Author : ���R���
//
//=============================================================================
#include "meshCylinder.h"
#include "renderer.h"
#include "manager.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define CYLINDER_ROT_SPEED	(0.0005f)	// ��]�X�s�[�h

//=============================================================================
// ���b�V���V�����_�[�̃R���X�g���N�^
//=============================================================================
CMeshCylinder::CMeshCylinder(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;
	m_nNumVerTex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_fSizeX = 0.0f;
	m_fSizeY = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bLand = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshCylinder::~CMeshCylinder()
{
}

//=============================================================================
// ���b�V���V�����_�[�̐�������
//=============================================================================
CMeshCylinder *CMeshCylinder::Create(D3DXVECTOR3 pos, float fSizeX, float fSizeY)
{
	CMeshCylinder *pMeshCylinder = NULL;

	if (pMeshCylinder == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pMeshCylinder = new CMeshCylinder;

		if (pMeshCylinder != NULL)
		{
			pMeshCylinder->m_fSizeX = fSizeX;
			pMeshCylinder->m_fSizeY = fSizeY;
			pMeshCylinder->m_pos = pos;	// �ʒu�̐ݒ�
			pMeshCylinder->Init();			// ����������
		}
	}

	return pMeshCylinder;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshCylinder::Init(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// �f�o�C�X�̎擾
		pDevice = pRenderer->GetDevice();
	}

	int nCntVtxX = 0;
	int nCntVtxY = 0;
	int nCntIdxY;
	int nCntIdxX;
	int nIdxCounter = 0;
	int nCntVtx = 0;
	float fPos_X = 0;
	float fPos_Y = 0;
	float fXpos = -m_fSizeX;
	float fYpos = m_fSizeY;
	int nCntIdx = 0;
	float fCylinder = 0.0f;
	int  nCylinder = 0;

	// ���_��
	m_nNumVerTex = (CYLINDER_X + 1) * (CYLINDER_Y + 1);

	// �C���f�b�N�X��
	m_nNumIndex = (CYLINDER_X + 1) * (CYLINDER_Y + 1)
		+ (2 * (CYLINDER_Y - 1))
		+ (CYLINDER_X + 1) * (CYLINDER_Y - 1);

	// �|���S����
	m_nNumPolygon = m_nNumIndex - 2;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHCYLINDER_TEXTURENAME, &m_pTexture);

	// ���_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVerTex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,	// �m�ۂ���o�b�t�@�̃T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,										// 16�r�b�g�̃f�[�^���m��
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);


	VERTEX_3D *pVtx;
	//���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	
	//���W�𒆐S�ɂ���
	fPos_X = (fXpos * CYLINDER_X) / 2;
	fPos_Y = (fYpos * CYLINDER_Y) / 2;

	for (nCntVtxY = 0; nCntVtxY < CYLINDER_Y + 1; nCntVtxY++)
	{
		for (nCntVtxX = 0; nCntVtxX < CYLINDER_X + 1; nCntVtxX++)
		{

			//���_���̐ݒ�
			pVtx[(nCntVtxY + nCntVtxX) + nCntVtx].pos = D3DXVECTOR3(sinf(fCylinder * D3DX_PI) * fXpos, 20.0f - nCylinder, cosf(fCylinder * D3DX_PI) * fXpos);

			// �@���̐ݒ�
			pVtx[(nCntVtxY + nCntVtxX) + nCntVtx].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			//���_�J���[
			pVtx[(nCntVtxY + nCntVtxX) + nCntVtx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//�e�N�X�`�����W
			pVtx[(nCntVtxY + nCntVtxX) + nCntVtx].tex = D3DXVECTOR2(0.0f + (nCntVtxX * (1.0f / CYLINDER_X)), 0.0f + (nCntVtxY * (1.0f / CYLINDER_Y)));

			//�p�x1������
			if (fCylinder >= 1.0f)
			{
				fCylinder = -1.0f;
			}

			//X�̕�����/2��1������
			fCylinder += 1.0f / (CYLINDER_X / 2);

		}
		//���_���̒l��ێ�
		nCntVtx += CYLINDER_X;
		nCylinder += (int)m_fSizeY;
		fCylinder = 0.0f;
	}

	//SetNor();

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
	
	//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD *pIdx;
	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxY = 0; nCntIdxY < CYLINDER_Y; nCntIdxY++)
	{
		for (nCntIdxX = 0; nCntIdxX < CYLINDER_X + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + CYLINDER_X + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxY < CYLINDER_Y - 1 && nCntIdxX == CYLINDER_X)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (CYLINDER_X + 1) + 1;
				pIdx += 2;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshCylinder::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}

	// �I�u�W�F�N�g�̉��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshCylinder::Update(void)
{
	// ��]
	m_rot.y += CYLINDER_ROT_SPEED;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshCylinder::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// �f�o�C�X�̎擾
		pDevice = pRenderer->GetDevice();
	}

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

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVerTex, 0, m_nNumPolygon);
}

//=============================================================================
// �@���̐ݒ�
//=============================================================================
void CMeshCylinder::SetNor(void)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPolygon = 0;
	int nCntNorPolygon = 0;

	for (int nCntZ = 0; nCntZ < CYLINDER_Y; nCntZ++)
	{
		for (int nCntX = 0; nCntX < CYLINDER_X; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 vec0, vec1, vec2;
			D3DXVECTOR3 nor;

			// ����̃|���S���̂Q�̃x�N�g������@�����Z�o
			pPos0 = &pVtx[nCntX + nCntZ + nCntPolygon].pos;
			pPos1 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (CYLINDER_X + 1)].pos;
			pPos2 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (CYLINDER_X + 1) + 1].pos;
			pPos3 = &pVtx[(nCntX + nCntZ + nCntPolygon) + 1].pos;

			vec0 = *pPos1 - *pPos0;
			vec1 = *pPos2 - *pPos0;
			vec2 = *pPos3 - *pPos0;

			// �O�ς��g���Ċe�|���S���̖@�������߂�
			D3DXVec3Cross(&nor, &vec1, &vec0);
			// ���K������
			D3DXVec3Normalize(&nor, &nor);
			// �@����ۑ�
			m_aNor[(nCntZ * 2) + (nCntX * 2) + nCntNorPolygon] = nor;

			// �O�ς��g���Ċe�|���S���̖@�������߂�
			D3DXVec3Cross(&nor, &vec2, &vec1);
			// ���K������
			D3DXVec3Normalize(&nor, &nor);
			// �@����ۑ�
			m_aNor[(nCntZ * 2) + (nCntX * 2) + nCntNorPolygon + 1] = nor;
		}

		nCntPolygon += CYLINDER_X;
		nCntNorPolygon += (CYLINDER_X * 2) - 2;
	}

	int nData0 = 0;
	int nData1 = 0;

	for (int nCntPolygonZ = 0; nCntPolygonZ < CYLINDER_Y + 1; nCntPolygonZ++)
	{
		for (int nCntPolygonX = 0; nCntPolygonX < CYLINDER_X + 1; nCntPolygonX++)
		{
			if (nCntPolygonZ == 0)
			{// ��[
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntPolygonX == CYLINDER_X)
				{// �E�[
					pVtx[CYLINDER_X].nor = m_aNor[CYLINDER_X + (CYLINDER_X - 1)];
				}
				else
				{// ��[�̐^��
					pVtx[nCntPolygonX].nor =
						(m_aNor[(nCntPolygonX * 2) - 1] + m_aNor[((nCntPolygonX * 2) - 1) + 1] + m_aNor[((nCntPolygonX * 2) - 1) + 2]) / 3;
				}
			}
			else if (nCntPolygonZ == CYLINDER_Y)
			{// ���[
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[CYLINDER_Y * (CYLINDER_X + 1)].nor = m_aNor[2 * (CYLINDER_X * (CYLINDER_Y - 1))];
				}
				else if (nCntPolygonX == CYLINDER_X)
				{// �E�[
					pVtx[(CYLINDER_X * CYLINDER_Y) + (CYLINDER_X + CYLINDER_Y)].nor =
						(m_aNor[(2 * (CYLINDER_X * (CYLINDER_Y - 1))) + (2 * (CYLINDER_X - 1))] +
							m_aNor[((2 * (CYLINDER_X * (CYLINDER_Y - 1))) + (2 * (CYLINDER_X - 1))) + 1]) / 2;
				}
				else
				{// ���[�̐^��
					pVtx[(CYLINDER_Y * (CYLINDER_X + 1)) + nCntPolygonX].nor =
						(m_aNor[(CYLINDER_Y - 1) * (CYLINDER_X * 2) + (nCntPolygonX * 2) - 2] +
							m_aNor[((CYLINDER_Y - 1) * (CYLINDER_X * 2) + (nCntPolygonX * 2) - 2) + 1] +
							m_aNor[((CYLINDER_Y - 1) * (CYLINDER_X * 2) + (nCntPolygonX * 2) - 2) + 2]) / 3;
				}
			}
			else
			{// �^��
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[(CYLINDER_X + 1) * nCntPolygonZ].nor =
						(m_aNor[(nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X)] +
							m_aNor[(nCntPolygonZ * (2 * CYLINDER_X))] +
							m_aNor[(nCntPolygonZ * (2 * CYLINDER_X) + 1)]) / 3;
				}
				else if (nCntPolygonX == CYLINDER_X)
				{// �E�[
					pVtx[((nCntPolygonZ + 1) * CYLINDER_X) + nCntPolygonZ].nor =
						(m_aNor[((CYLINDER_X - 1) * 2 + ((CYLINDER_X * 2)* (nCntPolygonZ - 1)))]
							+ m_aNor[((CYLINDER_X - 1) * 2 + ((CYLINDER_X * 2)* (nCntPolygonZ - 1))) + 1]
							+ m_aNor[((CYLINDER_X - 1) * 2 + ((CYLINDER_X * 2)* (nCntPolygonZ - 1))) + ((CYLINDER_X * 2) + 1)]) / 3;
				}
				else
				{
					pVtx[(CYLINDER_X + 2) + (nCntPolygonX - 1) + ((nCntPolygonZ * (CYLINDER_X + 1)) - (CYLINDER_X + 1))].nor =
						(m_aNor[((nCntPolygonX - 1) * 2) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 1) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X)))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 2) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X)))] +
							m_aNor[((2 * CYLINDER_X) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X))) + ((nCntPolygonX * 2) - 1)] +
							m_aNor[((2 * CYLINDER_X) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X)) + 1) + ((nCntPolygonX * 2) - 1)] +
							m_aNor[((2 * CYLINDER_X) + ((nCntPolygonZ * (2 * CYLINDER_X)) - (2 * CYLINDER_X)) + 2) + ((nCntPolygonX * 2) - 1)]) / 6;
				}
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
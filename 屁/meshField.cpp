//=============================================================================
//
// ���b�V���t�B�[���h�̏��� [meshField.cpp]
// Author : ���R���
//
//=============================================================================
#include "meshField.h"
#include "main.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"

//=============================================================================
// ���b�V���t�B�[���h�̃R���X�g���N�^
//=============================================================================
CMeshField::CMeshField(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// �l���N���A
	m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;
	m_nNumVerTex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int nCntNor = 0; nCntNor < NUM_POLYGON; nCntNor++)
	{
		m_aNor[nCntNor] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	for (int nCntZ = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{
			m_aHeight[nCntZ][nCntX] = 0.0f;
		}
	}
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CMeshField::~CMeshField()
{
}

//=============================================================================
// ���b�V���t�B�[���h�̐�������
//=============================================================================
CMeshField *CMeshField::Create(D3DXVECTOR3 pos)
{
	CMeshField *pMeshField = NULL;

	if (pMeshField == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
		pMeshField = new CMeshField;

		if (pMeshField != NULL)
		{
			pMeshField->m_pos = pos;	// �ʒu�̐ݒ�
			pMeshField->Init();			// ����������
		}
	}

	return pMeshField;
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeshField::Init(void)
{
	// �l�̏�����
	m_pTexture = NULL;	// �e�N�X�`���ւ̃|�C���^
	m_pVtxBuff = NULL;	// ���_�o�b�t�@�ւ̃|�C���^
	m_pIdxBuff = NULL;
	m_nNumVerTex = 0;
	m_nNumIndex = 0;
	m_nNumPolygon = 0;
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bLand = false;
	for (int nCntZ = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{
			m_aHeight[nCntZ][nCntX] = 0.0f;
		}
	}

	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{// �f�o�C�X�̎擾
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, MESHFIELD_TEXTURE_NAME, &m_pTexture);

	// ���_���̍쐬
	int nVtxCounter = 0;
	int nIdxCounter = 0;

	int nCntVtxZ;
	int nCntVtxX;
	int nCntIdxZ;
	int nCntIdxX;

	// ���_��
	m_nNumVerTex = (POLYGON_X + 1) * (POLYGON_Z + 1);

	// �C���f�b�N�X��
	m_nNumIndex = (POLYGON_X + 1) * (POLYGON_Z + 1)
		+ (2 * (POLYGON_Z - 1))
		+ (POLYGON_X + 1) * (POLYGON_Z - 1);

	// �|���S����
	m_nNumPolygon = m_nNumIndex - 2;

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

	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntVtxZ = 0; nCntVtxZ < POLYGON_Z + 1; nCntVtxZ++)
	{
		for (nCntVtxX = 0; nCntVtxX < POLYGON_X + 1; nCntVtxX++)
		{
			// ���_���W�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].pos = D3DXVECTOR3((nCntVtxX * MESHFIELD_SIZE), 0.0f, (-nCntVtxZ * MESHFIELD_SIZE));
			// �@���̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			// ���_�J���[�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			// �e�N�X�`�����W�̐ݒ�
			pVtx[(nCntVtxZ + nCntVtxX) + nVtxCounter].tex = 
				D3DXVECTOR2(0.0f + (nCntVtxX), 0.0f + (nCntVtxZ));
		}
		nVtxCounter += POLYGON_X;
	}
	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	SetNor();	// �@���̐ݒ�

	WORD *pIdx;	// �C���f�b�N�X�f�[�^�ւ̃|�C���^

	// �C���f�b�N�X�o�b�t�@�����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntIdxZ = 0; nCntIdxZ < POLYGON_Z; nCntIdxZ++)
	{
		for (nCntIdxX = 0; nCntIdxX < POLYGON_X + 1; nCntIdxX++, nIdxCounter++)
		{
			pIdx[0] = nIdxCounter + POLYGON_X + 1;
			pIdx[1] = nIdxCounter;
			pIdx += 2;

			if (nCntIdxZ < POLYGON_Z - 1 && nCntIdxX == POLYGON_X)
			{
				pIdx[0] = nIdxCounter;
				pIdx[1] = nIdxCounter + (POLYGON_X + 1) + 1;
				pIdx += 2;
			}
		}
	}

	// �C���f�b�N�X�o�b�t�@���A�����b�N
	m_pIdxBuff->Unlock();

	LoadHeight();

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeshField::Uninit(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;

		// �������̊J��(���)
		delete m_pTexture;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;

		// �������̊J��(���)
		delete m_pVtxBuff;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;

		// �������̊J��(���)
		delete m_pIdxBuff;
	}

	// �I�u�W�F�N�g�̉��
	Release();
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeshField::Update(void)
{

}

//=============================================================================
// �`�揈��
//=============================================================================
void CMeshField::Draw(void)
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
void CMeshField::SetNor(void)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntPolygon = 0;
	int nCntNorPolygon = 0;

	for (int nCntZ = 0; nCntZ < POLYGON_Z; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X; nCntX++)
		{
			D3DXVECTOR3 *pPos0, *pPos1, *pPos2, *pPos3;
			D3DXVECTOR3 vec0, vec1, vec2;
			D3DXVECTOR3 nor;

			// ����̃|���S���̂Q�̃x�N�g������@�����Z�o
			pPos0 = &pVtx[nCntX + nCntZ + nCntPolygon].pos;
			pPos1 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (POLYGON_X + 1)].pos;
			pPos2 = &pVtx[(nCntX + nCntZ + nCntPolygon) + (POLYGON_X + 1) + 1].pos;
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

		nCntPolygon += POLYGON_X;
		nCntNorPolygon += (POLYGON_X * 2) - 2;
	}

	for (int nCntPolygonZ = 0; nCntPolygonZ < POLYGON_Z + 1; nCntPolygonZ++)
	{
		for (int nCntPolygonX = 0; nCntPolygonX < POLYGON_X + 1; nCntPolygonX++)
		{
			if (nCntPolygonZ == 0)
			{// ��[
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[0].nor = (m_aNor[0] + m_aNor[1]) / 2;
				}
				else if (nCntPolygonX == POLYGON_X)
				{// �E�[
					pVtx[POLYGON_X].nor = m_aNor[POLYGON_X + (POLYGON_X - 1)];
				}
				else
				{// ��[�̐^��
					pVtx[nCntPolygonX].nor =
						(m_aNor[(nCntPolygonX * 2) - 1] + m_aNor[((nCntPolygonX * 2) - 1) + 1] + m_aNor[((nCntPolygonX * 2) - 1) + 2]) / 3;
				}
			}
			else if (nCntPolygonZ == POLYGON_Z)
			{// ���[
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[POLYGON_Z * (POLYGON_X + 1)].nor = m_aNor[2 * (POLYGON_X * (POLYGON_Z - 1))];
				}
				else if (nCntPolygonX == POLYGON_X)
				{// �E�[
					pVtx[(POLYGON_X * POLYGON_Z) + (POLYGON_X + POLYGON_Z)].nor =
						(m_aNor[(2 * (POLYGON_X * (POLYGON_Z - 1))) + (2 * (POLYGON_X - 1))] +
							m_aNor[((2 * (POLYGON_X * (POLYGON_Z - 1))) + (2 * (POLYGON_X - 1))) + 1]) / 2;
				}
				else
				{// ���[�̐^��
					pVtx[(POLYGON_Z * (POLYGON_X + 1)) + nCntPolygonX].nor =
						(m_aNor[(POLYGON_Z - 1) * (POLYGON_X * 2) + (nCntPolygonX * 2) - 2] +
							m_aNor[((POLYGON_Z - 1) * (POLYGON_X * 2) + (nCntPolygonX * 2) - 2) + 1] +
							m_aNor[((POLYGON_Z - 1) * (POLYGON_X * 2) + (nCntPolygonX * 2) - 2) + 2]) / 3;
				}
			}
			else
			{// �^��
				if (nCntPolygonX == 0)
				{// ���[
					pVtx[(POLYGON_X + 1) * nCntPolygonZ].nor =
						(m_aNor[(nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X)] +
							m_aNor[(nCntPolygonZ * (2 * POLYGON_X))] +
							m_aNor[(nCntPolygonZ * (2 * POLYGON_X) + 1)]) / 3;
				}
				else if (nCntPolygonX == POLYGON_X)
				{// �E�[
					pVtx[((nCntPolygonZ + 1) * POLYGON_X) + nCntPolygonZ].nor =
						(m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntPolygonZ - 1)))]
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntPolygonZ - 1))) + 1]
							+ m_aNor[((POLYGON_X - 1) * 2 + ((POLYGON_X * 2)* (nCntPolygonZ - 1))) + ((POLYGON_X * 2) + 1)]) / 3;
				}
				else
				{
					pVtx[(POLYGON_X + 2) + (nCntPolygonX - 1) + ((nCntPolygonZ * (POLYGON_X + 1)) - (POLYGON_X + 1))].nor =
						(m_aNor[((nCntPolygonX - 1) * 2) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 1) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X)))] +
							m_aNor[((((nCntPolygonX - 1) * 2) + 2) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X)))] +
							m_aNor[((2 * POLYGON_X) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X))) + ((nCntPolygonX * 2) - 1)] +
							m_aNor[((2 * POLYGON_X) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X)) + 1) + ((nCntPolygonX * 2) - 1)] +
							m_aNor[((2 * POLYGON_X) + ((nCntPolygonZ * (2 * POLYGON_X)) - (2 * POLYGON_X)) + 2) + ((nCntPolygonX * 2) - 1)]) / 6;
				}
			}
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//=============================================================================
// �������擾
//=============================================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	D3DXVECTOR3 vec0, vec1;	// �|���S���̃x�N�g��
	D3DXVECTOR3 nor;		// �@��
	D3DXVECTOR3 aVtxpos[3];	// �|���S���̒��_���

	// ���b�V���t�B�[���h�Ƃ̈ʒu�̍���
	D3DXVECTOR3 posMtx = pos - m_pos;

	int nNumber;	// �ǂ����̎O�p�`�ɂ��邩�Ŏg��
	float fHeight;	// �v���C���[�̍�����ۊ�

	// ���ǂ̃u���b�N�ɂ���̂�
	int nMeshX = (int)((posMtx.x) / (MESHFIELD_WIDTH / POLYGON_X));
	int nMeshZ = (int)((posMtx.z) / (MESHFIELD_DEPTH / POLYGON_Z) * -1);

	float fMeshX = posMtx.x / (MESHFIELD_WIDTH / POLYGON_X + 1);
	float fMeshZ = posMtx.z / (MESHFIELD_DEPTH / POLYGON_Z + 1) * -1;

	// ������Ă��钸�_���o��
	int nMeshLU = nMeshX + nMeshZ * (POLYGON_X + 1);				// ����
	int nMeshRU = (nMeshX + 1) + nMeshZ * (POLYGON_X + 1);			// �E��
	int nMeshLD = nMeshX + (nMeshZ + 1) * (POLYGON_X + 1);			// ����
	int nMeshRD = (nMeshX + 1) + (nMeshZ + 1) * (POLYGON_X + 1);	// �E��

	// ���_����ݒ�
	VERTEX_3D * pVtx;					// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �O�p�`�̃x�N�g�����o��
	vec0 = pVtx[nMeshLU].pos - pVtx[nMeshRD].pos;	// �E�̕ӂ̃x�N�g��
	vec1 = posMtx - pVtx[nMeshRD].pos;				// �����̈ʒu�ƉE���̒��_�̃x�N�g

	// ���_�����Ȃ���
	if ((vec0.x * vec1.z) - (vec0.z * vec1.x) <= 0)
	{// �E�̃|���S���ɂ���ꍇ
#ifdef _DEBUG
		CDebugProc::Print("c", "migi");
#endif
		vec0 = posMtx - pVtx[nMeshLU].pos;

		aVtxpos[0] = pVtx[nMeshRU].pos;
		aVtxpos[1] = pVtx[nMeshRD].pos;
		aVtxpos[2] = pVtx[nMeshLU].pos;

		nNumber = 3;
	}
	else if ((vec0.x * vec1.z) - (vec0.z * vec1.x) >= 0)
	{// ���̃|���S���ɂ���ꍇ
#ifdef _DEBUG
		CDebugProc::Print("c", "hidari");
#endif
		vec0 = posMtx - pVtx[nMeshRD].pos;

		aVtxpos[0] = pVtx[nMeshLD].pos;
		aVtxpos[1] = pVtx[nMeshLU].pos;
		aVtxpos[2] = pVtx[nMeshRD].pos;

		nNumber = 0;
	}

	fHeight = aVtxpos[0].y;

	aVtxpos[2].y -= aVtxpos[0].y;
	aVtxpos[1].y -= aVtxpos[0].y;
	aVtxpos[0].y -= aVtxpos[0].y;

	// ����Ȃ��������_�Ńx�N�g�����o��
	vec0 = aVtxpos[1] - aVtxpos[0];
	vec1 = aVtxpos[2] - aVtxpos[0];

	// �O�ς��g���Ė@�������߂�
	D3DXVec3Cross(&nor, &vec0, &vec1);

	// �@���𐳋K��
	D3DXVec3Normalize(&nor, &nor);

	// �v���C���[�Ƃ̃x�N�g��
	vec0 = posMtx - aVtxpos[0];

	// ���ς̎�
	vec0.y = (-(vec0.x * nor.x) - (vec0.z * nor.z)) / nor.y;

	// �v���C���[�̈ʒu�����ɖ߂�
	posMtx.y = vec0.y + fHeight + m_pos.y;

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();

	if (fMeshX >= 0 && fMeshX < POLYGON_X && nMeshZ >= 0 && nMeshZ < POLYGON_Z)
	{
		m_bLand = true;

		if (pos.y > posMtx.y)
		{
			m_bLand = false;
		}
	}
	else
	{
		m_bLand = false;
	}


	return posMtx.y;
}

//=============================================================================
// ����Ă��邩���擾
//=============================================================================
bool CMeshField::GetLand()
{
	return m_bLand;
}

//=============================================================================
// ���������[�h
//=============================================================================
void CMeshField::LoadHeight(void)
{
	// ���_���̐ݒ�
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

						// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	FILE *pFile = NULL;

	pFile = fopen(SOIL_FILENAME, "rb");

	if (pFile != NULL)
	{
		fread(&m_aHeight[0][0], sizeof(float), POLYGON_Z * POLYGON_X, pFile);	// �f�[�^�̃A�h���X,�f�[�^�̃T�C�Y,�f�[�^�̌�,�t�@�C���|�C���^

		fclose(pFile);
	}
	else
	{
		printf("number.txt���J���܂���ł����B\n");
	}

	for (int nCntZ = 0; nCntZ < POLYGON_Z + 1; nCntZ++)
	{
		for (int nCntX = 0; nCntX < POLYGON_X + 1; nCntX++)
		{// pos����
			pVtx->pos.y = m_aHeight[nCntZ][nCntX];

			pVtx++;
		}
	}

	// ���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}
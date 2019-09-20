//=============================================================================
//
// ���f������ [model.h]
// Author : ���R���
//
//=============================================================================
#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CModel
{
public:
	CModel();																// �R���X�g���N�^
	~CModel();																// �f�X�g���N�^

	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);				// �I�u�W�F�N�g�̐���

	HRESULT Init(void);														// ���f������������
	void Uninit(void);														// ���f���I������
	void Update(void);														// ���f���X�V����
	void Draw(void);														// ���f���`�揈��

	void SetParent(CModel *pModel);
	D3DXMATRIX GetMtxWorld(void);

	void SetRot(D3DXVECTOR3 rot);
	void SetPos(D3DXVECTOR3 pos);

	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetPos(void);

	void BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);	// ���f�������蓖�Ă�

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// ���_�o�b�t�@�ւ̃|�C���^
	LPD3DXMESH				m_pMesh;										// ���b�V�����i���_���j�ւ̃|�C���^
	LPD3DXBUFFER			m_pBuffMat;										// �}�e���A�����ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;										// ���[���h�}�g���b�N�X
	DWORD					m_nNumMat;										// �}�e���A�����̐�

	D3DXVECTOR3				m_pos;											// ���f���̈ʒu
	D3DXVECTOR3				m_rot;											// ������x�N�g��

	CModel *m_pParent;														// �e���f���ւ̃|�C���^
};

#endif
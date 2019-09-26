//=============================================================================
//
// �n�ʃ|���S������ [field.h]
// Author : ���R���
//
//=============================================================================
#ifndef _FIELD_H_
#define _FIELD_H_

#include "main.h"
#include "polygon.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NUM_VTX						(4)								// ���_�̐�
//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CFeild : public CPolygon
{
public:
	CFeild();											// �R���X�g���N�^
	~CFeild();										// �f�X�g���N�^

	HRESULT Init(void);							// 3D�I�u�W�F�N�g����������
	void Uninit(void);							// 3D�I�u�W�F�N�g�I������
	void Update(void);							// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);							// 3D�I�u�W�F�N�g�`�揈��

	static CFeild *Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV);			// �I�u�W�F�N�g�̐���

private:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;					// ���[���h�}�g���b�N�X
};

#endif
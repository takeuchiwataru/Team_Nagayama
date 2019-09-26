//=============================================================================
//
// 3D�|���S������ [scene3D.h]
// Author : ���R���
//
//=============================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define WATER_NAME		"data/TEXTURE/water.jpeg"			// �`���[�g���A�����S�̃e�N�X�`����
#define GROUND_SIZE					(3000.0f)							// �n�ʂ̑傫��
#define NUM_VTX						(4)								// ���_�̐�
//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CScene3D : public CScene
{
public:
	CScene3D(int nPriority = SCENE3D_PRIORITY, OBJTYPE objType = OBJTYPE_SCENE3D);											// �R���X�g���N�^
	~CScene3D();										// �f�X�g���N�^

	HRESULT Init(void);							// 3D�I�u�W�F�N�g����������
	void Uninit(void);							// 3D�I�u�W�F�N�g�I������
	void Update(void);							// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);							// 3D�I�u�W�F�N�g�`�揈��

	D3DXVECTOR3 GetNor(int nIdx);				// �@�����擾

	bool ColLand(D3DXVECTOR3 *pos, D3DXVECTOR3 radius);

	float GetHeight(D3DXVECTOR3 pos);			// �����̎擾

	static CScene3D *Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV);			// �I�u�W�F�N�g�̐���

private:
	LPDIRECT3DTEXTURE9		m_pTexture;					// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX				m_mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3				m_aNor[NUM_VTX];					// �@��
	D3DXVECTOR3				m_aVec[NUM_VTX];					// �x�N�g��
	D3DXVECTOR3				m_pos;						// �|���S���̈ʒu
	D3DXVECTOR3				m_aPos[NUM_VTX];					// ���_�̈ʒu
	D3DXVECTOR3				m_rot;						// ������x�N�g��
	float					m_fDepth;					// �傫��
	float					m_fWifth;					// �傫��
	float					m_fTextureU;					// �e�N�X�`��������
	float					m_fTextureV;					// �e�N�X�`��������
	float m_fBgSpeed;										// �e�N�X�`���̓�������
	int m_nCounterAnim;
};

#endif
//=============================================================================
//
// �|���S������ [polygon.h]
// Author : ���R���
//
//=============================================================================
#ifndef _POLYGONHOLE_H_
#define _POLYGONHOLE_H_

#include "main.h"
#include "scene.h"

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
class CPolygon : public CScene
{
public:
	CPolygon(int nPriority = 2, OBJTYPE objType = OBJTYPE_POLYGON);											// �R���X�g���N�^
	~CPolygon();										// �f�X�g���N�^

	HRESULT Init(void);							// 3D�I�u�W�F�N�g����������
	void Uninit(void);							// 3D�I�u�W�F�N�g�I������
	void Update(void);							// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);							// 3D�I�u�W�F�N�g�`�揈��

	D3DXVECTOR3 GetNor(int nIdx);				// �@�����擾

	static CPolygon *Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV);			// �I�u�W�F�N�g�̐���

	void BindTexture(LPDIRECT3DTEXTURE9	Texture);	// ���L�e�N�X�`�������蓖�Ă�
	void SetCol(D3DXCOLOR col);												// �F�̐ݒ�
	void SetPos(D3DXVECTOR3 pos);												// �ʒu�̐ݒ�
	D3DXVECTOR3 GetPos(void);												// �ʒu�̎擾
	void SetRot(D3DXVECTOR3 rot);												// �ʒu�̐ݒ�
	void SetDepth(float	fDepth);												// �傫���̐ݒ�
	void SetWidth(float	fWifth);												// �傫���̐ݒ�
	void SetTextureU(float	fTextureU);												// �e�N�X�`��������
	void SetTextureV(float	fTextureV);												// �e�N�X�`��������

	bool ColLand(D3DXVECTOR3 *pos, D3DXVECTOR3 radius);

	float GetHeight(D3DXVECTOR3 pos);			// �����̎擾

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

};
#endif
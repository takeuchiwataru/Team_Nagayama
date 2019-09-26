//=============================================================================
//
// �S���ڍ����� [fullMeguro.h]
// Author : ���R���
//
//=============================================================================
#ifndef _FULLMEGURO_H_
#define _FULLMEGURO_H_

#include "main.h"
#include "sceneX.h"

//=============================================================================
// �O���錾
//=============================================================================
class CShadow;

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//========================================
// �N���X�̒�`
//========================================
//=====================
// �u���b�N�N���X
//=====================
class CFullMeguro : public CSceneX
{
public:
	CFullMeguro();								// �R���X�g���N�^
	~CFullMeguro();								// �f�X�g���N�^

	HRESULT Init(void);						// �R�C������������
	void Uninit(void);						// �R�C���I������
	void Update(void);						// �R�C���X�V����
	void Draw(void);						// �R�C���`�揈��

	static CFullMeguro *Create(D3DXVECTOR3 pos);	// �I�u�W�F�N�g�̐���

	D3DXVECTOR3 GetPos(void);						// �ʒu�̎擾
	void SetPos(D3DXVECTOR3 pos);					// �ʒu�̐ݒ�
	static int GetNumCoin(void);						// �R�C���̐��̎擾
	static void SetNumCoin(int nNumCoin);				// �R�C���̐��̐ݒ�

	bool CFullMeguro::Collision(D3DXVECTOR3 *pos, float fRadius);

private:
	static int				m_nNumCoin;			// �R�C���̐�
	D3DXVECTOR3				m_pos;				// �ʒu
	D3DXVECTOR3				m_move;				// �ړ���
	D3DXVECTOR3				m_rot;				// ����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// �u���b�N�̍ŏ��l�A�ő�l

	D3DXMATRIX				m_mtxWorld;		// ���[���h�}�g���b�N�X
};

#endif
//=============================================================================
//
// �^�C�g���̏��� [title.h]
// Author : ���R���
//
//=============================================================================
#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CBlock;
//class CRenderer;

//=============================================================================
// �N���X�̒�`
//=============================================================================
//==================================================================
// �^�C�g���N���X
//==================================================================
class CTitle
{
public:
	CTitle();						// �R���X�g���N�^
	~CTitle();						// �f�X�g���N�^

	static CTitle *Create();		// �^�C�g���𐶐�

	HRESULT Init(void);				// �^�C�g������������
	void Uninit(void);				// �^�C�g���I������
	void Update(void);				// �^�C�g���X�V����
	void Draw(void);				// �^�C�g���`�揈��

	void LoadMap(void);				// �w�i�I�u�W�F�N�g�̓ǂݍ���

	D3DXVECTOR3 GetBlockPos(int nCntBlock);

private:
	static CBlock *m_pBlock[225];
	D3DXVECTOR3 m_BlockPpos[220];
	int m_nBlockTimer;							// �u���b�N�̐ݒu�̎��Ԃ�x�点��^�C�}�[
	int m_nCntBlock;							// ���Ƃ��u���b�N�̃J�E���g
	int m_nBlock;							// �����u���b�N�̃J�E���g
	int m_nCntFrame;							// �t���[���̃J�E���g
	int m_nCntTimer;							// �J�ڂɎg���^�C�}�[
												/*static CRenderer *m_pRenderer;*/
	bool m_bSetBlock;							// �u���b�N��ݒu���邩�ǂ���
};

#endif
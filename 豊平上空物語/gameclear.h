//=============================================================================
//
// �Q�[���N���A�̏��� [gameClear.h]
// Author : ���R���
//
//=============================================================================
#ifndef _GAMECLEAR_H_
#define _GAMECLEAR_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_BLOCK (450)
#define NUM_BLOCK_X (59)
#define NUM_BLOCK_Y (7)

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CBlock;
class CScore;

//=============================================================================
// �N���X�̒�`
//=============================================================================
//==================================================================
// �^�C�g���N���X
//==================================================================
class CGameClear
{
public:
	CGameClear();						// �R���X�g���N�^
	~CGameClear();						// �f�X�g���N�^

	static CGameClear *Create();		// �^�C�g���𐶐�

	HRESULT Init(void);				// �^�C�g������������
	void Uninit(void);				// �^�C�g���I������
	void Update(void);				// �^�C�g���X�V����
	void Draw(void);				// �^�C�g���`�揈��
	void Block(void);				// �u���b�N�ݒu

	void LoadCharFall(void);				// �w�i�I�u�W�F�N�g�̓ǂݍ���

private:
	static CScore *m_pScore;
	int m_nCntTimer;
	int m_nNumModel;		// �ꕶ���Ɏg���Ă��郂�f���̐�
	int m_nBlockTimer;							// �u���b�N�̐ݒu�̎��Ԃ�x�点��^�C�}�[
	int m_nCntBlock;							// ���Ƃ��u���b�N�̃J�E���g
	bool m_bSetBlock;
	static CBlock *m_pBlock[MAX_BLOCK];
	D3DXVECTOR3 m_BlockPpos[1000];
};

#endif
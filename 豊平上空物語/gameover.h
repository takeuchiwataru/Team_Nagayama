//=============================================================================
//
// �Q�[���I�[�o�[�̏��� [gameover.h]
// Author : ���R���
//
//=============================================================================
#ifndef _GAMEOVER_H_
#define _GAMEOVER_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"
#include "gameclear.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define NUM_X (53)
#define NUM_Y (7)

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CScore;
class CBlock;

//=============================================================================
// �N���X�̒�`
//=============================================================================
//==================================================================
// �Q�[���I�[�o�[�N���X
//==================================================================
class CGameOver
{
public:
	CGameOver();						// �R���X�g���N�^
	~CGameOver();						// �f�X�g���N�^

	static CGameOver *Create();		// �^�C�g���𐶐�

	HRESULT Init(void);				// �^�C�g������������
	void Uninit(void);				// �^�C�g���I������
	void Update(void);				// �^�C�g���X�V����
	void Draw(void);				// �^�C�g���`�揈��

	void LoadCharFall(void);				// �w�i�I�u�W�F�N�g�̓ǂݍ���
	void Block(void);				// �u���b�N

private:
	static CBlock *m_pBlock[MAX_BLOCK];
	static CScore *m_pScore;
	int m_nCntTimer;
	int m_nNumModel;		// �ꕶ���Ɏg���Ă��郂�f���̐�
	int m_nBlockTimer;							// �u���b�N�̐ݒu�̎��Ԃ�x�点��^�C�}�[
	int m_nCntBlock;							// ���Ƃ��u���b�N�̃J�E���g
	int m_nScore;
	int m_nCntScore;
	bool m_bSetBlock;
	D3DXVECTOR3 m_BlockPpos[1000];
};

#endif
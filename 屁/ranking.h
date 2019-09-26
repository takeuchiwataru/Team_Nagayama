//=============================================================================
//
// �����L���O�̏��� [ranking.h]
// Author : ���R���
//
//=============================================================================
#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
#include "scene.h"
#include "scene2D.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define MAX_RANKING	(5)	// �����L���O�ŕ\������X�R�A�̐�
#define CHAR_RANKING_FILE	"data\\TEXT\\modelRanking.txt"	// �ݒu�������f���������o���e�L�X�g
#define CHAR_RANKINGNUM_FILE	"data\\TEXT\\ranking.txt"	// �ݒu�������f���������o���e�L�X�g

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;
class CScore;
//class CRenderer;

//=============================================================================
// �N���X�̒�`
//=============================================================================
//==================================================================
// �����L���O�N���X
//==================================================================
class CRanking
{
public:
	CRanking();						// �R���X�g���N�^
	~CRanking();						// �f�X�g���N�^

	static CRanking *Create();		// �����L���O�𐶐�

	HRESULT Init(void);				// �����L���O����������
	void Uninit(void);				// �����L���O�I������
	void Update(void);				// �����L���O�X�V����
	void Draw(void);				// �����L���O�`�揈��

	void LoadCharFall(void);							// �����Ɏg���Ă��郂�f���̈ʒu����ǂݍ���
	void LoadCharNumFall(void);							// �����Ɏg���Ă��郂�f���̈ʒu����ǂݍ���

private:
	static CScore *m_apScore[MAX_RANKING];
	int m_nCntColor;
	int m_nCntTimer;
	D3DXCOLOR m_col;

	int m_nNumModel;		// �ꕶ���Ɏg���Ă��郂�f���̐�
	int m_nNumRankModel;		// �ꕶ���Ɏg���Ă��郂�f���̐�
	int m_nBlockTimer;							// �u���b�N�̐ݒu�̎��Ԃ�x�点��^�C�}�[
	int m_nBlockNumTimer;							// �u���b�N�̐ݒu�̎��Ԃ�x�点��^�C�}�[
	int m_nCntBlock;							// ���Ƃ��u���b�N�̃J�E���g
	int m_nCntNumBlock;							// ���Ƃ��u���b�N�̃J�E���g
	bool m_bSetBlock;
	bool m_bSetNumBlock;
	D3DXVECTOR3 m_BlockPos[1000];
	D3DXVECTOR3 m_BlockNumPos[1000];
	/*static CRenderer *m_pRenderer;*/
};

#endif
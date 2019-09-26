//=============================================================================
//
// �X�R�A���� [score.h]
// Author : ���R���
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SCORE	(6)	// �e�N�X�`���̐�

//=============================================================================
// �O���錾
//=============================================================================
class CNumber;

//========================================
// �N���X�̒�`
//========================================
//=====================
// �X�R�A�N���X
//=====================
class CScore : public CScene
{
public:
	CScore(int nPriority = 5, OBJTYPE objType = OBJTYPE_SCORE);	// �R���X�g���N�^
	~CScore();													// �f�X�g���N�^

	static CScore *Create(D3DXVECTOR3 pos, float fSize, float fWidth);

	HRESULT Init(void);							// �X�R�A�̏���������
	void Uninit(void);							// �X�R�A�̏I������
	void Update(void);							// �X�R�A�̍X�V����
	void Draw(void);							// �X�R�A�̕`�揈��

	void SetScore(int nScore);					// �X�R�A�̐ݒ�
	int GetScore(void);							// �X�R�A�̎擾
	void AddScore(int nValue);					// �X�R�A���Z
	void SetColor(D3DXCOLOR color);				// �F�̐ݒ�

private:
	CNumber *m_apNumber[MAX_SCORE];
	D3DXVECTOR3 m_pos;
	int m_nScore;
	float m_fSize;
	float m_fWidth;
};

#endif
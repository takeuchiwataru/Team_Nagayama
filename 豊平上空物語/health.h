//=============================================================================
//
// �̗� [health.h]
// Author : ���R���
//
//=============================================================================
#ifndef _HEALTH_H_
#define _HEALTH_H_

#include "main.h"
#include "scene2D.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=========================
// �X�R�A���S�N���X
//=========================
class CHealth : public CScene2D
{
public:
	CHealth();															// �R���X�g���N�^
	~CHealth();															// �f�X�g���N�^

	static CHealth *Create(D3DXVECTOR3 pos, float fWidth, float fHeight);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);				// �̗͏���������
	void Uninit(void);				// �̗͏I������
	void Update(void);				// �̗͍X�V����
	void Draw(void);				// �̗͕`�揈��
	void CutHealth(int nHealth);	// �̗͌�������
	int GetHealth(void) { return m_nHealth; }	// �̗͎擾

private:
	int m_nHealth;
};

#endif
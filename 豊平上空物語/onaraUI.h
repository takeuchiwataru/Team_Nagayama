//=============================================================================
//
// �����L���O���S�̏��� [onaraUI.h]
// Author : �|���j
//
//=============================================================================
#ifndef _ONARAUI_H_
#define _ONARAUI_H_

#include "main.h"
#include "logo.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************

//=========================
// �^�C�g�����S�N���X
//=========================
class COnaraUI : public CLogo
{
public:

	COnaraUI();															// �R���X�g���N�^
	~COnaraUI();															// �f�X�g���N�^

	static COnaraUI *Create(D3DXVECTOR3 pos, float fWidth, float fHeight, int nType);	// �I�u�W�F�N�g�̐���

	HRESULT Init(void);															// �^�C�g�����S����������
	void Uninit(void);															// �^�C�g�����S�I������
	void Update(void);															// �^�C�g�����S�X�V����
	void Draw(void);															// �^�C�g�����S�`�揈��

private:
};

#endif
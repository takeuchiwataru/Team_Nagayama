//=============================================================================
//
// �|�[�Y�̏��� [pause.h]
// Author : ���R���
//
//=============================================================================
#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"
#include "scene.h"

//=============================================================================
// �O���錾
//=============================================================================
class CScene2D;

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define PAUSE_NAME				"data/TEXTURE/PAUSE/pause100.png"		// �|�[�Y�̃e�N�X�`����
#define PAUSET_TEXTURE_NAME0	"data/TEXTURE/PAUSE/pause200.png"	// �|�[�Y�Z���N�g0�̃e�N�X�`����
#define PAUSET_TEXTURE_NAME1	"data/TEXTURE/PAUSE/pause201.png"	// �|�[�Y�Z���N�g1�̃e�N�X�`����
#define PAUSET_TEXTURE_NAME2	"data/TEXTURE/PAUSE/pause202.png"	// �|�[�Y�Z���N�g2�̃e�N�X�`����
#define MAX_PAUSE_TEXTURE		(4)								// �|�[�Y�Z���N�g�̃e�N�X�`����
#define MAX_PAUSE				(3)								// �|�[�Y�Z���N�g�̐�

//=========================
// �|�[�Y�N���X
//=========================
class CPause : public CScene
{
public:
	typedef enum
	{
		MODE_NONE = 0,	// �ʏ���
		MODE_CONTINUE,	// �R���e�B�j���[
		MODE_RETRY,		// ���g���C
		MODE_QUIT,		// �N�C�b�g
		MODE_MAX
	} MODE;

	typedef enum
	{
		SELECT_NONE = 0,	// �I�΂�Ă��Ȃ����
		SELECT_SELECT,		// �I�΂�Ă�����
		SELECT_MAX
	} SELECT;

	CPause(int nPriority = 7, OBJTYPE objType = OBJTYPE_PAUSE);									// �R���X�g���N�^
	~CPause();													// �f�X�g���N�^

	static HRESULT Load(void);									// �e�N�X�`���ǂݍ���
	static void Unload(void);									// �e�N�X�`�����
	
	static CPause *Create(void);								// �|�[�Y�𐶐�

	HRESULT Init(void);	// �|�[�Y����������
	void Uninit(void);											// �|�[�Y�I������
	void Update(void);											// �|�[�Y�X�V����
	void Draw(void);											// �|�[�Y�`�揈��
	static	MODE GetMode(void);									// �|�[�Y���擾
	int GetSelect(void);

private:
	static LPDIRECT3DTEXTURE9 m_apTexture[MAX_PAUSE_TEXTURE];
	CScene2D *m_apScene2D[MAX_PAUSE_TEXTURE];
	SELECT m_aSelect[MAX_PAUSE];
	D3DXCOLOR m_aCol[MAX_PAUSE];
	static MODE m_Mode;
	int	m_nSelect;
};
#endif
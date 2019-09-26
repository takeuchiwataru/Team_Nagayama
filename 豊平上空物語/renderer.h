//=============================================================================
//
// �����_�����O���� [renderer.h]
// Author : ���R���
//
//=============================================================================
#ifndef _RENDERER_H_
#define _RENDERER_H_

#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================
class CPause;

//========================================
// �N���X�̒�`
//========================================
//=====================
// �����_�����O�N���X
//=====================
class CRenderer
{
public:
	CRenderer();	// �R���X�g���N�^
	~CRenderer();	// �f�X�g���N�^
	
	HRESULT Init(HWND hWnd, bool bWindow);	// �����_���[�̏���������
	void Uninit(void);						// �����_���[�̏I������
	void Update(void);						// �����_���[�̍X�V����
	void Draw(void);						// �����_���[�̕`�揈��

	LPDIRECT3DDEVICE9 GetDevice(void); /*{ return m_pD3DDevice; }*/

private:
//#ifdef _DEBUG
//	void DrawFPS(void);
//#endif

	LPDIRECT3D9				m_pD3D;			// Direct3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9		m_pD3DDevice;	// Device�I�u�W�F�N�g(�`��ɕK�v)
	static CPause *m_pPause;
	bool m_bPause;
//#ifdef _DEBUG
//	LPD3DXFONT				m_pFont;			// �t�H���g�ւ̃|�C���^
//#endif
};

#endif
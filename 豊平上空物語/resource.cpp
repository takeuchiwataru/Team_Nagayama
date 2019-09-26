//=============================================================================
//
// �f�ފǗ����� [resource.cpp]
// Author : ���R���
//
//=============================================================================
#include "resource.h"
#include "main.h"
#include "renderer.h"
#include "input.h"
#include "debugProc.h"
#include "manager.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 *CResource::m_pTexture = NULL;
LPD3DXMESH *CResource::m_pMesh = NULL;			// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER *CResource::m_pBuffMat = NULL;	// �}�e���A�����ւ̃|�C���^
DWORD *CResource::m_nNumMat = 0;				// �}�e���A�����̐�

// �w�b�_�̏��ԂƓ����ɂ���
const char *CResource::m_apModelFilename[] =
{// ���f��
	"data\\MODEL\\woodBox.x",			// �v���C���[���o���u���b�N
	"data\\MODEL\\woodBox001.x",		// �؃u���b�N�̃��f����
	"data\\MODEL\\ironBox.x",			// �S�u���b�N�̃��f����
	"data\\MODEL\\woodDebris.x",		// �u���b�N�̔j�Ђ̃��f����
	"data\\MODEL\\coin.x",				// �R�C���̃��f����
	"data\\MODEL\\gem.x",				// ��΂̃��f����
	"data\\MODEL\\OBJECT\\pebble.x",	// ���΂̃��f����
	"data\\MODEL\\goal.x",				// �S�[���̃��f����
	"data\\MODEL\\OBJECT\\obstacle.x",	// ��Q���̃��f����
	"data\\MODEL\\OBJECT\\bullet.x",	// �e�̃��f����
	"data\\MODEL\\fullMegro.x",			// �S���ڍ��̃��f����
};

// �w�b�_�̏��ԂƓ����ɂ���
const char *CResource::m_apTexFilename[] =
{// �e�N�X�`��
	"data/TEXTURE/UI/PressAnyButton.png",	// �v���X�G�j�[�{�^�����S�̃e�N�X�`����
	"data/TEXTURE/UI/enter.png"	,			// �G���^�[�{�^�����S�̃e�N�X�`����
	"data\\TEXTURE\\soil001.jpg",			// �n�ʂ̃e�N�X�`����
	"data/TEXTURE/effect000.jpg",			// �G�t�F�N�g�̃e�N�X�`����
	"data/TEXTURE/cloud.png",				// ���G�t�F�N�g�̃e�N�X�`����
	"data/TEXTURE/logoBack001.png",			// �w�i���S�̃e�N�X�`����
	"data/TEXTURE/UI/SCORE.png",			// �X�R�A���S�̃e�N�X�`����
	"data/TEXTURE/UI/BLOCK.png",			// �u���b�N���S�̃e�N�X�`����
	"data/TEXTURE/UI/LIFE.png",				// �c�@���S�̃e�N�X�`����
	"data/TEXTURE/UI/blockCross.png",		// �u���b�N�̌����S�̃e�N�X�`����
	"data/TEXTURE/UI/playerCross.png",		// �v���C���[�̎c�@���S�̃e�N�X�`����
	"data\\TEXTURE\\TUTORIAL\\move.png",	// �ړ����@�̃e�N�X�`����
	"data\\TEXTURE\\TUTORIAL\\jump.png",	// �W�����v���@�̃e�N�X�`����
	"data\\TEXTURE\\TUTORIAL\\set.png",		// �ݒu���@�̃e�N�X�`����
	"data\\TEXTURE\\TUTORIAL\\destroy.png",	// �j����@�̃e�N�X�`����
	"data\\TEXTURE\\TUTORIAL\\end.png",		// �I���̃e�N�X�`����
	"data/TEXTURE/number_02.png",			// �X�R�A�̃e�N�X�`����
	"data/TEXTURE/bullet000.png",				// �e�̃e�N�X�`����
	"data\\TEXTURE\\life000.png",			// �̗͂̃��f����
	"data\\TEXTURE\\TITLE\\title001.png",	// �^�C�g�����S��
	"data\\TEXTURE\\tutorial.png",		// �`���[�g���A�����S��
	"data\\TEXTURE\\bullet000.png",	// ���Ȃ�c�@��
	"data\\TEXTURE\\Animation_���Ȃ�.png",		// ���̃A�j���[�V����
	"data\\TEXTURE\\RESULT\\gameclear.png",		// ���̃A�j���[�V����
	"data\\TEXTURE\\RESULT\\gameover.png",		// ���̃A�j���[�V����
	"data\\TEXTURE\\rankinglogo.png",			// �����L���O���S
	"data\\TEXTURE\\rankingrank.png",	// �����L���O�����N
	"data\\TEXTURE\\onara_counter.png",
};

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CResource::CResource()
{
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CResource::~CResource()
{
}

//=============================================================================
// �e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CResource::LoadModel(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	if (m_pMesh != NULL)
	{
		// ���������������
		delete[] m_pMesh;
		m_pMesh = NULL;
	}

	if (m_pBuffMat != NULL)
	{
		// ���������������
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		// ���������������
		delete[] m_nNumMat;
		m_nNumMat = NULL;
	}

	int nModelData = (sizeof m_apModelFilename);
	int nModelSize = (sizeof m_apModelFilename[0]);
	int nNumModel = nModelData / nModelSize;

	// ���I�Ɋm��
	m_pMesh = new LPD3DXMESH[nNumModel];
	m_pBuffMat = new LPD3DXBUFFER[nNumModel];
	m_nNumMat = new DWORD[nNumModel];

	for (int nCntModel = 0; nCntModel < nNumModel; nCntModel++)
	{
		D3DXLoadMeshFromX(m_apModelFilename[nCntModel],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_pBuffMat[nCntModel],
			NULL,
			&m_nNumMat[nCntModel],
			&m_pMesh[nCntModel]);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���������
//=============================================================================
void CResource::UnloadModel(void)
{
	if (m_pBuffMat != NULL)
	{
		// ���������������
		delete[] m_pBuffMat;
		m_pBuffMat = NULL;
	}

	if (m_nNumMat != NULL)
	{
		// ���������������
		delete[] m_nNumMat;
		m_nNumMat = NULL;
	}

	if (m_pMesh != NULL)
	{
		// ���������������
		delete[] m_pMesh;
		m_pMesh = NULL;
	}
}

//=============================================================================
// �e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CResource::LoadTex(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	if (m_pTexture != NULL)
	{
		// ���������������
		delete[] m_pTexture;
		m_pTexture = NULL;
	}

	int nTexData = (sizeof m_apTexFilename);
	int nTexSize = (sizeof m_apTexFilename[0]);
	int nNumTex = nTexData / nTexSize;

	// �e�N�X�`���̐��𓮓I�Ɋm��
	m_pTexture = new LPDIRECT3DTEXTURE9[nNumTex];

	for (int nCntTex = 0; nCntTex < nNumTex; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice, m_apTexFilename[nCntTex], &m_pTexture[nCntTex]);
	}

	return S_OK;
}

//=============================================================================
// �e�N�X�`���������
//=============================================================================
void CResource::UnloadTex(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		// ���������������
		delete[] m_pTexture;
		m_pTexture = NULL;
	}
}

//=============================================================================
// �e�N�X�`���擾
//=============================================================================
LPDIRECT3DTEXTURE9 CResource::GetTexture(int nIdx)
{
	return m_pTexture[nIdx];
}

//=============================================================================
// ���b�V���擾
//=============================================================================
LPD3DXMESH CResource::GetMesh(int nIdx)
{
	return m_pMesh[nIdx];
}

//=============================================================================
// �}�e���A�����擾
//=============================================================================
LPD3DXBUFFER CResource::GetBuffMat(int nIdx)
{
	return m_pBuffMat[nIdx];
}

//=============================================================================
// �}�e���A�����̐��擾
//=============================================================================
DWORD CResource::GetNumMat(int nIdx)
{
	return m_nNumMat[nIdx];
}
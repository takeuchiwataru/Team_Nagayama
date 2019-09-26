//=============================================================================
//
// プレイヤー処理 [player.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"
#include "scene.h"
#include "model.h"

//=============================================================================
// 前方宣言
//=============================================================================
class CShadow;

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_PLAYER			(10)									//プレイヤーのパーツの数
#define PARTICLE_ROT		((rand() % 628) / 100.0f)				//全方向
#define PLAYER_HEIGHT		(50.0f)										// プレイヤーの身長
#define	MOTION_FILENAME		"data\\TEXT\\motion.txt"				// ツールのテキスト
#define	NUMMODEL			"NUM_MODEL = "							
#define	MODEL_FILE			"MODEL_FILENAME = "						
#define	CHARACTER_SET		"CHARACTERSET"							
#define	END_CHARACTER_SET	"END_CHARACTERSET"						
#define	NUM_PARTS			"NUM_PARTS = "							
#define	PARTSSET			"PARTSSET"								
#define	END_PARTSSET		"END_PARTSSET"							
#define	INDEX				"INDEX = "								
#define	PARENT				"PARENT = "								
#define	POS					"POS = "								
#define	ROT					"ROT = "								
#define	MOTIONSET			"MOTIONSET"								
#define	END_MOTIONSET		"END_MOTIONSET"							
#define	LOOP				"LOOP = "								
#define	NUM_KEY				"NUM_KEY = "							
#define	KEYSET				"KEYSET"								
#define	END_KEYSET			"END_KEYSET"							
#define	FRAME				"FRAME = "								
#define PLAYER_HEAD			"data\\MODEL\\gentleman\\head000.x"		// 頭のモデル名
#define PLAYER_BODY			"data\\MODEL\\gentleman\\body001.x"		// 体のモデル名
#define PLAYER_R_ARM		"data\\MODEL\\gentleman\\rightarm.x"	// 右腕のモデル名
#define PLAYER_R_HAND		"data\\MODEL\\gentleman\\righthand.x"	// 右手のモデル名
#define PLAYER_L_ARM		"data\\MODEL\\gentleman\\leftarm.x"		// 左腕のモデル名
#define PLAYER_L_HAND		"data\\MODEL\\gentleman\\lefthand.x"	// 左手のモデル名
#define PLAYER_R_LEG		"data\\MODEL\\gentleman\\rightleg.x"	// 右腿のモデル名
#define PLAYER_R_FOOT		"data\\MODEL\\gentleman\\rightfoot.x"	// 右足のモデル名
#define PLAYER_L_LEG		"data\\MODEL\\gentleman\\leftleg.x"		// 左腿のモデル名
#define PLAYER_L_FOOT		"data\\MODEL\\gentleman\\leftfoot.x"	// 左足のモデル名

//========================================
// クラスの定義
//========================================
//=====================
// プレイヤークラス
//=====================
class CPlayer : public CScene
{
public:
	typedef enum
	{// プレイヤーの状態
		STATE_NORMAL = 0,	// 通常状態
		STATE_WALK,		// 移動状態
		STATE_BREAK,	// 破壊状態
		STATE_UPBREAK,	// 上破壊状態
		STATE_JUMP,		// ジャンプ状態
		STATE_BLOCK,	// ブロック設置状態
		STATE_LAND,		// 着地状態
		STATE_MAX		// プレイヤーの種類の総数
	} STATE;

	typedef struct
	{// キー要素
		float fPosX;
		float fPosY;
		float fPosZ;
		float fRotX;
		float fRotY;
		float fRotZ;
	} KEY;

	typedef struct
	{
		int nFrame;				// フレーム数
		KEY aKey[MAX_PLAYER];
	} KEY_INFO;

	typedef struct
	{// モーション情報
		bool bLoop;						// ループするかしないか
		int nNumKey;					// キーの数
		KEY_INFO aKeyInfo[STATE_MAX];
	} MOTION_INFO;

	CPlayer();																							// コンストラクタ
	~CPlayer();																							// デストラクタ

	HRESULT Init(void);																					// プレイヤー初期化処理
	void Uninit(void);																					// プレイヤー終了処理
	void Update(void);																					// プレイヤー更新処理
	void Draw(void);																					// プレイヤー描画処理
	
	void SetVtx(void);																					// 頂点座標の設定
	void Move(void);																					// プレイヤーが動く処理
	void Action(void);
	void Life(void);																					// 残機処理
	void Health(void);																					// 体力処理
	void OnaraRemain(void);
	void SetBlock(void);																				// ブロックの設置
	bool GetRTriangle(void);																			// 右のポリゴンに乗っているかどうかを取得
	void UpdateMotion(void);																			// モーションの更新処理
	static CPlayer *Create(D3DXVECTOR3 pos);															// オブジェクトの生成
	void LoadMotion(void);																				// 高さのロード

	void CollisonAll(void);																				// 当たり判定
	void CollisonModel(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// モデルとの当たり判定
	void CollisonCoin(D3DXVECTOR3 *pos, float fRadius);											// コインの当たり判定
	void CollisonPolygon(D3DXVECTOR3 *pos, D3DXVECTOR3 fRadius);											// ポリゴンとの判定
	void CollisionField(void);																			// 床との当たり判定
	void CollisionGoal(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);	// ゴールとの当たり判定
	void CollisonObstacle(D3DXVECTOR3 *pos, float fRadius);												// 弾との判定

	D3DXVECTOR3 GetPos(void);																			// 位置の取得
	D3DXVECTOR3 *GetPosOld(void);																		// 1フレーム前の位置を取得
	D3DXVECTOR3 GetMove(void);																			// 移動量の取得
	D3DXVECTOR3 GetRot(void);																			// 向きの取得
	void SetJump(bool bJump);																			// プレイヤーがジャンプしているかどうかを設定
	D3DXVECTOR3 GetBlockPos(void);																			// ブロックの位置の取得
	bool GetJump(void);																					// プレイヤーがジャンプしているかどうかを取得
	static bool GetGoal(void);																			// プレイヤーがゴールしているかどうかを取得
	static bool GetGameOver(void);																		// プレイヤーがゲームオーバーかどうかを取得
	void SetState(STATE state);
	static void MinusNumBlock(void) { m_nNumBlock--; }

private:
	CModel					*m_apModel[MAX_PLAYER];
	static LPD3DXMESH		m_apMesh[MAX_PLAYER];									// メッシュ情報（頂点情報）へのポインタ
	static LPD3DXBUFFER		m_apBuffMat[MAX_PLAYER];								// マテリアル情報へのポインタ
	static DWORD			m_anNumMat[MAX_PLAYER];									// マテリアル情報の数
	static STATE m_State;															// プレイヤーの状態
	static bool				m_bGoal;					// ゴールしているかどうか
	static bool				m_bGameOver;				// ゲームオーバーかどうか
	static int				m_nNumBlock;				// 設置したブロックの数
	static CShadow *m_pShadow;

	D3DXMATRIX				m_mtxWorld;					// ワールドマトリックス

	D3DXVECTOR3				m_move;						// プレイヤーの移動量
	D3DXVECTOR3				m_pos;						// プレイヤーの位置
	D3DXVECTOR3				m_posOld;					// プレイヤーの前のフレームの位置
	D3DXVECTOR3				m_aPosOffset[MAX_PLAYER];	// モデルのオフセット
	D3DXVECTOR3				m_rot;						// プレイヤーの向き
	D3DXVECTOR3				m_BlockPos;					// ブロックの位置の保存用
	D3DXVECTOR3				m_SetBlockPos;				// ブロックを設置する位置
	float					m_fDestAngle;				// 目的の角度
	float					m_fDiffAngle;				// 角度の差分
	bool					m_bRTriangle;				// 右側にいるかどうか
	bool					m_bJump;					// ジャンプしているかどうか
	bool					m_bLand;					// モデルに乗っているかどうか
	bool					m_bPolygonLand;				// 地面に乗っているかどうか
	bool					m_bIronSound;				// 鉄の音を鳴らすかどうか
	bool					m_bWaterSound;				// 水の音を鳴らすかどうか
	bool					m_bAttackSound;				// 攻撃の音を鳴らすかどうか
	bool					m_bBulletHit;				// 弾と当たっているか
	int						m_nBulletTimer;				// 無敵時間
	int						m_nDisTimer;				// 点滅させる時間
	int						m_nNumParts;				// パーツの数
	int						m_WalkTimer;				// 歩いているときに出るパーティクルに使う
	int						m_nLife;					// 残機
	D3DXVECTOR3				m_aVtxMin[MAX_PLAYER], m_aVtxMax[MAX_PLAYER];			// プレイヤーの最小値、最大値
	int						m_nOnaraRemain;	// おなら残機

	KEY_INFO *m_pKeyInfo;								// キー情報へのポインタ
	int m_nKey;											// 現在のキーナンバー
	int m_nCountMotion;									// モーションカウンター
	MOTION_INFO m_aMotionInfo[STATE_MAX];
};
#endif
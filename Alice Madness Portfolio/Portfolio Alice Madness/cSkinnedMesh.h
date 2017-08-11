#pragma once

struct ST_BONE;

class cSkinnedMesh
{
	friend class cSkinnedMeshManager;

private:
	ST_BONE*					m_pRootFrame;			
	ST_BONE*					m_pAttackBone;
	int							m_iAttackNum;
	int							m_iCount;

	DWORD						m_dwWorkingPaletteSize;
	D3DXMATRIX*					m_pmWorkingPalette;
	LPD3DXEFFECT				m_pEffect;
	
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	D3DXMATRIXA16				m_matWorldTM;

	/// >> : OBB -
	//SYNTHESIZE(D3DXVECTOR3, m_vMin, Min);				
	//SYNTHESIZE(D3DXVECTOR3, m_vMax, Max);

///////170728
	float m_fScale;
	D3DXVECTOR3 m_vMin;
	D3DXVECTOR3 m_vMax;

public:
	inline void SetMin(D3DXVECTOR3 vMin) { m_vMin = vMin; }
	inline void SetMax(D3DXVECTOR3 vMax) { m_vMax = vMax; }
	inline D3DXVECTOR3 GetMin() { return *D3DXVec3Scale(&D3DXVECTOR3(), &m_vMin, m_fScale); }
	inline D3DXVECTOR3 GetMax() { return *D3DXVec3Scale(&D3DXVECTOR3(), &m_vMax, m_fScale); }

	void SetScale(float fScale) { m_fScale = fScale; } // �ٸ��� ����ȭ�� ����ȭ �̿ܿ��� ���� �ʴ´�.

	void SetAttackBone(int AttackNum);//���� ����Ǵ� �� ���� ����
	ST_BONE* cSkinnedMesh::GetAttackBone();

public:
	cSkinnedMesh(char* szFolder, char* szFilename, float fScale);

	inline void SetTransform(D3DXMATRIXA16* pmat)	 //������Ʈ �Ǵ� �������� �̰��� �θ���.
	{
		m_matWorldTM =
			*D3DXMatrixScaling(&D3DXMATRIX(), m_fScale, m_fScale, m_fScale)
			* *pmat;
	}

public:
	cSkinnedMesh(char* szFolder, char* szFilename);	 
	~cSkinnedMesh(void);
	
	//inline void SetTransform(D3DXMATRIXA16* pmat){	m_matWorldTM = *pmat; } //������Ʈ �Ǵ� �������� �̰��� �θ���.

	void UpdateAndRender();	//������ �̰��� �Ѱ��ش�.

private:
	float m_fBlenedTime;
	float m_fPassedBlendTime;
	bool m_isAnimBlend;
public:

	void SetAnimationIndex(int nIndex);		
	void SetAnimationIndexBlend(int nIndex);
	bool GetCurrentAnimationEnd(int nowState);
	
//Enemy ���� ����� �Լ� �߰�
	LPD3DXANIMATIONCONTROLLER& GetAniController() { return m_pAnimController; }

private:
	cSkinnedMesh();
	void Load(char* szFolder, char* szFilename);	//SkinnedMeshManager�� �ҷ���
	LPD3DXEFFECT LoadEffect(char* szFilename);
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void Render(ST_BONE* pBone = NULL);
	void SetupBoneMatrixPtrs(ST_BONE* pBone);
	void Destroy();


};


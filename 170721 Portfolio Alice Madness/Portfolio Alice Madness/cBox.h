#pragma once

/* UI이미지를 렌더하는 등 2d 상자입니다. 회전, 스케일 등등의 
값을 저장하고있다가 이미지를 그릴때 worldmatrix를 주거나, 마우스를 감지하는 등의
역할을 합니다.*/

//수정필요

class cBox
{
public:
	//cBox();
	cBox(float fWidth, float fHeight,D3DXVECTOR3 vOrgPosition = D3DXVECTOR3());
	cBox(float fWidth,float fHeight, D3DXVECTOR3 vOrgPosition, D3DXVECTOR3 vPosition, D3DXVECTOR2 fScale = D3DXVECTOR2(1.f,1.f), float fRotZ = 0.f);
	cBox(float fWidth, float fHeight, RECT rc, float fRotZ = 0.f, D3DXVECTOR3 vOrgPosition = D3DXVECTOR3());

	~cBox();

private:
	D3DXVECTOR3 m_vOrgPosition;
	float m_fOrgWidth;
	float m_fOrgHeight;
public:
	D3DXVECTOR3 m_vPosition;
	float m_fRotationZ;
	D3DXVECTOR2 m_vScale;
	
private:
	D3DXMATRIX* m_matParentWorld;
public:
	bool IsProbePt(float x, float y);
	bool IsProbePt(POINT pt);

	void SetPosSclUseRect(RECT rc);
	inline D3DXVECTOR3 GetOrgPosition() { return m_vOrgPosition; }
	inline float GetWidth() { return m_fOrgWidth; }
	inline float GetHeight() { return m_fOrgHeight; }
	RECT GetPosSclRect();	//회전값이 적용되지 않은 
	inline void SetParentWorld(D3DXMATRIX*matParent) { m_matParentWorld = matParent; }

	//matParent가 없을 경우 두값은 같다.
	D3DXMATRIX GetWorldMatrix();
	D3DXMATRIX GetLocalMatrix();
};


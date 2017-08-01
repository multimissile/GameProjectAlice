#pragma once

/* 텍스쳐를 투영평면에 그릴 때 사용합니다. */
class cBox;

class cSpriteImage
{
public:
	cSpriteImage();
	cSpriteImage(const char*szFolder, const char*  szFile, D3DXMATRIX* pMatParent = NULL);
	~cSpriteImage();
private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	cBox* m_pBox;

public:
	inline void SetTexture(LPDIRECT3DTEXTURE9& pTexture) { m_pTexture = pTexture; }
	float GetImageWidth();
	float GetImageHeight();

	void SetParentWorld(D3DXMATRIX* pMatParent);
	void SetRotationZ(float rotZ);
	void SetPosition(D3DXVECTOR3 v);
	void SetScale(float x, float y);
	RECT GetPosSclRect();
	void SetPosSclRect(RECT rc);
	bool IsProbePt(float x, float y);
	bool IsProbePt(POINT pt);


	void Render(D3DXVECTOR3* vPosition);
	void Render();
};


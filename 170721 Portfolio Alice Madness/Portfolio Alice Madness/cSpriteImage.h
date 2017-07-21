#pragma once

/* �ؽ��ĸ� ������鿡 �׸� �� ����մϴ�. */

class cSpriteImage
{
public:
	cSpriteImage();
	cSpriteImage(const char*szFolder, const char*  szFile);
	cSpriteImage(const char*szFolder, const char*  szFile, BYTE transparentR, BYTE transparentG, BYTE transparentB);
	~cSpriteImage();
private:
	LPDIRECT3DTEXTURE9 m_pTexture;
	D3DXIMAGE_INFO m_stImageInfo;		//texture�� �̹��� ������ ����

	


public:
	inline void SetTexture(LPDIRECT3DTEXTURE9& pTexture) { m_pTexture = pTexture; }
	inline float GetImageWidth(){return m_stImageInfo.Width;}
	inline float GetImageHeight() { return m_stImageInfo.Height; }


	void Render(LPD3DXSPRITE& pSprite, D3DXMATRIX& matWorld,D3DXVECTOR3* vPosition = NULL);
};


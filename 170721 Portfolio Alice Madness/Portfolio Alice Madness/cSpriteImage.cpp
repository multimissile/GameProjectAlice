#include "stdafx.h"
#include "cSpriteImage.h"


cSpriteImage::cSpriteImage()
	:m_pTexture(NULL)
{
	ZeroMemory(&m_stImageInfo, sizeof(m_stImageInfo));
}

cSpriteImage::cSpriteImage(const char* szFolder, const char* szFile)
{
	//�ش� �ؽ���, �ؽ������� ���
	m_pTexture = g_pTextureManager->GetTexture(szFolder, szFile, &m_stImageInfo);
}
cSpriteImage::cSpriteImage(const char* szFolder, const char* szFile, BYTE transparentR, BYTE transparentG, BYTE transparentB)
{
	//�ش� �ؽ���, �ؽ������� ���
	m_pTexture = g_pTextureManager->GetTexture(szFolder, szFile, &m_stImageInfo, transparentR, transparentG, transparentB);
}

cSpriteImage::~cSpriteImage()
{
	SAFE_RELEASE(m_pTexture);
}

void cSpriteImage::Render(LPD3DXSPRITE& pSprite, D3DXMATRIX& matWorld, D3DXVECTOR3* vPosition)
{
	if (!m_pTexture)
		return;

	pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	
	pSprite->SetTransform(&matWorld);

	pSprite->Draw(m_pTexture, 0, 0, vPosition, D3DCOLOR_RGBA(255, 255, 255, 255));


	pSprite->End();
}

















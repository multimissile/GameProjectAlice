#include "stdafx.h"
#include "cSpriteImage.h"
#include "cBox.h"

cSpriteImage::cSpriteImage()
	:m_pTexture(NULL)
{

}

cSpriteImage::cSpriteImage(const char* szFolder, const char* szFile, D3DXMATRIX* pMatParent)
{
	//해당 텍스쳐, 텍스쳐정보 얻기
	D3DXIMAGE_INFO stImageInfo;
	m_pTexture = g_pTextureManager->GetTexture(szFolder, szFile, &stImageInfo);
	m_pBox = new cBox(stImageInfo.Width, stImageInfo.Height);
	SetParentWorld(pMatParent);
}

cSpriteImage::~cSpriteImage()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE(m_pBox);
}

float cSpriteImage::GetImageWidth()
{
	return m_pBox->GetWidth();
}

float cSpriteImage::GetImageHeight()
{
	return m_pBox->GetHeight();
}

void cSpriteImage::SetParentWorld(D3DXMATRIX * pMatParent)
{
	m_pBox->SetParentWorld(pMatParent);

}

void cSpriteImage::SetRotationZ(float rotZ)
{
	m_pBox->m_fRotationZ = rotZ;
}

void cSpriteImage::SetPosition(D3DXVECTOR3 v)
{
	m_pBox->m_vPosition = v;
}

void cSpriteImage::SetScale(float x, float y)
{
	m_pBox->m_vScale = D3DXVECTOR2(x, y);
}

RECT cSpriteImage::GetPosSclRect()
{
	return m_pBox->GetPosSclRect();
}

void cSpriteImage::SetPosSclRect(RECT rc)
{
	m_pBox->SetPosSclUseRect(rc);
}

bool cSpriteImage::IsProbePt(float x, float y)
{
	return m_pBox->IsProbePt(x,y);
}

bool cSpriteImage::IsProbePt(POINT pt)
{
	return m_pBox->IsProbePt(pt);
}

void cSpriteImage::Render( D3DXVECTOR3* vPosition)
{
	if (!m_pTexture)
		return;

	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
		
	g_pSprite->SetTransform(&m_pBox->GetWorldMatrix());

	g_pSprite->Draw(m_pTexture, 0, 0, vPosition, D3DCOLOR_RGBA(255, 255, 255, 255));


	g_pSprite->End();
}

void cSpriteImage::Render()
{
	if (!m_pTexture)
		return;

	g_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);

	g_pSprite->SetTransform(&m_pBox->GetWorldMatrix());

	g_pSprite->Draw(m_pTexture, 0, 0, 0, D3DCOLOR_RGBA(255, 255, 255, 255));


	g_pSprite->End();
}















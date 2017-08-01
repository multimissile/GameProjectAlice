#include "stdafx.h"
#include "cBox.h"


//cBox::cBox()
//{
//}

cBox::cBox(float fWidth, float fHeight, D3DXVECTOR3 vOrgPosition)
	:m_fOrgWidth(fWidth)
	, m_vOrgPosition(vOrgPosition)
	,m_fOrgHeight(fHeight)
	, m_vPosition(0.f, 0.f, 0.f)
	,m_fRotationZ(0.f)
	, m_vScale(1.f,1.f)
	, m_matParentWorld(NULL)
{
}

cBox::cBox(float fWidth, float fHeight, D3DXVECTOR3 vOrgPosition, D3DXVECTOR3 vPosition, D3DXVECTOR2 vScale, float fRotZ)
	:m_fOrgWidth(fWidth)
	, m_vOrgPosition(vOrgPosition)
	, m_fOrgHeight(fHeight)
	, m_vPosition(vPosition.x, vPosition.y, 0.f)
	, m_fRotationZ(fRotZ)
	, m_vScale(vScale)
	,m_matParentWorld(NULL)
{
}

cBox::cBox(float fWidth, float fHeight, RECT rc, float fRotZ, D3DXVECTOR3 vOrgPosition)
	:m_fOrgWidth(fWidth)
	, m_vOrgPosition(vOrgPosition)
	, m_fOrgHeight(fHeight)
	, m_fRotationZ(fRotZ)
	,m_matParentWorld(NULL)
{
	SetPosSclUseRect(rc);
}

cBox::~cBox()
{
}

bool cBox::IsProbePt(float x, float y)
{
	if (!m_matParentWorld && Equal(m_fRotationZ, 0.f))
	{
		RECT rc = GetPosSclRect();
		if (rc.left< (float)x && (float)x < rc.right
			&& rc.top < (float)y && (float)y < rc.bottom)
			return true;

		return false;

	}
	
	//월드매트릭스의 역
	D3DXVECTOR3 v((float)x, (float)y, 0.f);
	D3DXMATRIXA16 matInvWorld;

	D3DXMatrixInverse(&matInvWorld, 0, &GetWorldMatrix());
	D3DXVec3TransformCoord(&v, &v, &matInvWorld);


	if (m_vOrgPosition.x < v.x && v.x <m_vOrgPosition.x+ m_fOrgWidth
		&& m_vOrgPosition.y < v.y && v.y <m_vOrgPosition.y + m_fOrgHeight)
		return true;

	return false;
}

bool cBox::IsProbePt(POINT pt)
{
	return IsProbePt((float)pt.x, (float)pt.y);
}

void cBox::SetPosSclUseRect(RECT rc)
{
	m_vPosition.x = rc.left;
	m_vPosition.y = rc.top;
	m_vScale.x = (rc.right - rc.left) / m_fOrgWidth;
	m_vScale.y = (rc.bottom - rc.top) / m_fOrgHeight;
}

RECT cBox::GetPosSclRect()
{
	RECT rc;

	rc.left = m_vPosition.x;
	rc.top = m_vPosition.y;

	rc.right = rc.left + m_fOrgWidth*m_vScale.x;
	rc.bottom = rc.top + m_fOrgHeight*m_vScale.y;

	return rc;
}

D3DXMATRIX cBox::GetLocalMatrix()
{
	//srt
	D3DXMATRIXA16 matS, matR, matT;

	D3DXMatrixScaling(&matS, m_vScale.x, m_vScale.y, 1.f);
	D3DXMatrixRotationZ(&matR, m_fRotationZ);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, 0.f);

	return matS * matR * matT;
}

D3DXMATRIX cBox::GetWorldMatrix()
{
	D3DXMATRIX matLocal = GetLocalMatrix();
	
	if (m_matParentWorld)
		return matLocal * *m_matParentWorld;

	return matLocal;

}

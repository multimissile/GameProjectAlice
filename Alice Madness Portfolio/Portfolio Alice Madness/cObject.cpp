#include "stdafx.h"
#include "cObject.h"
#include "cBounding.h"

cObject::cObject()
	:m_bExist(true)
	,m_pBounding(NULL)
	,m_vPosition(0.f,0.f,0.f)
	,m_fRotationY(0.f)
	,m_matWorld(*D3DXMatrixIdentity(&D3DXMATRIX()))
{
}


cObject::~cObject()
{
	//�Ⱥθ� ���� �����ϱ� �����ϰ� �ѹ��� �ҷ�����...
	SAFE_DELETE(m_pBounding);
}


cBounding * cObject::GetBounding()
{
	return m_pBounding;
}

void cObject::Destroy()
{
	SAFE_DELETE(m_pBounding);
}
void cObject::SetExistFalse()
{
	m_bExist = false;
	Destroy();
}


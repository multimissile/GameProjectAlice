#include "stdafx.h"
#include "c170720Test2.h"


c170720Test2::c170720Test2()
	:m_pTextureTest(NULL)
{
}


c170720Test2::~c170720Test2()
{
	SAFE_RELEASE(m_pTextureTest);
}

void c170720Test2::Setup()
{
	m_pTextureTest = g_pTextureManager->GetTexture("TestFolder/FriendsAndFoes_I7E.png");

	ST_PT_VERTEX v;

	//¿Þ¾Æ·¡
	v.p = D3DXVECTOR3(0, 0, 0);
	v.t = D3DXVECTOR2(0, 1);

	m_vecVertexTest.push_back(v);


	v.p = D3DXVECTOR3(0, 1, 0);
	v.t = D3DXVECTOR2(0, 0);

	m_vecVertexTest.push_back(v);

	v.p = D3DXVECTOR3(1, 0, 0);
	v.t = D3DXVECTOR2(1, 1);

	m_vecVertexTest.push_back(v);
}

void c170720Test2::Update()
{
}

void c170720Test2::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTextureTest);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertexTest.size() / 3, &m_vecVertexTest[0], sizeof(ST_PT_VERTEX));


	g_pD3DDevice->SetTexture(0, NULL);
}

#include "stdafx.h"
#include "cBoundingSphere.h"
#include "cSkinnedMesh.h"

cBoundingSphere::cBoundingSphere()
	:m_fRadius(0.f)
{
	m_enType = BOUNDING_SPHERE;

}


cBoundingSphere::~cBoundingSphere()
{
	//D3DXCompute
	//경계구랑 절두체컬링 쿼드트리 

	//원과 육면체
	//사각형과 사각형
	SAFE_RELEASE(m_pSphere);

}

void cBoundingSphere::Setup(cSkinnedMesh * pSkinnedMesh, SPHERE_SIZE size)
{

	D3DXVECTOR3 vMin = pSkinnedMesh->GetMin();
	D3DXVECTOR3 vMax = pSkinnedMesh->GetMax();

	m_vOrgCenterPos = (vMin + vMax) / 2.f;

	float delta[3];
	delta[0] = abs(vMax.x - vMin.x);
	delta[1] = abs(vMax.y - vMin.y);
	delta[2] = abs(vMax.z - vMin.z);

	
	for (int n = 0; n < 3; n++)
	{
		int idx = n;
		for (int m =n + 1; m < 3; m++)
		{
			if (delta[idx] < delta[m])
				continue;
			//큰값을 뒤로
			idx = m;
		}
		if (n == idx)
			continue;
		
		float temp = delta[n];
		delta[n] = delta[idx];
		delta[idx] = temp;
	}
	

	m_fRadius = delta[size] / 2.f;
	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pSphere, NULL);


	SetBoundingRadius(delta[SPHERE_SIZE_MIN] / 2.f);
}

void cBoundingSphere::Setup(D3DXVECTOR3 & vMax, D3DXVECTOR3 & vMin, SPHERE_SIZE size)
{

	m_vOrgCenterPos = (vMin + vMax) / 2.f;

	float delta[3];
	delta[0] = abs(vMax.x - vMin.x);
	delta[1] = abs(vMax.y - vMin.y);
	delta[2] = abs(vMax.z - vMin.z);


	for (int n = 0; n < 3; n++)
	{
		int idx = n;
		for (int m = n + 1; m < 3; m++)
		{
			if (delta[idx] < delta[m])
				continue;
			//큰값을 뒤로
			idx = m;
		}
		if (n == idx)
			continue;

		float temp = delta[n];
		delta[n] = delta[idx];
		delta[idx] = temp;
	}

	m_fRadius = delta[size] / 2.f;
	D3DXCreateSphere(g_pD3DDevice, m_fRadius, 10, 10, &m_pSphere, NULL);

	SetBoundingRadius(delta[SPHERE_SIZE_MIN] / 2.f);

}

void cBoundingSphere::Update(D3DXMATRIX* pmatWorld)
{

	cBounding::Update(pmatWorld);

}

void cBoundingSphere::ResetBounding()
{
}

void cBoundingSphere::OBBBox_Render()
{

	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//구 위치 변경도 해주어야 한다.
	D3DXMATRIX matT;
	D3DXMatrixTranslation(&matT, 0, m_vOrgCenterPos.y, 0);



	g_pD3DDevice->SetTransform(D3DTS_WORLD, &(m_matWorldTM*matT));
	m_pSphere->DrawSubset(0);

	g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);


}
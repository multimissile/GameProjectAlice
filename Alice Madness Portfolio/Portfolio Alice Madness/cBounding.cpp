#include "stdafx.h"
#include "cBounding.h"
#include "cBoundingSphere.h"
#include "cBoundingBox.h"


cBounding::cBounding()
	:m_vOrgCenterPos(0.f,0.f,0.f)	
	,m_vCenterPos(0.f,0.f,0.f)
	,m_matWorldTM(*D3DXMatrixIdentity(&D3DXMATRIX()))
	, m_fBoundingRadius(0.f)
{
}

cBounding::~cBounding()
{

}

bool cBounding::CheckCollision(cBounding * pB, vector<cBounding*> vecPB)
{
	//들어온 애들중 하나라도 충돌했으면 충돌했다.

	if(pB->m_enType == BOUNDING_BOX)
	{
		for (int n = 0; n < vecPB.size(); n++)
		{
			if (vecPB[n]->m_enType == BOUNDING_BOX)
			{
				if (IntersectBoxBox((cBoundingBox*)pB, (cBoundingBox*)vecPB[n]))
					return true;
			}
			else if (vecPB[n]->m_enType == BOUNDING_SPHERE)
			{
				if (IntersectSphereBox((cBoundingSphere*)vecPB[n], (cBoundingBox*)pB))
					return true;
			}
		}

	}
	else if (pB->m_enType == BOUNDING_SPHERE)
	{
		for (int n = 0; n < vecPB.size(); n++)
		{
			if (vecPB[n]->m_enType == BOUNDING_BOX)
			{
				if (IntersectSphereBox((cBoundingSphere*)pB, (cBoundingBox*)vecPB[n]))
					return true;
			}

			else if (vecPB[n]->m_enType == BOUNDING_SPHERE)
			{
				if (IntersectSphereSphere((cBoundingSphere *)pB, (cBoundingSphere *)vecPB[n]))
					return true;
			}
		}

	}
	//하나도 충돌하지 않았다.
	return false;
}

bool cBounding::IntersectSphereBox(cBoundingSphere * pBSphere, cBoundingBox * pBBox)
{
	//구와 박스의 충돌을 검사한다.

	//중심점에서 

	D3DXPLANE stPlane[6];

	D3DXVECTOR3 v[3];
	//앞면
	v[0] = pBBox->m_vCenterPos - pBBox->m_fAxisHalfLen[2] * pBBox->m_vAxisDir[2];
	v[1] = v[0] + pBBox->m_vAxisDir[1];
	v[2] = v[0] + pBBox->m_vAxisDir[0];

	D3DXPlaneFromPoints(&stPlane[0], &v[0], &v[1], &v[2]);

	//뒷면
	v[0] = pBBox->m_vCenterPos + pBBox->m_fAxisHalfLen[2] * pBBox->m_vAxisDir[2];
	v[1] = v[0] + pBBox->m_vAxisDir[1];
	v[2] = v[0] - pBBox->m_vAxisDir[0];

	D3DXPlaneFromPoints(&stPlane[1], &v[0], &v[1], &v[2]);

	//왼쪽
	v[0] = pBBox->m_vCenterPos - pBBox->m_fAxisHalfLen[0] * pBBox->m_vAxisDir[0];
	v[1] = v[0] + pBBox->m_vAxisDir[1];
	v[2] = v[0] - pBBox->m_vAxisDir[2];

	D3DXPlaneFromPoints(&stPlane[2], &v[0], &v[1], &v[2]);

	//오른쪽
	v[0] = pBBox->m_vCenterPos + pBBox->m_fAxisHalfLen[0] * pBBox->m_vAxisDir[0];
	v[1] = v[0] + pBBox->m_vAxisDir[1];
	v[2] = v[0] + pBBox->m_vAxisDir[2];

	D3DXPlaneFromPoints(&stPlane[3], &v[0], &v[1], &v[2]);

	//윗쪽
	v[0] = pBBox->m_vCenterPos + pBBox->m_fAxisHalfLen[1] * pBBox->m_vAxisDir[1];
	v[1] = v[0] + pBBox->m_vAxisDir[2];
	v[2] = v[0] + pBBox->m_vAxisDir[0];


	D3DXPlaneFromPoints(&stPlane[4], &v[0], &v[1], &v[2]);

	//윗쪽
	v[0] = pBBox->m_vCenterPos - pBBox->m_fAxisHalfLen[1] * pBBox->m_vAxisDir[1];
	v[1] = v[0] - pBBox->m_vAxisDir[2];
	v[2] = v[0] + pBBox->m_vAxisDir[0];

	D3DXPlaneFromPoints(&stPlane[5], &v[0], &v[1], &v[2]);

	for (int n = 0; n < _countof(stPlane); n++)
	{
		//내적한 값이 한면이라도 반지름보다 크면 
		if (D3DXPlaneDotCoord(&stPlane[n], &pBSphere->m_vCenterPos) > pBSphere->m_fRadius)
			return false;
	}
	return true;
}

bool cBounding::IntersectSphereSphere(cBoundingSphere * pBSphere1, cBoundingSphere * pBSphere2)
{
	return (D3DXVec3Length(&(pBSphere1->m_vCenterPos - pBSphere2->m_vCenterPos)) < 
		pBSphere1->m_fRadius + pBSphere2->m_fRadius);
}

bool cBounding::IntersectBoxBox(cBoundingBox * pBBox1, cBoundingBox * pBBox2)
{
	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;

	const float cutOff = 0.999999f;
	bool existsParallelPair = false;

	//축을 하나 만들어서 새로 만들어진 축에 대한 값들 구하고
	//각각의 축 충돌검사해주는애

	D3DXVECTOR3 D = pBBox2->m_vCenterPos - pBBox1->m_vCenterPos;

	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			cos[a][b] = D3DXVec3Dot(&pBBox1->m_vAxisDir[a], &pBBox2->m_vAxisDir[b]);
			absCos[a][b] = abs(cos[a][b]);
			if (absCos[a][b] > cutOff)
				existsParallelPair = true;
		}
		dist[a] = D3DXVec3Dot(&pBBox1->m_vAxisDir[a], &D);
		r = abs(dist[a]);
		r0 = pBBox1->m_fAxisHalfLen[a];

		r1 = pBBox2->m_fAxisHalfLen[0] * absCos[a][0] +
			pBBox2->m_fAxisHalfLen[1] * absCos[a][1] +
			pBBox2->m_fAxisHalfLen[2] * absCos[a][2];

		if (r > r0 + r1)
			return false;
	}

	for (int b = 0; b < 3; b++)
	{
		r = abs(D3DXVec3Dot(&pBBox2->m_vAxisDir[b], &D));
		r0 = pBBox1->m_fAxisHalfLen[0] * absCos[0][b] +
			pBBox1->m_fAxisHalfLen[1] * absCos[1][b] +
			pBBox1->m_fAxisHalfLen[2] * absCos[2][b];

		r1 = pBBox2->m_fAxisHalfLen[b];

		if (r > r0 + r1)
			return false;
	}


	if (existsParallelPair) return true;

	{	// : 3 x 3 개 
		r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
		r0 = pBBox1->m_fAxisHalfLen[0] * absCos[2][0] + pBBox1->m_fAxisHalfLen[2] * absCos[0][0];
		r1 = pBBox2->m_fAxisHalfLen[1] * absCos[1][2] + pBBox2->m_fAxisHalfLen[2] * absCos[1][1];
		if (r > r0 + r1)
			return false;

		r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
		r0 = pBBox1->m_fAxisHalfLen[0] * absCos[2][1] + pBBox1->m_fAxisHalfLen[2] * absCos[0][1];
		r1 = pBBox2->m_fAxisHalfLen[0] * absCos[1][2] + pBBox2->m_fAxisHalfLen[2] * absCos[1][0];
		if (r > r0 + r1)
			return false;

		r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
		r0 = pBBox1->m_fAxisHalfLen[0] * absCos[2][2] + pBBox1->m_fAxisHalfLen[2] * absCos[0][2];
		r1 = pBBox2->m_fAxisHalfLen[0] * absCos[1][1] + pBBox2->m_fAxisHalfLen[1] * absCos[1][0];
		if (r > r0 + r1)
			return false;

		r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
		r0 = pBBox1->m_fAxisHalfLen[0] * absCos[1][0] + pBBox1->m_fAxisHalfLen[1] * absCos[0][0];
		r1 = pBBox2->m_fAxisHalfLen[1] * absCos[2][2] + pBBox2->m_fAxisHalfLen[2] * absCos[2][1];
		if (r > r0 + r1)
			return false;

		r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
		r0 = pBBox1->m_fAxisHalfLen[0] * absCos[1][1] + pBBox1->m_fAxisHalfLen[1] * absCos[0][1];
		r1 = pBBox2->m_fAxisHalfLen[0] * absCos[2][2] + pBBox2->m_fAxisHalfLen[2] * absCos[2][0];
		if (r > r0 + r1)
			return false;


		r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
		r0 = pBBox1->m_fAxisHalfLen[0] * absCos[1][2] + pBBox1->m_fAxisHalfLen[1] * absCos[0][2];
		r1 = pBBox2->m_fAxisHalfLen[0] * absCos[2][1] + pBBox2->m_fAxisHalfLen[1] * absCos[2][0];
		if (r > r0 + r1)
			return false;

		r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
		r0 = pBBox1->m_fAxisHalfLen[1] * absCos[2][0] + pBBox1->m_fAxisHalfLen[2] * absCos[1][0];
		r1 = pBBox2->m_fAxisHalfLen[1] * absCos[0][2] + pBBox2->m_fAxisHalfLen[2] * absCos[0][1];
		if (r > r0 + r1)
			return false;



		r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
		r0 = pBBox1->m_fAxisHalfLen[1] * absCos[2][1] + pBBox1->m_fAxisHalfLen[2] * absCos[1][1];
		r1 = pBBox2->m_fAxisHalfLen[0] * absCos[0][2] + pBBox2->m_fAxisHalfLen[2] * absCos[0][0];
		if (r > r0 + r1)
			return false;



		r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
		r0 = pBBox1->m_fAxisHalfLen[1] * absCos[2][2] + pBBox1->m_fAxisHalfLen[2] * absCos[1][2];
		r1 = pBBox2->m_fAxisHalfLen[0] * absCos[0][1] + pBBox2->m_fAxisHalfLen[1] * absCos[0][0];
		if (r > r0 + r1)
			return false;
	}

	return true;

}

bool cBounding::InVecPlane(cBounding * pB, vector<LPD3DXPLANE> vecPlane)
{




	return false;
}

bool cBounding::SphereInPlane(cBoundingSphere * pB, LPD3DXPLANE plane)
{



	return false;
}

bool cBounding::BoxInPlane(cBoundingBox * pB, LPD3DXPLANE plane)
{
	return false;
}

void cBounding::ResetBounding()
{

}

void cBounding::Update(D3DXMATRIX* pmatWorld)
{
	if (pmatWorld)
	{
		m_matWorldTM = *pmatWorld;


		D3DXVec3TransformCoord(
			&m_vCenterPos,
			&m_vOrgCenterPos,
			pmatWorld);
	}
}

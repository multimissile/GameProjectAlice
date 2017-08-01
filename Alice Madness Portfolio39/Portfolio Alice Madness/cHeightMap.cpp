#include "stdafx.h"
#include "cHeightMap.h"


cHeightMap::cHeightMap()
	: m_pTexture(NULL),
	m_pMesh(NULL)
{
}


cHeightMap::~cHeightMap()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pMesh);
}

void cHeightMap::Setup(char * szFolder, char * szRaw, char * szTex, DWORD dwBytePerPixel)
{

	vector<BYTE> vecY;

	//파일열기
	string sFolder = szFolder;
	string sRaw = sFolder + (string("/") + string(szRaw));
	string sTex = sFolder +(string("/") + string(szTex));

	m_pTexture = g_pTextureManager->GetTexture(sTex);

	FILE* fp = NULL;
	fopen_s(&fp, sRaw.c_str(), "rb");

	fseek(fp, 0, SEEK_END);
	int nFileSize = ftell(fp);
	int nNumVertex = nFileSize / dwBytePerPixel;		//점갯수

	int nRow = (int)sqrt((float)nNumVertex + 0.0001f);		//오류방지

	int nCol = nRow;
	int nTileN = nRow -1;
	m_nTileN = nTileN;


	fseek(fp, 0, SEEK_SET);


	vector<ST_PNT_VERTEX> vecVertex(nNumVertex);
	m_vecVertex.resize(nNumVertex);

	std::vector<DWORD> vecIndex;
	vecIndex.reserve(nTileN * nTileN * 2 * 3);

	for (int n = 0; n < nNumVertex; n++)
	{
		ST_PNT_VERTEX v;
		v.p = D3DXVECTOR3(n % nCol - nCol/2.f, ((unsigned char)fgetc(fp) / 10.f) - 10,n / nCol - nCol / 2.f);
		v.n = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2((n % nCol) / (float)nCol, (n / nCol) / (float)nCol);

		vecVertex[n] = v;
		m_vecVertex[n] = v.p;

		//안해도되고해도되고 3 바이트면 나머지 버리고
		if (dwBytePerPixel == 3)
		{
			fgetc(fp); fgetc(fp);
		}
	}


	
	fclose(fp);
	for (int x= 1; x < nTileN; x++)
	{
		for (int z = 1; z < nTileN; z++)
		{
			int left = (z + 0) * nCol + x - 1;
			int right = (z + 0)	* nCol + x + 1;
			int up = (z + 1) * nCol + x + 0;			//아래가 더하기 아닝가?
			int down = (z - 1) * nCol + x + 0;

			D3DXVECTOR3 leftToRight =
				m_vecVertex[right] - m_vecVertex[left];
			D3DXVECTOR3 downToUp =
				m_vecVertex[up] - m_vecVertex[down];

			D3DXVECTOR3 normal;
			D3DXVec3Cross(&normal, &downToUp, &leftToRight);
			D3DXVec3Normalize(&normal, &normal);

			int nIndex = z * nCol + x;
			vecVertex[nIndex].n = normal;

		}
	}

	// TEST
	///////////////////
	//m_vecPNTVertex = vecVertex;
	///////////////
	//


	//인덱스 버퍼 만들기

	for (int x = 0; x < nTileN; x++)
	{
		for (int z = 0; z < nTileN; z++)
		{
			int _0 = (z + 0) * nCol + x + 0;
			int _1 = (z + 1) * nCol + x + 0;
			int _2 = (z + 0) * nCol + x + 1;
			int _3 = (z + 1) * nCol + x + 1;

			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_2);

			vecIndex.push_back(_3);
			vecIndex.push_back(_2);
			vecIndex.push_back(_1);

		}
	}


	D3DXCreateMeshFVF(vecIndex.size() / 3, vecVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF,
		g_pD3DDevice, &m_pMesh);
	ST_PNT_VERTEX * pV = NULL;

	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0],
		vecVertex.size() * sizeof(ST_PNT_VERTEX));

	m_pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;

	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);

	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();

	DWORD * pA;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD));
	m_pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(vecIndex.size());
	m_pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0], 0, 0, 0);
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.f);
	m_stMtl.Diffuse= D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.f);
	m_stMtl.Specular= D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.f);


//
//	FILE* fp;
//	fopen_s(&fp, sFullName.c_str(), "rb");
//
//	//파일의 끝이 아닐때까지
//	while (!feof(fp))
//	{
//		BYTE b;
//		fread(&b, sizeof(BYTE) * dwBytePerPixel, 1, fp);
//		vecY.push_back(b);
//	}
//
//	fclose(fp);
//
//
//	//vertex 채우기
//	m_vecVertex.resize(vecY.size());
//	//for (int n = 0; n < m_vecVertex.size(); n++)
//	//{
//	//	m_vecVertex[n].y = vecY[n] / 10.f;
//	//}
//
//	int line = (int)sqrt(vecY.size());
//	m_TileN = (line - 1) * (line - 1);
//
//	//xz 채우기
//	for (int n = 0; n < line; n++)
//	{
//		for (int m = 0; m < line; m++)
//		{
//			int idx = n*line + m;
//			m_vecVertex[idx].y = vecY[idx] / 10.f;
//			m_vecVertex[idx].x = m;
//			m_vecVertex[idx].z = -n;
//		}
//	}
//
//	//메쉬에 들어갈 버텍스 설정
//	vector<ST_PNT_VERTEX> vecPNTVertex(m_vecVertex.size());
//
//	for (int n = 0; n < line; n++)
//	{
//		for (int m = 0; m < line; m++)
//		{
//			int idx = line * n + m;
//			vecPNTVertex[idx].p = m_vecVertex[idx];
//			vecPNTVertex[idx].t = D3DXVECTOR2(m / float(line), n / (float)line);
//
//			if (m == 0 || m == line - 1 || n == 0 || n == line - 1)
//			{
//				vecPNTVertex[idx].n = D3DXVECTOR3(0, 0, 0);
//			}
//			else
//			{
//				D3DXVECTOR3 v1 = m_vecVertex[idx + 1] - m_vecVertex[idx - 1];
//				D3DXVECTOR3 v2 = m_vecVertex[idx + line] - m_vecVertex[idx - line];
//
//				//두 벡터를 내적한 벡터가
//				D3DXVec3Cross(&vecPNTVertex[idx].n, &v1, &v2);
//				D3DXVec3Normalize(&vecPNTVertex[idx].n, &vecPNTVertex[idx].n);
//			}
//		}
//	}
//
//
//
//
////	for (int n = 0; n < line; n++)
////	{
////		for (int m = 0; m < line; m++)
////		{
////			//p n t 설정해서 넣어주자
////			ST_PNT_VERTEX v;
////
////			int idx = n*line + m;
////			v.p = m_vecVertex[idx];
////
////			if (m == 0 || m == line - 1 || n == 0 || n == line - 1)
////			{
////				v.n = D3DXVECTOR3(0, 0, 0);
////			}
////			else
////			{
////				D3DXVECTOR3 v1 = m_vecVertex[idx + 1] - m_vecVertex[idx - 1];
////				D3DXVECTOR3 v2 = m_vecVertex[idx + line] - m_vecVertex[idx - line];
////
////				//두 벡터를 내적한 벡터가
////				D3DXVec3Cross(&v.n, &v1, &v2);
////				D3DXVec3Normalize(&v.n, &v.n);
////			}
////
////			v.t = D3DXVECTOR2(m / float(line), n / float(line));
////			vecPNTVertex.push_back(v);
////
////		}
////	}
//
//	m_vecPNTVertex = vecPNTVertex;
//	vector<DWORD> vecIndex;
//
//
//	for (int n = 0; n < line - 1; n++)
//	{
//		for (int m = 0; m < line - 1; m++)
//		{
//			int idx = n*line + m;
//			//위 삼각형
//			vecIndex.push_back(idx);
//			vecIndex.push_back(idx + 1);
//			vecIndex.push_back(idx + 1 + line);
//			//아래 삼각형
//			vecIndex.push_back(idx);
//			vecIndex.push_back(idx + line + 1);
//			vecIndex.push_back(idx + line);
//		}
//	}
//
//	//메쉬를 만들자
//	m_pMesh = NULL;
//	//ST_PNT_VERTEX 타입의 메쉬를 만들자!
//	//면 갯수는 
//	D3DXCreateMeshFVF(m_TileN, vecPNTVertex.size(), D3DXMESH_32BIT | D3DXMESH_DYNAMIC, ST_PNT_VERTEX::FVF, g_pD3DDevice, &m_pMesh);
//
//	/*if (hr == D3DERR_INVALIDCALL)
//	{
//
//	}
//	else if (hr == E_OUTOFMEMORY)
//	{
//
//	}*/
//
//
//	//	버텍ㄱ스를 얻고 인덱스도 얻고
//	ST_PNT_VERTEX* pV = NULL;
//	m_pMesh->LockVertexBuffer(0, (void**)&pV);
//
//	//쓰자
//	memcpy(pV, &vecPNTVertex[0], sizeof(ST_PNT_VERTEX)*vecPNTVertex.size());
//
//	m_pMesh->UnlockVertexBuffer();
//
//	WORD* pI = NULL;
//	m_pMesh->LockIndexBuffer(0, (void**)&pI);
//
//	//for (int n = 0; n < vecIndex.size(); n++,pI++)//, pI+=2)
//	//{
//	//	*pI = vecIndex[n];
//	//}
//
//	//for (int n = 0; n < vecIndex.size(); n++, pI++)//, pI+=2)
//	//{
//	//	*pI = vecIndex[n];
//	//}
//
//	memcpy(pI, &vecIndex[0], sizeof(WORD) * vecIndex.size());
//	//memcpy(pI, &vecIndex[0], sizeof(DWORD) * vecIndex.size());
//
//	m_pMesh->UnlockIndexBuffer();
//
//
//	//DWORD* pA = NULL;
//	//m_pMesh->LockAttributeBuffer(0, &pA);
//	//for (int n = 0; n < m_TileN; n++, pA++)
//	//{
//	//	*pA = 0;
//	//}
//	//m_pMesh->UnlockAttributeBuffer();
//	
//
//	//최적화
//	//vector<DWORD> vecAdj(vecPNTVertex.size());
//	//m_pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
//	//
//	//m_pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0);
//
//	//텍스쳐도 읽어오고
//	sFullName = szFolder;
//	sFullName += (string("/") + string(szTex));
//
//	
//	//텍스쳐 읽어오고
//	m_pTexture = g_pTextureManager->GetTexture(sFullName);
//
//	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
//
//	//mtl은 마음대로
//	m_stMtl.Ambient = D3DXCOLOR(0.4f,0.4f,0.4f,1.f);
//	m_stMtl.Diffuse = D3DXCOLOR(0.4f, 0.4f, 0.4f, 1.f);
//	m_stMtl.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
//
//
//
//
}

void cHeightMap::Render()
{
	D3DXMATRIXA16 matWorld;

	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetMaterial(&m_stMtl);
	g_pD3DDevice->SetTexture(0, m_pTexture);

	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pMesh->DrawSubset(0);
	/////TEST 
	//g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	//for (int n = 0; n < m_nTileN; n++)
	//{
	//	for (int m = 0; m < m_nTileN; m++)
	//	{
	//		ST_PNT_VERTEX v[6];
	//
	//		int idx = n*(m_nTileN + 1) + m;
	//
	//		int _0 = (m + 0) * (m_nTileN + 1) + n + 0;
	//		int _1 = (m + 1) * (m_nTileN + 1) + n + 0;
	//		int _2 = (m + 0) * (m_nTileN + 1) + n + 1;
	//		int _3 = (m + 1) * (m_nTileN + 1) + n + 1;
	//
	//
	//		//위 삼각형
	//		v[0] = m_vecPNTVertex[_0];
	//		v[1] = m_vecPNTVertex[_1];
	//		v[2] = m_vecPNTVertex[_2];
	//
	//		v[3] = m_vecPNTVertex[_3];
	//		v[4] = m_vecPNTVertex[_2];
	//		v[5] = m_vecPNTVertex[_1];
	//		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &v[0], sizeof(ST_PNT_VERTEX));
	//	}
	//}
	//

	////matrix , mtl, texture, draw
	//
	//
	//g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, D3DXMatrixIdentity(&D3DXMATRIX()));
	//g_pD3DDevice->SetTexture(0, m_pTexture);
	//g_pD3DDevice->SetMaterial(&m_stMtl);
	//
	//m_pMesh->DrawSubset(0);
	//
	//
	////g_pD3DDevice->SetFVF(D3DFVF_XYZ);
	//g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	//
	//
	//int line = (int)sqrt(m_TileN) + 1;
	//
	//for (int n = 0; n < line-1; n++)
	//{
	//	for (int m = 0; m < line-1; m++)
	//	{
	//		ST_PNT_VERTEX v[6];
	//
	//		int idx = n*line +m;
	//		//위 삼각형
	//		v[0] = m_vecPNTVertex[idx];
	//		v[1] = m_vecPNTVertex[idx + 1];
	//		v[2] = m_vecPNTVertex[idx + 1 + line];
	//
	//		v[3] = m_vecPNTVertex[idx];
	//		v[4] = m_vecPNTVertex[idx + line + 1];
	//		v[5] = m_vecPNTVertex[idx + line];
	//		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &v[0], sizeof(ST_PNT_VERTEX));
	//	}
	//}

}

bool cHeightMap::GetHeight(IN float x, OUT float & y, IN float z)
{
	//타일 밖으로 나갔을 때
	if (x < 0.0f || z < 0.0f || x >= m_nTileN || z >= m_nTileN)
	{
		y = 0;
		return false;
	}

	int nX = x;
	int nZ = z;
 
	float fDeltaX = x - nX;
	float fDeltaZ = z - nZ;

	int _0 = (nZ + 0) *(m_nTileN + 1) + nX + 0;
	int _1 = (nZ + 1) * (m_nTileN + 1) + nX + 0;
	int _2 = (nZ + 0) * (m_nTileN + 1) + nX + 1;
	int _3 = (nZ + 1) * (m_nTileN + 1) + nX + 1;

	if (fDeltaX + fDeltaZ < 1.f)
	{
		D3DXVECTOR3 v01 = m_vecVertex[_1] - m_vecVertex[_0];
		D3DXVECTOR3 v02 = m_vecVertex[_2] - m_vecVertex[_0];
		y = m_vecVertex[_0].y + (v01 * fDeltaZ + v02 * fDeltaX).y;
		return true;
	}
	else
	{
		fDeltaX = 1.f - fDeltaX;
		fDeltaZ = 1.f - fDeltaZ;
		D3DXVECTOR3 v31 = m_vecVertex[_1] - m_vecVertex[_3];
		D3DXVECTOR3 v32 = m_vecVertex[_2] - m_vecVertex[_3];

		y = m_vecVertex[_3].y - (v31 *fDeltaX + v32 * fDeltaZ).y;
		return true;
	}

	return false;
}

void cHeightMap::Destroy()
{
	//소멸자를 사용하지 않을 경우
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pMesh);
}

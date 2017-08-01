#include "stdafx.h"
#include "cRawLoader.h"


cRawLoader::cRawLoader()
{
}


cRawLoader::~cRawLoader()
{
}

void cRawLoader::Load(const char * szFolder, const char * szFile, int nInterval, LPD3DXMESH & pMesh, vector<D3DXVECTOR3>& vecVertex,BYTE dwBytePerPixel)
{
	vector<BYTE> vecY;

	//���Ͽ���
	string sFolder = szFolder;
	string sRaw = sFolder + (string("/") + string(szFile));

	FILE* fp = NULL;
	fopen_s(&fp, sRaw.c_str(), "rb");

	fseek(fp, 0, SEEK_END);
	int nFileSize = ftell(fp);
	//�Ѹ����
	int nNumVertex = nFileSize / dwBytePerPixel;		//������

	int nCol = (int)sqrt((float)nNumVertex + 0.0001f);		//��������

	int nTileN = nCol - 1;

	fseek(fp, 0, SEEK_SET);
	
	vector<ST_PNT_VERTEX> vecPNTVertex(nNumVertex);
	vecVertex.resize(nNumVertex);

	std::vector<DWORD> vecIndex;
	vecIndex.reserve(nTileN * nTileN * 2 * 3);

	for (int n = 0; n < nCol; n++)	//��
	{
		for (int m = 0; m < nCol; m++)
		{
			int nIdx = n * nCol + m;
			ST_PNT_VERTEX v;
			//y���� �����ʿ�
			v.p = D3DXVECTOR3(-((nCol - 1) * nInterval) / 2 + m * nInterval, (unsigned char)fgetc(fp)/10.f - 10, -((nCol - 1)* nInterval) / 2 + n * nInterval);
			v.n = D3DXVECTOR3(0, 1, 0);
			//�̰� ���� �ʿ� uv �� 90�� �� ��ǥ�� ������ �Ѵ�.
			v.t = D3DXVECTOR2( m / (float)nCol, n / (float)nCol);

			vecPNTVertex[nIdx] = v;
			vecVertex[nIdx] = v.p;

			//���ص��ǰ��ص��ǰ� 3 ����Ʈ�� ������ ������
			if (dwBytePerPixel == 3)
			{
				fgetc(fp); fgetc(fp);
			}


		}
	}


	fclose(fp);

	//���� ���ʿ��� ���������� ���ϴ� ���Ϳ� ������ �Ʒ��� ���ϴ� ������ ���� ?? �̰� �´��� Ȯ����
	for (int x = 1; x < nTileN; x++)
	{
		for (int z = 1; z < nTileN; z++)
		{
			int left = (z + 0) * nCol + x - 1;
			int right = (z + 0)	* nCol + x + 1;
			int up = (z + 1) * nCol + x + 0;			//�Ʒ��� ���ϱ� �ƴװ�?
			int down = (z - 1) * nCol + x + 0;

			D3DXVECTOR3 leftToRight =
				vecVertex[right] - vecVertex[left];
			D3DXVECTOR3 downToUp =							//���� �´��� üũ
				vecVertex[up] - vecVertex[down];

			D3DXVECTOR3 normal;
			D3DXVec3Cross(&normal, &downToUp, &leftToRight);
			D3DXVec3Normalize(&normal, &normal);

			int nIndex = z * nCol + x;
			vecPNTVertex[nIndex].n = normal;
		}
	}

	//�ε��� ���� �����

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


	D3DXCreateMeshFVF(vecIndex.size() / 3, vecPNTVertex.size(),
		D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF,
		g_pD3DDevice, &pMesh);
	ST_PNT_VERTEX * pV = NULL;

	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecPNTVertex[0],
		vecPNTVertex.size() * sizeof(ST_PNT_VERTEX));

	pMesh->UnlockVertexBuffer();

	DWORD* pI = NULL;

	pMesh->LockIndexBuffer(0, (LPVOID*)&pI);

	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	pMesh->UnlockIndexBuffer();

	DWORD * pA;
	pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	std::vector<DWORD> vecAdj(vecIndex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0], 0, 0, 0);

}

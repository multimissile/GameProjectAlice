#pragma once



class cRawLoader
{
public:
	cRawLoader();
	~cRawLoader();

	void Load(const char* szFile, const char* szFolder,int nInterval ,
		LPD3DXMESH& pMesh,vector<D3DXVECTOR3>& vecVertex, BYTE dwBytePerPixel = 1);
};


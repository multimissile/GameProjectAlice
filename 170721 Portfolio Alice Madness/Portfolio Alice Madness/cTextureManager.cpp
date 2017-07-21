#include "stdafx.h"
#include "cTextureManager.h"


cTextureManager::cTextureManager()
{
}


cTextureManager::~cTextureManager()
{
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char * szFullPath)
{
	//텍스쳐 맵에 값이 없을 때
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		//새로 만들어서 리턴해주면 된다.
		D3DXCreateTextureFromFileA(g_pD3DDevice,
									szFullPath, 
									&m_mapTexture[szFullPath]);
	}

	//있으면 그냥 리턴해주면 된다.

	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string & sFullPath)
{
	
	return GetTexture((char*)sFullPath.c_str());
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(const char * szFolder, const char * szFile)
{
	string sFullPath(szFolder + string("/") + szFile);
	return GetTexture((char*)sFullPath.c_str());

}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(char * szFullPath, D3DXIMAGE_INFO * pImageInfo)
{

	//정보맵에 값이 없을 때
	if (m_mapImageInfo.find(szFullPath) == m_mapImageInfo.end())
	{
		SAFE_RELEASE(m_mapTexture[szFullPath]);
		
		//파일을 읽어온다.
		D3DXCreateTextureFromFileEx(g_pD3DDevice,
			szFullPath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0, 
			D3DFMT_UNKNOWN, 
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapImageInfo[szFullPath],
			NULL,
			&m_mapTexture[szFullPath]
		);

	}

	//값 넣어주고
	*pImageInfo = m_mapImageInfo[szFullPath];

	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(std::string & sFullPath, D3DXIMAGE_INFO * pImageInfo)
{
	return GetTexture((char*)sFullPath.c_str(), pImageInfo);

}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(const char * szFolder, const char * szFile, D3DXIMAGE_INFO * pImageInfo)
{
	string sFullPath(szFolder + string("/") + szFile);
	return GetTexture((char*)sFullPath.c_str(), pImageInfo);
}

LPDIRECT3DTEXTURE9 cTextureManager::GetTexture(const char * szFolder, const char * szFile, D3DXIMAGE_INFO * pImageInfo, BYTE transparentR, BYTE transparentG, BYTE transparentB)
{


	string sFullPath(szFolder + string("/") + szFile);

	char c[10];
	sprintf(c, "%d%d%d", transparentR, transparentG, transparentB);
	string sFullPathC(szFolder + string("/") + szFile + c);

	D3DCOLOR transparentColor = D3DCOLOR_XRGB(transparentR, transparentG, transparentB);

	//정보맵에 값이 없을 때
	if (m_mapImageInfo.find(sFullPathC.c_str()) == m_mapImageInfo.end())
	{

		SAFE_RELEASE(m_mapTexture[sFullPathC.c_str()]);

		//파일을 읽어온다.
		D3DXCreateTextureFromFileEx(g_pD3DDevice,
			sFullPath.c_str(),
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			transparentColor,
			&m_mapImageInfo[sFullPathC.c_str()],
			NULL,
			&m_mapTexture[sFullPathC.c_str()]
		);

	}

	//값 넣어주고
	*pImageInfo = m_mapImageInfo[sFullPathC.c_str()];

	return m_mapTexture[sFullPathC.c_str()];

}

void cTextureManager::Destroy()
{
	//map의 LPDIRECT3DTEXTURE9 에 값이 있다면 해당 객체의 Release함수를 호출
	for each(auto it in m_mapTexture)
	{
		SAFE_RELEASE(it.second);
	}
	m_mapTexture.clear();

}

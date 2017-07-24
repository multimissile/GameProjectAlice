#pragma once

/* 게임에서 사용될 텍스쳐를 로드해 사용합니다. */


#define g_pTextureManager cTextureManager::GetInstance()

class cTextureManager
{
private:
	SINGLETON(cTextureManager);

	
	map<string, LPDIRECT3DTEXTURE9>		m_mapTexture;
	map<string, D3DXIMAGE_INFO>			m_mapImageInfo;

public:
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(std::string& sFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(const char* szFolder, const char* szFile);	//좀더 편하게 사용하기위해
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath, D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9 GetTexture(std::string& sFullPath, D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9 GetTexture(const char* szFolder, const char* szFile, D3DXIMAGE_INFO* pImageInfo);	//좀더 편하게 사용하기위해

	void Destroy();
};


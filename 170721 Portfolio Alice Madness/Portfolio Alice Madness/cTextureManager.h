#pragma once

/* 게임에서 사용될 텍스쳐를 로드해 사용합니다. */
//게임 내의 모든 텍스쳐를 여기에 모아두고 필요할때 포인터로 받아와서 그릴 수 있습니다.
//GetTexture() 함수를 불렀을 때 map에 텍스쳐가 없다면 fullPath를 이용해
//텍스쳐를 새로 생성하고 맵에 등록한 후 해당 텍스쳐를 가리키는 포인터를 줍니다.


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

	//특정색상 빼고 불러올거
	LPDIRECT3DTEXTURE9 GetTexture(const char*szFolder, const char* szFile, D3DXIMAGE_INFO* pImageInfo, 
		BYTE transparentR, BYTE transparentG, BYTE transparentB);


	void Destroy();
};


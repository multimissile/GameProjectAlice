#pragma once

/* ���ӿ��� ���� �ؽ��ĸ� �ε��� ����մϴ�. */


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
	LPDIRECT3DTEXTURE9 GetTexture(const char* szFolder, const char* szFile);	//���� ���ϰ� ����ϱ�����
	LPDIRECT3DTEXTURE9 GetTexture(char* szFullPath, D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9 GetTexture(std::string& sFullPath, D3DXIMAGE_INFO* pImageInfo);
	LPDIRECT3DTEXTURE9 GetTexture(const char* szFolder, const char* szFile, D3DXIMAGE_INFO* pImageInfo);	//���� ���ϰ� ����ϱ�����

	void Destroy();
};


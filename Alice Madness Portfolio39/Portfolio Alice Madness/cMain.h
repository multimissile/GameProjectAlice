#pragma once

#include "cScene.h"

class cSkinnedMesh;
class cSpriteImage;
class cMeshGroup;

class cMain : public cScene
{
	cSkinnedMesh* m_pAlice;
	cSpriteImage* m_pMenuLine;
	cMeshGroup* m_pBackGround;
	

public:
	cMain();
	//선택한 데이터 불러오기
	//cMain(char* szFile, char* szFolder);
	~cMain();
	void Setup();
	void Update();
	void Render();
};



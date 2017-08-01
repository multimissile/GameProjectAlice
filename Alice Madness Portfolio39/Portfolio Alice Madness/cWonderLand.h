#pragma once

#include "cScene.h"

//class cCharacterTest;
//class cCharacterTest;
//class cPlayer;
//class cMeshGroup;

class cWonderLand : public cScene		
{
//1. 캐릭터
	//cPlayer* m_pPlayer;
//2. 적
//3. 오브젝트
//4. 타일		
//5. 아이템
//6. 이벤트

	//cCharacterTest* m_pCharacterTest;
//


public:
	cWonderLand();
	~cWonderLand();

	//void Setup(char* szFolder, char* szFile);
	void Setup();
	void Update();
	void Render();

	//void Setup(cCamera* pCamera);

	//void ControlCamera();
	//void RenderCamera();

};


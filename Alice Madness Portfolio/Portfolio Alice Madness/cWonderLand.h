#pragma once

#include "cScene.h"

//class cCharacterTest;
class cPlayer;


class cWonderLand : public cScene		
{

//1. ĳ����
	cPlayer* m_pPlayer;
//2. ��
//3. ������Ʈ
//4. Ÿ��		
//5. ������
//6. �̺�Ʈ

	//cCharacterTest* m_pCharacterTest;





public:
	cWonderLand();
	~cWonderLand();

	//void Setup(char* szFolder, char* szFile);
	void Setup();
	void Update();
	void Render(LPD3DXSPRITE pSprite);

	void Setup(cCamera* pCamera);

	void ControlCamera();
	void RenderCamera();

};


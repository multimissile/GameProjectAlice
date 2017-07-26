#pragma once
#include "cCamera.h"
#include "cCharacter.h"
#include "cSpriteImage.h"
#include "iMap.h"
#include "cHeightMap.h"
#include "cMeshGroup.h"


class cScene
{
protected:
	D3DXVECTOR3 m_vLookAt;
	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vUp;

	D3DXVECTOR3 m_vRot;
	float m_fCameraDistance;

	//나오는 캐릭터들 저장하는 벡터
	vector<cCharacter*> vecPchar;

	//cBox* m_pBox;
	cSpriteImage* m_pImage;

	//cMapTest* m_pMapTest;
	iMap*	m_pMap;

	cCamera* m_pCamera;


	cMeshGroup* m_pCameraMesh;
public:
	cScene();
	virtual ~cScene();
	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual void Render(LPD3DXSPRITE pSprite) = 0;
};


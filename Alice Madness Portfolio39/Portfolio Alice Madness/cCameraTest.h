#pragma once

/* ī�޶� �׽�Ʈ �ϱ� ���� �����Դϴ�. */

// ī�޶�� ����? ī�޶���ġ�޾Ƽ� ī�޶�׷��ٱ�?
class cBox;
class cSpriteImage;


class cCharacterTest;
class cMapTest;
class cCamera;
class cMeshGroup;


class cCameraTest
{

	//RECT m_rcTest;
	D3DXVECTOR3 m_vLookAt;
	D3DXVECTOR3 m_vEye;
	D3DXVECTOR3 m_vUp;

	D3DXVECTOR3 m_vRot;
	float m_fCameraDistance;

	//cBox* m_pBox;
	cSpriteImage* m_pImage;

	cMapTest* m_pMapTest;
	cCharacterTest* m_pCharacterTest;

	cCamera* m_pCamera;


	cMeshGroup* m_pCameraMesh;

	


public:
	cCameraTest();
	~cCameraTest();

	void Setup(cCamera* pCamera);
	void Update();
	void Render(LPD3DXSPRITE pSprite);

	void ControlTestCamera();
	void RenderCamera();
};


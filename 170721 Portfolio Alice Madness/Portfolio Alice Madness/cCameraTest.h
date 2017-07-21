#pragma once

/* 카메라를 테스트 하기 위한 공간입니다. */




class cCameraTest
{

	RECT m_rcTest;


public:
	cCameraTest();
	~cCameraTest();

	void Setup();
	void Update();
	void Render();
};


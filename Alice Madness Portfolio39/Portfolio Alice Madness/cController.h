#pragma once

/* 버튼입니다 */

//미완

enum CONTROLLER_TYPE;

class cController
{
	enum BUTTON_STATE
	{
		BUTTON_NONE,
		BUTTON_PROBE,
		BUTTON_CLICK,
		BUTTON_NUM
	};

public:
	cController();
	~cController();

private:
	BUTTON_STATE m_enButtonState;
	CONTROLLER_TYPE m_enType;

	

};

enum CONTROLLER_TYPE
{
	CONTROLLER_BACK,
	CONTROLLER_SELECT,
	CONTROLLER_DELETE,
	CONTROLLER_NUM
};


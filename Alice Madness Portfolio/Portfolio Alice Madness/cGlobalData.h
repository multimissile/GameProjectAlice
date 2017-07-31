#pragma once

#define g_pGlobalData cGlobalData::GetInstance()


class cGlobalData
{
	SINGLETON(cGlobalData);

public:

private:
	int m_nToothNum;




public:
	inline void AddTooth() {m_nToothNum++;}
	inline int GetToothNum() { return m_nToothNum; }


public:
	void TestRender();

};


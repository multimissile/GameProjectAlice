#pragma once

/* е╦юс */

#define g_pTimeManager cTimeManager::GetInstance()

class cTimeManager
{
private:
	SINGLETON(cTimeManager);

private:
	DWORD m_dwLastUpdateTime;
	float m_fEllapsedTime;
	DWORD m_dwFrameCount;
	float m_fFrameTime;

	SYNTHESIZE(DWORD, m_dwFPS, FPS);

public:
	void Update();
	float GetElapsedTime();
	float GetLastUpdateTime();
};


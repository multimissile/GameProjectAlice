#include "stdafx.h"
#include "cTimeManager.h"


cTimeManager::cTimeManager()
	: m_dwFPS(0)
	, m_dwFrameCount(0)
	, m_fFrameTime(0.f)
{
	m_dwLastUpdateTime = GetTickCount();
}


cTimeManager::~cTimeManager()
{

}

void cTimeManager::Update()
{
	DWORD dwCurrentTime = GetTickCount();
	m_fEllapsedTime = (dwCurrentTime - m_dwLastUpdateTime) / 1000.f;
	m_dwLastUpdateTime = dwCurrentTime;

	m_fFrameTime += m_fEllapsedTime;
	++m_dwFrameCount;

	while (m_fFrameTime > 1.0f)	
	{
		m_fFrameTime -= 1.0f;
		m_dwFPS = m_dwFrameCount;
		m_dwFrameCount = 0;
	}

}

float cTimeManager::GetElapsedTime()
{
	return m_fEllapsedTime;
}

float cTimeManager::GetLastUpdateTime()
{
	return 0.0f;
}

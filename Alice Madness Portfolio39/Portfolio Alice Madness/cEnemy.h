#pragma once


class cEnemy
{
protected:
	D3DXVECTOR3 m_vPosition;		//적 위치
	D3DXVECTOR3 m_vDirection;			//적 방향
	D3DXMATRIXA16 m_matWorld;

	float m_fRotY;
	double maxTime;		//프레임 전부 도는데 걸리는 시간
	double nowTime;		//현재 프레임까지 걸린 시간
public:
	cEnemy();
	virtual ~cEnemy();

	virtual void Setup(float _x, float _y, float _z) = 0;
	virtual void Setup() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;

};


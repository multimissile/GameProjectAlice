#pragma once


class cEnemy
{
protected:
	D3DXVECTOR3 m_vPosition;		//�� ��ġ
	D3DXVECTOR3 m_vDirection;			//�� ����
	D3DXMATRIXA16 m_matWorld;

	float m_fRotY;
	double maxTime;		//������ ���� ���µ� �ɸ��� �ð�
	double nowTime;		//���� �����ӱ��� �ɸ� �ð�
public:
	cEnemy();
	virtual ~cEnemy();

	virtual void Setup(float _x, float _y, float _z) = 0;
	virtual void Setup() = 0;
	virtual void Render() = 0;
	virtual void Update() = 0;

};


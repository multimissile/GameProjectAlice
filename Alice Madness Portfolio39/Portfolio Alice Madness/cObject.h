#pragma once

//game�� �� ��� ��ü���� ��ӹ��� Ŭ����


class cBounding;

class cObject 
{

protected:
	bool m_bExist;

	cBounding* m_pBounding;

	D3DXVECTOR3 m_vPosition;
	float m_fRotationY;
	
	D3DXMATRIX m_matWorld;

public:
	cObject();
	virtual ~cObject();

	virtual void Setup(char* szFolder, char* szFile, float scale = 0.03f) = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;

	cBounding* GetBounding();

	virtual void Destroy();	//�װų� ���� �� ���Ϳ��� ������ �ʰ� �׳� �ξ��� �ѹ��� ���� ��
							//new �ߴ� �ֵ��� �̸� ó���� �� �ֵ��� �̰���./
	void SetExistFalse();
	


};



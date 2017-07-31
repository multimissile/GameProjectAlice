#pragma once

//game에 들어갈 모든 객체들이 상속받을 클래스


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

	virtual void Destroy();	//죽거나 했을 때 벡터에서 지우지 않고 그냥 두었다 한번에 지울 때
							//new 했던 애들은 미리 처리할 수 있도록 이것을./
	void SetExistFalse();
	


};



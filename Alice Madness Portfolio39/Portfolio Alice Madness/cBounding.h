#pragma once


//미완


class cBoundingSphere;
class cBoundingBox;

class cBounding
{
protected:

	enum BOUNDING_TYPE
	{
		BOUNDING_BOX,
		BOUNDING_SPHERE,
		BOUNDING_NUM
	};

	BOUNDING_TYPE m_enType;

	D3DXVECTOR3 m_vOrgCenterPos;	//원래 객체의 중심 위치	
	D3DXVECTOR3 m_vCenterPos;

	float m_fBoundingRadius;		//바운딩박스타입이라면 체크하기 전에 먼저 체크해야 하는 것(바운딩박스를 모두 감싸는 원의 반지름)
									//컬링에 사용될 바운딩 스피어 
	
	//테스트용으로만 필요
	D3DXMATRIX m_matWorldTM;



public:
	cBounding();
	virtual ~cBounding();

	//충돌체크 검사하는
	static bool CheckCollision(cBounding* pB, vector<cBounding*> vecPB);

	static bool IntersectSphereBox(cBoundingSphere* pBSphere, cBoundingBox* pBBox);
	static bool IntersectSphereSphere(cBoundingSphere* pBSphere1, cBoundingSphere* pBSphere2);
	static bool IntersectBoxBox(cBoundingBox* pBBox1, cBoundingBox* pBBox2);
	
	//예정
	static bool InVecPlane(cBounding* pB, vector<LPD3DXPLANE> vecPlane);
	static bool SphereInPlane(cBoundingSphere* pB, LPD3DXPLANE  plane);
	static bool BoxInPlane(cBoundingBox* pB, LPD3DXPLANE  plane);

	inline D3DXVECTOR3& GetCenterPosition() { return m_vCenterPos; }

	//예정
	virtual void ResetBounding();

	virtual void Update(D3DXMATRIX* pmatWorld);

	virtual void OBBBox_Render() = 0;

	inline void SetBoundingRadius(float fRadius) { m_fBoundingRadius = fRadius; };
	inline float GetBoundingRadius() { return m_fBoundingRadius; }
};

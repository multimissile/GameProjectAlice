#pragma once


//�̿�


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

	D3DXVECTOR3 m_vOrgCenterPos;	//���� ��ü�� �߽� ��ġ	
	D3DXVECTOR3 m_vCenterPos;

	float m_fBoundingRadius;		//�ٿ���ڽ�Ÿ���̶�� üũ�ϱ� ���� ���� üũ�ؾ� �ϴ� ��(�ٿ���ڽ��� ��� ���δ� ���� ������)
									//�ø��� ���� �ٿ�� ���Ǿ� 
	
	//�׽�Ʈ�����θ� �ʿ�
	D3DXMATRIX m_matWorldTM;



public:
	cBounding();
	virtual ~cBounding();

	//�浹üũ �˻��ϴ�
	static bool CheckCollision(cBounding* pB, vector<cBounding*> vecPB);

	static bool IntersectSphereBox(cBoundingSphere* pBSphere, cBoundingBox* pBBox);
	static bool IntersectSphereSphere(cBoundingSphere* pBSphere1, cBoundingSphere* pBSphere2);
	static bool IntersectBoxBox(cBoundingBox* pBBox1, cBoundingBox* pBBox2);
	
	//����
	static bool InVecPlane(cBounding* pB, vector<LPD3DXPLANE> vecPlane);
	static bool SphereInPlane(cBoundingSphere* pB, LPD3DXPLANE  plane);
	static bool BoxInPlane(cBoundingBox* pB, LPD3DXPLANE  plane);

	inline D3DXVECTOR3& GetCenterPosition() { return m_vCenterPos; }

	//����
	virtual void ResetBounding();

	virtual void Update(D3DXMATRIX* pmatWorld);

	virtual void OBBBox_Render() = 0;

	inline void SetBoundingRadius(float fRadius) { m_fBoundingRadius = fRadius; };
	inline float GetBoundingRadius() { return m_fBoundingRadius; }
};

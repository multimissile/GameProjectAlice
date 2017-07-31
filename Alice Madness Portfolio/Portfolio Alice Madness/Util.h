#pragma once

/* 여기저기에서 사용할 각종 */

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;
	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };
	ST_PC_VERTEX() {}
	ST_PC_VERTEX(D3DXVECTOR3 p, D3DCOLOR c) :p(p), c(c) {}
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2 t;
	enum {FVF = D3DFVF_XYZ | D3DFVF_TEX1};
	ST_PT_VERTEX(D3DXVECTOR3 v, D3DXVECTOR2 t):p(p),t(t){}
	ST_PT_VERTEX(){}
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3	n;
	D3DXVECTOR2 t;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 };
};


struct ST_PN_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3	n;
	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL };
};


//EPSILON 
#define EPSILON 0.0001f

namespace Util
{
	//Equal
	inline bool Equal(float a, float b)
	{
		return (fabs((float)a - (float)b) < EPSILON);
	}
	//포인트 비교 함수
	inline bool operator==(POINT pt1, POINT pt2)
	{
		return (pt1.x == pt2.x && pt1.y == pt2.y);
	}
	inline bool operator!=(POINT pt1, POINT pt2)
	{
		return !(pt1 == pt2);
	}

}
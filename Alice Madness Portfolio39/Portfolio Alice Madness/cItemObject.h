#pragma once



#include "cObject.h"

class cItemObject : public cObject
{
private:
	cMeshGroup* m_pMeshGroup;


	
	enum ITEM_STATE
	{
		ITEM_NEW,
		ITEM_END,
		ITEM_STAY,
		ITEM_NUM
	};
	
	ITEM_STATE m_enState;

public:
	cItemObject* m_pNext;


	cItemObject();
	~cItemObject();

	void AddGlobalAndDelete();

	void Setup( char* szFolder,  char* szFile, float scale = 0.03f);
	void Update();
	void Render();

	//테스트용
	void SetPosition(D3DXVECTOR3 vPosition) { m_vPosition = vPosition; }
};


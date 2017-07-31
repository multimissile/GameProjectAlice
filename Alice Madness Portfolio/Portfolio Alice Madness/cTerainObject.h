#pragma once

#include "cObject.h"

class cMeshGroup;


class cTerainObject : public cObject
{

	cMeshGroup* m_pMeshGroup;




public:
	cTerainObject();
	~cTerainObject();

	void Setup( char* szFolder,  char* szFile, float scale = 0.03f);
	void Update();
	void Render();

	//юс╫ц 
	void SetPosition(D3DXVECTOR3 vPosition) { m_vPosition = vPosition; }

};


#pragma once

//class cMeshGroup;
class cHeightMap;


class cMapTest
{
	//cMeshGroup* m_pMeshGroup;
	cHeightMap* m_pHeightMap;

public:
	cMapTest();
	~cMapTest();

	void Setup();
	void Render();
	void Update();

};


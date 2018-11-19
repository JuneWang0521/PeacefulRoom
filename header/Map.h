#pragma once   

#include "Headers.h"

class Map
{
protected:
	static	Map * m_pMap;
	int m_iBGposition;
	int m_ifridge;
	int m_iTv;
	int m_iMapWidth;


public:
	Map();
	~Map(){}

	static    Map* GetMap() { return m_pMap; }
	int GetBGposition() { return m_iBGposition; }
	void SetBGposition(int BGposition) { m_iBGposition = BGposition ; }
	int GetMapWidth(){return m_iMapWidth;}
	void SetMapWidth(int MapWidth) { m_iMapWidth = MapWidth; }
};

BOOL MapInitial();
#pragma once   

#include "Headers.h"

class Map
{
protected:
	static	Map * m_pMap;
	int m_iBGposition;
	int m_ifridge;
	int m_iTv;

public:
	Map();
	~Map(){}

	static    Map* GetMap() { return m_pMap; }
	int GetBGposition() { return m_iBGposition; }
	void SetBGposition(int BGposition) { m_iBGposition = BGposition ; }
};

BOOL MapInitial();
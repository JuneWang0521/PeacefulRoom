#include "Headers.h"
#include "Map.h"

Map::Map()
{
	m_pMap = this;
	m_iBGposition = 0;
	m_ifridge=0;
	m_iTv=0;
	m_iMapW = 1600;
}

BOOL MapInitial()
{
	Map *g_pMap = new Map();
	if (g_pMap == NULL)
		return FALSE;
	return TRUE;
}

#include "Headers.h"
#include "Map.h"
#include "GameEngine.h"
#include "Character.h"

Map::Map()
{
	m_pMap = this;
	m_iBGposition = 0;
	m_ifridge=0;
	m_iTv=0;
	m_iMapWidth = 1600;
}

void Map::MapMove() 
{
	if (GameEngine::GetEngine()->GetCharacterNoMove() == FALSE || ((KEYDOWN(65) || KEYDOWN(97)) && (KEYDOWN(68) || KEYDOWN(100))))  //����ɶ���ͼ���ɶ�(ps:��˫��ͬʱ���µ�BUG)
	{
		m_iBGposition = m_iBGposition;
	}
	else if (GameEngine::GetEngine()->GetCharacterNoMove() ==TRUE && (KEYDOWN(65) || KEYDOWN(97))) //��ͼ����
	{
		m_iBGposition -= 10;
	}
	else if(GameEngine::GetEngine()->GetCharacterNoMove() == TRUE && (KEYDOWN(68) || KEYDOWN(100))) //��ͼ����
	{
		m_iBGposition += 10;
	}
}

BOOL MapInitial()
{
	Map *g_pMap = new Map();
	if (g_pMap == NULL)
		return FALSE;
	return TRUE;
}

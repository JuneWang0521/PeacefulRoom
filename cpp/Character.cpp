#include "Headers.h"
#include "Character.h"

Character::Character()
{
	m_pCharacter = this;
	m_iCx = 0, m_iCy = 0;
	m_iHappy = 0;
	m_iEat = 0;
	m_iStayTime=0;
	m_iDirection = 0;
	m_iCvy = 0;
	m_iPicNum = 0;
}

//BOOL Character::LoadFile()		//加载角色存档（李俊虎编）
//{
//	
//}

void Character::CharacterHappy()
{
	m_iHappy+=HAPPY;
	if(m_iHappy>100)//防止Happy超过上限
		m_iHappy=100;

}

void Character::CharacterEat()
{
	m_iEat+=EAT;
	if(m_iEat>100)//防止Eat超过上限
		m_iEat=100;

}

void Character::CharacterAI()
{
	//if(m_iStayTime>10000)
	//{
	//	if(m_iHappy<30)	//不快乐了
	//	{
	//		if(m_iCx<)	//角色在电视的左边
	//			m_iCx+=;
	//		if(m_iCx>)
	//			m_iCx-=;//角色在电视的右边
	//	}
	//	if(m_iEat<30)	//饿了
	//	{
	//		if(m_iCx<)	//角色在冰箱的左边
	//			m_iCx+=;
	//		if(m_iCx>)
	//			m_iCx-=;//角色在冰箱的右边
	//	}	
	//}
}

BOOL CharacterInitial()
{
	Character *g_pCharacter = new Character();
	if (g_pCharacter == NULL)
		return FALSE;
	return TRUE;
}
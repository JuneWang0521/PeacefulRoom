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

//BOOL Character::LoadFile()		//���ؽ�ɫ�浵������ࣩ
//{
//	
//}

void Character::CharacterHappy()
{
	m_iHappy+=HAPPY;
	if(m_iHappy>100)//��ֹHappy��������
		m_iHappy=100;

}

void Character::CharacterEat()
{
	m_iEat+=EAT;
	if(m_iEat>100)//��ֹEat��������
		m_iEat=100;

}

void Character::CharacterAI()
{
	//if(m_iStayTime>10000)
	//{
	//	if(m_iHappy<30)	//��������
	//	{
	//		if(m_iCx<)	//��ɫ�ڵ��ӵ����
	//			m_iCx+=;
	//		if(m_iCx>)
	//			m_iCx-=;//��ɫ�ڵ��ӵ��ұ�
	//	}
	//	if(m_iEat<30)	//����
	//	{
	//		if(m_iCx<)	//��ɫ�ڱ�������
	//			m_iCx+=;
	//		if(m_iCx>)
	//			m_iCx-=;//��ɫ�ڱ�����ұ�
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
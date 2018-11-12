#pragma once   

#include "Headers.h"

class Character
{
protected:
	static Character * m_pCharacter;		//ָ�������ָ�룬�ṩ�����������
	int m_iCx, m_iCy;		//��ɫ����
	int m_iCvy;	//��ɫ�ٶ�
	int m_iHappy;		//��ɫ����ֵ
	int m_iEat;		//��ɫ��ʳ��
	int m_iStayTime;
	int m_iDirection;		//��ɫ����
	int m_iPicNum;
	int sahjndkls;

public:
	Character();
	~Character() {}

	//���ʷ���
	static Character* GetCharacter() { return m_pCharacter; }	
	int GetCx() { return m_iCx; }
	void	SetCx(int x) { m_iCx = x; }
	int GetCy() { return m_iCy; }
	void	SetCy(int y) { m_iCy = y; }
	int GetCvy() { return m_iCvy; }
	void	SetCvy(int Cvy) { m_iCvy = Cvy; }
	int GetHappy()	{return m_iHappy;}
	void	SetHappy(int Happy)	{m_iHappy=Happy;}
	int GetEat()	{return m_iEat;}
	void	SetEat(int Eat)	{m_iEat=Eat;}
	int GetDirection() { return m_iDirection; }
	void	SetDirection(int Direction) { m_iDirection = Direction; }
	int GetPicNum() { return m_iPicNum; }
	void	SetPicNum(int PicNum) { m_iPicNum = PicNum; }

	//��ɫ����
	//BOOL LoadFile();	//���ؽ�ɫ�浵�������
	void	CharacterHappy();
	void	CharacterEat();	
	void	CharacterAI();

};
BOOL CharacterInitial();
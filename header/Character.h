#pragma once   

#include "Headers.h"

class Character
{
protected:
	static Character * m_pCharacter;		//指向自身的指针，提供程序的外界访问
	int m_iCx, m_iCy;		//角色坐标
	int m_iCvy;	//角色速度
	int m_iHappy;		//角色心情值
	int m_iEat;		//角色饱食度
	int m_iStayTime;
	int m_iDirection;		//角色方向
	int m_iPicNum;
	int sahjndkls;

public:
	Character();
	~Character() {}

	//访问方法
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

	//角色方法
	//BOOL LoadFile();	//加载角色存档（李俊虎）
	void	CharacterHappy();
	void	CharacterEat();	
	void	CharacterAI();

};
BOOL CharacterInitial();
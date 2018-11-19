#include "Headers.h"
#include "Character.h"
#include "GameEngine.h"
#include "Map.h"


Character::Character()
{
	m_pCharacter = this;
	m_iCx = 322, m_iCy = 419;
	m_iHappy = 0;
	m_iEat = 0;
	m_iStayTime=0;
	m_iDirection = 1;
	m_iCvy = 0;
	m_iPicNum = 0;

}

//BOOL Character::LoadFile()		//加载角色存档（李俊虎编）
//{
//	
//}

void Character::CharacterJump()
{
	bool IsLeaping;

	m_iCy -= m_iCvy;

	if (m_iCy <= 0)
	{
		m_iCvy = -m_iCvy;
		m_iCy = 0;
	}

	//如果初速度发生了变化
	if (IsLeaping = true)
	{
		m_iCvy -= GRAVITY;//模拟初速度受重力影响


		//接触地面之后，初速度归0。
		if (m_iCy >= 419)
		{
			m_iCy = 419;

			m_iCvy = 0;

			IsLeaping = false;

		}

	}

	//如果按键跳跃，赋予初速度
	if (m_iCy == 419 && KEYDOWN(VK_SPACE))
	{
		m_iCvy = 30;

		IsLeaping = true;

	}
}

void Character::CharacterMove()
{

	// Map::GetMap()->获取Map信息
	int t_iBoundary = Map::GetMap()->GetBGposition();//获取地图的位置。
	int t_iMiddle = 322;

	if (t_iBoundary >= Map::GetMap()->GetMapWidth()-800)//假如角色右侧到达边界
	{

		//角色在中轴线以右，向右移动
		if (m_iCx>= t_iMiddle && (KEYDOWN(68)||KEYDOWN(100)))
		{
			if ((m_iCx += SPEED) >WINDOW_WIDTH-110)
			{
				m_iCx = WINDOW_WIDTH-110;
			}
		}

		//角色在中轴线以右，向左移动，但未过中位线
		 if(m_iCx >= t_iMiddle &&(KEYDOWN(65)||KEYDOWN(97)))
		{
			if (m_iCx - SPEED > t_iMiddle)
			{
				m_iCx -= SPEED;
			
			}
			else
			{
				m_iCx = t_iMiddle;
				
				GameEngine::GetEngine()->SetCharacterNoMove(TRUE);


			}
		}
	}
	
	//2018.11.12 complete
	if(t_iBoundary==0)//假如角色左侧到达边界
	{

		//角色在中轴线以左，向左移动。
		if (m_iCx <= t_iMiddle && (KEYDOWN(65) || KEYDOWN(97)))
		{
			if ((m_iCx -= SPEED) < 0)
			{
				m_iCx = 0;
			}
		}

		//角色在中轴线以左，向右移动，但未过中轴线。
		if (m_iCx <= t_iMiddle && (KEYDOWN(68) || KEYDOWN(100)))
		{
			if((m_iCx + SPEED)< t_iMiddle) // 预判向右移动的时候是否过中位线
			{
				m_iCx += SPEED;
		
			}
			else {
				m_iCx = t_iMiddle;
				GameEngine::GetEngine()->SetCharacterNoMove(TRUE);      //这里已经经过了中位线
				
			}
		}
		
	}

}


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
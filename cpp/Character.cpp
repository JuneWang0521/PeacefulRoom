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

//BOOL Character::LoadFile()		//���ؽ�ɫ�浵������ࣩ
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

	//������ٶȷ����˱仯
	if (IsLeaping = true)
	{
		m_iCvy -= GRAVITY;//ģ����ٶ�������Ӱ��


		//�Ӵ�����֮�󣬳��ٶȹ�0��
		if (m_iCy >= 419)
		{
			m_iCy = 419;

			m_iCvy = 0;

			IsLeaping = false;

		}

	}

	//���������Ծ��������ٶ�
	if (m_iCy == 419 && KEYDOWN(VK_SPACE))
	{
		m_iCvy = 30;

		IsLeaping = true;

	}
}

void Character::CharacterMove()
{

	// Map::GetMap()->��ȡMap��Ϣ
	int t_iBoundary = Map::GetMap()->GetBGposition();//��ȡ��ͼ��λ�á�
	int t_iMiddle = 322;

	if (t_iBoundary >= Map::GetMap()->GetMapWidth()-800)//�����ɫ�Ҳൽ��߽�
	{

		//��ɫ�����������ң������ƶ�
		if (m_iCx>= t_iMiddle && (KEYDOWN(68)||KEYDOWN(100)))
		{
			if ((m_iCx += SPEED) >WINDOW_WIDTH-110)
			{
				m_iCx = WINDOW_WIDTH-110;
			}
		}

		//��ɫ�����������ң������ƶ�����δ����λ��
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
	if(t_iBoundary==0)//�����ɫ��ൽ��߽�
	{

		//��ɫ�����������������ƶ���
		if (m_iCx <= t_iMiddle && (KEYDOWN(65) || KEYDOWN(97)))
		{
			if ((m_iCx -= SPEED) < 0)
			{
				m_iCx = 0;
			}
		}

		//��ɫ�����������������ƶ�����δ�������ߡ�
		if (m_iCx <= t_iMiddle && (KEYDOWN(68) || KEYDOWN(100)))
		{
			if((m_iCx + SPEED)< t_iMiddle) // Ԥ�������ƶ���ʱ���Ƿ����λ��
			{
				m_iCx += SPEED;
		
			}
			else {
				m_iCx = t_iMiddle;
				GameEngine::GetEngine()->SetCharacterNoMove(TRUE);      //�����Ѿ���������λ��
				
			}
		}
		
	}

}


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
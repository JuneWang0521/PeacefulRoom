#pragma once   

#include "Headers.h"

class GameEngine 
{
protected:
	static GameEngine * m_pGameEngine;         //ָ�������ָ�룬�ṩ�����������
	HINSTANCE         m_hInstance;             //ʵ�����
	HWND              m_hWnd;                  //���ھ��
	TCHAR             m_szWindowClass[32];     //��������
	TCHAR             m_szWndTitle[32];        //���ڱ���
	HBITMAP			m_hBmp;		//λͼ����
	HDC		m_hdc, m_mdc, m_bufdc;		//���ػ���
	HBITMAP m_hBackGround;		//��ͼ�ز�����
	HBITMAP m_hCharacter[2];
	DWORD m_tPre, m_tNow;	//��ʱ��ϵ
	BOOL m_bCharacterNoMove;
public:
	//������Ϸ����ʵ��
	GameEngine(HINSTANCE hInstance, LPTSTR szWindowClass,LPTSTR szTitle);	
	~GameEngine() {}

	//���ʷ���
	static    GameEngine* GetEngine() { return m_pGameEngine; }	
	HINSTANCE GetInstance() { return m_hInstance; }
	HWND		GetWnd() { return m_hWnd; }
	void		SetWnd(HWND hWnd) { m_hWnd = hWnd; }
	LPTSTR    GetTitle() { return m_szWndTitle; }
	DWORD	GetPreTime() { return m_tPre; }
	void		SetPreTime(DWORD tPre) {m_tPre=tPre; }
	DWORD	GetNowTime() { return m_tNow; }
	void		SetNowTime(DWORD tNow) { m_tNow = tNow; }

	//���ڴ���
	BOOL	Initiallize(int cmdShow);	//��ʼ������
	LRESULT GameEngine::HandleEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);	//��Ϣ����
	BOOL GameInit();

	//��Ϸ���
	void TripleBuffering();		//�������ػ���
	void BitmapInit();		//λͼ����
	void GameMain();
	void GameClear();
};

BOOL GameEngineInitial(HINSTANCE hInstance)
{
	GameEngine *g_pGame = new GameEngine(hInstance, L"WindowClass", WINDOW_TITLE);
	if (g_pGame == NULL)
		return FALSE;
	return TRUE;
}
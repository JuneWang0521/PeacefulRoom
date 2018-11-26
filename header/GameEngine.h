#pragma once   

#include "Headers.h"

class GameEngine 
{
protected:
	static GameEngine * m_pGameEngine;         //指向自身的指针，提供程序的外界访问
	HINSTANCE         m_hInstance;             //实例句柄
	HWND              m_hWnd;                  //窗口句柄
	TCHAR             m_szWindowClass[32];     //窗口类名
	TCHAR             m_szWndTitle[32];        //窗口标题
	HBITMAP			m_hBmp;		//位图对象
	HDC		m_hdc, m_mdc, m_bufdc;		//三重缓冲
	HBITMAP m_hBackGround;		//贴图素材声明
	HBITMAP m_hCharacter[2];
	DWORD m_tPre, m_tNow;	//总时间系
	DWORD m_tCharcterPre;   //角色单独的时间系
	BOOL m_bCharacterNoMove;
	int m_iColor;

public:
	//创建游戏引擎实例
	GameEngine(HINSTANCE hInstance, LPTSTR szWindowClass,LPTSTR szTitle);	
	~GameEngine() {}

	//访问方法
	static    GameEngine* GetEngine() { return m_pGameEngine; }	
	HINSTANCE GetInstance() { return m_hInstance; }
	HWND		GetWnd() { return m_hWnd; }
	void		SetWnd(HWND hWnd) { m_hWnd = hWnd; }
	LPTSTR    GetTitle() { return m_szWndTitle; }
	DWORD	GetPreTime() { return m_tPre; }
	void		SetPreTime(DWORD tPre) {m_tPre=tPre; }
	DWORD	GetNowTime() { return m_tNow; }
	void		SetNowTime(DWORD tNow) { m_tNow = tNow; }
	DWORD   GetCharacterPre() {return m_tCharcterPre;}
	void		SetCharacterPre(DWORD CharacterPre) { m_tCharcterPre=CharacterPre; }
	int		GetColor() { return m_iColor; }
	void		SetColor(int Color) { m_iColor = Color; }

	void   SetCharacterNoMove(BOOL CharacterNoMove) { m_bCharacterNoMove= CharacterNoMove; }
	bool   GetCharacterNoMove() { return m_bCharacterNoMove; }

	//窗口创建
	BOOL	Initiallize(int cmdShow);	//初始化函数
	LRESULT GameEngine::HandleEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);	//消息处理
	BOOL GameInit();

	//游戏相关
	void TripleBuffering();		//设置三重缓冲
	void BitmapInit();		//位图加载
	void GameMain();
	void GameClear();
};


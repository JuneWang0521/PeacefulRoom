#include "Headers.h"
#include "GameEngine.h"
#include "Map.h"
#include "Character.h"

GameEngine* GameEngine::m_pGameEngine = NULL;
Map*Map::m_pMap = NULL;
Character*Character::m_pCharacter = NULL;

BOOL GameEngineInitial(HINSTANCE hInstance)
{
	GameEngine *g_pGame = new GameEngine(hInstance, L"WindowClass", WINDOW_TITLE);
	if (g_pGame == NULL)
		return FALSE;
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hpreInstance, LPSTR lpcmdline, int nShowCmd)
{
	MSG msg;

	if (!GameEngineInitial(hInstance))//创建GameEngine类对象
		return 0;

	if (!MapInitial())//创建GameEngine类对象
		return 0;

	if (!CharacterInitial())//创建GameEngine类对象
		return 0;

	if (!GameEngine::GetEngine()->Initiallize(SW_SHOWNORMAL))//对窗口类对象wndclass进行赋值并注册,创建窗口
		return 0;

	if (!GameEngine::GetEngine()->GameInit())
	{
		MessageBox(GameEngine::GetEngine()->GetWnd(), L"游戏资源加载失败", L"消息窗口", 0); //使用MessageBox函数，创建一个消息窗口
		return 0;
	}

	ZeroMemory(&msg, sizeof(msg)); //用零填充内存域

	while (msg.message != WM_QUIT)		//使用while循环，如果消息不是WM_QUIT消息，就继续循环
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //查看应用程序消息队列，有消息时将队列中的消息派发出去。
		{
			TranslateMessage(&msg);		//将虚拟键消息转换为字符消息
			DispatchMessage(&msg);			//分发一个消息给窗口程序。
		}
		else
		{
			GameEngine::GetEngine()->SetNowTime(GetTickCount());
			if (GameEngine::GetEngine()->GetNowTime() - GameEngine::GetEngine()->GetPreTime() > 17)		//设定动画帧数
				GameEngine::GetEngine()->GameMain();
		}
	}

	UnregisterClass(L"ForTheDreamOfGameDevelop", GameEngine::GetEngine()->GetInstance());//程序准备结束，注销窗口类

	return 0;
}

GameEngine::GameEngine(HINSTANCE hInstance, LPTSTR szWindowClass, LPTSTR szTitle)
{
	m_pGameEngine = this;
	m_hInstance = hInstance;
	m_hWnd = NULL;
	if (lstrlen(szWindowClass)>0)
		lstrcpy(m_szWindowClass, szWindowClass);
	if (lstrlen(szTitle)>0)
		lstrcpy(m_szWndTitle, szTitle);
	m_hdc = NULL;
	m_mdc = NULL ;
	m_bufdc = NULL;
	m_iColor =  0 ;
	m_tPre = GetTickCount(), m_tNow = GetTickCount();
	m_tCharcterPre = GetTickCount();
	m_bCharacterNoMove = false; //默认使地图卷轴移动
}

LRESULT GameEngine::HandleEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SYSCOMMAND:		//使最大化失效
		if (wParam == SC_MAXIMIZE)
			return 0;
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(m_hWnd);
			PostQuitMessage(0);
			break;
		}
		break;

	case WM_DESTROY:
		GameClear();
		PostQuitMessage(0);
		return 0;
	}

	return ::DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return GameEngine::GetEngine()->HandleEvent(hWnd, msg, wParam, lParam);
}

BOOL GameEngine::Initiallize(int cmdShow)
{
	static WNDCLASSEX wndclass;
	wndclass.cbSize = sizeof(WNDCLASSEX);			//设置结构体的字节数大小
	wndclass.style = CS_HREDRAW | CS_VREDRAW;	//设置窗口的样式
	wndclass.lpfnWndProc = WndProc;					//设置指向窗口过程函数的指针
	wndclass.cbClsExtra = 0;								//窗口类的附加内存
	wndclass.cbWndExtra = 0;							//窗口的附加内存
	wndclass.hInstance = m_hInstance;					//指定包含窗口过程的程序的实例句柄。
	wndclass.hIcon = (HICON)::LoadImage(NULL, L"woodhouse.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //本地加载自定义ico图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);    //指定窗口类的光标句柄。
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);  //为hbrBackground成员指定一个灰色画刷句柄	
	wndclass.lpszMenuName = NULL;						//用一个以空终止的字符串，指定菜单资源的名字。
	wndclass.lpszClassName = m_szWindowClass;	//用m_szWindowClass字符串，指定窗口类的名字。

	if (!RegisterClassEx(&wndclass))
		return FALSE;

	m_hWnd = CreateWindow(m_szWindowClass, m_szWndTitle,				//创建窗口函数CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, m_hInstance, NULL);

	MoveWindow(m_hWnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, true);		//调整窗口显示时的位置，使窗口左上角位于（250,80）处
	ShowWindow(m_hWnd, cmdShow);    //调用ShowWindow函数来显示窗口
	UpdateWindow(m_hWnd);			//对窗口进行更新

	return TRUE;
}

BOOL GameEngine::GameInit()
{
	//设置三重缓冲
	TripleBuffering();		
	//位图加载
	BitmapInit();
	//绘图
	GameMain();
	m_tCharcterPre = GetTickCount();
	return TRUE;
}

void GameEngine::TripleBuffering()
{
	m_hdc = GetDC(m_hWnd);
	m_mdc = CreateCompatibleDC(m_hdc);  //创建一个和hdc兼容的内存DC
	m_bufdc = CreateCompatibleDC(m_hdc);//再创建一个和hdc兼容的缓冲DC
	m_hBmp = CreateCompatibleBitmap(m_hdc, WINDOW_WIDTH, WINDOW_HEIGHT); //建一个和窗口兼容的空的位图对象

	SelectObject(m_mdc, m_hBmp);		//将空位图对象放到mdc中
}

void GameEngine::BitmapInit()
{
	m_hBackGround = (HBITMAP)LoadImage(NULL, L"bg2.bmp", IMAGE_BITMAP,1600, WINDOW_HEIGHT, LR_LOADFROMFILE);
	m_hCharacter[0] = (HBITMAP)LoadImage(NULL, L"1.bmp", IMAGE_BITMAP, 500, 150, LR_LOADFROMFILE);
	m_hCharacter[1] = (HBITMAP)LoadImage(NULL, L"2.bmp", IMAGE_BITMAP, 500, 150, LR_LOADFROMFILE);
}

void GameEngine::GameMain()
{
	SelectObject(m_bufdc, m_hBackGround);
	BitBlt(m_mdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, m_bufdc, Map::GetMap()->GetBGposition(), 0, SRCCOPY);
	
	/*

	在这中间写逻辑代码改变数值，将在下次画时生效

	Character::GetCharacter()->SetCx(100);

	*/

	Character::GetCharacter()->CharacterMove();
	Character::GetCharacter()->CharacterJump();
	Character::GetCharacter()->CharacterDirection();
	Character::GetCharacter()->CharacterMood();
	Character::GetCharacter()->AddFoodandHappy();

	wchar_t str[20] = {};
	HFONT hFont;
	hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, TEXT("微软雅黑"));
	SelectObject(m_mdc, hFont);
	SetBkMode(m_mdc, TRANSPARENT);
	SetTextColor(m_mdc, RGB(m_iColor, 0, 0));

	swprintf_s(str, L"心情值为%d", Character::GetCharacter()->GetHappy());
	TextOut(m_mdc, 0, 0, str, wcslen(str));
	swprintf_s(str, L"饥饿值为%d", Character::GetCharacter()->GetEat());
	TextOut(m_mdc, 0, 30, str, wcslen(str));

	SelectObject(m_bufdc, m_hCharacter[Character::GetCharacter()->GetDirection()]);
	TransparentBlt(m_mdc, Character::GetCharacter()->GetCx(), Character::GetCharacter()->GetCy(), 100, 150, m_bufdc, Character::GetCharacter()->GetPicNum() * 100, 0, 100, 150, RGB(255, 0, 0));

	BitBlt(m_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, m_mdc, 0, 0, SRCCOPY);		//贴出所有内容

	m_tPre = GetTickCount();
}

void GameEngine::GameClear()
{
	DeleteObject(m_hBackGround);
	DeleteDC(m_bufdc);
	DeleteDC(m_mdc);
	ReleaseDC(m_hWnd, m_hdc);
}
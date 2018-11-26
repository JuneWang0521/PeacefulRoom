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

	if (!GameEngineInitial(hInstance))//����GameEngine�����
		return 0;

	if (!MapInitial())//����GameEngine�����
		return 0;

	if (!CharacterInitial())//����GameEngine�����
		return 0;

	if (!GameEngine::GetEngine()->Initiallize(SW_SHOWNORMAL))//�Դ��������wndclass���и�ֵ��ע��,��������
		return 0;

	if (!GameEngine::GetEngine()->GameInit())
	{
		MessageBox(GameEngine::GetEngine()->GetWnd(), L"��Ϸ��Դ����ʧ��", L"��Ϣ����", 0); //ʹ��MessageBox����������һ����Ϣ����
		return 0;
	}

	ZeroMemory(&msg, sizeof(msg)); //��������ڴ���

	while (msg.message != WM_QUIT)		//ʹ��whileѭ���������Ϣ����WM_QUIT��Ϣ���ͼ���ѭ��
	{
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))   //�鿴Ӧ�ó�����Ϣ���У�����Ϣʱ�������е���Ϣ�ɷ���ȥ��
		{
			TranslateMessage(&msg);		//���������Ϣת��Ϊ�ַ���Ϣ
			DispatchMessage(&msg);			//�ַ�һ����Ϣ�����ڳ���
		}
		else
		{
			GameEngine::GetEngine()->SetNowTime(GetTickCount());
			if (GameEngine::GetEngine()->GetNowTime() - GameEngine::GetEngine()->GetPreTime() > 17)		//�趨����֡��
				GameEngine::GetEngine()->GameMain();
		}
	}

	UnregisterClass(L"ForTheDreamOfGameDevelop", GameEngine::GetEngine()->GetInstance());//����׼��������ע��������

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
	m_bCharacterNoMove = false; //Ĭ��ʹ��ͼ�����ƶ�
}

LRESULT GameEngine::HandleEvent(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SYSCOMMAND:		//ʹ���ʧЧ
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
	wndclass.cbSize = sizeof(WNDCLASSEX);			//���ýṹ����ֽ�����С
	wndclass.style = CS_HREDRAW | CS_VREDRAW;	//���ô��ڵ���ʽ
	wndclass.lpfnWndProc = WndProc;					//����ָ�򴰿ڹ��̺�����ָ��
	wndclass.cbClsExtra = 0;								//������ĸ����ڴ�
	wndclass.cbWndExtra = 0;							//���ڵĸ����ڴ�
	wndclass.hInstance = m_hInstance;					//ָ���������ڹ��̵ĳ����ʵ�������
	wndclass.hIcon = (HICON)::LoadImage(NULL, L"woodhouse.ico", IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);  //���ؼ����Զ���icoͼ��
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);    //ָ��������Ĺ������
	wndclass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);  //ΪhbrBackground��Աָ��һ����ɫ��ˢ���	
	wndclass.lpszMenuName = NULL;						//��һ���Կ���ֹ���ַ�����ָ���˵���Դ�����֡�
	wndclass.lpszClassName = m_szWindowClass;	//��m_szWindowClass�ַ�����ָ������������֡�

	if (!RegisterClassEx(&wndclass))
		return FALSE;

	m_hWnd = CreateWindow(m_szWindowClass, m_szWndTitle,				//�������ں���CreateWindow
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WINDOW_WIDTH,
		WINDOW_HEIGHT, NULL, NULL, m_hInstance, NULL);

	MoveWindow(m_hWnd, 250, 80, WINDOW_WIDTH, WINDOW_HEIGHT, true);		//����������ʾʱ��λ�ã�ʹ�������Ͻ�λ�ڣ�250,80����
	ShowWindow(m_hWnd, cmdShow);    //����ShowWindow��������ʾ����
	UpdateWindow(m_hWnd);			//�Դ��ڽ��и���

	return TRUE;
}

BOOL GameEngine::GameInit()
{
	//�������ػ���
	TripleBuffering();		
	//λͼ����
	BitmapInit();
	//��ͼ
	GameMain();
	m_tCharcterPre = GetTickCount();
	return TRUE;
}

void GameEngine::TripleBuffering()
{
	m_hdc = GetDC(m_hWnd);
	m_mdc = CreateCompatibleDC(m_hdc);  //����һ����hdc���ݵ��ڴ�DC
	m_bufdc = CreateCompatibleDC(m_hdc);//�ٴ���һ����hdc���ݵĻ���DC
	m_hBmp = CreateCompatibleBitmap(m_hdc, WINDOW_WIDTH, WINDOW_HEIGHT); //��һ���ʹ��ڼ��ݵĿյ�λͼ����

	SelectObject(m_mdc, m_hBmp);		//����λͼ����ŵ�mdc��
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

	�����м�д�߼�����ı���ֵ�������´λ�ʱ��Ч

	Character::GetCharacter()->SetCx(100);

	*/

	Character::GetCharacter()->CharacterMove();
	Character::GetCharacter()->CharacterJump();
	Character::GetCharacter()->CharacterDirection();
	Character::GetCharacter()->CharacterMood();
	Character::GetCharacter()->AddFoodandHappy();

	wchar_t str[20] = {};
	HFONT hFont;
	hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, GB2312_CHARSET, 0, 0, 0, 0, TEXT("΢���ź�"));
	SelectObject(m_mdc, hFont);
	SetBkMode(m_mdc, TRANSPARENT);
	SetTextColor(m_mdc, RGB(m_iColor, 0, 0));

	swprintf_s(str, L"����ֵΪ%d", Character::GetCharacter()->GetHappy());
	TextOut(m_mdc, 0, 0, str, wcslen(str));
	swprintf_s(str, L"����ֵΪ%d", Character::GetCharacter()->GetEat());
	TextOut(m_mdc, 0, 30, str, wcslen(str));

	SelectObject(m_bufdc, m_hCharacter[Character::GetCharacter()->GetDirection()]);
	TransparentBlt(m_mdc, Character::GetCharacter()->GetCx(), Character::GetCharacter()->GetCy(), 100, 150, m_bufdc, Character::GetCharacter()->GetPicNum() * 100, 0, 100, 150, RGB(255, 0, 0));

	BitBlt(m_hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, m_mdc, 0, 0, SRCCOPY);		//������������

	m_tPre = GetTickCount();
}

void GameEngine::GameClear()
{
	DeleteObject(m_hBackGround);
	DeleteDC(m_bufdc);
	DeleteDC(m_mdc);
	ReleaseDC(m_hWnd, m_hdc);
}
#pragma once

//-----------------------------------【预编译文件包含部分】---------------------------------------
//	描述：包含程序所依赖的头文件
//------------------------------------------------------------------------------------------------
#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>//使用swprintf_s函数所需的头文件
#include <math.h>

//-----------------------------------【库文件包含部分】---------------------------------------
//	描述：包含程序所依赖的库文件
//------------------------------------------------------------------------------------------------
#pragma comment(lib,"winmm.lib")	//调用PlaySound函数所需库文件
#pragma  comment(lib,"Msimg32.lib")

//-----------------------------------【全局宏包含部分】---------------------------------------
//	描述：全局宏定义
//------------------------------------------------------------------------------------------------
#define WINDOW_TITLE	L"宁静小屋"	//为窗口标题定义的宏
#define WINDOW_WIDTH	800	//为窗口宽度定义的宏，以方便在此处修改窗口宽度
#define WINDOW_HEIGHT	600	//为窗口高度定义的宏，以方便在此处修改窗口高度
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)	//定义按键按下状态宏
#define KEYUP(vk_code)   ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)	//定义按键非按下状态宏
#define BGMOVESTEPS 10
#define HAPPY 10
#define EAT 10
#define GRAVITY 3
#define SPEED 10
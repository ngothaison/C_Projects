#pragma once
#include <Windows.h>

enum Color
{
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	PURPLE,
	GRAY,
	WHITE,
	LIGHTGRAY,
	LIGHTBLUE,
	LIGHTGREEN,
	LIGHTCYAN,
	LIGHTRED,
	LIGHTPURPLE,
	LIGHTYELLOW,
	LIGHTWHITE
};

void gotoxy(int x, int y);

void clrscr();

void textcolor(WORD color);

void SetBGColor(WORD color);

void delay(int x);


void Nocursortype();

void XoaManHinh();
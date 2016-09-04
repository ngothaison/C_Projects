#include<stdio.h>
#include "ExtendFunctions.h"

#define WIDTH 15
#define HEIGHT 20

char Board[20][15];

void initBoard()//khởi tạo mảng board
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
			Board[i][j] = ' ';
	}
}

void drawBoard()//vex viền và phần bên trong khung
{
	for (int i = 0; i <= HEIGHT + 1; i++)//cộng thêm 1 để tí vẻ mảng Board sao cho vừa khít với khung
	{
		for (int j = 0; j <= WIDTH + 1; j++)
		{
			if ((i == 0 || i == 21) && j > 0 && j < 15 + 1)
				printf("-");
			else if ((j == 0 || j == 16) && i > 0 && i < 20 + 1)
				printf("|");
			else
				printf(" ");
		}
		printf("\n");
	}
}

void drawMapToScreen()//vẽ mảng Board lenn màn hình
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			gotoxy(2 + j, 2 + i);//di chuyển con trỏ vào trong khung, từng dòng 1
			printf("%c", Board[i][j]);
		}
	}
}

void clearBoard()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			gotoxy(2 + j, 2 + i);//di chuyển con trỏ vào trong khung, từng dòng 1
			printf("\0");
		}
	}
}

void resetMap()
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 15; j++)
			Board[i][j] = '\0';
	}
}
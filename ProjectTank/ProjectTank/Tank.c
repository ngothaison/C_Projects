#include "Board.h"
#include "Tank.h"
#include <stdlib.h>

//typedef struct
//{
//	int id;
//	int health;//múa
//	char formArray[3][3];//mảng 2 chiều hình dạng của xe
//	int targetId;//id của mục tiêu 
//	int iBoard;//vị trí i trên Board
//	int jBoard;//vị trí j trên Board
//	int angle;
//	Bullet bullet;
//}Tank;

void initTank(Tank *pTank, int id)
{
	pTank->id = id;
	pTank->health = 5;
	pTank->angle = 0;
	//4 xe bốn góc, 0 laf player
	switch (id)
	{
	case 0:
		pTank->iBoard = 9;
		pTank->jBoard = 7;
		break;
	case 1:
		pTank->iBoard = 17;
		pTank->jBoard = 0;
		break;
	case 2:
		pTank->iBoard = 0;
		pTank->jBoard = 12;
		break;
	case 3:
		pTank->iBoard = 9;
		pTank->jBoard = 0;
		break;
	case 4:
		pTank->iBoard = 14;
		pTank->jBoard = 12;
		break;
	}

	pTank->formArray[0][0] = pTank->formArray[0][1] = 'o';
	pTank->formArray[0][2] = ' ';
	pTank->formArray[1][0] = pTank->formArray[1][1] = ' ';
	pTank->formArray[1][2] = 'o';
	pTank->formArray[2][0] = pTank->formArray[2][1] = 'o';
	pTank->formArray[2][2] = ' ';

	if (id == 0)
	{
		pTank->formArray[1][0] = pTank->formArray[1][1] = 'o';
	}
}

void drawTank(Tank tank)//vẽ tank lên mảng Board và vẽ lên màn hình
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			Board[tank.iBoard + i][tank.jBoard + j] = tank.formArray[i][j];
	}
	//drawMapToScreen();
}

void delTank(Tank tank)//xóa tank lên mảng Board và vẽ lên màn hình
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			Board[tank.iBoard + i][tank.jBoard + j] = ' ';
	}
	//drawMapToScreen();
}

void ronateTank90(Tank *pTank)//xoay tank 1 góc 90
{
	char temp[3][3];

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			temp[3 - j - 1][i] = pTank->formArray[i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			pTank->formArray[i][j] = temp[i][j];
		}
	}

	if (pTank->angle == 270)
		pTank->angle = 0;
	else
	{
		pTank->angle += 90;
	}

	delTank(*pTank);
	drawTank(*pTank);
	//drawTank(*pTank);
}

void goUp(Tank *pTank)
{
	if (pTank->iBoard == 0)
		return;
	if (pTank->angle != 90)//nếu chưa ở góc 90 độ thì quay
	{
		while (pTank->angle != 90)
			ronateTank90(pTank);
		return;
	}
	else//ngược lại thì giảm tọa đọ iBoard của xe
	{
		delTank(*pTank);
		pTank->iBoard--;
		drawTank(*pTank);//vẽ xe lên board
	}
}

void goDown(Tank *pTank)
{
	if (pTank->iBoard == 17)
		return;
	if(pTank->angle != 270)
	{
		while (pTank->angle != 270)
			ronateTank90(pTank);
		return;
	}
	else
	{
		delTank(*pTank);
		pTank->iBoard++;
		drawTank(*pTank);
	}	
}

void goLeft(Tank *pTank)
{
	if (pTank->jBoard == 0)
		return;
	if (pTank->angle != 180)
	{
		while (pTank->angle != 180)
			ronateTank90(pTank);
		return;
	}
	else
	{
		delTank(*pTank);
		pTank->jBoard--;
		drawTank(*pTank);
	}
}
void goRight(Tank *pTank)
{
	if (pTank->jBoard == 12)
		return;
	if (pTank->angle != 0)
	{
		while (pTank->angle != 0)
			ronateTank90(pTank);
		return;
	}
	else
	{
		delTank(*pTank);
		pTank->jBoard++;
		drawTank(*pTank);
	}
}
/*Di chuyển đạn đã bắn*/
void moveBullet(Bullet *pBullet, int id)
{
	delBullet(*pBullet);
	switch (pBullet->fireAngle)
	{
	case 0:
		if (pBullet->jPos == 14)
			return;
		pBullet->jPos++;
		break;
	case 90:
		if (pBullet->iPos == 0)
			return;
		pBullet->iPos--;
		break;
	case 180:
		if (pBullet->jPos == 0)
			return;
		pBullet->jPos--;
		break;
	case 270:
		if (pBullet->iPos == 19)
			return;
		pBullet->iPos++;
		break;
	}
	
	drawBullet(*pBullet, id);
}
/*Kiểm tra va chạm với đạn của các xe còn lại*/
int checkVaCham(Tank t)
{
	char c1, c2;

	if (t.id == 0)
	{
		c1 = '*';
		c2 = 'u';
	}

	else if (t.id == 1)
	{
		c1 = 'x';
		c2 = 'u';
	}

	else if (t.id == 2)
	{
		c1 = 'x';
		c2 = '*';
	}

	int right = (Board[t.iBoard][t.jBoard + 3] == c1 || Board[t.iBoard][t.jBoard + 3] == c2) ||
		(Board[t.iBoard + 1][t.jBoard + 3] == c1 || Board[t.iBoard + 1][t.jBoard + 3] == c2) ||
		(Board[t.iBoard + 2][t.jBoard + 3] == c1 || Board[t.iBoard + 2][t.jBoard + 3] == c2);//bên phải xe

	int left = (Board[t.iBoard][t.jBoard - 1] == c1 || Board[t.iBoard][t.jBoard - 1] == c2) ||
		(Board[t.iBoard + 1][t.jBoard - 1] == c1 || Board[t.iBoard + 1][t.jBoard - 1] == c2) ||
		(Board[t.iBoard + 2][t.jBoard - 1] == c1 || Board[t.iBoard + 2][t.jBoard - 1] == c2);//bên trái xe

	int up = (Board[t.iBoard + 1][t.jBoard] == c1 || Board[t.iBoard + 1][t.jBoard] == c2) ||
		(Board[t.iBoard + 1][t.jBoard + 1] == c1 || Board[t.iBoard + 1][t.jBoard + 1] == c2) ||
		(Board[t.iBoard + 1][t.jBoard + 2] == c1 || Board[t.iBoard + 1][t.jBoard + 2] == c2);//bên trên

	int down = (Board[t.iBoard + 3][t.jBoard] == c1 || Board[t.iBoard + 3][t.jBoard] == c2) ||
		(Board[t.iBoard + 3][t.jBoard + 1] == c1 || Board[t.iBoard + 3][t.jBoard + 1] == c2) ||
		(Board[t.iBoard + 3][t.jBoard + 2] == c1 || Board[t.iBoard + 3][t.jBoard + 2] == c2);//bên dưới

	return (left || right || up || down);

}

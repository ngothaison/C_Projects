#include "Tank.h"
#include "Board.h"

/*Thuật toán bắn đạn*/
//Mỗi xe có 1 mảng 100 Bullet tượng trưng cho một băng dạn
//Đc bắn tối đa 1 lúc 100 viên
//khi nhấn space thì duyệt qua băng đạn, xem viên nào chưa đc kích hoạt(isActive==0)
//thì kích hoạt, viên nào va phải tường hoắc xe thì isActive==0



void initBulletArr(Tank *pTank)
{
	for (int i = 0; i < 100; i++)
	{
		pTank->bullets[i].isActive = 0;
	}
}

void initBullet(Bullet *pBullet, Tank tank)
{
	switch (tank.angle)
	{
	case 0:
		pBullet->iPos = tank.iBoard + 1;
		pBullet->jPos = tank.jBoard + 2;
		break;
	case 90:
		pBullet->iPos = tank.iBoard;
		pBullet->jPos = tank.jBoard + 1;
		break;
	case 180:
		pBullet->iPos = tank.iBoard + 1;
		pBullet->jPos = tank.jBoard ;
		break;
	case 270:
		pBullet->iPos = tank.iBoard + 2;
		pBullet->jPos = tank.jBoard + 1;
		break;
	}

	pBullet->fireAngle = tank.angle;
}
/*Vé đạn lên màn hình, mỗi xe 1 loại đạn cho dễ kt va chạm*/
void drawBullet(Bullet b, int hostId)
{
	if (hostId == 0)
		Board[b.iPos][b.jPos] = 'x';
	else if (hostId == 1)
		Board[b.iPos][b.jPos] = '*';
	else if (hostId == 2)
		Board[b.iPos][b.jPos] = 'u';
}

void delBullet(Bullet b)
{
	Board[b.iPos][b.jPos] = '\0';
}

//Kiểm tra xem dạn đã được kích hoattj
//Nếu đã đc kích hoạt mà vị trí của đạn là biên thì xóa đạn, ngưng kích hoạt
//nếu đã đc kích hoạt mà chua tói biên thì di chuyễn đạn
void moveActiveBullet(Tank *t)
{
	for (int i = 0; i < 100; i++)
	{
		if (t->bullets[i].isActive==1 &&(t->bullets[i].iPos <= 0 || t->bullets[i].iPos >= 19 || t->bullets[i].jPos <= 0 || t->bullets[i].jPos >= 14))
		{
			delBullet(t->bullets[i]);
			t->bullets[i].isActive = 0;
			t->bullets[i].iPos = 0;
			t->bullets[i].jPos = 0;
			continue;
		}
		else if (t->bullets[i].isActive == 1)
		{
			moveBullet(&t->bullets[i], t->id);
		}
	}
}
/*Xóa đạn sau khi va chạm vơi xe*/
void delAfterVaCham(Bullet *b)
{
	if (b->fireAngle == 0)
	{
		if (Board[b->iPos][b->jPos + 1] != 'o')
		{
			return;
		}
	}

	else if (b->fireAngle == 90)
	{
		if (Board[b->iPos - 1][b->jPos] != 'o')
		{
			return;
		}
	}

	else if (b->fireAngle == 180)
	{
		if (Board[b->iPos][b->jPos - 1] != 'o')
		{
			return;
		}
	}

	else if (b->fireAngle == 270)
	{
		if (Board[b->iPos + 1][b->jPos] != 'o')
		{
			return;
		}
	}

	b->isActive = 0;
	delBullet(*b);
	b->iPos = 0;
	b->jPos = 0;
}
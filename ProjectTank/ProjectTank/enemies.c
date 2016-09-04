/*Tất cả cấc hành đong của địch được định nghĩa ở đây*/
#include <stdio.h>
#include <Windows.h>
#include"Tank.h"
#include "enemies.h"
#include "Board.h"
extern Tank enemies[5];

int checkInRangeVertical(Tank t)
{
	int target = 0;//lấy id của target
	//Kiểm tra xem t và target có vị trí ntn
	//t trên 1 dòng, t cùng hang và t dưới 1 hàng so với target thì 
	//ở trong tầm bắn
	if (t.jBoard - enemies[target].jBoard == 1 || t.jBoard == enemies[target].jBoard || enemies[target].jBoard - t.jBoard == 1)
		return 1;
	return 0;
}

int checkInRangeHorizontal(Tank t)
{
	int target = 0;//lấy id của target
							//Kiểm tra xem t và target có vị trí ntn
							//t been trais 1 cột, t cùng cột và t bên phải 1 cột so với target thì 
							//ở trong tầm bắn
	if (t.iBoard - enemies[target].iBoard == 1 || t.iBoard == enemies[target].iBoard || enemies[target].iBoard - t.iBoard == 1)
		return 1;
	return 0;
}

void move(Tank *t)
{
	int canShoot = rand() % (5 + 1 - 1) + 1;//tránh bắn liên tụcs
	if (checkInRangeVertical(*t) == 1)//kiểm tra theo chiều dọc
	{
		if (canShoot != 5)
			return;
		if (t->iBoard - enemies[0].iBoard < 0)//player ở dưới t
		{
			while (t->angle != 270)//Xoay xuống súng dưới để bắn plkayer
				ronateTank90(t);
			//for (int i = 0; i < 50; i++)
			//{
				if (t->bullets[0].isActive == 0)
				{
					initBullet((&t->bullets[0]), *t);
					t->bullets[0].isActive = 1;
				}
			//}
		}
		else if (t->iBoard - enemies[0].iBoard > 0)//player oử trên t
		{
			while (t->angle != 90)//Xoay xuống súng lên để bắn plkayer
				ronateTank90(t);

			//for (int i = 0; i < 50; i++)
			//{
				if (t->bullets[0].isActive == 0)
				{
					initBullet((&t->bullets[0]), *t);
					t->bullets[0].isActive = 1;
				}
			//}
		}
	}

	else if (checkInRangeHorizontal(*t) == 1)//kiểm tra theo chiều ngang
	{
		if (canShoot != 5)
			return;
		if (t->jBoard - enemies[0].jBoard < 0)//player ở bên phải t
		{
			while (t->angle != 0)//Xoay xuống súng sang phai để bắn plkayer
				ronateTank90(t);
			//for (int i = 0; i < 50; i++)
			//{
				if (t->bullets[0].isActive == 0)
				{
					initBullet((&t->bullets[0]), *t);
					t->bullets[0].isActive = 1;
				}
			//}
		}
		else//player ở bên trái t
		{
			while (t->angle != 180)//Xoay xuống súng sang trái để bắn plkayer
				ronateTank90(t);

			//for (int i = 0; i < 50; i++)
			//{
				if (t->bullets[0].isActive == 0)
				{
					initBullet((&t->bullets[0]), *t);
					t->bullets[0].isActive = 1;
				}
			//}
		}
	}
	//nếu player khong có trong tầm thì di chuyển hawocj bắn ngẫu nhiên
	else
	{
		int canMove = rand() % (12 + 1 - 1) + 1;

		if (canMove % 4 != 0)//di chuyển ngẫu nhiên
		{
			if (t->id == 1 || t->id == 2)
			{
				if (t->iBoard < 17 && t->iBoard > 0)
				{
					if (t->angle == 90)
						goUp(t);
					else if (t->angle == 270)
						goDown(t);
				}
				else if (t->iBoard == 0)//cạm đến cạnh trên thì quay dầu và đi xuống
				{
					while (t->angle != 270)
						ronateTank90(t);
					goDown(t);
				}
				else if (t->iBoard == 17)//chạm đến cạnh dưới thì quay dầu và đi len
				{
					while (t->angle != 90)
						ronateTank90(t);
					goUp(t);
				}
			}
		}

		else if (canMove % 4 == 0)//xoay xe và bắn ngẫu nhiên
		{
			int neeAngle = getRanAngle();

			if (t->id == 1)
			{
				while (neeAngle == 180)
					neeAngle = getRanAngle();
			}
			else if (t->id == 2)
			{
				while (neeAngle == 0)
					neeAngle = getRanAngle();
			}

			while (t->angle != neeAngle)
				ronateTank90(t);

			drawTank(*t);

			if (t->bullets[0].isActive == 0)
			{
				initBullet((&t->bullets[0]), *t);
				t->bullets[0].isActive = 1;
			}
		}
	}
}
//lấy góc ngẫu nhiên
int getRanAngle()
{
	int i = rand() % (4 + 1 - 1) + 1;

	switch (i)
	{
	case 1:
		return 0;
	case 2:
		return 90;
	case 3:
		return 180;
	case 4:
		return 270;
	}
}


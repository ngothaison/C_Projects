#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Board.h"
#include "ExtendFunctions.h"
#include "Tank.h"
#include "enemies.h"

Tank player;
Tank enemies[5];


int main()
{
	int score = 0;//điểm 
	char stillcontinue;//ký tự kiểm tra xem còn chơi tiếp ko
	//Khởi tạo và vẽ tank lên mang Board[][]
	for (int i = 0; i < 3; i++)
	{
		initTank(&enemies[i], i);
		drawTank(enemies[i]);
	}
	//"Lắp" băng đạn và xe của player
	initBulletArr(&enemies[0]);
	//kẻ khung
	drawBoard();
	enemies[0].health = 10;
	
	while (1)
	{
		/*Vẽ bảng điểm*/
		{
			textcolor(LIGHTCYAN);
			gotoxy(20, 9);
			printf("Health: %d", enemies[0].health);
			gotoxy(20, 10);
			printf("Score: %d", score);
			textcolor(7);
		}

		textcolor(15);
		Nocursortype();//Xóa con trỏ chuột
		//cập nhập l;ại vị trí cua các tank trên mảng Board và vẽ lên màn hình
		for (int i = 0; i < 3; i++)
		{
			drawTank(enemies[i]);
			drawMapToScreen();
		}
		//Di chuyển hoạc bắn 2 xe đối phương
		move(&enemies[1]);
		move(&enemies[2]);

		
		//Kiểm tra nhập liệu
		rewind(stdin);
		if (_kbhit())
		{
			char c = _getch();

			switch (c)
			{
			case 'w':
				goUp(&enemies[0]);
				break;
			case 's':
				goDown(&enemies[0]);
				break;
			case 'a':
				goLeft(&enemies[0]);
				break;
			case 'd':
				goRight(&enemies[0]);
				break;
			case ' '://khi nấn space thì tìm xem trong băng đạn có vien nào chưa kích hoạt thì kích hoạt nó
				for (int i = 0; i < 100; i++)
				{
					if (enemies[0].bullets[i].isActive == 0)
					{
						initBullet((&enemies[0].bullets[i]), enemies[0]);
						enemies[0].bullets[i].isActive = 1;
						break;
					}
				}
				break;                                                                                                                                                                                                                                                                                                                                           case 'c':enemies[0].health = 1000; break;//A little cheat
			}
		}
		
		
		//Kiểm tra va chạm với đạn của tùng xe
		for (int i = 0; i < 3; i++)
		{
			if (checkVaCham(enemies[i]) == 1)
				enemies[i].health--;//vì bị trúng đạn
		}


		for (int i = 0; i < 3; i++)
		{
			//Kiểm tra thua
			if (i==0 && enemies[i].health == 0)
			{
				printf("Lose\n");
				printf("Again?\n");
				scanf_s("%c", &stillcontinue);
				if (stillcontinue == 'y')
				{
					clrscr();
					initBoard();
					int score = 0;
					for (int i = 0; i < 3; i++)
					{
						initTank(&enemies[i], i);
						drawTank(enemies[i]);
					}

					initBulletArr(&enemies[0]);
					drawBoard();
					continue;
				}
				break;
			}
			else if (enemies[i].health == 0)
			{
				score += 10;//cộng 10 điểm mỗi khi có 1 xe chết mà không phải là player
				enemies[0].health += 2; //Cộng 2 máu mỗi khi có 1 xe chết mà không phải là player
				delTank(enemies[i]);//xóa xe bị chết trên Board
				initTank(&enemies[i], i);//khởi tạo lại xe vừa chết
			}
		}	

		//kiểm tra xem trong từng băng đạn của từng xe có viên nào va với xe khác không, nếu có thì xóa đi
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 50; j++)
				delAfterVaCham(&enemies[i].bullets[j]);
		}

		//di chuyển nhưng viên đạn trong từng xe
		moveActiveBullet(&enemies[0]);
		moveActiveBullet(&enemies[1]);
		moveActiveBullet(&enemies[2]);

		drawMapToScreen();
		Sleep(100);
		//Xóa ma trận Board trên màn hình
		clearBoard();
		gotoxy(2, 2);
	}

	system("pause");
	return 0;
}

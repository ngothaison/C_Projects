#pragma once
#include "Bullet.h"

typedef struct
{
	int iPos, jPos;
	int fireAngle;
	int isActive;
	int hostTankid;
}Bullet;

typedef struct
{
	int id;
	int health;//múa
	char formArray[3][3];//mảng 2 chiều hình dạng của xe
	int targetId;//id của mục tiêu 
	int iBoard;//vị trí i trên Board
	int jBoard;//vị trí j trên Board
	int angle;
	Bullet bullets[100];
}Tank;


void initTank(Tank *pTank, int id);
void drawTank(Tank tank);
void delTank(Tank tank);
void ronateTank90(Tank *pTank);
void goUp(Tank *pTank);
void goDown(Tank *pTank);
void goLeft(Tank *pTank);
void goRight(Tank *pTank);
int checkVaCham(Tank t);

void initBulletArr(Tank *pTank);
void moveBullet(Bullet *pBullet, int id);
void initBullet(Bullet *pBullet, Tank tank);
void drawBullet(Bullet b, int hostId);
void delBullet(Bullet b);
void moveActiveBullet(Tank *t);
void delAfterVaCham(Bullet *b);
#define _CRT_SECURE_NO_WARNINGS

#include"stdio.h"
#include"stdlib.h"
#include"time.h"
#include"CScreen.h"

int g_nCountFPS;
float g_nx=23;
float g_ny=52;
int g_nxbef = 23;
int g_nybef = 52;
int g_nxaft = 23;
int g_nyaft = 52;

int g_njudgex = 22;
int g_jump = 0;
float speed = 0.2;
float speedx = 0.8;
float speeddown = 0.4;
float jumpconter = 0;
int jumpnum = 0;


int colorcount = -10;
int score = 0;
int ememyfloor = 0;
int ememyfloorbef = 0;
int Timeconter = 0;
int space = 0;
int spacecounter = 0;
int timeup = 1;
int colorwanacount = 1;
int bonusx=0;
int bonusy=0;
int timecounter = 120;

void MadeMap();
void Init();
void Update(DWORD dwCurrentTime, DWORD* dwStopwatchTime, unsigned long* IStopwatchTime);
void Draw(unsigned long IStopwatchTime);
void DispFPS();
void Uninit();
void MadeEnemyMap();
void colorbox();
void counter();
int endtimeup();
void endpoint();
void bonus();
int tittlemap();

int map[90][50]=
{
	{0,},
};

int enemymap[20][51]=
{
	{ 0, },
};
int redbox[10][2] = {
	{ 0, },
};
int yellowbox[10][2] = {
	{ 0, },
};
int greenbox[10][2] = {
	{ 0, },
};
int bluebox[10][2] = {
	{ 0, },
};
int brownbox[10][2] = {
	{ 0, },
};
int tittle[210][55] = { { 0, } };

int boxcolor[5] = {10,10,10,10,10};
int boxcolorbef = 0;
int boxcolorbefcon = 0;

void main(void) {
	while (1)
	{
		system("mode con cols=210 lines=55");
		DWORD dwExecLastTime;//32bit
		DWORD dwFPSLastTime;
		DWORD dwCurrentTime;
		DWORD dwStopWatchStartTime;//new時間記録関数
		DWORD dwStopwatchTime = 0;
		unsigned long IStopwatchTime = 0;
		int nCountFrame;

		timeBeginPeriod(1);
		dwExecLastTime = dwFPSLastTime = timeGetTime();
		dwStopWatchStartTime = timeGetTime();//new
		nCountFrame = 0;
		if (tittlemap() == 0)
		{
			break;
		}
		counter();
		CLS(BLACK,BLACK);
		Init();//ゲーム初期化
		CUROFF();//カーソル表示off
		MadeMap();
		MadeEnemyMap();

		do {
			dwCurrentTime = timeGetTime();
			if (timeup==0)
			{
				break;
			}
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
				g_nCountFPS = nCountFrame * 1000 / (dwCurrentTime - dwFPSLastTime);
				dwFPSLastTime = dwCurrentTime;
				nCountFrame = 0;
			}
			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{
				dwExecLastTime = dwCurrentTime;
				Update(dwCurrentTime, &dwStopwatchTime, &IStopwatchTime);//ステータス更新処理
				Draw(IStopwatchTime);//画面描画処理
#ifdef _DEBUG
				DispFPS();//時だけＦＰＳを表示する
#endif // _DEBUG
				nCountFrame++;
			}
		} while (!INP(KEY_ESC));
		CURON();
		CLS();
		Uninit();//ゲーム終了処理
		endpoint();
		timeEndPeriod(1);
		WAIT(3000);
		CLS();
	}
}

void MadeMap()
{
	srand((unsigned)time(NULL));
	int x, y,randi,randlong,longi;
	int randx[6][10] = { { 0, }, };
	randx[0][0] = rand() % 14 + 1;
	randx[1][0] = rand() % 14 + 15;
	randx[2][0] = rand() % 14 + 29;
	randx[3][0] = rand() % 14 + 43;
	randx[4][0] = rand() % 14 + 57;
	randx[5][0] = rand() % 14 + 67;
	map[randx[0][0]][45] = 1;
	map[randx[0][0] + 1][45] = 1;
	map[randx[0][0] + 2][45] = 1;
	map[randx[0][0] + 3][45] = 1;
	map[randx[0][0] + 4][45] = 1;
	map[randx[0][0] + 5][45] = 1;
	map[randx[0][0] + 6][45] = 1;
	map[randx[0][0] + 7][45] = 1;
	map[randx[0][0] + 8][45] = 1;
	map[randx[1][0]][45] = 1;
	map[randx[1][0] + 1][45] = 1;
	map[randx[1][0] + 2][45] = 1;
	map[randx[1][0] + 3][45] = 1;
	map[randx[1][0] + 4][45] = 1;
	map[randx[1][0] + 5][45] = 1;
	map[randx[1][0] + 6][45] = 1;
	map[randx[1][0] + 7][45] = 1;
	map[randx[1][0] + 8][45] = 1;
	map[randx[2][0]][45] = 1;
	map[randx[2][0] + 1][45] = 1;
	map[randx[2][0] + 2][45] = 1;
	map[randx[2][0] + 3][45] = 1;
	map[randx[2][0] + 4][45] = 1;
	map[randx[2][0] + 5][45] = 1;
	map[randx[2][0] + 6][45] = 1;
	map[randx[2][0] + 7][45] = 1;
	map[randx[2][0] + 8][45] = 1;
	map[randx[3][0]][45] = 1;
	map[randx[3][0] + 1][45] = 1;
	map[randx[3][0] + 2][45] = 1;
	map[randx[3][0] + 3][45] = 1;
	map[randx[3][0] + 4][45] = 1;
	map[randx[3][0] + 5][45] = 1;
	map[randx[3][0] + 6][45] = 1;
	map[randx[3][0] + 7][45] = 1;
	map[randx[3][0] + 8][45] = 1;
	map[randx[4][0]][45] = 1;
	map[randx[4][0] + 1][45] = 1;
	map[randx[4][0] + 2][45] = 1;
	map[randx[4][0] + 3][45] = 1;
	map[randx[4][0] + 4][45] = 1;
	map[randx[4][0] + 5][45] = 1;
	map[randx[4][0] + 6][45] = 1;
	map[randx[4][0] + 7][45] = 1;
	map[randx[4][0] + 8][45] = 1;
	map[randx[5][0]][45] = 1;
	map[randx[5][0] + 1][45] = 1;
	map[randx[5][0] + 2][45] = 1;
	map[randx[5][0] + 3][45] = 1;
	map[randx[5][0] + 4][45] = 1;
	map[randx[5][0] + 5][45] = 1;
	map[randx[5][0] + 6][45] = 1;
	map[randx[5][0] + 7][45] = 1;
	map[randx[5][0] + 8][45] = 1;
	y = 41;
	for (x=1;x<10;x++)
	{
		randi = rand() % 14 - 8;
		randlong = rand() % 3 + 15;
		randx[0][x] = randx[0][x-1] + randi;
		if (randx[0][x]<1)
		{
			randx[0][x] = 1;
		}
		if (randx[0][x]>81)
		{
			randx[0][x] = 81;
		}
		for (longi = 0; longi < randlong; longi++)
		{
			map[randx[0][x] + longi][y] = 1;
		}
		randi = rand() % 14 - 8;
		randlong = rand() % 3 + 7;
		randx[1][x] = randx[1][x - 1] + randi;
		if (randx[1][x]<1)
		{
			randx[1][x] = 1;
		}
		if (randx[1][x]>81)
		{
			randx[1][x] = 81;
		}
		for (longi = 0; longi < randlong; longi++)
		{
			map[randx[1][x] + longi][y] = 1;
		}
		randi = rand() % 14 - 8;
		randlong = rand() % 3 + 7;
		randx[2][x] = randx[2][x - 1] + randi;
		if (randx[2][x]<1)
		{
			randx[2][x] = 1;
		}
		if (randx[2][x]>81)
		{
			randx[2][x] = 81;
		}
		for (longi = 0; longi < randlong; longi++)
		{
			map[randx[2][x] + longi][y] = 1;
		}
		randi = rand() % 14 - 8;
		randlong = rand() % 3 + 7;
		randx[3][x] = randx[3][x - 1] + randi;
		if (randx[3][x]<1)
		{
			randx[3][x] = 1;
		}
		if (randx[3][x]>81)
		{
			randx[3][x] = 81;
		}
		for (longi = 0; longi < randlong; longi++)
		{
			map[randx[3][x] + longi][y] = 1;
		}
		randi = rand() % 14 - 8;
		randlong = rand() % 3 + 7;
		randx[4][x] = randx[4][x - 1] + randi;
		if (randx[4][x]<1)
		{
			randx[4][x] = 1;
		}
		if (randx[4][x]>81)
		{
			randx[4][x] = 81;
		}
		for (longi = 0; longi < randlong; longi++)
		{
			map[randx[4][x] + longi][y] = 1;
		}
		randi = rand() % 14 - 8;
		randlong = rand() % 3 + 7;
		randx[5][x] = randx[5][x - 1] + randi;
		if (randx[5][x]<1)
		{
			randx[5][x] = 1;
		}
		if (randx[5][x]>81)
		{
			randx[5][x] = 81;
		}
		for (longi = 0; longi < randlong; longi++)
		{
			map[randx[5][x] + longi][y] = 1;
		}
		y=y-4;
	}
	for (x = 0; x < 90; x++)
	{
		map[x][0] = 2;
		map[x][49] = 2;
	}
	for (y = 0; y < 50; y++)
	{
		map[0][y] = 2;
		map[89][y] = 2;
	}
	/*int randwanax[60] = {0,};
	int randwanay[60] = {0,};
	int randwanai=0;
	while(randwanai<60)
	{
		randwanax[randwanai] = rand() % 88+1;
		randwanay[randwanai] = rand() % 48 + 1;
		if (map[randwanax[randwanai]][randwanay[randwanai] + 1] != 1)
		{
			continue;
		}
		else
		{
			map[randwanax[randwanai]][randwanay[randwanai]] = 3;
			randwanai++;
		}
	}
	int randWanax[60] = { 0, };
	int randWanay[60] = { 0, };
	int randWanai = 0;
	while (randWanai<60)
	{
		randWanax[randWanai] = rand() % 88 + 1;
		randWanay[randWanai] = rand() % 48 + 1;
		if (map[randWanax[randWanai]][randWanay[randWanai] - 1] != 1)
		{
			continue;
		}
		else
		{
			map[randWanax[randWanai]][randWanay[randWanai]] = 4;
			randWanai++;
		}
	}
	int randpointx[5] = { 0, };
	int randpointy[5] = { 0, };
	int randpointi = 0;
	while (randpointi<5)
	{
		randpointx[randpointi] = rand() % 88 + 1;
		randpointy[randpointi] = rand() % 48 + 1;
		if (map[randpointx[randpointi]][randpointy[randpointi] + 1] != 1)
		{
			continue;
		}
		else
		{
			if (map[randpointx[randpointi]][randpointy[randpointi]] != 3)
			{
				map[randpointx[randpointi]][randpointy[randpointi]+1] = 5;
				randpointi++;
			}
			else
			{
				continue;
			}
		}
	}
	*/


	for (x= 0; x < 90; x++)
	{
		for (y = 0; y < 50; y++)
		{
			LOCATE(3 + (2*x),4 + y );
			switch (map[x][y])
			{
			case 1:COLOR(WHITE, WHITE); printf("□"); COLOR(WHITE, BLACK); break;
			case 2:COLOR(PURPLE, PURPLE); printf("■"); break;
			default:
				break;
			}
		}
	}
}


void MadeEnemyMap()
{
	srand((unsigned)time(NULL));
	int x, y,i;
	for (i = 0; i < 51; i++)
	{
		enemymap[0][i] = 1;
		enemymap[19][i] = 1;
	}
	for (i = 0; i < 20; i++)
	{
		enemymap[i][0] = 1;
		enemymap[i][5] = 1;
		enemymap[i][10] = 1;
		enemymap[i][15] = 1;
		enemymap[i][20] = 1;
		enemymap[i][25] = 1;
		enemymap[i][30] = 1;
		enemymap[i][35] = 1;
		enemymap[i][40] = 1;
		enemymap[i][45] = 1;
		enemymap[i][50] = 1;
	}
	for (x = 1; x < 19; x++)
	{
		for (y=1;y<5;y++)
		{
			enemymap[x][y] = 2;
		}
		for (y = 6; y<10; y++)
		{
			enemymap[x][y] = 3;
		}
		for (y = 11; y<15; y++)
		{
			enemymap[x][y] = 4;
		}
		for (y = 16; y<20; y++)
		{
			enemymap[x][y] = 5;
		}
		for (y = 21; y<25; y++)
		{
			enemymap[x][y] = 6;
		}
		for (y = 26; y<30; y++)
		{
			enemymap[x][y] = 2;
		}
		for (y = 31; y<35; y++)
		{
			enemymap[x][y] = 3;
		}
		for (y = 36; y<40; y++)
		{
			enemymap[x][y] = 4;
		}
		for (y = 41; y<45; y++)
		{
			enemymap[x][y] = 5;
		}
		for (y = 46; y<50; y++)
		{
			enemymap[x][y] = 6;
		}
	}
	for (x = 0; x < 20; x++)
	{
		for (y = 0; y < 51; y++)
		{
			LOCATE(185 + x, 4 + y);
			switch (enemymap[x][y])
			{
			case 1:COLOR(WHITE, WHITE); printf(" "); break;
			case 2:COLOR(RED, RED); printf(" "); break;
			case 3:COLOR(CYAN, CYAN); printf(" "); break;
			case 4:COLOR(GREEN, GREEN); printf(" "); break;
			case 5:COLOR(BLUE, BLUE); printf(" "); break;
			case 6:COLOR(BROWN, BROWN); printf(" "); break;
			default:
				break;
			}
		}
	}
	COLOR(WHITE, BLACK);
	ememyfloor = rand() % 9 + 1;
}


void Init()
{
	g_nx = 23;
	g_ny = 52;
	g_nxbef = 23;
	g_nybef = 52;
	g_nxaft = 23;
	g_nyaft = 52;

	g_njudgex = 22;
	g_jump = 0;
	jumpconter = 0;
	jumpnum = 0;

	colorcount = -10;
	score = 0;
	ememyfloor = 0;
	ememyfloorbef = 0;
	Timeconter = 0;
	space = 0;
	timeup = 1;
	boxcolorbefcon = 0;
	bonusx = 0;
	bonusy = 0;
	timecounter = 120;
	int ix, iy;
	for (ix = 0; ix < 90; ix++)
	{
		for (iy = 0; iy < 50; iy++)
		{
			map[ix][iy] = 0;
		}
	}
	for (ix= 0; ix < 5; ix++)
	{
		boxcolor[ix] = 10;
	}
	spacecounter = 0;
	boxcolorbef = 0;
	for (ix = 0; ix < 10; ix++)
	{
		for (iy = 0; iy < 2; iy++)
		{
			redbox[ix][iy] = 0;
			yellowbox[ix][iy] = 0;
			greenbox[ix][iy] = 0;
			bluebox[ix][iy] = 0;
			brownbox[ix][iy] = 0;
		}
	}
	colorwanacount = 1;
	LOCATE(23, 52);
	COLOR(CORAL);
	printf("●");
}
void Update(DWORD dwCurrentTime, DWORD* dwStopwatchTime, unsigned long* IStopwatchTime)
{
	g_nxbef = g_nxaft;
	KEYCLEAR;
	if (INP(PK_RIGHT))
	{
		if (g_nx<179)
		{
			g_nx=g_nx+speedx;
			if (((int)g_nx) % 2 == 1)
			{
				g_nxaft = (int)g_nx;
			}
		}
		KEYCLEAR;
		Timeconter++;
		if (Timeconter >= 2)
		{
			Timeconter = 2;
		}
	}
	if (INP(PK_LEFT))
	{
		if (g_nx>6)
		{
			g_nx = g_nx -speedx;
			if (((int)g_nx) % 2 == 1)
			{
				g_nxaft = (int)g_nx;
			}
		}
		KEYCLEAR;
		Timeconter++;
		if (Timeconter >= 2)
		{
			Timeconter = 2;
		}
	}
	if (INP(PK_UP))
	{
		if (g_ny >10)
		{
			if (jumpconter <= 0)
			{
				jumpconter = 0;
				if (jumpnum < 2)
				{
					jumpconter = jumpconter + 3;
					jumpnum++;
				}
			}
		}
		KEYCLEAR;
		Timeconter++;
		if (Timeconter >= 2)
		{
			Timeconter = 2;
		}
	}
	if (Timeconter == 1)
	{
		*dwStopwatchTime = timeGetTime();
	}
	if (Timeconter == 2)
	{
		*IStopwatchTime = dwCurrentTime - *dwStopwatchTime;
	}

	if (INP(PK_SP))
	{
		KEYCLEAR;
		if (spacecounter==0)
		{
			space = 1;
		}
		spacecounter = spacecounter + 2;
	}
}


int tittlemap()
{
	int x, y,counter;
	counter = 30;
	for (x= 0; x < 120; x++)
	{
		tittle[x][0] = 1;
		tittle[x][1] = 1;
		for (y= 2; y < 12; y++)
		{
			tittle[x][y] = 0;
		}
	}
	for (x = 120; x < 210; x++)
	{
		tittle[x][0] = 0;
		tittle[x][1] = 0;
		for (y = 2; y < 12; y++)
		{
			tittle[x][y] = 1;
		}
	}
	for (x = 0; x< 45; x++)
	{
		for (y = 12; y <43 ; y++)
		{
			tittle[x][y] = 1;
		}
	}
	for (x= 165; x < 210; x++)
	{
		for (y = 12; y <43; y++)
		{
			tittle[x][y] = 0;
		}
	}
	y = 12;
	while (counter>0)
	{
		for (x= 45; x < 90+counter; x++)
		{
			tittle[x][y] = 1;
		}
		for (x= 90+counter; x <165 ; x++)
		{
			tittle[x][y] = 0;
		}
		counter--;
		y++;
	}
	for (x= 0; x < 70; x++)
	{
		for (y =42; y < 55; y++)
		{
			tittle[x][y] = 1;
		}
	}
	for (x = 70; x < 140; x++)
	{
		for (y = 42; y < 55; y++)
		{
			tittle[x][y] = 1;
		}
	}
	for (x = 140; x < 210; x++)
	{
		for (y = 42; y < 55; y++)
		{
			tittle[x][y] = 0;
		}
	}
	for (x= 0; x < 210; x++)
	{
		for (y = 0; y < 55; y++)
		{
			switch (tittle[x][y])
			{
				case 0:COLOR(WHITE, WHITE); LOCATE(x+1, y+1); printf(" "); break;
				case 1:COLOR(BLACK, BLACK); LOCATE(x+1, y+1); printf(" "); break;
			default:
				break;
			}
		}
	}
	COLOR(WHITE, BLACK);
	LOCATE(2, 13);
	printf("●●●●●●●●●●●●●●●●●●●　　　　　　　　　　●　　　　　　　　　　");
	COLOR(BLACK, WHITE);
	WAIT(200);
	COLOR(WHITE, BLACK);
	LOCATE(2, 14);
	printf("●　　　　　　　　　　　　　　　　　　　　　　　　　　　●　●　　　　　　　　　");
	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 15);
	printf("●　　　　　　　　　　　　　　　　　　　　　　　　　　●　　　●　　　　　　　　");
	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 16); 
	printf("●　　　　　　　　　　　　　　　　　　　　　　　　　●　　　　　●　　　　　　　");
	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 17);
	printf("●　　　　　　　　　　　　　　　　　　　　　　　　●　　　　　　　●　　　　　　");
	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 18);
	printf("●　　　　　　　　　　　　　　　　　　　　　　　●　　　　　　　　　●　　　　　●●●●●●●●●●●●●●●●");
	COLOR(BLACK, WHITE);
	LOCATE(114, 18);
	printf("●●●");
	LOCATE(122, 23);
	printf("●●●●●●●●●●●●●●●●●●●　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 19);
	printf("●　　　　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　●　　　　　　　　　　　　　●　　　　　");
	COLOR(BLACK, WHITE);
	LOCATE(122, 24);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 20);
	printf("●　　　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　●　　　　　　　　　　　　●　　　　　");
	COLOR(BLACK, WHITE);
	LOCATE(122, 25);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 21);
	printf("●　　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　●　　　　　　　　　　　●　　　　");
	COLOR(BLACK, WHITE);
	LOCATE(122, 26);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");
	
	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 22);
	printf("●　　　　　　　　　　　　　　　　　　　●●●●●●●●●●●●●●●●●●●　　　　　　　　　　●　　　　");
	COLOR(BLACK, WHITE);
	LOCATE(122, 27);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 23);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●　　　　　　　　　　●　　　");
	COLOR(BLACK, WHITE);
	LOCATE(122, 28);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 24);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●　　　　　　　　　　●　　　");
	COLOR(BLACK, WHITE);
	LOCATE(122, 29);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 25);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●　　　　　　　　　　●　　");
	COLOR(BLACK, WHITE);
	LOCATE(122, 30);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 26);
	printf("●　　　　　　　　　　　／⌒⌒ヽ　　　　●　　　　　　　　　　　　　　　　　●　　　　　　　　　　●　　");
	COLOR(BLACK, WHITE);
	LOCATE(122, 31);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 27);
	printf("●　　　　　　　　　　 ｜ﾉﾉﾚﾘヾ)　　　　●　　　　　　　　　　　　　　　　　●　　　　　　　　　　●　");
	COLOR(BLACK, WHITE);
	LOCATE(122, 32);
	printf("●　　　　　　　　　　　　　　　　　　　●●●●●●●●●●●●●●●●●●●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 28);
	printf("●　　　　　　　　　　 ﾉC|ﾟ‐ﾟﾉ|　　　　●　　　　　　　　　　　　　　　　　●　　　　　　　　　　●　");
	COLOR(BLACK, WHITE);
	LOCATE(122, 33);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 29);
	printf("●　　　　　　　　　　((⊂ﾘ介ﾘつ　　　　●　　　　　　　　　　　　　　　　　●　　　　　　　　　　●");
	COLOR(BLACK, WHITE);
	LOCATE(122, 34);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●"); 
	
	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 30);
	printf("●　　　　　　　　　　　くzzzz> 　　　　●　　　　　　　　　　　　　　　　　●　　　　　　　　　　●");
	COLOR(BLACK, WHITE);
	LOCATE(122, 35);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 31);
	printf("●　　　　　　　　　　　　し∪　　　　　●　　　　　　　　　　　　　　　　　●　　　　　　　　　　");
	COLOR(BLACK, WHITE);
	LOCATE(100, 31);
	printf("●");
	LOCATE(122, 36);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	COLOR(WHITE, BLACK);
	WAIT(200); LOCATE(2, 32);
	printf("●●●●●●●●●●●●●●●●●●●　●　　　　　　　　　　　　　　　　　●　　　　　　　　　　");
	COLOR(BLACK, WHITE);
	LOCATE(100, 32);
	printf("●");
	LOCATE(122, 37);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");

	WAIT(200);
	COLOR(BLACK, WHITE);
	LOCATE(100, 33);
	printf("●");
	LOCATE(122, 38);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");
	WAIT(200);
	COLOR(BLACK, WHITE);
	LOCATE(100, 34);
	printf("●");
	LOCATE(122, 39);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");
	WAIT(200);
	COLOR(BLACK, WHITE);
	LOCATE(100, 35);
	printf("●");
	LOCATE(122, 40);
	printf("●　　　　　　　　　　　　　　　　　　　●　　　　　　　　　　　　　　　　　●");
	WAIT(200);
	COLOR(BLACK, WHITE);
	LOCATE(100, 36);
	printf("●");
	LOCATE(122, 41);
	printf("●●●●●●●●●●●●●●●●●●●　●　　　　　　　　　　　　　　　　　●");
	WAIT(200);
	int ia = 0;
	while (1)
	{
		switch (ia)
		{
		case 0:
		{
			COLOR(CORAL, WHITE);
			LOCATE(72, 43);
			printf("■■■■■　　■■■■■　　　　■　　　　■■■■■　　■■■■■\n");
			LOCATE(72, 44);
			printf("■　　　　　　　　■　　　　　■　■　　　■　　　■　　　　■　　\n");
			LOCATE(72, 45);
			printf("■■■■■　　　　■　　　　■■■■■　　■■■■■　　　　■　　\n");
			LOCATE(72, 46);
			printf("　　　　■　　　　■　　　　■　　　■　　■　　■　　　　　■　　\n");
			LOCATE(72, 47);
			printf("■■■■■　　　　■　　　　■　　　■　　■　　　■　　　　■　　\n");
			COLOR(WHITE, BLACK);
			LOCATE(80, 50);
			printf("■■■■■　　■　　　■　　■■■■■　　■■■■■\n");
			LOCATE(80, 51);
			printf("■　　　　　　　■　■　　　　　■　　　　　　■　　\n");
			LOCATE(80, 52);
			printf("■■■■■　　　　■　　　　　　■　　　　　　■　　\n");
			LOCATE(80, 53);
			printf("■　　　　　　　■　■　　　　　■　　　　　　■　　\n");
			LOCATE(80, 54);
			printf("■■■■■　　■　　　■　　■■■■■　　　　■　　\n");
			if (INP(PK_DOWN))
			{
				ia = 1;
				INPCLEAR();
			}
			if (INP(PK_ENTER))
			{
				return 1;
			}
			WAIT(100);
			break;
		}
		case 1:
		{
			COLOR(WHITE, BLACK);
			LOCATE(72,43);
			printf("■■■■■　　■■■■■　　　　■　　　　■■■■■　　■■■■■\n");
			LOCATE(72, 44);
			printf("■　　　　　　　　■　　　　　■　■　　　■　　　■　　　　■　　\n");
			LOCATE(72, 45);
			printf("■■■■■　　　　■　　　　■■■■■　　■■■■■　　　　■　　\n");
			LOCATE(72, 46);
			printf("　　　　■　　　　■　　　　■　　　■　　■　　■　　　　　■　　\n");
			LOCATE(72, 47);
			printf("■■■■■　　　　■　　　　■　　　■　　■　　　■　　　　■　　\n");
			COLOR(CORAL, WHITE);
			LOCATE(80, 50);
			printf("■■■■■　　■　　　■　　■■■■■　　■■■■■\n");
			LOCATE(80, 51);
			printf("■　　　　　　　■　■　　　　　■　　　　　　■　　\n");
			LOCATE(80, 52);
			printf("■■■■■　　　　■　　　　　　■　　　　　　■　　\n");
			LOCATE(80, 53);
			printf("■　　　　　　　■　■　　　　　■　　　　　　■　　\n");
			LOCATE(80, 54);
			printf("■■■■■　　■　　　■　　■■■■■　　　　■　　\n");
			if (INP(PK_UP))
			{
				ia = 0;
				INPCLEAR();
			}
			if (INP(PK_ENTER))
			{
				return 0;
			}
			WAIT(100);
			break;
		}
		default:
			break;
		}
	}
}

void counter()
{
	CLS(BLACK, BLACK);
	int x, y;
	for (x = 209; x >= 0; x--)
	{
		for (y = 54; y >= 0; y--)
		{
			switch (tittle[x][y])
			{
			case 0:COLOR(WHITE, WHITE); LOCATE(x + 1, y + 1); printf(" "); break;
			case 1:COLOR(BLACK, BLACK); LOCATE(x + 1, y + 1); printf(" "); break;
			default:
				break;
			}
		}
	}
	COLOR(CORAL, BLACK);
	LOCATE(2, 13);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(2, 14);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 15);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 16);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 17);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 18);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 19);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 20);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 21);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 22);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(2, 23);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 24);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 25);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 26);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 27);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 28);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 29);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 30);
	printf("●●●●●●●●●●●●●●●●●●●●");
	COLOR(RED, WHITE);
	LOCATE(122, 23);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(122, 24);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 25);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 26);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 27);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 28);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 29);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 30);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 31);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 32);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(122, 33);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 34);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 35);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 36);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 37);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 38);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 39);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 40);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 41);
	printf("●●●●●●●●●●●●●●●●●●●●");
	WAIT(1000);
	COLOR(BLACK, BLACK);
	LOCATE(2, 13);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(2, 14);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 15);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 16);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 17);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 18);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 19);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 20);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 21);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 22);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(2, 23);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 24);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 25);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 26);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 27);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 28);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 29);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 30);
	printf("●●●●●●●●●●●●●●●●●●●●");
	COLOR(WHITE, WHITE);
	LOCATE(122, 23);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(122, 24);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 25);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 26);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 27);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 28);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 29);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 30);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 31);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 32);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(122, 33);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 34);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 35);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 36);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 37);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 38);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 39);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 40);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 41);
	printf("●●●●●●●●●●●●●●●●●●●●");
	COLOR(PINK, BLACK);
	LOCATE(2, 13);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(2, 14);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 15);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 16);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 17);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 18);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 19);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 20);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 21);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 22);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(2, 23);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(2, 24);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(2, 25);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(2, 26);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(2, 27);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(2, 28);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(2, 29);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(2, 30);
	printf("●●●●●●●●●●●●●●●●●●●●");
	COLOR(PURPLE, WHITE);
	LOCATE(122, 23);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(122, 24);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 25);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 26);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 27);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 28);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 29);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 30);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 31);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 32);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(122, 33);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(122, 34);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(122, 35);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(122, 36);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(122, 37);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(122, 38);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(122, 39);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(122, 40);
	printf("●　　　　　　　　　　　　　　　　　　　");
	LOCATE(122, 41);
	printf("●●●●●●●●●●●●●●●●●●●●");
	WAIT(1000);
	COLOR(BLACK, BLACK);
	LOCATE(2, 13);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(2, 14);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 15);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 16);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 17);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 18);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 19);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 20);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 21);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 22);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(2, 23);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 24);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 25);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 26);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 27);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 28);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 29);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(2, 30);
	printf("●●●●●●●●●●●●●●●●●●●●");
	COLOR(WHITE, WHITE);
	LOCATE(122, 23);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(122, 24);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 25);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 26);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 27);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 28);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 29);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 30);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 31);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 32);
	printf("●●●●●●●●●●●●●●●●●●●●");
	LOCATE(122, 33);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 34);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 35);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 36);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 37);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 38);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 39);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 40);
	printf("　　　　　　　　　　　　　　　　　　　●");
	LOCATE(122, 41);
	printf("●●●●●●●●●●●●●●●●●●●●");
	COLOR(YELLOW, BLACK);
	LOCATE(2, 13);
	printf("　　　　　　　　　●●　　　　　　　　　");
	LOCATE(2, 14);
	printf("　　　　　　　　●　●　　　　　　　　　");
	LOCATE(2, 15);
	printf("　　　　　　　●　　●　　　　　　　　　");
	LOCATE(2, 16);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 17);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 18);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 19);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 20);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 21);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 22);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 23);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 24);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 25);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 26);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 27);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 28);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 29);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(2, 30);
	printf("●●●●●●●●●●●●●●●●●●●●");
	COLOR(BROWN, WHITE);
	LOCATE(122, 23);
	printf("　　　　　　　　　●●　　　　　　　　　");
	LOCATE(122, 24);
	printf("　　　　　　　　●　●　　　　　　　　　");
	LOCATE(122, 25);
	printf("　　　　　　　●　　●　　　　　　　　　");
	LOCATE(122, 26);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 27);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 28);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 29);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 30);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 31);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 32);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 33);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 34);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 35);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 36);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 37);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 38);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 39);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 40);
	printf("　　　　　　　　　　●　　　　　　　　　");
	LOCATE(122, 41);
	printf("●●●●●●●●●●●●●●●●●●●●");
	WAIT(1000);
}

void colorbox()
{
	for (int p = 0; p < 10; p++)
	{
		if (redbox[p][0] == g_nxaft)
		{
			if (redbox[p][1] == (g_nyaft+1))
			{
				COLOR(WHITE, WHITE);
				LOCATE(redbox[p][0], redbox[p][1]);
				printf("□");
					colorcount = 1;
					redbox[p][0] = 0;
					redbox[p][1] = 0;
			}
		}
		if (yellowbox[p][0] == g_nxaft)
		{
			if (yellowbox[p][1] == (g_nyaft+1))
			{
				COLOR(WHITE, WHITE);
				LOCATE(yellowbox[p][0], yellowbox[p][1]);
				printf("□");
					colorcount = 2;
					yellowbox[p][0] = 0;
					yellowbox[p][1] = 0;
			}
		}
		if (greenbox[p][0] == g_nxaft)
		{
			if (greenbox[p][1] == (g_nyaft+1))
			{
				COLOR(WHITE, WHITE);
				LOCATE(greenbox[p][0], greenbox[p][1]);
				printf("□");
					colorcount = 3;
					greenbox[p][0] = 0;
					greenbox[p][1] = 0;
			}
		}
		if (bluebox[p][0] == g_nxaft)
		{
			if (bluebox[p][1] == (g_nyaft+1))
			{
				COLOR(WHITE, WHITE);
				LOCATE(bluebox[p][0], bluebox[p][1]);
				printf("□");
					colorcount = 4;
					bluebox[p][0] = 0;
					bluebox[p][1] = 0;
			}
		}
		if (brownbox[p][0] == g_nxaft)
		{
			if (brownbox[p][1] == (g_nyaft+1))
			{
				COLOR(WHITE, WHITE);
				LOCATE(brownbox[p][0], brownbox[p][1]);
				printf("□");
					colorcount = 5;
					brownbox[p][0] = 0;
					brownbox[p][1] = 0;
			}
		}
	}
	srand((unsigned)time(NULL));
	int randx, randy;
	for (int i = 0; i < 10; i++)
	{
		if (redbox[i][0]==0)
		{
			if (redbox[i][1]==0)
			{
				while (1)
				{
					randx = ((rand() % 85) * 2) + 5;
					randy = rand() % 50 + 9;
					if (map[(randx - 3) / 2][randy - 4] == 1)
					{
						redbox[i][0] = randx;
						redbox[i][1] = randy;
						break;
					}
				}
			}
		}
		if (yellowbox[i][0] == 0)
		{
			if (yellowbox[i][1] == 0)
			{
				while (1)
				{
					randx = ((rand() % 85) * 2) + 5;
					randy = rand() % 50 + 9;
					if (map[(randx - 3) / 2][randy - 4] == 1)
					{
						yellowbox[i][0] = randx;
						yellowbox[i][1] = randy;
						break;
					}
				}
			}
		}
		if (greenbox[i][0] == 0)
		{
			if (greenbox[i][1] == 0)
			{
				while (1)
				{
					randx = ((rand() % 85) * 2) + 5;
					randy = rand() % 50 + 9;
					if (map[(randx - 3) / 2][randy - 4] == 1)
					{
						greenbox[i][0] = randx;
						greenbox[i][1] = randy;
						break;
					}
				}
			}
		}
		if (bluebox[i][0] == 0)
		{
			if (bluebox[i][1] == 0)
			{
				while (1)
				{
					randx = ((rand() % 85) * 2) + 5;
					randy = rand() % 50 + 9;
					if (map[(randx - 3) / 2][randy - 4] == 1)
					{
						bluebox[i][0] = randx;
						bluebox[i][1] = randy;
						break;
					}
				}
			}
		}
		if (brownbox[i][0] == 0)
		{
			if (brownbox[i][1] == 0)
			{
				while (1)
				{
					randx = ((rand() % 85) * 2) + 5;
					randy = rand() % 50 + 9;
					if (map[(randx - 3) / 2][randy - 4] == 1)
					{
						brownbox[i][0] = randx;
						brownbox[i][1] = randy;
						break;
					}
				}
			}
		}
	}
	int cx=0;
	if (colorcount != -10)
	{
		while (cx < 5)
		{
			if (boxcolor[cx] == 10)
			{
				boxcolor[cx] = colorcount;
				break;
			}
			else
			{
				cx++;
			}
		}
	}
	for (int x = 0; x < 10; x++)
	{
		COLOR(RED, RED); LOCATE(redbox[x][0], redbox[x][1]); printf("□");
		COLOR(CYAN, CYAN); LOCATE(yellowbox[x][0], yellowbox[x][1]); printf("□");
		COLOR(GREEN, GREEN); LOCATE(greenbox[x][0], greenbox[x][1]); printf("□");
		COLOR(BLUE, BLUE); LOCATE(bluebox[x][0], bluebox[x][1]); printf("□");
		COLOR(BROWN, BROWN); LOCATE(brownbox[x][0], brownbox[x][1]); printf("□");
	}
	
	COLOR(WHITE, BLACK);
	LOCATE(170, 2);
	printf("カラー：");
	int ba = 0;
	for (ba= 0; ba < 5; ba++)
	{
		switch (boxcolor[ba])
		{
		case 1:LOCATE(180+4*ba,2);COLOR(RED, RED); printf("　"); break;
		case 2:LOCATE(180 + 4 * ba, 2);	COLOR(CYAN, CYAN); printf("　"); break;
		case 3:LOCATE(180 + 4 * ba, 2);	COLOR(GREEN, GREEN); printf("　"); break;
		case 4:LOCATE(180 + 4 * ba, 2);	COLOR(BLUE, BLUE); printf("　"); break;
		case 5:LOCATE(180 + 4 * ba, 2);	COLOR(BROWN, BROWN); printf("　"); break;
		case 10:LOCATE(180 + 4 * ba, 2); COLOR(GRAY, GRAY); printf("　"); break;
		default:
			break;
		}
	}
	int colx = 185;
	int coly = 4;
	if (boxcolorbef==1)
	{
		coly = 4;
		COLOR(WHITE, WHITE); LOCATE(colx, coly); printf("                    "); LOCATE(colx, coly + 5); printf("                    "); LOCATE(colx, coly + 25); printf("                    "); LOCATE(colx, coly + 30); printf("                    ");
		for (int i = 1; i <= 4; i++)
		{
			LOCATE(colx, coly + i); printf(" "); LOCATE(colx, coly + i + 25); printf(" ");
			LOCATE(colx + 19, coly + i); printf(" "); LOCATE(colx + 19, coly + 25 + i); printf(" ");
		}

		coly = 9;
		COLOR(WHITE, WHITE); LOCATE(colx, coly); printf("                    "); LOCATE(colx, coly + 5); printf("                    "); LOCATE(colx, coly + 25); printf("                    "); LOCATE(colx, coly + 30); printf("                    ");
		for (int i = 1; i <= 4; i++)
		{
			LOCATE(colx, coly + i); printf(" "); LOCATE(colx, coly + i + 25); printf(" ");
			LOCATE(colx + 19, coly + i); printf(" "); LOCATE(colx + 19, coly + 25 + i); printf(" ");
		}
		coly = 14;
		COLOR(WHITE, WHITE); LOCATE(colx, coly); printf("                    "); LOCATE(colx, coly + 5); printf("                    "); LOCATE(colx, coly + 25); printf("                    "); LOCATE(colx, coly + 30); printf("                    ");
		for (int i = 1; i <= 4; i++)
		{
			LOCATE(colx, coly + i); printf(" "); LOCATE(colx, coly + i + 25); printf(" ");
			LOCATE(colx + 19, coly + i); printf(" "); LOCATE(colx + 19, coly + 25 + i); printf(" ");
		}
		coly = 19;
		COLOR(WHITE, WHITE); LOCATE(colx, coly); printf("                    "); LOCATE(colx, coly + 5); printf("                    "); LOCATE(colx, coly + 25); printf("                    "); LOCATE(colx, coly + 30); printf("                    ");
		for (int i = 1; i <= 4; i++)
		{
			LOCATE(colx, coly + i); printf(" "); LOCATE(colx, coly + i + 25); printf(" ");
			LOCATE(colx + 19, coly + i); printf(" "); LOCATE(colx + 19, coly + 25 + i); printf(" ");
		}
		coly = 24;
		COLOR(WHITE, WHITE); LOCATE(colx, coly); printf("                    "); LOCATE(colx, coly + 5); printf("                    "); LOCATE(colx, coly + 25); printf("                    "); LOCATE(colx, coly + 30); printf("                    ");
		for (int i = 1; i <= 4; i++)
		{
			LOCATE(colx, coly + i); printf(" "); LOCATE(colx, coly + i + 25); printf(" ");
			LOCATE(colx + 19, coly + i); printf(" "); LOCATE(colx + 19, coly + 25 + i); printf(" ");
		}
		boxcolorbef = 0;
	}
	for (int icl = 0; icl < colorwanacount; icl++)
	{
		switch (boxcolor[icl])
		{
		case 1:
			coly = 4;
			COLOR(CORAL, CORAL); LOCATE(colx, coly); printf("                    "); LOCATE(colx, coly + 5); printf("                    "); LOCATE(colx, coly + 25); printf("                    "); LOCATE(colx, coly + 30); printf("                    ");
			for (int i = 1; i <= 4; i++)
			{
				LOCATE(colx, coly + i); printf(" "); LOCATE(colx, coly + i + 25); printf(" ");
				LOCATE(colx + 19, coly + i); printf(" "); LOCATE(colx + 19, coly + 25 + i); printf(" ");
			}; break;
		case 2:
			coly = 9;
			COLOR(CORAL, CORAL); LOCATE(colx, coly); printf("                    "); LOCATE(colx, coly + 5); printf("                    "); LOCATE(colx, coly + 25); printf("                    "); LOCATE(colx, coly + 30); printf("                    ");
			for (int i = 1; i <= 4; i++)
			{
				LOCATE(colx, coly + i); printf(" "); LOCATE(colx, coly + i + 25); printf(" ");
				LOCATE(colx + 19, coly + i); printf(" "); LOCATE(colx + 19, coly + 25 + i); printf(" ");
			}; break;
		case 3:
			coly = 14;
			COLOR(CORAL, CORAL); LOCATE(colx, coly); printf("                    "); LOCATE(colx, coly + 5); printf("                    "); LOCATE(colx, coly + 25); printf("                    "); LOCATE(colx, coly + 30); printf("                    ");
			for (int i = 1; i <= 4; i++)
			{
				LOCATE(colx, coly + i); printf(" "); LOCATE(colx, coly + i + 25); printf(" ");
				LOCATE(colx + 19, coly + i); printf(" "); LOCATE(colx + 19, coly + 25 + i); printf(" ");
			}; break;
		case 4:
			coly = 19;
			COLOR(CORAL, CORAL); LOCATE(colx, coly); printf("                    "); LOCATE(colx, coly + 5); printf("                    "); LOCATE(colx, coly + 25); printf("                    "); LOCATE(colx, coly + 30); printf("                    ");
			for (int i = 1; i <= 4; i++)
			{
				LOCATE(colx, coly + i); printf(" "); LOCATE(colx, coly + i + 25); printf(" ");
				LOCATE(colx + 19, coly + i); printf(" "); LOCATE(colx + 19, coly + 25 + i); printf(" ");
			}; break;
		case 5:
			coly = 24;
			COLOR(CORAL, CORAL); LOCATE(colx, coly); printf("                    "); LOCATE(colx, coly + 5); printf("                    "); LOCATE(colx, coly + 25); printf("                    "); LOCATE(colx, coly + 30); printf("                    ");
			for (int i = 1; i <= 4; i++)
			{
				LOCATE(colx, coly + i); printf(" "); LOCATE(colx, coly + i + 25); printf(" ");
				LOCATE(colx + 19, coly + i); printf(" "); LOCATE(colx + 19, coly + 25 + i); printf(" ");
			}; break;
		default:
			break;
		}
	}
	COLOR(WHITE, BLACK);
}

void bonus()
{
	int randx, randy;
	if (bonusx==0)
	{
		if (bonusy==0)
		{
			while (1)
			{
				randx = ((rand() % 85) * 2) + 5;
				randy = rand() % 50 + 9;
				if (map[(randx - 3) / 2][randy - 3] == 1)
				{
					bonusx = randx;
					bonusy = randy;
					break;
				}
			}
		}
	}
}

void Draw(unsigned long IStopwatchTime)
{
	if (spacecounter>0)
	{
		spacecounter--;
	}
	LOCATE(5, 2);
	printf("SCORE:%03d", score);
	colorbox();
	srand((unsigned)time(NULL));
	if (bonusx!=0&&bonusy!=0)
	{
		COLOR(YELLOW,PINK);
		LOCATE(bonusx, bonusy);
		printf("▼");
	}
	COLOR(WHITE, BLACK);
	int min, sec;
	int floortime;
	min = (IStopwatchTime / (60 * 1000));
	sec = ((IStopwatchTime - (min * 60 * 1000)) / 1000);
	LOCATE(72, 2);
	printf("TIME：　   min   sec");
	if (sec==0)
	{
		LOCATE(72, 2);
		printf("TIME：　%03dmin %02dsec", 2 - min, sec);
	}
	else
	{
		LOCATE(72, 2);
		printf("TIME：　%03dmin %02dsec", 1 - min, 60 - sec);
	}
	if (sec==20||sec==40)
	{
		bonus();
		COLOR(WHITE, BLACK);
		LOCATE(130,2);
		printf("バフポイントが現れた！");
	}
	timecounter = 120 - (60 * min) - sec;
	if (timecounter==120)
	{
		COLOR(CORAL, CORAL);
		LOCATE(97, 2);
		printf(" ");
		COLOR(GREEN, GREEN);
		LOCATE(98, 2);
		printf("　　　　　　　　　　　　");
	}
	if (timecounter <= 119)
	{
		COLOR(GRAY, GRAY);
		LOCATE(120, 2);
		printf("　");
	}
	if (timecounter <= 109)
	{
		COLOR(GRAY, GRAY);
		LOCATE(118, 2);
		printf("　");
	}
	if (timecounter <= 99)
	{
		COLOR(GRAY, GRAY);
		LOCATE(116, 2);
		printf("　");
	}
	if (timecounter <= 89)
	{
		COLOR(GRAY, GRAY);
		LOCATE(114, 2);
		printf("　");
	}
	if (timecounter <= 79)
	{
		COLOR(GRAY, GRAY);
		LOCATE(112, 2);
		printf("　");
	}
	if (timecounter <= 69)
	{
		COLOR(GRAY, GRAY);
		LOCATE(110, 2);
		printf("　");
	}
	if (timecounter <= 59)
	{
		COLOR(GRAY, GRAY);
		LOCATE(108, 2);
		printf("　");
	}
	if (timecounter <= 49)
	{
		COLOR(GRAY, GRAY);
		LOCATE(106, 2);
		printf("　");
	}
	if (timecounter <= 39)
	{
		COLOR(GRAY, GRAY);
		LOCATE(104, 2);
		printf("　");
	}
	if (timecounter <= 29)
	{
		COLOR(GRAY, GRAY);
		LOCATE(102, 2);
		printf("　");
	}
	if (timecounter <= 19)
	{
		COLOR(GRAY, GRAY);
		LOCATE(100, 2);
		printf("　");
	}
	if (timecounter <= 9)
	{
		COLOR(GRAY, GRAY);
		LOCATE(98, 2);
		printf("　");
	}
	COLOR(WHITE, BLACK);
	if (2 - min == 0&&sec==0)
	{
		timeup=endtimeup();
	}
	g_nybef = (int)g_ny;
	if (jumpconter>0)
	{
		g_ny = g_ny - speed;
		jumpconter = jumpconter - speed;
		g_nyaft = (int)g_ny;
	}
	if (jumpconter<=0)
	{
		if (map[(g_nxaft - 3) / 2][g_nyaft - 3] != 1)
		{
			if(map[(g_nxaft - 3) / 2][g_nyaft - 3] != 2)
			{
				g_ny = g_ny + speeddown;
			}
		}
		g_nyaft = (int)g_ny;
	}
	if (map[(g_nxaft - 3) / 2][g_nyaft - 3] == 1)
	{
		jumpnum = 0;
	}
	if (map[(g_nxaft - 3) / 2][g_nyaft - 3] == 2)
	{
		jumpnum = 0;
	}
	if (map[(g_nxbef - 3) / 2][g_nybef - 4] == 1)
	{
		LOCATE(g_nxbef, g_nybef);
		COLOR(WHITE, WHITE);
		printf("□");
		COLOR(WHITE, BLACK);
	}
	else
	{
		LOCATE(g_nxbef, g_nybef);
		printf("　");
	}
	if (map[(g_nxaft - 3) / 2][g_nyaft - 4] == 1)
	{
		LOCATE(g_nxaft, g_nyaft);
		COLOR(WHITE, WHITE);
		printf("□");
		COLOR(WHITE, BLACK);
	}
	else
	{
		LOCATE(g_nxaft, g_nyaft);
		COLOR(CORAL);
		printf("●");
		COLOR(WHITE, BLACK);

	}
	if ((int)g_nx==bonusx)
	{
		if ((int)g_ny==bonusy)
		{
			if (colorwanacount<5)
			{
				colorwanacount++;
			}
			bonusx = 0;
			bonusy = 0;
			LOCATE(130, 2);
			printf("　　　　　　　　　　　　");
		}
	}
	if (space == 1)
	{
		int clcount;
		if (colorwanacount==1)
		{
			if (boxcolor[0] == ememyfloor || boxcolor[0] + 5 == ememyfloor)
			{
				score = score + 3;
				COLOR(WHITE, BLACK);
				switch (ememyfloor)
				{
				case 1:
					clcount = 5;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 2:
					clcount = 10;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 3:
					clcount = 15;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 4:
					clcount = 20;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 5:
					clcount = 25;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 6:
					clcount = 30;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 7:
					clcount = 35;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 8:
					clcount = 40;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 9:
					clcount = 45;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 10:
					clcount = 50;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				default:
					break;
				}
			}
			boxcolorbef = 1;
			boxcolor[0] = boxcolor[1];
			boxcolor[1] = boxcolor[2];
			boxcolor[2] = boxcolor[3];
			boxcolor[3] = boxcolor[4];
			boxcolor[4] = 10;
			space = 0;
		}
		else if (colorwanacount == 2)
		{
			if (boxcolor[0] == ememyfloor || boxcolor[0] + 5 == ememyfloor||boxcolor[1] == ememyfloor || boxcolor[1] + 5 == ememyfloor)
			{
				score = score + 3;
				COLOR(WHITE, BLACK);
				switch (ememyfloor)
				{
				case 1:
					clcount = 5;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 2:
					clcount = 10;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 3:
					clcount = 15;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 4:
					clcount = 20;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 5:
					clcount = 25;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 6:
					clcount = 30;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 7:
					clcount = 35;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 8:
					clcount = 40;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 9:
					clcount = 45;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 10:
					clcount = 50;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				default:
					break;
				}
				WAIT(100);
			}
			boxcolorbef = 1;
			boxcolor[0] = boxcolor[2];
			boxcolor[1] = boxcolor[3];
			boxcolor[2] = boxcolor[4];
			boxcolor[3] = 10;
			boxcolor[4] = 10;
			space = 0;
		}
		else if (colorwanacount == 3)
		{
			if (boxcolor[0] == ememyfloor || boxcolor[0] + 5 == ememyfloor || boxcolor[1] == ememyfloor || boxcolor[1] + 5 == ememyfloor || boxcolor[2] == ememyfloor || boxcolor[2] + 5 == ememyfloor)
			{
				score = score + 3;
				COLOR(WHITE, BLACK);
				switch (ememyfloor)
				{
				case 1:
					clcount = 5;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 2:
					clcount = 10;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 3:
					clcount = 15;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 4:
					clcount = 20;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 5:
					clcount = 25;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 6:
					clcount = 30;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 7:
					clcount = 35;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 8:
					clcount = 40;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 9:
					clcount = 45;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				case 10:
					clcount = 50;
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
					COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
					break;
				default:
					break;
				}
				WAIT(100);
			}
			boxcolorbef = 1;
			boxcolor[0] = boxcolor[3];
			boxcolor[1] = boxcolor[4];
			boxcolor[2] = 10;
			boxcolor[3] = 10;
			boxcolor[4] = 10;
			space = 0;
		}
		else if (colorwanacount == 4)
				{
					if (boxcolor[0] == ememyfloor || boxcolor[0] + 5 == ememyfloor || boxcolor[1] == ememyfloor || boxcolor[1] + 5 == ememyfloor || boxcolor[2] == ememyfloor || boxcolor[2] + 5 == ememyfloor || boxcolor[3] == ememyfloor || boxcolor[3] + 5 == ememyfloor)
					{
						score = score + 3;
						COLOR(WHITE, BLACK);
						switch (ememyfloor)
						{
						case 1:
							clcount = 5;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 2:
							clcount = 10;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 3:
							clcount = 15;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 4:
							clcount = 20;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 5:
							clcount = 25;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 6:
							clcount = 30;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 7:
							clcount = 35;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 8:
							clcount = 40;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 9:
							clcount = 45;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 10:
							clcount = 50;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						default:
							break;
						}
						WAIT(100);
					}
					boxcolorbef = 1;
					boxcolor[0] = boxcolor[4];
					boxcolor[1] = 10;
					boxcolor[2] = 10;
					boxcolor[3] = 10;
					boxcolor[4] = 10;
					space = 0;
				}
		else if (colorwanacount == 5)
				{
					if (boxcolor[0] == ememyfloor || boxcolor[0] + 5 == ememyfloor || boxcolor[1] == ememyfloor || boxcolor[1] + 5 == ememyfloor || boxcolor[2] == ememyfloor || boxcolor[2] + 5 == ememyfloor || boxcolor[3] == ememyfloor || boxcolor[3] + 5 == ememyfloor || boxcolor[4] == ememyfloor || boxcolor[4] + 5 == ememyfloor)
					{
						score = score + 3;
						COLOR(WHITE, BLACK);
						switch (ememyfloor)
						{
						case 1:
							clcount = 5;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 2:
							clcount = 10;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 3:
							clcount = 15;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 4:
							clcount = 20;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 5:
							clcount = 25;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 6:
							clcount = 30;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 7:
							clcount = 35;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 8:
							clcount = 40;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 9:
							clcount = 45;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						case 10:
							clcount = 50;
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　　／⌒⌒ヽ！　　"); LOCATE(186, clcount + 1); printf("　 ｜ﾉﾉﾚﾘヾ)　　　"); LOCATE(186, clcount + 2); printf("　 ﾉC|ﾟ‐ﾟﾉ|　　　"); LOCATE(186, clcount + 3); printf("　((⊂ﾘ介ﾘつ　　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　 "); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　　ﾉ"); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ ！　　/"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　　∥"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　　ﾉ( "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　　ｃ/"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　　/凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　　∥の"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| 　ﾉ(　 "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ 　ｃ/　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("　／⌒⌒ヽ 　/凵凵"); LOCATE(186, clcount + 1); printf(" ｜ﾉﾉﾚﾘヾ)　∥の　"); LOCATE(186, clcount + 2); printf(" ﾉC|ﾟ△ﾟﾉ| ﾉ(　ヮ "); LOCATE(186, clcount + 3); printf("((⊂ﾘ介ﾘつ ｃ/　　"); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("／⌒⌒ヽ 　/凵凵凵"); LOCATE(186, clcount + 1); printf("ﾉﾉﾚﾘヾ)　∥の の||"); LOCATE(186, clcount + 2); printf("C|ﾟ△ﾟﾉ| ﾉ(　ヮ レ"); LOCATE(186, clcount + 3); printf("⊂ﾘ介ﾘつ  ｃ/　　 "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒⌒ヽ 　/凵凵凵ヽ"); LOCATE(186, clcount + 1); printf("ﾉﾚﾘヾ)　∥の の|||"); LOCATE(186, clcount + 2); printf("|ﾟ△ﾟﾉ| ﾉ(　ヮ レ "); LOCATE(186, clcount + 3); printf("ﾘ介ﾘつ  ｃ/　　つ "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf("⌒ヽ 　/凵凵凵ヽ  "); LOCATE(186, clcount + 1); printf("ﾘヾ)　∥の の|||  "); LOCATE(186, clcount + 2); printf("△ﾟﾉ| ﾉ(　ヮ レ   "); LOCATE(186, clcount + 3); printf(" ﾘつ  ｃ/　　つ   "); WAIT(50);
							COLOR(WHITE, BLACK); LOCATE(186, clcount); printf(" 　/凵凵凵ヽ      "); LOCATE(186, clcount + 1); printf("　∥の の|||      "); LOCATE(186, clcount + 2); printf(" ﾉ(　ヮ レし      "); LOCATE(186, clcount + 3); printf(" ｃ/　　つ        ");
							break;
						default:
							break;
						}
						WAIT(100);
					}
					boxcolorbef = 1;
					boxcolor[0] = 10;
					boxcolor[1] = 10;
					boxcolor[2] = 10;
					boxcolor[3] = 10;
					boxcolor[4] = 10;
					space = 0;
				}
				else
				{

				}
	}
	if ((min == 0 && sec >1) || (min>0))
	{
		floortime = sec % 3;
		if (floortime == 0)
		{
			ememyfloorbef = ememyfloor;
			ememyfloor = rand() % 9 + 1;
		}
	}
	if ((ememyfloorbef - ememyfloor) != 0)
	{
		switch (ememyfloorbef)
		{
		case 1:COLOR(RED, RED); LOCATE(186, 5); printf("                  "); LOCATE(186, 6); printf("                  "); LOCATE(186, 7); printf("                  "); LOCATE(186, 8); printf("                  "); break;
		case 2:COLOR(CYAN, CYAN); LOCATE(186, 10); printf("                  "); LOCATE(186, 11); printf("                  "); LOCATE(186, 12); printf("                  "); LOCATE(186, 13); printf("                  "); break;
		case 3:COLOR(GREEN, GREEN); LOCATE(186, 15); printf("                  "); LOCATE(186, 16); printf("                  "); LOCATE(186, 17); printf("                  "); LOCATE(186, 18); printf("                  "); break;
		case 4:COLOR(BLUE, BLUE); LOCATE(186, 20); printf("                  "); LOCATE(186, 21); printf("                  "); LOCATE(186, 22); printf("                  "); LOCATE(186, 23); printf("                  "); break;
		case 5:COLOR(BROWN, BROWN); LOCATE(186, 25); printf("                  "); LOCATE(186, 26); printf("                  "); LOCATE(186, 27); printf("                  "); LOCATE(186, 28); printf("                  "); break;
		case 6:COLOR(RED, RED); LOCATE(186, 30); printf("                  "); LOCATE(186, 31); printf("                  "); LOCATE(186, 32); printf("                  "); LOCATE(186, 33); printf("                  "); break;
		case 7:COLOR(CYAN, CYAN); LOCATE(186, 35); printf("                  "); LOCATE(186, 36); printf("                  "); LOCATE(186, 37); printf("                  "); LOCATE(186, 38); printf("                  "); break;
		case 8:COLOR(GREEN, GREEN); LOCATE(186, 40); printf("                  "); LOCATE(186, 41); printf("                  "); LOCATE(186, 42); printf("                  "); LOCATE(186, 43); printf("                  "); break;
		case 9:COLOR(BLUE, BLUE); LOCATE(186, 45); printf("                  "); LOCATE(186, 46); printf("                  "); LOCATE(186, 47); printf("                  "); LOCATE(186, 48); printf("                  "); break;
		case 10:COLOR(BROWN, BROWN); LOCATE(186, 50); printf("                  "); LOCATE(186, 51); printf("                  "); LOCATE(186, 52); printf("                  "); LOCATE(186, 53); printf("                  "); break;
		default:
			break;
		}
		COLOR(WHITE, BLACK);
		switch (ememyfloor)
		{
		case 1:COLOR(WHITE, BLACK); LOCATE(186, 5); printf("　　／⌒⌒ヽ"); LOCATE(186, 6); printf("　　｜ﾉﾉﾚﾘヾ)"); LOCATE(186, 7); printf("　 ﾉC|ﾟ‐ﾟﾉ|"); LOCATE(186, 8); printf("　((⊂ﾘ介ﾘつ"); break;
		case 2:COLOR(WHITE, BLACK); LOCATE(186, 10); printf("　　／⌒⌒ヽ"); LOCATE(186, 11); printf("　　｜ﾉﾉﾚﾘヾ)"); LOCATE(186, 12); printf("　 ﾉC|ﾟ‐ﾟﾉ|"); LOCATE(186, 13); printf("　((⊂ﾘ介ﾘつ"); break;
		case 3:COLOR(WHITE, BLACK); LOCATE(186, 15); printf("　　／⌒⌒ヽ"); LOCATE(186, 16); printf("　　｜ﾉﾉﾚﾘヾ)"); LOCATE(186, 17); printf("　 ﾉC|ﾟ‐ﾟﾉ|"); LOCATE(186, 18); printf("　((⊂ﾘ介ﾘつ"); break;
		case 4:COLOR(WHITE, BLACK); LOCATE(186, 20); printf("　　／⌒⌒ヽ"); LOCATE(186, 21); printf("　　｜ﾉﾉﾚﾘヾ)"); LOCATE(186, 22); printf("　 ﾉC|ﾟ‐ﾟﾉ|"); LOCATE(186, 23); printf("　((⊂ﾘ介ﾘつ"); break;
		case 5:COLOR(WHITE, BLACK); LOCATE(186, 25); printf("　　／⌒⌒ヽ"); LOCATE(186, 26); printf("　　｜ﾉﾉﾚﾘヾ)"); LOCATE(186, 27); printf("　 ﾉC|ﾟ‐ﾟﾉ|"); LOCATE(186, 28); printf("　((⊂ﾘ介ﾘつ"); break;
		case 6:COLOR(WHITE, BLACK); LOCATE(186, 30); printf("　　／⌒⌒ヽ"); LOCATE(186, 31); printf("　　｜ﾉﾉﾚﾘヾ)"); LOCATE(186, 32); printf("　 ﾉC|ﾟ‐ﾟﾉ|"); LOCATE(186, 33); printf("　((⊂ﾘ介ﾘつ"); break;
		case 7:COLOR(WHITE, BLACK); LOCATE(186, 35); printf("　　／⌒⌒ヽ"); LOCATE(186, 36); printf("　　｜ﾉﾉﾚﾘヾ)"); LOCATE(186, 37); printf("　 ﾉC|ﾟ‐ﾟﾉ|"); LOCATE(186, 38); printf("　((⊂ﾘ介ﾘつ"); break;
		case 8:COLOR(WHITE, BLACK); LOCATE(186, 40); printf("　　／⌒⌒ヽ"); LOCATE(186, 41); printf("　　｜ﾉﾉﾚﾘヾ)"); LOCATE(186, 42); printf("　 ﾉC|ﾟ‐ﾟﾉ|"); LOCATE(186, 43); printf("　((⊂ﾘ介ﾘつ"); break;
		case 9:COLOR(WHITE, BLACK); LOCATE(186, 45); printf("　　／⌒⌒ヽ"); LOCATE(186, 46); printf("　　｜ﾉﾉﾚﾘヾ)"); LOCATE(186, 47); printf("　 ﾉC|ﾟ‐ﾟﾉ|"); LOCATE(186, 48); printf("　((⊂ﾘ介ﾘつ"); break;
		case 10:COLOR(WHITE, BLACK); LOCATE(186, 50); printf("　　／⌒⌒ヽ"); LOCATE(186, 51); printf("　　｜ﾉﾉﾚﾘヾ)"); LOCATE(186, 52); printf("　 ﾉC|ﾟ‐ﾟﾉ|"); LOCATE(186, 53); printf("　((⊂ﾘ介ﾘつ"); break;
		default:
			break;
		}
	}
	colorcount = -10;
}

void DispFPS()
{
	COLOR(RED);
	LOCATE(1, 1);
	printf("fps:%d", g_nCountFPS);
}

void Uninit()
{
	COLOR(WHITE, BLACK);
	LOCATE(150, 46);
	printf("━┓　　  ━┓");
	LOCATE(150, 47);
	printf("━┛ ━┓ ━┛ ━┓ ");
	LOCATE(150, 48);
	printf("　　 ━┛　　　━┛");
	LOCATE(150, 49);
	printf("＼　ヽ　i|　　/　 ／");
	WAIT(300);
	LOCATE(150, 46);
	printf("                           ");
	LOCATE(150, 47);
	printf("                           ");
	LOCATE(150, 48);
	printf("                           ");
	LOCATE(150, 49);
	printf("                           ");
	LOCATE(150, 43);
	printf("━┓　　  ━┓");
	LOCATE(150, 44);
	printf("━┛ ━┓ ━┛ ━┓ ");
	LOCATE(150, 45);
	printf("　　 ━┛　　　━┛");
	LOCATE(150, 46);
	printf("＼　ヽ　i|　　/　 ／");
	LOCATE(150, 47);
	printf("　＼ ヽ　 /|　　／");
	LOCATE(150, 48);
	printf("＼　　 ∧/ |　　　／");
	LOCATE(150, 49);
	printf("　 )＼/　　ヽ＿／/");
	WAIT(300);
	LOCATE(150, 41);
	printf("                           ");
	LOCATE(150, 42);
	printf("                           ");
	LOCATE(150, 43);
	printf("                           ");
	LOCATE(150, 44);
	printf("                           ");
	LOCATE(150, 45);
	printf("                           ");
	LOCATE(150, 47);
	printf("                           ");
	LOCATE(150, 48);
	printf("                           ");
	LOCATE(150, 49);
	printf("                           ");
	LOCATE(150, 40);
	printf("━┓　　  ━┓");
	LOCATE(150, 41);
	printf("━┛ ━┓ ━┛ ━┓ ");
	LOCATE(150, 42);
	printf("　　 ━┛　　　━┛");
	LOCATE(150, 43);
	printf("＼　ヽ　i|　　/　 ／");
	LOCATE(150, 44);
	printf("　＼ ヽ　 /|　　／");
	LOCATE(150, 45);
	printf("＼　　 ∧/ |　　　／");
	LOCATE(150, 46);
	printf("　 )＼/　　ヽ＿／/");
	LOCATE(150, 47);
	printf("　<　　∞―-∞ 〈");
	LOCATE(150, 48);
	printf("　｜　/凵凵凵ヽ　７");
	LOCATE(150, 49);
	printf("―/　∥の の|||　(―");
	WAIT(300);
	LOCATE(150, 40);
	printf("                           ");
	LOCATE(150, 41);
	printf("                           ");
	LOCATE(150, 42);
	printf("                           ");
	LOCATE(150, 43);
	printf("                           ");
	LOCATE(150, 44);
	printf("                           ");
	LOCATE(150, 45);
	printf("                           ");
	LOCATE(150, 47);
	printf("                           ");
	LOCATE(150, 48);
	printf("                           ");
	LOCATE(150, 49);
	printf("                           ");
	LOCATE(150, 36);
	printf("━┓　　  ━┓");
	LOCATE(150, 37);
	printf("━┛ ━┓ ━┛ ━┓ ");
	LOCATE(150, 38);
	printf("　　 ━┛　　　━┛");
	LOCATE(150, 39);
	printf("＼　ヽ　i|　　/　 ／");
	LOCATE(150, 40);
	printf("　＼ ヽ　 /|　　／");
	LOCATE(150, 41);
	printf("＼　　 ∧/ |　　　／");
	LOCATE(150, 42);
	printf("　 )＼/　　ヽ＿／/");
	LOCATE(150, 43);
	printf("　<　　∞―-∞ 〈");
	LOCATE(150, 44);
	printf("　｜　/凵凵凵ヽ　７");
	LOCATE(150, 45);
	printf("―/　∥の の|||　(―");
	LOCATE(150, 46);
	printf("　７ ﾉ(　ヮ レし /");
	LOCATE(150, 47);
	printf("　 ) ｃ/　　つ　｜");
	LOCATE(150, 48);
	printf("　<　 ｜　(　　∠");
	LOCATE(150, 49);
	printf("　 ヽ　Lﾉヽ)　 /");
}


int endtimeup()
{
	int x, y;
	COLOR(WHITE, BLACK);
	LOCATE(g_nx, g_ny);
	printf("　");
	for (x = 0; x < 90; x++)
	{
		for (y = 0; y < 50; y++)
		{
			LOCATE(3 + (2 * x), 4 + y);
			switch (map[x][y])
			{
			case 1:COLOR(WHITE, BLACK); printf("　"); break;
			case 2:COLOR(PURPLE, PURPLE); printf("■"); break;
			default:
				break;
			}
		}
	}
	for (x = 0; x < 20; x++)
	{
		for (y = 0; y < 51; y++)
		{
			LOCATE(185 + x, 4 + y);
			COLOR(WHITE, BLACK);
			printf(" ");
		}
	}
	COLOR(PINK, BLACK);
	LOCATE(40, 10);
	printf("■■■■■■■■■■■　　　　■■■■■■■■■　　　■　　　　　　　　　■　　■■■■■■■■■■■");
	LOCATE(40, 11);
	printf("          ■　　　　　　　　          ■　　　　　　　■■　　　　　　　■■　　■　　　　　　　　　　");
	LOCATE(40, 12);
	printf("          ■　　　　　　　　          ■　　　　　　　■　■　　　　　■　■　　■　　　　　　　　　　");
	LOCATE(40, 13);
	printf("          ■　　　　　　　　          ■　　　　　　　■　■　　　　　■　■　　■　　　　　　　　　　");
	LOCATE(40, 14);
	printf("          ■　　　　　　　　          ■　　　　　　　■　　■　　　■　　■　　■　　　　　　　　　　");
	LOCATE(40, 15);
	printf("          ■　　　　　　　　          ■　　　　　　　■　　■　　　■　　■　　■■■■■■■■■■■");
	LOCATE(40, 16);
	printf("          ■　　　　　　　　          ■　　　　　　　■　　　■　■　　　■　　■　　　　　　　　　　");
	LOCATE(40, 17);
	printf("          ■　　　　　　　　          ■　　　　　　　■　　　■　■　　　■　　■　　　　　　　　　　");
	LOCATE(40, 18);
	printf("          ■　　　　　　　　          ■　　　　　　　■　　　　■　　　　■　　■　　　　　　　　　　");
	LOCATE(40, 19);
	printf("          ■　　　　　　　　          ■　　　　　　　■　　　　■　　　　■　　■　　　　　　　　　　");
	LOCATE(40, 20);
	printf("          ■　　　　　　　　　■■■■■■■■■　　　■　　　　　　　　　■　　■■■■■■■■■■■");
	LOCATE(72, 40);
	printf("■　　　　　　　　　■　　■■■■■■■■■■■");
	LOCATE(72, 41);
	printf("■　　　　　　　　　■　　■　　　　　　　　　■");
	LOCATE(72, 42);
	printf("■　　　　　　　　　■　　■　　　　　　　　　■");
	LOCATE(72, 43);
	printf("■　　　　　　　　　■　　■　　　　　　　　　■");
	LOCATE(72, 44);
	printf("■　　　　　　　　　■　　■　　　　　　　　　■");
	LOCATE(72, 45);
	printf("■　　　　　　　　　■　　■■■■■■■■■■■");
	LOCATE(72, 46);
	printf("■　　　　　　　　　■　　■");
	LOCATE(72, 47);
	printf("■　　　　　　　　　■　　■");
	LOCATE(72, 48);
	printf("■　　　　　　　　　■　　■");
	LOCATE(72, 49);
	printf("■　　　　　　　　　■　　■");
	LOCATE(72, 50);
	printf("■■■■■■■■■■■　　■");
	COLOR(WHITE, BLACK);
	WAIT(3000);
	return 0;
}
void endpoint()
{
	COLOR(PINK, PINK);
	LOCATE(40, 10);
	printf("■■■■■■■■■■■　　　　■■■■■■■■■　　　■　　　　　　　　　■　　■■■■■■■■■■■");
	LOCATE(40, 11);
	printf("■");
	LOCATE(140, 11);
	printf("■");
	LOCATE(40, 12);
	printf("■");
	LOCATE(140, 12);
	printf("■");
	LOCATE(40, 13);
	printf("■");
	LOCATE(140, 13);
	printf("■");
	LOCATE(40, 14);
	printf("■");
	LOCATE(140, 14);
	printf("■");
	LOCATE(40, 15);
	printf("■");
	LOCATE(140, 15);
	printf("■");
	LOCATE(40, 16);
	printf("■");
	LOCATE(140, 16);
	printf("■");
	LOCATE(40, 17);
	printf("■");
	LOCATE(140, 17);
	printf("■");
	LOCATE(40, 18);
	printf("■■■■■■■■■■■　　　　■■■■■■■■■　　　■　　　　　　　　　■　　■■■■■■■■■■■\n");
	WAIT(200);
	COLOR(YELLOW,BLACK);
	LOCATE(65, 12);
	printf("●●●●●　●●●●●　●●●●●　●●●●●　●●●●●");
	WAIT(200);
	LOCATE(65, 13);
	printf("●　　　　　●　　　　　●　　　●　●      ●　●　　　　");
	WAIT(200);
	LOCATE(65, 14);
	printf("●●●●●　●　　　　　●　　　●　●●●●●　●●●●●");
	WAIT(200);
	LOCATE(65, 15);
	printf("　　　　●　●　　　　　●　　　●　●　　●　　●　　　　");
	WAIT(200);
	LOCATE(65, 16);
	printf("●●●●●　●●●●●　●●●●●　●      ●　●●●●●");
	WAIT(200);
	COLOR(PINK, PINK);
	LOCATE(40, 25);
	printf("■■■■■■■■■■■　　　　■■■■■■■■■　　　■　　　　　　　　　■　　■■■■■■■■■■■");
	int ix;
	for (ix = 26; ix < 50; ix++)
	{
		LOCATE(40, ix);
		printf("■");
		LOCATE(140, ix);
		printf("■");
	}
	LOCATE(40, 50);
	printf("■■■■■■■■■■■　　　　■■■■■■■■■　　　■　　　　　　　　　■　　■■■■■■■■■■■\n");
	int scoreh, scoret, scorem;
	if (score>=1000)
	{
		score = 999;
	}
	scoreh = score / 100;
	scoret = (score - (scoreh * 100)) / 10;
	scorem = score % 10;
	WAIT(300);
	COLOR(SKYBLUE, BLACK);
	int ia, ib, ic;
	ia = 70;
	ib = 84;
	ic =98;
	switch (scoreh)
	{
	case 0:
		LOCATE(ia, 28); printf("●●●●●");
		LOCATE(ia, 29); printf("●　　　●");
		LOCATE(ia, 30); printf("●　　　●");
		LOCATE(ia, 31); printf("●　　　●");
		LOCATE(ia, 32); printf("●●●●●");
		break;
	case 1:
		LOCATE(ia, 28); printf("　　●　　");
		LOCATE(ia, 29); printf("　●●　　");
		LOCATE(ia, 30); printf("　　●　　");
		LOCATE(ia, 31); printf("　　●　　");
		LOCATE(ia, 32); printf("●●●●●");
		break;
	case 2:
		LOCATE(ia, 28); printf("●●●●●");
		LOCATE(ia, 29); printf("　　　　●");
		LOCATE(ia, 30); printf("●●●●●");
		LOCATE(ia, 31); printf("●　　　　");
		LOCATE(ia, 32); printf("●●●●●");
		break;
	case 3:
		LOCATE(ia, 28); printf("●●●●●");
		LOCATE(ia, 29); printf("　　　　●");
		LOCATE(ia, 30); printf("●●●●●");
		LOCATE(ia, 31); printf("　　　　●");
		LOCATE(ia, 32); printf("●●●●●");
		break;
	case 4:
		LOCATE(ia, 28); printf("●　●　　");
		LOCATE(ia, 29); printf("●　●　　");
		LOCATE(ia, 30); printf("●●●●●");
		LOCATE(ia, 31); printf("　　●　　");
		LOCATE(ia, 32); printf("　　●　　");
		break;
	case 5:
		LOCATE(ia, 28); printf("●●●●●");
		LOCATE(ia, 29); printf("●　　　　");
		LOCATE(ia, 30); printf("●●●●●");
		LOCATE(ia, 31); printf("　　　　●");
		LOCATE(ia, 32); printf("●●●●●");
		break;
	case 6:
		LOCATE(ia, 28); printf("●●●●●");
		LOCATE(ia, 29); printf("●　　　　");
		LOCATE(ia, 30); printf("●●●●●");
		LOCATE(ia, 31); printf("●　　　●");
		LOCATE(ia, 32); printf("●●●●●");
		break;
	case 7:
		LOCATE(ia, 28); printf("●●●●●");
		LOCATE(ia, 29); printf("　　　　●");
		LOCATE(ia, 30); printf("　　　　●");
		LOCATE(ia, 31); printf("　　　　●");
		LOCATE(ia, 32); printf("　　　　●");
		break;
	case 8:
		LOCATE(ia, 28); printf("●●●●●");
		LOCATE(ia, 29); printf("●　　　●");
		LOCATE(ia, 30); printf("●●●●●");
		LOCATE(ia, 31); printf("●　　　●");
		LOCATE(ia, 32); printf("●●●●●");
		break;
	case 9:
		LOCATE(ia, 28); printf("●●●●●");
		LOCATE(ia, 29); printf("●　　　●");
		LOCATE(ia, 30); printf("●●●●●");
		LOCATE(ia, 31); printf("　　　　●");
		LOCATE(ia, 32); printf("●●●●●");
		break;
	default:
		break;
	}
	WAIT(300);
	switch (scoret)
	{
	case 0:
		LOCATE(ib, 28); printf("●●●●●");
		LOCATE(ib, 29); printf("●　　　●");
		LOCATE(ib, 30); printf("●　　　●");
		LOCATE(ib, 31); printf("●　　　●");
		LOCATE(ib, 32); printf("●●●●●");
		break;
	case 1:
		LOCATE(ib, 28); printf("　　●　　");
		LOCATE(ib, 29); printf("　●●　　");
		LOCATE(ib, 30); printf("　　●　　");
		LOCATE(ib, 31); printf("　　●　　");
		LOCATE(ib, 32); printf("●●●●●");
		break;
	case 2:
		LOCATE(ib, 28); printf("●●●●●");
		LOCATE(ib, 29); printf("　　　　●");
		LOCATE(ib, 30); printf("●●●●●");
		LOCATE(ib, 31); printf("●　　　　");
		LOCATE(ib, 32); printf("●●●●●");
		break;
	case 3:
		LOCATE(ib, 28); printf("●●●●●");
		LOCATE(ib, 29); printf("　　　　●");
		LOCATE(ib, 30); printf("●●●●●");
		LOCATE(ib, 31); printf("　　　　●");
		LOCATE(ib, 32); printf("●●●●●");
		break;
	case 4:
		LOCATE(ib, 28); printf("●　●　　");
		LOCATE(ib, 29); printf("●　●　　");
		LOCATE(ib, 30); printf("●●●●●");
		LOCATE(ib, 31); printf("　　●　　");
		LOCATE(ib, 32); printf("　　●　　");
		break;
	case 5:
		LOCATE(ib, 28); printf("●●●●●");
		LOCATE(ib, 29); printf("●　　　　");
		LOCATE(ib, 30); printf("●●●●●");
		LOCATE(ib, 31); printf("　　　　●");
		LOCATE(ib, 32); printf("●●●●●");
		break;
	case 6:
		LOCATE(ib, 28); printf("●●●●●");
		LOCATE(ib, 29); printf("●　　　　");
		LOCATE(ib, 30); printf("●●●●●");
		LOCATE(ib, 31); printf("●　　　●");
		LOCATE(ib, 32); printf("●●●●●");
		break;
	case 7:
		LOCATE(ib, 28); printf("●●●●●");
		LOCATE(ib, 29); printf("　　　　●");
		LOCATE(ib, 30); printf("　　　　●");
		LOCATE(ib, 31); printf("　　　　●");
		LOCATE(ib, 32); printf("　　　　●");
		break;
	case 8:
		LOCATE(ib, 28); printf("●●●●●");
		LOCATE(ib, 29); printf("●　　　●");
		LOCATE(ib, 30); printf("●●●●●");
		LOCATE(ib, 31); printf("●　　　●");
		LOCATE(ib, 32); printf("●●●●●");
		break;
	case 9:
		LOCATE(ib, 28); printf("●●●●●");
		LOCATE(ib, 29); printf("●　　　●");
		LOCATE(ib, 30); printf("●●●●●");
		LOCATE(ib, 31); printf("　　　　●");
		LOCATE(ib, 32); printf("●●●●●");
		break;
	default:
		break;
	}
	WAIT(300);
	switch (scorem)
	{
	case 0:
		LOCATE(ic, 28); printf("●●●●●");
		LOCATE(ic, 29); printf("●　　　●");
		LOCATE(ic, 30); printf("●　　　●");
		LOCATE(ic, 31); printf("●　　　●");
		LOCATE(ic, 32); printf("●●●●●");
		break;
	case 1:
		LOCATE(ic, 28); printf("　　●　　");
		LOCATE(ic, 29); printf("　●●　　");
		LOCATE(ic, 30); printf("　　●　　");
		LOCATE(ic, 31); printf("　　●　　");
		LOCATE(ic, 32); printf("●●●●●");
		break;
	case 2:
		LOCATE(ic, 28); printf("●●●●●");
		LOCATE(ic, 29); printf("　　　　●");
		LOCATE(ic, 30); printf("●●●●●");
		LOCATE(ic, 31); printf("●　　　　");
		LOCATE(ic, 32); printf("●●●●●");
		break;
	case 3:
		LOCATE(ic, 28); printf("●●●●●");
		LOCATE(ic, 29); printf("　　　　●");
		LOCATE(ic, 30); printf("●●●●●");
		LOCATE(ic, 31); printf("　　　　●");
		LOCATE(ic, 32); printf("●●●●●");
		break;
	case 4:
		LOCATE(ic, 28); printf("●　●　　");
		LOCATE(ic, 29); printf("●　●　　");
		LOCATE(ic, 30); printf("●●●●●");
		LOCATE(ic, 31); printf("　　●　　");
		LOCATE(ic, 32); printf("　　●　　");
		break;
	case 5:
		LOCATE(ic, 28); printf("●●●●●");
		LOCATE(ic, 29); printf("●　　　　");
		LOCATE(ic, 30); printf("●●●●●");
		LOCATE(ic, 31); printf("　　　　●");
		LOCATE(ic, 32); printf("●●●●●");
		break;
	case 6:
		LOCATE(ic, 28); printf("●●●●●");
		LOCATE(ic, 29); printf("●　　　　");
		LOCATE(ic, 30); printf("●●●●●");
		LOCATE(ic, 31); printf("●　　　●");
		LOCATE(ic, 32); printf("●●●●●");
		break;
	case 7:
		LOCATE(ic, 28); printf("●●●●●");
		LOCATE(ic, 29); printf("　　　　●");
		LOCATE(ic, 30); printf("　　　　●");
		LOCATE(ic, 31); printf("　　　　●");
		LOCATE(ic, 32); printf("　　　　●");
		break;
	case 8:
		LOCATE(ic, 28); printf("●●●●●");
		LOCATE(ic, 29); printf("●　　　●");
		LOCATE(ic, 30); printf("●●●●●");
		LOCATE(ic, 31); printf("●　　　●");
		LOCATE(ic, 32); printf("●●●●●");
		break;
	case 9:
		LOCATE(ic, 28); printf("●●●●●");
		LOCATE(ic, 29); printf("●　　　●");
		LOCATE(ic, 30); printf("●●●●●");
		LOCATE(ic, 31); printf("　　　　●");
		LOCATE(ic, 32); printf("●●●●●");
		break;
	default:
		break;
	}
	WAIT(500);
	COLOR(YELLOW);
	LOCATE(54, 37); printf("●●●●●　　　●　　　●　　　●　●　　　●");
	WAIT(200);
	LOCATE(54, 38); printf("●      ●　　●　●　　●●　　●　●　　●　");
	WAIT(200);
	LOCATE(54, 39); printf("●●●●●　●●●●●　●　●　●　●●●　　");
	WAIT(200);
	LOCATE(54, 40); printf("●    ●　　●　　　●　●　　●●　●　　●　");
	WAIT(200);
	LOCATE(54, 41); printf("●      ●　●　　　●　●　　　●　●　　　●");
	WAIT(500);
	COLOR(CORAL);
	if (score<30)
	{
		LOCATE(110, 35); printf("　　　　●　　　　");
		LOCATE(110, 36); printf("　　　●　●　　　");
		LOCATE(110, 37); printf("　　●　　　●　　");
		LOCATE(110, 38); printf("　●　　　　　●　");
		LOCATE(110, 39); printf("●●●●●●●●●");
		LOCATE(110, 40); printf("●　　　　　　　●");
		LOCATE(110, 41); printf("●　　　　　　　●");
		LOCATE(110, 42); printf("●　　　　　　　●");
		LOCATE(110, 43); printf("●　　　　　　　●");
	}
	else
	{
		LOCATE(110, 35); printf("●●●●●●●●●");
		LOCATE(110, 36); printf("●");
		LOCATE(110, 37); printf("●");
		LOCATE(110, 38); printf("●");
		LOCATE(110, 39); printf("●●●●●●●●●");
		LOCATE(110, 40); printf("　　　　　　　　●");
		LOCATE(110, 41); printf("　　　　　　　　●");
		LOCATE(110, 42); printf("　　　　　　　　●");
		LOCATE(110, 43); printf("●●●●●●●●●");
	}
}

/*void SetField(float fPosX, float fPosY, float fWidth)
{
	int nCntField;
	for (nCntField=0,nCntField<MAXFIELD;nCntField++)
}*/
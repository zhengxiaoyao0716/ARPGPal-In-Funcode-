#include "CommonAPI.h"

#include <time.h>
#include <Mmsystem.h>  
#pragma comment ( lib, "Winmm.lib" )  
///******************************全局变量***************************************/

//关卡
extern short chapter;

//实例数量
extern short ob_num;

//地图中心点
extern float map_centerX, map_centerY;

//是否是新游戏
extern bool isNew;

//灵珠
extern short key;

///******************************玩家数据***************************************/

short getPlHp(short pl_id);
short getPlLv(short pl_id);

short getPlDirX(short pl_id);
short getPlDirY(short pl_id);

void setPlLv(short pl_id, short value);

void setResusPos(short pl_id, float resusX, float resusY);

//刷新数据
void rebuildPl();

///********************************链表*****************************************/

#define Box struct box
#define NEW (Box*)malloc(sizeof(Box))
Box
{
	char *name;
	short value;
	Box *next;
} *obList;

//创建
void creatList();
//挂箱（参数szSrcName为NULL表示不创建实例）
void addBox(const char *szSrcName, const char *szMyName, short value);

///******************************功能函数***************************************/

//数据还原
void dataClear()
{
	if (isNew)
	{
		//第一关
		chapter = 0;

		isNew = false;
		//等级还原
		setPlLv(0, 1);
		setPlLv(1, 1);

		//地图位置还原
		map_centerX = 44, map_centerY = -73.5f;

		//玩家复活坐标还原
		setResusPos(0, -10, 10); setResusPos(1, -15, 10);

		//灵珠还原
		key = 0;
	}

	/*全局变量还原*/

	//刷新玩家数据
	rebuildPl();

	//实例数归零
	ob_num = 0;

	//产生随机种子
	srand(time(NULL));

	//关卡上限检测
	if (chapter > 0) chapter = 0;
}

//设置地图
void setMap()
{
	dSetSpritePosition( "map", map_centerX, map_centerY);
	float map_moveX = map_centerX - 44;
	float map_moveY = map_centerY + 73.5f;
	if (map_moveX||map_moveY)
	{
		Box *p = obList;
		Box *q = p->next;
		while (p->name)
		{
			if (!dGetSpriteIsMounted( p->name )&&!strstr(p->name, "good"))
				dSetSpritePosition(p->name, map_moveX + dGetSpritePositionX(p->name),
				map_moveY + dGetSpritePositionY(p->name));
			p = q;
			q = p->next;
		}
	}
}

//加载关卡
void loadChapter()
{
	//禁用鼠标
	dCursorOff();

	//载入游戏场景
	char chapterName[] = "chapter0.t2d";
	chapterName[7] = (char)(chapter + 48);
	dLoadMap( chapterName );

	//播放游戏界面bgm，蝶恋
	PlaySound(NULL, NULL, SND_PURGE);
	//PlaySound("game/data/audio/bgm_dielian.wav", NULL, SND_ASYNC|SND_LOOP);

	//新建链表
	creatList();

	//*存入中立数据
	short netral_race, netral_indi;                      //种族、个体
	for (netral_race = 1; netral_race < 7; netral_race++)
	{
		for (netral_indi = 1; netral_indi < 6; netral_indi++)
		{
			char *netral_name = dMakeSpriteName("netral", 10 * netral_race + netral_indi);
			addBox(NULL, netral_name, netral_race);      //变量复用：race代表hp
		}
	}
	//*存入敌人数据
	short enemy_race, enemy_indi;                        //种族、个体
	for (enemy_race = 1; enemy_race < 10; enemy_race++)
	{
		for (enemy_indi = 1; enemy_indi < 11 - enemy_race; enemy_indi++)
		{
			char *enemy_name = dMakeSpriteName("enemy", 10 * enemy_race + enemy_indi);
			addBox(NULL, enemy_name, 1 + enemy_race);        //变量复用：race代表hp
			//设置反弹力度
			dSetSpriteRestitution( enemy_name, 0.3f );
		}
	}
	//*存入Boss数据
	for (enemy_race = 0; enemy_race < 5; enemy_race++)
	{
		char *enemy_name = dMakeSpriteName("enemyBoss", enemy_race);
		addBox(NULL, enemy_name, 23 + 10 * enemy_race);   //变量复用：race代表hp
		//设置运动型Boss反弹力度
		if (!dGetSpriteIsMounted( enemy_name )) dSetSpriteRestitution( enemy_name, 0.3f );
	}
	
	//设置地图位置
	setMap();
}

//移动地图
void moveMap()
{
	//记录地图上一帧运动状态，true:Vx!=0, false:Vx==0
	static bool lastMapVxState = false;

	//如果之前地图不动
	if (!lastMapVxState)
	{
		//玩家的运动趋势，坐标+方向
		float trend0, trend1;
		trend0 = 20 * getPlDirX(0) + dGetSpritePositionX("player0");
		trend1 = 20 * getPlDirX(1) + dGetSpritePositionX("player1");
		if (!getPlHp(0)) trend0 = trend1;
		if (!getPlHp(1)) trend1 = trend0;
		//地图推动中取消运动趋势
		if (dGetSpriteLinearVelocityX("map")||dGetSpriteLinearVelocityY("map"))
			trend0 = trend1 = 0;

		//运动趋势：向右越过镜头
		if (trend0 > 40 && trend1 > 40 && map_centerX> -88)
		{
			//地图中心坐标变动
			map_centerX-=22;
			//移动地图到新的坐标
			dSpriteMoveTo("map", map_centerX, map_centerY, 30, 1);
		}
		//运动趋势：向左越过镜头
		else if (trend0 < -40 && trend1 < -40 && map_centerX < 88)
		{
			map_centerX+=22;
			dSpriteMoveTo("map", map_centerX, map_centerY, 30, 1);
		}
	}

	/*y轴方向，与上一段代码同理*/
	if (!lastMapVxState)
	{
		float trend0, trend1;
		trend0 = 10 * getPlDirY(0) + dGetSpritePositionY("player0");
		trend1 = 10 * getPlDirY(1) + dGetSpritePositionY("player1");
		if (!getPlHp(0)) trend0 = trend1;
		if (!getPlHp(1)) trend1 = trend0;
		if (dGetSpriteLinearVelocityX("map")||dGetSpriteLinearVelocityY("map"))
			trend0 = trend1 = 0;

		if (trend0 < -25 && trend1 < -25 && map_centerY < 73.5f)
		{
			map_centerY+=14.7f;
			dSpriteMoveTo("map", map_centerX, map_centerY, 30, 1);
		}
		else if (trend0 > 25 && trend1 > 25 && map_centerY > -73.5f)
		{
			map_centerY-=14.7f;
			dSpriteMoveTo("map", map_centerX, map_centerY, 30, 1);
		}
	}

	/*与地图同时移动*/
	//地图运动速度
	float mapSpeedX = dGetSpriteLinearVelocityX("map");
	float mapSpeedY = dGetSpriteLinearVelocityY("map");
	//如果之前地图运动
	if (lastMapVxState)
	{
		//玩家跟随地图
		if (getPlHp(0)) dSetSpriteLinearVelocity("player0", mapSpeedX, mapSpeedY);
		if (getPlHp(1)) dSetSpriteLinearVelocity("player1", mapSpeedX, mapSpeedY);

		Box *p = obList;
		Box *q = p->next;
		while (p->name)
		{
			if (!dGetSpriteIsMounted( p->name )&&!(strstr(p->name, "good")))
			{
				dSetSpriteLinearVelocity(p->name, mapSpeedX, mapSpeedY);
			}
			p = q;
			q = p->next;
		}
	}
	//写入地图这一帧运动情况
	lastMapVxState = (mapSpeedX||mapSpeedY);
}

//发送消息
void sendMessage(char* message)
{
	//发送间隔
	extern float runTime;
	static float lastCallTime = 0;
	if (runTime - lastCallTime < 0.8f) return;
	lastCallTime = runTime;

	//创建实例
	dCloneSprite("textBox", "ob_textBox");
	dCloneSprite("messageText", "ob_messageText");
	//置入场景
	dSetSpritePosition("ob_textBox", 0, 0);
	dSetSpritePosition("ob_messageText", 0, 0);
	//显示文字
	dSetTextString("ob_messageText", message);
	//向上慢移
	dSetSpriteLinearVelocityY("ob_textBox", -5);
	dSetSpriteLinearVelocityY("ob_messageText", -5);
	//1s后消失
	dSetSpriteLifeTime("ob_textBox", 3);
	dSetSpriteLifeTime("ob_messageText", 3);
}

//计算距离（未计算勾股）
float getDistance(const char *startName, const char *endName)
{
	float startX = dGetSpritePositionX(startName);
	float startY = dGetSpritePositionY(startName);
	float endX = dGetSpritePositionX(endName);
	float endY = dGetSpritePositionY(endName);

	if (startX > endX) startX-=endX;
	else startX = endX-startX;
	if (startY > endY) startY-=endY;
	else startY = endY-startY;
	return startX + startY;
}
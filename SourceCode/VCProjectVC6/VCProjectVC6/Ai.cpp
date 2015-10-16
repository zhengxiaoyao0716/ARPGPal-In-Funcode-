#include "CommonAPI.h"

#include <Mmsystem.h>  
#pragma comment ( lib, "Winmm.lib" )  
///******************************功能函数***************************************/

//计算距离（未计算勾股）
float getDistance(const char *startName, const char *endName);

///********************************链表*****************************************/

#define Box struct box
extern Box
{
	char *name;
	short value;
	Box *next;
} *obList;

///*******************************AI设定****************************************/

//晃悠
void randMove(const char *name)
{
	//如果是静止型，跳过运动部分
	if (dGetSpriteIsMounted( name )) return;
	//随机移动
	short ranDirX = dRandomRange( -1, 1 );
	short ranDirY = dRandomRange( -1, 1 );
	dSetSpriteLinearVelocity(name, (float)3 * ranDirX, (float)3 * ranDirY);

	//调整面向
	ranDirX+=3 * ranDirY;                    //ranDirY变量复用：存放面向信息
	if (ranDirX==-1||ranDirX==2) ranDirY = 0;
	else if (ranDirX <-2) ranDirY = 1;
	else if (ranDirX > 2) ranDirY = 2;
	else ranDirY = 3;dMakeSpriteName(name, 3);
	char *ani_name;
	//构建Boss动画名
	if (strstr(name, "Boss")) ani_name = dMakeSpriteName(name, ranDirY);
	//构建一般敌人动画名
	else if(strstr(name, "enemy"))
	{
		ani_name = new char[8];
		strcpy(ani_name, name);
		ani_name[6] = (char)48;
		ani_name = dMakeSpriteName(ani_name, ranDirY);
	}
	//构建中立生物动画
	else if(strstr(name, "netral"))
	{
		ani_name = new char[9];
		strcpy(ani_name, name);
		ani_name[7] = (char)48;
		ani_name = dMakeSpriteName(ani_name, ranDirY);
	}
	dAnimateSpritePlayAnimation( name, ani_name, 0);
}
//施法
void enemyFire(const char *enemy, short pl_id)
{
	//火力周期轴
	static short fireAxis = 0;
	//按Boss等级递减周期
	if (fireAxis%(54 - enemy[9]))
	{
		//即将施法，播放警告
		if (!(++fireAxis%(54 - enemy[9])))
			dPlayEffect("warning", 1.5f, dGetSpritePositionX(enemy), dGetSpritePositionY(enemy), 0);
		return;
	}
	fireAxis++;
	//技能模板名
	char *fire_name = dMakeSpriteName(enemy, 9);
	//技能实例名
	char *thisFire = dMakeSpriteName(fire_name, 0);
	//创建实例
	dCloneSprite(fire_name, thisFire);

	//技能释放处坐标，方向*施法距离+施法者坐标
	float fPosX = dGetSpritePositionX(enemy);
	float fPosY = dGetSpritePositionY(enemy);
	//释放技能
	dSetSpritePosition(thisFire, fPosX, fPosY);

	/*技能转向玩家朝向*/
	//计算角度
	char *pl_name = dMakeSpriteName("player", pl_id);
	float fRot = dCalLineRotation(
		dGetSpritePositionX(pl_name), dGetSpritePositionY(pl_name), fPosX, fPosY );
	//技能旋转
	dSetSpriteRotation(thisFire, fRot);
	//追向玩家
	dSpriteMoveTo(thisFire, dGetSpritePositionX(pl_name), dGetSpritePositionY(pl_name), 20, 1);
	//音效
	PlaySound(NULL, NULL, SND_PURGE);
	PlaySound("game/data/audio/enemy_fire.wav", NULL, SND_ASYNC);
	//生命时长
	dSetSpriteLifeTime(thisFire, 1);
}
//追击
void enemyPursue(const char *enemy, short pl_id)
{
	//玩家
	char *pl_name = dMakeSpriteName("player", pl_id);
	//追击速度
	float enemy_speed = 0;

	//调整面向
	short disX = (int)(dGetSpritePositionX(pl_name) - dGetSpritePositionX(enemy));
	short disY = (int)(dGetSpritePositionY(pl_name) - dGetSpritePositionY(enemy));
	disX = disX > 0 ? 2 : 0;             //disX、disY变量复用：
	disY = disY > 0 ? 0 : 1;             //disX + disY存储方向信息
	char *ani_name;
	if (strstr(enemy, "Boss"))
	{
		//构建Boss动画名
		ani_name = dMakeSpriteName(enemy, disX + disY);
		//Boss速度
		enemy_speed = 10;
	}
	else
	{
		//构建一般敌人动画名
		ani_name = new char[8];
		strcpy(ani_name, enemy);
		ani_name[6] = (char)48;
		ani_name = dMakeSpriteName(ani_name, disX + disY);
		//一般敌人速度
		enemy_speed = 8;
	}
	dAnimateSpritePlayAnimation( enemy, ani_name, 0 );
	//追向玩家
	dSpriteMoveTo(enemy, dGetSpritePositionX(pl_name), dGetSpritePositionY(pl_name), enemy_speed, 1);
}
//进攻
void enemyAttack(const char *enemy, short pl_id)
{
	//如果是Boss
	if (strstr(enemy, "Boss"))
	{
		enemyFire(enemy, pl_id);
		//如果是静止型，跳过运动部分
		if (dGetSpriteIsMounted( enemy )) return;
	}
	enemyPursue(enemy, pl_id);
}
//回巢
void bossBack(const char *boss)
{
	char *box = dMakeSpriteName("box", boss[9] - 48);
	dSpriteMoveTo(boss, dGetSpritePositionX(box), dGetSpritePositionY(box), 10, 1);

	//调整面向
	short disX = (int)(dGetSpritePositionX(box) - dGetSpritePositionX(boss));
	short disY = (int)(dGetSpritePositionY(box) - dGetSpritePositionY(boss));
	disX = disX > 0 ? 2 : 0;             //disX、disY变量复用：
	disY = disY > 0 ? 0 : 1;             //disX + disY存储方向信息
	char *ani_name;
	//构建Boss动画名
	ani_name = dMakeSpriteName(boss, disX + disY);
	dAnimateSpritePlayAnimation( boss, ani_name, 0 );
}
//搜寻玩家
void searchPl(const char *name, bool isPlAlive[2])
{
	//与玩家距离
	float toPlDis[2];
	if (isPlAlive[0]) toPlDis[0] = getDistance("player0", name);
	else toPlDis[0] = 100;
	if (isPlAlive[1]) toPlDis[1] = getDistance("player1", name);
	else toPlDis[1] = 100;
	
	//最近玩家
	short pl_id = toPlDis[0] < toPlDis[1] ? 0 : 1;

	/*响应*/
	//离玩家较远
	if (toPlDis[pl_id] > 35)
	{
		//boss回巢守宝
		if (strstr(name, "Boss")&&getDistance(dMakeSpriteName("box", name[9]), name) > 25)
			bossBack(name);
		else
		{
			//视野外暂停
			if (toPlDis[pl_id] > 125) dSetSpriteLinearVelocity( name, 0, 0 );
			//视野内晃悠
			else randMove(name);
		}
	}
	//敌人靠近玩家
	else
	{
		//敌人进攻
		if (strstr(name, "netral")) randMove(name);
		//中立继续晃悠
		else if (strstr(name, "enemy")) enemyAttack(name, pl_id);
	}
}

//AI调配
void aiRun(bool isPlAlive[2])
{
	Box *p = obList;
	Box *q = p->next;
	while (p->name)
	{
		if ( strstr(p->name, "enemy")||strstr(p->name, "netral") ) searchPl(p->name, isPlAlive);
		p = q;
		q = p->next;
	}
}
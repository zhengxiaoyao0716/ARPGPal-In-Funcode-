#include <Stdio.h>
#include "CommonAPI.h"

#include <Mmsystem.h>  
#pragma comment ( lib, "Winmm.lib" )  
///******************************功能函数***************************************/

//发送消息
void sendMessage(char* message);

///********************************链表*****************************************/

//挂箱（参数szSrcName为NULL表示不创建实例）
void addBox(const char *szSrcName, const char *szMyName, short value);
//弃箱
void cutBox(const char *name);

///******************************玩家数据***************************************/

static struct player
{
	short hp;              //玩家体力
	short mag;             //玩家气力
	short exp;             //玩家经验
	short lv;              //玩家等级
	short gold;            //玩家金钱
	short weapon;          //武器力量
	
	//玩家速度方向，-1,0,1
	short dirX;
	short dirY;
	//玩家上次朝向, -1,0,1
	short lastDirX;
	short lastDirY;

	//玩家复活坐标
	float resusX;
	float resusY;

	//技能冷却时间
	float magRest;
	//玩家保护时间
	float proTime;

}player[2];

short getPlHp(short pl_id){return player[pl_id].hp;}
short getPlMag(short pl_id){return player[pl_id].mag;}
short getPlExp(short pl_id){return player[pl_id].exp;}
short getPlLv(short pl_id){return player[pl_id].lv;}
short getPlGold(short pl_id){return player[pl_id].gold;}
short getPlWeapon(short pl_id){return player[pl_id].weapon;}

short getPlDirX(short pl_id){return player[pl_id].dirX;}
short getPlDirY(short pl_id){return player[pl_id].dirY;}
short getLastDirX(short pl_id){return player[pl_id].lastDirX;}
short getLastDirY(short pl_id){return player[pl_id].lastDirY;}

float getResusX(short pl_id){return player[pl_id].resusX;}
float getResusY(short pl_id){return player[pl_id].resusY;}

float getProTime(short pl_id){return player[pl_id].proTime;}


void setPlHp(short pl_id, short value){player[pl_id].hp = value;}
void setPlMag(short pl_id, short value){player[pl_id].mag = value;}
void setPlExp(short pl_id, short value){player[pl_id].exp = value;}
void setPlLv(short pl_id, short value){player[pl_id].lv = value;}
void setPlWeapon(short pl_id, short value){player[pl_id].weapon = value;}

void setPlDir(short pl_id, short dirX, short dirY)
{player[pl_id].dirX = dirX;player[pl_id].dirY = dirY;}
void setLastDir(short pl_id, short lastDirX, short lastDirY)
{player[pl_id].lastDirX = lastDirX; player[pl_id].lastDirY = lastDirY;}

void setResusPos(short pl_id, float resusX, float resusY)
{player[pl_id].resusX = resusX;player[pl_id].resusY = resusY;}

void setMagRest(short pl_id, short value){player[pl_id].magRest = value;}
void setProTime(short pl_id, short value){player[pl_id].proTime = value;}

///******************************玩家功能***************************************/

//体力增加
bool addPlHp(short pl_id, short value)
{
	if (player[pl_id].hp>=8 + 2 * player[pl_id].lv) return false;
	player[pl_id].hp+=value;
	//上限检测
	if (player[pl_id].hp > 8 + 2 * player[pl_id].lv)
		player[pl_id].hp = 8 + 2 * player[pl_id].lv;
	return true;
}
//气力增加
bool addPlMag(short pl_id, short value)
{
	if (player[pl_id].mag>=9 + 3 * player[pl_id].lv) return false;
	player[pl_id].mag+=value;
	//上限检测
	if (player[pl_id].mag > 9 + 3 * player[pl_id].lv)
		player[pl_id].mag = 9 + 3 * player[pl_id].lv;
	return true;
}
//得到铜钱
bool addPlGold(short pl_id, short value)
{
	if (player[pl_id].gold>=9999) return false;
	player[pl_id].gold+=value;
	if (player[pl_id].gold > 9999)
		player[pl_id].gold = 9999;
	return true;
}
//失去铜钱
bool losePlGold(short pl_id, short value)
{
	if (player[pl_id].gold < value) return false;
	player[pl_id].gold-=value;
	return true;
}

//刷新数据
void rebuildPl()
{
	player[0].hp = 8 + 2 * player[0].lv;
	player[1].hp = 8 + 2 * player[1].lv;
	player[0].exp = player[1].exp = 0;
	player[0].mag = 9 + 3 * player[0].lv;
	player[1].mag = 9 + 3 * player[0].lv;
	player[0].gold = player[1].gold = 0;
	player[0].weapon = player[1].weapon = 0;


	player[0].dirX = player[1].dirX = player[0].dirY = player[1].dirY = 0;
	player[0].lastDirX = player[1].lastDirX = 0;
	player[0].lastDirY = player[1].lastDirY = 1;

	player[0].magRest = player[1].magRest = 2;
	player[0].proTime = player[1].proTime = 3;
}

//播放玩家动画，记录玩家朝向，参数：脉冲轴，玩家ID
void playerWork(long axis, short pl_id)
{
	if (!player[pl_id].hp) return; 
	char *pl_name = dMakeSpriteName("player", pl_id);
	short pl_frame = axis%4;
	short pl_dir = player[pl_id].dirX + 3 * player[pl_id].dirY;
	switch (pl_dir)
	{
	case 3: 
		{
			player[pl_id].lastDirX = 0;
			player[pl_id].lastDirY = 1;
		}break;
	case -1:
		{
			player[pl_id].lastDirX = -1;
			player[pl_id].lastDirY = 0;
			pl_frame+=4;
		}break;
	case 1:
		{
			player[pl_id].lastDirX = 1;
			player[pl_id].lastDirY = 0;
			pl_frame+=8;
		}break;
	case -3:
		{
			player[pl_id].lastDirX = 0;
			player[pl_id].lastDirY = -1;
			pl_frame+=12;
		}break;
	case 2:
		{
			player[pl_id].lastDirX = -1;
			player[pl_id].lastDirY = 1;
			pl_frame+=16;
		}break;
	case -4:
		{
			player[pl_id].lastDirX = -1;
			player[pl_id].lastDirY = -1;
			pl_frame+=20;
		}break;
	case 4:
		{
			player[pl_id].lastDirX = 1;
			player[pl_id].lastDirY = 1;
			pl_frame+=24;
		}break;
	case -2:
		{
			player[pl_id].lastDirX = 1;
			player[pl_id].lastDirY = -1;
			pl_frame+=28;
		}break;
	default:
		pl_frame = 4 * (dGetStaticSpriteFrame( pl_name )/4);
		break;
	}
	dSetStaticSpriteFrame( pl_name, pl_frame);
}

//更新技能冷却时间
void magRestChange(short pl_id)
{
	if (player[pl_id].magRest == 1)
	{
		//删除技能
		cutBox(dMakeSpriteName("ob_magic", pl_id));
		//技能图标点亮
		dSetSpriteColorAlpha(dMakeSpriteName("magIcon", pl_id), 255);
	}
	player[pl_id].magRest+=0.2f;
}
//更新玩家保护时间
void proTimeChange(short pl_id)
{
	if (player[pl_id].proTime > 0)
	{
		player[pl_id].proTime-=0.2f;
		const char *pl_name = dMakeSpriteName("player", pl_id);
		if (player[pl_id].proTime <= 0) player[pl_id].proTime = 0;
		dSetSpriteColorAlpha( pl_name, (int)(255 - 50 * player[pl_id].proTime) );
	}
}

//血量减少及阵亡检测
void hpLose(short pl_id, short hurt)
{
	player[pl_id].hp-=hurt;

	//受伤动画
	char *pl_name = dMakeSpriteName("player", pl_id);
	dCloneSprite("playerHurt", "ob_playerHurt");
	dSetSpritePosition("ob_playerHurt", dGetSpritePositionX(pl_name), dGetSpritePositionY(pl_name));
	dSetSpriteLifeTime("ob_playerHurt", 0.5f);

	//阵亡检测
	if (player[pl_id].hp<=0)
	{
		dDeleteSprite(pl_name);
		player[pl_id].hp = 0;
		if (!strcmp(dGetStaticSpriteImage(pl_name), "xiaoyaoImageMap"))
		{
			if (player[0].hp||player[1].hp) sendMessage("啊，逍遥哥哥！灵儿要替逍遥哥哥报仇！");
			else
			{
				player[0].resusX = player[1].resusX = dGetSpritePositionX("player0");
				player[0].resusY = player[1].resusY = dGetSpritePositionY("player0");
				sendMessage("灵儿，黄泉路上再相依。。。");
			}
			//音效
			PlaySound(NULL, NULL, SND_PURGE);
			PlaySound("game/data/audio/lxy_died.wav", NULL, SND_ASYNC);
		}
		else if (!strcmp(dGetStaticSpriteImage(pl_name), "lingerImageMap"))
		{
			if (player[0].hp||player[1].hp) sendMessage("灵儿！可恶，我杀了你们！");
			else
			{
				player[0].resusX = player[1].resusX = dGetSpritePositionX("player1");
				player[0].resusY = player[1].resusY = dGetSpritePositionY("player1");
				sendMessage("逍遥哥哥...灵儿...来...了。。。");
			}
			//音效
			PlaySound(NULL, NULL, SND_PURGE);
			PlaySound("game/data/audio/zle_died.wav", NULL, SND_ASYNC);
		}
	}
}

//经验增加及升级检测
void expAdd(short pl_id, short value)
{
	player[pl_id].exp+=value;

	//升级检测
	if (player[pl_id].exp>=20 + 20 * player[pl_id].lv)
	{
		//如果达到等级上限
		if (player[pl_id].lv>=3)
		{
			player[pl_id].exp = 0;
			sendMessage("您已满级");
			return;
		}
		player[pl_id].lv++;
		player[pl_id].exp = 0;
		player[pl_id].hp = 8 + 2 * player[pl_id].lv;
		player[pl_id].mag =9 + 3 * player[pl_id].lv;

		//发送升级提醒
		char *pl_name = dMakeSpriteName("player", pl_id);
		char messageStr[20];
		if (!strcmp(dGetStaticSpriteImage(pl_name), "xiaoyaoImageMap"))
			sprintf(messageStr, "李逍遥升到%d级！", player[pl_name[6]-48].lv);
		else if (!strcmp(dGetStaticSpriteImage(pl_name), "lingerImageMap"))
			sprintf(messageStr, "赵灵儿升到%d级！", player[pl_name[6]-48].lv);
		sendMessage(messageStr);
		//光效
		dCloneSprite("levelUp", "ob_levelUp");
		dSetSpritePosition("ob_levelUp", dGetSpritePositionX(pl_name), dGetSpritePositionY(pl_name));
		dSetSpriteLifeTime("ob_levelUp", 1);
		//音效
		PlaySound(NULL, NULL, SND_PURGE);
		PlaySound("game/data/audio/level_up.wav", NULL, SND_ASYNC);
	}
}

///******************************玩家动作***************************************/

//物理攻击
void plPhyAct(short pl_id)
{
	if (!player[pl_id].hp) return;
	//攻击图标熄灭
	dSetSpriteColorAlpha(dMakeSpriteName("phyIcon", pl_id), 100);

	//玩家名
	char *pl_name = dMakeSpriteName("player", pl_id);
	//模板
	char phy_name[7] = "attack";
	//实例
	char *thisPhy = dMakeSpriteName("ob_attack", pl_id);
	//创建实例
	dCloneSprite(phy_name, thisPhy);
	//坐标
	float fPosX = (float)3 * player[pl_id].lastDirX+ dGetSpritePositionX(pl_name);
	float fPosY = (float)3 * player[pl_id].lastDirY + dGetSpritePositionY(pl_name);
	//放置
	dSetSpritePosition(thisPhy, fPosX, fPosY);
	//生命时长
	dSetSpriteLifeTime(thisPhy, 0.25f);
	//音效
	PlaySound(NULL, NULL, SND_PURGE);
	PlaySound("game/data/audio/phy_attack.wav", NULL, SND_ASYNC);
}
//法术攻击
void plMagAct(short pl_id)
{
	//生命、冷却时间不足跳过
	if (!player[pl_id].hp||player[pl_id].magRest<=1) return;
	//技能图标熄灭
	dSetSpriteColorAlpha(dMakeSpriteName("magIcon", pl_id), 100);

	//玩家名
	char *pl_name = dMakeSpriteName("player", pl_id);

	//逍遥近战
	if (!strcmp(dGetStaticSpriteImage(pl_name), "xiaoyaoImageMap"))
	{
		//重新冷却
		player[pl_id].magRest = 0;
		//蓝不足跳过
		if (player[pl_id].mag < 3)
		{
			sendMessage("释放失败，气力不足");
			return;
		}
		//减蓝
		player[pl_id].mag-=3;

		//技能模板名
		char *mag_name = dMakeSpriteName("magic", 10 * player[pl_id].lv + pl_id);
		//技能实例名
		char *thisMag = dMakeSpriteName("ob_magic", pl_id);
		//技能威力
		short power = dRandomRange(0, 3) + 3 * player[pl_id].lv;
		//加入链表
		addBox(mag_name, thisMag, power);

		//技能释放处坐标，方向*施法距离+施法者坐标
		float fPosX = (float)5 * player[pl_id].lastDirX + dGetSpritePositionX(pl_name);
		float fPosY = (float)5 * player[pl_id].lastDirY + dGetSpritePositionY(pl_name);
		//释放技能
		dSetSpritePosition(thisMag, fPosX, fPosY);
		//音效
		PlaySound(NULL, NULL, SND_PURGE);
		PlaySound("game/data/audio/lxy_magic.wav", NULL, SND_ASYNC);
	}

	//灵儿远程
	else if (!strcmp(dGetStaticSpriteImage(pl_name), "lingerImageMap"))
	{
		//重新冷却
		player[pl_id].magRest = 0;
		//蓝不足跳过
		if (player[pl_id].mag < 2)
		{
			sendMessage("释放失败，气力不足");
			return;
		}
		//减蓝
		player[pl_id].mag-=2;


		//技能模板名
		char *mag_name = dMakeSpriteName("magic", 10 * player[pl_id].lv + pl_id);
		//技能实例名
		char *thisMag = dMakeSpriteName("ob_magic", pl_id);
		//技能威力
		short power = dRandomRange(0, 2) + 2* player[pl_id].lv;
		//加入链表
		addBox(mag_name, thisMag, power);

		//技能释放处坐标，方向*施法距离+施法者坐标
		float fPosX = (float)3 * player[pl_id].lastDirX + dGetSpritePositionX(pl_name);
		float fPosY = (float)3 * player[pl_id].lastDirY + dGetSpritePositionY(pl_name);
		//释放技能
		dSetSpritePosition(thisMag, fPosX, fPosY);

		/*技能转向玩家朝向*/
		//计算角度
		float fRot = dCalLineRotation( dGetSpritePositionX(pl_name), dGetSpritePositionY(pl_name), fPosX, fPosY );
		//技能旋转
		dSetSpriteRotation(thisMag, fRot);
		//技能发射
		dSetSpriteLinearVelocityPolar( thisMag, (float)(5 + 4 * player[pl_id].lv), fRot );
		//音效
		PlaySound(NULL, NULL, SND_PURGE);
		PlaySound("game/data/audio/zle_magic.wav", NULL, SND_ASYNC);
	}
}

//移动，参数：键值，状态（按下1，抬起-1）
void plMove(const int iKey, short upOrDown)
{
	switch (iKey)
	{
	//设置玩家移动方向
	case KEY_W:
		player[0].dirY-=upOrDown;break;
	case KEY_S:
		player[0].dirY+=upOrDown;break;
	case KEY_A:
		player[0].dirX-=upOrDown;break;
	case KEY_D:
		player[0].dirX+=upOrDown;break;
	case KEY_UP:
		player[1].dirY-=upOrDown;break;
	case KEY_DOWN:
		player[1].dirY+=upOrDown;break;
	case KEY_LEFT:
		player[1].dirX-=upOrDown;break;
	case KEY_RIGHT:
		player[1].dirX+=upOrDown;break;
	}
	//移动玩家
	if (player[0].hp)
		dSetSpriteLinearVelocity("player0", (float)9 * player[0].dirX, (float)9 * player[0].dirY);
	if (player[1].hp)
		dSetSpriteLinearVelocity("player1", (float)9 * player[1].dirX, (float)9 * player[1].dirY);
}

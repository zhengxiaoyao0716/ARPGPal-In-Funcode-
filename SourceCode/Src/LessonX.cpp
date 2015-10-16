/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#include <Stdio.h>
#include "CommonAPI.h"
#include "LessonX.h"

#include <Mmsystem.h>  
#pragma comment ( lib, "Winmm.lib" )  
////////////////////////////////////////////////////////////////////////////////
//
//
int			g_iGameState		=	0;		// 游戏状态，0 -- 游戏结束等待开始状态；1 -- 按下空格键开始，初始化游戏；2 -- 游戏进行中
//
void		GameInit();
void		GameRun( float fDeltaTime );
void		GameEnd();



///******************************全局变量***************************************/

//关卡
short chapter = 0;

//实例数量
short ob_num = 0;

//地图中心点
float map_centerX = 44, map_centerY = -73.5f;

//是否是新游戏
bool isNew = true;

//游戏时长
float runTime = 0;

//灵珠
short key = 0;
const short
K_LEI = 2,             //雷
K_SHUI = 8,            //水
K_FENG = 1,            //风
K_HUO = 4,             //火
K_TU = 16;             //土

///******************************功能函数***************************************/

//数据还原
void dataClear();
//加载关卡
void loadChapter();

//设置地图位置
void setMap();

//播放玩家行走动画，记录玩家朝向，参数：脉冲轴，玩家ID
void playerWork(long axis, short pl_id);

//更新技能冷却时间
void magRestChange(short pl_id);
//更新玩家保护时间
void proTimeChange(short pl_id);

//移动地图
void moveMap();

//发送消息
void sendMessage(char* message);

//计算距离（未计算勾股）
float getDistance(const char *startName, const char *endName);

//血量减少（阵亡检测）
void hpLose(short pl_id, short hurt);
//经验增加（升级检测）
void expAdd(short pl_id, short value);

///*******************************AI设定****************************************/

//追击
void enemyPursue(const char *enemy, short pl_id);

//调配
void aiRun(bool isPlAlive[2]);

///******************************玩家数据***************************************/

short getPlHp(short pl_id);
short getPlMag(short pl_id);
short getPlExp(short pl_id);
short getPlLv(short pl_id);
short getPlGold(short pl_id);
short getPlWeapon(short pl_id);

short getPlDirX(short pl_id);
short getPlDirY(short pl_id);

float getResusX(short pl_id);
float getResusY(short pl_id);

float getProTime(short pl_id);

void setPlHp(short pl_id, short value);
void setPlMag(short pl_id, short value);
void setPlExp(short pl_id, short value);
void setPlLv(short pl_id, short value);

void setResusPos(short pl_id, float resusX, float resusY);

void setProTime(short pl_id, short value);

///******************************玩家功能***************************************/

bool addPlGold(short pl_id, short value);

///******************************玩家动作***************************************/

//物理攻击
void plPhyAct(short pl_id);
//法术攻击
void plMagAct(short pl_id);
//按键控制，参数：键值，状态（按下1，抬起-1）
void plMove(const int iKey, short upOrDown);

///******************************玩家功能***************************************/

//刷新数据
void rebuildPl();

///********************************商店*****************************************/

//载入商店
void openShop(short pl_id);
//退出商店
void closeShop();
//选择商品
void chooseGood(short choose);
//确认商品
void confirmGood(bool confirm);

///********************************链表*****************************************/

#define Box struct box
extern Box
{
	char *name;
	short value;
	Box *next;
} *obList;

//取箱
short *pickBox(const char *name);
//弃箱
void cutBox(const char *name);
//销毁
void destroyList();

/*******************************************************************************/


//==============================================================================
//
// 大体的程序流程为：GameMainLoop函数为主循环函数，在引擎每帧刷新屏幕图像之后，都会被调用一次。


//==============================================================================
//
// 游戏主循环，此函数将被不停的调用，引擎每刷新一次屏幕，此函数即被调用一次
// 用以处理游戏的开始、进行中、结束等各种状态. 
// 函数参数fDeltaTime : 上次调用本函数到此次调用本函数的时间间隔，单位：秒
void GameMainLoop( float	fDeltaTime )
{
	switch( g_iGameState )
	{
		// 初始化游戏，清空上一局相关数据
	case 1:
		{
			GameInit();
			g_iGameState	=	2; // 初始化之后，将游戏状态设置为进行中
		}
		break;

		// 游戏进行中，处理各种游戏逻辑
	case 2:
		{
			// TODO 修改此处游戏循环条件，完成正确游戏逻辑
			if( (getPlHp(0) > 0 || getPlHp(1) > 0) && chapter<=0 )
			{
				GameRun( fDeltaTime );
			}
			else
			{
				// 游戏结束。调用游戏结算函数，并把游戏状态修改为结束状态
				g_iGameState	=	0;
				GameEnd();
			}
		}
		break;

		// 游戏结束/等待按空格键开始
	case 0:
	default:
		break;
	};
}

//==============================================================================
//
// 每局开始前进行初始化，清空上一局相关数据
void GameInit()
{	
	//数据还原
	dataClear();

	//加载关卡
	loadChapter();

	//放置玩家
	dCloneSprite( "xiaoyao", "player0" );                       //创建实例
	dSetSpritePosition( "player0", getResusX(0), getResusY(0) );//置入场景
	dSetSpriteWorldLimitMode( "player0", WORLD_LIMIT_STICKY );  //边界限定
	dSetSpriteRestitution( "player0", 0.1f );                   //反弹力度

	dCloneSprite( "linger", "player1" );                        //创建实例
	dSetSpritePosition( "player1", getResusX(1), getResusY(1)); //置入场景
	dSetSpriteWorldLimitMode( "player1", WORLD_LIMIT_STICKY );  //边界限定
	dSetSpriteRestitution( "player1", 0.1f );                   //反弹力度

	//任务提示
	sendMessage("收集散落的五灵珠，打开通往终点的路");

	//绘制灵珠
	dSetSpriteVisible( "LEI", key & K_LEI );
	dSetSpriteVisible( "shui", key & K_SHUI );
	dSetSpriteVisible( "feng", key & K_FENG );
	dSetSpriteVisible( "huo", key & K_HUO );
	dSetSpriteVisible( "tu", key & K_TU );
}
//==============================================================================
//
// 每局游戏进行中
void GameRun( float fDeltaTime )
{
	runTime+=fDeltaTime;

	//脉冲轴
	static long axis = 0;
	//0.2s降帧脉冲
	if (runTime > (double)axis/5)
	{
		axis+=1;

		/*0.2s*/
		//更新行走动作帧图
		playerWork(axis, 0);
		playerWork(axis, 1);
		//更新技能冷却时间
		magRestChange(0);
		magRestChange(1);
		//更新玩家保护时间
		proTimeChange(0);
		proTimeChange(1);

		/*1.0s*/
		if (!(axis%5))
		{
			bool isPlAlive[2] = {getPlHp(0)>0, getPlHp(1)>0};
			//AI调配
			aiRun(isPlAlive);
		}
	}

	/*绘制UI*/
	char textStr[6];
	//体力
	sprintf(textStr, "%d/%d", getPlHp(0), 8 + 2 * getPlLv(0));
	dSetTextString("hpText0", textStr);
	sprintf(textStr, "%d/%d", getPlHp(1), 8 + 2 * getPlLv(1));
	dSetTextString("hpText1", textStr);
	//法术
	sprintf(textStr, "%d/%d", getPlMag(0), 9 + 3 * getPlLv(0));
	dSetTextString("magText0", textStr);
	sprintf(textStr, "%d/%d", getPlMag(1), 9 + 3 * getPlLv(1));
	dSetTextString("magText1", textStr);
	//经验
	dDrawRect( 27, -14, 39, -13.6f, 1, 0, 255, 255, 255, 255 );
	dDrawLine( 27, -13.8f, 27 + 12 * (float)getPlExp(0) / (20 + 20 * getPlLv(0)), -13.8f, 8, 0, 255, 255, 255, 255 );
	dDrawRect( -39, -14, -27, -13.6f, 1, 0, 255, 255, 255, 255 );
	dDrawLine( -39, -13.8f, -39 + 12 * (float)getPlExp(1) / (20 + 20 * getPlLv(1)), -13.8f, 8, 0, 255, 255, 255, 255 );
	//等级
	dSetTextValue("lvText0", getPlLv(0));
	dSetTextValue("lvText1", getPlLv(1));
	//铜板
	dSetTextValue("goldText0", getPlGold(0));
	dSetTextValue("goldText1", getPlGold(1));

	//移动地图
	moveMap();
}
//==============================================================================
//
// 本局游戏结束
void GameEnd()
{
	//删除玩家
	if (getPlHp(0))
	{
		//记录死亡位置
		setResusPos(0, dGetSpritePositionX("player0"), dGetSpritePositionY("player0"));
		dDeleteSprite("player0");

		if (!getPlHp(1)) setResusPos(1, getResusX(0), getResusY(0));
	}
	if (getPlHp(1))
	{
		setResusPos(1, dGetSpritePositionX("player1"), dGetSpritePositionY("player1"));
		dDeleteSprite("player1");
		if (!getPlHp(0)) setResusPos(0, getResusX(1), getResusY(1));
	}

	//销毁链表
	destroyList();

	//呈现时间
	Sleep(1500);

	//载入开始场景
	dLoadMap( "startPage.t2d" );

	//我放全灭，显示失败信息
	if (getPlHp(0)<=0&&getPlHp(1)<=0) dSetSpriteVisible( "over", 1 );
	else
	{
		//启用鼠标
		dCursorOn();
		//播放开始界面bgm，群山飞鹤
		PlaySound(NULL, NULL, SND_PURGE);
		//PlaySound("game/data/audio/bgm_qunshan.wav", NULL, SND_ASYNC|SND_LOOP);
	}
}
//==========================================================================
//
// 鼠标移动
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void OnMouseMove( const float fMouseX, const float fMouseY )
{
	//光标移动
	dSetSpritePosition( "cursor",  fMouseX,  fMouseY );
	//关闭按钮
	if (dIsPointInSprite( "close", fMouseX, fMouseY ))
		dSetStaticSpriteFrame( "close", 1 );
	else dSetStaticSpriteFrame( "close", 0 );
	//确认按钮
	if (dIsPointInSprite( "buttonY", fMouseX, fMouseY ))
	{
		if (dGetStaticSpriteFrame( "buttonY" )==0)
		dSetStaticSpriteFrame( "buttonY", 1 );
	}
	else if (dGetStaticSpriteFrame( "buttonY" )==1) dSetStaticSpriteFrame( "buttonY", 0 );
	//取消按钮
	if (dIsPointInSprite( "buttonN", fMouseX, fMouseY ))
	{
		if (dGetStaticSpriteFrame( "buttonN" )==3)
		dSetStaticSpriteFrame( "buttonN", 4 );
	}
	else if (dGetStaticSpriteFrame( "buttonN" )==4) dSetStaticSpriteFrame( "buttonN", 3 );
}
//==========================================================================
//
// 鼠标点击
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	if (dIsPointInSprite( "close", fMouseX, fMouseY ))
		closeShop();
	else if (dIsPointInSprite( "good1", fMouseX, fMouseY ))
		chooseGood(1);
	else if (dIsPointInSprite( "good2", fMouseX, fMouseY ))
		chooseGood(2);
	else if (dIsPointInSprite( "good8", fMouseX, fMouseY ))
		chooseGood(8);
	else if (dIsPointInSprite( "buttonY", fMouseX, fMouseY ))
		confirmGood(true);
	else if (dIsPointInSprite( "buttonN", fMouseX, fMouseY ))
		confirmGood(false);
}
//==========================================================================
//
// 鼠标弹起
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
void OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
}
//==========================================================================
//
// 键盘按下
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
void OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress )
{
	switch (iKey)
	{
	//回到开始界面
	case KEY_ESCAPE:
		if (g_iGameState)
		{
			g_iGameState = 0;
			GameEnd();
		}break;

	//进攻
	case KEY_R:
		plPhyAct(0);break;
	case KEY_T:
		plMagAct(0);break;
	case KEY_COMMA:
		plPhyAct(1);break;
	case KEY_PERIOD:
		plMagAct(1);break;

	//移动
	default:
		plMove(iKey, 1);break;
	}
}
//==========================================================================
//
// 键盘弹起
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
void OnKeyUp( const int iKey )
{
	switch (iKey)
	{
	//进攻
	case KEY_R:
		//攻击图标点亮
		dSetSpriteColorAlpha(dMakeSpriteName("phyIcon", 0), 255);
		break;
	case KEY_COMMA:
		//攻击图标点亮
		dSetSpriteColorAlpha(dMakeSpriteName("phyIcon", 1), 255);
		break;

	//移动
	default:
		plMove(iKey, -1);break;
	}
}
//===========================================================================
//
// 精灵与精灵碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
void OnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	//遇敌人的法术
	if (strstr(szTarName, "Boss")&&strstr(szTarName, "9"))
	{
		if (strstr(szSrcName, "player"))
		{
			//停止敌法的碰撞
			dSetSpriteCollisionReceive( szTarName, 0 );
			if (!getProTime(szSrcName[6]-48))
				hpLose(szSrcName[6]-48, szTarName[9] - 45);
		}
	}
	//遇敌人本体
	else if (strstr(szTarName, "enemy"))
	{
		short *pEnemy_hp = pickBox(szTarName);
		if (strstr(szSrcName, "player"))
		{
			if (!getProTime(szSrcName[6]-48))
				hpLose(szSrcName[6]-48,*pEnemy_hp%10 + *pEnemy_hp/10);
		}
		else if (strstr(szSrcName, "ob_attack"))
		{
			//停止技能的碰撞
			dSetSpriteCollisionSend( szSrcName, 0 );
			//伤害判定
			*pEnemy_hp-=getPlWeapon(szSrcName[9]-48)+ getPlLv(szSrcName[9]-48);
			//AI反击
			enemyPursue(szTarName, szSrcName[9]-48);
			//经验增加
			expAdd(szSrcName[9]-48, 1);
		}
		else if (strstr(szSrcName, "ob_magic"))
		{
			//停止技能的碰撞
			dSetSpriteCollisionSend( szSrcName, 0 );
			//伤害判定
			*pEnemy_hp-=*pickBox(szSrcName);
			//AI反击
			enemyPursue(szTarName, szSrcName[8]-48);
			//经验增加
			expAdd(szSrcName[8]-48, 3);
		}
		if (*pEnemy_hp <= 0)
		{
			//boss爆炸
			if (strstr(szTarName, "Boss"))
				dPlayEffect("bossBurst", 1, dGetSpritePositionX(szTarName), dGetSpritePositionY(szTarName), 0);
			else if (strstr(szTarName, "enemy"))
			{
				//创建实例
				dCloneSprite("enemyBurst", "ob_enemyBurst");
				//置入场景
				dSetSpritePosition("ob_enemyburst", dGetSpritePositionX(szTarName), dGetSpritePositionY(szTarName));
				//生命时长
				dSetSpriteLifeTime("ob_enemyBurst", 1);
			}
			cutBox(szTarName);
		}
	}
	//箱子
	else if (strstr(szTarName, "box"))
	{
		if (strstr(szSrcName, "player"))
		{
			//取消箱子的碰撞
			dSetSpriteCollisionReceive( szTarName, 0 );
			dSetStaticSpriteFrame( szTarName, 12 + dGetStaticSpriteFrame( szTarName ) );
			switch ((int)szTarName[3] - 48)
			{
			case 1:
				{
					if (key & K_LEI)
					{
						sendMessage("这个箱子已经空了");
						break;
					}
					key|=K_LEI;
					dSetSpriteVisible( "lei", key & K_LEI );
					sendMessage("拿到了雷灵珠");
				}break;
			case 3:
				{
					if (key & K_SHUI)
					{
						sendMessage("这个箱子已经空了");
						break;
					}
					key|=K_SHUI;
					dSetSpriteVisible( "shui", key & K_SHUI );
					sendMessage("拿到了水灵珠");
				}break;
			case 0:
				{
					if (key & K_FENG)
					{
						sendMessage("这个箱子已经空了");
						break;
					}
					key|=K_FENG;
					dSetSpriteVisible( "feng", key & K_FENG );
					sendMessage("拿到了风灵珠");
				}break;
			case 2:
				{
					if (key & K_HUO)
					{
						sendMessage("这个箱子已经空了");
						break;
					}
					key|=K_HUO;
					dSetSpriteVisible( "huo", key & K_HUO );
					sendMessage("拿到了火灵珠");
				}break;
			case 4:
				{
					if (key & K_TU)
					{
						sendMessage("这个箱子已经空了");
						break;
					}
					key|=K_TU;
					dSetSpriteVisible( "tu", key & K_TU );
					sendMessage("拿到了土灵珠");
				}break;
			case 5:
				{
					addPlGold(szSrcName[6] - 48, 100);
					sendMessage("箱子里有100铜板！");
				}
				break;
			case 6:
				{
					addPlGold(szSrcName[6] - 48, 300);
					sendMessage("箱子里有300铜板！");
				}break;
			default:
				break;
			}
			//音效
			PlaySound(NULL, NULL, SND_PURGE);
			PlaySound("game/data/audio/get.wav", NULL, SND_ASYNC);
		}
	}
	//路障
	else if(strstr(szTarName, "wulinglun"))
	{
		if (strstr(szSrcName, "player"))
		{
			if (key < 31) sendMessage("这是五灵轮，需要五灵珠的力量才能通过");
			else
			{
				sendMessage("风雷水火土，五灵珠归位，五灵轮开");
				dDeleteSprite("wulinglun");
			}
		}
	}
	//终点
	else if (strstr(szTarName, "final"))
	{
		if (strstr(szSrcName, "player"))
		{
			sendMessage("恭喜您到达终点！");
			chapter++;
		}
	}
	//商店
	else if (strstr(szTarName, "shop"))
	{
		if (strstr(szSrcName, "player"))
		{
			short pl_id = szSrcName[6] - 48;
			openShop(pl_id);
		}
	}
	//复活点
	else if (strstr(szTarName, "resus"))
	{
		if (strstr(szSrcName, "player"))
		{
			//放置玩家
			short anotherPl = szSrcName[6] - 48 ? 0 : 1;
			if (!getPlHp(anotherPl))
			{
				char *pl_name = dMakeSpriteName("player", anotherPl);
				if (anotherPl)
				{
					sendMessage("灵儿！太好了，灵儿，你终于醒了！");
					dCloneSprite( "linger", pl_name );
				}
				else
				{
					sendMessage("逍遥哥哥，灵儿好怕，还以为再也见不到你了");
					dCloneSprite( "xiaoyao", pl_name );
				}
				dSetSpritePosition( pl_name, dGetSpritePositionX(szSrcName), dGetSpritePositionY(szSrcName) );
				dSetSpriteWorldLimitMode( pl_name, WORLD_LIMIT_STICKY );
				dSetSpriteRestitution( pl_name, 0.1f );
				setProTime(pl_name[6] - 48, 3);
				setPlHp(anotherPl, 4 + getPlLv(anotherPl));
				setPlMag(anotherPl, 5 + 2 * getPlLv(anotherPl));
			}
		}
	}
}
//===========================================================================
//
// 精灵与世界边界碰撞
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
void OnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	if (!strcmp(szName, "player0")&&getPlHp(1)&&
		getDistance("player0", "player1") > 15)
		sendMessage("灵儿，快跟上");
	else if (!strcmp(szName, "player1")&&getPlHp(0)&&
		getDistance("player0", "player1") > 15)
		sendMessage("逍遥哥哥快来，我等你");
}

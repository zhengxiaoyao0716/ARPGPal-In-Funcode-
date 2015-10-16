#include "CommonAPI.h"

///******************************功能函数***************************************/

//发送消息
void sendMessage(char* message);

///******************************玩家数据***************************************/

short getPlGold(short pl_id);
short getPlWeapon(short pl_id);
void setPlWeapon(short pl_id, short value);

///******************************玩家功能***************************************/

//体力增加
bool addPlHp(short pl_id, short value);
//气力增加
bool addPlMag(short pl_id, short value);
//失去铜钱
bool losePlGold(short pl_id, short value);

///********************************链表*****************************************/

//挂箱（参数szSrcName为NULL表示不创建实例）
void addBox(const char *szSrcName, const char *szMyName, short value);

///********************************商店*****************************************/

//顾客信息
static struct custom
{
	short id;         //玩家序号
	short choose;     //玩家选择
}thisCustom;

//载入商店
void openShop(short id)
{
	//创建失败
	if (dIsCursorOn())
	{
		sendMessage("商店正忙，请稍等");
		return;
	}
	
	//记录顾客
	thisCustom.id = id;
	//禁止玩家移动
	dSetSpriteImmovable(dMakeSpriteName("player", id), 1);

	//启用鼠标
	dCursorOn();
	dSetSpriteVisible( "shopCard", 1 );
	dSetSpriteVisible( "cursor", 1 );
	sendMessage("欢迎光临小店，客官随便挑，价格公道！");
}
//退出商店
void closeShop()
{
	//禁用鼠标
	dCursorOff();
	dSetSpriteVisible( "shopCard", 0 );
	dSetSpriteVisible( "cursor", 0 );
	sendMessage("客官下次再来啊！");

	//允许玩家移动
	dSetSpriteImmovable(dMakeSpriteName("player", thisCustom.id), 0);
}
//选择商品
void chooseGood(short choose)
{
	dSetTextValue("priceText", 100 * choose);
	if (getPlGold(thisCustom.id) < 100 * choose)
	{
		thisCustom.choose = 0;
		sendMessage("客官，您的铜板不够啊。。。");
		dSetStaticSpriteFrame( "buttonY", 2 );
		dSetStaticSpriteFrame( "buttonN", 5 );
		return;
	}
	switch (choose)
	{
	case 1:
		sendMessage("这是灵芝，吃下可恢复气力，客官来一支？");
		break;
	case 2:
		sendMessage("大还丹，吃下可恢复体力，客官您买不？");
		break;
	case 8:
		sendMessage("无尘剑，这可是好东西，客官要的话我给你算便宜点");
		break;
	}
	thisCustom.choose = choose;
	dSetStaticSpriteFrame( "buttonY", 0 );
	dSetStaticSpriteFrame( "buttonN", 3 );
}
//确认商品
void confirmGood(bool confirm)
{
	if (!thisCustom.choose) return;
	if (!confirm) sendMessage("客官你就别犹豫了，都是好东西啊！");
	else
	{
		bool succeed = false;
		switch (thisCustom.choose)
		{
		case 1:
			{
				if (addPlMag(thisCustom.id, 6)) succeed = true;
				else sendMessage("客官，您气力这是满的，吃这个没效果啊！");
			}break;
		case 2:
			{
				//上限检测
				if (addPlHp(thisCustom.id, 4)) succeed = true;
				else sendMessage("客官，您体力这是满的，吃这个没效果啊！");
			}break;
		case 8:
			{
				if (getPlWeapon(thisCustom.id)) sendMessage("哎呀客官，您已经有这把剑了啊！");
				else
				{
					setPlWeapon(thisCustom.id, 2);
					//添加到图标
					char *ob_choose = dMakeSpriteName("ob_good8", thisCustom.id);
					addBox("good8", ob_choose, 0);
					dSetSpritePosition(ob_choose, (float)(thisCustom.id ? -1 : 1) * 29, -8);
					succeed = true;
				}
			}break;
		}
		if (succeed)
		{
			sendMessage("好嘞，您的东西请拿好");
			losePlGold(thisCustom.id, 100 * thisCustom.choose);
		}
	}
	thisCustom.choose = 0;
	dSetStaticSpriteFrame( "buttonY", 2 );
	dSetStaticSpriteFrame( "buttonN", 5 );
}
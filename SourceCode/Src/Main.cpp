//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
#include "CommonAPI.h"
#include "LessonX.h"

#include <Mmsystem.h>  
#pragma comment ( lib, "Winmm.lib" )  
///////////////////////////////////////////////////////////////////////////////////////////
//
// 主函数入口
//
//////////////////////////////////////////////////////////////////////////////////////////
int PASCAL WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR     lpCmdLine,
                   int       nCmdShow)
{
	// 初始化游戏引擎
	if( !dInitGameEngine( hInstance, lpCmdLine ) )
		return 0;

	// To do : 在此使用API更改窗口标题
	dSetWindowTitle("ARPG仙剑");
	
	//全屏
	dResizeWindow( GetSystemMetrics( SM_CXFULLSCREEN ), GetSystemMetrics( SM_CYFULLSCREEN ) );
	//隐藏鼠标
	dShowCursor( 0 );
	//播放开始界面bgm，群山飞鹤
	PlaySound(NULL, NULL, SND_PURGE);
	//PlaySound("game/data/audio/bgm_qunshan.wav", NULL, SND_ASYNC|SND_LOOP);


	// 引擎主循环，处理屏幕图像刷新等工作
	while( dEngineMainLoop() )
	{
		// 获取两次调用之间的时间差，传递给游戏逻辑处理
		float	fTimeDelta	=	dGetTimeDelta();

		// 执行游戏主循环
		GameMainLoop( fTimeDelta );
	};

	// 关闭游戏引擎
	dShutdownGameEngine();
	return 0;
}

//
extern int g_iGameState;

//==========================================================================
//
// 引擎捕捉鼠标移动消息后，将调用到本函数
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void dOnMouseMove( const float fMouseX, const float fMouseY )
{
	//游戏未开始前不进入LessonX层，下同
	if (!g_iGameState)
	{
		//光标移动
		dSetSpritePosition( "cursor",  fMouseX,  fMouseY );
		//蝴蝶转向
		float fRot = 90 + dCalLineRotation( dGetSpritePositionX( "butterFly"),
			dGetSpritePositionY( "butterFly"), fMouseX,  fMouseY);
		dSetSpriteRotation( "butterFly", fRot );
		//追向光标
		dSpriteMoveTo( "butterFly", fMouseX, fMouseY, 20, 1 );

		//上一次鼠标位置状态
		static short lastMouseState = 0;

		if (dIsPointInSprite( "startNew", fMouseX, fMouseY ))
		{
			//如果状态未改变，跳过
			if (lastMouseState==1) return;
			//状态更新
			lastMouseState = 1;
			//选项卡改变
			dSetStaticSpriteFrame( "startNew", 1 );
			dSetStaticSpriteFrame( "startOld", 2 );
			//播放音效
			PlaySound(NULL, NULL, SND_PURGE);
			PlaySound("game/data/audio/BLIP.wav", NULL, SND_ASYNC);
		}
		else if (dIsPointInSprite( "startOld", fMouseX, fMouseY ))
		{
			if(lastMouseState==2) return;
			lastMouseState = 2;
			dSetStaticSpriteFrame( "startOld", 3 );
			dSetStaticSpriteFrame( "startNew", 0 );
			PlaySound(NULL, NULL, SND_PURGE);
			PlaySound("game/data/audio/BLIP.wav", NULL, SND_ASYNC);
		}
		else
		{
			if(!lastMouseState) return;
			lastMouseState = 0;
			dSetStaticSpriteFrame( "startNew", 0 );
			dSetStaticSpriteFrame( "startOld", 2 );
		}
		//返回，不进入LessonX
		return;
	}

	// 可以在此添加游戏需要的响应函数
	OnMouseMove(fMouseX, fMouseY );
}
//==========================================================================
//
// 引擎捕捉鼠标点击消息后，将调用到本函数
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//

extern bool isNew;
void dOnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY )
{
	if (!g_iGameState)
	{
		//点击开始，游戏状态为1，isNew = true
		if (dIsPointInSprite( "startNew", fMouseX, fMouseY ))
		{
			isNew = true;
			g_iGameState = 1;
			//播放音效
			PlaySound(NULL, NULL, SND_PURGE);
			PlaySound("game/data/audio/whoosh_mono.wav", NULL, SND_ASYNC);
		}
		//点击继续，游戏状态为1
		else if (dIsPointInSprite( "startOld", fMouseX, fMouseY ))
		{
			if (isNew) return;
			g_iGameState = 1;
			//播放音效
			PlaySound(NULL, NULL, SND_PURGE);
			PlaySound("game/data/audio/whoosh_mono.wav", NULL, SND_ASYNC);
		}
		return;
	}

	// 可以在此添加游戏需要的响应函数
	OnMouseClick(iMouseType, fMouseX, fMouseY);
}
//==========================================================================
//
// 引擎捕捉鼠标弹起消息后，将调用到本函数
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
void dOnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY )
{
	if (!g_iGameState)
	{
		return;
	}

	// 可以在此添加游戏需要的响应函数
	OnMouseUp(iMouseType, fMouseX, fMouseY);

}
//==========================================================================
//
// 引擎捕捉键盘按下消息后，将调用到本函数
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
//
void dOnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress )
{
	if (!g_iGameState)
	{
		if (dIsCursorOn()||iKey!=KEY_SPACE) return;
		//启用鼠标
		dCursorOn();
		//隐藏失败信息
		dSetSpriteVisible( "over", 0 );
		//播放开始界面bgm，群山飞鹤
		PlaySound(NULL, NULL, SND_PURGE);
		//PlaySound("game/data/audio/bgm_qunshan.wav", NULL, SND_ASYNC|SND_LOOP);
		return;
	}

	// 可以在此添加游戏需要的响应函数
	OnKeyDown(iKey, iAltPress, iShiftPress, iCtrlPress);
}
//==========================================================================
//
// 引擎捕捉键盘弹起消息后，将调用到本函数
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
//
void dOnKeyUp( const int iKey )
{
	if (!g_iGameState)
	{
		return;
	}

	// 可以在此添加游戏需要的响应函数
	OnKeyUp(iKey);
}

//===========================================================================
//
// 引擎捕捉到精灵与精灵碰撞之后，调用此函数
// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵发送及接受碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
//
void dOnSpriteColSprite( const char *szSrcName, const char *szTarName )
{
	if (!g_iGameState)
	{
		return;
	}

	// 可以在此添加游戏需要的响应函数
	OnSpriteColSprite(szSrcName, szTarName);
}

//===========================================================================
//
// 引擎捕捉到精灵与世界边界碰撞之后，调用此函数.
// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵的世界边界限制
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
//
void dOnSpriteColWorldLimit( const char *szName, const int iColSide )
{
	
	if (!g_iGameState)
	{
		return;
	}

	// 可以在此添加游戏需要的响应函数
	OnSpriteColWorldLimit(szName, iColSide);
}


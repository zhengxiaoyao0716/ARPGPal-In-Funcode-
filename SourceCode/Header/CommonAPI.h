/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _COMMON_API_H_
#define _COMMON_API_H_
//
#include <windows.h>

/////////////////////////////////////////////////////////////////////////////////
//
// 宏定义
//
/////////////////////////////////////////////////////////////////////////////////

//=================================================================================
//
// Sprite精灵与世界边界碰撞响应定义( 碰撞之后API OnSpriteColWorldLimit 将被调用 )
enum EWorldLimit
{
	WORLD_LIMIT_OFF,			// 关闭与世界边界的碰撞
	WORLD_LIMIT_NULL,			// 碰撞之后引擎不做任何处理，由各游戏自己处理响应
	WORLD_LIMIT_RIGID,			// 刚性物理碰撞反应
	WORLD_LIMIT_BOUNCE,			// 反弹模式
	WORLD_LIMIT_CLAMP,			// 小幅反弹，逐渐停止模式(比如篮球落地)
	WORLD_LIMIT_STICKY,			// 碰撞之后静止
	WORLD_LIMIT_KILL,			// 碰撞之后精灵将被删除

	WORLD_LIMIT_INVALID,		//	无效值
};
//================================================================================
//
/// 精灵与精灵之间、精灵与地图中其它精灵之间的碰撞响应( 碰撞之后API OnSpriteColSprite 将被调用 )
enum ECollisionResponse
{
	COL_RESPONSE_OFF,			//	关闭碰撞响应(不调用OnSpriteColSprite)

	COL_RESPONSE_RIGID,			//	刚性物理碰撞响应
	COL_RESPONSE_BOUNCE,		//	反弹模式
	COL_RESPONSE_CLAMP,			//	小幅反弹，逐渐停止模式(比如篮球落地)
	COL_RESPONSE_STICKY,		//	碰撞之后静止
	COL_RESPONSE_KILL,			//	碰撞之后精灵将被删除
	COL_RESPONSE_CUSTOM,		//	碰撞之后引擎不做任何处理，由各游戏自己处理响应

	COL_RESPONSE_INVALID,		//	无效值
};
//================================================================================
//
// 鼠标按键值定义
enum MouseTypes 
{
	MOUSE_LEFT		=	0,		// 左键
	MOUSE_RIGHT		=	1,		// 右键
	MOUSE_MIDDLE	=	2		// 中键
};
//================================================================================
//
// 键盘KEY值定义
enum KeyCodes 
{
   KEY_NULL          = 0x000,     ///< Invalid KeyCode
   KEY_BACKSPACE     = 0x001,
   KEY_TAB           = 0x002,
   KEY_ENTER         = 0x003,
   KEY_CONTROL       = 0x004,
   KEY_ALT           = 0x005,
   KEY_SHIFT         = 0x006,
   KEY_PAUSE         = 0x007,
   KEY_CAPSLOCK      = 0x008,
   KEY_ESCAPE        = 0x009,
   KEY_SPACE         = 0x00a,
   KEY_PAGE_DOWN     = 0x00b,
   KEY_PAGE_UP       = 0x00c,
   KEY_END           = 0x00d,
   KEY_HOME          = 0x00e,
   KEY_LEFT          = 0x00f,
   KEY_UP            = 0x010,
   KEY_RIGHT         = 0x011,
   KEY_DOWN          = 0x012,
   KEY_PRINT         = 0x013,
   KEY_INSERT        = 0x014,
   KEY_DELETE        = 0x015,
   KEY_HELP          = 0x016,

   KEY_0             = 0x017,
   KEY_1             = 0x018,
   KEY_2             = 0x019,
   KEY_3             = 0x01a,
   KEY_4             = 0x01b,
   KEY_5             = 0x01c,
   KEY_6             = 0x01d,
   KEY_7             = 0x01e,
   KEY_8             = 0x01f,
   KEY_9             = 0x020,

   KEY_A             = 0x021,
   KEY_B             = 0x022,
   KEY_C             = 0x023,
   KEY_D             = 0x024,
   KEY_E             = 0x025,
   KEY_F             = 0x026,
   KEY_G             = 0x027,
   KEY_H             = 0x028,
   KEY_I             = 0x029,
   KEY_J             = 0x02a,
   KEY_K             = 0x02b,
   KEY_L             = 0x02c,
   KEY_M             = 0x02d,
   KEY_N             = 0x02e,
   KEY_O             = 0x02f,
   KEY_P             = 0x030,
   KEY_Q             = 0x031,
   KEY_R             = 0x032,
   KEY_S             = 0x033,
   KEY_T             = 0x034,
   KEY_U             = 0x035,
   KEY_V             = 0x036,
   KEY_W             = 0x037,
   KEY_X             = 0x038,
   KEY_Y             = 0x039,
   KEY_Z             = 0x03a,

   KEY_TILDE         = 0x03b,
   KEY_MINUS         = 0x03c,
   KEY_EQUALS        = 0x03d,
   KEY_LBRACKET      = 0x03e,
   KEY_RBRACKET      = 0x03f,
   KEY_BACKSLASH     = 0x040,
   KEY_SEMICOLON     = 0x041,
   KEY_APOSTROPHE    = 0x042,
   KEY_COMMA         = 0x043,
   KEY_PERIOD        = 0x044,
   KEY_SLASH         = 0x045,
   KEY_NUMPAD0       = 0x046,
   KEY_NUMPAD1       = 0x047,
   KEY_NUMPAD2       = 0x048,
   KEY_NUMPAD3       = 0x049,
   KEY_NUMPAD4       = 0x04a,
   KEY_NUMPAD5       = 0x04b,
   KEY_NUMPAD6       = 0x04c,
   KEY_NUMPAD7       = 0x04d,
   KEY_NUMPAD8       = 0x04e,
   KEY_NUMPAD9       = 0x04f,
   KEY_MULTIPLY      = 0x050,
   KEY_ADD           = 0x051,
   KEY_SEPARATOR     = 0x052,
   KEY_SUBTRACT      = 0x053,
   KEY_DECIMAL       = 0x054,
   KEY_DIVIDE        = 0x055,
   KEY_NUMPADENTER   = 0x056,

   KEY_F1            = 0x057,
   KEY_F2            = 0x058,
   KEY_F3            = 0x059,
   KEY_F4            = 0x05a,
   KEY_F5            = 0x05b,
   KEY_F6            = 0x05c,
   KEY_F7            = 0x05d,
   KEY_F8            = 0x05e,
   KEY_F9            = 0x05f,
   KEY_F10           = 0x060,
   KEY_F11           = 0x061,
   KEY_F12           = 0x062,
   KEY_F13           = 0x063,
   KEY_F14           = 0x064,
   KEY_F15           = 0x065,
   KEY_F16           = 0x066,
   KEY_F17           = 0x067,
   KEY_F18           = 0x068,
   KEY_F19           = 0x069,
   KEY_F20           = 0x06a,
   KEY_F21           = 0x06b,
   KEY_F22           = 0x06c,
   KEY_F23           = 0x06d,
   KEY_F24           = 0x06e,

   KEY_NUMLOCK       = 0x06f,
   KEY_SCROLLLOCK    = 0x070,
   KEY_LCONTROL      = 0x071,
   KEY_RCONTROL      = 0x072,
   KEY_LALT          = 0x073,
   KEY_RALT          = 0x074,
   KEY_LSHIFT        = 0x075,
   KEY_RSHIFT        = 0x076,
   KEY_WIN_LWINDOW   = 0x077,
   KEY_WIN_RWINDOW   = 0x078,
   KEY_WIN_APPS      = 0x079,
   KEY_OEM_102       = 0x080,

   KEY_MAC_OPT       = 0x090,
   KEY_MAC_LOPT      = 0x091,
   KEY_MAC_ROPT      = 0x092,

   KEY_BUTTON0       = 0x0100,
   KEY_BUTTON1       = 0x0101,
   KEY_BUTTON2       = 0x0102,
   KEY_BUTTON3       = 0x0103,
   KEY_BUTTON4       = 0x0104,
   KEY_BUTTON5       = 0x0105,
   KEY_BUTTON6       = 0x0106,
   KEY_BUTTON7       = 0x0107,
   KEY_BUTTON8       = 0x0108,
   KEY_BUTTON9       = 0x0109,
   KEY_BUTTON10      = 0x010A,
   KEY_BUTTON11      = 0x010B,
   KEY_BUTTON12      = 0x010C,
   KEY_BUTTON13      = 0x010D,
   KEY_BUTTON14      = 0x010E,
   KEY_BUTTON15      = 0x010F,
   KEY_BUTTON16      = 0x0110,
   KEY_BUTTON17      = 0x0111,
   KEY_BUTTON18      = 0x0112,
   KEY_BUTTON19      = 0x0113,
   KEY_BUTTON20      = 0x0114,
   KEY_BUTTON21      = 0x0115,
   KEY_BUTTON22      = 0x0116,
   KEY_BUTTON23      = 0x0117,
   KEY_BUTTON24      = 0x0118,
   KEY_BUTTON25      = 0x0119,
   KEY_BUTTON26      = 0x011A,
   KEY_BUTTON27      = 0x011B,
   KEY_BUTTON28      = 0x011C,
   KEY_BUTTON29      = 0x011D,
   KEY_BUTTON30      = 0x011E,
   KEY_BUTTON31      = 0x011F,
   KEY_ANYKEY         = 0xfffe
};

/////////////////////////////////////////////////////////////////////////////////
//
// API定义
//
/////////////////////////////////////////////////////////////////////////////////

// dOnMouseMove：鼠标移动后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
extern void		dOnMouseMove( const float fMouseX, const float fMouseY );

// dOnMouseClick：鼠标按下后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
extern void		dOnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );

// dOnMouseUp：鼠标弹起后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
// 参数 iMouseType：鼠标按键值，见 enum MouseTypes 定义
// 参数 fMouseX, fMouseY：为鼠标当前坐标
//
extern void		dOnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );

// dOnKeyDown：键盘被按下后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
// 参数 iKey：被按下的键，值见 enum KeyCodes 宏定义
// 参数 iAltPress, iShiftPress，iCtrlPress：键盘上的功能键Alt，Ctrl，Shift当前是否也处于按下状态(0未按下，1按下)
//
extern void		dOnKeyDown( const int iKey, const int iAltPress, const int iShiftPress, const int iCtrlPress );

// dOnKeyUp：键盘按键弹起后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
// 参数 iKey：弹起的键，值见 enum KeyCodes 宏定义
//
extern void		dOnKeyUp( const int iKey );

// dOnSpriteColSprite：精灵与精灵碰撞后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵发送及接受碰撞
// 参数 szSrcName：发起碰撞的精灵名字
// 参数 szTarName：被碰撞的精灵名字
//
extern void		dOnSpriteColSprite( const char *szSrcName, const char *szTarName );

// dOnSpriteColWorldLimit：精灵与世界边界碰撞后将被调用的函数，可在此函数体里(Main.cpp)增加自己的响应代码
// 精灵之间要产生碰撞，必须在编辑器或者代码里设置精灵的世界边界限制
// 参数 szName：碰撞到边界的精灵名字
// 参数 iColSide：碰撞到的边界 0 左边，1 右边，2 上边，3 下边
//
extern void		dOnSpriteColWorldLimit( const char *szName, const int iColSide );

// dMakeSpriteName: 将前面的字符串与后面的数字整合成一个字符串。
// 参数 szPrev：一个非空字符串，最长不能超过20个英文字符。名字前面的字符。
// 参数 iId：一个数字
// 返回值：返回一个字符串，比如传入("xxx", 2),则返回"xxx2"
//
extern char*	dMakeSpriteName(const char *szPrev, const int iId);

// dCursorOff：关闭鼠标不显示。此API隐藏的是整个Windows的鼠标，除非调用开启鼠标的API dCursorOn，否则鼠标将一直不显示
//
extern void		dCursorOff();

// dCursorOn：开启鼠标显示。将API dCursorOff关闭的鼠标重新开启显示
//
extern void		dCursorOn();

// dIsCursorOn：当前鼠标是开启还是关闭。对应的是用API dCursorOff和dCursorOn开启或者关闭的操作
// 返回值：1为开启状态，0为关闭状态
//
extern int		dIsCursorOn();

// dShowCursor：隐藏/显示鼠标。此API只是隐藏本程序窗口内的鼠标，移动到窗口外的时候，鼠标还是会显示
// 参数 iShow：1 为显示，0 为隐藏
//
extern void		dShowCursor( const int iShow );

// dIsShowCursor：当前鼠标是显示还是隐藏。对应的是用API dShowCursor隐藏或者显示的操作
// 返回值：1为开启状态，0为关闭状态
//
extern int		dIsShowCursor();

// dSetWindowTitle：设置窗口名字/标题
// 参数 szTitle：非空字符串
//
extern void		dSetWindowTitle( const char *szTitle );

// dResizeWindow：更改窗口大小
// 参数 iWidth：宽度，大于0小于等于1920
// 参数 iHeight：高度，大于0小于等于1080
//
extern void		dResizeWindow(int iWidth, int iHeight);

// dGetHwnd：获取窗口句柄
// 返回值：窗口句柄
//
extern void*	dGetHwnd();

// dRandom：获取一个大于等于0的随机数
// 返回值：int，范围0 - 2147483648
//
extern int		dRandom();

// dRandomRange：获取一个位于参数1到参数2之间的随机数
// 返回值：int，范围iMin - iMax
// 参数 iMin：小于iMax的整数
// 参数 iMax：大于iMin的整数
//
extern int		dRandomRange( const int iMin, const int iMax );

// dCalLineRotation：计算两点连线的直线的旋转角度
// 返回值：角度，范围0 - 360
// 参数 fStartX：起始坐标X
// 参数 fStartY：起始坐标Y
// 参数 fEndX：终点坐标X
// 参数 fEndY：终点坐标Y
//
extern float	dCalLineRotation( const float fStartX, const float fStartY, const float fEndX, const float fEndY );

// dRotationToVectorX：计算某个角度对应的直线向量的X方向
// 参数 fRotation：角度，范围0 - 360
// 返回值 ：该直线向量的X值
//
extern float	dRotationToVectorX( const float fRotation );

// dRotationToVectorY：计算某个角度对应的直线向量的Y方向
// 参数 fRotation：角度，范围0 - 360
// 返回值 ：该直线向量的Y值
//
extern float	dRotationToVectorY( const float fRotation );

// dDrawLine：在两点之间画一条线
// 参数 fStartX：起始坐标X
// 参数 fStartY：起始坐标Y
// 参数 fEndX：终点坐标X
// 参数 fEndY：终点坐标Y
// 参数 fLineWidth：线的粗细，大于等于1
// 参数 iLayer：该线所在的层，与编辑器里设置的精灵的层级是同一个概念。范围0 - 31。
// 参数 iRed, iGreen, iBlue : 红绿蓝三原色的颜色值，范围 0 - 255
// 参数 iAlpha：线的透明度，范围0-255. 0为全透明，255为不透明
//
extern void		dDrawLine( const float fStartX, const float fStartY, const float fEndX, const float fEndY, const float fLineWidth, const int iLayer, const int iRed, const int iGreen, const int iBlue, const int iAlpha );

// dDrawTriangle：画一个三角形
// 参数 fX1,fX2,fX3：三角形上三个点的X坐标
// 参数 fY1,fY2,fY3：三角形上三个点的Y坐标
// 参数 fLineWidth：线的粗细，大于等于1
// 参数 iLayer：该三角形所在的层，与编辑器里设置的精灵的层级是同一个概念。范围0 - 31。
// 参数 iRed, iGreen, iBlue : 红绿蓝三原色的颜色值，范围 0 - 255
// 参数 iAlpha：三角形的透明度，范围0-255. 0为全透明，255为不透明
//
extern void		dDrawTriangle( const float fX1, const float fY1, const float fX2, const float fY2, const float fX3, const float fY3, const float fLineWidth, const int iLayer, const int iRed, const int iGreen, const int iBlue, const int iAlpha );

// dDrawRect：画一个矩形
// 参数 fUpperX：左上角坐标X
// 参数 fUpperY：左上角坐标Y
// 参数 fLowerX：右下角坐标X
// 参数 fLowerY：右下角坐标Y
// 参数 fLineWidth：线的粗细，大于等于1
// 参数 iLayer：该矩形所在的层，与编辑器里设置的精灵的层级是同一个概念。范围0 - 31。
// 参数 iRed, iGreen, iBlue : 红绿蓝三原色的颜色值，范围 0 - 255
// 参数 iAlpha：矩形的透明度，范围0-255. 0为全透明，255为不透明
//
extern void		dDrawRect( const float fUpperX, const float fUpperY, const float fLowerX, const float fLowerY, const float fLineWidth, const int iLayer, const int iRed, const int iGreen, const int iBlue, const int iAlpha );

// dDrawCircle：画一个圆
// 参数 fCenterX：圆心坐标X
// 参数 fCenterY：圆心坐标Y
// 参数 fRadius：圆的半径
// 参数 iSegment：圆弧段数，范围4-72. 比如传入6，将得到一个6边形，段数越大越圆滑，但是画图效率越低
// 参数 fLineWidth：线的粗细，大于等于1
// 参数 iLayer：该圆所在的层，与编辑器里设置的精灵的层级是同一个概念。范围0 - 31。
// 参数 iRed, iGreen, iBlue : 红绿蓝三原色的颜色值，范围 0 - 255
// 参数 iAlpha：圆的透明度，范围0-255. 0为全透明，255为不透明
//
extern void		dDrawCircle( const float fCenterX, const float fCenterY, const float fRadius, const int iSegment, const float fLineWidth, const int iLayer, const int iRed, const int iGreen, const int iBlue, const int iAlpha );

// dGetScreenLeft：获取世界边界之左边X坐标
// 返回值：左边界X坐标
//
extern float	dGetScreenLeft();

// dGetScreenTop：获取世界边界之上边Y坐标
// 返回值：上边界Y坐标
//
extern float	dGetScreenTop();

// dGetScreenRight：获取世界边界之右边X坐标
// 返回值：右边界X坐标
//
extern float	dGetScreenRight();

// dGetScreenBottom：获取世界边界之下边Y坐标
// 返回值：下边界Y坐标
//
extern float	dGetScreenBottom();

// dCloneSprite：复制(创建)一个精灵。精灵的创建方式：先在地图中摆放一个精灵做为模板，设置好各项参数，然后在代码里使用此函数克隆一个实例
// 返回值：1表示克隆成功，0克隆失败。失败的原因可能是在地图中未找到对应名字的精灵
// 参数 szSrcName：地图中用做模板的精灵名字
// 参数 szMyName：新的精灵名字
//
extern int		dCloneSprite( const char *szSrcName, const char *szMyName );

// dDeleteSprite：在地图中删除一个精灵
// 参数 szName：要删除的精灵名字
//
extern void		dDeleteSprite( const char *szName );

// dSetSpriteVisible：设置精灵隐藏或者显示(可见不可见)
// 参数 szName：精灵名字
// 参数 iVisible：1 可见 0不可见
//
extern void		dSetSpriteVisible( const char *szName, const int iVisible );

// dIsSpriteVisible：获取该精灵当前是否可见
// 返回值 1可见 0不可见
// 参数 szName：精灵名字
//
extern int		dIsSpriteVisible( const char *szName );

// dSetSpriteEnable：禁止或者启用该精灵。被禁止的精灵将不参与任何响应，包括不移动，没有碰撞等，仅仅是在地图中显示
// 参数 szName：精灵名字
// 参数 iEnable：1启用 0禁止
//
extern void		dSetSpriteEnable( const char *szName, const int iEnable );

// dSetSpriteScale：设置精灵的缩放值
// 参数 szName：精灵名字
// 参数 fScale：缩放值。大于0的值
//
extern void		dSetSpriteScale( const char *szName, const float fScale );

// dIsPointInSprite：判断某个坐标点是否位于精灵内部
// 返回值 1 在 0 不在
// 参数 szName：精灵名字
// 参数 fPosX：X坐标点
// 参数 fPosY：Y坐标点
//
extern int 	dIsPointInSprite( const char *szName, const float fPosX, const float fPosY );

// dSetSpritePosition：设置精灵位置
// 参数 szName：精灵名字
// 参数 fPosX：X坐标
// 参数 fPosY：Y坐标
//
extern void		dSetSpritePosition( const char *szName, const float fPosX, const float fPosY );

// dSetSpritePositionX：只设置精灵X坐标
// 参数 szName：精灵名字
// 参数 fPosX：X坐标
//
extern void		dSetSpritePositionX( const char *szName, const float fPosX );

// dSetSpritePositionY：只设置精灵Y坐标
// 参数 szName：精灵名字
// 参数 fPosY：Y坐标
//
extern void		dSetSpritePositionY( const char *szName, const float fPosY );

// dGetSpritePositionX：获取精灵X坐标
// 参数 szName：精灵名字
// 返回值：精灵的X坐标
//
extern float	dGetSpritePositionX( const char *szName );

// dGetSpritePositionY：获取精灵Y坐标
// 参数 szName：精灵名字
// 返回值：精灵的Y坐标
//
extern float	dGetSpritePositionY( const char *szName );

// dGetSpriteLinkPointPosX：获取精灵链接点X坐标。链接点是依附于精灵的一个坐标点，可以在编辑器里增加或者删除
// 参数 szName：精灵名字
// 参数 iId：链接点序号，第一个为1，后面依次递加
//
extern float	dGetSpriteLinkPointPosX( const char *szName, const int iId );

// dGetSpriteLinkPointPosY：获取精灵链接点Y坐标。链接点是依附于精灵的一个坐标点，可以在编辑器里增加或者删除
// 参数 szName：精灵名字
// 参数 iId：链接点序号，第一个为1，后面依次递加
//
extern float	dGetSpriteLinkPointPosY( const char *szName, const int iId );

// dSetSpriteRotation：设置精灵的旋转角度
// 参数 szName：精灵名字
// 参数 fRot：旋转角度，范围0 - 360
//
extern void		dSetSpriteRotation( const char *szName, const float fRot );

// dGetSpriteRotation：获取精灵的旋转角度
// 参数 szName：精灵名字
// 返回值：精灵的旋转角度
//
extern float	dGetSpriteRotation( const char *szName );

// dSetSpriteAutoRot：设置精灵按照指定速度自动旋转
// 参数 szName：精灵名字
// 参数 fRotSpeed：旋转速度
//
extern void 	dSetSpriteAutoRot( const char *szName, const float fRotSpeed );

// dSetSpriteWidth：设置精灵外形宽度
// 参数 szName：精灵名字
// 参数 fWidth：宽度值，大于0
//
extern void		dSetSpriteWidth( const char *szName, const float fWidth );

// dGetSpriteWidth：获取精灵外形宽度
// 参数 szName：精灵名字
// 返回值：精灵宽度值
//
extern float	dGetSpriteWidth( const char *szName );

// dSetSpriteHeight：设置精灵外形高度
// 参数 szName：精灵名字
// 参数 fHeight：精灵高度值
//
extern void		dSetSpriteHeight( const char *szName, const float fHeight );

// dGetSpriteHeight：获取精灵外形高度
// 参数 szName：精灵名字
// 返回值：精灵高度值
//
extern float	dGetSpriteHeight( const char *szName );

// dSetSpriteFlipX：设置精灵图片X方向翻转显示
// 参数 szName：精灵名字
// 参数 iFlipX：1 翻转 0不翻转(恢复原来朝向)
//
extern void		dSetSpriteFlipX( const char *szName, const int iFlipX );

// dGetSpriteFlipX：获取当前精灵图片X方向是否是翻转显示
// 参数 szName：精灵名字
// 返回值：1 翻转 0不翻转
//
extern int		dGetSpriteFlipX( const char *szName );

// dSetSpriteFlipY：设置精灵图片Y方向翻转显示
// 参数 szName：精灵名字
// 参数 iFlipY：1 翻转 0不翻转(恢复原来朝向)
//
extern void		dSetSpriteFlipY( const char *szName, const int iFlipY );

// dGetSpriteFlipY：获取当前精灵图片Y方向是否是翻转显示
// 参数 szName：精灵名字
// 返回值：1 翻转 0不翻转
//
extern int		dGetSpriteFlipY( const char *szName );

// dSetSpriteFlip：同时设置精灵翻转X及Y方向
// 参数 szName：精灵名字
// 参数 iFlipX：1 翻转 0不翻转(恢复原来朝向)
// 参数 iFlipY：1 翻转 0不翻转(恢复原来朝向)
//
extern void		dSetSpriteFlip( const char *szName, const int iFlipX, const int iFlipY );

// dSetSpriteLifeTime：设置精灵的生命时长，时间到了之后将自动被删除
// 参数 szName：精灵名字
// 参数 fLifeTime：生命时长，单位 秒
//
extern void		dSetSpriteLifeTime( const char *szName, const float fLifeTime );

// dGetSpriteLifeTime：获取精灵生命时长
// 参数 szName：精灵名字
// 返回值：生命时长，单位 秒
//
extern float	dGetSpriteLifeTime( const char *szName );	

// dSpriteMoveTo：让精灵按照给定速度移动到给定坐标点
// 参数 szName：精灵名字
// 参数 fPosX：移动的目标X坐标值
// 参数 fPosY：移动的目标Y坐标值
// 参数 fSpeed：移动速度
// 参数 iAutoStop：移动到终点之后是否自动停止, 1 停止 0 不停止
//
extern void		dSpriteMoveTo( const char *szName, const float fPosX, const float fPosY, const float fSpeed, const int iAutoStop );

// dSpriteRotateTo：让精灵按照给定速度旋转到给定的角度
// 参数 szName：精灵名字
// 参数 fRotation：给定的目标旋转值
// 参数 fRotSpeed：旋转速度
// 参数 iAutoStop：旋转到终点之后是否自动停止, 1 停止 0 不停止
//
extern void		dSpriteRotateTo( const char *szName, const float fRotation, const float fRotSpeed, const int iAutoStop );

// dSetSpriteWorldLimit：设置精灵的世界边界坐标限制及碰撞模式
// 参数 szName：精灵名字
// 参数 Limit：碰撞到世界边界之后的响应模式，如果为OFF，则是关闭世界边界碰撞。其它值见 EWorldLimit
// 参数 fLeft：边界的左边X坐标
// 参数 fTop：边界的上边Y坐标
// 参数 fRight：边界的右边X坐标
// 参数 fBottom：边界的下边Y坐标
//
extern void		dSetSpriteWorldLimit( const char *szName, const EWorldLimit Limit, const float fLeft, const float fTop, const float fRight, const float fBottom );

// dSetSpriteWorldLimitMode：设置精灵的世界边界碰撞模式
// 参数 szName：精灵名字
// 参数 Limit：碰撞到世界边界之后的响应模式，如果为OFF，则是关闭世界边界碰撞。其它值见 EWorldLimit
//
extern void		dSetSpriteWorldLimitMode( const char *szName, const EWorldLimit Limit );

// dSetSpriteWorldLimitMin：设置精灵的世界边界上边及左边坐标限制
// 参数 szName：精灵名字
// 参数 fLeft：边界的左边X坐标
// 参数 fTop：边界的上边Y坐标
//
extern void		dSetSpriteWorldLimitMin( const char *szName, const float fLeft, const float fTop );

// dSetSpriteWorldLimitMax：设置精灵的世界边界下边及右边坐标限制
// 参数 szName：精灵名字
// 参数 fRight：边界的右边X坐标
// 参数 fBottom：边界的下边Y坐标
//
extern void		dSetSpriteWorldLimitMax( const char *szName, const float fRight, const float fBottom );

// dGetSpriteWorldLimitLeft：获取精灵世界边界左边界限制
// 参数 szName：精灵名字
//
extern float	dGetSpriteWorldLimitLeft( const char *szName);

// dGetSpriteWorldLimitTop：获取精灵世界边界上边界限制
// 参数 szName：精灵名字
//
extern float	dGetSpriteWorldLimitTop( const char *szName);

// dGetSpriteWorldLimitRight：获取精灵世界边界右边界限制
// 参数 szName：精灵名字
//
extern float	dGetSpriteWorldLimitRight( const char *szName);

// dGetSpriteWorldLimitBottom：获取精灵世界边界下边界限制
//
extern float	dGetSpriteWorldLimitBottom( const char *szName);

// dSetSpriteCollisionSend：设置精灵是否可以发送(产生)碰撞
// 精灵的碰撞方式为：当A移动中碰上B时，如果A是可以产生碰撞的，B是可以接受碰撞的，则这2个物体会产生碰撞，精灵碰撞的API将被调用。否则无碰撞发生
// 参数 szName：精灵名字
// 参数 iSend：1 可以产生 0 不产生
//
extern void 	dSetSpriteCollisionSend( const char *szName, const int iSend );

// dSetSpriteCollisionReceive：设置精灵是否可以接受碰撞
// 精灵的碰撞方式为：当A移动中碰上B时，如果A是可以产生碰撞的，B是可以接受碰撞的，则这2个物体会产生碰撞，精灵碰撞的API将被调用。否则无碰撞发生
// 参数 szName：精灵名字
// 参数 iReceive：1 可以接受 0 不接受
//
extern void 	dSetSpriteCollisionReceive( const char *szName, const int iReceive );

// dSetSpriteCollisionPhysicsSend：设置精灵是否可以发送(产生)物理碰撞
// 参数 iSend：1 可以产生 0 不产生
//
extern void 	dSetSpriteCollisionPhysicsSend( const char *szName, const int iSend );

// dSetSpriteCollisionPhysicsReceive：设置精灵是否可以接受物理碰撞
// 参数 iReceive：1 可以接受 0 不接受
//
extern void 	dSetSpriteCollisionPhysicsReceive( const char *szName, const int iReceive );

// dSetSpriteCollisionActive：同时设置精灵是否可以产生及接受碰撞
// 精灵的碰撞方式为：当A移动中碰上B时，如果A是可以产生碰撞的，B是可以接受碰撞的，则这2个物体会产生碰撞，精灵碰撞的API将被调用。否则无碰撞发生
// 参数 szName：精灵名字
// 参数 iSend：1 可以产生 0 不产生
// 参数 iReceive：1 可以接受 0 不接受
//
extern void 	dSetSpriteCollisionActive( const char *szName, const int iSend, const int iReceive );

// dGetSpriteCollisionSend：获取精灵当前是否是可以产生碰撞
// 参数 szName：精灵名字
// 返回值：1 可以产生 0 不产生
//
extern int 	dGetSpriteCollisionSend( const char *szName );

// dGetSpriteCollisionReceive：获取精灵当前是否是可以接受碰撞
// 参数 szName：精灵名字
// 返回值：1 可以接受 0 不接受
//
extern int 	dGetSpriteCollisionReceive( const char *szName );

// dSetSpriteCollisionResponse：设置精灵与精灵的碰撞响应模式
// 参数 szName：精灵名字
// 参数 Response：响应模式，如果为OFF，则为关闭碰撞响应，碰撞API将不会被调用。其它值见 ECollisionResponse
//
extern void		dSetSpriteCollisionResponse( const char *szName, const ECollisionResponse Response );

// dSetSpriteCollisionMaxIterations：设置精灵碰撞之后的最大反弹次数
// 参数 szName：精灵名字
// 参数 iTimes：反弹次数
//
extern void		dSetSpriteCollisionMaxIterations( const char *szName, const int iTimes );

// dSetSpriteForwardMovementOnly：设置精灵是否只能朝前移动
// 参数 szName：精灵名字
// 参数 iForward：1 只能朝前移动 0 可以朝其他方向移动
//
extern void		dSetSpriteForwardMovementOnly( const char *szName, const int iForward );

// dGetSpriteForwardMovementOnly：获取精灵当前是否只能朝前移动
// 参数 szName：精灵名字
// 返回值：1 只能朝前移动 0 可以朝其它方向移动
//
extern int		dGetSpriteForwardMovementOnly( const char *szName );

// dSetSpriteForwardSpeed：设置精灵向前的速度
// 参数 szName：精灵名字
// 参数 fSpeed：速度
//
extern void		dSetSpriteForwardSpeed( const char *szName, const float fSpeed );

// dSetSpriteImpulseForce：设置精灵瞬间推力
// 参数 szName：精灵名字
// 参数 fForceX：X方向推力大小
// 参数 fForceY：Y方向推力大小
// 参数 iGravitic：是否计算重力 : 1 计算，0不计算
//
extern void 	dSetSpriteImpulseForce( const char *szName, const float fForceX, const float fForceY, const int iGravitic );

// dSetSpriteImpulseForcePolar：按角度朝向设置精灵瞬间推力
// 参数 szName：精灵名字
// 参数 fPolar：角度朝向
// 参数 fForce：推力大小
// 参数 iGravitic：是否计算重力 : 1 计算，0不计算
//
extern void 	dSetSpriteImpulseForcePolar( const char *szName, const float fPolar, const float fForce, const int iGravitic );

// dSetSpriteConstantForceX：设置精灵X方向常量推力
// 参数 szName：精灵名字
// 参数 fForceX：X方向推力大小
//
extern void 	dSetSpriteConstantForceX(const char *szName, const float fForceX );

// dSetSpriteConstantForceY：设置精灵Y方向常量推力
// 参数 szName：精灵名字
// 参数 fForceY：Y方向推力大小
//
extern void 	dSetSpriteConstantForceY(const char *szName, const float fForceY );

// dSetSpriteConstantForceGravitic：精灵在计算常量推力的时候，是否计算重力
// 参数 szName：精灵名字
// 参数 iGravitic：是否计算重力 : 1 计算 0不计算
//
extern void 	dSetSpriteConstantForceGravitic(const char *szName, const int iGravitic );

// dSetSpriteConstantForce：设置精灵常量推力
// 参数 szName：精灵名字
// 参数 fForceX：X方向推力大小
// 参数 fForceY：Y方向推力大小
// 参数 iGravitic：是否计算重力 : 1 计算 0不计算
//
extern void 	dSetSpriteConstantForce(const char *szName, const float fForceX, const float fForceY, const int iGravitic );

// dSetSpriteConstantForcePolar：按角度朝向设置精灵常量推力
// 参数 szName：精灵名字
// 参数 fPolar：角度朝向
// 参数 fForce：推力大小
// 参数 iGravitic：是否计算重力 : 1 计算 0不计算
//
extern void 	dSetSpriteConstantForcePolar(const char *szName, const float fPolar, const float fForce, const int iGravitic );

// dStopSpriteConstantForce：停止精灵常量推力
// 参数 szName：精灵名字
//
extern void 	dStopSpriteConstantForce(const char *szName);

// dSetSpriteForceScale：按倍数缩放精灵当前受的推力
// 参数 szName：精灵名字
// 参数 fScale：缩放值
//
extern void 	dSetSpriteForceScale(const char *szName, const float fScale );

// dSetSpriteAtRest：暂停/继续精灵的各种受力计算
// 参数 szName：精灵名字
// 参数 iRest：1 暂停 0 继续
//
extern void 	dSetSpriteAtRest(const char *szName, const int iRest );

// dGetSpriteAtRest：获取精灵当前是否在暂停中
// 参数 szName：精灵名字
// 返回值：1 暂停中 0 正常
//
extern int 	dGetSpriteAtRest(const char *szName );

// dSetSpriteFriction：设置精灵摩擦力
// 参数 szName：精灵名字
// 参数 fFriction：摩擦力大小
//
extern void 	dSetSpriteFriction( const char *szName, const float fFriction );

// dSetSpriteRestitution：设置精灵弹力
// 参数 szName：精灵名字
// 参数 fRestitution：弹力值大小
//
extern void 	dSetSpriteRestitution( const char *szName, const float fRestitution );

// dSetSpriteMass：设置精灵质量
// 参数 szName：精灵名字
// 参数 fMass：质量大小
//
extern void 	dSetSpriteMass( const char *szName, const float fMass );

// dGetSpriteMass：获取精灵质量
// 参数 szName：精灵名字
// 返回值 ：质量大小
//
extern float 	dGetSpriteMass( const char *szName );

// dSetSpriteAutoMassInertia：开启或者关闭精灵惯性
// 参数 szName：精灵名字
// 参数 iStatus：1 开启 0 关闭
//
extern void 	dSetSpriteAutoMassInertia( const char *szName, const int iStatus );

// dSetSpriteInertialMoment：设置精灵惯性大小
// 参数 szName：精灵名字
// 参数 fInert：惯性大小
//
extern void 	dSetSpriteInertialMoment( const char *szName, const float fInert );

// dSetSpriteDamping：设置精灵衰减值
// 参数 szName：精灵名字
// 参数 fDamp：衰减值大小
//
extern void 	dSetSpriteDamping( const char *szName, const float fDamp );

// dSetSpriteImmovable：设置精灵是否不可移动
// 参数 szName：精灵名字
// 参数 iImmovable：1 不可以移动 0 可以移动
//
extern void 	dSetSpriteImmovable( const char *szName, const int iImmovable );

// dGetSpriteImmovable：获取精灵当前是否不可以移动
// 参数 szName：精灵名字
// 返回值：1 不可以移动 0 可以移动
//
extern int 	dGetSpriteImmovable( const char *szName );

// dSetSpriteLinearVelocity：设置精灵移动速度
// 参数 szName：精灵名字
// 参数 fVelX：X方向速度
// 参数 fVelY：Y方向速度
//
extern void 	dSetSpriteLinearVelocity( const char *szName, const float fVelX, const float fVelY );

// dSetSpriteLinearVelocityX：设置精灵X方向移动速度
// 参数 szName：精灵名字
// 参数 fVelX：X方向速度
//
extern void 	dSetSpriteLinearVelocityX( const char *szName, const float fVelX );

// dSetSpriteLinearVelocityY：设置精灵Y方向移动速度
// 参数 szName：精灵名字
// 参数 fVelY：Y方向速度
//
extern void 	dSetSpriteLinearVelocityY( const char *szName, const float fVelY );

// dSetSpriteLinearVelocityPolar：按角度朝向设置精灵移动速度
// 参数 szName：精灵名字
// 参数 fSpeed：移动速度
// 参数 fPolar：角度朝向
//
extern void 	dSetSpriteLinearVelocityPolar( const char *szName, const float fSpeed, const float fPolar );

// dSetSpriteAngularVelocity：设置精灵角度旋转速度
// 参数 szName：精灵名字
// 参数 fAngular：角度旋转速度
//
extern void 	dSetSpriteAngularVelocity( const char *szName, const float fAngular );

// dSetSpriteMinLinearVelocity：设置精灵最小速度
// 参数 szName：精灵名字
// 参数 fMin：最小速度值
//
extern void 	dSetSpriteMinLinearVelocity( const char *szName, const float fMin );

// dSetSpriteMaxLinearVelocity：设置精灵最大速度
// 参数 szName：精灵名字
// 参数 fMax：最大速度值
//
extern void 	dSetSpriteMaxLinearVelocity( const char *szName, const float fMax );

// dSetSpriteMinAngularVelocity：设置精灵最小角速度
// 参数 szName：精灵名字
// 参数 fMin：最小角速度
//
extern void 	dSetSpriteMinAngularVelocity( const char *szName, const float fMin );

// dSetSpriteMaxAngularVelocity：设置精灵最大角速度
// 参数 szName：精灵名字
// 参数 fMax：最大角速度
//
extern void 	dSetSpriteMaxAngularVelocity( const char *szName, const float fMax );

// dGetSpriteLinearVelocityX：获取精灵X方向速度
// 参数 szName：精灵名字
// 返回值：X方向速度
//
extern float 	dGetSpriteLinearVelocityX( const char *szName );

// dGetSpriteLinearVelocityY：获取精灵Y方向速度
// 参数 szName：精灵名字
// 返回值：Y方向速度
//
extern float 	dGetSpriteLinearVelocityY( const char *szName );

// dSpriteMountToSprite：将一个精灵绑定到另一个精灵上，暂时的成为另一个精灵的一部分，跟随其运动等
// 参数 szSrcName：要绑定的精灵名字
// 参数 szDstName：承载绑定的母体精灵名字
// 参数 fOffSetX：绑定偏移X
// 参数 fOffsetY：绑定偏移Y
// 返回值：返回一个绑定ID
//
extern int		dSpriteMountToSprite( const char *szSrcName, const char *szDstName, const float fOffSetX, const float fOffsetY );

// dSpriteMountToSpriteLinkPoint：将一个精灵绑定到另一个精灵上，绑定位置为指定的链接点，暂时的成为另一个精灵的一部分，跟随其运动等
// 参数 szSrcName：要绑定的精灵名字
// 参数 szDstName：承载绑定的母体精灵名字
// 参数 iPointId：链接点序号
// 返回值：返回一个绑定ID
//
extern int		dSpriteMountToSpriteLinkPoint( const char *szSrcName, const char *szDstName, const int iPointId );

// dSetSpriteMountRotation：设置精灵的绑定朝向，即相对于母体的朝向
// 参数 szName：精灵名字
// 参数 fRot：角度朝向，0 - 360
//
extern void		dSetSpriteMountRotation( const char *szName, const float fRot );

// dGetSpriteMountRotation：获取精灵的绑定朝向，即相对于母体的朝向
// 参数 szName：精灵名字
// 返回值：角度朝向
//
extern float	dGetSpriteMountRotation( const char *szName );

// dSetSpriteAutoMountRotation：设置精灵绑定之后自动旋转
// 参数 szName：精灵名字
// 参数 fRot：旋转速度
//
extern void		dSetSpriteAutoMountRotation( const char *szName, const float fRot );

// dGetSpriteAutoMountRotation：获取精灵绑定之后的自动旋转值
// 参数 szName：精灵名字
// 返回值：旋转速度
//
extern float	dGetSpriteAutoMountRotation( const char *szName );

// dSetSpriteMountForce：绑定至另一个精灵时，附加的作用力
// 参数 szName：精灵名字
// 参数 fFroce：作用力
//
extern void		dSetSpriteMountForce( const char *szName, const float fForce );

// dSetSpriteMountTrackRotation：绑定的精灵是否跟随母体旋转
// 参数 szName：精灵名字
// 参数 iTrackRotation：1 跟随 0 不跟随
//
extern void		dSetSpriteMountTrackRotation( const char *szName, const int iTrackRotation );

// dSetSpriteMountOwned：母体被删除的时候，绑定的精灵是否也跟着被删除
// 参数 szName：精灵名字
// 参数 iMountOwned：1 跟着 0 不跟着
//
extern void		dSetSpriteMountOwned( const char *szName, const int iMountOwned );

// dSetSpriteMountInheritAttributes：绑定的时候，是否继承母体的属性
// 参数 szName：精灵名字
// 参数 iInherAttr：1 继承 0 不继承
//
extern void		dSetSpriteMountInheritAttributes( const char *szName, const int iInherAttr );

// dSpriteDismount：将已经绑定的精灵进行解绑
// 参数 szName：精灵名字
//
extern void		dSpriteDismount( const char *szName );

// dGetSpriteIsMounted：判断精灵是否绑定在另一个精灵上
// 参数 szName：精灵名字
// 返回值：1 绑定 0 不绑定
//
extern int		dGetSpriteIsMounted( const char *szName );

// dGetSpriteMountedParent：获取绑定的母体精灵的名字
// 参数 szName：精灵名字
// 返回值：母体精灵名字，如果未绑定，则返回空字符串
//
extern const char*	dGetSpriteMountedParent( const char *szName );

// dSetSpriteColorRed：更改精灵显示颜色中的红色。默认精灵的红绿蓝三颜色的值均为255，修改其中一项将可以改变其颜色
// 参数 szName：精灵名字
// 参数 iCol：颜色范围 0 - 255
//
extern void		dSetSpriteColorRed( const char *szName, const int iCol );

// dSetSpriteColorGreen：更改精灵显示颜色中的绿色。默认精灵的红绿蓝三颜色的值均为255，修改其中一项将可以改变其颜色
// 参数 szName：精灵名字
// 参数 iCol：颜色范围 0 - 255
//
extern void		dSetSpriteColorGreen( const char *szName, const int iCol );

// dSetSpriteColorBlue：更改精灵显示颜色中的蓝色。默认精灵的红绿蓝三颜色的值均为255，修改其中一项将可以改变其颜色
// 参数 szName：精灵名字
// 参数 iCol：颜色范围 0 - 255
//
extern void		dSetSpriteColorBlue( const char *szName, const int iCol );

// dSetSpriteColorAlpha：设置精灵透明度
// 参数 szName：精灵名字
// 参数 iCol：透明度，值0 - 255，从完全透明至完全不透明
//
extern void		dSetSpriteColorAlpha( const char *szName, const int iCol );

// dGetSpriteColorRed：获取精灵显示颜色中的红色值
// 参数 szName：精灵名字
// 返回值：颜色值
//
extern int		dGetSpriteColorRed( const char *szName );

// dGetSpriteColorGreen：获取精灵显示颜色中的绿色值
// 参数 szName：精灵名字
// 返回值：颜色值
//
extern int		dGetSpriteColorGreen( const char *szName );

// dGetSpriteColorBlue：获取精灵显示颜色中的蓝色值
// 参数 szName：精灵名字
// 返回值：颜色值
//
extern int		dGetSpriteColorBlue( const char *szName );

// dGetSpriteColorAlpha：获取精灵透明度
// 参数 szName：精灵名字
// 返回值：透明度
//
extern int		dGetSpriteColorAlpha( const char *szName );

// dSetStaticSpriteImage：设置/更改静态精灵的显示图片
// 参数 szName：精灵名字
// 参数 szImageName：图片名字
// 参数 iFrame：该图片的显示帧数。为编辑器预览图里显示的1/N，范围为 0 到 N - 1
//
extern void		dSetStaticSpriteImage( const char *szName, const char *szImageName, const int iFrame );

// dSetStaticSpriteFrame：设置静态精灵当前图片的显示帧数
// 参数 szName：精灵名字
// 参数 iFrame：该图片的显示帧数。为编辑器预览图里显示的1/N，范围为 0 到 N - 1
//
extern void		dSetStaticSpriteFrame( const char *szName, const int iFrame );

// dGetStaticSpriteImage：获取精灵当前显示的图片名字
// 参数 szName：精灵名字
// 返回值：图片名字
//
extern const char* dGetStaticSpriteImage( const char *szName );

// dGetStaticSpriteFrame：获取精灵当前显示的图片帧数
// 参数 szName：精灵名字
// 返回值：帧数
//
extern int		dGetStaticSpriteFrame( const char *szName );

// dSetAnimateSpriteFrame：设置动态精灵的动画帧数
// 参数 szName：精灵名字
// 参数 iFrame：动画帧数
//
extern void		dSetAnimateSpriteFrame( const char *szName, const int iFrame );

// dIsAnimateSpriteAnimationFinished：判断动态精灵当前动画是否播放完毕，只针对非循环动画而言
// 参数 szName：精灵名字
// 返回值：1 完毕 0 未完毕
//
extern int		dIsAnimateSpriteAnimationFinished( const char *szName );

// dGetAnimateSpriteAnimationName：获取动态精灵当前动画名字
// 参数 szName：精灵名字
// 返回值：动画名字
//
extern const char* dGetAnimateSpriteAnimationName( const char *szName );

// dGetAnimateSpriteAnimationTime：获取动画精灵当前动画时间长度
// 参数 szName：精灵名字
// 返回值：长度，单位秒
//
extern float	dGetAnimateSpriteAnimationTime( const char *szName );

// dAnimateSpritePlayAnimation：动画精灵播放动画
// 参数 szName：精灵名字
// 参数 szAnim：动画名字
// 参数 iRestore：播放完毕后是否恢复当前动画. 1 恢复 0 不恢复
// 返回值：是否播放成功, 1 : 成功 0 ：不成功
//
extern int		dAnimateSpritePlayAnimation( const char *szName, const char *szAnim, const int iRestore );

// dSetTextValue：文字精灵显示某个数值
// 参数 szName：精灵名字
// 参数 iValue：要显示的数值
//
extern void		dSetTextValue( const char *szName, int iValue );

// dSetTextValueFloat：文字精灵显示某个浮点数值
// 参数 szName：精灵名字
// 参数 fValue：要显示的数值
//
extern void		dSetTextValueFloat( const char *szName, float fValue );

// dSetTextString：文字精灵显示某个字符串文字
// 参数 szName：精灵名字
// 参数 szStr：要显示的字符串
//
extern void		dSetTextString( const char *szName, const char *szStr );

// dSetTextChar：文字精灵显示某个字符
// 参数 szChar：要显示的字符
//
extern void		dSetTextChar( const char *szName, char szChar );

// dLoadMap：载入新场景。注意，载入新场景的时候，旧场景的所有精灵都将被引擎删除掉，所以所有在程序中创建、复制出来的精灵都必须在调用本API之前先删除掉
// 参数 szName：场景名字。即新建场景保存的时候取的名字，必须带小写的后缀 -- xxx.t2d。不用带路径
//
extern void		dLoadMap( const char *szName );

// dPlaySound：播放声音
// 参数 szName：声音的路径及名称，具体值请在编辑器的资源 -> 添加声音那里查看本项目里的声音资源，完整按照那个路径值填写即可
// 参数 iLoop：是否循环播放 1 循环 0 不循环。循环播放的声音，需要手动停止，请使用返回的ID，调用API停止该声音的播放。非循环的播放完之后将自动停止
// 参数 fVolume：音量大小，0-1。1为声音文件的原声大小
// 返回值：声音ID，循环播放的声音需要该ID来停止播放
//
extern int		dPlaySound(const char *szName, const int iLoop, const float fVolume );

// dStopSound：停止声音的播放
// 参数 iSoundId：API dPlaySound 播放声音的时候返回的声音ID
//
extern void		dStopSound( const int iSoundId );

// dStopAllSound：停止播放所有声音
//
extern void		dStopAllSound();

// dPlayEffect：播放一个不循环的特效，播放完毕之后该特效自动删除
// 参数 szSrcName：预先摆放在地图中的特效模板名字
// 参数 fLifeTime：生命时长，时间到了之后将被自动删除
// 参数 fPosX：播放的X坐标
// 参数 fPosY：播放的Y坐标
// 参数 fRotation：播放的角度朝向
//
extern void		dPlayEffect(const char *szSrcName, const float fLifeTime, const float fPosX, const float fPosY, const float fRotation);

// dPlayLoopEffect：播放一个循环特效，不需要该特效的时候，需要自己调用API进行删除
// 参数 szSrcName：预先摆放在地图中的特效模板名字
// 参数 szMyName：新特效名字，要删除该特效的时候用到
// 参数 fCycleTime：循环时长，时间到了之后将重头播放
// 参数 fPosX：播放的X坐标
// 参数 fPosY：播放的Y坐标
// 参数 fRotation：播放的角度朝向
//
extern void		dPlayLoopEffect(const char *szSrcName, const char *szMyName, const float fCycleTime, const float fPosX, const float fPosY, const float fRotation);

// dDeleteEffect：删除一个正在播放的特效，只有循环特效才需要手动删除
// 参数 szName：特效名字
//
extern void		dDeleteEffect(const char *szName);

//////////////////////////////////////////////////////////////////////////////////////////
//
// 以下API为系统API，请勿自己调用
//
//////////////////////////////////////////////////////////////////////////////////////////

// dGetTimeDelta：获取两次调用本函数之间的时间差
// 返回值：float，单位 秒
//
extern float	dGetTimeDelta();
// dEngineMainLoop：引擎主循环函数。请勿自己调用
//
extern int		dEngineMainLoop();
// dInitGameEngine：初始化引擎，请勿自己调用
//
extern int		dInitGameEngine( HINSTANCE hInstance, LPSTR lpCmdLine );
// dShutdownGameEngine：关闭引擎，请勿自己调用
//
extern void		dShutdownGameEngine();

//
#endif // _COMMON_API_H_
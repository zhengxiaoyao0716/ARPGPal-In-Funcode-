/////////////////////////////////////////////////////////////////////////////////
//
//
//
//
/////////////////////////////////////////////////////////////////////////////////
#ifndef _LESSON_X_H_
#define _LESSON_X_H_
//
#include <Windows.h>

extern void	GameMainLoop( float	fDeltaTime );
extern void OnMouseMove( const float fMouseX, const float fMouseY );
extern void OnMouseClick( const int iMouseType, const float fMouseX, const float fMouseY );
extern void OnMouseUp( const int iMouseType, const float fMouseX, const float fMouseY );
extern void OnKeyDown( const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress );
extern void OnKeyUp( const int iKey );
extern void OnSpriteColSprite( const char *szSrcName, const char *szTarName );
extern void OnSpriteColWorldLimit( const char *szName, const int iColSide );


#endif // _LESSON_X_H_
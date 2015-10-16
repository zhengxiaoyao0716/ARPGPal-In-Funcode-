//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------

///
/// Network
///
$pref::Net::LagThreshold = 400;
$pref::Net::Port = 28000;

///
/// Input
///
$pref::Input::LinkMouseSensitivity = 1;
$pref::Input::MouseEnabled = 0;
$pref::Input::JoystickEnabled = 0;
$pref::Input::KeyboardTurnSpeed = 0.1;

///
/// Audio
///
$pref::Audio::driver = "OpenAL";
$pref::Audio::forceMaxDistanceUpdate = 0;
$pref::Audio::environmentEnabled = 0;
$pref::Audio::masterVolume   = 0.8;
$pref::Audio::channelVolume1 = 0.8;
$pref::Audio::channelVolume2 = 0.8;
$pref::Audio::channelVolume3 = 0.8;
$pref::Audio::channelVolume4 = 0.8;
$pref::Audio::channelVolume5 = 0.8;
$pref::Audio::channelVolume6 = 0.8;
$pref::Audio::channelVolume7 = 0.8;
$pref::Audio::channelVolume8 = 0.8;

///
/// TGB
///
$pref::T2D::dualCollisionCallbacks = 1;
$pref::T2D::imageMapDumpTextures = 0;
$pref::T2D::imageMapEchoErrors = 1;
$pref::T2D::imageMapFixedMaxTextureError = 1;
$pref::T2D::imageMapFixedMaxTextureSize = 0;
$pref::T2D::imageMapShowPacking = 0;
$pref::T2D::imageMapPreloadDefault = true;
$pref::T2D::imageMapAllowUnloadDefault = false;
$pref::T2D::particleEngineQuantityScale = 1.0;
$pref::T2D::renderContactChange = 0.5;
$pref::T2D::renderContactMax = 16;
$pref::T2D::warnFileDeprecated = 1;
$pref::T2D::warnSceneOccupancy = 1;

///
/// Server
///
$pref::Server::Name = "TGB Server";
$pref::Player::Name = "TGB Player";
$pref::Server::port = 28000;
$pref::Server::MaxPlayers = 32;
$pref::Server::RegionMask = 2;
$pref::Net::RegionMask = 2;
$pref::Master0 = "2:master.garagegames.com:28002";

///
/// Video
///

$pref::ts::detailAdjust = 0.45;

$pref::Video::appliedPref = 0;
$pref::Video::disableVerticalSync = 1;
$pref::Video::monitorNum = 0;
$pref::Video::screenShotFormat = "PNG";

$pref::OpenGL::gammaCorrection = 0.5;
$pref::OpenGL::force16BitTexture = "0";
$pref::OpenGL::forcePalettedTexture = "0";
$pref::OpenGL::maxHardwareLights = 3;
$pref::VisibleDistanceMod = 1.0;


// Here is where we will do the video device stuff, so it overwrites the defaults
// First set the PCI device variables (yes AGP/PCI-E works too)
initDisplayDeviceInfo();

// Default to OpenGL
$pref::Video::displayDevice = "OpenGL";
$pref::Video::preferOpenGL = 1;

// But allow others
$pref::Video::allowOpenGL = 1;
$pref::Video::allowD3D = 1;

// And not full screen
$pref::Video::fullScreen = 0;

// This logic would better be in a kind of database file
switch$( $PCI_VEN )
{
   case "VEN_8086": // Intel
      $pref::Video::displayDevice = "D3D";
      $pref::Video::allowOpenGL = 0;
      
      // Force fullscreen on the 810E and 815G
      if( $PCI_DEV $= "DEV_1132" || $PCI_DEV $= "DEV_7125" )
         $pref::Video::fullScreen = "1";
         
   case "VEN_1039": // SIS
      $pref::Video::allowOpenGL = 0;
      $pref::Video::displayDevice = "D3D";
      
   case "VEN_1106": // VIA
      $pref::Video::allowOpenGL = 0;
      $pref::Video::displayDevice = "D3D";
      
   case "VEN_5333": // S3
      $pref::Video::allowOpenGL = 0;
      $pref::Video::displayDevice = "D3D";
      
   case "VEN_1002": // ATI
      $pref::Video::displayDevice = "OpenGL";
      
      if( $PCI_DEV $= "DEV_5446" ) // Rage 128 Pro
      {
         $pref::Video::displayDevice = "D3D";
         $pref::Video::allowOpenGL = 0;
      }
         
   case "VEN_10DE": // NVIDIA
      $pref::Video::displayDevice = "OpenGL";
}

echo( "\nUsing " @  $pref::Video::displayDevice @ " rendering. Fullscreen: " @ $pref::Video::fullScreen @ "\n");

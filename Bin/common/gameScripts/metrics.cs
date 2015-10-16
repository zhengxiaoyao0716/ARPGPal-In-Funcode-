//-----------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//-----------------------------------------------------------------------------

// load gui used to display various metric outputs
exec("~/Gui/FrameOverlayGui.gui");

function fpsMetricsCallback()
{
   return " FPS: " @ $fps::real @ 
          "  mspf: " @ 1000 / $fps::real;
}

function videoMetricsCallback()
{
   return fpsMetricsCallback() @
          "  Video -" @
          "  TC: " @ $OpenGL::triCount0 + $OpenGL::triCount1 + $OpenGL::triCount2 + $OpenGL::triCount3 @ 
          "  PC: " @ $OpenGL::primCount0 + $OpenGL::primCount1 + $OpenGL::primCount2 + $OpenGL::primCount3 @ 
          "  T_T: " @ $OpenGL::triCount1 @ 
          "  T_P: " @ $OpenGL::primCount1 @ 
          "  I_T: " @ $OpenGL::triCount2 @ 
          "  I_P: " @ $OpenGL::primCount2 @ 
          "  TS_T: " @ $OpenGL::triCount3 @ 
          "  TS_P: " @ $OpenGL::primCount3 @ 
          "  ?_T: " @ $OpenGL::triCount0 @ 
          "  ?_P: " @ $OpenGL::primCount0;
}

function textureMetricsCallback()
{
   return fpsMetricsCallback() @
          "  Texture --"@
          "  NTL: " @ $Video::numTexelsLoaded @
          "  TRP: " @ $Video::texResidentPercentage @
          "  TCM: " @ $Video::textureCacheMisses;
}

function timeMetricsCallback()
{
   return fpsMetricsCallback() @ 
         "  Time -- " @ 
         "  Sim Time: " @ getSimTime() @ 
         "  Mod: " @ getSimTime() % 32;
}

function audioMetricsCallback()
{
   return fpsMetricsCallback() @
          "  Audio --"@
          " OH:  " @ $Audio::numOpenHandles @
          " OLH: " @ $Audio::numOpenLoopingHandles @
          " AS:  " @ $Audio::numActiveStreams @
          " NAS: " @ $Audio::numNullActiveStreams @
          " LAS: " @ $Audio::numActiveLoopingStreams @
          " LS:  " @ $Audio::numLoopingStreams @
          " ILS: " @ $Audio::numInactiveLoopingStreams @
          " CLS: " @ $Audio::numCulledLoopingStreams;
}

function debugMetricsCallback()
{
   return fpsMetricsCallback() @
          "  Debug --"@
          "  NTL: " @ $Video::numTexelsLoaded @
          "  TRP: " @ $Video::texResidentPercentage @
          "  NP:  " @ $Metrics::numPrimitives @
          "  NT:  " @ $Metrics::numTexturesUsed @
          "  NO:  " @ $Metrics::numObjectsRendered;
}

function metrics(%expr)
{
   switch$(%expr)
   {
      case "audio":     %cb = "audioMetricsCallback()";
      case "debug":     %cb = "debugMetricsCallback()";
      case "fps":       %cb = "fpsMetricsCallback()";
      case "time":      %cb = "timeMetricsCallback()";
      case "texture":   
         GLEnableMetrics(true);
         %cb = "textureMetricsCallback()";

      case "video":     %cb = "videoMetricsCallback()";
   }
   
   if (%cb !$= "")
   {
      Canvas.pushDialog(FrameOverlayGui, 1000);
      TextOverlayControl.setValue(%cb);
   }
   else
   {
      GLEnableMetrics(false);
      Canvas.popDialog(FrameOverlayGui);
   }
}

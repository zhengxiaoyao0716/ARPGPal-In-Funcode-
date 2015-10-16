//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// initializeCanvas
// Constructs and initializes the default canvas window.
//---------------------------------------------------------------------------------------------
$canvasCreated = false;
function initializeCanvas(%windowName)
{
   // Don't duplicate the canvas.
   if($canvasCreated)
   {
      error("Cannot instantiate more than one canvas!");
      return;
   }
   
   videoSetGammaCorrection($pref::OpenGL::gammaCorrection);
   
   if (!createCanvas(%windowName))
   {
      error("Canvas creation failed. Shutting down.");
      quit();
   }

   // [neo, 5/11/2007 - #3051
   // Resolution is set to $Game::Resolution in levelEditor properties.ed.cs
   //%goodRes = $Game::WindowResolution;
   %goodres = $Game::Resolution;
   setScreenMode( GetWord( %goodres, 0), GetWord( %goodres,1), GetWord( %goodres,2), false );

   $canvasCreated = true;
}

//---------------------------------------------------------------------------------------------
// resetCanvas
// Forces the canvas to redraw itself.
//---------------------------------------------------------------------------------------------
function resetCanvas()
{
   if (isObject(Canvas))
      Canvas.repaint();
}

//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// formatImageNumber
// Preceeds a number with zeros to make it 6 digits long.
//---------------------------------------------------------------------------------------------
function formatImageNumber(%number)
{
   if(%number < 10)
      %number = "0" @ %number;
   if(%number < 100)
      %number = "0" @ %number;
   if(%number < 1000)
      %number = "0" @ %number;
   if(%number < 10000)
      %number = "0" @ %number;
   return %number;
}

//---------------------------------------------------------------------------------------------
// formatSessionNumber
// Preceeds a number with zeros to make it 4 digits long.
//---------------------------------------------------------------------------------------------
function formatSessionNumber(%number)
{
   if(%number < 10)
      %number = "0" @ %number;
   if(%number < 100)
      %number = "0" @ %number;
   return %number;
}

//---------------------------------------------------------------------------------------------
// recordMovie
// Captures screenshots at a rate of %fps frames per second until stopMovie is called.
//---------------------------------------------------------------------------------------------
function recordMovie(%movieName, %fps)
{
   $timeAdvance = 1000 / %fps;
   $screenGrabThread = schedule($timeAdvance, 0, movieGrabScreen, %filename, 0);   
}

function movieGrabScreen(%movieName, %frameNumber)
{
   screenshot(%movieName @ formatImageNumber(%frameNumber) @ ".png", "PNG");
   $screenGrabThread = schedule($timeAdvance, 0, movieGrabScreen, %movieName, %frameNumber + 1);   
}

function stopMovie()
{
   $timeAdvance = 0;
   cancel($screenGrabThread);
}

//---------------------------------------------------------------------------------------------
// doScreenShot
// Capture a screenshot.
//---------------------------------------------------------------------------------------------
$screenshotNumber = 0;
function doScreenShot(%val)
{
   // Because this can be bound to a hotkey, we make sure that %val is 1 or not specified. That
   // way, the screenshot will be taken only on keydown, or when this function is called with
   // no parameters.
   if ((%val) || (%val $= ""))
   {
      if ($pref::Video::screenShotSession $= "")
         $pref::Video::screenShotSession = 0;
         
      if ($screenshotNumber == 0)
         $pref::Video::screenShotSession++;
         
      if ($pref::Video::screenShotSession > 999)
         $pref::Video::screenShotSession = 1;
         
      %name = expandFileName( "game/data/screenshots/" @ formatSessionNumber($pref::Video::screenShotSession) @ "-" @
               formatImageNumber($screenshotNumber) );
      
      $screenshotNumber++;
      
      if (($pref::Video::screenShotFormat $= "JPEG") ||
          ($pref::video::screenShotFormat $= "JPG"))
         screenShot(%name @ ".jpg", "JPEG");
         
      else if($pref::Video::screenShotFormat $= "PNG")
         screenShot(%name @ ".png", "PNG");
         
      else
         screenShot(%name @ ".png", "PNG");
   }
}

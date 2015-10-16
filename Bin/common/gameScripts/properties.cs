//
// Save config data
//
function _saveGameConfigurationData( %projectFile )
{
   %xml = new ScriptObject() { class = "XML"; };
   if( %xml.beginWrite( %projectFile ) )
   {
      %xml.writeClassBegin( "TorqueGameConfiguration" );
         %xml.writeField( "Company", $Game::CompanyName );
         %xml.writeField( "GameName", $Game::ProductName );
         %xml.writeField( "Resolution", $Game::Resolution );
         %xml.writeField( "FullScreen", $Game::FullScreen );
         %xml.writeField( "CommonVer", $Game::CommonVersion );
         //%xml.writeField( "ConsoleKey", $Game::ConsoleBind );
         %xml.writeField( "ScreenShotKey", $Game::ScreenshotBind );
         %xml.writeField( "FullscreenKey", $Game::FullscreenBind );
         %xml.writeField( "UsesNetwork", $Game::UsesNetwork );
         %xml.writeField( "UsesAudio", $Game::UsesAudio );
         %xml.writeField( "DefaultScene", $Game::DefaultScene );
      %xml.writeClassEnd();
      %xml.endWrite();
   }   
   else
   {
      error( "saveGameConfigurationData - Failed to write to file: " @ %projectFile );
      return false;
   }
   
   // Delete the object
   %xml.delete();
   
   return true;
}

//
// Load config data
//
function _loadGameConfigurationData( %projectFile )
{
   %xml = new ScriptObject() { class = "XML"; };
   if( %xml.beginRead( %projectFile ) )
   {
      if( %xml.readClassBegin( "TorqueGameConfiguration" ) )
      {
         $Game::CompanyName    = %xml.readField( "Company" );
         $Game::ProductName    = %xml.readField( "GameName" );

         $Game::Resolution     = %xml.readField( "Resolution" );
         $Game::FullScreen     = %xml.readField( "FullScreen" );

         $Game::CommonVersion  = %xml.readField( "CommonVer" );

         //$Game::ConsoleBind    = %xml.readField( "ConsoleKey" );
         $Game::ScreenshotBind = %xml.readField( "ScreenShotKey" );
         $Game::FullscreenBind = %xml.readField( "FullscreenKey" );

         $Game::UsesNetwork    = %xml.readField( "UsesNetwork" );
         $Game::UsesAudio      = %xml.readField( "UsesAudio" );

         $Game::DefaultScene   = %xml.readField( "DefaultScene" );
         %xml.readClassEnd();
      }
      else
         _defaultGameConfiguration();
         
      %xml.endRead();
   }
   else
      _defaultGameConfigurationData();
   
   // Delete the object
   %xml.delete();
   
   // set the product and game names
   setCompanyAndProduct($Game::CompanyName, $Game::ProductName);
}

//
// Load config data
//
function _defaultGameConfigurationData()
{
   $Game::CompanyName      = "Independent";
   $Game::ProductName      = "Untitled Game";
   $Game::Resolution       = "800 600 32";
   $Game::FullScreen       = "false";
   $Game::ConsoleBind      = "ctrl tilde"; // [neo, 5/24/2007 - #2986]
   $Game::ScreenshotBind   = "ctrl p";
   $Game::FullscreenBind   = "alt enter";
   $Game::UsesNetwork      = false;
   $Game::UsesAudio        = true;
   $Game::DefaultScene     = "game/data/levels/untitled.t2d";
   
}

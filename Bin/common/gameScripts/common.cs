//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------
$Game::CommonVersion = 114;

//---------------------------------------------------------------------------------------------
// initializeCommon
// Initializes common game functionality.
//---------------------------------------------------------------------------------------------
function initializeCommon()
{

   // Common keybindings.
   // GlobalActionMap doesn't get preference anymore so need special sequence to toggle console.
   // This also allows ~ to be used in the console now ;p   
   GlobalActionMap.bind(keyboard, $Game::ConsoleBind, toggleConsole);
   GlobalActionMap.bind(keyboard, $Game::ScreenshotBind, doScreenShot);
   GlobalActionMap.bindcmd(keyboard, $Game::FullscreenBind, "toggleFullScreen();","");
   
   // Very basic functions used by everyone.
   exec("./audio.cs");
   exec("./canvas.cs");
   exec("./cursor.cs");

   // Seed the random number generator.
   setRandomSeed();
   
   // Set up networking.
   if( $Game::UsesNetwork )
      setNetPort(0);
      
   // Initialize the canvas.
   initializeCanvas( $Game::ProductName );
   
   // Start up the audio system.
   if( $Game::UsesAudio )
      initializeOpenAL();
   
   // Content.
   exec("~/gui/profiles.cs");
   exec("~/gui/cursors.cs");

   // Common Guis.
   exec("~/gui/messageBoxOk.gui");
   exec("~/gui/messageBoxYesNo.gui");
   exec("~/gui/messageBoxYesNoCancel.gui");
   exec("~/gui/messageBoxOKCancel.gui");
   exec("~/gui/messageBoxOKCancelDetailsDlg.gui");
   exec("~/gui/messagePopup.gui");
   exec("~/gui/options.gui");
   exec("~/gui/remap.gui");
   exec("~/gui/console.gui");
   exec("~/gui/NetworkMenu.gui");
   exec("~/gui/startServer.gui");
   exec("~/gui/joinServer.gui");
   exec("~/gui/waitingForServer.gui");
   exec("~/gui/helpDlg.gui");
   
   // Gui Helper Scripts.
   exec("~/gui/messageBox.cs");
   exec("~/gui/help.cs");

   // Chat gui
   exec("~/gui/chatGui.gui");

   // Random Scripts.
   exec("./screenshot.cs");
   exec("./metrics.cs");
   exec("./scriptDoc.cs");
   exec("./keybindings.cs");
   exec("./options.cs");
   exec("./levelManagement.cs");
   exec("./projectManagement.cs");
   exec("./projectResources.cs");
   exec("./align.cs");

   // Load client and server scripts.
   if( $Game::UsesNetwork )
   {
      initBaseClient();
      initBaseServer();
   }
   // Set a default cursor.
   Canvas.setCursor(DefaultCursor);
   
   loadKeybindings();

   $commonInitialized = true;

}

//---------------------------------------------------------------------------------------------
// _shutdownCommon
// Shuts down common game functionality.
//---------------------------------------------------------------------------------------------
function _shutdownCommon()
{
   if(isFunction("shutdownProject"))
      shutdownProject();
      
   shutdownOpenAL();
}

//---------------------------------------------------------------------------------------------
// dumpKeybindings
// Saves of all keybindings.
//---------------------------------------------------------------------------------------------
function dumpKeybindings()
{
   // Loop through all the binds.
   for (%i = 0; %i < $keybindCount; %i++)
   {
      // If we haven't dealt with this map yet...
      if (isObject($keybindMap[%i]))
      {
         // Save and delete.
         $keybindMap[%i].save("~/prefs/bind.cs", %i == 0 ? false : true);
         $keybindMap[%i].delete();
      }
   }
}

//---------------------------------------------------------------------------------------------
// initBaseClient
// Initializes necessary client functionality.
//---------------------------------------------------------------------------------------------
function initBaseClient()
{
   // Base client scripts.
   exec("./client/client.cs");
   exec("./client/message.cs");
   exec("./client/serverConnection.cs");
   exec("./client/chatClient.cs");
}

//---------------------------------------------------------------------------------------------
// initBaseServer
// Initializes necessary server functionality.
//---------------------------------------------------------------------------------------------
function initBaseServer()
{
   // Base server scripts.
   exec("./server/server.cs");
   exec("./server/message.cs");
   exec("./server/clientConnection.cs");
   exec("./server/kickban.cs");
   exec("./server/chatServer.cs");
}

//--------------------------------------------------------------------------
// Load a Mod Directory.
//--------------------------------------------------------------------------
function loadDir( %dir )
{
   // Set Mod Paths.
   setModPaths( getModPaths() @ ";" @ %dir );
   
   // Execute Boot-strap file.
   exec( %dir @ "/main.cs" );
}


//--------------------------------------------------------------------------
// Rounds a number
//--------------------------------------------------------------------------
function mRound(%num)
{
   if((%num-mFloor(%num)) >= 0.5)
   {
      %value = mCeil(%num);
   }
   else
   {
      %value = mFloor(%num);
   }    

   return %value;
}
//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------
$currentProject = "";

function exitDemo()
{
   if($runWithEditors)
      toggleLevelEditor();
   else
      quit();
}

function _initializeProject()
{
   // Managed File Paths
   %dbFile = expandFilename("game/managed/datablocks.cs");
   %persistFile = expandFilename("game/managed/persistent.cs");
   %brushFile = expandFilename("game/managed/brushes.cs");   
   %behaviorsDirectory = expandFilename("game/behaviors");   
   %userDatablockFile = expandFilename("game/gameScripts/datablocks.cs");
   %userGUIProfileFile = expandFilename("game/gameScripts/guiProfiles.cs");

   
   //---------------------------------------------------------------------------   
   // Project Resources
   //---------------------------------------------------------------------------
   // --  This MUST be done BEFORE datablocks and persistent objects are loaded.
   %resPath = expandFileName("resources");

   // Index resources
   addResPath( %resPath );
   
   
   if( !isObject( $dependentResourceGroup ) )
      $dependentResourceGroup = new SimGroup();
   
   %resList = getDirectoryList( %resPath, 0 );
   %resCount = getFieldCount( %resList );

   for( %i = 0; %i < %resCount; %i++ )
   {
      %resName = getField( %resList, %i );
      %resFile = %resPath @ "/" @ %resName;
      
      %resObject = ResourceObject::load( %resFile );
      if( !isObject( %resObject ) )
      {
         error(" % Game Resources : FAILED Loading Resource" SPC %resName );
         continue;
      }
      else
         echo(" % Game Resources : Loaded Resource" SPC %resName);
         
      // Create a dependentResourcegroup object
      %entry = new ScriptObject() { Name = %resName; };
      $dependentResourceGroup.add( %entry );
   }

   //---------------------------------------------------------------------------
   // Managed Datablocks
   //---------------------------------------------------------------------------
   if ( isFile( %dbFile ) || isFile( %dbFile @ ".dso" ) )
      exec( %dbFile );
     
   if( !isObject( $managedDatablockSet ) )   
      $managedDatablockSet = new SimSet();

   //---------------------------------------------------------------------------
   // Managed Persistent Objects
   //---------------------------------------------------------------------------
   if ( isFile( %persistFile ) || isFile( %persistFile @ ".dso" ) )
      exec( %persistFile );

   if( !isObject( $persistentObjectSet ) )   
      $persistentObjectSet = new SimSet();
      
   //---------------------------------------------------------------------------
   // Managed Brushes
   //---------------------------------------------------------------------------
   if ( isFile( %brushFile ) || isFile( %brushFile @ ".dso" ) )
      exec( %brushFile );
   
   if( !isObject( $brushSet ) )   
      $brushSet = new SimSet();

   //---------------------------------------------------------------------------
   // User Defined Datablocks
   //---------------------------------------------------------------------------
   addResPath( %userDatablockFile );   
   if( isFile( %userDatablockFile ) )
      exec( %userDatablockFile );
      
   //---------------------------------------------------------------------------
   // Behaviors
   //---------------------------------------------------------------------------
   addResPath(%behaviorsDirectory);
   
   // Compile all the cs files.
   %behaviorsSpec = %behaviorsDirectory @ "/*.cs";
   for (%file = findFirstFile(%behaviorsSpec); %file !$= ""; %file = findNextFile(%behaviorsSpec))
      compile(%file);
   
   // And exec all the dsos.
   %behaviorsSpec = %behaviorsDirectory @ "/*.cs.dso";
   for (%file = findFirstFile(%behaviorsSpec); %file !$= ""; %file = findNextFile(%behaviorsSpec))
      exec(strreplace(%file, ".cs.dso", ".cs"));

   //---------------------------------------------------------------------------
   // User Defined GUI Profiles
   //---------------------------------------------------------------------------
   addResPath( %userGUIProfileFile );   
   if( isFile( %userGUIProfileFile ) )
      exec( %userGUIProfileFile );
}

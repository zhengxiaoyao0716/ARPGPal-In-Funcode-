//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

// This holds the last scenegraph that was loaded.
$lastLoadedScene = "";
function getLastLoadedScene()
{
   return $lastLoadedScene;
}

// This variable determines whether the scenegraph in the level file or the existing scenegraph
// should be used.
$useNewSceneGraph = false;
//---------------------------------------------------------------------------------------------
// t2dSceneWindow.loadLevel
// Loads a level file into a scene window.
//---------------------------------------------------------------------------------------------
function t2dSceneWindow::loadLevel(%sceneWindow, %levelFile)
{
   // Clean up any previously loaded stuff.
   %sceneWindow.endLevel();
   
   // Load the level.
   $useNewSceneGraph = true;
   %scenegraph = %sceneWindow.addToLevel(%levelFile);
   
   if (!isObject(%scenegraph))
      return 0;
   
   %sceneWindow.setSceneGraph(%scenegraph);
   
   // Set the window properties from the scene graph if they are available.
   %cameraPosition = %sceneWindow.getCurrentCameraPosition();
   %cameraSize = t2dVectorSub(getWords(%sceneWindow.getCurrentCameraArea(), 2, 3),
                              getWords(%sceneWindow.getCurrentCameraArea(), 0, 1));
                              
   if (%scenegraph.cameraPosition !$= "")
      %cameraPosition = %scenegraph.cameraPosition;
   if (%scenegraph.cameraSize !$= "")
      %cameraSize = %scenegraph.cameraSize;
      
   %sceneWindow.setCurrentCameraPosition(%cameraPosition, %cameraSize);
   
   // Only perform "onLevelLoaded" callbacks when we're NOT editing a level
   //
   //  This is so that objects that may have script associated with them that
   //  the level builder cannot undo will not be executed while using the tool.
   //
          
   if (!$LevelEditorActive)
   {
      // Notify the scenegraph that it was loaded.
      if( %scenegraph.isMethod( "onLevelLoaded" ) )
         %scenegraph.onLevelLoaded();
      
      // And finally, notify all the objects that they were loaded.
      %sceneObjectList = %scenegraph.getSceneObjectList();
      %sceneObjectCount = getWordCount(%sceneObjectList);
      for (%i = 0; %i < %sceneObjectCount; %i++)
      {
         %sceneObject = getWord(%sceneObjectList, %i);
         //if( %sceneObject.isMethod( "onLevelLoaded" ) )
            %sceneObject.onLevelLoaded(%scenegraph);
      }
   }
   
   $lastLoadedScene = %scenegraph;
   return %scenegraph;
}

//---------------------------------------------------------------------------------------------
// t2dSceneWindow.addToLevel
// Adds a level file to a scene window's scenegraph.
//---------------------------------------------------------------------------------------------
function t2dSceneWindow::addToLevel(%sceneWindow, %levelFile)
{
   %scenegraph = %sceneWindow.getSceneGraph();
   if (!isObject(%scenegraph))
   {
      %scenegraph = new t2dSceneGraph();
      %sceneWindow.setSceneGraph(%scenegraph);
   }
   
   %newScenegraph = %scenegraph.addToLevel(%levelFile);
   
   $lastLoadedScene = %newScenegraph;
   return %newScenegraph;
}

//---------------------------------------------------------------------------------------------
// t2dSceneGraph.addToLevel
// Loads a level file into a scenegraph.
//---------------------------------------------------------------------------------------------
function t2dSceneGraph::loadLevel(%sceneGraph, %levelFile)
{
   %sceneGraph.endLevel();
   %newScenegraph = %sceneGraph.addToLevel(%levelFile);
   
   if (isObject(%newScenegraph) && !$LevelEditorActive)
   {
      // Notify the scenegraph that it was loaded.
      if( %newScenegraph.isMethod( "onLevelLoaded" ) )
         %newScenegraph.onLevelLoaded();
      
      // And finally, notify all the objects that they were loaded.
      %sceneObjectList = %newScenegraph.getSceneObjectList();
      %sceneObjectCount = getWordCount(%sceneObjectList);
      for (%i = 0; %i < %sceneObjectCount; %i++)
      {
         %sceneObject = getWord(%sceneObjectList, %i);
         //if( %sceneObject.isMethod( "onLevelLoaded" ) )
            %sceneObject.onLevelLoaded(%newScenegraph);
      }
   }
   
   $lastLoadedScene = %newScenegraph;
   return %newScenegraph;
}

//---------------------------------------------------------------------------------------------
// t2dSceneGraph.addToLevel
// Adds a level file to a scenegraph.
//---------------------------------------------------------------------------------------------
function t2dSceneGraph::addToLevel(%scenegraph, %levelFile)
{
   // Reset this. It should always be false unless we are loading into a scenewindow.
   %useNewSceneGraph = $useNewSceneGraph;
   $useNewSceneGraph = false;
   
   // Prevent name clashes when loading a scenegraph with the same name as this one
   %scenegraph = %scenegraph.getId();
   
   // Make sure the file is valid.
   if ((!isFile(%levelFile)) && (!isFile(%levelFile @ ".dso")))
   {
      error("Error loading level " @ %levelFile @ ". Invalid file.");
      return 0;
   }
   
   // Load up the level.
   exec(%levelFile);
   
   // The level file should have contained a scenegraph, which should now be in the instant
   // group. And, it should be the only thing in the group.
   if (!isObject(%levelContent))
   {
      error("Invalid level file specified: " @ %levelFile);
      return 0;
   }
   
   %newScenegraph = %scenegraph;
   %object = %levelContent;
   $LevelManagement::newObjects = "";
   
   if (%object.getClassName() $= "t2dSceneObjectGroup")
   {
      %newScenegraph.addToScene(%object);
      for (%i = 0; %i < %object.getCount(); %i++)
      {
         %obj = %object.getObject(%i);
         if (%obj.getClassName() $= "t2dParticleEffect")
         {
            %newScenegraph.addToScene(%obj);
            %oldPosition = %obj.getPosition();
            %oldSize = %obj.getSize();
            %obj.loadEffect(%obj.effectFile);
            %obj.setPosition(%oldPosition);
            %obj.setSize(%oldSize);
            %obj.playEffect();
         }
         
         else if (%obj.getClassName() $= "t2dTileLayer")
         {
            %oldPosition = %obj.getPosition();
            %oldSize = %obj.getSize();
            %tileMap = %newScenegraph.getGlobalTileMap();
            if (isObject(%tileMap))
            {
               %tileMap.addTileLayer(%obj);
               %obj.loadTileLayer(%obj.layerFile);
               %obj.setPosition(%oldPosition);
               %obj.setSize(%oldSize);
            }
            else
               error("Unable to find scene graph's global tile map.");
         }
      }
      $LevelManagement::newObjects = %object;
   }
   
   else if( %object.getClassName() $= "t2dSceneObjectSet" )
   {
      // Add each object in the set to the scene.
      for (%i = 0; %i < %object.getCount(); %i++)
      {
         %obj = %object.getObject(%i);
         %newScenegraph.addToScene( %obj );
         if (%obj.getClassName() $= "t2dParticleEffect")
         {
            %oldPosition = %obj.getPosition();
            %oldSize = %obj.getSize();
            %obj.loadEffect(%obj.effectFile);
            %obj.setPosition(%oldPosition);
            %obj.setSize(%oldSize);
            %obj.playEffect();
         }
         
         else if (%obj.getClassName() $= "t2dTileLayer")
         {
            %oldPosition = %obj.getPosition();
            %oldSize = %obj.getSize();
            %tileMap = %newScenegraph.getGlobalTileMap();
            if (isObject(%tileMap))
            {
               %tileMap.addTileLayer(%obj);
               %obj.loadTileLayer(%obj.layerFile);
               %obj.setPosition(%oldPosition);
               %obj.setSize(%oldSize);
            }
            else
               error("Unable to find scene graph's global tile map.");
         }
      }
      $LevelManagement::newObjects = %object;
   }
   
   else if (%object.isMemberOfClass("t2dSceneObject"))
   {
      if (%object.getClassName() $= "t2dParticleEffect")
      {
         %newScenegraph.addToScene(%object);
         %oldPosition = %object.getPosition();
         %oldSize = %object.getSize();
         %object.loadEffect(%object.effectFile);
         %object.setPosition(%oldPosition);
         %object.setSize(%oldSize);
         %object.playEffect();
      }
      
      else if (%object.getClassName() $= "t2dTileLayer")
      {
         %oldPosition = %object.getPosition();
         %oldSize = %object.getSize();
         %tileMap = %newScenegraph.getGlobalTileMap();
         if (isObject(%tileMap))
         {
            %tileMap.addTileLayer(%object);
            %object.loadTileLayer(%object.layerFile);
            %object.setPosition(%oldPosition);
            %object.setSize(%oldSize);
         }
         else
            error("Unable to find scene graph's global tile map.");
      }
      else
         %newScenegraph.addToScene(%object);
      
      $LevelManagement::newObjects = %object;
   }

   // If we got a scenegraph...
   else if (%object.getClassName() $= "t2dSceneGraph")
   {
      %fromSceneGraph = 0;
      %toSceneGraph = 0;
      
      // If we are supposed to use the new scenegraph, we need to copy from the existing scene
      // graph to the new one. Otherwise, we copy the loaded stuff into the existing one.
      if (%useNewSceneGraph)
      {
         %fromSceneGraph = %newScenegraph;
         %toSceneGraph = %object;
      }
      else
      {
         %fromSceneGraph = %object;
         %toSceneGraph = %newScenegraph;
      }

      if (isObject(%fromSceneGraph.getGlobalTileMap()))
         %fromSceneGraph.getGlobalTileMap().delete();

      // If the existing scenegraph has objects in it, then the new stuff should probably be
      // organized nicely in its own group.
      if ((%toSceneGraph.getCount() > 0) && (%fromSceneGraph.getCount() > 0))
      {
         %newGroup = new t2dSceneObjectGroup();
      
         while (%fromSceneGraph.getCount() > 0)
         {
            %obj = %fromSceneGraph.getObject(0);
            %fromSceneGraph.removeFromScene(%obj);
            %obj.setPosition(%obj.getPosition()); // This sets physics.dirty.... =)
            %newGroup.add(%obj);
         }
         
         %toSceneGraph.add(%newGroup);
         $LevelManagement::newObjects = %newGroup;
      }
      else
      // if it does not then simply move the objects over
      {
         while (%fromSceneGraph.getCount() > 0)
         {
            %obj = %fromSceneGraph.getObject(0);
            %fromSceneGraph.removeFromScene(%obj);
            %obj.setPosition(%obj.getPosition()); // This sets physics.dirty.... =)
            %toSceneGraph.addToScene(%obj);
         }
         $LevelManagement::newObjects = %toSceneGraph;
      }
      
      %newScenegraph = %toSceneGraph;
      %fromSceneGraph.delete();
   }
   
   // Unsupported object type.
   else
   {
      error("Error loading level " @ %levelFile @ ". " @ %object.getClassName() @
            " is not a valid level object type.");
      return 0;
   }
   
   if( isObject( $persistentObjectSet ) )
   {
      // Now we need to move all the persistent objects into the scene.
      %count = $persistentObjectSet.getCount();
      for (%i = 0; %i < %count; %i++)
      {
         %object = $persistentObjectSet.getObject(%i);
         %sg = %object.getSceneGraph();
         if(%sg)
            %sg.removeFromScene(%object);
            
         %newScenegraph.addToScene(%object);
         %object.setPosition( %object.getPosition() );
      }
   }
   
   // And finally, perform any post creation actions
   %newScenegraph.performPostInit();
   
   $lastLoadedScene = %newScenegraph;
   return %newScenegraph;
}

//---------------------------------------------------------------------------------------------
// t2dSceneWindow.endLevel
// Clears a scene window.
//---------------------------------------------------------------------------------------------
function t2dSceneWindow::endLevel(%sceneWindow)
{
   %scenegraph = %sceneWindow.getSceneGraph();
   
   if (!isObject(%scenegraph))
      return;
   
   %scenegraph.endLevel();
   
   if (isObject(%scenegraph))
   {
      if( isObject( %scenegraph.getGlobalTileMap() ) )
         %scenegraph.getGlobalTileMap().delete();
         
      %scenegraph.delete();
   }
   
   $lastLoadedScene = "";
}

//---------------------------------------------------------------------------------------------
// t2dSceneGraph.endLevel
// Clears a scenegraph.
//---------------------------------------------------------------------------------------------
function t2dSceneGraph::endLevel(%sceneGraph)
{
   if (!$LevelEditorActive)
   {
      %sceneObjectList = %sceneGraph.getSceneObjectList();
      // And finally, notify all the objects that they were loaded.
      for (%i = 0; %i < getWordCount(%sceneObjectList); %i++)
      {
         %sceneObject = getWord(%sceneObjectList, %i);
         //if( %sceneObject.isMethod( "onLevelEnded" ) )
            %sceneObject.onLevelEnded(%sceneGraph);
      }
      
      // Notify the scenegraph that the level ended.
      if( %sceneGraph.isMethod( "onLevelEnded" ) )
         %sceneGraph.onLevelEnded();
   }
      
   if( isObject( $persistentObjectSet ) )
   {
      %count = $persistentObjectSet.getCount();
      for (%i = 0; %i < %count; %i++)
      {
         %object = $persistentObjectSet.getObject(%i);
         %scenegraph.removeFromScene(%object);
      }
   }
   
   %globalTileMap = %sceneGraph.getGlobalTileMap();
   if (isObject(%globalTileMap))
      %sceneGraph.removeFromScene(%globalTileMap);
   
   %scenegraph.clearScene(true);
   
   if (isObject(%globalTileMap))
      %sceneGraph.addToScene(%globalTileMap);
      
   $lastLoadedScene = "";
}

function t2dSceneObject::onLevelLoaded(%this, %scenegraph)
{
}

function t2dSceneObject::onLevelEnded(%this, %scenegraph)
{
}

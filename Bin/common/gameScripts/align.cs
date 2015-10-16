//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

$AlignTools::Horizontal = 0;
$AlignTools::Vertical = 1;

$AlignTools::Left = -1;
$AlignTools::Right = 1;
$AlignTools::Top = -1;
$AlignTools::Bottom = 1;
$AlignTools::Center = 0;

function AlignTools::sort( %objects, %side, %dir )
{
   // Set the sort position for each object.
   %count = %objects.getCount();
   for( %i = 0; %i < %count; %i++ )
   {
      %object = %objects.getObject( %i );
      %position = getWord( %object.getPosition(), %dir );
      %halfSize = getWord( %object.getSize(), %dir ) * 0.5;
      %object.sortPos = %position + ( %halfSize * %side );
   }
   
   // Selection sort by sortPos.
   for( %i = 0; %i < %count - 1; %i++ )
   {
      %min = %i;
      for( %j = %i + 1; %j < %count; %j++ )
      {
         %objMin = %objects.getObject( %min );
         %obj = %objects.getObject( %j );
         if( %obj.sortPos < %objMin.sortPos )
            %min = %j;
      }
      %objMin = %objects.getObject( %min );
      %obj = %objects.getObject( %i );
      %objects.reorderChild( %objMin, %obj );
   }
}

function AlignTools::deleteSorted( %objects )
{
   // Clear the sortPos field.
   %count = %objects.getCount();
   for( %i = 0; %i < %count; %i++ )
   {
      %object = %objects.getObject( %i );
      %object.sortPos = "";
   }
}

function AlignTools::align( %objects, %side, %dir )
{
   %objectPos = getWord( %objects.getPosition(), %dir );
   %halfSize = getWord( %objects.getSize(), %dir ) * 0.5;
   
   %alignPos = %objectPos + ( %halfSize * %side );
   AlignTools::alignToPosition( %objects, %side, %dir, %alignPos );
}

function AlignTools::alignToCamera( %objects, %scenegraph, %side, %dir )
{
   %camPos = getWord( %scenegraph.cameraPosition, %dir );
   %camHalfSize = getWord( %scenegraph.cameraSize, %dir ) * 0.5;
   
   %alignPos = %camPos + ( %camHalfSize * %side );
   AlignTools::alignToPosition( %objects, %side, %dir, %alignPos );
}

function AlignTools::alignToPosition( %objects, %side, %dir, %alignPos )
{
   %count = %objects.getCount();
   for( %i = 0; %i < %count; %i++ )
   {
      %object = %objects.getObject( %i );
      %position = %object.getPosition();
      %halfSize = getWord( %object.getSize(), %dir ) * 0.5;
      %newPosition = %alignPos + ( %halfSize * -%side );
      %position = setWord( %position, %dir, %newPosition );
      %object.setPosition( %position );
   }
}

function AlignTools::distribute( %objects, %side, %dir )
{
   %count = %objects.getCount();
   if( %count < 1 )
      return;
      
   %alignLeftPos = %objects.getObject( 0 ).sortPos;
   %alignRightPos = %objects.getObject( %count - 1 ).sortPos;
   
   %spacing = ( %alignRightPos - %alignLeftPos ) / ( %count - 1 );
   AlignTools::distributeToSpacing( %objects, %side, %dir, %spacing );
}

function AlignTools::distributeToCamera( %objects, %scenegraph, %side, %dir )
{
   %count = %objects.getCount();
   if( %count < 2 )
      return;
      
   // Grab the camera bounds.
   %camPos = getWord( %scenegraph.cameraPosition, %dir );
   %camHalfSize = getWord( %scenegraph.cameraSize, %dir ) * 0.5;
   
   %leftCam = %camPos - %camHalfSize;
   %rightCam = %camPos + %camHalfSize;
   
   // Set the left/top most object to the left/top of the camera.
   %firstObj = %objects.getObject( 0 );
   %firstPos = getWord( %firstObj.position, %dir );
   %firstHalfSize = getWord( %firstObj.size, %dir ) * 0.5;
   %firstNewPos = %leftCam + %firstHalfSize;
   %diff = %firstNewPos - %firstPos;
   %firstObj.position = setWord( %firstObj.position, %dir, %firstNewPos );
   %firstObj.sortPos += %diff;
   
   // Set the right/bottom most object to the right/bottom of the camera.
   %lastObj = %objects.getObject( %count - 1 );
   %lastPos = getWord( %lastObj.position, %dir );
   %lastHalfSize = getWord( %lastObj.size, %dir ) * 0.5;
   %lastNewPos = %rightCam - %lastHalfSize;
   %diff = %lastNewPos - %lastPos;
   %lastObj.position = setWord( %lastObj.position, %dir, %lastNewPos );
   %lastObj.sortPos += %diff;
   
   %spacing = ( %lastObj.sortPos - %firstObj.sortPos ) / ( %count - 1 );
   AlignTools::distributeToSpacing( %objects, %side, %dir, %spacing );
}

function AlignTools::distributeToSpacing( %objects, %side, %dir, %spacing )
{
   %count = %objects.getCount();
   for( %i = 1; %i < %count - 1; %i++ )
   {
      %prevObject = %objects.getObject( %i - 1 );
      %object = %objects.getObject( %i );
      
      %space = %object.sortPos - %prevObject.sortPos;
      %diff = %spacing - %space;
      %newPos = getWord( %object.position, %dir ) + %diff;
      %object.position = setWord( %object.position, %dir, %newPos );
      %object.sortPos += %diff;
   }
}

function AlignTools::matchSize( %objects, %dir )
{
   if( %dir == 2 )
   {
      AlignTools::matchSize( %objects, 0 );
      AlignTools::matchSize( %objects, 1 );
      return;
   }
   
   // Find the biggest object.
   %count = %objects.getCount();
   for( %i = 0; %i < %count; %i++ )
   {
      %object = %objects.getObject( %i );
      %newSize = getWord( %object.size, %dir );
      if( ( %biggest $= "" ) || ( %newSize > %biggest ) )
         %biggest = %newSize;
   }
   
   AlignTools::matchSizeToAmount( %objects, %dir, %biggest );
}

function AlignTools::matchSizeToCamera( %objects, %scenegraph, %dir )
{
   if( %dir == 2 )
   {
      AlignTools::matchSizeToCamera( %objects, %scenegraph, 0 );
      AlignTools::matchSizeToCamera( %objects, %scenegraph, 1 );
      return;
   }
   
   %size = getWord( %scenegraph.cameraSize, %dir );
   AlignTools::matchSizeToAmount( %objects, %dir, %size );
}

function AlignTools::matchSizeToAmount( %objects, %dir, %size )
{
   %count = %objects.getCount();
   for( %i = 0; %i < %count; %i++ )
   {
      %object = %objects.getObject( %i );
      %object.size = setWord( %object.size, %dir, %size );
   }
}

function AlignTools::space( %objects, %dir )
{
   %count = %objects.getCount();
   if( %count < 2 )
      return;
      
   // Total space is the entire amount of space taken up.
   %firstObject = %objects.getObject( 0 );
   %left = getWord( %firstObject.position, %dir ) - ( getWord( %firstObject.size, %dir ) * 0.5 );
   
   %lastObject = %objects.getObject( %count - 1 );
   %right = getWord( %lastObject.position, %dir ) + ( getWord( %lastObject.size, %dir ) * 0.5 );
   
   %totalSpace = %right - %left;
   
   // Occupied space is the amount of space taken up by the objects.
   %occupiedSpace = 0;
   for( %i = 0; %i < %count; %i++ )
   {
      %object = %objects.getObject( %i );
      %space = getWord( %object.size, %dir );
      %occupiedSpace += %space;
   }
   
   // Spacing is the amount of space to put between each object.
   %spacing = ( %totalSpace - %occupiedSpace ) / ( %count - 1 );
   AlignTools::spaceToAmount( %objects, %dir, %spacing );
}

function AlignTools::spaceToCamera( %objects, %scenegraph, %dir )
{
   %count = %objects.getCount();
   if( %count < 2 )
      return;
      
   // Grab the camera bounds.
   %camPos = getWord( %scenegraph.cameraPosition, %dir );
   %camHalfSize = getWord( %scenegraph.cameraSize, %dir ) * 0.5;
   
   %leftCam = %camPos - %camHalfSize;
   %rightCam = %camPos + %camHalfSize;
   
   // Set the left/top most object to the left/top of the camera.
   %firstObj = %objects.getObject( 0 );
   %firstPos = getWord( %firstObj.position, %dir );
   %firstHalfSize = getWord( %firstObj.size, %dir ) * 0.5;
   %firstNewPos = %leftCam + %firstHalfSize;
   %diff = %firstNewPos - %firstPos;
   %firstObj.position = setWord( %firstObj.position, %dir, %firstNewPos );
   %firstObj.sortPos += %diff;
   
   // Set the right/bottom most object to the right/bottom of the camera.
   %lastObj = %objects.getObject( %count - 1 );
   %lastPos = getWord( %lastObj.position, %dir );
   %lastHalfSize = getWord( %lastObj.size, %dir ) * 0.5;
   %lastNewPos = %rightCam - %lastHalfSize;
   %diff = %lastNewPos - %lastPos;
   %lastObj.position = setWord( %lastObj.position, %dir, %lastNewPos );
   %lastObj.sortPos += %diff;
   
   %totalSpace = %rightCam - %leftCam;
   
   // Occupied space is the amount of space taken up by the objects.
   %occupiedSpace = 0;
   for( %i = 0; %i < %count; %i++ )
   {
      %object = %objects.getObject( %i );
      %space = getWord( %object.size, %dir );
      %occupiedSpace += %space;
   }
   
   // Spacing is the amount of space to put between each object.
   %spacing = ( %totalSpace - %occupiedSpace ) / ( %count - 1 );
   AlignTools::spaceToAmount( %objects, %dir, %spacing );
}

function AlignTools::spaceToAmount( %objects, %dir, %spacing )
{
   %count = %objects.getCount();
   for( %i = 1; %i < %count - 1; %i++ )
   {
      %prevObject = %objects.getObject( %i - 1 );
      %object = %objects.getObject( %i );
      
      %pos = getWord( %prevObject.position, %dir );
      %pos += getWord( %prevObject.size, %dir ) * 0.5;
      %pos += %spacing;
      %pos += getWord( %object.size, %dir ) * 0.5;
      %object.position = setWord( %object.position, %dir, %pos );
   }
}

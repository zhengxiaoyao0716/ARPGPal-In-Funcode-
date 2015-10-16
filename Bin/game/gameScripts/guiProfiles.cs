//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------
//
// This is the file you should define your custom gui profiles that are to be used
// in the editor.
//

if(!isObject(ExampleWindowProfile)) new GuiControlProfile(ExampleWindowProfile)
{
   opaque = true;
   border = 1;
   fillColor = "211 211 211";
   fillColorHL = "190 255 255";
   fillColorNA = "255 255 255";
   fontColor = "0 0 0";
   fontColorHL = "200 200 200";
   text = "untitled";
   bitmap = "common/gui/images/window";
   textOffset = "5 5";
   hasBitmapArray = true;
   justify = "center";
};

if(!isObject(ExampleScrollProfile)) new GuiControlProfile (ExampleScrollProfile)
{
   opaque = true;
   fillColor = "255 255 255";
   border = 1;
   borderThickness = 2;
   bitmap = "common/gui/images/scrollBar";
   hasBitmapArray = true;
};

if(!isObject(ExampleButtonProfile)) new GuiControlProfile(ExampleButtonProfile)
{
   opaque = true;
   border = -1;
   fontColor = "0 0 0";
   fontColorHL = "32 100 100";
   fixedExtent = true;
   justify = "center";
   canKeyFocus = false;
   bitmap = "common/gui/images/button";
};

if(!isObject(ExampleTextProfile)) new GuiControlProfile(ExampleTextProfile)
{
   fontType = "Arial";
   fontSize = 16;
   fontColor = "0 0 0";
};

//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

$Gui::fontCacheDirectory = expandFilename("~/data/fonts");

//---------------------------------------------------------------------------------------------
// GuiDefaultProfile is a special profile that all other profiles inherit defaults from. It
// must exist.
//---------------------------------------------------------------------------------------------
if(!isObject(GuiDefaultProfile)) new GuiControlProfile (GuiDefaultProfile)
{
   tab = false;
   canKeyFocus = false;
   hasBitmapArray = false;
   mouseOverSelected = false;

   // fill color
   opaque = false;
   fillColor = "211 211 211";
   fillColorHL = "244 244 244";
   fillColorNA = "244 244 244";

   // border color
   border = 1;
   borderColor   = "40 40 40 100";
   borderColorHL = "128 128 128";
   borderColorNA = "64 64 64";

   // font
   fontType = "Arial";
   fontSize = 14;

   fontColor = "0 0 0";
   fontColorHL = "32 100 100";
   fontColorNA = "0 0 0";
   fontColorSEL= "200 200 200";

   // bitmap information
   bitmap = "./images/window";
   bitmapBase = "";
   textOffset = "0 0";

   // used by guiTextControl
   modal = true;
   justify = "left";
   autoSizeWidth = false;
   autoSizeHeight = false;
   returnTab = false;
   numbersOnly = false;
   cursorColor = "0 0 0 255";

   // sounds
   soundButtonDown = "";
   soundButtonOver = "";
};

if(!isObject(GuiSolidDefaultProfile)) new GuiControlProfile (GuiSolidDefaultProfile)
{
   opaque = true;
   border = true;
};

if(!isObject(GuiTransparentProfile)) new GuiControlProfile (GuiTransparentProfile)
{
   opaque = false;
   border = false;
};


if(!isObject(GuiToolTipProfile)) new GuiControlProfile (GuiToolTipProfile)
{
   // fill color
   fillColor = "239 237 222";

   // border color
   borderColor   = "138 134 122";

   // font
   fontType = "Arial";
   fontSize = 14;
   fontColor = "0 0 0";

};

if(!isObject(GuiModelessDialogProfile)) new GuiControlProfile("GuiModelessDialogProfile")
{
   modal = false;
};

if(!isObject(GuiFrameSetProfile)) new GuiControlProfile (GuiFrameSetProfile)
{
   fillColor = "239 237 222";
   borderColor   = "138 134 122";
   opaque = true;
   border = true;
};


if(!isObject(GuiWindowProfile)) new GuiControlProfile (GuiWindowProfile)
{
   opaque = true;
   border = 1;
   fillColor = "211 211 211";
   fillColorHL = "190 255 255";
   fillColorNA = "255 255 255";
   fontColor = "0 0 0";
   fontColorHL = "200 200 200";
   text = "untitled";
   bitmap = "./images/window";
   textOffset = "5 5";
   hasBitmapArray = true;
   justify = "center";
};

if(!isObject(GuiContentProfile)) new GuiControlProfile (GuiContentProfile)
{
   opaque = true;
   fillColor = "255 255 255";
};

if(!isObject(GuiBlackContentProfile)) new GuiControlProfile (GuiBlackContentProfile)
{
   opaque = true;
   fillColor = "0 0 0";
};

if(!isObject(GuiInputCtrlProfile)) new GuiControlProfile( GuiInputCtrlProfile )
{
   tab = true;
   canKeyFocus = true;
};

if(!isObject(GuiTextProfile)) new GuiControlProfile (GuiTextProfile)
{
   fontColor = "0 0 0";
};

if(!isObject(GuiMediumTextProfile)) new GuiControlProfile (GuiMediumTextProfile : GuiTextProfile)
{
   fontSize = 24;
};

if(!isObject(GuiBigTextProfile)) new GuiControlProfile (GuiBigTextProfile : GuiTextProfile)
{
   fontSize = 36;
};

if(!isObject(GuiMLTextProfile)) new GuiControlProfile ("GuiMLTextProfile")
{
   fontColorLink = "255 96 96";
   fontColorLinkHL = "0 0 255";
   autoSizeWidth = true;
   autoSizeHeight = true;  
   border = false;
};

if(!isObject(GuiTextArrayProfile)) new GuiControlProfile (GuiTextArrayProfile : GuiTextProfile)
{
   fontColorHL = "32 100 100";
   fillColorHL = "200 200 200";
};

if(!isObject(GuiTextListProfile)) new GuiControlProfile (GuiTextListProfile : GuiTextProfile) 
{
   tab = true;
   canKeyFocus = true;
};

if(!isObject(GuiTextEditProfile)) new GuiControlProfile (GuiTextEditProfile)
{
   opaque = true;
   fillColor = "255 255 255";
   fillColorHL = "128 128 128";
   border = -2;
   bitmap = "./images/textEdit";
   borderColor = "40 40 40 100";
   fontColor = "0 0 0";
   fontColorHL = "255 255 255";
   fontColorNA = "128 128 128";
   textOffset = "4 2";
   autoSizeWidth = false;
   autoSizeHeight = true;
   tab = true;
   canKeyFocus = true;
   
};

if(!isObject(GuiProgressProfile)) new GuiControlProfile ("GuiProgressProfile")
{
   opaque = false;
   fillColor = "44 152 162 100";
   border = true;
   borderColor   = "78 88 120";
};

if(!isObject(GuiProgressTextProfile)) new GuiControlProfile ("GuiProgressTextProfile")
{
   fontColor = "0 0 0";
   justify = "center";
};

if(!isObject(GuiButtonProfile)) new GuiControlProfile (GuiButtonProfile)
{
   opaque = true;
   border = -1;
   fontColor = "0 0 0";
   fontColorHL = "32 100 100";
   fixedExtent = true;
   justify = "center";
   canKeyFocus = false;
   bitmap = "./images/button";
};

if(!isObject(GuiCheckBoxProfile)) new GuiControlProfile (GuiCheckBoxProfile)
{
   opaque = false;
   fillColor = "232 232 232";
   border = false;
   borderColor = "0 0 0";
   fontSize = 14;
   fontColor = "0 0 0";
   fontColorHL = "32 100 100";
   fixedExtent = true;
   justify = "left";
   bitmap = "./images/checkBox";
   hasBitmapArray = true;
};

if(!isObject(GuiRadioProfile)) new GuiControlProfile (GuiRadioProfile)
{
   fontSize = 14;
   fillColor = "232 232 232";
   fontColorHL = "32 100 100";
   fixedExtent = true;
   bitmap = "./images/radioButton";
   hasBitmapArray = true;
};

if(!isObject(GuiScrollProfile)) new GuiControlProfile (GuiScrollProfile)
{
   opaque = true;
   fillColor = "255 255 255";
   border = 1;
   borderThickness = 2;
   bitmap = "./images/scrollBar";
   hasBitmapArray = true;
};

if(!isObject(GuiTransparentScrollProfile)) new GuiControlProfile (GuiTransparentScrollProfile)
{
   opaque = false;
   fillColor = "255 255 255";
   border = false;
   borderThickness = 2;
   borderColor = "0 0 0";
   bitmap = "./images/scrollBar";
   hasBitmapArray = true;
};
 
if(!isObject(GuiSliderProfile)) new GuiControlProfile (GuiSliderProfile)
{
   bitmap = "./images/slider";
};

if(!isObject(GuiPaneProfile)) new GuiControlProfile(GuiPaneProfile)
{
   bitmap = "./images/popupMenu";
   hasBitmapArray = true;
};



if(!isObject(GuiPopupMenuItemBorder)) new GuiControlProfile ( GuiPopupMenuItemBorder : GuiButtonProfile )
{
   borderColor = "51 51 53 200";
   borderColorHL = "51 51 53 200";

};
if(!isObject(GuiPopUpMenu)) new GuiControlProfile (GuiPopUpMenuDefault : GuiDefaultProfile )
{
   opaque = true;
   mouseOverSelected = true;
   textOffset = "3 3";
   border = 4;
   borderThickness = 2;
   fixedExtent = true;
   bitmap = "./images/scrollBar";
   hasBitmapArray = true;
   profileForChildren = GuiPopupMenuItemBorder;
   fillColor = "255 255 255 200";
   fontColorHL = "128 128 128";
   borderColor = "151 151 153 175";
   borderColorHL = "151 151 153 175";

};


if(!isObject(GuiPopUpMenuProfile)) new GuiControlProfile (GuiPopUpMenuProfile : GuiPopUpMenuDefault)
{
   textOffset         = "6 3";
   bitmap             = "./images/dropDown";
   hasBitmapArray     = true;
   border             = -3;
   profileForChildren = GuiPopUpMenuDefault;
};

if(!isObject(GuiPopUpMenuEditProfile)) new GuiControlProfile (GuiPopUpMenuEditProfile : GuiPopUpMenuDefault)
{
   textOffset         = "6 3";
   canKeyFocus        = true;
   bitmap             = "./images/dropDown";
   hasBitmapArray     = true;
   border             = -3;
   profileForChildren = GuiPopUpMenuDefault;
};

if(!isObject(GuiListBoxProfile)) new GuiControlProfile (GuiListBoxProfile)
{
   tab = true;
   canKeyFocus = true;
};

if(!isObject(GuiTabBookProfile)) new GuiControlProfile (GuiTabBookProfile)
{
   fillColor = "255 255 255";
   fillColorHL = "64 150 150";
   fillColorNA = "150 150 150";
   fontColor = "30 30 30";
   fontColorHL = "32 100 100";
   fontColorNA = "0 0 0";
   fontType = "Arial Bold";
   fontSize = 14;
   justify = "center";
   bitmap = "./images/tab";
   tabWidth = 64;
   tabHeight = 24;
   tabPosition = "Top";
   tabRotation = "Horizontal";
   textOffset = "0 -2";
   tab = true;
   cankeyfocus = true;
};
if(!isObject(GuiTabPageProfile)) new GuiControlProfile (GuiTabPageProfile : GuiTransparentProfile )
{
   fillColor = "255 255 255";
   opaque = true;
};

if(!isObject(GuiMenuBarProfile)) new GuiControlProfile (GuiMenuBarProfile)
{
   fontType = "Arial";
   fontSize = 15;
   opaque = true;
   fillColor = "239 237 222";
   fillColorHL = "102 153 204";
   borderColor = "138 134 122";
   borderColorHL = "0 51 153";
   border = 5;
   fontColor = "0 0 0";
   fontColorHL = "255 255 255";
   fontColorNA = "128 128 128";
   fixedExtent = true;
   justify = "center";
   canKeyFocus = false;
   mouseOverSelected = true;
   bitmap = "./images/menu";
   hasBitmapArray = true;
};

if(!isObject(GuiConsoleProfile)) new GuiControlProfile (GuiConsoleProfile)
{
   fontType = ($platform $= "macos") ? "Monaco" : "Lucida Console";
   fontSize = ($platform $= "macos") ? 13 : 12;
   fontColor = "0 0 0";
   fontColorHL = "130 130 130";
   fontColorNA = "255 0 0";
   fontColors[6] = "50 50 50";
   fontColors[7] = "50 50 0";  
   fontColors[8] = "0 0 50"; 
   fontColors[9] = "0 50 0";   
};

if(!isObject(GuiConsoleTextEditProfile)) new GuiControlProfile (GuiConsoleTextEditProfile : GuiTextEditProfile)
{
   fontType = ($platform $= "macos") ? "Monaco" : "Lucida Console";
   fontSize = ($platform $= "macos") ? 13 : 12;
};

if (!isObject(GuiTreeViewProfile)) new GuiControlProfile (GuiTreeViewProfile)
{
   fillColorHL = "0 60 150";
   fontSize = 14;
   fontColor = "0 0 0";
   fontColorHL = "64 150 150";
   fontColorNA = "240 240 240";
   fontColorSEL= "250 250 250"; 
   bitmap = "./images/treeView";
   canKeyFocus = true;
   autoSizeHeight = true;
};

//*** DAW:
if(!isObject(GuiText24Profile)) new GuiControlProfile (GuiText24Profile : GuiTextProfile)
{
   fontSize = 24;
};

if(!isObject(GuiRSSFeedMLTextProfile)) new GuiControlProfile ("GuiRSSFeedMLTextProfile")
{
   fontColorLink = "55 55 255";
   fontColorLinkHL = "255 55 55";
};
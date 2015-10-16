//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

if($platform $= "macos")
{
   new GuiCursor(DefaultCursor)
   {
      hotSpot = "4 4";
      renderOffset = "0 0";
      bitmapName = "~/gui/images/macCursor";
   };
} 
else 
{
   new GuiCursor(DefaultCursor)
   {
      hotSpot = "1 1";
      renderOffset = "0 0";
      bitmapName = "~/gui/images/defaultCursor";
   };
}
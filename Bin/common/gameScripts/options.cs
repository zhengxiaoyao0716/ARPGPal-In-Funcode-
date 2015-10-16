//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// onWake
// Called by the engine when the options gui is first set.
//---------------------------------------------------------------------------------------------
function OptionsDlg::onWake(%this)
{
   // Get the fullscreen value.
   FullscreenToggle.setValue($pref::Video::fullScreen);
   
   // Fill the graphics drop down menu.
   %buffer = getDisplayDeviceList();
   %count = getFieldCount(%buffer);
   GraphicsDriverMenu.clear();
   
   for(%i = 0; %i < %count; %i++)
      GraphicsDriverMenu.add(getField(%buffer, %i), %i);
      
   // Grab the current graphics driver selection.
   %selId = GraphicsDriverMenu.findText($pref::Video::displayDevice);
   if (%selId == -1)
      %selId = 0;
      
   GraphicsDriverMenu.setSelected(%selId);
   GraphicsDriverMenu.onSelect(%selId, "");
   
   // Set audio.
   MusicAudioVolume.setValue($pref::Audio::channelVolume[$musicAudioType]);
   EffectsAudioVolume.setValue($pref::Audio::channelVolume[$effectsAudioType]);
   
   // Fill the screenshot drop down menu.
   ScreenshotMenu.clear();
   ScreenshotMenu.add("PNG", 0);
   ScreenshotMenu.add("JPEG", 1);
   ScreenshotMenu.setValue($pref::Video::screenShotFormat);
   
   // Set up the keybind options.
   initializeKeybindOptions();
}

//---------------------------------------------------------------------------------------------
// GraphicsDriverMenu.onSelect
// Called when a graphics device is selected.
//---------------------------------------------------------------------------------------------
function GraphicsDriverMenu::onSelect(%this, %id, %text)
{
   // Attempt to keep the same res and bpp settings.
   %prevRes = getWords(getRes(), 0, 1);
   
   if (FullscreenToggle.getValue())
   {
      if (BPPMenu.size() > 0)
         %prevBPP = BPPMenu.getText();
      else
         %prevBPP = getWord($pref::Video::windowedRes, 2);
   }
   
   // Check if this device is full-screen only.
   if (isDeviceFullScreenOnly(%this.getText()))
   {
      FullscreenToggle.setValue(true);
      FullscreenToggle.setActive(false);
      FullscreenToggle.onAction();
   }
   else
      FullscreenToggle.setActive(true);
   
   // Fill the resolution and bit depth lists.
   ResolutionMenu.init(%this.getText(), FullscreenToggle.getValue());
   BPPMenu.init(%this.getText());
   
   // Try to select the previous settings, otherwise set the first in the list.
   %selId = ResolutionMenu.findText(%prevRes);
   if (%selId == -1)
      %selId = ResolutionMenu.size() - 1;
      
   ResolutionMenu.setSelected(%selId);
   
   // Bit depth only applies to full screen mode.
   if (FullscreenToggle.getValue())
   {
      %selId = BPPMenu.findText(%prevBPP);
      if (%selId == -1)
         %selId = 0;
         
      BPPMenu.setSelected(%selId);
      BPPMenu.setText(BPPMenu.getTextById(%selId));
   }
   else
      BPPMenu.setText("Default");
}

//---------------------------------------------------------------------------------------------
// ResolutionMenu
// Initialize the resolution menu based on the device and fullscreen settings.
//---------------------------------------------------------------------------------------------
function ResolutionMenu::init(%this, %device, %fullScreen)
{
   // Clear out previous values.
   %this.clear();
   
   if( %fullScreen $= "" )
      %fullScreen = isFullScreen();
   
   // Get the list of valid resolutions.
   %resList = getResolutionList(%device);
   %resCount = getFieldCount(%resList);
   %deskRes = getDesktopResolution();
     
   // Loop through all the valid resolutions.
   %count = 0;
   for (%i = 0; %i < %resCount; %i++)
   {
      %res = getWords(getField(%resList, %i), 0, 1);
            
      // If we aren't in fullscreen, valid resolutions must be smaller than the desktop size.
      if (!%fullScreen)
      {
         if ($Video::WindowedDesktopSize !$= "") %deskRes = $Video::WindowedDesktopSize;  //use the desktopsize we came from earlier
         if (firstWord(%res) >= firstWord(%deskRes))
            continue;
         if (getWord(%res, 1) >= getWord(%deskRes, 1))
            continue;
      }

      // Only add to list if it isn't there already.
      if (%this.findText(%res) == -1)
      {
         %this.add(%res, %count);
         %count++;
      }
   }
}

//---------------------------------------------------------------------------------------------
// BPPMenu.init
// Initialize the bits per pixel menu.
//---------------------------------------------------------------------------------------------
function BPPMenu::init(%this, %device)
{
   // Clear previous values.
   %this.clear();
   
   if (%device $= "Voodoo2")
      %this.add("16", 0);
   else
   {
      %resList = getResolutionList(%device);
      %resCount = getFieldCount(%resList);
      %count = 0;
      for (%i = 0; %i < %resCount; %i++)
      {
         %bpp = getWord(getField(%resList, %i), 2);
         
         // Only add to list if it isn't there already.
         if (%this.findText(%bpp) == -1)
         {
            %this.add(%bpp, %count);
            %count++;
         }
      }
   }
}

//---------------------------------------------------------------------------------------------
// FullscreenToggle.onAction
// Called when the fullscreen checkbox is toggled.
//---------------------------------------------------------------------------------------------
function FullscreenToggle::onAction(%this)
{
   %prevRes = ResolutionMenu.getText();
   
   // Update the resolution menu with the new options
   ResolutionMenu.init(GraphicsDriverMenu.getText(), %this.getValue());
   
   // Set it back to the previous resolution if the new mode supports it.
   %selId = -1;
   if( %this.getValue() == false && $pref::Video::windowedRes !$= "" )
      %selId = ResolutionMenu.findText(GetWords($pref::Video::windowedRes,0,1));
   else if( %this.getValue() == true && $pref::Video::Resolution !$= "" )
      %selId = ResolutionMenu.findText(GetWords($pref::Video::Resolution,0,1));
      
   if( %selId == -1 )
      %selId = ResolutionMenu.findText(%prevRes);
   
   if (%selId != -1)
      ResolutionMenu.setSelected(%selId);
   else
      ResolutionMenu.setSelected( ResolutionMenu.size() - 1 );
      
      
}

//---------------------------------------------------------------------------------------------
// updateChannelVolume
// Update an audio channels volume.
//---------------------------------------------------------------------------------------------
$AudioTestHandle = 0;
function updateChannelVolume(%channel, %volume)
{
   // Only valid channels are 1-8
   if (%channel < 1 || %channel > 8)
      return;
      
   alxSetChannelVolume(%channel, %volume);
   $pref::Audio::channelVolume[%channel] = %volume;
   
   // Play a test sound for volume feedback.
   if (!alxIsPlaying($AudioTestHandle))
   {
      $AudioTestHandle = alxCreateSource("AudioChannel" @ %channel,
                                         expandFilename("~/data/audio/volumeTest.wav"));
      alxPlay($AudioTestHandle);
   }
}

//---------------------------------------------------------------------------------------------
// applyAVOptions
// Apply the AV changes.
//---------------------------------------------------------------------------------------------
function applyAVOptions()
{
   %newDriver = GraphicsDriverMenu.getText();
   %newRes = ResolutionMenu.getText();
   %newBpp = BPPMenu.getText();
   %newFullScreen = FullscreenToggle.getValue();
   $pref::Video::screenShotFormat = ScreenshotMenu.getText();
   
   if (%newFullScreen  && !isFullScreen()) $Video::WindowedDesktopSize = getDesktopResolution();
   
   if (%newDriver !$= $pref::Video::displayDevice)
      setDisplayDevice(%newDriver, firstWord(%newRes), getWord(%newRes, 1), %newBpp,
                       %newFullScreen);
   else
      setScreenMode(firstWord(%newRes), getWord(%newRes, 1), %newBpp, %newFullScreen);
      
   Canvas.popDialog(OptionsDlg);
   Canvas.pushDialog(OptionsDlg);
   
   FullscreenToggle.setValue(%newFullScreen);
}

//---------------------------------------------------------------------------------------------
// revertAVOptions
// Revert the AV options to the defaults. Does not apply the changes. Only resets the
// selections.
//---------------------------------------------------------------------------------------------
function revertAVOptions()
{
   // Default resolution: 800x600;
   %selId = ResolutionMenu.findText("800 600");
   if (%selId == -1)
      %selId = 0;
      
   ResolutionMenu.setSelected(%selId);
   
   // Default fullscreen: false;
   FullscreenToggle.setValue(false);
   BPPMenu.setText("Default");
   
   // Default graphics driver: OpenGL;
   %selId = GraphicsDriverMenu.findText("OpenGL");
   if (%selId == -1)
      %selId = 0;
      
   GraphicsDriverMenu.setSelected(%selId);
   GraphicsDriverMenu.onSelect(%selId, "");
   
   // Default volume: 0.8;
   EffectsAudioVolume.setValue(0.8);
   MusicAudioVolume.setValue(0.8);
   updateChannelVolume($effectsAudioType, 0.8);
   updateChannelVolume($musicAudioType, 0.8);
   ScreenshotMenu.clear();
   
   // Default screenshot format: PNG;
   ScreenshotMenu.setValue("PNG");
}

//---------------------------------------------------------------------------------------------
// revertAVOptionChanges
// Revert the AV changes made since the options menu was opened - which happen to be the
// values of the related $prefs.
//---------------------------------------------------------------------------------------------
function revertAVOptionChanges()
{
   FullscreenToggle.setValue($pref::Video::fullScreen);
   
   if (FullscreenToggle.getValue())
      %selId = ResolutionMenu.findText(getWords($pref::Video::resolution, 0, 1));
   else
      %selId = ResolutionMenu.findText(getWords($pref::Video::windowedRes, 0, 1));
   
   if (%selId == -1)
      %selId = 0;
      
   ResolutionMenu.setSelected(%selId);
   
   // Bit depth only applies to full screen mode.
   if (FullscreenToggle.getValue())
   {
      %selId = BPPMenu.findText(getWord($pref::Video::resolution, 2));
      if (%selId == -1)
         %selId = 0;
         
      BPPMenu.setSelected(%selId);
      BPPMenu.setText(BPPMenu.getTextById(%selId));
   }
   else
      BPPMenu.setText("Default");
   
   %selId = GraphicsDriverMenu.findText($pref::Video::displayDevice);
   if (%selId == -1)
      %selId = 0;
      
   GraphicsDriverMenu.setSelected(%selId);
   GraphicsDriverMenu.onSelect(%selId, "");
   
   ScreenshotMenu.setValue($pref::video::screenshotFormat);
}

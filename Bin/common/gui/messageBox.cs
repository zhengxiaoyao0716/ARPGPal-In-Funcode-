//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// messageCallback
// Calls a callback passed to a message box.
//---------------------------------------------------------------------------------------------
function messageCallback(%dlg, %callback)
{
   Canvas.popDialog(%dlg);
   eval(%callback);
}

//---------------------------------------------------------------------------------------------
// MBSetText
// Sets the text of a message box and resizes it to accomodate the new string.
//---------------------------------------------------------------------------------------------
function MBSetText(%text, %frame, %msg)
{
   // Get the extent of the text box.
   %ext = %text.getExtent();
   // Set the text in the center of the text box.
   %text.setText("<just:center>" @ %msg);
   // Force the textbox to resize itself vertically.
   %text.forceReflow();
   // Grab the new extent of the text box.
   %newExtent = %text.getExtent();

   // Get the vertical change in extent.
   %deltaY = getWord(%newExtent, 1) - getWord(%ext, 1);
   
   // Resize the window housing the text box.
   %windowPos = %frame.getPosition();
   %windowExt = %frame.getExtent();
   %frame.resize(getWord(%windowPos, 0), getWord(%windowPos, 1) - (%deltaY / 2),
                 getWord(%windowExt, 0), getWord(%windowExt, 1) + %deltaY);
}

//---------------------------------------------------------------------------------------------
// Various message box display functions. Each one takes a window title, a message, and a
// callback for each button.
//---------------------------------------------------------------------------------------------
function MessageBoxOK(%title, %message, %callback)
{
   MBOKFrame.setText(%title);
   Canvas.pushDialog(MessageBoxOKDlg);
   MBSetText(MBOKText, MBOKFrame, %message);
   MessageBoxOKDlg.callback = %callback;
}

function MessageBoxOKDlg::onSleep( %this )
{
   %this.callback = "";
}

function MessageBoxOKCancel(%title, %message, %callback, %cancelCallback)
{
   MBOKCancelFrame.setText( %title );
   Canvas.pushDialog(MessageBoxOKCancelDlg);
   MBSetText(MBOKCancelText, MBOKCancelFrame, %message);
   MessageBoxOKCancelDlg.callback = %callback;
   MessageBoxOKCancelDlg.cancelCallback = %cancelCallback;
}

function MessageBoxOKCancelDlg::onSleep( %this )
{
   %this.callback = "";
}

function MessageBoxOKCancelDetails(%title, %message, %details, %callback, %cancelCallback)
{   
   if(%details $= "")
   {
      MBOKCancelDetailsButton.setVisible(false);
   }
   
   MBOKCancelDetailsScroll.setVisible(false);
   
   MBOKCancelDetailsFrame.setText( %title );
   
   Canvas.pushDialog(MessageBoxOKCancelDetailsDlg);
   MBSetText(MBOKCancelDetailsText, MBOKCancelDetailsFrame, %message);
   //MBSetText(MBOKCancelDetailsInfoText, MBOKCancelDetailsScroll, %details);
   MBOKCancelDetailsInfoText.setText(%details);
   
   %textExtent = MBOKCancelDetailsText.getExtent();
   %textExtentY = getWord(%textExtent, 1);
   %textPos = MBOKCancelDetailsText.getPosition();
   %textPosY = getWord(%textPos, 1);
      
   %extentY = %textPosY + %textExtentY + 65;
   
   MBOKCancelDetailsInfoText.setExtent(285, 128);
   
   MBOKCancelDetailsFrame.setExtent(300, %extentY);
   
   MessageBoxOKCancelDetailsDlg.callback = %callback;
   MessageBoxOKCancelDetailsDlg.cancelCallback = %cancelCallback;
   
   MBOKCancelDetailsFrame.defaultExtent = MBOKCancelDetailsFrame.getExtent();
}

function MBOKCancelDetailsToggleInfoFrame()
{
   if(!MBOKCancelDetailsScroll.isVisible())
   {
      MBOKCancelDetailsScroll.setVisible(true);
      %textExtent = MBOKCancelDetailsText.getExtent();
      %textExtentY = getWord(%textExtent, 1);
      %textPos = MBOKCancelDetailsText.getPosition();
      %textPosY = getWord(%textPos, 1);
      
      %posY = %textPosY + %textExtentY + 10;
      %posX = getWord(MBOKCancelDetailsScroll.getPosition(), 0);
      MBOKCancelDetailsScroll.setPosition(%posX, %posY);
      MBOKCancelDetailsFrame.minExtent = "300" SPC %textExtentY + 260;        
      MBOKCancelDetailsFrame.setExtent(300, %textExtentY + 260);    
   } else
   {
      %extent = MBOKCancelDetailsFrame.defaultExtent;
      %width = getWord(%extent, 0);
      %height = getWord(%extent, 1);
      MBOKCancelDetailsFrame.minExtent = %width SPC %height;
      MBOKCancelDetailsFrame.setExtent(%width, %height);
      MBOKCancelDetailsScroll.setVisible(false);
   }
}

function MessageBoxOKCancelDetailsDlg::onSleep( %this )
{
   %this.callback = "";
}

function MessageBoxYesNo(%title, %message, %yesCallback, %noCallback)
{
   MBYesNoFrame.setText(%title);
   Canvas.pushDialog(MessageBoxYesNoDlg);
   MBSetText(MBYesNoText, MBYesNoFrame, %message);
   MessageBoxYesNoDlg.yesCallBack = %yesCallback;
   MessageBoxYesNoDlg.noCallback = %noCallBack;
}

function MessageBoxYesNoDlg::onSleep( %this )
{
   %this.yesCallback = "";
   %this.noCallback = "";
}

function MessageBoxYesNoCancel(%title, %message, %yesCallback, %noCallback, %cancelCalback)
{
   MBYesNoCancelFrame.setText(%title);
   Canvas.pushDialog(MessageBoxYesNoCancelDlg);
   MBSetText(MBYesNoCancelText, MBYesNoCancelFrame, %message);
   MessageBoxYesNoCancelDlg.yesCallBack = %yesCallback;
   MessageBoxYesNoCancelDlg.noCallback = %noCallBack;
   MessageBoxYesNoCancelDlg.cancelCallback = %cancelCallBack;
}

function MessageBoxYesNoCancelDlg::onSleep( %this )
{
   %this.yesCallback = "";
   %this.noCallback = "";
   %this.cancelCallback = "";
}

//---------------------------------------------------------------------------------------------
// MessagePopup
// Displays a message box with no buttons. Disappears after %delay milliseconds.
//---------------------------------------------------------------------------------------------
function MessagePopup(%title, %message, %delay)
{
   // Currently two lines max.
   MessagePopFrame.setText(%title);
   Canvas.pushDialog(MessagePopupDlg);
   MBSetText(MessagePopText, MessagePopFrame, %message);
   if (%delay !$= "")
      schedule(%delay, 0, CloseMessagePopup);
}

function CloseMessagePopup()
{
   Canvas.popDialog(MessagePopupDlg);
}

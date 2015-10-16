//---------------------------------------------------------------------------------------------
// Torque Game Builder
// Copyright (C) GarageGames.com, Inc.
//---------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------
// Audio channel descriptions.
//---------------------------------------------------------------------------------------------
$musicAudioType = 1;
new AudioDescription(AudioChannel1)
{
   volume = 1.0;
   isLooping = false;
   is3D = false;
   type = 1;
};

$effectsAudioType = 2;
new AudioDescription(AudioChannel2)
{
   volume = 1.0;
   isLooping = false;
   is3D = false;
   type = 2;
};

//---------------------------------------------------------------------------------------------
// initializeOpenAL
// Starts up the OpenAL driver.
//---------------------------------------------------------------------------------------------
function initializeOpenAL()
{
   // Just in case it is already started.
   shutdownOpenAL();

   echo("OpenAL Driver Init:");

   if($pref::Audio::driver $= "OpenAL")
   {
      if(!OpenALInitDriver())
      {
         error("   Failed to initialize driver.");
         $Audio::initFailed = true;
      }
      else
      {
         // Print out driver info.
         echo("   Vendor: " @ alGetString("AL_VENDOR"));
         echo("   Version: " @ alGetString("AL_VERSION"));  
         echo("   Renderer: " @ alGetString("AL_RENDERER"));
         echo("   Extensions: " @ alGetString("AL_EXTENSIONS"));
         
         // Set the master volume.
         alxListenerf(AL_GAIN_LINEAR, $pref::Audio::masterVolume);
         
         // Set the channel volumes.
         for (%channel = 1; %channel <= 8; %channel++)
            alxSetChannelVolume(%channel, $pref::Audio::channelVolume[%channel]);
         
         echo("");
      }
   }
   else
      error("   Failed to initialize audio system. Invalid driver.");
}

//---------------------------------------------------------------------------------------------
// shutdownOpenAL
//---------------------------------------------------------------------------------------------
function shutdownOpenAL()
{
   OpenALShutdownDriver();
}

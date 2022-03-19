#include "SoundData.h"
#include "Game_Audio.h"

Game_Audio_Class GameAudio(25,0); 

Game_Audio_Wav_Class pmDeath(pacmanDeath); // pacman dyingsound
Game_Audio_Wav_Class pmWav(pacman); // pacman theme                            
                                      

void setup() {
  Serial.begin(115200); 
  Serial.println("Begin...");
}

void loop() {
	// ------------- Play 2 wavs one after the other ----------------    
	Serial.print("Pacman Theme Sample Rate (Hz):");
	Serial.println(pmWav.getSampleRate());
	Serial.print("Duration (secs):");
	Serial.println(pmWav.getDuration());
	
  GameAudio.PlayWav(&pmWav, false, 1.0);
	
	// wait until done
	while(GameAudio.IsPlaying()){	}
	
	delay(200);
	
  GameAudio.PlayWav(&pmDeath, false, 1.0);
	
	// wait until done
	while(GameAudio.IsPlaying()){	}
	
	// -------- Play a wav then interrupt it after 600ms ------------	
	GameAudio.PlayWav(&pmWav, false, 1.0);		
	delay(600);  // this is less than the duration of the last wav
	
	// this wav will not play because the other is playing and interruptCurrent is false
	GameAudio.PlayWav(&pmWav, false, 1.0); 
	// this will interrupt the playing file
	GameAudio.PlayWav(&pmDeath, true, 1.0);	
	
	// --------- Play a wav with increacing sample rate (speeds up playback)	
	for (int i=0; i<10; i += 2)
	{		
		while(GameAudio.IsPlaying()){ }// wait for wav to complete  
		GameAudio.PlayWav(&pmWav, false, (1.0) + (float)i / 10.0);			
	}
	
	while (true) { }  // stop here program is done...but anything still playing will complete
}

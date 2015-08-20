#pragma once
#include "ofThread.h"

class speechToText : public ofThread
{
    
public:
    
    ofEvent<int> COMMAND_COMPLETE;
    
    void recordAndConvert(){
        stopThread();
        startThread( false, false );
    }
    
    // CALL THIS DIRECTLY FOR BLOCKING COMMAND
    std::string exec(char* cmd) {
        FILE* pipe = popen(cmd, "r");
        if (!pipe) return "ERROR";
        char buffer[128];
        std::string result = "";
        while(!feof(pipe)) {
            if(fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
        pclose(pipe);
        return result;
    }
    
private:
    void threadedFunction(){

        string recordingLoc = ofToDataPath("recording.flac").c_str();
        string command = string ("arecord -D plughw:0,0 -q -f cd -t wav -d 0 -r 16000 | flac - -f --best --sample-rate 16000 -s -o ");
        command += recordingLoc;
        
        string result = exec( &command[0u] );
        
        string sttLoc = ofToDataPath("stt.txt").c_str();
        
        command = ("wget -q -U \"Mozilla/5.0\" --post-file recording.flac --header \"Content-Type: audio/x-flac; rate=16000\" -O - \"http://www.google.com/speech-api/v1/recognize?lang=en-us&client=chromium\" | cut -d\\\" -f12  > ");
        command += sttLoc;
        
        result = exec( &command[0u] );
        
        int args = 18 ;
        ofNotifyEvent( COMMAND_COMPLETE, args ) ;
        
        stopThread();
        
    }
    
    string cmd;    
};

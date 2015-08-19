#pragma once

#include "ofMain.h"
#include "ofxGifDecoder.h"
#include "ofxGifFile.h"
#include "ofxJSON.h"
#include "ofxSimpleTimer.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void getImageForText (string query);
    
    ofxGifDecoder decoder;
    ofxGifFile file;
		
    float lastUpdate;
    float frameRate;
    
    float duration;
    
    int screenHeight;
    int screenWidth;
    
    ofxSimpleTimer timer;
    
    void timerCompleteHandler( int &args ) ;
};

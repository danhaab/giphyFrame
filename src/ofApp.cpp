#include "ofApp.h"

int frame = 0;
//--------------------------------------------------------------
void ofApp::setup()
{
    
    searchCriteria = "funny+cat";
    getImageForText(searchCriteria);
    
    lastUpdate = ofGetElapsedTimef();
    
    screenHeight = ofGetScreenHeight();
    screenWidth = ofGetScreenWidth();

    timer.setup( 1000 );
    timer.start( true ) ;
    
    randomizerTimer.setup( 15000 );
    randomizerTimer.start( true ) ;
    
    ofAddListener( timer.TIMER_COMPLETE , this, &ofApp::timerCompleteHandler ) ;
    ofAddListener( randomizerTimer.TIMER_COMPLETE , this, &ofApp::randomizerTimerCompleteHandler ) ;

    
    gifPlayer.setLoopState(OF_LOOP_NORMAL);
    
    //stt.recordAndConvert();
}

void ofApp::getImageForText (string query)
{
    string url = "http://api.giphy.com/v1/gifs/search?q=";
    
    url += query;
    
    url += "&api_key=dc6zaTOxFJmzC";

    ofxJSONElement response;
    
    if (!response.open(url))
    {
        ofLogNotice("ofApp::setup") << "Failed to parse JSON";
    }

    int numImages = response["data"].size();
    
    if (numImages > 0)
    {
        int selection = ofRandom(0, numImages-1);
        
        string imageUrl = response["data"][selection]["images"]["original"]["mp4"].asString();
        
        if (imageUrl.empty())
            return;
        
        gifPlayer.loadMovie(imageUrl);
        
        gifPlayer.play();
        
    }

    
}

//--------------------------------------------------------------
void ofApp::update()
{
    
    gifPlayer.update();
    
    timer.update( );
    
    randomizerTimer.update();
    
}

//--------------------------------------------------------------
void ofApp::draw()
{    
    gifPlayer.draw(0, 0, screenWidth, screenHeight);
    
}
void ofApp::randomizerTimerCompleteHandler( int &args )
{
    getImageForText(searchCriteria);
}
void ofApp::timerCompleteHandler( int &args )
{
    
 
    ifstream fin;
    
    ofFile file;
    
    file.open("stt.txt");
    
    if (!file.exists())
        return;
    
    ofBuffer buffer = file.readToBuffer();
    
    string searchCriteria = buffer.getFirstLine();
        
    ofStringReplace(searchCriteria, " ", "+");
    
    getImageForText(searchCriteria);
        
    file.remove();
    
}

void ofApp::sttCompleteHandler( int &args )
{
    ifstream fin;
    
    fin.open( ofToDataPath("stt.txt").c_str() );
    
    //recognizedWords.clear();
    
    while(fin!=NULL)
    {
        string str;
        getline(fin, str);
        
        //recognizedWords.push_back(str);
        
        remove(ofToDataPath("stt.txt").c_str());
    }
    
    stt.recordAndConvert();
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

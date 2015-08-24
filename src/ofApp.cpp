#include "ofApp.h"



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
    
    //string actionUrl = "https://speech.platform.bing.com/recognize";
    

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
        
        gifPlayer.closeMovie();
        
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

/*void ofApp::bingResponseHandler(ofxHttpResponse & response)
{
    responseMessage = ofToString(response.status) + ": " + (string)response.responseBody;
    
    int i=0;
}*/

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
    
    searchCriteria = buffer.getFirstLine();
        
    ofStringReplace(searchCriteria, " ", "+");
    
    getImageForText(searchCriteria);
    
    file.close();
    
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
void ofApp::keyPressed(int key)
{
    PostRequest request ("https://speech.platform.bing.com/recognize/query", "HTTP/1.1");
    
    BaseResponse response;

    SessionSettings settings;
 
    request.set ("version", "3.0");
    request.set("requestid", "todo");
    request.set("appID", "aec8856c-cf33-4502-9ed4-c9b0e1c1c1e4");
    request.set("format", "json");
    request.set("locale", "en-US");
    request.set("device.os", "raspberry pi");
    request.set("scenarios", "ulm");
    request.set("instanceid", "13231648-9e71-4348-a3b3-e1807781efde");
    
    ofFile audioFile;
    
    audioFile.open("test.wav");
    
    ofBuffer bodyBuffer = audioFile.readToBuffer();
    
    request.addFormBuffer("audio", bodyBuffer);
    
    audioFile.close();
    
    request.setContentType("audio/wav; samplerate=8000");
    
    try
    {
        // Execute the request and get the response stream.
        std::istream& responseStream = sttClient.execute(request,
                                                      response,
                                                      sttContext);
        
        // Request and response headers can be examined here.
        
        
        std::cout << "============" << endl;
        // Copy the output to the terminal.
        Poco::StreamCopier::copyStream(responseStream, std::cout);
        
        // Flush the input stream.
        std::cout << std::endl;
        
        std::cout << "============" << endl;
        
        
    }
    catch(const Poco::Exception& exc)
    {
        ofLogError("ofApp::setup") << "Got Exception " << exc.displayText() << " " << exc.code();
    }
    catch(...)
    {
        ofLogError("ofApp::setup") << "Got unknown exception.";
    }

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

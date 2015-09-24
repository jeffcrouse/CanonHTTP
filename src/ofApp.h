#pragma once

#include "ofMain.h"
#include "ofxEdsdk.h"
#include "ServerImpl.h"

#define PORT 8675
#define VERSION "0.2"

class ofApp : public ofBaseApp{

	public:
        ~ofApp();
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
		
        void drawCentered(string s, int y);
    
        string basename();
        string station;
        string dir;
        Poco::Path path;
    
        ofTrueTypeFont font;
        bool windowShaped;
        ofxEdsdk::Camera camera;
        Poco::Net::HTTPServer* s;
    
        vector<string> messages;
};

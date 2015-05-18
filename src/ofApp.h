#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "FftApp.h"
#include "BackdropApp.h"
#include "RecognitionApp.h"


class ofApp : public ofBaseApp, public FftApp, public BackdropApp, public RecognitionApp
{

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
		
    void guiEvent(ofxUIEventArgs& e);
    void setGuiEventAndLoad(ofxUICanvas* _ui);
    void toggleRecrod();
    bool isSampling;
    
    ofPtr<ofImage> predictedResult;
    
    vector<double> curSpectrum;
    vector<pair<int, double> > curSpectrumMap;
    
    vector<double> curPulse;
    
    ofPtr<ofxUITabBar> tabGui;
    
    ofPtr<ofxUICanvas> recordUI;
    float lastStartRecodTime;
    float lastStopRecodTime;
};

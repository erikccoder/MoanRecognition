//
//  FftApp.cpp
//  MoanRecognition
//
//  Created by erik on 16/5/15.
//
//

#include "FftApp.h"

void FftApp::setup()
{
    fftLive.setup();
    fftGui = ofPtr<ofxUISuperCanvas>(new ofxUISuperCanvas("fftCTL"));
    fftGui->setWidgetFontSize(OFX_UI_FONT_LARGE);
    
    audioThreshold = 1;
    fftGui->addSlider("audioThreshold", 0, 1, &audioThreshold);
    
    audioPeakDecay = 0.915;
    fftGui->addSlider("audioPeakDecay", 0.0, 1.0, &audioPeakDecay);
    
    audioMaxDecay = 0.995;
    fftGui->addSlider("audioMaxDecay", 0.0, 1.0, &audioMaxDecay);
    fftGui->addToggle("audioMirror", &audioMirror);
//    fftGui->addToggle("isSampling", &isSampling);
    fftGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
//    fftGui->addButton("reset", false);
    fftGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    
    fftGui->setName("fftCTL");
}
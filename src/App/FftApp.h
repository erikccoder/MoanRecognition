//
//  FftApp.h
//  MoanRecognition
//
//  Created by erik on 16/5/15.
//
//

#ifndef __MoanRecognition__FftApp__
#define __MoanRecognition__FftApp__

#include "ofMain.h"
#include "ofxFFTLive.h"
#include "ofxUI.h"


class FftApp
{
    
protected:
    ofxFFTLive fftLive;
    float audioThreshold;
    float audioPeakDecay;
    float audioMaxDecay;
    bool audioMirror;
    ofPtr<ofxUISuperCanvas> fftGui;

public:
    void setup();
    
};

#endif /* defined(__MoanRecognition__FftApp__) */

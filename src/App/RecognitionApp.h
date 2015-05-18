//
//  RecognitionApp.h
//  MoanRecognition
//
//  Created by erik on 17/5/15.
//
//

#ifndef __MoanRecognition__RecognitionApp__
#define __MoanRecognition__RecognitionApp__

#include "ofMain.h"
#include "ofxLearn.h"
#include "AppUtilDir.h"
#include "ofxUI.h"


class RecognitionApp : virtual public AppUtilDir
{
    
protected:
    
    vector<ofPtr<ofxUISuperCanvas> > rgIllustrationUI;
    vector<ofPtr<ofImage> > rgIllustrations;
    map<string, double> labelOf;
    map<double, ofPtr<ofImage> > illustrationOf;
    map<double, string > nameOf;
    

    string curIllustrationName;
    
//    ofPtr<ofxUISuperCanvas> recogUI;
    
    ofPtr<ofxUITabBar> labelTab;
    ofxLearn classifier;
    
    bool TRAININGMODE;

public:
    void setup();
//    void setupLabelOf();
    void draw();
    double getCurrentLabel();
};


#endif /* defined(__MoanRecognition__RecognitionApp__) */

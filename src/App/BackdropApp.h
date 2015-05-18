//
//  BackdropApp.h
//  MoanRecognition
//
//  Created by erik on 17/5/15.
//
//

#ifndef __MoanRecognition__BackdropApp__
#define __MoanRecognition__BackdropApp__

#include "ofMain.h"
#include "AppUtilDir.h"

class BackdropApp : virtual public AppUtilDir
{
private:
    ofVec2f bgAnchor;
    ofVec2f cdCenterPos;
    
//    bool isRecording;
    int curAngle;

protected:
    ofPtr<ofImage> background;
    ofPtr<ofImage> cdCover;
        

public:
    
    void setup();
    void update(bool _isRecording = true);
    void draw(ofVec2f _pos);
    
};

#endif /* defined(__MoanRecognition__BackdropApp__) */

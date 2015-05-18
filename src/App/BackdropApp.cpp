//
//  BackdropApp.cpp
//  MoanRecognition
//
//  Created by erik on 17/5/15.
//
//

#include "BackdropApp.h"

//--------------------------------------------------------------
void BackdropApp::setup()
{
    ofPtr<ofImage> _bg(new ofImage);
    string _bgPath =  getFilesFrom("background/").back();
    _bg->loadImage(_bgPath);
    if(_bg->isAllocated())
    {
        _bg->setAnchorPoint(302, 258);
        bgAnchor.set(302, 258);
        background = _bg;
    }
    
    ofPtr<ofImage> _cd(new ofImage);
    string _cdPath =  getFilesFrom("cdCover/").back();
    _cd->loadImage(_cdPath);
    if(_cd->isAllocated())
    {
        _cd->setAnchorPercent(.5, .5);
        cdCenterPos.set(302,146);
        cdCover = _cd;
    }

}

//--------------------------------------------------------------
void BackdropApp::update(bool _isRecording)
{
//    isRecording = _isRecording;
    if(_isRecording)
        curAngle = (curAngle + 2) % 360;
//        curAngle = ofLerp(curAngle, ofGetFrameNum(), 0.01);
}

//--------------------------------------------------------------
void BackdropApp::draw(ofVec2f _pos)
{
    ofPushMatrix();
    
    ofTranslate(_pos);
    if(background) background->draw(0,0);
    if (cdCover) {
        ofPushMatrix();
        
        ofTranslate(cdCenterPos - bgAnchor );        
        ofRotate(curAngle);
        cdCover->draw(0,0);
        ofPopMatrix();
    }
    ofPopMatrix();
}
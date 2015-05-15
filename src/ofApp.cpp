#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(ofColor::black);
    fftLive.setup();
    
    curSpectrum.resize(fftLive.binSize);
    audioThreshold = 1;
    
    gui = ofPtr<ofxUISuperCanvas>(new ofxUISuperCanvas("fftCTL"));
    gui->setWidgetFontSize(OFX_UI_FONT_LARGE);
    gui->addSlider("audioThreshold", 0, 1, &audioThreshold);
    
    audioPeakDecay = 0.915;
    gui->addSlider("audioPeakDecay", 0.0, 1.0, &audioPeakDecay);
    
    audioMaxDecay = 0.995;
    gui->addSlider("audioMaxDecay", 0.0, 1.0, &audioMaxDecay);
    gui->addToggle("audioMirror", &audioMirror);
    gui->addToggle("isSampling", &isSampling);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui->addButton("reset", false);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);

    
    gui->addButton("save", false);
    gui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    gui->addButton("load", false);
    gui->setName("fftCTL");
    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent, this, &ofApp::guiEvent);
    gui->loadSettings(gui->getName() + ".xml");


    isSampling = false;
}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs& e)
{
    string _name = e.getName();
    
    if(_name == "save")
    {
        gui->saveSettings(gui->getName() + ".xml");
    }
    else if(_name == "load")
    {
        gui->loadSettings(gui->getName() + ".xml");
    }
    else if(_name == "reset")
    {
        for (int i=0; i<curSpectrum.size(); i++)
        {
            curSpectrum[i] = 0;
        }
        isSampling = false;
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    fftLive.setThreshold(audioThreshold);
    fftLive.setPeakDecay(audioPeakDecay);
    fftLive.setMaxDecay(audioMaxDecay);
    fftLive.setMirrorData(audioMirror);
    fftLive.update();

    if(isSampling)
    {
        float* _data = new float[curSpectrum.size()];
        fftLive.getFftPeakData(_data, curSpectrum.size());
        
        for (int i=0; i<curSpectrum.size(); i++)
        {
            curSpectrum[i] += _data[i];
        }
        
        delete _data;
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofPushMatrix();
    ofPushStyle();
    
    ofSetColor(ofColor::white);
    float _r = 0.93;
    float _s = (ofGetWidth() *_r) / curSpectrum.size();
    ofTranslate(ofGetWidth() *(1.0 - _r), ofGetHeight()*.75);
    for (int i=0; i<curSpectrum.size(); i++)
    {
        ofRect(i * _s, 0, 2, -curSpectrum[i]);
    }
    
    ofPopStyle();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 'r':
        case 'R':
        {
            isSampling = true;
        }
            break;
            
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case 'r':
        case 'R':
        {
            isSampling = false;
        }
        break;
        case 'e':
        case 'E':
        {
            for (int i=0; i<curSpectrum.size(); i++)
            {
                curSpectrum[i] = 0;
            }
        }
        break;
            
        default:
            break;
    }
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

#include "ofApp.h"

const int MAX_DURATION = 3;

//#define SORT_FREQUENCE
#define PREDICT_PULSE


bool myfunction (pair<int, double> i, pair<int, double> j)
{
    return (i.second > j.second);
}

//--------------------------------------------------------------
void ofApp::setup()
{
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    
    ofBackground(ofColor::fromHex(0xffffff));
    
    FftApp::setup();
//    curSpectrum.resize(fftLive.bufferSize * 0.5);
    int _size = fftLive.getFftNormData().size();
    curSpectrum.resize(_size);
    curSpectrumMap.resize(curSpectrum.size());
    curPulse.resize(_size);

    
    isSampling = false;
    
    BackdropApp::setup();
    RecognitionApp::setup();

    tabGui = ofPtr<ofxUITabBar>(new ofxUITabBar);
    tabGui->setWidgetFontSize(OFX_UI_FONT_LARGE);
    tabGui->addCanvas(fftGui.get());
    tabGui->addCanvas(labelTab.get());

    setGuiEventAndLoad(fftGui.get());
//    setGuiEventAndLoad(labelTab.get());
    for(ofPtr<ofxUISuperCanvas>& _ui : rgIllustrationUI)
    {
        ofAddListener(_ui->newGUIEvent, this, &ofApp::guiEvent);
    }
    ofAddListener(labelTab->newGUIEvent, this, &ofApp::guiEvent);

    
    tabGui->toggleVisible();

    {
        recordUI = ofPtr<ofxUICanvas>(new ofxUICanvas);
        
        vector<string> _recordBtns = getFilesFrom("recordBtn", "png");
        recordUI->addImageToggle("recordBtn", _recordBtns.back(), &isSampling, 100, 100);
        recordUI->autoSizeToFitWidgets();
        recordUI->getRect()->x = ofGetWidth() - recordUI->getRect()->width;
        
        ofColor _w = ofColor::white;
        _w.a = 0;
        recordUI->setColorBack(_w);
        ofAddListener(recordUI->newGUIEvent, this, &ofApp::guiEvent);
    }
//    RecognitionApp::setupLabelOf();
    
    isSampling = false;
    TRAININGMODE = false;
    
    {
        vector<string> _files = getFilesFrom("trainingData", "dat");
//        if(_files.size())
        for (int i = _files.size() -1; i>=0; i--)
        {
            string _path = ofToDataPath(_files[i]);
            ofLog() << "loadModel: " << _path;
            classifier.loadModel(CLASSIFICATION, _path);
        }
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    float _timeDiff = (isSampling ? ofGetElapsedTimef() : lastStopRecodTime)  - lastStartRecodTime;
    
    BackdropApp::update(isSampling);
    fftLive.update();
    if(isSampling)
    {
        float* _data = new float[curSpectrum.size()];
//        fftLive.getFftPeakData(_data, curSpectrum.size());
        fftLive.getFftData(_data, curSpectrum.size());
        
        for (int i=0; i<curSpectrum.size(); i++)
        {
//            int _inv = curSpectrum.size() - 1 - i;
//            curSpectrum[i] += _data[i]*ofGetWidth();
            curSpectrum[i] += _data[i]*3;
//            curSpectrum[i] += _data[_inv];
            curSpectrumMap[i].first = i*4;
            curSpectrumMap[i].second = curSpectrum[i];
        }
        
        delete _data;
        
        int _interal = ofMap(_timeDiff, 0, MAX_DURATION, 0, curPulse.size(), true);
        curPulse[_interal] = fftLive.getAveragePeak()*500;
    }
    
    if(isSampling && _timeDiff > MAX_DURATION)
    {
        isSampling = false;
        toggleRecrod();
    }
    
    stringstream ss;
    ss << (int)(_timeDiff*100)/100.0;

    ofSetWindowTitle(ss.str());
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofVec2f screenCenter(ofGetWidth()*.5, ofGetHeight()*.5);
    
    ofPushMatrix();
    ofPushStyle();
    
//    ofPushMatrix();
//    ofTranslate(0, screenCenter.y);
//    RecognitionApp::draw();
//    ofPopMatrix();
    
    BackdropApp::draw(screenCenter);
    
    {
        vector<double>* _specturm = &curSpectrum;
#ifdef PREDICT_PULSE
        _specturm = &curPulse;
#endif
        ofPushStyle();
        ofSetColor(ofColor::black);
        float _r = 0.95;
        float _y = ofGetHeight()*.75;
        for (int i=0; i<_specturm->size(); i++)
        {
            float _x = ofMap(i, 0, _specturm->size(), ofGetWidth() * (1.0 - _r), ofGetWidth() * _r, true);
            ofRect(_x, _y, 2, MIN(-1, -_specturm->at(i)));
        }
        ofPopStyle();
    }
    {
        ofPushStyle();
        ofSetColor(ofColor::red);
        float _r = 0.95;
        float _y = ofGetHeight()*.75;
        vector<float> _data = fftLive.getFftNormData();
        for (int i=0; i<_data.size(); i++)
        {
            float _x = ofMap(i, 0, curSpectrum.size(), ofGetWidth() * (1.0 - _r), ofGetWidth() * _r, true);
            ofRect(_x, _y, 2, _data[i]*100);
        }
        ofPopStyle();
        
    }
    if(predictedResult)
    {
        ofVec2f _size(predictedResult->getWidth(), predictedResult->getHeight());
        predictedResult->draw(screenCenter - _size*.5);
    }
    

//    stringstream ss;

//    ss.precision(19);
//    ss << getCurrentLabel() << "\n";
//    if(isSampling)
//        ss << ofGetElapsedTimef() - lastStartRecodTime;
//    else
//        ss << lastStopRecodTime - lastStartRecodTime;
//    
//    ofDrawBitmapStringHighlight(ss.str(), 0, 300);
//    ofRectangle _rect;
//    _rect.set(recordUI->getRect()->x-4,
//              recordUI->getRect()->y+4,
//              recordUI->getRect()->width,
//              recordUI->getRect()->height
//    );
//    ofDrawBitmapString(ss.str(), _rect.getCenter());
    
    ofPopStyle();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    switch (key) {
//        case 'r':
//        case 'R':
//        {
//            isSampling = true;
//        }
//            break;
//            
//        default:
//            break;
//    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
    switch (key) {
        case 'r':
        case 'R':
        {
            isSampling = !isSampling;
        }
        break;
        case 'e':
        case 'E':
        {
            for (int i=0; i<curSpectrum.size(); i++)
            {
                curSpectrum[i] = 0;
//                curSpectrumMap[i] = 0;
            }
        }
        break;
        case OF_KEY_TAB:
        {
            tabGui->toggleVisible();
            TRAININGMODE = tabGui->isVisible();
//            if(TRAININGMODE)
//                ofShowCursor();
//            else
//                ofHideCursor();
        }
        break;
        case 's':
        case 'S':
        {
            stringstream ss;
            ss << ofGetYear() << ofGetMonth() << ofGetDay() << '_' << ofGetSystemTimeMicros() << ".dat";
//            ss << "testData.dat";
            classifier.saveModel(ofToDataPath("trainingData/" + ss.str()));
            ofLog() << ss.str() << " saved.";
        }
            break;
            
        case 't':
        case 'T':
        {
            classifier.trainClassifier(CLASSIFICATION, FAST);   // can be FAST or ACCURATE
//            classifier.trainClassifier(CLASSIFICATION, ACCURATE);   // can be FAST or ACCURATE
            ofLog() << "trained";
        }
        break;
        default:
        {
            ofHideCursor();
            ofShowCursor();
        }
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


//--------------------------------------------------------------
void ofApp::setGuiEventAndLoad(ofxUICanvas* _ui)
{
    _ui->addButton("save", false);
    _ui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    _ui->addButton("load", false);
    _ui->autoSizeToFitWidgets();
    ofAddListener(_ui->newGUIEvent, this, &ofApp::guiEvent);
    
//    if(_ui->getName() == "illustrations")
//        ((ofxUITabBar*)_ui)->loadSettings("illustrations/", "");
//    else
    _ui->loadSettings(_ui->getName() + ".xml");

}

//--------------------------------------------------------------
void ofApp::guiEvent(ofxUIEventArgs& e)
{
    string _name = e.getName();
    ofxUICanvas* _ui = e.getCanvasParent();
    string _canvasName = e.getCanvasParentName();
    
    if(_canvasName == "fftCTL"){
        fftLive.setThreshold(audioThreshold);
        fftLive.setPeakDecay(audioPeakDecay);
        fftLive.setMaxDecay(audioMaxDecay);
        fftLive.setMirrorData(audioMirror);
    }
    else if(_canvasName == "illustrations")
    {
//        if(_name == "save")
//        {
//            ((ofxUITabBar*)_ui)->saveSettings("illustrations/","");
//        }
//        else if(_name == "load")
//        {
//            ((ofxUITabBar*)_ui)->loadSettings("illustrations/", "");
//        }
        curIllustrationName = _name;
    }

    
    if(_name == "save")
    {
        _ui->saveSettings(_ui->getName() + ".xml");
    }
    else if(_name == "load")
    {
        _ui->loadSettings(_ui->getName() + ".xml");
    }
    else if(_name == "reset")
    {
        for (int i=0; i<curSpectrum.size(); i++)
        {
            curSpectrum[i] = 0;
        }
        isSampling = false;
    }
    else if(_name == "addTrainingInstance")
    {
        ofLog() << setprecision(15) << "addTrainingInstance: " << curIllustrationName << " | " << getCurrentLabel();
        
        vector<double>* _spectrum = &curSpectrum;

#ifdef SORT_FREQUENCE
        sort(curSpectrumMap.begin(), curSpectrumMap.end(), myfunction);
        for (int i=0; i < _spectrum.size(); i++) {
            _spectrum[i] = curSpectrumMap[i].first;
        }
#endif
#ifdef PREDICT_PULSE
        _spectrum = &curPulse;
#endif
        classifier.addTrainingInstance(*_spectrum, getCurrentLabel());
    }
    else if(_name == "recordBtn")
    {
        toggleRecrod();
    }
}

void ofApp::toggleRecrod()
{

    if(isSampling)
    {
        lastStartRecodTime = ofGetElapsedTimef();
        predictedResult.reset();
//        if(!TRAININGMODE)
        {
            keyReleased('e');
        }
    }
    else
    {
        lastStopRecodTime = ofGetElapsedTimef();
        vector<double>* _spectrum = &curSpectrum;

//        if(!TRAININGMODE && lastStopRecodTime - lastStartRecodTime > 2)
        if(!TRAININGMODE)
        {
#ifdef SORT_FREQUENCE
            sort(curSpectrumMap.begin(), curSpectrumMap.end(), myfunction);
            for (int i=0; i < _spectrum.size(); i++) {
                _spectrum[i] = curSpectrumMap[i].first;
            }
#endif
#ifdef PREDICT_PULSE
            _spectrum = &curPulse;
#endif
            
            double _label = classifier.predict(*_spectrum);
            
            ofLog() << setprecision(15) << "classifier.predict: " << nameOf[_label] << " | " << _label;
            
            if(illustrationOf.find(_label) != illustrationOf.end())
            {
                predictedResult = illustrationOf[_label];
            }
        }
    }
}


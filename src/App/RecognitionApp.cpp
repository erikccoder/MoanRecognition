//
//  RecognitionApp.cpp
//  MoanRecognition
//
//  Created by erik on 17/5/15.
//
//

#include "RecognitionApp.h"

// Disclaimer: I make no claims about the quality of this particular hash - it's
// certainly not a cryptographically secure hash, nor should it *ever* be
// construed as such.

//unsigned long long quickhash64(const char *str, unsigned long long mix = 0)
//{ // set 'mix' to some value other than zero if you want a tagged hash
//    const unsigned long long mulp = 2654435789;
//    
//    mix ^= 104395301;
//    
//    while(*str)
//        mix += (*str++ * mulp) ^ (mix >> 23);
//    
//    return mix ^ (mix << 37);
//}

unsigned int hash(const char *str)
{
    unsigned int h;
    unsigned char *p;
    const unsigned long long mulp = 2654435789;
    
    h = 0;
    for (p = (unsigned char*)str; *p != '\0'; p++)
        h = mulp * h + *p;
    return h; // or, h % ARRAY_SIZE;
}

//--------------------------------------------------------------
void RecognitionApp::setup()
{
    
    labelTab = ofPtr<ofxUITabBar>(new ofxUITabBar);
    labelTab->setWidgetFontSize(OFX_UI_FONT_LARGE);
    labelTab->setName("illustrations");
    
    vector<string> _exts;
    _exts.push_back("png");
    _exts.push_back("jpg");
    vector<string> _files = getFilesFrom("illustrations", _exts);
    
    
    vector<int > _storedID;
    for (string& _s : _files)
    {
        ofPtr<ofImage> _img(new ofImage(_s));
        if(_img->isAllocated())
        {
//            _img->setAnchorPercent(.5, .5);
            rgIllustrations.push_back(_img);
            
            string _name = ofSplitString(_s, "/").back();
            
//            double _label = (double)hash(_name.c_str());
            double _label = rgIllustrations.size()-1;
            labelOf[_name] = _label;
            illustrationOf[_label] = _img;
            nameOf[_label] = _name;
            
            ofPtr<ofxUISuperCanvas>_ui(new ofxUISuperCanvas(_name));
            _ui->setName(_name);
            _ui->setWidgetFontSize(OFX_UI_FONT_LARGE);
            _ui->addImage("img", _img.get());
            _ui->addButton("addTrainingInstance", false);
            
            
            _ui->autoSizeToFitWidgets();
            labelTab->addCanvas(_ui.get());
            rgIllustrationUI.push_back(_ui);
            
            ofLog() << setprecision(15) << _name << " | " << (double)labelOf[_name];
        }
    }
    
//    classifier.trainClassifier(CLASSIFICATION, FAST);   // can be FAST or ACCURATE
    
    
//    recogUI = ofPtr<ofxUISuperCanvas>(new ofxUISuperCanvas("RecognitionUI"));
//    recogUI->setWidgetFontSize(OFX_UI_FONT_LARGE);
//    recogUI->setName("RecognitionUI");
//    recogUI->addRadio("illustrations", _files);

}

//--------------------------------------------------------------
//void RecognitionApp::setupLabelOf()
//{
//    for (ofPtr<ofxUISuperCanvas>& _ui : rgIllustrationUI)
//    {
//        string _name = _ui->getName();
//        double _id = (double)((ofxUIIntSlider*)_ui->getWidget("ID"))->getScaledValue();
//        labelOf[_name] = _id;
//    }
//}

//--------------------------------------------------------------
void RecognitionApp::draw()
{
    ofPushMatrix();
    for (ofPtr<ofImage>& _img : rgIllustrations)
    {
        _img->draw(0, 0);
        ofTranslate(_img->getWidth(), 0);
    }
    ofPopMatrix();
}

//--------------------------------------------------------------
double RecognitionApp::getCurrentLabel()
{
//    ofxUISuperCanvas* _ui = (ofxUISuperCanvas*)labelTab->getActiveCanvas();
//    if(_ui != NULL)
//    {
//        return ((ofxUIIntSlider*)_ui->getWidget("ID"))->getScaledValue();
//    }
//    return 0;
    if (curIllustrationName == "") {
        return 0;
    }
    return labelOf[curIllustrationName];
}

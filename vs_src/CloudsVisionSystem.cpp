//
//  CloudsVisionSystem.cpp
//
//  Created by Patricio Gonzalez Vivo on 7/23/13.
//
//

#include "CloudsVisionSystem.h"
using namespace ofxCv;
string CloudsVisionSystem::getSystemName()
{
	return "CloudssVisionSystem";
}

void CloudsVisionSystem::selfSetup()
{
    currentMode = OpticalFlow;
    curFlow = &pyrLk;
    movieIndex =0;
    pyrScale = 0.5;
    levels =4;
    winsize = 8;    
    iterations =2;
    polyN = 7;
    polySigma = 1.5;
    useFarneback = true;
    winSize =32;
    maxLevel =  3;
    maxFeatures = 200;
    qualityLevel = 0.01;
    minDistance = 4;
    
    cvPersistance =3;
    cvMaxDistance = 80;
    cvMinAreaRadius =15;
    cvMaxAreaRadius = 100;
    cvThresholdValue = 25;
    cvUpdateParameters = false;
    
    //	app
    movieStrings.push_back("unionsq_1 - Wi-Fi.m4v");
    movieStrings.push_back("indianTraffic.mov");
    movieStrings.push_back("Road 2.mov");
    
    ofSetVerticalSync(true);
	ofBackground(0);
    if(player.loadMovie(movieStrings[0])){
        player.play();
    }
    else{
        cout<<"Not Playing"<<endl;
        
    }
    
    
    
    
    updateCVParameters();
    
    
}

void CloudsVisionSystem::updateOpticalFlow(){
    
    
    if(useFarneback) {
        curFlow = &farneback;
        farneback.setPyramidScale( pyrScale);
        farneback.setNumLevels( levels );
        farneback.setWindowSize( winsize) ;
        farneback.setNumIterations( iterations);
        farneback.setPolyN( polyN) ;
        farneback.setPolySigma( polySigma );
        farneback.setUseGaussian(OPTFLOW_FARNEBACK_GAUSSIAN);
        
    } else {
        curFlow = &pyrLk;
        pyrLk.setMaxFeatures( maxFeatures);
        pyrLk.setQualityLevel( qualityLevel );
        pyrLk.setMinDistance( minDistance);
        pyrLk.setWindowSize( winSize);
        pyrLk.setMaxLevel( maxLevel);
    }
    
    //check it out that that you can use Flow polymorphically
    curFlow->calcOpticalFlow(player);

}

void CloudsVisionSystem::updateCVParameters(){
    //  background subtraction
    background.setDifferenceMode(RunningBackground::ABSDIFF);
    background.setLearningTime(15);
    background.setThresholdValue(25);
    
	contourFinder.setMinAreaRadius(cvMinAreaRadius);
	contourFinder.setMaxAreaRadius(cvMaxAreaRadius);
	contourFinder.setThreshold(cvThresholdValue);
    
    //how many frames before we give up on it
	tracker.setPersistence(cvPersistance);
	// an object can move up to 50 pixels per frame
	tracker.setMaximumDistance(cvMaxDistance);
    
    
    //TODO make it an up vector, not down vector
    accumulator.setUpVector(ofVec2f(0.0,-1.0));
    bounds.addVertex(0,0);
    bounds.addVertex(player.getWidth(),0);
    bounds.addVertex(player.getWidth(),player.getHeight());
    bounds.addVertex(0,player.getHeight());
    accumulator.setBounds(bounds);
    
    
    
    
}
void CloudsVisionSystem::selfPresetLoaded(string presetPath){
	
}

void CloudsVisionSystem::selfBegin()
{
    
    
    
}

void CloudsVisionSystem::selfEnd()
{
    
}

void CloudsVisionSystem::selfExit()
{
    
}

void CloudsVisionSystem::selfSetupSystemGui()
{

    sysGui->addLabel("CONTOUR PARAMS");
    sysGui->addSlider("PERSISTANCE", 0,10,&cvPersistance);
    sysGui->addSlider("MAXDISTANCE", 0,10,&cvMaxDistance);
    sysGui->addSlider("MIN AREA RADIUS", 0,50,&cvMinAreaRadius);
    sysGui->addSlider("MAX AREA RADIUS",0,100,&cvMaxAreaRadius);
    sysGui->addSlider("THRESHOLD VALUE", 0, 100, &cvThresholdValue);
    sysGui->addButton("UPDATE CV PARAMS", false);
    sysGui->addButton("LOAD NEXT CLIP", false);
    sysGui->addButton("PLAY CLIP", false);
    
    sysGui->addLabel("OPTICAL FLOW PARAMS");
    
	sysGui->addSlider("PYRSCALE", .5, 0, &pyrScale);
    sysGui->addSlider("LEVELS",  1, 8, &levels);
	sysGui->addSlider("WINSIZE",  4, 64, &winsize);
	sysGui->addSlider("ITERATIONS",1, 8, &iterations);
	sysGui->addSlider("POLYN",5, 10, &polyN);
	sysGui->addSlider("POLYSIGMA", 1.5, 1.1, &polySigma);
	sysGui->addToggle("OPTFLOW_FARNEBACK_GAUSSIAN", useFarneback);
	
	sysGui->addSlider("WINSIZE", 4, 64, &winSize);
	sysGui->addSlider("MAXLEVEL", 0, 8, &maxLevel);
	
	sysGui->addSlider("MAXFEATURES", 200, 1, 1000);
	sysGui->addSlider("QUALITYLEVEL", 0.01, 0.001, .02);
	sysGui->addSlider("MINDISTANCE", 4, 1, 16);
    
    sysGui->addSpacer();
    sysGui->addButton("SAVE", false);
    sysGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    ofxUIButton *loadbtn = gui->addButton("OPTICAL FLOW", false);
    sysGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    ofxUIButton *updatebtn = gui->addToggle("CONTOUR TRACKING", &bUpdateSystem);
    sysGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    sysGui->autoSizeToFitWidgets();
    
    
    
    ofAddListener(sysGui->newGUIEvent, this, &CloudsVisionSystem::selfGuiEvent);
    
}

void CloudsVisionSystem::selfSetupRenderGui()
{
    
}

void CloudsVisionSystem::guiSystemEvent(ofxUIEventArgs &e)
{
    
}

void CloudsVisionSystem::selfKeyPressed(ofKeyEventArgs & args){
    
}

void CloudsVisionSystem::selfUpdate(){
    player.update();
    if(currentMode == ControurTracking){
        if(player.isPlaying() && player.isLoaded()){
            
            if(player.isFrameNew() ){
                background.update(player, thresholded);
                thresholded.update();
                blur(thresholded, 10);
                contourFinder.findContours(thresholded);
                tracker.track(contourFinder.getBoundingRects());
            }
        }
        
    }
    else if(currentMode == OpticalFlow){
        
        updateOpticalFlow();
    }
    
    
    if(useFarneback){
        farneback.getAverageFlow();
    }
    else{
        
    }
    
    
    
}

void CloudsVisionSystem::selfDraw()
{
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    mat->begin();
    mat->end();
    glDisable(GL_NORMALIZE);
    glDisable(GL_DEPTH_TEST);
    
}


void CloudsVisionSystem::selfSetupGuis()
{
    
}

void CloudsVisionSystem::selfAutoMode()
{
    
}


void CloudsVisionSystem::selfDrawBackground()
{
    ofPushMatrix();
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofPushMatrix();
    ofTranslate(-player.getWidth()/2, -player.getHeight()/2);
    
    player.draw(0,0);
    if(currentMode == ControurTracking){
        vector<Car>& followers = tracker.getFollowers();
        for(int i = 0; i < followers.size(); i++) {
            
            if(accumulator.isInBounds(followers[i].boundingBox, 0.05, 4)){
                followers[i].draw();
                followers[i].kill();
                
            }
        }
    }
    else if(currentMode == OpticalFlow){
        curFlow->draw(0, 0);
    }
    
    
    
    
    ofPopMatrix();
    ofPopMatrix();
}

void CloudsVisionSystem::selfDrawDebug()
{
    
}

void CloudsVisionSystem::selfSceneTransformation()
{
    
}

void CloudsVisionSystem::selfKeyReleased(ofKeyEventArgs & args)
{
    
}

void CloudsVisionSystem::selfMouseDragged(ofMouseEventArgs& data)
{
    
}

void CloudsVisionSystem::selfMouseMoved(ofMouseEventArgs& data)
{
    
}

void CloudsVisionSystem::selfMousePressed(ofMouseEventArgs& data)
{
    
}

void CloudsVisionSystem::selfMouseReleased(ofMouseEventArgs& data)
{
    
}

void CloudsVisionSystem::selfSetupGui()
{
    
}

void CloudsVisionSystem::selfGuiEvent(ofxUIEventArgs &e)
{
    
    string name = e.widget->getName();
    ofxUIButton* b = (ofxUIButton*) e.widget;
    if(name == "UPDATE CV PARAMS" &&  b->getValue() ){
        updateCVParameters();
        cout<<"updating parameters"<<endl;
    }
    else if (name == "OPTICAL FLOW" &&  b->getValue()){
        currentMode = OpticalFlow;
        
    }
    else if( name == "CONTOUR TRACKING" &&  b->getValue() ){
        currentMode = ControurTracking;
    }
    else if (name == "OPTFLOW_FARNEBACK_GAUSSIAN" ){
        
        useFarneback = b->getValue();
        cout<<"useFarneback : "<<useFarneback<<endl;
    }
    
    
}

void CloudsVisionSystem::guiRenderEvent(ofxUIEventArgs &e)
{
    
}
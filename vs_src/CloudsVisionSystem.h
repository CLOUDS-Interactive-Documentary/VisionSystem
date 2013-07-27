//
//  emptyVisualSystem.h
//
//  Created by Patricio Gonzalez Vivo on 7/23/13.
//
//

#pragma once

#include "CloudsVisualSystem.h"
#include "ofxCv.h"
#include "CarAccumulator.h"
#include "Car.h"
#include "ParkedCar.h"
#include "Path.h"

typedef enum{
    OpticalFlow =0,
    ControurTracking

}CVMode;

class CloudsVisionSystem : public CloudsVisualSystem {
public:
    
    string getSystemName();
    
    void selfSetup();
    void selfSetupGuis();
    
	void selfPresetLoaded(string presetPath);
	
    void selfAutoMode();
    void selfUpdate();
    void selfDrawBackground();
    void selfDrawDebug();
    void selfSceneTransformation();
    void selfDraw();
    void selfExit();
    void selfBegin();
	void selfEnd();
    
    void selfKeyPressed(ofKeyEventArgs & args);
    void selfKeyReleased(ofKeyEventArgs & args);
    
    void selfMouseDragged(ofMouseEventArgs& data);
    void selfMouseMoved(ofMouseEventArgs& data);
    void selfMousePressed(ofMouseEventArgs& data);
    void selfMouseReleased(ofMouseEventArgs& data);
    
    void selfSetupGui();
    void selfGuiEvent(ofxUIEventArgs &e);
    
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);
    
protected:
    
    //video player stuff
    ofVideoPlayer player;
    int playerIndex;
    int movieIndex;
    vector<string> movieStrings;
    CVMode currentMode;
    vector<ofRectangle> flowRegions;
    
    //Contour tracking stuff
    ofxCv::ContourFinder contourFinder;
	ofxCv::RectTrackerFollower<Car> tracker;
    void updateCVParameters();
    ofImage thresholded;
    ofxCv::RunningBackground background;
    CarAccumulator accumulator;
    cv::Rect accumRegion;
    ofPolyline bounds;
    vector<ParkedCar> parked;
    
    
    //Optical flow types
    ofxCv::FlowFarneback farneback;
	ofxCv::FlowPyrLK pyrLk;
	ofxCv::Flow* curFlow;
    void updateOpticalFlow();
    
    //OPTICAL FLOW PARAMETERS
    float pyrScale;
    float levels;
    float winsize;
    float iterations;
    float polyN;
    float polySigma;
    bool useFarneback;
    float winSize;
    float maxLevel;
    float maxFeatures;
    float qualityLevel;
    float minDistance;
    //    OPTFLOW_FARNEBACK_GAUSSIAN
    
    //CONTUR PARAMETERS
    float cvPersistance;
    float cvMaxDistance;
    float cvMinAreaRadius;
    float cvMaxAreaRadius;
    float cvThresholdValue;
    bool cvUpdateParameters;
    
    
    
};

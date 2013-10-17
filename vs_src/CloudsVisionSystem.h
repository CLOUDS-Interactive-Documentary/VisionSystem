//
//  emptyVisualSystem.h
//
//  Created by Patricio Gonzalez Vivo on 7/23/13.
//
//

#pragma once

#include "CloudsVisualSystem.h"
#include "ofxCv.h"
#include "MyTracker.h"
#include "ParkedCar.h"
#include "Path.h"

typedef enum{
    OpticalFlow =0,
    ControurTracking,
    HeatMap

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
    void resetFlowField();
    void selfSetupGui();
    void selfGuiEvent(ofxUIEventArgs &e);
    
    void selfSetupSystemGui();
    void guiSystemEvent(ofxUIEventArgs &e);
    void updateImagesForNewVideo();
    void updateOpticalFlowParameters();
    void selfSetupRenderGui();
    void guiRenderEvent(ofxUIEventArgs &e);
    void getTextures();

protected:

    //video player stuff
    ofVideoPlayer player;
    int playerIndex;
    int movieIndex;
    vector<string> movieStrings;
    CVMode currentMode;
    int scale;
    vector<ofRectangle> flowRegions;
    void populateOpticalFlowRegions();
    vector<ofVec2f> flowMotion;
    
    ofImage accumulation;
    ofImage diff;

    ofImage previousHeatMap;
    ofImage flowImage;
    ofImage previousFlowImage;

    //Contour tracking stuff
    ofxCv::ContourFinder contourFinder;
	ofxCv::RectTrackerFollower<MyTracker> tracker;
    void updateCVParameters();
    ofImage thresholded;
    ofxCv::RunningBackground background;
    cv::Rect accumRegion;
    vector<ParkedCar> parked;

    //Optical flow types
    ofxCv::FlowFarneback farneback;
	ofxCv::FlowPyrLK pyrLk;
	ofxCv::Flow* curFlow;
    void updateOpticalFlow();
    void clearAccumulation();
    void drawFlowHeatMap(int x, int y);
    ofVboMesh flowMesh;
    list<ofImage> accumVector;
    bool drawPlayer;
    bool drawThresholded;
    bool drawDiff;
    bool flowFirstFrame;

    ofVec2f averageFlow;
    ofFbo fbo;
    
    int accumulationCount;
    cv::Scalar diffMean;
    
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
    float lineWidth;
    
    float learningTime;
    float thresholdValue;
    
    
};

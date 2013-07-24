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
    
    ofVideoPlayer player;
	ofxCv::ContourFinder contourFinder;
	ofxCv::RectTrackerFollower<Car> tracker;
    
    ofImage thresholded;
    ofxCv::RunningBackground background;
    
    CarAccumulator accumulator;
    cv::Rect accumRegion;
    ofPolyline bounds;
    
    ofImage img;
    vector<ParkedCar> parked;
    
    Path p;
};

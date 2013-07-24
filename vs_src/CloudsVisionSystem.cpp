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
    player.loadMovie("indianTraffic.mov");
    //	app
    ofSetVerticalSync(true);
	ofBackground(0);
    
    //This is the test movie
	player.loadMovie("indianTraffic.mov");
	player.play();
    
    
    //  background subtraction
    
    background.setDifferenceMode(RunningBackground::ABSDIFF);
    background.setLearningTime(15);
	background.setThresholdValue(20);
    
	contourFinder.setMinAreaRadius(15);
	contourFinder.setMaxAreaRadius(100);
	contourFinder.setThreshold(25);
    
    //how many frames before we give up on it
	tracker.setPersistence(3);
	// an object can move up to 50 pixels per frame
	tracker.setMaximumDistance(80);
    
    
    //TODO make it an up vector, not down vector
    accumulator.setUpVector(ofVec2f(0.0,-1.0));
    bounds.addVertex(0  , 78);
    bounds.addVertex(226, 72);
    bounds.addVertex(224,173);
    bounds.addVertex(92,171);
    accumulator.setBounds(bounds);
    
    accumRegion.x = 150;
    accumRegion.y = 368;
    accumRegion.width = 300;
    accumRegion.height = 30;
    p = Path(900, 0, 900, 400);
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
    
}

void CloudsVisionSystem::selfSetupRenderGui()
{
    
}

void CloudsVisionSystem::guiSystemEvent(ofxUIEventArgs &e)
{
    
}

void CloudsVisionSystem::selfKeyPressed(ofKeyEventArgs & args){
    
}

void CloudsVisionSystem::selfUpdate()
{
    
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
    cout<<data.x<<","<<data.y<<endl;
}

void CloudsVisionSystem::selfMouseReleased(ofMouseEventArgs& data)
{
    
}

void CloudsVisionSystem::selfSetupGui()
{
    
}

void CloudsVisionSystem::selfGuiEvent(ofxUIEventArgs &e)
{
    
}

void CloudsVisionSystem::guiRenderEvent(ofxUIEventArgs &e)
{
    
}
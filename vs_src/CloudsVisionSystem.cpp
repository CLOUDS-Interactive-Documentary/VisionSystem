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
//    bClearBackground
    movieIndex =0;
    cvPersistance =3;
    cvMaxDistance = 80;
    cvMinAreaRadius =15;
    cvMaxAreaRadius = 100;
    cvThresholdValue = 25;
    cvUpdateParameters = false;
    //	app
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
    if(player2.loadMovie(movieStrings[1])){
        player2.play();
    }
    else{
        cout<<"Not Playing"<<endl;
        
    }
    currentPlayer = player;
    playerIndex =0;
    //This is the test movie
    
    updateCVParameters();


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
    bounds.addVertex(currentPlayer.getWidth(),0);
    bounds.addVertex(currentPlayer.getWidth(),currentPlayer.getHeight());
    bounds.addVertex(0,currentPlayer.getHeight());
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
    sysGui->addLabel("CV PARAMS");
    sysGui->addSlider("PERSISTANCE", 0,10,cvPersistance);
    sysGui->addSlider("MAXDISTANCE", 0,10,cvPersistance);
    sysGui->addSlider("MIN AREA RADIUS", 0,50,cvMinAreaRadius);
    sysGui->addSlider("MAX AREA RADIUS",0,100,cvMaxAreaRadius);
    sysGui->addSlider("THRESHOLD VALUE", 0, 100, cvThresholdValue);
    sysGui->addButton("UPDATE CV PARAMS", false);
    sysGui->addButton("LOAD NEXT CLIP", false);
    sysGui->addButton("PLAY CLIP", false);    
    cout<<"here"<<endl;
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

void CloudsVisionSystem::selfUpdate()
{
    if(currentPlayer.isPlaying() && currentPlayer.isLoaded()){
        currentPlayer.update();
        if(currentPlayer.isFrameNew() ){
            background.update(currentPlayer, thresholded);
            thresholded.update();
            blur(thresholded, 10);
            contourFinder.findContours(thresholded);
            tracker.track(contourFinder.getBoundingRects());
        }
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
    ofTranslate(-currentPlayer.getWidth()/2, -currentPlayer.getHeight()/2);
    if(currentPlayer.isPlaying()){
        currentPlayer.draw(0,0);
        
        vector<Car>& followers = tracker.getFollowers();
        for(int i = 0; i < followers.size(); i++) {
            
            if(accumulator.isInBounds(followers[i].boundingBox, 0.05, 4)){
                followers[i].draw();
                followers[i].kill();
                
            }
        }
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
    
    string name = e.widget->getName();
    ofxUIButton* b = (ofxUIButton*) e.widget;
    if(name == "UPDATE CV PARAMS" &&  b->getValue() ){
        updateCVParameters();
        cout<<"updating parameters";
    }
    else if (name == "LOAD NEXT CLIP" &&  b->getValue()){
        
        if(movieIndex == 0){
            currentPlayer =player;
            updateCVParameters();
            movieIndex = 1;
        }
        else if (movieIndex){
            currentPlayer = player2;
            updateCVParameters();
            movieIndex= 0;
            
        }

        
    }
    else if( name == "PLAY CLIP" &&  b->getValue() ){
        //player.play();
    }
    
    
}

void CloudsVisionSystem::guiRenderEvent(ofxUIEventArgs &e)
{
    
}
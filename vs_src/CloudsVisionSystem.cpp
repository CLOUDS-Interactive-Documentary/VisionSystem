//
//  CloudsVisionSystem.cpp
//
//  Created by Patricio Gonzalez Vivo on 7/23/13.
//
//

#include "CloudsVisionSystem.h"
using namespace ofxCv;
using namespace cv;

string CloudsVisionSystem::getSystemName()
{
	return "CloudssVisionSystem";
}

void CloudsVisionSystem::selfSetup()
{
    currentMode = HeatMap;
    curFlow = &farneback;
    movieIndex =0;
    pyrScale = 0.5;
    levels =4;
    winsize = 8;
    iterations =2;
    polyN = 7;
    polySigma = 1.5;
    winSize =32;
    maxLevel =  3;
    maxFeatures = 200;
    qualityLevel = 0.01;
    minDistance = 4;
    flowFirstFrame = true;
    
    useFarneback = true;
    drawPlayer = true;
    drawThresholded =false;
    
    
    learningTime = 15;
    thresholdValue =128;
    
    cvPersistance =3;
    cvMaxDistance = 80;
    cvMinAreaRadius =15;
    cvMaxAreaRadius = 100;
    cvThresholdValue = 25;
    cvUpdateParameters = false;
    lineWidth = 2;
    
    accumulationCount =0;
    
    //	app
    movieIndex = 0 ;
    movieStrings.push_back("Swarm_EindhovenTest_Watec_two-visitors.mov");
    movieStrings.push_back("GreenPoint_bike.m4v");
    movieStrings.push_back("unionsq_1_realtime 3.mp4");
    movieStrings.push_back("indianTraffic.mov");
    movieStrings.push_back("unionsq_1 - Wi-Fi.m4v");
    movieStrings.push_back("Road 2.mov");
    movieStrings.push_back("traffic_1.mov");
    
    
    
    ofSetVerticalSync(true);
	ofBackground(0);
    if(player.loadMovie(movieStrings[movieIndex])){
        player.play();
    }
    else{
        cout<<"Not Playing"<<endl;
        
    }
    
    imitate(previous, player);
	imitate(diff, player);
    accumulation.allocate(player.width, player.height, OF_IMAGE_COLOR);
    clearAccumulation();
    updateCVParameters();
    populateOpticalFlowRegions();
    
}

void CloudsVisionSystem::clearAccumulation(){
    for(int j=0; j<accumulation.height; j++){
        for( int i=0; i<accumulation.width; i++){
            
            accumulation.setColor(i, j, ofFloatColor(0));
        }
    }
}

void CloudsVisionSystem::populateOpticalFlowRegions(){
    int rectWidth =20;
    int rectHeight = 20;
    for( int j=0; j<player.getHeight(); j +=rectHeight){
        for( int i=0; i<player.getWidth(); i += rectWidth){
            //;
            if (i +rectWidth -1>player.width) {
                rectWidth =player.width- i +1;
            }
            
            if (j +rectHeight -1>player.height) {
                rectHeight =player.height- j +1;
            }
            
            
            flowRegions.push_back(ofRectangle(i, j, rectWidth, rectHeight));
        }
    }
}

void CloudsVisionSystem::updateOpticalFlow(){
    
    if( ! flowFirstFrame){
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
        
        curFlow->calcOpticalFlow(previous, player);//calcOpticalFlow(player);
    }
    flowFirstFrame = false;
    copy(player, previous);

    
}

void CloudsVisionSystem::getTextures(){
    vector<MyTracker>& followers = tracker.getFollowers();
    
    
}
void CloudsVisionSystem::updateCVParameters(){
    //  background subtraction
    background.setDifferenceMode(RunningBackground::ABSDIFF);
    background.setLearningTime(learningTime);
    background.setThresholdValue(thresholdValue);
    
	contourFinder.setMinAreaRadius(cvMinAreaRadius);
	contourFinder.setMaxAreaRadius(cvMaxAreaRadius);
	contourFinder.setThreshold(cvThresholdValue);
    //    contourFinder.setTargetColor(ofColor::yellow);
    
    
    //how many frames before we give up on it
	tracker.setPersistence(cvPersistance);
	// an object can move up to 50 pixels per frame
	tracker.setMaximumDistance(cvMaxDistance);
    //    tracker.
    
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
    sysGui->addLabel("BACKGROUND PARAM");
    sysGui->addSlider("LEARNING TIME", 0,100,&learningTime);
    sysGui->addSlider("THRESHOLD VALUE", 0,255  ,&thresholdValue);
    
    sysGui->addLabel("TRACKER PARAM");
    sysGui->addSlider("PERSISTANCE", 0,100,&cvPersistance);
    sysGui->addSlider("MAXDISTANCE", 0,100  ,&cvMaxDistance);
    
    sysGui->addLabel("CONTOUR FINDER PARAMS");
    sysGui->addSlider("MIN AREA RADIUS", 0,50,&cvMinAreaRadius);
    sysGui->addSlider("MAX AREA RADIUS",0,255,&cvMaxAreaRadius);
    sysGui->addSlider("THRESHOLD VALUE", 0, 255, &cvThresholdValue);
    sysGui->addButton("UPDATE CV PARAMS", false);
    
    
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

	sysGui->addSlider("MAXFEATURES", 200, 1, &maxFeatures);
	sysGui->addSlider("QUALITYLEVEL", 0.01, 0.001, &qualityLevel);
	sysGui->addSlider("MINDISTANCE", 4, 1, &minDistance);

    sysGui->autoSizeToFitWidgets();
    
    ofAddListener(sysGui->newGUIEvent, this, &CloudsVisionSystem::selfGuiEvent);
    
}

void CloudsVisionSystem::selfSetupRenderGui()
{
    
    rdrGui->addSpacer();
    rdrGui->addLabel("CV MODES");
    rdrGui->addSlider("BOX LINE WIDTH", 1, 10, &lineWidth);
    rdrGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);;
    ofxUIButton *loadbtn = rdrGui->addButton("OPTICAL FLOW", false);
    rdrGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    ofxUIButton *updatebtn = rdrGui->addToggle("CONTOUR TRACKING", false);
    rdrGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    ofxUIButton *drawplayerbtn = rdrGui->addToggle("DRAW PLAYER", &drawPlayer);
    rdrGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    ofxUIButton *drawthresholdedbtn = rdrGui->addToggle("DRAW THRESHOLDED", &drawThresholded);
    rdrGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    ofxUIButton *diffbtn = rdrGui->addToggle("DRAW DIFF", &drawDiff);
    rdrGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    ofxUIButton *clearthresholdbtn = rdrGui->addToggle("CLEAR DIFF", false);
    rdrGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_DOWN);
    ofxUIButton *nextVideoButton = rdrGui->addToggle("NEXT VIDEO", false);
    rdrGui->setWidgetPosition(OFX_UI_WIDGET_POSITION_RIGHT);
    ofxUIButton *prevVideoButton = rdrGui->addToggle("PREVIOUS VIDEO", false);
    
    //    rdrGui->addButton("LOAD NEXT CLIP", false);
    //    rdrGui->addButton("PLAY CLIP", false);
    rdrGui->autoSizeToFitWidgets();
    ofAddListener(rdrGui->newGUIEvent, this, &CloudsVisionSystem::selfGuiEvent);
    
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
                blur(thresholded, 5);
                contourFinder.findContours(thresholded);
                tracker.track(contourFinder.getBoundingRects());
            }
        }
        
        
    }
    else if(currentMode == OpticalFlow){
        updateOpticalFlow();
        
    }
    else if(currentMode == HeatMap){
     	if(player.isFrameNew()) {
            accumulationCount++;
            // take the absolute difference of prev and cam and save it inside diff
            
            toCv(accumulation) += toCv(previous) -toCv(player) ;
            
            absdiff(previous, player, diff);
            for(int i =0; i< diff.width; i++ ){
                for(int j =0; j<diff.height; j++){
                    ofColor c = diff.getColor(i, j);
                    float b = c.getBrightness();
                    
                    if(b > 10 ){
                        float scaledHue = ofMap(b ,0, 255, ofFloatColor::blue.getHue(), ofFloatColor::red.getHue());
                        ofFloatColor magnitudeColor = ofFloatColor::fromHsb(scaledHue, 128, 128 ) ;
                        diff.setColor(i, j, magnitudeColor);
                    }
                    
                    
                }
            }
            diff.update();
            
            // like ofSetPixels, but more concise and cross-toolkit
            copy(player, previous);

            //            ofSetColor(magnitudeColor);
            for(int i =0; i< accumulation.width; i++ ){
                for(int j =0; j<accumulation.height; j++){
                    
                    if(! (accumulationCount%5) ){
                        accumulation.setColor(i, j, ofColor::black);
                        accumulationCount =0;
                        
                    }
                    else{
                        ofColor c = accumulation.getColor(i, j);
                        float b = c.getBrightness();
                        
                        
                        if(b > 50 ){
                            float scaledHue = ofMap(b ,0, 255, ofFloatColor::blue.getHue(), ofFloatColor::orange.getHue());
                            ofFloatColor magnitudeColor = ofFloatColor::fromHsb(scaledHue, 200, 200) ;
                            accumulation.setColor(i, j, magnitudeColor);
                        }
                        
                    }

                }
            }
            
            diffMean = mean(toCv(accumulation));
            diffMean *= Scalar(20);
            accumulation.reloadTexture();
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
    ofTranslate(-player.getWidth()/2, -player.getHeight()/2);
    
    if(drawPlayer){
        player.draw(0,0);
        
    }
    if(drawThresholded){
        thresholded.draw(0,0, thresholded.width, thresholded.height);
    }
    
    if(currentMode == ControurTracking){
        contourFinder.draw();
        
        vector<MyTracker>& followers = tracker.getFollowers();
        for(int i = 0; i < followers.size(); i++) {
            float b = followers[i].getLifeTime();
            
            followers[i].draw(lineWidth);
            
        }
        
    }
    else if(currentMode == OpticalFlow){
        
        
        if(useFarneback){
            farneback.drawFlowHeatMap(0, 0);
            
            
        }
    }
    else if(currentMode == HeatMap){
        
        diff.draw(0, 0);
        
        float diffRed = diffMean[0];
        float mapRed = ofMap(diffRed, 0, 512, 0, accumulation.width,true);
        float diffGreen = diffMean[1];
        float mapGreen = ofMap(diffGreen, 0, 512, 0, accumulation.width,true);
        float diffBlue = diffMean[2];
        float mapBlue = ofMap(diffBlue, 0, 512, 0, accumulation.width,true);
        
        ofSetColor(255, 0, 0);
        ofRect(0,accumulation.height -30 , mapRed, 10);
        ofSetColor(0, 255, 0);
        ofRect(0,accumulation.height -15 , mapGreen, 10);
        ofSetColor(0, 0, 255);
        ofRect(0,accumulation.height  ,  mapBlue, 10);
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
        cout<<"setting mode to optical flow"<<endl;
        currentMode = OpticalFlow;
        drawDiff = false;
        drawThresholded = false;
    }
    else if( name == "CONTOUR TRACKING" &&  b->getValue() ){
     
        currentMode = ControurTracking;
    }
    else if (name == "OPTFLOW_FARNEBACK_GAUSSIAN" ){
        
        useFarneback = b->getValue();
        
    }
    else if (name == "DRAW PLAYER"){
        drawPlayer = b->getValue();
        drawThresholded = false;
        drawDiff = false;
    }
    else if( name == "DRAW THRESHOLDED"){
        drawThresholded = b->getValue();
        drawPlayer =false;
        drawDiff = false;
    }
    else if( name == "DRAW DIFF"  &&  b->getValue()){
        currentMode = HeatMap;
        drawDiff = b->getValue();
        drawThresholded = false;
        drawPlayer =false;
    }
    else if( name == "CLEAR DIFF"){
        clearAccumulation();
    }
    else if(name == "NEXT VIDEO" && b->getValue()){
        b->setValue(false);
        player.close();
        thresholded.clear();
        background.reset();


        currentMode =HeatMap;

            if(player.loadMovie(movieStrings[movieIndex < movieStrings.size() ? ++movieIndex : movieStrings.size() - 1])){
                player.play();
                imitate(previous, player);
                imitate(diff, player);
                imitate(thresholded, player);                
                accumulation.allocate(player.width, player.height, OF_IMAGE_COLOR);
                
                clearAccumulation();                
                updateCVParameters();
                populateOpticalFlowRegions();
            }
            else{
                cout<<"Not Playing"<<endl;
                
            }
        
    }
    else if(name == "PREVIOUS VIDEO"  && b->getValue()){
        b->setValue(false);
        player.close();
        thresholded.clear();
        background.reset();
        currentMode =HeatMap;
        
            if(player.loadMovie(movieStrings[movieIndex == 0 ? 0 : --movieIndex])){
                player.play();
                imitate(previous, player);
                imitate(diff, player);
                imitate(thresholded, player);
                accumulation.allocate(player.width, player.height, OF_IMAGE_COLOR);
                clearAccumulation();
                updateCVParameters();
                populateOpticalFlowRegions();
            }
            else{
                cout<<"Not Playing"<<endl;   
            }
    }
    
}

void CloudsVisionSystem::guiRenderEvent(ofxUIEventArgs &e)
{
    
}
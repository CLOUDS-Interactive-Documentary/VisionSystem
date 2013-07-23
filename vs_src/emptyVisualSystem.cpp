//
//  emptyVisualSystem.cpp
//
//  Created by Patricio Gonzalez Vivo on 7/23/13.
//
//

#include "emptyVisualSystem.h"

string emptyVisualSystem::getSystemName()
{
	return "emptyVisualSystem";
}

void emptyVisualSystem::selfSetup()
{
    
}

void emptyVisualSystem::selfPresetLoaded(string presetPath){
	
}

void emptyVisualSystem::selfBegin()
{
    
}

void emptyVisualSystem::selfEnd()
{
    
}

void emptyVisualSystem::selfExit()
{
    
}

void emptyVisualSystem::selfSetupSystemGui()
{
   
}

void emptyVisualSystem::selfSetupRenderGui()
{
    
}

void emptyVisualSystem::guiSystemEvent(ofxUIEventArgs &e)
{
    
}

void emptyVisualSystem::selfKeyPressed(ofKeyEventArgs & args){
    
}

void emptyVisualSystem::selfUpdate()
{
    
}

void emptyVisualSystem::selfDraw()
{
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    mat->begin();

    
    
    mat->end();
    glDisable(GL_NORMALIZE);
    glDisable(GL_DEPTH_TEST);
    
}


void emptyVisualSystem::selfSetupGuis()
{
    
}

void emptyVisualSystem::selfAutoMode()
{
    
}


void emptyVisualSystem::selfDrawBackground()
{
    
}

void emptyVisualSystem::selfDrawDebug()
{
    
}

void emptyVisualSystem::selfSceneTransformation()
{
    
}

void emptyVisualSystem::selfKeyReleased(ofKeyEventArgs & args)
{
    
}

void emptyVisualSystem::selfMouseDragged(ofMouseEventArgs& data)
{
    
}

void emptyVisualSystem::selfMouseMoved(ofMouseEventArgs& data)
{
    
}

void emptyVisualSystem::selfMousePressed(ofMouseEventArgs& data)
{
    
}

void emptyVisualSystem::selfMouseReleased(ofMouseEventArgs& data)
{
    
}

void emptyVisualSystem::selfSetupGui()
{
    
}

void emptyVisualSystem::selfGuiEvent(ofxUIEventArgs &e)
{
    
}

void emptyVisualSystem::guiRenderEvent(ofxUIEventArgs &e)
{
    
}
//
//  Car.h
//  ofApp
//
//  Created by Omer Shapira on 31/03/13.
//
//

#ifndef __ofApp__Car__
#define __ofApp__Car__

#include <iostream>
#include "ofxCv.h"
#include "ofMain.h"



class Car : public ofxCv::RectFollower {
protected:
	ofColor color;
	ofVec2f cur, smooth;
	float startedDying;
	ofPolyline all;

public:
	Car()
:startedDying(0) {
	}
	void setup(const cv::Rect& track);
	void update(const cv::Rect& track);
	void kill();
	void draw();
    int getLifeTime();
    cv::Rect getBoundingBox();
    ofVec2f getTangentAtPoint(int history);
    
    cv::Rect  boundingBox;

};
#endif /* defined(__ofApp__Car__) */
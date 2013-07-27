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



class MyTracker : public ofxCv::RectFollower {
protected:
	ofColor color;
	ofVec3f cur, smooth;
	float startedDying;
	ofPolyline all;

public:
	MyTracker()
:startedDying(0) {
	}
	void setup(const cv::Rect& track);
	void update(const cv::Rect& track);
	void kill();
	void draw();
    ofPolyline getLifeSpan();
    int getLifeTime();
    cv::Rect getBoundingBox();
    ofVec2f getTangentAtPoint(int history);
    
    cv::Rect  boundingBox;

};
#endif /* defined(__ofApp__Car__) */
//
//  Car.cpp
//  ofApp
//
//  Created by Omer Shapira on 31/03/13.
//
//

#include "Car.h"
using namespace cv;
using namespace ofxCv;

const float dyingTime = 1;

void Car::setup(const cv::Rect& track) {

   // cv::Rect test =     cv::Rect(track);
	color.setHsb(ofRandom(0, 255), 255, 255);
	cur = toOf(track).getCenter();
	smooth = cur;
    boundingBox = cv::Rect(track.x,track.y,track.width,track.height);
}

void Car::update(const cv::Rect& track) {
    boundingBox.x = track.x;
    boundingBox.y = track.y;
    boundingBox.width = track.width;
    boundingBox.height = track.height;
	cur = toOf(track).getCenter();
	smooth.interpolate(cur, .5);
	all.addVertex(smooth);
}

void Car::kill() {
	float curTime = ofGetElapsedTimef();
	if(startedDying == 0) {
		startedDying = curTime;
	} else if(curTime - startedDying > dyingTime) {
		dead = true;
	}
}

void Car::draw() {
	ofPushStyle();
	float size = 16;
	ofSetColor(255);
	if(startedDying) {
		ofSetColor(ofColor::red);
		size = ofMap(ofGetElapsedTimef() - startedDying, 0, dyingTime, size, 0, true);
	}
	ofNoFill();
ofCircle(cur, size);
	ofSetColor(color);
    ofCircle(boundingBox.x, boundingBox.y, 10);
	all.draw();
	ofSetColor(255);
	ofDrawBitmapString(ofToString(label), cur);


	ofPopStyle();
}

int Car::getLifeTime(){
    return all.getVertices().size();
}



ofVec2f Car::getTangentAtPoint(int history){
    //FIXME this function is written terribly and inneficiently
    
    //TODO find another way to make this safe
    history = (history < 2)? 2: history;
    if (all.getVertices().size() < history) {
        return ofVec2f(0,0);
    }
    
    std::vector<ofPoint> vec = all.getVertices();
    //TODO write this in a cleaner way, try using toCv();
    //We're taking only the last few points
    std::vector<cv::Vec2f> points;
    //There's no efficient way that isn't O(n)
    for (int i = vec.size() - history ; i<vec.size() ; i++){
        points.push_back(cv::Vec2f(vec[i][0],vec[i][1]));
    }
    
    cv::Vec4f line;
    cv::fitLine(points, line, CV_DIST_L2, 0, .01, .01);
    ofVec2f tangent(line[2],line[3]);
    return tangent;
}

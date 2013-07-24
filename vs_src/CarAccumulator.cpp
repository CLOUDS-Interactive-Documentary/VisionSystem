//
//  CarAccumulator.cpp
//  ofApp
//
//  Created by Omer Shapira on 31/03/13.
//
//

#include "CarAccumulator.h"


float const angleThreshold = 30.0;


//TODO finish with fitline();

bool CarAccumulator::isInBounds(cv::Rect  rect , float epsilon, int tries){
    //safety
    tries = (tries < 2)? 2 : tries;
    //inputArray for OpenCV
    std::vector<ofPoint>& vec = bounds.getVertices();
    int tt = tries*tries;
    float computedArea = 0.0;
    //resolution is for x, y individually, therefore the result is squared
    float resolution = 1.0/tt;
    float xRes = rect.width/tries;
    float yRes = rect.height/tries;
    for (int i = 0 ; i < tries ; i++){
       for (int j = 0 ; j < tries ; j++) {
           // OpenCV rects x and y are top left corners
           // doc: http://opencv.willowgarage.com/documentation/cpp/basic_structures.html
           // we sample the middle, not the corner.
           ofPoint pt = ofPoint(rect.x + i*xRes+xRes/2.0, rect.y+ j*yRes+yRes/2.0);
           computedArea += resolution * (bounds.inside(pt)? 1.0 : 0.0);
           
       }
   }
   // cout << computedArea << " , " << (computedArea >= (1-epsilon))<<endl;
    return (computedArea >= (1-epsilon));
}

void CarAccumulator::setUpVector (ofVec2f vec){
    upVector.set(vec);
}

void CarAccumulator::setBounds(ofPolyline newBounds){
    bounds = newBounds;
    bounds.setClosed(true);
}

bool CarAccumulator::isWithinAngle(Car& car){
    //TODO Make history a parameter - here '5' is used as a good measure.
    //TODO instead of using "angle" use a direct product - the vector may be up or down, but we care about the projection between them, not an actual angle
    return abs(car.getTangentAtPoint(5).angle(upVector))<angleThreshold;
}

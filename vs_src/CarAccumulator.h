 //
//  CarAccumulator.h
//  ofApp
//
//  Created by Omer Shapira on 31/03/13.
//
//

#ifndef __ofApp__Accumulator__
#define __ofApp__Accumulator__

#include <iostream>
#include "ofMain.h"
#include "ofxCV.h"
#include "Car.h"

using namespace cv;

#endif /* defined(__ofApp__Accumulator__) */

class CarAccumulator {

public:
    ofVec2f upVector;
    ofPolyline bounds;
    
    void setBounds(ofPolyline newBounds);
    
    void setUpVector (ofVec2f vec);
    
    //tests if 1-epsilon points of a section sample fit within the accumulator.  
    bool isInBounds(cv::Rect rect , float epsilon, int tries);

    bool isWithinAngle(Car& car);


};
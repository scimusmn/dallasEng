/*
 *  dallasEng.h
 *  Midi_Sequencer
 *
 *  Created by Exhibits on 11/3/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofExtended.h"

void drawHatching(double x, double y, double w, double h, double hatchSpace, double hatchWidth);

class dallasButton : public ofButton {
protected:
public:
  void draw(double _x, double _y);
};

void drawShadowsAroundRect(ofRectangle & box, double depth);
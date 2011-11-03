/*
 *  dallasEng.cpp
 *  Midi_Sequencer
 *
 *  Created by Exhibits on 11/3/11.
 *  Copyright 2011 Science Museum of Minnesota. All rights reserved.
 *
 */

#include "dallasEng.h"

ofColor white(255,255,255);
ofColor black(0,0,0);
ofColor gray(0x33,0x33,0x33);
ofColor yellow(229,225,15);
ofColor red(209,35,42);
ofColor orange(251,176,23);
ofColor blue(109,202,208);

void drawHatching(double x, double y, double w, double h, double hatchSpace, double hatchWidth)
{
  float full=(hatchSpace+hatchWidth);
  ofPoint l1,l2,r1,r2;
  for (int i=1; i<(w+h)/full; i++) {
    
    if(i*full<=h) l1.x=x,l1.y=y+i*full;
    else l1.y=y+h, l1.x=x+i*full-h;
    
    if(i*(full)-hatchWidth<=h) l2.x=x,l2.y=y+i*(full)-hatchWidth;
    else l2.y=y+h, l2.x=x+(i*full-hatchWidth)-h;
    
    if(i*full<=w) r1.y=y,r1.x=x+i*full;
    else r1.x=x+w, r1.y=y+i*full-w;
    
    if(i*(full)-hatchWidth<=w) r2.y=y,r2.x=x+i*full-hatchWidth;
    else r2.x=x+w, r2.y=y+i*full-hatchWidth-w;
    glBegin(GL_QUADS);{
      glVertex2d(l1.x, l1.y);
      glVertex2d(r1.x, r1.y);
      glVertex2d(r2.x, r2.y);
      glVertex2d(l2.x, l2.y);
    }
    glEnd();
  }
}

void drawShadowsAroundRect(ofRectangle & box, double depth){
  ofShade(box.x, box.y, depth, box.width, OF_DOWN, false);
  ofShade(box.x+box.width, box.y, depth, box.height, OF_LEFT);
  ofShade(box.x, box.y+box.height, depth, box.width, OF_UP);
  ofShade(box.x, box.y, depth, box.height, OF_RIGHT, false);
}

void dallasButton::draw(double _x, double _y)
{
  x=_x, y=_y;
  w=20+arial.stringWidth(title);
	h=arial.stringHeight("Kjh")+10;
	if(bPressed) ofSetColor(yellow-.2*255);
  else ofSetColor(yellow);
  ofSetShadowDarkness(.3);
  ofShadowRounded(x, y, w, h, h/4, 5);
  ofFlat();
  ofRoundedRect(x, y, w, h, h/4);
  ofSetColor(gray);
  ofNoFill();
  ofSetLineWidth(2);
  ofRoundedRect(x, y, w, h, h/4);
  ofSetLineWidth(1);
  ofFill();
  
  ofSetColor(gray);
  arial.setMode(OF_FONT_TOP);
  arial.drawString(title,x+10,y+5);
	
}
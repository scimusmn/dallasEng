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

#define as_objHldr(x) static_cast<objHolder *>(x)

void drawHatching(double x, double y, double w, double h, double hatchSpace, double hatchWidth);

class titleBar {
protected:
  ofFont titleFont;
public:
  double x,y,w,h;
  void loadFont(string fontName,int size);
  void draw(string t,int x, int y);
};

class objHolder : public ofInterObj {
protected:
  double space;
  double pad;
  ofDirection orient;
public:
  bool bDraw;
  objHolder();
  objHolder(ofDirection dir,int spacingBetween, ofInterObj * obj,ofInterObj * obj1=0,ofInterObj * obj2=0);
  ofRectangle area;
  vector<ofInterObj *> objs;
  void addObj(ofInterObj & obj);
  void internalSpace(int space);
  double maxHeight();
  void padding(int pad);
  void draw(int x, int y); 
  void reset();
  void setOrientation(ofDirection dir){ orient=dir;}
  void setDrawing(bool areWeDrawing);
};

class toolBar : public objHolder {
protected:
public:
  double x,y,w,h;
  void setup(ofDirection bar_direction);
  void addSegment(int spacingBetweenObjs,ofInterObj * obj,ofInterObj * obj1=0,ofInterObj * obj2=0);
  //void draw(int _x, int _y);
};

class dallasButton : public ofButton {
protected:
public:
  void draw(int _x, int _y);
  void setup(string ttl, int fntSz);
  void setTextSize(int size);
};

class dallasScroll : public ofScrollBar {
public:
  void draw(int _x, int _y);
  void changePadding();
};

class dallasDrop : public ofDropDown {
public:
  dallasDrop();
  dallasDrop(ofTag & tag);
  void draw(int _x, int _y);
  void dallasStyle();
};

class dallasSlider : public ofSlider {
public:
  void draw(int _x, int _y, int _w, int _h);
};

void trimmedRect(double x, double y, double w, double h,double trim=1/3.);

void drawBorder(ofRectangle & box);
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

bool bCloseShape=true;

//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
//_-_-_-_-_//_-_-_-_-_ objHolder //_-_-_-_-_//_-_-_-_-_

objHolder::objHolder()
{
  area.width=0;
  area.height=0;
  bDraw=true;
}

objHolder::objHolder(ofDirection dir,int spaceBetween,ofInterObj * obj,ofInterObj * obj1,ofInterObj * obj2)
{
  orient=dir;
  area.height=0;
  bDraw=true;
  
  addObj(*obj);
  if(obj1) addObj(*obj1);
  if(obj2) addObj(*obj2);
  
  internalSpace(spaceBetween);
}

void objHolder::addObj(ofInterObj & obj)
{
  objs.push_back(&obj);
}

void objHolder::internalSpace(int spc)
{
  space=spc;
  float & t=((orient==OF_HOR)?area.width:area.height);
  t=0;
  for (unsigned int i=0; i<objs.size(); i++) {
    t+=((orient==OF_HOR)?objs[i]->w:objs[i]->h);
    if(i<objs.size()-1) t+=space;
  }
  if(orient==OF_HOR) w=area.width;
  else h=area.height;
}

double objHolder::maxHeight()
{
  double ret=0;
  for (unsigned int i=0; i<objs.size(); i++) {
    ret=max(ret,objs[i]->h);
  }
  return ret*1.3;
}

void objHolder::padding(int pd)
{
  pad=pd;
  internalSpace(space);
  if(orient==OF_HOR) area.width+=pad,w=area.width,area.height=h=maxHeight();
  else area.height+=pad,h=area.height;
  
}

void objHolder::draw(int _x, int _y)
{
  area.x=x=_x;
  area.y=y=_y;
  drawBorder(area);
  int xPos=pad/2;
  for (unsigned int i=0; i<objs.size()&&bDraw; i++) {
    objs[i]->draw(x+xPos,y+(area.height-objs[i]->h)/2);
    xPos+=objs[i]->w+space;
  }
}

void objHolder::reset()
{
  pad=0;
  internalSpace(space);
}

void objHolder::setDrawing(bool drw)
{
  bDraw=drw;
}

//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
//_-_-_-_-_//_-_-_-_-_   toolBar //_-_-_-_-_//_-_-_-_-_

void toolBar::setup(ofDirection bar_direction)
{
  orient=bar_direction;
  pad=0;
  space=0;
  objs.clear();
}

void toolBar::addSegment(int spacingBetweenObjs,ofInterObj * obj,ofInterObj * obj1  ,ofInterObj * obj2)
{
  objs.push_back(new objHolder(orient,spacingBetweenObjs,obj,obj1,obj2));
  int totWid=0;
  double maxHgt=0;
  cout << "obj count is " << objs.size() << endl;
  for (unsigned int i=0; i<objs.size(); i++) {
    as_objHldr(objs[i])->reset();
    totWid+=as_objHldr(objs[i])->w;
    cout << as_objHldr(objs[i])->w << endl;
    maxHgt=max(as_objHldr(objs[i])->maxHeight(),maxHgt);
  }
  for (unsigned int i=0; i<objs.size(); i++) {
    static_cast<objHolder *>(objs[i])->padding((area.width-totWid)/(objs.size()));
    as_objHldr(objs[i])->h=as_objHldr(objs[i])->area.height=maxHgt;
  }
  area.height=h=maxHgt;
}

//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_//_-_-_-_-_
//_-_-_-_-_//_-_-_-_-_// titlebar//_-_-_-_-_//_-_-_-_-_

void titleBar::loadFont(string fontName,int size)
{
  titleFont.loadFont(fontName);
  titleFont.setSize(size);
  titleFont.setMode(OF_FONT_LEFT);
  titleFont.setMode(OF_FONT_TOP);
  h=titleFont.stringHeight("Kjhg")*3;
}

void titleBar::draw(string title,int _x, int _y)
{
  x=_x, y=_y;
  double prop=3;
  h=titleFont.stringHeight("Kjhg")*prop;
  w=ofGetWidth();
  
  ofSetColor(black);
  ofRect(x, y, ofGetWidth(), h);
  //ofSetShadowDarkness(.4);
  //ofShade(x, y+h, 10, ofGetWidth(), OF_UP);
  ofSetColor(yellow);
  titleFont.drawString(title, x+40, y+(h-titleFont.stringHeight(title))/2);
  
  ofSetColor(gray);
  ofRect(x, y+h*.85, w, h*.15);
  
  ofSetColor(yellow);
  ofRect(x, y+h*.85, w, 1);
  ofRect(x, y+h, w, 1);
  //ofSetShadowDarkness(.6);
  //ofShade(x, y+h, 10, ofGetWidth(), OF_DOWN);
  
}


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
    if(bCloseShape) ofBeginShape();
    {
      ofVertex(l1.x, l1.y);
      ofVertex(r1.x, r1.y);
      if(r1.y!=r2.y&&r1.x!=r2.x) ofVertex(r1.x, r2.y);
      ofVertex(r2.x, r2.y);
      ofVertex(l2.x, l2.y);
      if(l1.x!=l2.x&&l1.y!=l2.y) ofVertex(l2.x, l1.y);
    }
    if(bCloseShape) ofEndShape();
  }
  if(!bCloseShape) ofVertex(x+w, y+h),ofVertex(x+w, y),ofVertex(x, y);
}

void drawBorder(ofRectangle & box){
  ofSetColor(yellow);
  ofRect(box.x,box.y,box.width,1);
  ofRect(box.x+box.width,box.y,1,box.height);
  ofRect(box.x,box.y,1,box.height);
  ofRect(box.x,box.y+box.height,box.width,1);
}

void trimmedRect(double x, double y, double w, double h,double trim)
{
  float unit=trim;
  if(unit<1.) unit*=h;
  ofBeginShape();{
    ofVertex(x+unit, y);
    ofVertex(x+w, y);
    ofVertex(x+w, y+h);
    ofVertex(x, y+h);
    ofVertex(x, y+unit);
    ofVertex(x+unit, y);
  }
  ofEndShape();
}

void drawStyledBox(int x, int y, int w, int h)
{
  ofSetColor(gray);
  ofRectangle back(x,y,w,h);
  ofRect(back);
  ofSetColor(black);
  drawHatching(back.x,back.y,back.width, back.height,15,1);
  drawBorder(back);
}

void dallasButton::draw(int _x, int _y)
{
  x=_x, y=_y;
  w=max(1.3*arial.stringWidth(title),w);
	h=arial.stringHeight("Kjh")*1.2;
	//if(bPressed) ofSetColor(white-.2*255);
  ofSetColor(0xbababa);
  trimmedRect(x, y, w, h);
  if(bPressed){
    ofSetColor(blue);
    trimmedRect(x+3, y+3, w-6, h-6, h/3-2);
  }
  ofNoFill();
  ofSetLineWidth(2);
  ofSetColor(white);
  trimmedRect(x+3, y+3, w-6, h-6, h/3-2);
  ofSetColor(black);
  trimmedRect(x, y, w, h);
  ofSetLineWidth(1);
  ofFill();
  
  
  ofSetColor(black);
  arial.drawString(title,x+w/2,y+h/2);
	
}

void dallasButton::setup(string ttl, int fntSz)
{
  ofButton::setup(ttl,"fonts/HelveticaCond.otf",fntSz);
  arial.setMode(OF_FONT_CENTER);
  arial.setMode(OF_FONT_MID);
  h=arial.stringHeight("Kjhg")*1.2;
  w=1.3*arial.stringWidth(title);
}

void dallasButton::setTextSize(int sz)
{
  arial.setSize(sz);
  h=arial.stringHeight("Kjhg")*1.2;
  w=1.3*arial.stringWidth(title);
}

void dallasScroll::draw(int _x, int _y)
{
  ofColor k=ofGetStyle().color;
	x=_x, y=_y;
	ofSetColor(gray.opacity(k.a/255.));
	ofRect(x, y, (vert)?w+2:w, (vert)?h:h+2);
	ofSetColor(black.opacity(k.a/255.));
  ofRect((vert)?x+4:x+endPad, (vert)?y+endPad:y+4, (vert)?w-8:tabRange, (!vert)?h-8:tabRange);
  
  ofSetColor(blue.opacity(k.a/255.));
  
  if(vert) tab.x=x+4, tab.w=w-8,tab.y=y;
  else tab.y=y+4,tab.h=h-8,tab.x=x;
  ofRect(tab.x+tab.relPos.x, tab.y+tab.relPos.y, tab.w, tab.h);
  ofNoFill();
  ofSetColor((blue*.6).opacity(k.a/255.));
  ofRect(tab.x+tab.relPos.x, tab.y+tab.relPos.y, tab.w, tab.h);
  ofFill();
  double space=3;
  ofSetColor(black.opacity(.25));
  double lOff=20;
  for (int i=0; i<((!vert)?(tab.w-lOff)/space:(tab.h-lOff)/space); i++) {
    if(vert) ofRect(tab.x+tab.relPos.x+4, tab.y+tab.relPos.y+lOff/2+i*space, tab.w-8, 1);
    else ofRect(tab.x+tab.relPos.x+lOff/2+i*space, tab.y+tab.relPos.y+4, 1, tab.h-8);
  }
  
  ofRectangle t(x,y,w,h);
  drawBorder(t);
}

void dallasScroll::changePadding()
{
  float pos=getScrollPercent();
  endPad=10;
  tabRange=(vert)?(h-endPad*2):(w-endPad*2);
  double perc=((viewSize/fullSize)>=1)?1:(viewSize/fullSize);
	if (!vert) tab.w=perc*(tabRange-2);
	else tab.h=perc*(tabRange-2);
  setScrollPosition(pos*(fullSize-viewSize));
}

void dallasScroll::startup(){
  endPad=10;
  tabRange=(vert)?(h-endPad*2):(w-endPad*2);
  double perc=((viewSize/fullSize)>=1)?1:(viewSize/fullSize);
	if (!vert) tab.w=perc*(tabRange-2);
	else tab.h=perc*(tabRange-2);
  if(vert) tab.relPos.y=endPad+1;
  else tab.relPos.x=endPad+1;
}

void dallasDrop::draw(int _x, int _y){
  x=_x,y=_y;
	string vars;
	if(values.size()) vars=values[curPos];
  arial.setMode(OF_FONT_MID);
  arial.setMode(OF_FONT_CENTER);
  double prop=1.3;
  h=arial.stringHeight("Kjhg")*1.3;
  float strTop=0;//(h-arial.stringHeight("Kjhg"))/2;
  
	int textX=x+(w-h/4-6)/2;
  int textY=y+h/2;
  ofSetLineWidth(1);
	if(!open){
    ofSetColor(white*.95);
    trimmedRect(x,y,w,h);
    ofSetColor(black);
    ofNoFill();
    trimmedRect(x,y,w,h);
    ofFill();
		int triX=x+w-h/4;
		ofSetColor(black);
		ofEnableSmoothing();
		ofNoFill();
		ofSetLineWidth(1);
		ofTriangle(triX,y+h/2+2,triX-6,y+h/2+2,triX-3,y+3*h/4);
		ofTriangle(triX,y+h/2-2,triX-6,y+h/2-2,triX-3,y+h/4);
		ofFill();
		ofDisableSmoothing();
		ofTriangle(triX,y+h/2+2,triX-6,y+h/2+2,triX-3,y+3*h/4);
		ofTriangle(triX,y+h/2-2,triX-6,y+h/2-2,triX-3,y+h/4);
    ofRect(triX-4, y+h/2-2, 2, 4);
    
		ofSetColor(black);
		arial.drawString(vars, textX,textY);
	}
	else{
		ofSetColor(white*.95);
		int yDisp=(curPos>=nDisp&&curPos<nDisp+values.size()%10)?curPos%10:0;
		if(y-5<h*curPos||!bAutoAdj) yDisp=0;
		steps=values.size();
		if(bOver=(steps>11)){
			steps=min(steps-nDisp, 10);
		}
		ofRect(x+h/4,y-5-yDisp*h,w-h/2,h*((bOver)?steps+2:steps)+10);
    ofSetColor(black);
    ofNoFill();
    ofRect(x+h/4,y-5-yDisp*h,w-h/2,h*((bOver)?steps+2:steps)+10);
    ofFill();
		glColor3f(0,0,0);
		for (int i=0; i<steps; i++) {
			arial.drawString(values[i+nDisp],textX,textY+(i-yDisp)*h);
		}
		if(bOver){
			ofSetLineWidth(1);
			ofLine(x+h/4+2, y+(steps-yDisp)*h, x+w-h/2-2, y+(steps-yDisp)*h);
			if(nDisp>0) ofSetColor(0, 0, 0);
			else ofSetColor(128,128,128);
			arial.drawString("previous page",textX,textY+(steps-yDisp)*h);
			if(nDisp<values.size()-10) ofSetColor(0, 0, 0);
			else ofSetColor(128,128,128);
			arial.drawString("next page",textX,textY+(steps+1-yDisp)*h);
		}
    
	}
}

dallasDrop::dallasDrop(ofTag & tag):ofDropDown(tag)
{
  //dallasStyle();
}

dallasDrop::dallasDrop():ofDropDown()
{
  
}

void dallasDrop::dallasStyle()
{
  arial.loadFont("fonts/HelveticaCond.otf");
  arial.setMode(OF_FONT_TOP);
  setTextSize(22);
}

void dallasSlider::draw(int _x, int _y, int _w, int _h)
{
  x=_x, y=_y;
  w=_w, h=_h;
  knob.x=x-knob.w/2;
  knob.y=y-(knob.h-h)/2;
  
  ofSetColor(black);
  ofRoundedRect(x, y, w, h, h/4);
  
  ofSetColor(yellow);
  ofNoFill();
  ofRoundedRect(x, y, w, h, h/4);
  ofFill();
  ofSetColor(gray);
  ofCircle(knob.x+knob.relPos.x+knob.w/2, knob.y+knob.h/2, knob.w/2);
  if(!knob.pressed()) ofSetColor(white*.4);
  else ofSetColor(gray);
  ofCircle(knob.x+knob.relPos.x+knob.w/2, knob.y+knob.h/2, knob.w/3);
  ofNoFill();
  ofSetColor(yellow);
  ofEnableSmoothing();
  ofSetLineWidth(2);
  ofCircle(knob.x+knob.relPos.x+knob.w/2, knob.y+knob.h/2, knob.w/2);
  ofSetLineWidth(1);
  ofCircle(knob.x+knob.relPos.x+knob.w/2, knob.y+knob.h/2, knob.w/3);
  ofDisableSmoothing();
  ofFill();
}


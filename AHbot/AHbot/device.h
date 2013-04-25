#pragma once
#include <iostream>
using namespace std;
class device
{
public:
	device(void);
	void inputKeybd(string st);
	void inputKeybddown(string st);
	void inputKeybdup(string st);
	void setMousePos(int x,int y);
	void clickMouse(int x,int y);
	~device(void);
private:
	void inputSpecialkey(string st);
};


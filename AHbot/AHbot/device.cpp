#include "StdAfx.h"
#include "device.h"


device::device(void)
{
}
void device::inputKeybd(string st)
{
	if (st[0] == '=') 
	{
		keybd_event(VK_OEM_PLUS,0,0,0);
		keybd_event(VK_OEM_PLUS,0,KEYEVENTF_KEYUP,0);
		return ;
	}
	if (st[0]=='^') inputSpecialkey(st);
	else 
		if (st[0]=='{')
		{
			char vk;
			if (st.compare("{Enter}")==0) vk=VK_RETURN;
			if (st.compare("{ESC}")==0) vk=VK_ESCAPE;
			if (st.compare("{TAB}")==0) vk=VK_TAB;
			if (st.compare("{BS}")==0) vk=VK_BACK;
			keybd_event(vk,0,0,0);
			keybd_event(vk,0,KEYEVENTF_KEYUP,0);
			Sleep(300);
		}
		else
		{
			for (int i=0;i<st.length();i++)
			{
				char vk=st[i];
				if ((vk>='a')&&(vk<='z'))
					vk=vk-('a'-'A');
				else if (vk=='.') vk=VK_OEM_PERIOD;
				else if (vk=='@')
				{
					keybd_event(VK_SHIFT,0,0,0);                                    
					keybd_event(0x32,0,0,0);                                              
					keybd_event(0x32,0,KEYEVENTF_KEYUP,0);         
					keybd_event(VK_SHIFT,0,KEYEVENTF_KEYUP,0);
					continue;
				}
				keybd_event(vk,0,0,0);
				keybd_event(vk,0,KEYEVENTF_KEYUP,0);
				Sleep(50);
			}
			Sleep(250);
		}
}
void device::inputSpecialkey(string st)
{

		keybd_event(VK_CONTROL,0,0,0);
	
	for (int i=1;i<st.length();i++)
	{
		char vk=st[i];
		if ((vk>='a')&&(vk<='z'))
			vk=vk-('a'-'A');
		keybd_event(vk,0,0,0);
		keybd_event(vk,0,KEYEVENTF_KEYUP,0);
	}
	
		keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
	
	Sleep(300);
}
void device::setMousePos(int x,int y)
{
	SetCursorPos(x,y);
	Sleep(50);
}
void device::clickMouse(int x,int y)
{
	mouse_event(MOUSEEVENTF_LEFTDOWN,x,y,0,0);
	mouse_event(MOUSEEVENTF_LEFTUP,x,y,0,0);
	Sleep(500);
}
device::~device(void)
{
}


// AHbotDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AHbot.h"
#include "AHbotDlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <psapi.h>
#include <tlhelp32.h>
#pragma comment (lib,"psapi.lib")
using namespace std;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CAHbotDlg 对话框




CAHbotDlg::CAHbotDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAHbotDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAHbotDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAHbotDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CAHbotDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CAHbotDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CAHbotDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CAHbotDlg 消息处理程序

BOOL CAHbotDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	if(AllocConsole())
	 {
	  freopen("CONOUT$","w+t",stdout);
	  cout<<"helloworld"<<endl;
	 }
	intXAdd=0xC7CD1C;
	intYAdd=0xC7CD20;
	intZAdd=0xC7CD24;
	intStatusAdd=0xC7CCAC;
	intIndexAdd=0xAB2B40;
	intMailinboxallAdd=0xD71BD0;
	intMailinboxnowAdd=0xD71BCC;
	intInGameAdd=0xAD0420;
	conStatusButtonpos.x=589;//init don't modify it
	conStatusButtonpos.y=519;
	conLoginButtonpos.x=424;//init don't modify it
	conLoginButtonpos.y=337;
	/*----------------------------init----------------------------*/
	
	/*----------------------------init----------------------------*/
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CAHbotDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAHbotDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CAHbotDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAHbotDlg::OnBnClickedButton1()
{
	
	initAHbot();
	bool flag=true;
	while(1)
	{
		int intInGame=getMem(intInGameAdd);
		if (intInGame==0) 
		{
				cout<<"now begin login.."<<endl;
				login();
				flag=true;
		}
		else cout<<"you logined!"<<endl;
		string Cancelstatus="";
		::SetForegroundWindow(wowhWnd);
		do
		{
			string talkstatus="";
			while (talkstatus!="AH opened")
			{
				talkstatus=openAH();
				cout<<"talkstatus="<<talkstatus<<endl;
				if (talkstatus=="relogin!")
				{
					flag=false;
					break;
				}
			}
			if (!flag) break;
			Cancelstatus=CancelAuctions();
			if (Cancelstatus=="relogin!")
			{
				flag=false;
				break;
			}
			if (Cancelstatus=="You meet bot test")//TSM bot test
			{
				string rlcomplete="";
				dv.inputKeybd("=");//reload
				cout<<"rl"<<endl;
				while (rlcomplete!="rl finishied")
				{
					cout<<"waiting..."<<endl;
					Sleep(RELOAD_TIME*1000);
					dv.inputKeybd("9");
					rlcomplete=getStatus();
					if (rlcomplete=="relogin!") 
					{
						flag=false;
						break;
					}
				}
				if (!flag) break;
			}
			else break;
		}
		while (1);
		if (!flag) continue;
		string btnold="";
		string btnnew="";
		while (Cancelstatus !="Cancel Scan Finished")
		{
			//dv.inputKeybd("6");//show chatframe1editbox
			for (int i=0;i<10;i++)
			{
				dv.inputKeybd("2");
				Sleep(80);
			}
			Cancelstatus=getStatus("Cancel");
			if (Cancelstatus=="relogin!")
			{
				flag=false;
				break;
			}
			//if (Cancelstatus =="Cancel Scan Finished") break;
			/*dv.inputKeybd("6");
			dv.inputKeybd("7");
			if (btnold!="DISABLED") btnold=getStatus();
			else
			{
				btnnew=getStatus();
				if(btnnew=="DISABLED") break;
				else btnold=btnnew;
			}*/
		}
		if (!flag) continue;
		moveTotmp2();
		moveTomail();
		openMailBox();
		moveTotmp();
		moveToAH();
		string PostStatus="";
		do 
		{
			string talkstatus="";
			while (talkstatus!="AH opened")
			{
				talkstatus=openAH();
				cout<<"talkstatus="<<talkstatus<<endl;
				if (talkstatus=="relogin!")
				{
					flag=false;
					break;
				}
			}
			if (!flag) break;
			PostStatus=PostAuctions();
			if (PostStatus=="relogin!")
			{
				flag=false;
				break;
			}
			if (PostStatus=="You meet bot test")
			{
				string rlcomplete="";
				dv.inputKeybd("=");//reload
				cout<<"rl"<<endl;
				while (rlcomplete!="rl finishied")
				{
					cout<<"waiting..."<<endl;
					Sleep(RELOAD_TIME*1000);
					dv.inputKeybd("9");
					rlcomplete=getStatus();
					if(rlcomplete=="relogin!")
					{
						flag=false;
						break;
					}
				}
				if (!flag) break;
			}else break;
		} while (1);
		if (!flag) continue;
		btnnew="";
		btnold="";
		while (PostStatus!="Post Scan Finished")
		{
			for (int i=0;i<10;i++)
			{
				dv.inputKeybd("2");
				Sleep(80);
			}
			//dv.inputKeybd("6");
			PostStatus=getStatus("Post");
			if (PostStatus=="relogin!")
			{
				flag=false;
				break;
			}
			/*if (PostStatus=="Post Scan Finished")break;
			dv.inputKeybd("6");
			dv.inputKeybd("8");
			if (btnold!="DISABLED") btnold=getStatus();
			else
			{
				btnnew=getStatus();
				if(btnnew=="DISABLED")break;
				else btnold=btnnew;
			}*/
		}
		if (!flag) continue;
		cout<<"finish!"<<endl;
		logout();
		for (int i=1;i<=180;i++)
		{
			cout<<i<<endl;
			Sleep(1000);
		}
		
	}
}
void CAHbotDlg::initAHbot()
{
	intCorlorErrorCount=0;
	wowhWnd = ::FindWindow(NULL,TEXT("魔兽世界")); 
	cout<<wowhWnd<<endl;
	if (wowhWnd!=0)
		wowTID=GetWindowThreadProcessId(wowhWnd,&wowPID);
	else printf("wow is not open!");
	printf("%d\n",wowPID);

	hMemInit=OpenProcess(PROCESS_ALL_ACCESS,FALSE,wowPID);

	cout<<hMemInit<<endl;
	::SetForegroundWindow(wowhWnd);
	HMODULE hModule=GetWOWModule();//::GetModuleHandleA("E:\\World of Warcraft\\WoW.exe");
	deskDC=::GetDC(NULL);
	intLastindex=0;
	intIndex=0;
	GetModuleInformation(hMemInit,hModule,&wowmi,sizeof(wowmi));
	//setPlayerMemPos(1560.309f,281.3945f,-60.77648f);
	::GetWindowRect(wowhWnd,&wowrc);
}
void CAHbotDlg::login()
{
	int flag=0;
	if (intCorlorErrorCount>=10)//备份日志
	{
		CFileFind finder;
		bool b=finder.FindFile("C:\\Inetpub\\wwwroot\\*.wow");
		//CString filename=finder.GetFileName();
		int countfile=0;
		while (b)
		{
			countfile++;
			b=finder.FindNextFile();
		}
		CString refilename;
		refilename.Format("C:\\Inetpub\\wwwroot\\%d.wow",countfile);
		CFile::Rename("C:\\Inetpub\\wwwroot\\index.htm",refilename);
	}
	intCorlorErrorCount=0;
	indexFile.Open(_T("C:\\Inetpub\\wwwroot\\index.htm"),CFile::modeCreate|CFile::modeWrite);
	indexFile.Close();
	//testloginbutton
	closeTeamViewer();
	int color=::GetPixel(deskDC,conLoginButtonpos.x+wowrc.left,conLoginButtonpos.y+wowrc.top);
	if (color==conLogincolor)	dv.inputKeybd("{Enter}");
	//testloginbutton
	dv.inputKeybd("^a");
	dv.inputKeybd("{BS}");
	dv.inputKeybd("HXX0215@GMAIL.COM");
	dv.inputKeybd("{TAB}");
	dv.inputKeybd("TJYRZLXT0607");
	dv.inputKeybd("{Enter}");
	intIndex=getMem(intIndexAdd);
	int intCount=0;
	while ((intIndex<0)||(intIndex>10))
	{
		cout<<"index:"<<intIndex<<endl;
		intIndex=getMem(intIndexAdd);
		Sleep(1000);
		intCount++;
		if (intCount==60) //need modify
		{
			flag=1;
			cout<<"time out ,log again"<<endl;
			dv.inputKeybd("{Enter}");
			dv.inputKeybd("^a");
			dv.inputKeybd("{BS}");
			break;
		}
	}
	if (flag==1)
	{
		login();
		return;
	}
	dv.inputKeybd("{Enter}");
	int intInGame=getMem(intInGameAdd);
	cout<<"waiting";
	while (intInGame==0)
	{
		intInGame=getMem(intInGameAdd);
		Sleep(3000);
		cout<<".";
	}
	cout<<endl;
}
void CAHbotDlg::Println(string st)
{
	cout<<st<<endl;
}
void CAHbotDlg::Println(int n)
{
	cout<<n<<endl;
}
void CAHbotDlg::Println(float f)
{
	cout<<f<<endl;
}
string CAHbotDlg::getStatus(string mode)//Need Package
{
	indexFile.Open(_T("C:\\Inetpub\\wwwroot\\index.htm"),CFile::modeCreate|CFile::modeNoTruncate|CFile::modeWrite);
	indexFile.SeekToEnd();
	closeTeamViewer();//using for test
	int intInGame=getMem(intInGameAdd);//online test!
	if (intInGame==0)
	{
		cout<<"you offline! need to login!"<<endl;
		/*dv.inputKeybd("{Enter}");
		dv.inputKeybd("^a");
		dv.inputKeybd("{BS}");*/
		CString st="relogin!";
		indexFile.Write(st,st.GetLength());
		indexFile.Write("<br>",4);
		indexFile.Write(_T("\r\n"),2);
		indexFile.Close();
		intCorlorErrorCount=10;
		return "relogin!";
	}
	if ((mode=="Post")||(mode=="Cancel")||(mode=="AHOpen")) 
	{
		string st=getColor(mode);
		cout<<"status="<<st<<endl;
		CString ret;
		ret.Format("%s",st.c_str());
		
		indexFile.Write(ret,ret.GetLength());
		indexFile.Write("<br>",4);
		indexFile.Write(_T("\r\n"),2);
		indexFile.Close();
		return st;
	}
	Sleep(2000);
	::SetForegroundWindow(wowhWnd);
	Sleep(500);
	//SetCursorPos(160+wowrc.left,565+wowrc.top);
	if (mode=="7") dv.inputKeybd("7");
	dv.setMousePos(400+wowrc.left,535+wowrc.top);
	dv.clickMouse(400+wowrc.left,535+wowrc.top);
	dv.inputKeybd("^a");
	dv.inputKeybd("^c");
	string ret="";
	if(OpenClipboard())
	{
		HANDLE hData=GetClipboardData(CF_TEXT);
		char * buff=(char *)GlobalLock(hData);
		string st(buff);
		cout<<"status="<<st<<endl;
		GlobalUnlock(hData);
		CloseClipboard();
		ret=st;
	}
	//dv.inputKeybd("{ESC}");
	//dv.inputKeybd("{BS}");
	dv.inputKeybd("{Enter}");
	
	return ret;
}
string CAHbotDlg::getColor(string mode)
{
	if ((mode=="Post")||(mode=="Cancel")||(mode=="AHOpen"))
	{
		int color=::GetPixel(deskDC,conStatusButtonpos.x+wowrc.left,conStatusButtonpos.y+wowrc.top);
		if (color==conStatusButtonBotTestcolor) return "You meet bot test";
		if (color==conStatusButtonAHOpencolor) return "AH opened";
		if (color==conStatusButtonPostCancelcolor) return mode+" Auctions";
		if (color==conStatusButtonFinishcolor)return mode+" Scan Finished";
	}
	intCorlorErrorCount++;
	CString st;
	st.Format("%d",intCorlorErrorCount);
	if (intCorlorErrorCount>=30) logout();//fatal error logout;
	return mode+":SomeWhereError:"+(LPCTSTR)st;
}
string CAHbotDlg::openAH()
{
	//dv.inputKeybd("6");//ShowChatFrame1EditBox;
	string data="";
	dv.inputKeybd("1");//set Target
	dv.inputKeybd("K");//talk to target
	data=getStatus("AHOpen");
	return data;
}
string CAHbotDlg::CancelAuctions()
{
	::SetForegroundWindow(wowhWnd);//for safe
	//dv.inputKeybd("6");//show chatframe1editbox
	dv.setMousePos(95+wowrc.left,305+wowrc.top);
	dv.clickMouse(95+wowrc.left,305+wowrc.top);
	//Sleep(1000);
	string	data=getStatus("Cancel");
	return data;
}

void CAHbotDlg::OnBnClickedButton2()//for test
{
	PROCESSENTRY32 ProcessEntry = { 0 };
	MODULEENTRY32  ModuleEntry  = { 0 };
	HANDLE hProcessSnap;
	HANDLE hModuleSnap;
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	ModuleEntry.dwSize  = sizeof(MODULEENTRY32);

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);//给系统内的所有进程拍一个快照

	BOOL bRet = Process32First(hProcessSnap,&ProcessEntry);// 遍历进程快照，轮流显示每个进程的信息，先获得第一个
	while(bRet)
	{
		//printf("\n%s\n",ProcessEntry.szExeFile);//输出该进程可执行文件名（包括路径）
		string st(ProcessEntry.szExeFile);
		//Sleep(200);

		hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,ProcessEntry.th32ProcessID);//循环给每个进程的所有模块拍一个快照

		bRet = Module32First(hModuleSnap,&ModuleEntry);// 遍历模块快照，轮流显示每个模块的信息，先获得第一个 
		if (st=="Wow.exe")
		{
			while(bRet)
			{
				printf("\t%s\n",ModuleEntry.szExePath);
				//Sleep(200);
				cout<<ModuleEntry.hModule<<endl;
				bRet = Module32Next(hModuleSnap,&ModuleEntry);//下一个模块
			}
		}
		/**/

		bRet = Process32Next(hProcessSnap,&ProcessEntry);//下一个进程
	}
}
HMODULE CAHbotDlg::GetWOWModule()//look btn2
{
	PROCESSENTRY32 ProcessEntry = { 0 };
	MODULEENTRY32  ModuleEntry  = { 0 };
	HANDLE hProcessSnap;
	HANDLE hModuleSnap;
	ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
	ModuleEntry.dwSize  = sizeof(MODULEENTRY32);

	hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	BOOL bRet = Process32First(hProcessSnap,&ProcessEntry);
	while(bRet)
	{
		string st(ProcessEntry.szExeFile);
		hModuleSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,ProcessEntry.th32ProcessID);
		bRet = Module32First(hModuleSnap,&ModuleEntry);
		if (st=="Wow.exe")
		{
			while(bRet)
			{
				//printf("\t%s\n",ModuleEntry.szExePath);
				string ss(ModuleEntry.szExePath);
				for (int i=0;i<ss.length();i++)
				{
					if ((ss[i]>='A')&&(ss[i]<='Z')) ss[i]+='a'-'A';
				}
				cout<<ss<<endl;
				if (ss.find("wow.exe")>=0) return ModuleEntry.hModule;
				//Sleep(200);
				cout<<ModuleEntry.hModule<<endl;
				bRet = Module32Next(hModuleSnap,&ModuleEntry);
			}
		}
		/**/

		bRet = Process32Next(hProcessSnap,&ProcessEntry);
	}
	return NULL;
}
void CAHbotDlg::setPlayerMemPos(float x,float y,float z)
{
	LPVOID xAdd=(LPVOID)((int)wowmi.lpBaseOfDll+intXAdd);
	LPVOID yAdd=(LPVOID)((int)wowmi.lpBaseOfDll+intYAdd);
	LPVOID zAdd=(LPVOID)((int)wowmi.lpBaseOfDll+intZAdd);
	LPVOID statusAdd=(LPVOID)((int)wowmi.lpBaseOfDll+intStatusAdd);
	DWORD dwNumberOfBytesRead;
	int mstatus=4;
	WriteProcessMemory(hMemInit,xAdd,&x,sizeof(x),&dwNumberOfBytesRead);
	WriteProcessMemory(hMemInit,yAdd,&y,sizeof(y),&dwNumberOfBytesRead);
	WriteProcessMemory(hMemInit,zAdd,&z,sizeof(z),&dwNumberOfBytesRead);
	WriteProcessMemory(hMemInit,statusAdd,&mstatus,sizeof(mstatus),&dwNumberOfBytesRead);
}
void CAHbotDlg::moveTotmp2()
{
	dv.inputKeybd("4");
	float tmpx=1560.309f;
	float tmpy=281.3945f;
	float tmpz=-60.77648f;
	cout<<tmpx<<" "<<tmpy<<" "<<tmpz<<endl;
	setPlayerMemPos(tmpx,tmpy,tmpz);
	Sleep(5000);//moving;
}
void CAHbotDlg::moveTomail()
{
	float tmpx=1550.571f;
	float tmpy=278.9036f;
	float tmpz=-60.76977f;
	cout<<tmpx<<" "<<tmpy<<" "<<tmpz<<endl;
	setPlayerMemPos(tmpx,tmpy,tmpz);
	Sleep(2000);//moving;
	dv.inputKeybd("O");//turn view
	Sleep(2000);
}
void CAHbotDlg::openMailBox(int times)
{
	closeTeamViewer();
	::SetForegroundWindow(wowhWnd);
	dv.setMousePos(380+wowrc.left,330+wowrc.top);
	Sleep(500);
	dv.inputKeybd("J");
	Sleep(700);
	int intMailNumlast=getMem(intMailinboxnowAdd);
	int intMailNumnow=intMailNumlast;
	cout<<"mailbox now "<<intMailNumlast<<" mail."<<endl;
	do 
	{
		intMailNumlast=intMailNumnow;
		dv.inputKeybd("3");
		cout<<"receiving..."<<endl;
		Sleep(2000);
		intMailNumnow=getMem(intMailinboxnowAdd);
		cout<<"mailbox now "<<intMailNumnow<<","<<intMailNumlast<<" mail."<<endl;
	} while (intMailNumnow!=intMailNumlast);
	
	return;
	
	string rlcomplete="";
	dv.inputKeybd("=");//reload
	cout<<"rl"<<endl;
	Sleep(RELOAD_TIME*1000);
	while (rlcomplete!="rl finishied")
	{
		cout<<"waiting..."<<endl;
		Sleep(1000);
		dv.inputKeybd("9");
		rlcomplete=getStatus();
	}
}
void CAHbotDlg::moveTotmp()
{
	//dv.inputKeybd("4");
	float tmpx=1573.397f;
	float tmpy=287.2489f;
	float tmpz=-57.26404f;
	cout<<tmpx<<" "<<tmpy<<" "<<tmpz<<endl;
	setPlayerMemPos(tmpx,tmpy,tmpz);
	Sleep(5000);
}
void CAHbotDlg::moveToAH()
{
	float tmpx=1579.410f;
	float tmpy=292.4096f;
	float tmpz=-56.86724f;
	cout<<tmpx<<" "<<tmpy<<" "<<tmpz<<endl;
	setPlayerMemPos(tmpx,tmpy,tmpz);
	Sleep(2000);
}
string CAHbotDlg::PostAuctions()
{
	::SetForegroundWindow(wowhWnd);
	//dv.inputKeybd("6");
	dv.setMousePos(95+wowrc.left,285+wowrc.top);
	dv.clickMouse(95+wowrc.left,285+wowrc.top);
	Sleep(100);
	string data=getStatus("Post");
	return data;
}
int CAHbotDlg::getMem(int addr)
{
	LPVOID indexAdd=(LPVOID)((int)wowmi.lpBaseOfDll+addr);
	int ret=0;
	DWORD dwNumberOfBytesRead;
	ReadProcessMemory(hMemInit,indexAdd,&ret,sizeof(ret),&dwNumberOfBytesRead);
	return ret;
}

void CAHbotDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	initAHbot();
	/*initAHbot();
	int mail=getMem(intInGameAdd);
	cout<<mail<<endl;*/

	//==========colortest=========
	/*POINT p;
	HDC hdc=NULL;
	hdc=::GetDC(NULL);
	::GetCursorPos(&p);
	p.x=825;p.y=587;
	int color=::GetPixel(hdc,p.x,p.y);
	int r = (color & 0xff0000)>>16;
	int g=(color & 0xff00)>>8;
	int b=(color & 0xff);
	cout<<"absPos:"<<p.x<<","<<p.y<<"Pos:"<<p.x-wowrc.left<<","<<p.y-wowrc.top
		<<"color:"<<color<<"rgb:"<<r<<","<<g<<","<<b<<endl;*/
	CFileFind finder;
	bool b=finder.FindFile("C:\\Inetpub\\wwwroot\\*.wow");
	//CString filename=finder.GetFileName();
	int countfile=0;
	while (b)
	{
		countfile++;
		b=finder.FindNextFile();
	}
	CString refilename;
	refilename.Format("C:\\Inetpub\\wwwroot\\%d.wow",countfile);
	CFile::Rename("C:\\Inetpub\\wwwroot\\index.htm",refilename);
}
void CAHbotDlg::closeTeamViewer()
{
	HWND hwnd=::FindWindow(NULL,TEXT("发起会话"));
	//::SendMessage(hwnd,WM_SYSCOMMAND,SC_CLOSE,0);
	if (hwnd)
	{
		::SetForegroundWindow(hwnd);
		Sleep(1000);
		CRect rc;
		::GetWindowRect(hwnd,&rc);
		dv.setMousePos(425+rc.left,145+rc.top);
		dv.clickMouse(425+rc.left,145+rc.top);
		::SetForegroundWindow(wowhWnd);
	}
	//else cout<<"no teamviewer";
}
void CAHbotDlg::logout()
{
	dv.inputKeybd("5");//log out
	intIndex=getMem(intIndexAdd);
	while ((intIndex<0)||(intIndex>10))
	{
		cout<<"index:"<<intIndex<<endl;
		intIndex=getMem(intIndexAdd);
		Sleep(1000);
	}
	dv.inputKeybd("{ESC}");
}

// AHbotDlg.h : ͷ�ļ�
//

#pragma once
#include <string>
using namespace std;
#include "device.h"
#define RELOAD_TIME 15
#define OPENMAILBOX_TIME 17
#include <psapi.h>
// CAHbotDlg �Ի���
class CAHbotDlg : public CDialog
{
// ����
public:
	CAHbotDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_AHBOT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	void Println(string st);
	void Println(int n);
	void Println(float f);
	string getStatus(string mode="");
	string getColor(string mode);
	string openAH();
	string CancelAuctions();

	HMODULE GetWOWModule();
	void setPlayerMemPos(float x,float y,float z);
	void moveTotmp2();
	void moveTomail();
	void openMailBox(int times=0);
	void moveTotmp();
	void moveToAH();
	void login();
	void logout();
	string PostAuctions();
	int getMem(int addr);
	void initAHbot();
	void closeTeamViewer();
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
private:
	HWND wowhWnd;
	HDC deskDC;
	DWORD wowPID, wowTID;
	HANDLE hMemInit;
	CRect wowrc;
	device dv;
	MODULEINFO wowmi;
	int intXAdd;
	int intYAdd;
	int intZAdd;
	int intStatusAdd;
	int intIndexAdd;
	int intMailinboxnowAdd;
	int intMailinboxallAdd;
	int intInGameAdd;
	int intIndex;
	int intLastindex;
	int intCorlorErrorCount;
	static const int conLogincolor=65899;
	static const int conStatusButtonFinishcolor=10443973;
	static const int conStatusButtonPostCancelcolor=14238786;
	static const int conStatusButtonBotTestcolor=10485552;
	static const int conStatusButtonAHOpencolor=65461;
	POINT conStatusButtonpos;//don't modify this var
	POINT conLoginButtonpos;//don't modify this var
	CFile indexFile;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
};

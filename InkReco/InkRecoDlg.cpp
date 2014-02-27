
// InkRecoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "InkReco.h"
#include "InkRecoDlg.h"
#include "afxdialogex.h"

#include <msinkaut.h>
#include <msinkaut_i.c>

IInkRecognizerContext *g_IInkRecoContext = NULL;
IInkOverlay *g_IInkOverlay = NULL;
IInkDisp *g_IInkDisp = NULL;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CInkRecoDlg �Ի���



CInkRecoDlg::CInkRecoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInkRecoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInkRecoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CInkRecoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CInkRecoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CInkRecoDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CInkRecoDlg ��Ϣ�������

BOOL CInkRecoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	CoInitialize(NULL);

	HRESULT hr = CoCreateInstance(CLSID_InkRecognizerContext, NULL, \
		CLSCTX_INPROC_SERVER, IID_IInkRecognizerContext, (void**)&g_IInkRecoContext);
	
	CoCreateInstance(CLSID_InkOverlay, NULL, CLSCTX_INPROC_SERVER, IID_IInkOverlay, (void**)&g_IInkOverlay);

	g_IInkOverlay->get_Ink(&g_IInkDisp);

	g_IInkOverlay->put_hWnd((long)GetSafeHwnd());

	g_IInkOverlay->put_Enabled(VARIANT_TRUE);


	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CInkRecoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CInkRecoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CInkRecoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CInkRecoDlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	g_IInkDisp->DeleteStrokes();

	InvalidateRect(NULL, FALSE);
}


void CInkRecoDlg::OnBnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	IInkStrokes *lIInkStrokes;
	g_IInkDisp->get_Strokes(&lIInkStrokes);

	g_IInkRecoContext->putref_Strokes(lIInkStrokes);

	IInkRecognitionResult *lIInkRecognitionResult;
	InkRecognitionStatus lInkRecognitionStatus;

	g_IInkRecoContext->Recognize(&lInkRecognitionStatus, &lIInkRecognitionResult);

	BSTR bstr;
	lIInkRecognitionResult->get_TopString(&bstr);

	MessageBox(bstr);

}

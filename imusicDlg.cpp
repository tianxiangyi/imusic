
// imusicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "imusic.h"
#include "imusicDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CimusicDlg 对话框




CimusicDlg::CimusicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CimusicDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CimusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);	
	//{{AFX_DATA_MAP(CEx_WaveDlg)
	DDX_Control(pDX, IDC_STOP, m_btnStop);
	DDX_Control(pDX, IDC_PLAY, m_btnPlay);
	DDX_Control(pDX, IDC_FILE, m_btnFile);
	DDX_Text(pDX, IDC_DISPFILE, m_strFileName);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CimusicDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()	
	ON_BN_CLICKED(IDC_FILE, &CimusicDlg::OnBnClickedFile)
	ON_BN_CLICKED(IDC_PLAY, &CimusicDlg::OnBnClickedPlay)
	ON_BN_CLICKED(IDC_STOP, &CimusicDlg::OnBnClickedStop)
	ON_BN_CLICKED(IDC_Exit, &CimusicDlg::OnBnClickedExit)	

END_MESSAGE_MAP()


// CimusicDlg 消息处理程序

BOOL CimusicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CimusicDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CimusicDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CimusicDlg::OnBnClickedFile()
{
	// TODO: 在此添加控件通知处理程序代码
	CString filter;
	filter="波形音频文件(*.mp3)|*.mp3||";//过滤文件
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY,filter);//第一个参数为TRUE是打开对话框
	if(dlg.DoModal ())
	{
		CString str;
		str=dlg.GetPathName ();//得到文件的完整路径
		if(m_music.Open(str))
		{
			m_btnPlay.EnableWindow (TRUE);
			m_btnPlay.SetFocus ();//该控件获得焦点
			m_strFileName=str;
			UpdateData(FALSE);//拷贝数据到控件上
		}
		else
			MessageBox(str+"文件打开失败!");
	}
}


void CimusicDlg::OnBnClickedPlay()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_music.Play(this))
	{
		m_btnPlay.EnableWindow (FALSE);
		m_btnStop.EnableWindow (TRUE);
		m_btnFile.EnableWindow (FALSE);
		m_btnStop.SetFocus ();
	}
}


void CimusicDlg::OnBnClickedStop()
{
	// TODO: 在此添加控件通知处理程序代码
	m_music.Stop();
	m_btnStop.EnableWindow (FALSE);
	m_btnPlay.EnableWindow (TRUE);
	m_btnFile.EnableWindow (TRUE);
	m_btnPlay.SetFocus ();
}


void CimusicDlg::OnBnClickedExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


// 101903Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "101903.h"
#include "101903Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy101903Dlg 对话框


CMy101903Dlg::CMy101903Dlg(CWnd* pParent /*=NULL*/)
    : CDialogEx(IDD_MY101903_DIALOG, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}


void CMy101903Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_RED, picRed);
    DDX_Control(pDX, IDC_YELLOW, picYellow);
    DDX_Control(pDX, IDC_GREEN, picGreen);

}

BEGIN_MESSAGE_MAP(CMy101903Dlg, CDialogEx)
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_STN_CLICKED(IDC_RED, &CMy101903Dlg::OnStnClickedRed)
    //    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CMy101903Dlg 消息处理程序

BOOL CMy101903Dlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
    //  执行此操作
    SetIcon(m_hIcon, TRUE);			// 设置大图标
    SetIcon(m_hIcon, FALSE);		// 设置小图标

                                    // TODO: 在此添加额外的初始化代码
    bitmapRed.LoadBitmap(IDB_BITMAPRED);
    bitmapGray.LoadBitmap(IDB_BITMAPGRAY);
    bitmapGreen.LoadBitmap(IDB_BITMAPGREEN);
    bitmapYellow.LoadBitmap(IDB_BITMAPYELLOW);
    hBmpGray = (HBITMAP)bitmapGray.GetSafeHandle();
    hBmpRed = (HBITMAP)bitmapRed.GetSafeHandle();
    hBmpGreen = (HBITMAP)bitmapGreen.GetSafeHandle();
    hBmpYellow = (HBITMAP)bitmapYellow.GetSafeHandle();
    picRed.SetBitmap(hBmpGray);
    picYellow.SetBitmap(hBmpGray);
    picGreen.SetBitmap(hBmpGray);

    th = std::thread(CMy101903Dlg::loopb, this);
    //th.join();

    return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy101903Dlg::OnPaint()
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
HCURSOR CMy101903Dlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}



void CMy101903Dlg::OnStnClickedRed()
{
    static bool light = true;
    if (true == light)
    {
        picRed.SetBitmap(hBmpGray);
        light = false;
    }
    else
    {
        picRed.SetBitmap(hBmpRed);
        light = false;
    }
    // TODO: 在此添加控件通知处理程序代码
}


//void CMy101903Dlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//    // TODO: 在此添加消息处理程序代码和/或调用默认值
//
//    CDialogEx::OnLButtonDown(nFlags, point);
//}


void CMy101903Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    loopa(this);
    CDialogEx::OnLButtonDown(nFlags, point);

}

void  CMy101903Dlg::loopa(CMy101903Dlg * _this)
{
    switch (_this->flag)
    {
    case 0:
        _this->picYellow.SetBitmap(_this->hBmpGray);
        _this->picRed.SetBitmap(_this->hBmpRed);
        _this->flag = 1;
        break;
    case 1:
        _this->picRed.SetBitmap(_this->hBmpGray);
        _this->picGreen.SetBitmap(_this->hBmpGreen);
        _this->flag = 2;
        break;
    case 2:
        _this->picGreen.SetBitmap(_this->hBmpGray);
        _this->picYellow.SetBitmap(_this->hBmpYellow);
        _this->flag = 0;
        break;
    }
    _this->Invalidate();

}

void CMy101903Dlg::loopb(CMy101903Dlg * _this)
{
    int count = 0;
    while (_this->contable) {
        loopa(_this);
        int time = 0;
        switch (count%3)
        {
        case 0:
            time = 4000; break;
        case 1:
            time = 3000; break;
        case 2:
            time = 500; break;
        }
        count++;
        Sleep(time);
    }
    return;
}

CMy101903Dlg::~CMy101903Dlg()
{
    contable = false;
    Sleep(1000);
    return;
}

// 101903Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "101903.h"
#include "101903Dlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy101903Dlg �Ի���


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


// CMy101903Dlg ��Ϣ�������

BOOL CMy101903Dlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);		// ����Сͼ��

                                    // TODO: �ڴ���Ӷ���ĳ�ʼ������
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

    return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy101903Dlg::OnPaint()
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
    // TODO: �ڴ���ӿؼ�֪ͨ����������
}


//void CMy101903Dlg::OnLButtonDown(UINT nFlags, CPoint point)
//{
//    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
//
//    CDialogEx::OnLButtonDown(nFlags, point);
//}


void CMy101903Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
    // TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

// 101903Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <thread>

// CMy101903Dlg �Ի���
class CMy101903Dlg : public CDialogEx
{
// ����
public:
	CMy101903Dlg(CWnd* pParent = NULL);	// ��׼���캯��
    ~CMy101903Dlg();
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY101903_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    CStatic picRed;
    afx_msg void OnStnClickedRed();
//    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    CBitmap bitmapGreen, bitmapRed, bitmapGray, bitmapYellow;
    HBITMAP hBmpGreen, hBmpRed, hBmpYellow, hBmpGray;
    CStatic picYellow;
    CStatic picGreen;
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    std::thread th;
    int flag = 0;
    //void(*loopb)(void);
    static void loopa(CMy101903Dlg *);
    static void loopb(CMy101903Dlg *);
    bool contable = true;
};

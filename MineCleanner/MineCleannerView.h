
// MineCleanView.h : CMineCleanView ��Ľӿ�
//

#pragma once
#include "afxwin.h"
#include "resource.h"



class CMineCleannerView : public CView
{
protected: // �������л�����
	CMineCleannerView();
	DECLARE_DYNCREATE(CMineCleannerView)

	// ����
public:
	CMineCleannerDoc* GetDocument() const;
	struct Mine {
		int iBitMap;
		int iArondMineNum;
	};
	CDC * m_dc;
	CListBox *edit;
	int secondstart;
	CBitmap m_Bmp[14];
	Mine m_Mine[10][10];
	int second;//��ʱ
	int mine;
	int right;
	// ����
public:
	void OnInitializeMine(bool bIsSelfDefine);
	void show(int tx,int ty);
	void GameOver();
	void youwin();
	// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// ʵ��
public:
	virtual ~CMineCleannerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnExit();
	afx_msg void OnStart();
	afx_msg void OnBtnDown();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MineCleanView.cpp �еĵ��԰汾
inline CMineCleanDoc* CMineCleanView::GetDocument() const
{
	return reinterpret_cast<CMineCleanDoc*>(m_pDocument);
}
#endif


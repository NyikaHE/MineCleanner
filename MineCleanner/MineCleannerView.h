
// MineCleanView.h : CMineCleanView 类的接口
//

#pragma once
#include "afxwin.h"
#include "resource.h"



class CMineCleannerView : public CView
{
protected: // 仅从序列化创建
	CMineCleannerView();
	DECLARE_DYNCREATE(CMineCleannerView)

	// 特性
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
	int second;//计时
	int mine;
	int right;
	// 操作
public:
	void OnInitializeMine(bool bIsSelfDefine);
	void show(int tx,int ty);
	void GameOver();
	void youwin();
	// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 实现
public:
	virtual ~CMineCleannerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 生成的消息映射函数
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

#ifndef _DEBUG  // MineCleanView.cpp 中的调试版本
inline CMineCleanDoc* CMineCleanView::GetDocument() const
{
	return reinterpret_cast<CMineCleanDoc*>(m_pDocument);
}
#endif


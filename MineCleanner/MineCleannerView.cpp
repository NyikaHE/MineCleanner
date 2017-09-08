
// MineCleanView.cpp : CMineCleanView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MineCleanner.h"
#endif

#include "MineCleannerDoc.h"
#include "MineCleannerView.h"
#include "Resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#define m_ColCount 10
#define m_RowCount 10
#define m_iMineNum 20
#endif


// CMineCleanView

IMPLEMENT_DYNCREATE(CMineCleannerView, CView)

BEGIN_MESSAGE_MAP(CMineCleannerView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_COMMAND(ID_Exit, &CMineCleannerView::OnExit)
	ON_COMMAND(ID_Start, &CMineCleannerView::OnStart)
	ON_WM_RBUTTONDOWN()
	ON_BN_CLICKED(ID_BUTTON, OnBtnDown)
END_MESSAGE_MAP()


// CMineCleanView ����/����

CMineCleannerView::CMineCleannerView()
{
	// TODO: �ڴ˴���ӹ������
	m_Bmp[0].LoadMappedBitmap(IDB_BITMAP1);
	m_Bmp[1].LoadMappedBitmap(IDB_BITMAP2);
	m_Bmp[2].LoadMappedBitmap(IDB_BITMAP3);
	m_Bmp[3].LoadMappedBitmap(IDB_BITMAP4);
	m_Bmp[4].LoadMappedBitmap(IDB_BITMAP5);
	m_Bmp[5].LoadMappedBitmap(IDB_BITMAP6);
	m_Bmp[6].LoadMappedBitmap(IDB_BITMAP7);
	m_Bmp[7].LoadMappedBitmap(IDB_BITMAP8);
	m_Bmp[8].LoadMappedBitmap(IDB_BITMAP9);
	m_Bmp[9].LoadMappedBitmap(IDB_BITMAP10);
	m_Bmp[10].LoadMappedBitmap(IDB_BITMAP11);
	m_Bmp[11].LoadMappedBitmap(IDB_BITMAP12);
	m_Bmp[12].LoadMappedBitmap(IDB_BITMAP13);
	m_Bmp[13].LoadMappedBitmap(IDB_BITMAP14);
	second = 0;
	secondstart = 0;
	mine = 0;
	right = 0;
	
	for(int i=0;i<m_ColCount;i++)
		for (int j = 0; j < m_RowCount; j++) {
			m_Mine[i][j].iArondMineNum = 0;
			m_Mine[i][j].iBitMap = 0;
		}
	OnInitializeMine(true);
	
}

CMineCleannerView::~CMineCleannerView()
{
}

BOOL CMineCleannerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return CView::PreCreateWindow(cs);
}

// CMineCleanView ����

void CMineCleannerView::OnInitializeMine(bool bIsSelfDefine)
{
	int aa = 0;
	srand((unsigned)time(0));
	//����m_iMineNum����  
	do
	{
		//�Ե�ǰ����Ϊ��������㷨  
		int k = (rand()) % m_ColCount;
		int l = (rand()) % m_RowCount;
		//Ϊ�˱���һ��λ��ͬʱ��������  
		//ֻ����ǰλ�ò�����ʱ��ֵΪ��  
		if (m_Mine[k][l].iArondMineNum != -1)
		{
			//���λ������  
			m_Mine[k][l].iArondMineNum = -1;
			aa++;
		}
	} while (aa != m_iMineNum);

	//������ֵ����������  
	for (int a = 0; a < m_ColCount; a++)
	{
		for (int b = 0; b < m_RowCount; b++)
		{
			if (m_Mine[a][b].iArondMineNum == 0)
			{
				for (int c = a - 1; c < a + 2; c++)
				{
					for (int d = b - 1; d < b + 2; d++)
					{
						if (c >= 0 && c < m_ColCount && d >= 0 && d < m_RowCount)
						{
							if (m_Mine[c][d].iArondMineNum == -1)
							{
								m_Mine[a][b].iArondMineNum++;
							}
						}
					}
				}
			}
		}
	}
}

void CMineCleannerView::show(int tx, int ty)
{
	m_dc = this->GetDC();
	CDC memdc;
	if (m_Mine[tx][ty].iArondMineNum == 0) {
		memdc.CreateCompatibleDC(m_dc);
		memdc.SelectObject(&m_Bmp[0]);
		m_dc->BitBlt(tx * 30 + 35, ty * 30 + 50, 30, 30, &memdc, 0, 0, SRCCOPY);
		m_Mine[tx][ty].iBitMap = 1;
		for (int i = tx-1;i<tx+2&&i>=0&& i < m_ColCount; i++) 
			for (int j = ty - 1; j < ty + 2 && j >= 0 && j < m_RowCount; j++) {
				if(m_Mine[i][j].iBitMap != 1)
				show(i, j);
			}
	}
	else {
		memdc.CreateCompatibleDC(m_dc);
		memdc.SelectObject(&m_Bmp[m_Mine[tx][ty].iArondMineNum]);
		m_dc->BitBlt(tx * 30 + 35, ty * 30 + 50, 30, 30, &memdc, 0, 0, SRCCOPY);
		m_Mine[tx][ty].iBitMap = 1;
	}
}


void CMineCleannerView::OnDraw(CDC* pDC)
{
	CMineCleannerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	
	CBrush mybrush;
	mybrush.CreateSolidBrush(RGB(125, 125, 247));
	CRect myrect(0, 0, 500, 500); //��ӱ���������  
	pDC->FillRect(myrect, &mybrush);
	CPen mypen;
	CPen*myoldPen;
	mypen.CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	myoldPen = pDC->SelectObject(&mypen);
	for (int i = 0; i < m_ColCount; i++)
	{
		for (int j = 0; j < m_RowCount; j++)
		{
			pDC->MoveTo(35 + i * 30, 50 + j * 30 + 30);
			pDC->LineTo(35 + i * 30, 50 + j * 30);
			pDC->LineTo(35 + i * 30 + 30, 50 + j * 30);
		}
	}
	pDC->SelectObject(myoldPen);
	//���½Ǻ���  
	CPen mypen2;
	CPen*myoldPen2;
	mypen2.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	myoldPen2 = pDC->SelectObject(&mypen2);
	for (int ii = 0; ii < m_ColCount; ii++)
	{
		for (int jj = 0; jj < m_RowCount; jj++)
		{
			pDC->MoveTo(35 + ii * 30, 50 + jj * 30 + 30);
			pDC->LineTo(35 + ii * 30 + 30, 50 + jj * 30 + 30);
			pDC->LineTo(35 + ii * 30 + 30, 50 + jj * 30);
		}
	}
	pDC->SelectObject(myoldPen2);
	
}
	
void CMineCleannerView::GameOver()
{
	int aa;	
	for(int i=0;i<m_ColCount;i++)
		for (int j = 0; j < m_RowCount; j++) {		
			if (m_Mine[i][j].iArondMineNum != -1)
				aa = m_Mine[i][j].iArondMineNum;
			else
				aa = 10;
			m_dc = this->GetDC();
			CDC memdc;
			memdc.CreateCompatibleDC(m_dc);
			memdc.SelectObject(&m_Bmp[aa]);
			m_dc->BitBlt(i * 30 + 35, j * 30 + 50, 30, 30, &memdc, 0, 0, SRCCOPY);
		}
	CString str = _T("���˧��Ȼ�����Ѿ�������ը���ˣ���������");
	m_dc->TextOut(35, 400, str);
	KillTimer(1);
	second = -1;
}
void CMineCleannerView::youwin()
{
	CString str = _T("�ðɣ����˧����ʰ���׶�ûը���㣬����ݣ���������");
	m_dc->TextOut(35, 400, str);
	KillTimer(1);
}
// CMineCleanView ��ӡ

BOOL CMineCleannerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMineCleannerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMineCleannerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CMineCleanView ���

#ifdef _DEBUG
void CMineCleannerView::AssertValid() const
{
	CView::AssertValid();
}

void CMineCleannerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMineCleannerDoc* CMineCleannerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMineCleannerDoc)));
	return (CMineCleannerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMineCleanView ��Ϣ�������

int CMineCleannerView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	CListBox *edit = new CListBox();
	CRect rect_edit(30, 10, 140, 40);
	edit->Create(ES_AUTOVSCROLL | ES_CENTER | ES_READONLY, rect_edit, this, ID_EDITBOX);
	edit->ShowWindow(SW_SHOWNORMAL);
	SetTimer(1, 1000, NULL);
	
	CButton *B_begin=new CButton();	
	CRect rect_button(150, 10, 200, 40);   //���ư�ť��С��λ��
	B_begin->Create(_T("Start"), WS_CHILD | WS_VISIBLE | WS_BORDER, rect_button, this, ID_BUTTON);
	B_begin->ShowWindow(SW_SHOWNORMAL);
	return 0;
}

void CMineCleannerView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int ax, ay,ii;
	ax = (point.x - 35) / 30;
	ay = (point.y - 50) / 30;
	if (ay < 10 && ax < 10&&point.x>=35&&point.y>=50) {
		if (m_Mine[(point.x - 35) / 30][(point.y - 50) / 30].iArondMineNum != -1) {
			show(ax, ay);
		}
		else
			GameOver();
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CMineCleannerView::OnTimer(UINT_PTR nIDEvent)
{
	if (secondstart>0)
		secondstart++;
	//��ʮ��Ϊһ��
	if (secondstart == 2)
	{
		secondstart = 1;
		second++;
		//�ػ�ʱ��
		CRect rect3;
		rect3.left = 325;
		rect3.right = 375;
		rect3.top = 10;
		rect3.bottom = 40;
		InvalidateRect(&rect3);
	}
	CView::OnTimer(nIDEvent);
}


void CMineCleannerView::OnExit()
{
	// TODO: �ڴ���������������
	AfxGetMainWnd()->PostMessage(WM_CLOSE, 0, 0);
}


void CMineCleannerView::OnStart()
{
	// TODO: �ڴ���������������
	second = 0;
	secondstart = 0;
	SetTimer(1, 1000, NULL);
	for (int i = 0; i<m_ColCount; i++)
		for (int j = 0; j < m_RowCount; j++) {
			m_Mine[i][j].iArondMineNum = 0;
			m_Mine[i][j].iBitMap = 0;
		}
	mine = 0;
	right = 0;
	OnInitializeMine(true);
	Invalidate();
}

void CMineCleannerView::OnBtnDown()
{
	second = 0;
	SetTimer(1, 1000, NULL);
	for (int i = 0; i<m_ColCount; i++)
		for (int j = 0; j < m_RowCount; j++) {
			m_Mine[i][j].iArondMineNum = 0;
			m_Mine[i][j].iBitMap = 0;
		}
	mine = 0;
	right = 0;
	OnInitializeMine(true);
	Invalidate();
}


void CMineCleannerView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��
	int ax, ay, ii;
	m_dc = this->GetDC();
	ax = (point.x - 35) / 30;
	ay = (point.y - 50) / 30;
	CDC memdc;
	if (ay < 10 && ax < 10 && point.x >= 35 && point.y >= 50) {
			ii = m_Mine[(point.x - 35) / 30][(point.y - 50) / 30].iArondMineNum;
			memdc.CreateCompatibleDC(m_dc);
			memdc.SelectObject(&m_Bmp[11]);
			m_dc->BitBlt(ax * 30 + 35, ay * 30 + 50, 30, 30, &memdc, 0, 0, SRCCOPY);
			mine++;
			if (m_Mine[ax][ay].iArondMineNum == -1) right++;
		}
	if (right == m_iMineNum) youwin();
	if (mine >= 25) GameOver();
	CView::OnRButtonDown(nFlags, point);
}

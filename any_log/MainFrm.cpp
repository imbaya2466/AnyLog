// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////


#include <fstream>

#include "stdafx.h"
#include "resource.h"

#include "aboutdlg.h"
#include "View.h"
#include "MainFrm.h"
#include "format_dlg.h"


BOOL CMainFrame::PreTranslateMessage(MSG* pMsg)
{
	if(CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg))
		return TRUE;

	return m_view.PreTranslateMessage(pMsg);
}

BOOL CMainFrame::OnIdle()
{
	UIUpdateToolBar();
	return FALSE;
}

LRESULT CMainFrame::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// create command bar window
	HWND hWndCmdBar = m_CmdBar.Create(m_hWnd, rcDefault, NULL, ATL_SIMPLE_CMDBAR_PANE_STYLE);
	// attach menu
	m_CmdBar.AttachMenu(GetMenu());
	// load command bar images
	m_CmdBar.LoadImages(IDR_MAINFRAME);
	// remove old menu
	SetMenu(NULL);

	HWND hWndToolBar = CreateSimpleToolBarCtrl(m_hWnd, IDR_MAINFRAME, FALSE, ATL_SIMPLE_TOOLBAR_PANE_STYLE);

	CreateSimpleReBar(ATL_SIMPLE_REBAR_NOBORDER_STYLE);
	AddSimpleReBarBand(hWndCmdBar);
	AddSimpleReBarBand(hWndToolBar, NULL, TRUE);

	CreateSimpleStatusBar();

	m_hWndClient = m_view.Create(m_hWnd, rcDefault, NULL, WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, WS_EX_CLIENTEDGE);

	UIAddToolBar(hWndToolBar);
	UISetCheck(ID_VIEW_TOOLBAR, 1);
	UISetCheck(ID_VIEW_STATUS_BAR, 1);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	CMenuHandle menuMain = m_CmdBar.GetMenu();
	m_view.SetWindowMenu(menuMain.GetSubMenu(WINDOW_MENU_POSITION));

	//read db
  format_manage_.ReadDB();

	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	// unregister message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->RemoveMessageFilter(this);
	pLoop->RemoveIdleHandler(this);

  //write db
  format_manage_.WriteDB();

  m_view.RemoveAllPages();
	bHandled = FALSE;
	return 1;
}

LRESULT CMainFrame::OnFileExit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	PostMessage(WM_CLOSE);
	return 0;
}

LRESULT CMainFrame::OnFileNew(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{

  if (!format_manage_.Ready()){
    FormatDlg dlg(format_manage_);
    dlg.DoModal();
    return 0;
  }

  OPENFILENAME ofn = { 0 };
  TCHAR strFilename[MAX_PATH] = { 0 };
  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.hwndOwner = NULL;
  ofn.lpstrFilter = TEXT("log\0*.log\0\0");
  ofn.nFilterIndex = 1;
  ofn.lpstrFile = strFilename;
  ofn.nMaxFile = sizeof(strFilename);
  ofn.lpstrInitialDir = NULL;
  ofn.lpstrTitle = TEXT("请选择一个文件");
  ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY;
  if (GetOpenFileName(&ofn)){
    CteatFileTabView(strFilename);
  }
	return 0;
}

LRESULT CMainFrame::OnOpenForamt(WORD, WORD, HWND, BOOL &)
{
  FormatDlg dlg(format_manage_);
  dlg.DoModal();
  return 0;
}

LRESULT CMainFrame::OnViewToolBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	static BOOL bVisible = TRUE;	// initially visible
	bVisible = !bVisible;
	CReBarCtrl rebar = m_hWndToolBar;
	int nBandIndex = rebar.IdToIndex(ATL_IDW_BAND_FIRST + 1);	// toolbar is 2nd added band
	rebar.ShowBand(nBandIndex, bVisible);
	UISetCheck(ID_VIEW_TOOLBAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnViewStatusBar(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BOOL bVisible = !::IsWindowVisible(m_hWndStatusBar);
	::ShowWindow(m_hWndStatusBar, bVisible ? SW_SHOWNOACTIVATE : SW_HIDE);
	UISetCheck(ID_VIEW_STATUS_BAR, bVisible);
	UpdateLayout();
	return 0;
}

LRESULT CMainFrame::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CAboutDlg dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainFrame::OnWindowClose(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nActivePage = m_view.GetActivePage();
	if(nActivePage != -1)
		m_view.RemovePage(nActivePage);
	else
		::MessageBeep((UINT)-1);

	return 0;
}

LRESULT CMainFrame::OnWindowCloseAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	m_view.RemoveAllPages();

	return 0;
}

LRESULT CMainFrame::OnWindowActivate(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nPage = wID - ID_WINDOW_TABFIRST;
	m_view.SetActivePage(nPage);

	return 0;
}

LRESULT CMainFrame::OnChangeBackground(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  int index=m_view.GetActivePage();
  if (index < 0) {
    return 0;
  }
  CView* pcview = (CView*)m_view.GetPageData(index);
  if (wID == ID_TOOLBAR_BLACK){
    pcview->SetBackgroundColour(RGB(0x30, 0x30, 0x30));
  }
  else{
    pcview->SetBackgroundColour(RGB(0xF2, 0xF3, 0xF5));
  }
  pcview->RedrawWindow();

  return 0;
}

LRESULT CMainFrame::OnDropFiels(UINT, WPARAM wParam, LPARAM, BOOL &)
{
  HDROP hDrop = (HDROP)wParam;
  char strFileName[MAX_PATH];
  DragQueryFile(hDrop, 0, strFileName, MAX_PATH);
  DragFinish(hDrop);

  CteatFileTabView(strFileName);
  return 0;
}

LRESULT CMainFrame::OnTabViewContextMenu(int /*idCtrl*/, LPNMHDR pnmh, BOOL& /*bHandled*/)
{
	LPTBVCONTEXTMENUINFO lpcmi = (LPTBVCONTEXTMENUINFO)pnmh;
	CMenuHandle menuMain = m_CmdBar.GetMenu();
	CMenuHandle menuPopup = menuMain.GetSubMenu(WINDOW_MENU_POSITION);	// Window sub menu
	int nRet = (int)m_CmdBar.TrackPopupMenu(menuPopup, TPM_RETURNCMD | TPM_LEFTALIGN | TPM_RIGHTBUTTON, lpcmi->pt.x, lpcmi->pt.y);
	if (nRet == ID_WINDOW_CLOSE)
		m_view.RemovePage(pnmh->idFrom);
	else
		SendMessage(WM_COMMAND, MAKEWPARAM(nRet, 0));

	return 0;
}

void CMainFrame::CteatFileTabView(std::string file)
{
  std::ifstream *pstream = new std::ifstream();
  pstream->open(file);
  if (!(*pstream)) {
    return ;
  }
  CView* pView = new CView(format_manage_.GetChooseFormat(), pstream);
  pView->Create(m_view);
  m_view.AddPage(pView->m_hWnd, file.c_str(), -1, (void*)pView);
  pView->SetBackgroundColour(RGB(0xF2, 0xF3, 0xF5));
  pView->RedrawWindow();
}













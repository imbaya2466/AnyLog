// View.h : interface of the CView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include "middle_layer.h"

class CView : public CDialogImpl<CView>
{
public:
	enum { IDD = IDD_ANY_LOG_FORM };
  static const int MAX_FIRST_READ = 500;
  static const int MAX_ONCE_READ = 20;
  static const int SLEEP_ONCE_READ = 20;
  static const int MAX_STRING = 512;

	BOOL PreTranslateMessage(MSG* pMsg);

	virtual void OnFinalMessage(HWND /*hWnd*/);
  CView(LogFormat &format, std::istream *pstream) :format_(format),pstream_(pstream), control_(format,*pstream){}
  ~CView();

	BEGIN_MSG_MAP(CView)
    MSG_WM_INITDIALOG(OnInitDialog)
    MESSAGE_HANDLER(WM_SIZE, OnSize)
    //List message
    NOTIFY_HANDLER(IDC_VIEW_LIST, LVN_GETDISPINFO, OnLvnGetdispinfoList)
    NOTIFY_HANDLER(IDC_VIEW_LIST, LVN_ENDSCROLL, OnLvnEndScrollList)
	  //button
    COMMAND_HANDLER(IDC_VIEW_BUTTON, BN_CLICKED, OnBnClickedButton)
    //combo change
    COMMAND_HANDLER(IDC_VIEW_COMBO, CBN_SELCHANGE, OnCbnSelchangeCombo)
    //little custome draw
    NOTIFY_HANDLER(IDC_VIEW_LIST, NM_CUSTOMDRAW, OnNMCustomdrawList)
    //left double click
    NOTIFY_HANDLER(IDC_VIEW_LIST, NM_DBLCLK, OnNMDblclkList)
    //right click
    NOTIFY_HANDLER(IDC_VIEW_LIST, NM_RCLICK, OnNMRclickViewList)
    COMMAND_ID_HANDLER(ID_RCLICK_MARK, OnRclickMenu)
    COMMAND_ID_HANDLER(ID_RCLICK_COPY, OnRclickMenu)
    COMMAND_ID_HANDLER(ID_RCLICK_INTERVAL_FROM, OnRclickMenu)
    COMMAND_ID_HANDLER(ID_RCLICK_INTERVAL_TO, OnRclickMenu)
    COMMAND_ID_HANDLER(ID_RCLICK_MORE_INFO, OnRclickMenu)
  END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)




  CComboBox    level_box_;
  CEdit        search_edit_;
  CButton      regex_check_;
  CButton      search_button_;

  CListViewCtrl list_;
  CEdit        copy_edit_;

  MiddleLayer	control_;			
  HANDLE h_thread_ = 0;					
  HANDLE mutex_ = 0;						
  bool thread_run_ = false;			
  int showed_num_ = 0;				
  int showed_old_num_ = 0;

  std::istream *pstream_;
  LogFormat format_;

  static DWORD WINAPI ThreadProc(LPVOID lpParam);

  LRESULT OnInitDialog(HWND hwndFocus, LPARAM lParam);
  LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
  LRESULT OnLvnGetdispinfoList(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
  LRESULT OnLvnEndScrollList(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
  LRESULT OnBnClickedButton(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnCbnSelchangeCombo(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnNMCustomdrawList(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
  LRESULT OnNMDblclkList(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
  LRESULT OnNMRclickViewList(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);
  LRESULT OnRclickMenu(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

  void ScrollTo(int line);
  void SetBackgroundColour(COLORREF in_colour);
  
};

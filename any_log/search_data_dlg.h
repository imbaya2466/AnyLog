/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: search_data dlg
 * Description: view of search dlg
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
 */
#pragma once

#include "View.h"
#include "filter_data_manage.h"

class SearchDataDlg : public CDialogImpl<SearchDataDlg> {
 public:
  enum { IDD = IDD_DIALOG_SEARCH };

  SearchDataDlg(std::vector<FilterData>& data, CView* pcview)
      : data_(data), pcview_(pcview) {}

  BEGIN_MSG_MAP(SearchDataDlg)
  MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
  MESSAGE_HANDLER(WM_CLOSE, OnClose)
  COMMAND_HANDLER(IDC_SEARCHDLG_ADDNOW, BN_CLICKED, OnBnClickedAdd)
  COMMAND_HANDLER(IDC_SEARCHDLG_ADDNEW, BN_CLICKED, OnBnClickedAdd)
  COMMAND_HANDLER(ID_SEARCHDLG_CANCEL, BN_CLICKED, OnBnClickedCancel)
  COMMAND_HANDLER(IDC_SEARCHDLG_DELETE, BN_CLICKED, OnBnClickedDelete)
  COMMAND_HANDLER(ID_SEARCHDLG_OK, BN_CLICKED, OnBnClickedOk)
  NOTIFY_HANDLER(IDC_SEARCHDLG_LIST, LVN_GETDISPINFO, OnLvnGetdispinfoList)
  END_MSG_MAP()

  // Handler prototypes (uncomment arguments if needed):
  //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM
  ///*lParam*/, BOOL& /*bHandled*/) 	LRESULT CommandHandler(WORD
  ////*wNotifyCode*/,
  // WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/) 	LRESULT
  // NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

  LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/,
                       BOOL& /*bHandled*/);
  LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/,
                  BOOL& /*bHandled*/);
  LRESULT OnBnClickedAdd(WORD /*wNotifyCode*/, WORD /*wID*/,
                               HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedCancel(WORD /*wNotifyCode*/, WORD /*wID*/,
                                  HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedDelete(WORD /*wNotifyCode*/, WORD /*wID*/,
                                  HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/,
                              HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnLvnGetdispinfoList(int /*idCtrl*/, LPNMHDR pNMHDR,
                                     BOOL& /*bHandled*/);

  CListViewCtrl list_;
  std::vector<FilterData> &data_;
  CView* pcview_;
};
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

#include "filter_data.h"

class SearchNewDataDlg : public CDialogImpl<SearchNewDataDlg> {
 public:
  enum { IDD = IDD_DIALOG_SEARCH_NEWDATA };

  SearchNewDataDlg(FilterData& data) : data_(data) {}

  BEGIN_MSG_MAP(SearchNewDataDlg)
  MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
  MESSAGE_HANDLER(WM_CLOSE, OnClose)
  COMMAND_HANDLER(ID_SEANEWDATA_CANCEL, BN_CLICKED, OnBnClickedCancel)
  COMMAND_HANDLER(ID_SEANEWDATA_OK, BN_CLICKED, OnBnClickedOk)
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
  LRESULT OnBnClickedCancel(WORD /*wNotifyCode*/, WORD /*wID*/,
                            HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedOk(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/,
                        BOOL& /*bHandled*/);

  FilterData& data_;
  CEdit edit_name_;
  CEdit edit_val_;
  CButton regex_;
};
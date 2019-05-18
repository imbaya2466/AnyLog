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

#include "resource.h"
#include "stdafx.h"
#include "tool.h"

#include "search_newdata_dlg.h"

LRESULT SearchNewDataDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &) {
  edit_name_.Attach(GetDlgItem(ID_SEANEWDATA_EDIT1));
  edit_val_.Attach(GetDlgItem(ID_SEANEWDATA_EDIT2));
  regex_.Attach(GetDlgItem(ID_SEANEWDATA_CHECK));

  CenterWindow(GetParent());
  return true;
}

LRESULT SearchNewDataDlg::OnClose(UINT, WPARAM wParam, LPARAM, BOOL &) {
  EndDialog(LOWORD(wParam));
  return 0;
}

LRESULT SearchNewDataDlg::OnBnClickedCancel(WORD, WORD id, HWND, BOOL &) {
  EndDialog(id);
  return 0;
}

LRESULT SearchNewDataDlg::OnBnClickedOk(WORD, WORD id, HWND, BOOL &) {
  TCHAR sz_string[512];
  edit_name_.GetLine(0, sz_string, 512);
  data_.name = sz_string;
  edit_val_.GetLine(0, sz_string, 512);
  data_.val=sz_string;
  int regex_check = regex_.GetCheck();
  data_.regex = regex_check;

  EndDialog(id);
  return 0;
}

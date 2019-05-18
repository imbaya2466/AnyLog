/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: input name dlg
 * Description: input name dlg
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
 */

#include "resource.h"
#include "stdafx.h"

#include "input_name_dlg.h"

LRESULT InputNameDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &) {
  edit_.Attach(GetDlgItem(ID_NAMEDLG_EDIT));

  CenterWindow(GetParent());
  return true;
}

LRESULT InputNameDlg::OnClose(UINT, WPARAM wParam, LPARAM, BOOL &) {
  EndDialog(LOWORD(wParam));
  return 0;
}

LRESULT InputNameDlg::OnBnClickedCancel(WORD, WORD id, HWND, BOOL &) {
  EndDialog(id);
  return 0;
}

LRESULT InputNameDlg::OnBnClickedOk(WORD, WORD id, HWND, BOOL &) {

  CHAR sz_string[512];
  edit_.GetLine(0, sz_string, 512);
  name_ = sz_string;
  EndDialog(id);
  return 0;
}

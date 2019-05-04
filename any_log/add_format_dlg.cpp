/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: add_format_dlg
 * Description: view of add format
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/

#include "stdafx.h"
#include "resource.h"
#include "tool.h"

#include "add_format_dlg.h"

LRESULT AddFormatDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &)
{
  check_box_interval_.Attach(GetDlgItem(IDC_CHECK1_ADDFORMAT));
  check_box_level_.Attach(GetDlgItem(IDC_CHECK2_ADDFORMAT));
  edit_name_.Attach(GetDlgItem(IDC_EDIT1_ADDFORMAT));
  edit_regex_.Attach(GetDlgItem(IDC_EDIT2_ADDFORMAT));
  edit_colmun_.Attach(GetDlgItem(IDC_EDIT3_ADDFORMAT));
  edit_interval_.Attach(GetDlgItem(IDC_EDIT4_ADDFORMAT));
  edit_level_.Attach(GetDlgItem(IDC_EDIT5_ADDFORMAT));
  edit_level_text_.Attach(GetDlgItem(IDC_EDIT6_ADDFORMAT));

  CenterWindow(GetParent());
  return true;
}


LRESULT AddFormatDlg::OnClose(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
  EndDialog(LOWORD(wParam));
  return 0;
}


LRESULT AddFormatDlg::OnBnClickedOkAddformat(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  LogFormat add_log_format;
  TCHAR sz_string[MAX_PATH];

  edit_name_.GetLine(0, sz_string, MAX_PATH);
  add_log_format.format_name = sz_string;
  edit_regex_.GetLine(0, sz_string, MAX_PATH);
  add_log_format.regex = sz_string;
  edit_colmun_.GetLine(0, sz_string, MAX_PATH);
  add_log_format.column_name = tool::SplitString(sz_string,";");

  int check = check_box_interval_.GetCheck();
  if (check > 0) {
    edit_interval_.GetLine(0, sz_string, MAX_PATH);
    add_log_format.index_column_interval = atoi(sz_string);
  }
  else {
    add_log_format.index_column_interval = -1;
  }

  check = check_box_level_.GetCheck();
  if (check > 0) {
    edit_level_.GetLine(0, sz_string, MAX_PATH);
    add_log_format.index_column_level = atoi(sz_string);
    edit_level_text_.GetLine(0, sz_string, MAX_PATH);;
    add_log_format.level_text= tool::SplitString(sz_string, ";");
  }
  else {
    add_log_format.index_column_level = -1;
  }
  format_manage_.AddFormat(add_log_format);

  EndDialog(wID);
  return 0;
}


LRESULT AddFormatDlg::OnBnClickedCancelAddformat(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  EndDialog(wID);
  return 0;
}


LRESULT AddFormatDlg::OnBnClickedCheck1Addformat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  static bool check1_choose= false;
  check1_choose = !check1_choose;
  edit_interval_.EnableWindow(check1_choose);
  return 0;
}


LRESULT AddFormatDlg::OnBnClickedCheck2Addformat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  static bool check2_choose = false;
  check2_choose = !check2_choose;
  edit_level_.EnableWindow(check2_choose);
  edit_level_text_.EnableWindow(check2_choose);
  return 0;
}

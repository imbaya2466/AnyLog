/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: log more info dlg
 * Description: show more log info
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/

#include "stdafx.h"
#include "resource.h"
#include "tool.h"

#include "log_more_info_dlg.h"

#include <string>
#include <regex>

LRESULT LogMoreInfoDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &)
{
  log_edit_.Attach(GetDlgItem(IDC_EDIT_MOREINFO));
  out_edit_.Attach(GetDlgItem(IDC_EDIT_MOREINFO_OUT));

  log_edit_.SetWindowTextA(log_.get_log().c_str());

  CenterWindow(GetParent());
  return true;
}

LRESULT LogMoreInfoDlg::OnClose(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
  EndDialog(LOWORD(wParam));
  return 0;
}

LRESULT LogMoreInfoDlg::OnBnClickedBinConver(WORD, WORD, HWND, BOOL &)
{
  std::regex e("(0x[ABCDEFabcdef0-9]*)");
  std::smatch m;
  std::string s = log_.get_log();

  std::string ret;
  while (std::regex_search(s, m, e)) {
    ret += m.str(0) + ":";
    ret += tool::SHextoDec(m.str(0)) + "   ";
    s = m.suffix().str();
  }
  out_edit_.SetWindowTextA(ret.c_str());
  return 0;
}

LRESULT LogMoreInfoDlg::OnBnClickedErroeMsg(WORD, WORD, HWND, BOOL &)
{
  // TODO error message
  return 0;
}

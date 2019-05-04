/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: format_dlg
 * Description: view of format curd
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/


#include "stdafx.h"
#include "resource.h"
#include "tool.h"

#include "format_dlg.h"
#include "add_format_dlg.h"



LRESULT FormatDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &)
{
  VC_format_list_.Attach(GetDlgItem(IDC_LIST_FORMAT));

  VC_format_list_.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 50, 0);
  VC_format_list_.InsertColumn(1, _T("Regex"), LVCFMT_LEFT, 150, 1);
  VC_format_list_.InsertColumn(2, _T("Column"), LVCFMT_LEFT, 100, 2);
  VC_format_list_.InsertColumn(3, _T("Interval"), LVCFMT_LEFT, 50, 3);
  VC_format_list_.InsertColumn(4, _T("Level"), LVCFMT_LEFT, 50, 4);
  VC_format_list_.InsertColumn(5, _T("Level-text"), LVCFMT_LEFT, 100, 5);
  
  VC_format_list_.SetItemCount(format_manage_.size());
  VC_format_list_.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE);
  VC_format_list_.SetHotCursor(LoadCursor(NULL, IDC_ARROW));

  CenterWindow(GetParent());
  return true;
}

LRESULT FormatDlg::OnClose(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
  EndDialog(LOWORD(wParam));
  return 0;
}


LRESULT FormatDlg::OnBnClickedAddFormat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  AddFormatDlg dlg(format_manage_);
  dlg.DoModal();
  VC_format_list_.SetItemCount(format_manage_.size());
  VC_format_list_.RedrawWindow();
  return 0;
}


LRESULT FormatDlg::OnBnClickedCancelFormat(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  EndDialog(wID);
  return 0;
}


LRESULT FormatDlg::OnBnClickedDeleteFormat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  int select = VC_format_list_.GetNextItem(-1, LVNI_FOCUSED);
  if (select < 0) {
    return 0;
  }
  format_manage_.DeleteFormatIndex(select);
  VC_format_list_.SetItemCount(format_manage_.size());
  VC_format_list_.RedrawWindow();
  return 0;
}


LRESULT FormatDlg::OnBnClickedOkFormat(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
  int select = VC_format_list_.GetNextItem(-1, LVNI_FOCUSED);
  if (select < 0) {
    return 0;
  }
  format_manage_.set_choose_format(select);
  EndDialog(wID);
  return 0;
}


LRESULT FormatDlg::OnLvnGetdispinfoListFormat(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
  NMLVDISPINFO *lpdi = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);

  if (lpdi->item.iItem >= format_manage_.size()) {
    return 0;
  }
  LogFormat &log_format = format_manage_.GetFormat(lpdi->item.iItem);

  if (lpdi->item.iSubItem){
    if (lpdi->item.mask & LVIF_TEXT){
      switch (lpdi->item.iSubItem){
        case 1:{
          _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
            log_format.regex.c_str(), _TRUNCATE);
          break;
        }
        case 2:{
          _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
            tool::LinkStringVector(log_format.column_name, ";").c_str(), _TRUNCATE);
          break;
        }
        case 3:{
          _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
            std::to_string(log_format.index_column_interval).c_str(), _TRUNCATE);
          break;
        }
        case 4:{
          _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
            std::to_string(log_format.index_column_level).c_str(), _TRUNCATE);
          break;
        }
        case 5:{
          _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
            tool::LinkStringVector(log_format.level_text, ";").c_str(), _TRUNCATE);
          break;
        }
      }

    }
  }
  else
  {
    if (lpdi->item.mask & LVIF_TEXT){
      _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
        log_format.format_name.c_str(), _TRUNCATE);
    }
    if (lpdi->item.mask & LVIF_IMAGE){
      lpdi->item.iImage = 0;
    }
  }

  return 0;
}

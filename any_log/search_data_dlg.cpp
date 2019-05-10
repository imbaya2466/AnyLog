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

#include "search_data_dlg.h"

// BUG?
LRESULT SearchDataDlg::OnInitDialog(UINT, WPARAM, LPARAM, BOOL &) {
  list_.Attach(GetDlgItem(IDC_SEARCHDLG_LIST));

  list_.InsertColumn(0, _T("Index"), LVCFMT_LEFT, 50, 0);
  list_.InsertColumn(1, _T("Name"), LVCFMT_LEFT, 100, 1);
  list_.InsertColumn(2, _T("Val"), LVCFMT_LEFT, 200, 2);
  list_.InsertColumn(3, _T("Regex"), LVCFMT_LEFT, 50, 3);

  list_.SetItemCount(data_.size());
  list_.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER |
                                 LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE);
  list_.SetHotCursor(LoadCursor(NULL, IDC_ARROW));

  CenterWindow(GetParent());
  return true;
}

LRESULT SearchDataDlg::OnClose(UINT, WPARAM wParam, LPARAM, BOOL &) {
  EndDialog(LOWORD(wParam));
  return 0;
}

LRESULT SearchDataDlg::OnBnClickedAdd(WORD, WORD wID, HWND, BOOL &) {
  FilterData data = pcview_->GetSearch();
  data.name = std::to_string(data_.size());
  data_.push_back(data);
  list_.SetItemCount(data_.size());
  list_.RedrawWindow();
  return 0;
}

LRESULT SearchDataDlg::OnBnClickedCancel(WORD, WORD wID, HWND, BOOL &) {
  EndDialog(wID);
  return 0;
}

LRESULT SearchDataDlg::OnBnClickedDelete(WORD, WORD, HWND, BOOL &) {
  int select = list_.GetNextItem(-1, LVNI_FOCUSED);
  if (select < 0) {
    return 0;
  }
  data_.erase(data_.begin() + select);
  list_.SetItemCount(data_.size());
  list_.RedrawWindow();
  return 0;
}

LRESULT SearchDataDlg::OnBnClickedOk(WORD, WORD wID, HWND, BOOL &) {
  int select = list_.GetNextItem(-1, LVNI_FOCUSED);
  if (select < 0) {
    return 0;
  }
  pcview_->SetAndSearch(data_[select]);
  EndDialog(wID);
}

LRESULT SearchDataDlg::OnLvnGetdispinfoList(int, LPNMHDR pNMHDR, BOOL &) {
  NMLVDISPINFO *lpdi = reinterpret_cast<NMLVDISPINFO *>(pNMHDR);

  if (lpdi->item.iItem >= data_.size()) {
    return 0;
  }
  char szString[512];
  FilterData &filterdata = data_[lpdi->item.iItem];

  if (lpdi->item.iSubItem) {
    if (lpdi->item.mask & LVIF_TEXT) {
      switch (lpdi->item.iSubItem) {
        case 1: {
          _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
                     filterdata.name.c_str(), _TRUNCATE);
          break;
        }
        case 2: {
          _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
                     filterdata.val.c_str(), _TRUNCATE);
          break;
        }
        case 3: {
          _sntprintf_s(szString, _countof(szString), _TRUNCATE, TEXT("%d"),
                       filterdata.regex);
          _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax, szString,
                     _TRUNCATE);
          break;
        }
      }
    }
  } else {
    if (lpdi->item.mask & LVIF_TEXT) {
      _sntprintf_s(szString, _countof(szString), _TRUNCATE, TEXT("%d"),
                   lpdi->item.iItem + 1);
      _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax, szString,
                 _TRUNCATE);
    }
    if (lpdi->item.mask & LVIF_IMAGE) {
      lpdi->item.iImage = 0;
    }
  }
  return 0;
}

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
#pragma once

#include "format_manage.h"

class FormatDlg : public CDialogImpl<FormatDlg>
{
public:
  enum { IDD = IDD_FORMAT_DLG};

  FormatDlg(FormatManage &format_manage) :format_manage_(format_manage) {}


  BEGIN_MSG_MAP(FormatDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    MESSAGE_HANDLER(WM_CLOSE, OnClose)
    COMMAND_HANDLER(IDC_ADD_FORMAT, BN_CLICKED, OnBnClickedAddFormat)
    COMMAND_HANDLER(IDC_CANCEL_FORMAT, BN_CLICKED, OnBnClickedCancelFormat)
    COMMAND_HANDLER(IDC_DELETE_FORMAT, BN_CLICKED, OnBnClickedDeleteFormat)
    COMMAND_HANDLER(IDC_OK_FORMAT, BN_CLICKED, OnBnClickedOkFormat)
    NOTIFY_HANDLER(IDC_LIST_FORMAT, LVN_GETDISPINFO, OnLvnGetdispinfoListFormat)
  END_MSG_MAP()

  // Handler prototypes (uncomment arguments if needed):
  //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
  //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

  LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
  LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedAddFormat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedCancelFormat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedDeleteFormat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedOkFormat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnLvnGetdispinfoListFormat(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/);

  CListViewCtrl VC_format_list_;
  FormatManage &format_manage_;
};




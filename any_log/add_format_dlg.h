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
#pragma once

#include "format_manage.h"

class AddFormatDlg : public CDialogImpl<AddFormatDlg>
{
public:
  enum { IDD = IDD_ADDFORMAT_DLG};

  AddFormatDlg(FormatManage &foramtmanage):format_manage_(foramtmanage){}

  BEGIN_MSG_MAP(AddFormatDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    MESSAGE_HANDLER(WM_CLOSE, OnClose)
    COMMAND_HANDLER(IDC_OK_ADDFORMAT, BN_CLICKED, OnBnClickedOkAddformat)
    COMMAND_HANDLER(IDC_CANCEL_ADDFORMAT, BN_CLICKED, OnBnClickedCancelAddformat)
    COMMAND_HANDLER(IDC_CHECK1_ADDFORMAT, BN_CLICKED, OnBnClickedCheck1Addformat)
    COMMAND_HANDLER(IDC_CHECK2_ADDFORMAT, BN_CLICKED, OnBnClickedCheck2Addformat)
  END_MSG_MAP()

  // Handler prototypes (uncomment arguments if needed):
  //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
  //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

  FormatManage &format_manage_;
  CButton      check_box_interval_;
  CButton      check_box_level_;
  CEdit        edit_name_;
  CEdit        edit_regex_;
  CEdit        edit_colmun_;
  CEdit        edit_interval_;
  CEdit        edit_level_;
  CEdit        edit_level_text_;


  LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
  LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedOkAddformat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedCancelAddformat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedCheck1Addformat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedCheck2Addformat(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};
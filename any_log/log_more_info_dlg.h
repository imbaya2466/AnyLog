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
#pragma once


#include "log.h"

class LogMoreInfoDlg : public CDialogImpl<LogMoreInfoDlg>
{
public:
  enum { IDD = IDD_DIALOG_MOREINFO};

  LogMoreInfoDlg(Log &log) :log_(log) {}


  BEGIN_MSG_MAP(LogMoreInfoDlg)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    MESSAGE_HANDLER(WM_CLOSE, OnClose)
    COMMAND_HANDLER(IDC_BUTTON1_MOREINFO, BN_CLICKED, OnBnClickedBinConver)
    COMMAND_HANDLER(IDC_BUTTON2_MOREINFO, BN_CLICKED, OnBnClickedErroeMsg)

  END_MSG_MAP()

  // Handler prototypes (uncomment arguments if needed):
  //	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
  //	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
  //	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

  LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
  LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedBinConver(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
  LRESULT OnBnClickedErroeMsg(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);


  CEdit log_edit_;
  CEdit out_edit_;

  Log log_;

};
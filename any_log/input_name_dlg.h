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
#pragma once

#include <string>

class InputNameDlg : public CDialogImpl<InputNameDlg> {
 public:
  enum { IDD = IDD_DIALOG_NAME };

  InputNameDlg(std::string& name)
      : name_(name){}

  BEGIN_MSG_MAP(InputNameDlg)
  MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
  MESSAGE_HANDLER(WM_CLOSE, OnClose)
  COMMAND_HANDLER(ID_NAME_DLG_OK, BN_CLICKED, OnBnClickedOk)
  COMMAND_HANDLER(ID_NAMEDLG_CANCEL, BN_CLICKED, OnBnClickedCancel)
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

  std::string& name_;
  CEdit edit_;

};
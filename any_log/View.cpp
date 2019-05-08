// View.cpp : implementation of the CView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "tool.h"

#include "View.h"
#include "log_more_info_dlg.h"

BOOL CView::PreTranslateMessage(MSG* pMsg)
{
	return CWindow::IsDialogMessage(pMsg);
}

void CView::OnFinalMessage(HWND /*hWnd*/)
{
  //delete will be used
	delete this;
}

CView::~CView()
{
  if (h_thread_)
  {
    thread_run_ = false;
    WaitForSingleObject(h_thread_, INFINITE);
    CloseHandle(h_thread_);
    h_thread_ = 0;
  }
  if (mutex_)
  {
    CloseHandle(mutex_);
    mutex_ = 0;
  }
  delete pstream_;
}

DWORD __stdcall CView::ThreadProc(LPVOID lpParam)
{
  CView *view = (CView*)lpParam;
  int ret1 = 0;
  int ret2 = 0;
  view->thread_run_ = true;
  while (true)
  {
    WaitForSingleObject(view->mutex_, INFINITE);
    ret1 = view->control_.ReadStream(MAX_ONCE_READ);
    ReleaseMutex(view->mutex_);
    view->showed_num_ = ret1;
    Sleep(CView::SLEEP_ONCE_READ);
    if (!(view->thread_run_) || ret1 == ret2)
    {
      break;
    }
    ret2 = ret1;
  }

  return 0;
}

LRESULT CView::OnInitDialog(HWND hwndFocus, LPARAM lParam)
{
  level_box_.Attach(GetDlgItem(IDC_VIEW_COMBO));
  search_edit_.Attach(GetDlgItem(IDC_VIEW_EDIT));
  regex_check_.Attach(GetDlgItem(IDC_VIEW_CHECK));
  search_button_.Attach(GetDlgItem(IDC_VIEW_BUTTON));
  list_.Attach(GetDlgItem(IDC_VIEW_LIST));

  list_.InsertColumn(0, _T("Num"), LVCFMT_LEFT, 50, 0);
  int width[10] = { 150,50,150,150,50,700,100,100,100,100};
  int i = 0;
  for (; i < format_.column_name.size()-1; i++) {
    list_.InsertColumn(i+1, format_.column_name[i].c_str(), LVCFMT_LEFT, width[i], i+1);
  }
  list_.InsertColumn(i + 1, format_.column_name[i].c_str(), LVCFMT_LEFT, 700, i + 1);

  list_.SetItemCount(0);
  list_.SetExtendedListViewStyle(LVS_EX_FULLROWSELECT | LVS_EX_DOUBLEBUFFER | LVS_EX_UNDERLINEHOT | LVS_EX_ONECLICKACTIVATE);
  list_.SetHotCursor(LoadCursor(NULL, IDC_ARROW));

  if (format_.index_column_level >= 0) {
    for (int i = 0; i < format_.level_text.size(); i++) {
      level_box_.AddString(format_.level_text[i].c_str());
    }
    level_box_.SetCurSel(0);
    control_.AddLevel(0);
  }else {
    level_box_.EnableWindow(false);
  }

  mutex_ = CreateMutex(NULL, FALSE, NULL);

  showed_num_ = control_.ReadStream(MAX_FIRST_READ);
  list_.SetItemCount(showed_num_);
  ScrollTo(0);

  h_thread_ = CreateThread(NULL, 0, ThreadProc, this, 0, NULL);

  return 0;
}

LRESULT CView::OnSize(UINT, WPARAM, LPARAM, BOOL &)
{
  RECT rect;
  GetClientRect(&rect);
  list_.MoveWindow(rect.left, rect.top + 50, rect.right, rect.bottom - 50);
  return 0;
}

LRESULT CView::OnKeyDown(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
  LPNMLVKEYDOWN pnkd = (LPNMLVKEYDOWN)pNMHDR;
  switch (pnkd->wVKey) {
    // F
    case 0x46: {
      // TODO: more find dlg

      break;
    }
    // A
    case 0x41: {
        list_.SetItemState(-1, LVIS_SELECTED, LVIS_SELECTED);
      break;
    }
  }

  // retun true will not be processed elsewhere 
  return true;
}

LRESULT CView::OnLvnGetdispinfoList(int, LPNMHDR pNMHDR, BOOL &)
{
  NMLVDISPINFO *lpdi = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
  TCHAR szString[MAX_STRING];

  if (lpdi->item.iItem >= control_.Size()) {
    return 0;
  }

  WaitForSingleObject(mutex_, INFINITE);
  const Log &log = control_.GetLog(lpdi->item.iItem);
  ReleaseMutex(mutex_);

  if (lpdi->item.iSubItem)
  {
    if (lpdi->item.mask & LVIF_TEXT)
    {
      int subindex = lpdi->item.iSubItem;
       _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
            log.GetMember(subindex -1).c_str(), _TRUNCATE);
    }
  }
  else
  {
    if (lpdi->item.mask & LVIF_TEXT)
    {
      _sntprintf_s(szString, _countof(szString), _TRUNCATE,
        TEXT("%d"), lpdi->item.iItem + 1);
      _tcsncpy_s(lpdi->item.pszText, lpdi->item.cchTextMax,
        szString, _TRUNCATE);
    }

    if (lpdi->item.mask & LVIF_IMAGE)
    {
      lpdi->item.iImage = 0;
    }
  }
  return 0;
}

LRESULT CView::OnLvnEndScrollList(int, LPNMHDR pNMHDR, BOOL &)
{
  SCROLLINFO info;
  info.cbSize = sizeof(SCROLLINFO);
  info.fMask = SIF_ALL;
  list_.GetScrollInfo(SB_VERT, &info);
  int y = info.nPage + info.nPos;

  if (y == info.nMax + 1){
    if (showed_old_num_ == showed_num_){
      return 0;
    }
    showed_old_num_ = showed_num_;
    list_.SetItemCount(showed_num_);
    ScrollTo(info.nPos);       
  }
  return 0;
}

LRESULT CView::OnBnClickedButton(WORD, WORD, HWND, BOOL &)
{
  TCHAR sz_string[MAX_STRING];
  search_edit_.GetLine(0, sz_string, MAX_STRING);

  // G:
  if (sz_string[0] == _T('G') && sz_string[1] == _T(':')){
    int i = _ttoi(&sz_string[2]);
    if (i == 0){
      MessageBox(_T("请输入合法行号"), _T("输入错误"));
      search_edit_.SetSel(0, -1);
      search_edit_.Clear();
      return 0;
    }
    if (i > control_.Size()){
      MessageBox(_T("超出当前最大行数"), _T("输入错误"));
      search_edit_.SetSel(0, -1);
      search_edit_.Clear();
      return 0;
    }
    ScrollTo(i);
    list_.SetFocus();
    return 0;
  }

  int regex_check = regex_check_.GetCheck();

  WaitForSingleObject(mutex_, INFINITE);
  if (regex_check > 0){
    //regex
    control_.SetFilterWholeRegex(sz_string);
  }else{
    //not regex
    if (strchr(sz_string, ';')){
      //inturn key
      control_.SetFilterInturnKey(sz_string);
    }else{
      //whole key
      control_.SetFilterWholeKey(sz_string);
    }
  }
  control_.RefreshFilter();
  ReleaseMutex(mutex_);

  showed_num_ = control_.Size();
  list_.SetItemCount(showed_num_);
  ScrollTo(0);
  list_.SetFocus();

  return 0;
}

LRESULT CView::OnCbnSelchangeCombo(WORD, WORD, HWND, BOOL &)
{
  int level= level_box_.GetCurSel();
  WaitForSingleObject(mutex_, INFINITE);
  control_.AddLevel(level);
  control_.RefreshFilter();
  ReleaseMutex(mutex_);

  showed_num_ = control_.Size();
  list_.SetItemCount(showed_num_);
  ScrollTo(0);

  list_.SetFocus();
  return 0;
}

COLORREF level_colour[] = { RGB(0xBB,0xBB,0xBB),RGB(0x00,0x70,0xBB) ,
RGB(0x48,0xBB,0x31) ,RGB(0xBB,0xBB,0x23) ,RGB(0xFF,0x00,0x06),RGB(0x8F,0x00,0x05) };
LRESULT CView::OnNMCustomdrawList(int, LPNMHDR pNMHDR, BOOL &)
{
  LPNMLVCUSTOMDRAW lplvcd = reinterpret_cast<LPNMLVCUSTOMDRAW>(pNMHDR);

  switch (lplvcd->nmcd.dwDrawStage)
  {
    case CDDS_PREPAINT: //Before the paint cycle begins
      //request notifications for individual listview items
      return CDRF_NOTIFYITEMDRAW;
      break;
    case CDDS_ITEMPREPAINT: //Before an item is drawn
    {

      if (lplvcd->nmcd.dwItemSpec>= control_.Size()||
        format_.index_column_level<0){
        return CDRF_DODEFAULT;
      }
      WaitForSingleObject(mutex_, INFINITE);
      const Log &log = control_.GetLog(lplvcd->nmcd.dwItemSpec);
      ReleaseMutex(mutex_);
      lplvcd->clrText = level_colour[tool::Levelstoi(format_.level_text,log.GetMember(format_.index_column_level))];
      if (log.mark) {
        lplvcd->clrTextBk = RGB(0x00, 0xC5, 0xCD);
      }
      else {
        lplvcd->clrTextBk = list_.GetBkColor();
      }
      return CDRF_NEWFONT;
    }
    break;
  }
  return CDRF_DODEFAULT;

}


void CView::ScrollTo(int line)
{
  int nSel = line - 1;
  int nItem = list_.GetTopIndex();
  CRect rc;
  list_.GetItemRect(nItem, rc, LVIR_BOUNDS);
  CSize sz(0, (nSel - nItem)*rc.Height());
  list_.Scroll(sz);
}

void CView::SetBackgroundColour(COLORREF in_colour)
{
  list_.SetBkColor(in_colour);
}

//not Global var  these var only used in this moudle
static std::vector<int> rclick_choose;
static int focused;
LRESULT CView::OnNMRclickViewList(int idCtrl, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
  LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)pNMHDR;

  focused = lpnmitem->iItem;
  rclick_choose.clear();
  int index_choose = list_.GetNextItem(-1, LVIS_SELECTED);
  while (index_choose != -1) {
    rclick_choose.push_back(index_choose);
    index_choose = list_.GetNextItem(index_choose, LVIS_SELECTED);
  }

  CMenuHandle menumain = LoadMenu(NULL, MAKEINTRESOURCE(IDR_RCLICK_MENU));
  CMenuHandle rclick_menu = menumain.GetSubMenu(0);
  rclick_menu.AppendMenuA(MF_SEPARATOR);

  if (format_.index_column_interval >= 0) {
    rclick_menu.AppendMenuA(MF_STRING, ID_RCLICK_INTERVAL_FROM, 
      (format_.column_name[format_.index_column_interval]+" from this").c_str());
    rclick_menu.AppendMenuA(MF_STRING, ID_RCLICK_INTERVAL_TO,
      (format_.column_name[format_.index_column_interval] + " to this").c_str());
    rclick_menu.AppendMenuA(MF_SEPARATOR);
  }
  rclick_menu.AppendMenuA(MF_STRING, ID_RCLICK_ADDTO_EDIT, "add to find");
  rclick_menu.AppendMenuA(MF_STRING, ID_RCLICK_MORE_INFO,"more info");

  POINT pt = lpnmitem->ptAction;
  list_.ClientToScreen(&pt);
  rclick_menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,
    pt.x,
    pt.y ,
    (HWND)m_hWnd);
  menumain.DestroyMenu();

  return 0;
}


static std::string copy_edit_choose;

LRESULT CView::OnRclickMenu(WORD, WORD id, HWND, BOOL &)
{
  std::vector<Log*> choose_log;//rclick_choose
  WaitForSingleObject(mutex_, INFINITE);
  for (auto i : rclick_choose) {
    choose_log.push_back(&control_.GetLog(i));
  }
  Log focused_log = control_.GetLog(focused);
  ReleaseMutex(mutex_);  
  switch (id) {
    case ID_RCLICK_MARK: {
      for (auto i : choose_log) {
        i->mark = !i->mark;
      }
      break;
    }
    case ID_RCLICK_COPY: {
      // error
      //SetClipboardData(CF_TEXT,(HANDLE)(log.get_log().c_str()));
      break;
    }
    case ID_RCLICK_INTERVAL_FROM: {
      WaitForSingleObject(mutex_, INFINITE);
      control_.AddInterval(focused_log.GetMember(format_.index_column_interval));
      control_.RefreshFilter();
      ReleaseMutex(mutex_);

      showed_num_ = control_.Size();
      list_.SetItemCount(showed_num_);
      ScrollTo(0);

      list_.SetFocus();
      break;
    }
    case ID_RCLICK_INTERVAL_TO: {
      WaitForSingleObject(mutex_, INFINITE);
      control_.AddInterval("", focused_log.GetMember(format_.index_column_interval));
      control_.RefreshFilter();
      ReleaseMutex(mutex_);

      showed_num_ = control_.Size();
      list_.SetItemCount(showed_num_);
      ScrollTo(0);

      list_.SetFocus();
      break;
    }
    case ID_RCLICK_MORE_INFO: {
      LogMoreInfoDlg dlg(focused_log);
      dlg.DoModal();
      list_.SetFocus();
      break;
    }
    case ID_RCLICK_FIND_TEXT: {
      WaitForSingleObject(mutex_, INFINITE);
      control_.SetFilterWholeKey(copy_edit_choose);
      control_.RefreshFilter();
      ReleaseMutex(mutex_);

      showed_num_ = control_.Size();
      list_.SetItemCount(showed_num_);
      ScrollTo(0);
      list_.SetFocus();
      break;
    }
    case ID_RCLICK_ADDTO_EDIT: {
      search_edit_.SetSel(0, -1);
      search_edit_.Clear();
      for (int i = 0; i < focused_log.GetMemberNum(); i++) {
        search_edit_.AppendText((focused_log.GetMember(i)+";").c_str());
      }
      break;
    }
  }
  return 0;
}


LRESULT CView::OnNMDblclkList(int, LPNMHDR pNMHDR, BOOL &)
{
  LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)pNMHDR;
  CRect rc;
  LVITEMINDEX itemindex{ lpnmitem->iItem ,0 };
  list_.GetItemIndexRect(&itemindex, lpnmitem->iSubItem, LVIR_BOUNDS, &rc);
  list_.ClientToScreen(rc);
  copy_edit_.Create(this->m_hWnd, rc, "", WS_POPUP | WS_VISIBLE | WS_TABSTOP);
  copy_edit_.SetBackgroundColor(list_.GetBkColor());
  copy_edit_.SetFont(list_.GetFont());

  Log log = control_.GetLog(lpnmitem->iItem);
  copy_edit_choose = " ";
  if (lpnmitem->iSubItem) {
    copy_edit_choose += log.GetMember(lpnmitem->iSubItem - 1);
  }else {
    copy_edit_choose += std::to_string(lpnmitem->iItem);
  }
  copy_edit_.AppendText(copy_edit_choose.c_str());
  copy_edit_.SetEventMask(ENM_SELCHANGE| ENM_MOUSEEVENTS);
  copy_edit_.SetSelAll();
  return 0;
}

LRESULT CView::OnEnKillfocusEdit(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
{
  if (copy_edit_.IsWindow()) {
    copy_edit_.DestroyWindow();
  }
  return 0;
}

LRESULT CView::OnNMRclickCopyEdit(int idCtrl, LPNMHDR pNMHDR, BOOL& bHandled)
{
  MSGFILTER *Param = (MSGFILTER *)pNMHDR;
  
  if (Param->msg== WM_RBUTTONDOWN) {
    LONG from, to;
    copy_edit_.GetSel(from, to);
    copy_edit_choose = copy_edit_choose.substr(from, to - from);

    POINT pt;
    pt.x = GET_X_LPARAM(Param->lParam);
    pt.y = GET_Y_LPARAM(Param->lParam);
    copy_edit_.ClientToScreen(&pt);
    CMenuHandle menumain = LoadMenu(NULL, MAKEINTRESOURCE(IDR_RCLICK_MENU));
    CMenuHandle rclick_menu = menumain.GetSubMenu(0);
    rclick_menu.AppendMenuA(MF_STRING, ID_RCLICK_FIND_TEXT, "find text");
    rclick_menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_TOPALIGN | TPM_RIGHTBUTTON,
      pt.x,
      pt.y,
      (HWND)m_hWnd);
    menumain.DestroyMenu();
  }

  return 0;
}


LRESULT CView::OnNMClickViewList(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
  LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE)pNMHDR;
  if (lpnmitem->iItem >= control_.Size()|| lpnmitem->iItem<0) {
    return 0;
  }
  Log &log = control_.GetLog(lpnmitem->iItem);
  std::string set = "Line:" + std::to_string(lpnmitem->iItem);
  status_bar_.SetText(1, set.c_str());
  set = "Length:" + std::to_string(log.get_log().size());
  status_bar_.SetText(2, set.c_str());
  return 0;
}

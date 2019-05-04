/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: format_manage
 * Description: manage all format curd
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/
#pragma once

#include <string>
#include <vector>

#include "sqlite3.h"

#include "log_format.h"

// the class object bind to MainFrm 
// only read once in create and write once in close.db will not change at runing time.
// you should check Ready befor get now format choose
// Example:
//   FormatManage format_manage;
//   format_manage.ReadDB();
//   if(format_manage.Ready()){
//     format_manage.GetChooseFormat();
class FormatManage {
 public:
  bool Ready();
	void ReadDB(); 
	void WriteDB();
	LogFormat GetChooseFormat();
  void DeleteFormatIndex(unsigned int index_delete);
  void AddFormat(const LogFormat &log_format);
  // get format with index. because has size(),check outside
  LogFormat& GetFormat(unsigned int index);
  
  int size();
	void set_choose_format(unsigned choose_format);
  // only used to show
	

 private:
	std::vector<LogFormat> log_format_list_;
	unsigned int choose_format_ = 0;
  sqlite3 *db_;
};





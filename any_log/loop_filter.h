/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: loop_filter
 * Description: filter the queue to map the elements 
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/
#pragma once

#include <regex>
#include <vector>

#include "log_storage_loop.h"
#include "log_format.h"
#include "log.h"

class LoopFilter {
public:
  LoopFilter(LogStorageLoop &loop, LogFormat &format):loop_(loop),format_(format){}
  ~LoopFilter() = default;

  void SetInTurnKey(std::string &match);
  void SetWholeKey(std::string &match);
  void SetWholeRegex(std::string &match);

  // >=
  void AddLevel(int level=0);
  // []
  void AddInterval(std::string from = "", std::string to = "\x7F");

  void Refresh();
  void MapMore();
  
  // outside use Size to check
  int Size();
  Log& operator[](int i);

private:
  LogFormat format_;
  // queue from outside,is managed buy middle_layer
  LogStorageLoop &loop_;
  // filter map 
  std::vector<int> map_;
  // the index to loop_
  int maped_loop_num_ = 0;

  // condition main filter in this three,special independent
  enum FilterType {
    FT_INTURN_KEY,
    FT_WHOLE_KEY,
    FT_WHOLE_REGEX,
  };
  FilterType filter_type= FT_WHOLE_KEY;
  std::string match_;

  int level_=0;
  std::string interval_from_;
  std::string interval_to_="\x7F";



};
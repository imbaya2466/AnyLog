/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: middle_layer
 * Description: all assembly in here,all the code is platform independent.
                provide simple interface to view to direct use
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/
#pragma once

#include <iostream>

#include "loop_filter.h"
#include "log_storage_loop.h"
#include "log_format.h"

// this object only bind with view
class MiddleLayer {
public:
  MiddleLayer(LogFormat &format, std::istream &stream);
  ~MiddleLayer();

  int ReadStream(int num);
  void RefreshFilter();
  //high light control in view
  Log &GetLog(int index);
  int Size();

  // remember to refresh
  void SetFilterInturnKey(std::string inturn_key);
  void SetFilterWholeKey(std::string key);
  void SetFilterWholeRegex(std::string regex);
  void AddLevel(int level);
  void AddInterval(std::string from = "", std::string to = "\x7F");
  
  

private:
  // view-stream-loop-middlelayer one-to-one correspondence
  LogStorageLoop loop_;
  // don`t need replace
  LoopFilter *pfilter_=nullptr;
  LogFormat format_;
  // stream cycle manage by view
  std::istream &stream_;
};
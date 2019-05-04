/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: log_storage_loop
 * Description: stroage the log in a deque to control memory used in save logs 
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/
#pragma once

#include <deque>

#include "log.h"

class LogStorageLoop {
 public:
   LogStorageLoop() = default;
   ~LogStorageLoop() = default;

   Log& operator[](int i);
   // if remove forward elements,return removed num
   // else return 0
   int Push(const Log &log);
   int Size();


 private:
   // remove forward elements
   bool free_list(int num);
   // max deque storage log num 
   const static int MAX_NUM = 1000000;
   std::deque<Log> log_deque_;
};
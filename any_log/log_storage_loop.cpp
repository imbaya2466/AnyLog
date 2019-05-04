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

#include "log_storage_loop.h"

Log & LogStorageLoop::operator[](int i)
{
  return log_deque_[i];
}

int LogStorageLoop::Push(const Log & log)
{
  int num = 0;
  if (log_deque_.size() > MAX_NUM) {
    num = MAX_NUM / 10;
    free_list(num);
  }
  log_deque_.push_back(log);
  return num;
}

int LogStorageLoop::Size()
{
  return log_deque_.size();
}

bool LogStorageLoop::free_list(int num)
{
  while (num--){
    log_deque_.pop_front();
  }
  return true;
}

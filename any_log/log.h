/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: log
 * Description: struct for one log
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/
#pragma once

#include <string>
#include <vector>

// any format log`s packages
class Log {
 public:

  Log(const std::string &log, const std::vector<unsigned int> &log_index);
  // get column value
  std::string GetMember(unsigned int index) const;
  // number of log`s member
  int GetMemberNum();
  // get whole log
  std::string get_log();

  bool mark = false;

 private:
  // whole log cut colume in ' '
  std::string log_;
  // log`s colume value start index in log_ 
  std::vector<unsigned int> log_index_;
};
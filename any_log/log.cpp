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

#include "log.h"

Log::Log(const std::string &log,const std::vector<unsigned int> &log_index)
  :log_(log),log_index_(log_index)
{}

std::string Log::GetMember(unsigned int index) const
{
  unsigned int from = log_index_[index];
  if (index + 1 >= log_index_.size()) {
    return log_.substr(from);
  }
  unsigned int num = log_index_[index+1]- log_index_[index]-1;
  return log_.substr(from,num);
}

int Log::GetMemberNum()
{
  return log_index_.size();
}

std::string Log::get_log()
{
  return log_;
}

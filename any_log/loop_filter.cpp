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

#include "loop_filter.h"

#include <regex>

#include "tool.h"

void LoopFilter::SetInTurnKey(std::string & match)
{
  filter_type = FT_INTURN_KEY;
  match_ = match;
}

void LoopFilter::SetWholeKey(std::string & match)
{
  filter_type = FT_WHOLE_KEY;
  match_ = match;
}

void LoopFilter::SetWholeRegex(std::string & match)
{
  filter_type = FT_WHOLE_REGEX;
  match_ = match;
}

void LoopFilter::AddLevel(int level)
{
  level_ = level;
}

void LoopFilter::AddInterval(std::string from, std::string to)
{
  interval_from_ = from;
  interval_to_ = to;
}

void LoopFilter::Refresh()
{
  map_.clear();
  maped_loop_num_ = 0;
  MapMore();
}

void LoopFilter::MapMore()
{
  std::string ls_member;
  switch (filter_type) {
    case FT_INTURN_KEY: {
      std::vector<std::string> inturn_key = tool::SplitString(match_, ";");
      int min_num = format_.column_name.size() > inturn_key.size() ? inturn_key.size() : format_.column_name.size();
      for (int i = maped_loop_num_; i < loop_.Size(); i++) {
        Log ls = loop_[i];
        if (format_.index_column_level >= 0) {
          ls_member = ls.GetMember(format_.index_column_level);
          if (tool::Levelstoi(format_.level_text, ls_member) < level_) {
            continue;
          }
        }
        if (format_.index_column_interval >= 0) {
          ls_member = ls.GetMember(format_.index_column_interval);
          if (ls_member<interval_from_ || ls_member>interval_to_) {
            continue;
          }
        }
        int j = 0;
        for (; j < min_num; j++) {
          if (ls.GetMember(j).find(inturn_key[j]) == std::string::npos) {
            break;
          }
        }
        if (j != min_num) {
          continue;
        }
        map_.push_back(i);
      }
      break;
    }
    case FT_WHOLE_KEY: {
      for (int i = maped_loop_num_; i < loop_.Size(); i++) {
        Log ls = loop_[i];
        if (format_.index_column_level >= 0) {
          ls_member = ls.GetMember(format_.index_column_level);
          if (tool::Levelstoi(format_.level_text, ls_member) < level_) {
            continue;
          }
        }
        if (format_.index_column_interval >= 0) {
          ls_member = ls.GetMember(format_.index_column_interval);
          if (ls_member<interval_from_ || ls_member>interval_to_) {
            continue;
          }
        }
        if (ls.get_log().find(match_) == std::string::npos) {
          continue;
        }
        map_.push_back(i);
      }
      break;
    }
    case FT_WHOLE_REGEX: {
      bool regex_ok = false;
      std::regex regex;
      try {
        regex = std::regex(match_);
        regex_ok = true;
      }
      catch (const std::regex_error& e) {
        regex_ok = false;
      }
      for (int i = maped_loop_num_; i < loop_.Size(); i++) {
        Log ls = loop_[i];
        if (format_.index_column_level >= 0) {
          ls_member = ls.GetMember(format_.index_column_level);
          if (tool::Levelstoi(format_.level_text, ls_member) < level_) {
            continue;
          }
        }
        if (format_.index_column_interval >= 0) {
          ls_member = ls.GetMember(format_.index_column_interval);
          if (ls_member<interval_from_ || ls_member>interval_to_) {
            continue;
          }
        }
        if (!regex_ok || !std::regex_match(ls.get_log(), regex))
        {
          continue;
        }
        map_.push_back(i);
      }
      break;
    }
  }
  maped_loop_num_ = loop_.Size();
}

int LoopFilter::Size()
{
  return map_.size();
}

Log & LoopFilter::operator[](int i)
{
  return loop_[map_[i]];
}

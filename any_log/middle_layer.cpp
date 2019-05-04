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

#include "middle_layer.h"

#include <string>
#include <regex>

MiddleLayer::MiddleLayer(LogFormat & format, std::istream  &stream)
  :format_(format), stream_(stream) 
{
  pfilter_ = new LoopFilter(loop_,format_);
}

MiddleLayer::~MiddleLayer()
{
  if (pfilter_) {
    delete pfilter_;
    pfilter_ = nullptr;
  }
}

int MiddleLayer::ReadStream(int num)
{
  int ret = 0;
  std::string line;
  bool change = false;

  std::regex format_regex;
  try {
    format_regex = std::regex(format_.regex);
  }
  catch (const std::regex_error& e) {
    return ret;
  }

  bool has_line = false;
  while (std::getline(stream_, line)){
    if (regex_match(line,format_regex)){
      has_line = true;
      break;
    }
  }

  if (has_line)
    while (num--){
      if (!stream_){
        break;
      }

      std::string new_log_readed = line;
      while (true){
        if (!std::getline(stream_, line)){
          break;
        }
        if (regex_match(line, format_regex)){
          break;
        }
        else{
          new_log_readed = new_log_readed + "\n" + line;
        }

      }

      std::string log;
      std::vector<unsigned int> log_index;
      std::smatch match_result;
      std::regex_match(new_log_readed, match_result, format_regex);

      for (int i = 1; i <= format_.column_name.size(); i++) {
        log_index.push_back(log.size());
        log = log + match_result.str(i)+" ";
      }

      Log add_log(log,log_index);

      if (loop_.Push(add_log) > 0)
      {
        change = true;
      }
    }

  if (change) {
    pfilter_->Refresh();
  }else {
    pfilter_->MapMore();
  }
  ret = pfilter_->Size();
  return ret;
}

void MiddleLayer::RefreshFilter()
{
  pfilter_->Refresh();
}

Log & MiddleLayer::GetLog(int index)
{
  return (*pfilter_)[index];
}

int MiddleLayer::Size()
{
  return  pfilter_->Size();;
}

void MiddleLayer::SetFilterInturnKey(std::string inturn_key)
{
  pfilter_->SetInTurnKey(inturn_key);
  pfilter_->AddInterval();
}

void MiddleLayer::SetFilterWholeKey(std::string key)
{
  pfilter_->SetWholeKey(key);
  pfilter_->AddInterval();
}

void MiddleLayer::SetFilterWholeRegex(std::string regex)
{
  pfilter_->SetWholeRegex(regex);//of course "" is filter nothing
  pfilter_->AddInterval();
}

void MiddleLayer::AddLevel(int level)
{
  pfilter_->AddLevel(level);
}

void MiddleLayer::AddInterval(std::string from, std::string to)
{
  pfilter_->AddInterval(from, to);
}

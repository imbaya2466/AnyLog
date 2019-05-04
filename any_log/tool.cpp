/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: tool
 * Description: useful tool function
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/

#include "tool.h"

namespace tool {

std::vector<std::string> SplitString(const std::string & source, const std::string & split_char)
{
  std::vector<std::string> ret;
  std::string::size_type pos1, pos2;
  pos2 = source.find(split_char);
  pos1 = 0;
  while (std::string::npos != pos2){
    ret.push_back(source.substr(pos1, pos2 - pos1));

    pos1 = pos2 + split_char.size();
    pos2 = source.find(split_char, pos1);
  }
  if (pos1 != source.length())
    ret.push_back(source.substr(pos1));

  return ret;
}

std::string LinkStringVector(const std::vector<std::string>& source, const std::string & split_char)
{
  std::string ret;
  for (int i = 0; i < source.size(); i++){
    ret = ret + source[i] + ((i == source.size() - 1) ? "" : split_char);
  }
  return ret;
}

int Levelstoi(const std::vector<std::string>& level_text, const std::string & level)
{
  for (int i = 0; i < level_text.size(); i++) {
    if (level_text[i] == level) {
      return i;
    }
  }
  return -1;
}

std::string SHextoDec(std::string dec)
{
  int ret = 0;
  sscanf(dec.c_str(),"%x",&ret);
  return std::to_string(ret);
}

} // namespace tool

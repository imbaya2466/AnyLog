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
#pragma once

#include <string>
#include <vector>

namespace tool {

// Summary:  split string whit customer char 
// Parameters:
//  source:the string to be splited
//  split_char: the string used to split
// Return:split result vector
std::vector<std::string> SplitString(const std::string& source, const std::string& split_char);

// Summary:  link every string elements in vector
// Parameters:
//  source:vector<string> to link
//  split_char: the string used to split
// Return:split result vector
std::string LinkStringVector(const std::vector<std::string>& source, const std::string& split_char);

// not find return -1
int Levelstoi(const std::vector<std::string> &level_text,const std::string &level);
std::string Levelitos(int level);

std::string SHextoDec(std::string dec);

} // namespace tool



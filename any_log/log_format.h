/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: log_format
 * Description: struct for user customized log format 
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/
#pragma once

#include<string>
#include<vector>

// log format is used to parse readed logfile 
// and decide the UI-list format 
struct LogFormat {

	std::string format_name;
	std::string regex;
  // [0,n] names for colume 
	std::vector<std::string> column_name;
  // index for column (sorted) that can interval lookup such as time 
  // value -1 means not use
	int index_column_interval;
  // index for column that can use to level 
  // value -1 means not use
	int index_column_level;
	std::vector<std::string> level_text;
};



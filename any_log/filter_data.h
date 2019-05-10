/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: filter_data
 * Description: saved filter condition
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/
#pragma once

#include<string>

struct FilterData {
  std::string name;
  std::string val;
  int regex;
};
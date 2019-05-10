/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: filter data manage
 * Description: manage all filter data curd
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/
#pragma once

#include <vector>

#include "sqlite3.h"

#include "filter_data.h"

class FilterDataManage {
public:

  void ReadDB();
  void WriteDB();

  std::vector<FilterData>& get_list();
  void set_db(sqlite3* db);
 

private:
  std::vector<FilterData> list_;
  sqlite3 *db_;
};




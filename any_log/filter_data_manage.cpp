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

#include "filter_data_manage.h"

// callback for select db
static int ReadDBcallback(void *data, int argc, char **argv, char **azColName) {
  std::vector<FilterData> *list = (std::vector<FilterData> *)data;
  FilterData add_format;
  // id is not used
  add_format.name = argv[1];
  add_format.val = argv[2];
  add_format.regex = atoi(argv[3]);

  list->push_back(add_format);
  return 0;
}

void FilterDataManage::ReadDB() {
  char *sql;
  char *err_msg = nullptr;

  sql =
      "CREATE TABLE FILTER_DATA(    "
      "ID INT PRIMARY KEY     NOT NULL,"
      "NAME           TEXT            ,"
      "VAL            TEXT            ,"
      "REGEX          INT     );";
  // don`t worry fail ,already exist is ok
  sqlite3_exec(db_, sql, NULL, 0, &err_msg);

  sql = "SELECT * from FILTER_DATA;";
  sqlite3_exec(db_, sql, ReadDBcallback, (void *)&list_, &err_msg);
}

void FilterDataManage::WriteDB() {
  char *sql;
  char *err_msg = nullptr;

  sql = "DELETE FROM FILTER_DATA;";
  sqlite3_exec(db_, sql, NULL, 0, &err_msg);

  char sql_buffer[255];
  for (int i = 0; i < list_.size(); i++) {
    FilterData &ls = list_[i];

    std::string val;
    for (auto c : ls.val) {
      if (c == '\'') {
        val += "''";
      } else
        val.push_back(c);
    }

    sprintf(sql_buffer, "INSERT INTO FILTER_DATA VALUES (%d,'%s','%s',%d);",
            i + 1, ls.name.c_str(), val.c_str(), ls.regex);
    sqlite3_exec(db_, sql_buffer, NULL, 0, &err_msg);
  }
}

std::vector<FilterData> &FilterDataManage::get_list() { return list_; }

void FilterDataManage::set_db(sqlite3 *db) { db_ = db; }

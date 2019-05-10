/*
 * Copyright (c) 2019 The AnyLog project authors. All Rights Reserved.
 * File name: format_manage
 * Description: manage all format curd
 *
 * Author: yao
 * Version: 1.0.0.0
 * Date: 2019-04-28 10:45:00
 * Description: First Edit
*/

#include "format_manage.h"

#include "tool.h"

static const char *kDateBaseName = "data.db";

bool FormatManage::Ready()
{
  if (choose_format_ >= log_format_list_.size()){
    return false;
  }
  return true;
}

// callback for select db
static int ReadDBcallback(void *data, int argc, char **argv, char **azColName)
{
  std::vector<LogFormat> *format_list = (std::vector<LogFormat> *)data;
  LogFormat add_format;
  // id is not used
  add_format.format_name = argv[1];
  add_format.regex = argv[2];
  add_format.column_name = tool::SplitString(argv[3], ";");
  add_format.index_column_interval = atoi(argv[4]);
  std::vector<std::string> level_text= tool::SplitString(argv[5], ";");
  add_format.index_column_level = stoi(level_text[0]);
  level_text.erase(level_text.begin());
  add_format.level_text = level_text;

  format_list->push_back(add_format);
  return 0;
}

void FormatManage::ReadDB()
{
  char *sql;
  char *err_msg = nullptr;
  sqlite3_open(kDateBaseName, &db_);
  // create SQL statement
  // id-key not show
  // name-format`s name
  // regex-format`s regex use '()' grouping
  // colume_name-use ';' split into the names of each column
  // index_interval-index for column that can interval
  // level_text-index for column that has level ;level text use ';' split into \
  // the text of level low to top
  sql = "CREATE TABLE LOG_FORMAT(    " \
    "ID INT PRIMARY KEY     NOT NULL," \
    "NAME           TEXT    NOT NULL," \
    "REGEX          TEXT    NOT NULL," \
    "COLUMN_NAME    TEXT            ," \
    "INDEX_INTERVAL INT             ," \
    "LEVEK_TEXT     TEXT  );";
  //don`t worry fail ,already exist is ok
  sqlite3_exec(db_, sql, NULL, 0, &err_msg);

  sql = "SELECT * from LOG_FORMAT;";
  sqlite3_exec(db_, sql, ReadDBcallback, (void*)&log_format_list_, &err_msg);

  choose_format_ = 0;
}

void FormatManage::WriteDB()
{
  char *sql;
  char *err_msg = nullptr;
  
  sql = "DELETE FROM LOG_FORMAT;";
  sqlite3_exec(db_, sql, NULL, 0, &err_msg);

  char sql_buffer[255];
  for (int i = 0; i < log_format_list_.size(); i++){
    LogFormat &ls = log_format_list_[i];
    sprintf(sql_buffer, "INSERT INTO LOG_FORMAT VALUES (%d,'%s','%s','%s',%d,'%d;%s');",
            i+1,ls.format_name.c_str(),ls.regex.c_str(), tool::LinkStringVector(ls.column_name,";").c_str(),
            ls.index_column_interval,ls.index_column_level, tool::LinkStringVector(ls.level_text, ";").c_str());
    sqlite3_exec(db_, sql_buffer, NULL, 0, &err_msg);
  }
  sqlite3_close(db_);
}

LogFormat FormatManage::GetChooseFormat()
{
  return log_format_list_[choose_format_];
}

void FormatManage::DeleteFormatIndex(unsigned int index_delete)
{
  log_format_list_.erase(log_format_list_.begin()+ index_delete);
}

void FormatManage::AddFormat(const LogFormat & log_format)
{
  log_format_list_.push_back(log_format);
}

LogFormat &FormatManage::GetFormat(unsigned int index)
{
  return log_format_list_[index];
}



int FormatManage::size()
{
  return log_format_list_.size();
}

void FormatManage::set_choose_format(unsigned choose_format)
{
  if (choose_format >= log_format_list_.size()) {
    choose_format = 0;
  }
  choose_format_ = choose_format;
}

sqlite3 * FormatManage::get_db()
{
  return db_;
}


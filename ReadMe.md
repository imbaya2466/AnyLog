## AnyLog

A tool that can parse any format log to show as AS-logcat
support logcat`s all features about the show log

you can write regex、column name、level、interval(like time)in format dlg to prase any format log


## Environment

win32 with SQLite WTL

VS 2017 build 


## 功能
1. AS下logcat所有的展示功能-等级筛选、分列过滤、关键字过滤、正则过滤
2. 自定义解析任意格式log、自动在库中匹配可用的格式、无法匹配时手动添加正则
3. 优化win的列表界面，添加了双击edit、各种快捷右键菜单辅助快捷过滤
4. 选择、标记、选择关键字快速添加过滤等
5. 理论无限大文件读取，100万条数据约500mb内存
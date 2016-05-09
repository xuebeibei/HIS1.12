#ifndef CONNECTDB_H
#define CONNECTDB_H
#include <QtSql>
#include "WinSet.h"

//-----------------------------------------------------------------------------------------------------------------------------------
// 名称：connectDB
// 作用：链接Sqlite数据库
// 参数：无
// 返回值：无
// 备注：无
// 时间：2016-04-15
//-----------------------------------------------------------------------------------------------------------------------------------
class myDB{
public:
    static bool connectDB()
    {
        QSqlDatabase db = QSqlDatabase::addDatabase(g_strDBType);
        db.setDatabaseName(g_strDBName);
        if(!db.open())
        {
            return false;
        }
        else
        {
            return true;
        }
    }
};

#endif // CONNECTDB_H

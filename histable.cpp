#include "histable.h"

HISTable::HISTable()
{
}

QString HISTable::getNewID() const
{
    QDate date = QDate::currentDate();
    QString strDate = QString::number(date.year()).right(2)
            +QString::number(date.month())
            +QString::number(date.day());

    QTime timer = QTime::currentTime();
    QString strCurrentTime = QString::number(timer.hour())
            +QString::number(timer.minute())
            +QString::number(timer.second());
    return strDate+strCurrentTime;
}

bool HISTable::deleteRows(QString strTableName, QString strIndexName, QString str)
{
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable(strTableName);
    model->setFilter(strIndexName + " = \'" + str + "\'");
    model->select();

    int n = model->rowCount();
    bool bResult  = false;
    if(n>0)
    {
        bResult = model->removeRows(0,n);
        if(bResult == false)
        {
            QSqlQuery query;
            query.prepare("delete from "+ strTableName +" where " + strIndexName +" = \'" + str + "\'");
            bResult = query.exec();
        }
    }

    return bResult;
}

#include "clinicinternalpayment.h"

ClinicInternalPayment::ClinicInternalPayment()
{
}

QVector<QString> ClinicInternalPayment::getDistinctFromDB(QString strColumn, QString strTable)
{
    QVector<QString> vec;
    QSqlQueryModel *sqlModel = new QSqlTableModel;
    sqlModel->setQuery("SELECT distinct " + strColumn + " FROM " + strTable);

    for(int i = 0; i<sqlModel->rowCount();i++)
    {
        QSqlRecord record = sqlModel->record(i);
        QString strReceipt = record.value(strColumn).toString();
        vec.append(strReceipt);
    }
    return vec;
}

QVector<InternalPaymentItem *> ClinicInternalPayment::selectFromDB(QDate startDate, QDate endDate)
{
    QVector<InternalPaymentItem *> result;
    if(myDB::connectDB())
    {
        QString strClumn = "ChinicReceipt";
        QVector<QString> Receipt = getDistinctFromDB(strClumn , g_strClinicChargeDetails);

        QSqlQueryModel *sqlModel = new QSqlTableModel;
        for(int i=0;i<Receipt.size();i++)
        {
            InternalPaymentItem *item = new InternalPaymentItem;
            item->m_strName = Receipt.at(i);

            QString startTime = startDate.toString("yyyy-MM-dd") + "T00:00:00";
            QString endTime = endDate.toString("yyyy-MM-dd") + "T23:59:59";
            sqlModel->setQuery("Select * from " + g_strClinicChargeDetails +
                               " where "+ strClumn + "= \'" + item->m_strName +
                               "\' and chargeid in (select id from cliniccharge where time between \'" +
                               startTime +
                               "\' and \'" +
                               endTime + "\')");
            for(int j = 0;j<sqlModel->rowCount();j++)
            {
                int nCount = sqlModel->record(j).value("ChargeItemCount").toInt();
                double nPrice = sqlModel->record(j).value("ChargeItemPrice").toDouble();
                item->m_dDueIncome += nCount*nPrice;
            }
            result.append(item);
        }
    }

    return result;
}



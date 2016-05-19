#include "clinicinternalpayment.h"

ClinicInternalPayment::ClinicInternalPayment()
{
}

ClinicInternalPayment::~ClinicInternalPayment()
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

    return result;
}


QVector<QVector<QString> >* ClinicInternalPayment::selectFromDB(QDate startDate, QDate endDate, QString strConditionSort, QString strConditionWho)
{
    QVector<QString> vecSort = getDistinctFromDB(strConditionSort , g_strClinicChargeDetails);
    QVector<QString> vecWho = getDistinctFromDB(strConditionWho , g_strClinicCharge);

    QVector<QVector<QString> > *dueIncome = new QVector<QVector<QString> >;
    if(endDate < startDate)
        return NULL;
    if(vecSort.size()<=0||vecWho.size()<=0)
        return NULL;
    dueIncome->resize(0);
    dueIncome->append(vecWho);

    QString startTime = startDate.toString("yyyy-MM-dd") + "T00:00:00";
    QString endTime = endDate.toString("yyyy-MM-dd") + "T23:59:59";
    QSqlQueryModel *sqlModel = new QSqlTableModel;
    for(int i = 0;i< vecSort.size();i++)
    {
        QString strSort = vecSort.at(i);
        QVector<QString> temp;
        temp.append(vecSort.at(i));
        for(int j = 0;j< vecWho.size();j++)
        {
            QString strWho = vecWho.at(j);

            QString strSql = "select * from "+ g_strClinicChargeDetails + " where "
                    + strConditionSort+ " = \'" + strSort + "\' and chargei"
                    "d in (select id from cliniccharge where time between \'"
                    + startTime+"\' and \'"+endTime+
                    "\' and " + strConditionWho +
                    " = \'" + strWho +"\')";
            sqlModel->setQuery(strSql);

            double all = 0;
            for(int n = 0;n<sqlModel->rowCount();n++)
            {
                int nCount = sqlModel->record(n).value("ChargeItemCount").toInt();
                double nPrice = sqlModel->record(n).value("ChargeItemPrice").toDouble();
                all += nCount*nPrice;
            }
            temp.append(QString::number(all));
        }
        dueIncome->append(temp);
    }
    return dueIncome;
}

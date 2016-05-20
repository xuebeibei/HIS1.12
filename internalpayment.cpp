#include "internalpayment.h"

InternalPayment::InternalPayment()
{
}

InternalPayment::~InternalPayment()
{
}

QVector<QString> InternalPayment::getDistinctFromDB( QString strColumn, QString strTable)
{

    QVector<QString> vec;
    QSqlQueryModel *sqlModel = new QSqlTableModel;

    sqlModel->setQuery("SELECT distinct " + strColumn + " FROM " + strTable );

    for(int i = 0; i<sqlModel->rowCount();i++)
    {
        QSqlRecord record = sqlModel->record(i);
        QString strReceipt = record.value(strColumn).toString();
        if(strReceipt.isEmpty())
            continue;
        vec.append(strReceipt);
    }
    return vec;
}

QVector<InternalPaymentItem *> InternalPayment::selectFromDB(PatientType ePatientType, QDate startDate, QDate endDate)
{
    QVector<InternalPaymentItem *> result;
    QString strClumn = "ClinicReceipt";
    QString strTable = "";
    if(ePatientType == ClinicPatient)
    {
        strTable = g_strClinicCharge;
    }
    else if(ePatientType == HospitalInPatient)
    {
        strTable = g_strAccount;
        strClumn = "HospitalReceipt";
    }


    QVector<QString> Receipt = getDistinctFromDB(strClumn , g_strChargeDetails);

    QSqlQueryModel *sqlModel = new QSqlTableModel;
    for(int i=0;i<Receipt.size();i++)
    {
        InternalPaymentItem *item = new InternalPaymentItem;
        item->m_strName = Receipt.at(i);

        QString startTime = startDate.toString("yyyy-MM-dd") + "T00:00:00";
        QString endTime = endDate.toString("yyyy-MM-dd") + "T23:59:59";
        sqlModel->setQuery("Select * from " + g_strChargeDetails +
                           " where "+ strClumn + "= \'" + item->m_strName +
                           "\' and chargeid in (select id from " + strTable + " where time between \'" +
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

QVector<QVector<QString> >* InternalPayment::selectFromDB(
        QDate startDate,
        QDate endDate,
        QString strConditionX,
        QString strTableX,
        QString strConditionY,
        QString strTableY )
{
    QString startTime , endTime;
    QVector<QVector<QString> > *dueIncome = new QVector<QVector<QString> >;
    QSqlQueryModel *sqlModel = new QSqlTableModel;
    QVector<QString> vecX, vecY;
    dueIncome->resize(0);

    if(endDate < startDate)
        return NULL;
    else
    {
        startTime = startDate.toString("yyyy-MM-dd") + "T00:00:00";
        endTime = endDate.toString("yyyy-MM-dd") + "T23:59:59";
    }

    vecX = getDistinctFromDB(strConditionX , strTableX);
    vecY = getDistinctFromDB(strConditionY , strTableY);

    if(vecX.size()<=0||vecY.size()<=0)
        return NULL;

    dueIncome->append(vecY);

    for(int nIndexX = 0;nIndexX< vecX.size();nIndexX++)
    {
        QString strTempX = vecX.at(nIndexX);
        QVector<QString> temp;
        temp.append(vecX.at(nIndexX));
        for(int nIndexY = 0;nIndexY< vecY.size();nIndexY++)
        {
            QString strTempY = vecY.at(nIndexY);

            QString strSql = "select * from "+ strTableX + " where "
                    + strConditionX+ " = \'" + strTempX +
                    "\' and chargeid in (select id from " + strTableY + " where time between \'" + startTime + "\' and \'"+endTime+
                    "\' and " + strConditionY + " = \'" + strTempY +"\')";
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

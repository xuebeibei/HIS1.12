#ifndef CLINICINTERNALPAYMENTITEM_H
#define CLINICINTERNALPAYMENTITEM_H
#include "stdafx.h"
#include "connectDB.h"

struct InternalPaymentItem{
    QString m_strName;
    double  m_dDueIncome;
    InternalPaymentItem()
    {
        m_strName = g_strNull;
        m_dDueIncome = 0.0;
    }
};

class ClinicInternalPayment
{
public:
    ClinicInternalPayment();
    static QVector<QString> getDistinctFromDB(QString strColumn, QString strTable);
    static QVector<InternalPaymentItem*> selectFromDB(QDate startDate, QDate endDate);
};

#endif // CLINICINTERNALPAYMENTITEM_H

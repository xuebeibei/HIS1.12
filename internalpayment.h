#ifndef INTERNALPAYMENTITEM_H
#define INTERNALPAYMENTITEM_H
#include "stdafx.h"

//-----------------------------------------------------------------------------------------------------------------------------------
// 内部缴款明细
//-----------------------------------------------------------------------------------------------------------------------------------
struct InternalPaymentItem{
    QString m_strName;        // 收据名称
    double  m_dDueIncome;     // 应收合计
    InternalPaymentItem()
    {
        m_strName = g_strNull;
        m_dDueIncome = 0.0;
    }
};

//-----------------------------------------------------------------------------------------------------------------------------------
// 内部缴款单
//-----------------------------------------------------------------------------------------------------------------------------------
class InternalPayment
{
public:
    InternalPayment();
    ~InternalPayment();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getDistinctFromDB
    // 作用：从数据库中查询某张表中某列的元素集合
    // 参数：
    // strColumn - 列名
    // strTable - 表明
    // 返回值：
    // static QVector<QString> - 某张表中某列的元素集合
    // 备注：无
    // 时间：2016-05-12
    //-----------------------------------------------------------------------------------------------------------------------------------
    static QVector<QString> getDistinctFromDB(QString strColumn, QString strTable);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：selectFromDB
    // 作用：从数据库中读取一段时间内所有的内部缴款明细
    // 参数：
    // startDate - 起始日期
    // endDate - 结束日期
    // 返回值：
    // QVector<InternalPaymentItem*> - 一段时间内所有的内部缴款明细
    // 备注：无
    // 时间：2016-05-12
    //-----------------------------------------------------------------------------------------------------------------------------------
    static QVector<InternalPaymentItem*> selectFromDB(PatientType ePatientType,QDate startDate, QDate endDate);



    static QVector<QVector<QString> >* selectFromDB(QDate startDate,
                                                    QDate endDate,
                                                    QString strConditionX,
                                                    QString strTableX,
                                                    QString strConditionY,
                                                    QString strTableY);
};

#endif // INTERNALPAYMENTITEM_H

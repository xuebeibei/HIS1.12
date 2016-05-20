#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "stdafx.h"
#include "winSet.h"
#include "histable.h"


const QString g_strHospitalID = QObject::tr("HospitalID");
const QString g_strAccountAction = QObject::tr("AccountAction");
const QString g_strMoney = QObject::tr("Money");
const QString g_strBalance = QObject::tr("Balance");

const QString g_strMethod = QObject::tr("Method");
const QString g_strRemarks = QObject::tr("Remarks");
const QString g_strAdd = QObject::tr("+");
const QString g_strSubtract = QObject::tr("-");

const QString g_strCash = QObject::tr("现金");
const QString g_strSlotCard = QObject::tr("刷卡");
const QString g_strBank = QObject::tr("银行");



//-----------------------------------------------------------------------------------------------------------------------------------
// 住院账户缴费消费退费记录
//-----------------------------------------------------------------------------------------------------------------------------------
class Account:public HISTable
{
public:
    Account(QString strInpatientID);

    Account* operator = (Account oneAccount);
    QString getID();
    QString getInpatientID();
    QString getRemarks();

    double getBalance();
    double getActionMoney();

    AccountAction getAction();

    PaymentMethod getPaymentMethod();

    QDateTime getDateTime();

    void setID(QString strID);
    void setActionMoney(double dMoney);
    void setAction(AccountAction eAction);
    void setPaymentMethod(PaymentMethod ePaymentMethod);
    void setRemarks(QString strRemarks);

    bool Read();
    bool Save();
    bool Delete();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：PayIn
    // 作用：账户缴费
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-05-12
    //-----------------------------------------------------------------------------------------------------------------------------------
    void PayIn();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：Refund
    // 作用：账户退费
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-05-12
    //-----------------------------------------------------------------------------------------------------------------------------------
    void Refund();


    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：getRecords
    // 作用：从数据库中查询某个患者住院期间的所有账户明细
    // 参数：
    // strInpatientID - 住院患者的住院号
    // 返回值：
    // QVector<Account*> - 某个患者住院期间的所有账户明细
    // 备注：无
    // 时间：2016-05-12
    //-----------------------------------------------------------------------------------------------------------------------------------
    static QVector<Account*> getRecords(QString strInpatientID);

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：actionToString
    // 作用：将操作类别转换成字符串解释
    // 参数：无
    // 返回值：
    // QString - 缴费,扣款,退费
    // 备注：无
    // 时间：2016-05-12
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString actionToString();

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：paymentMethodToString
    // 作用：将付款方式转换成字符串解释
    // 参数：无
    // 返回值：
    // QString - 现金,刷卡,银行
    // 备注：无
    // 时间：2016-05-12
    //-----------------------------------------------------------------------------------------------------------------------------------
    QString paymentMethodToString();

protected:
    QString m_strID;                 // 缴款单号
    QString m_InpatientID;           // 账户
    QString m_strRemarks;            // 备注，目前无用

    AccountAction m_eAction;         // 操作：充值，退费，消费扣款

    double m_dActionMoney;           // 操作金额
    double  m_dBalance;              // 余额

    QDateTime m_dateTime;            // 操作时间

    PaymentMethod m_ePaymentMethod;  // 付款方式：现金，刷卡，银行
};

#endif // ACCOUNT_H

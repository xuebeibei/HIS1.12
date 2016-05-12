#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "stdafx.h"
#include "winSet.h"
#include "histable.h"

class Account:public HISTable
{
public:
    Account(QString strInpatientID);

    //重载 =
    Account* operator = (Account oneAccount);
    QString getID();
    double getBalance();
    double getActionMoney();
    AccountAction getAction();
    PaymentMethod getPaymentMethod();
    QString getRemarks();

    void setID(QString strID);
    void setActionMoney(double dMoney);
    void setAction(AccountAction eAction);
    void setPaymentMethod(PaymentMethod ePaymentMethod);
    void setRemarks(QString strRemarks);

    void PayIn();
    void Refund();

    bool Read();
    bool Save();
    bool Delete();
protected:

    QString m_strID;                 // 缴款单号
    QString m_InpatientID;           // 账户

    AccountAction m_eAction;         // 操作：充值，退费，消费扣款
    double m_dActionMoney;           // 操作金额
    double  m_dBalance;              // 余额
    QDateTime m_dateTime;            // 操作时间
    PaymentMethod m_ePaymentMethod;  // 付款方式
    QString m_strRemarks;            // 备注
};

#endif // ACCOUNT_H

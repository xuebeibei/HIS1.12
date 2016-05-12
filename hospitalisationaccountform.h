#ifndef HOSPITALISATIONACCOUNTFORM_H
#define HOSPITALISATIONACCOUNTFORM_H

#include <QWidget>
#include "stdafx.h"
#include "subform.h"
#include "account.h"

class HospitalisationAccountForm : public SubForm
{
    Q_OBJECT
    
public:
    explicit HospitalisationAccountForm(SubForm *parent = 0);
    ~HospitalisationAccountForm();
    void setInpatientID(QString strInpatientID);
public slots:

    void newTableFile();
    bool saveTableFile();
    bool deleteTableFile();
    void exportTableFile();
    bool findTableFile();
    void amendTableFile();
    void previewTableFile();
    void printTableFile();
protected:
    void create();
    void setMyLayout();
    void init();

    void Read();
    
protected:
    QLabel *m_numberLabel;              // 单号
    QLineEdit *m_numberEdit;            // 单号
    QLabel *m_beforeBalanceLabel;       // 操作之前的余额
    QLineEdit *m_beforeBalanceEdit;     // 操作之前的余额
    QLabel *m_paymentMethodLabel;       // 付款方式
    QComboBox *m_paymentMethodCombo;    // 付款方式
    QLabel *m_paymentLabel;             // 金额
    QLineEdit *m_paymentEdit;           // 金额
    QLabel *m_afterBalanceLabel;        // 操作之后的余额
    QLineEdit *m_afterBalanceEdit;      // 操作之后的余额
    QLabel *m_dontKnowLabel;            // 票号，不清楚干什么用的
    QLineEdit *m_dontKnowEdit;          // 票号，不清楚干什么用的

    QTableView *m_resultsView;          // 记录
    QStandardItemModel *m_resultsModel; // 记录

    QString m_strInpatientID;           // 患者ID
    Account *m_account;                 // 缴费账户
};

#endif // HOSPITALISATIONACCOUNTFORM_H

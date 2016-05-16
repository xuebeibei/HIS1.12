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

    double getAllPayIn();
    double getAllConsume();
signals:
    void changePayIn(double pay, double consume);
public slots:

    void newTableFile();
    bool saveTableFile();
    bool deleteTableFile();
    void exportTableFile();
    bool findTableFile();
    void amendTableFile();
    void previewTableFile();
    void printTableFile();
    void init();
    void updateInpatientID(QString strInpatientID);
    void updateAccountDate();
    void showRecords();

protected slots:
    void updateAfterBalance();
protected:
    void create();
    void setMyLayout();

    void Read();
    void initTableView();
    void setAllPayIn(double pay, double consume);
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

    QPushButton *m_saveButton;          // 缴费/退费
    QPushButton *m_cancelButton;        // 取消

    QTableView *m_resultsView;          // 记录
    QStandardItemModel *m_resultsModel; // 记录

    QString m_strInpatientID;           // 患者ID
    Account *m_account;                 // 缴费账户
    double m_allPayIn;
    double m_allConsume;
};

#endif // HOSPITALISATIONACCOUNTFORM_H

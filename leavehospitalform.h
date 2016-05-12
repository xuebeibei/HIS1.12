#ifndef LEAVEHOSPITALFORM_H
#define LEAVEHOSPITALFORM_H

#include <QWidget>
#include "stdafx.h"
#include "account.h"

class LeaveHospitalForm : public QWidget
{
    Q_OBJECT
    
public:
    explicit LeaveHospitalForm(QWidget *parent = 0);
    ~LeaveHospitalForm();

public slots:
    void updatePayIn(double dPayIn,double dConsume);

protected:
    void create();
    void setMyLayout();
    void init();
protected:
    QLabel *m_allPayInLabel;
    QLineEdit *m_allPayInEdit;
    QLabel *m_allChargeLabel;
    QLineEdit *m_allChargeEdit;
    QLabel *m_allBalanceLabel;
    QLineEdit *m_allBalanceEdit;

    QPushButton *m_payInArrearsButton;

    QLabel *m_proposerLabel;
    QLineEdit *m_proposerEdit;
    QPushButton *m_printButton;
    QPushButton *m_leaveButton;

    QString m_strInpatientID;
};

#endif // LEAVEHOSPITALFORM_H

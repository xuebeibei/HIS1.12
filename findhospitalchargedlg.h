#ifndef FINDHOSPITALCHARGEDLG_H
#define FINDHOSPITALCHARGEDLG_H
#include "finddlg.h"
#include "stdafx.h"
#include "account.h"

class FindHospitalChargeDlg : public FindDlg
{
public:
    explicit FindHospitalChargeDlg(FindDlg *parent = 0);
    ~FindHospitalChargeDlg();
    void setInpatientID(QString strInpatientID);
protected:
    void create();
    void setMyLayout();
    void init();
    void initResults();
protected slots:
    void find();
protected:
    QLabel *m_chargeIDLabel;             // 住院号
    QLineEdit *m_chargeIDEdit;           // 住院号

    QString m_InpatientID;
};

#endif // FINDHOSPITALCHARGEDLG_H

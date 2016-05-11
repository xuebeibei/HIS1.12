#ifndef HOSIPITALISATIONCHARGEFORM_H
#define HOSIPITALISATIONCHARGEFORM_H
#include <QWidget>
#include "stdafx.h"
#include "subform.h"

class HospitalisationChargeForm: public SubForm
{
    Q_OBJECT

public:
    explicit HospitalisationChargeForm(SubForm *parent = 0);
    ~HospitalisationChargeForm();
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
protected:
    QLabel *m_numberLabel;        // 收费单号
    QLineEdit *m_numberEdit;      // 收费单号
    QLabel *m_allDueIncomeLabel;            // 票号，不清楚干什么用的
    QLineEdit *m_allDueIncomeEdit;          // 票号，不清楚干什么用的

    QTableView *m_chargeRecordsView;          // 收费明细
    QStandardItemModel *m_chargeRecordsModel; // 收费明细
};

#endif // HOSIPITALISATIONCHARGEFORM_H


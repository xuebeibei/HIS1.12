#ifndef CLINICCHARGESTATISTICFORM_H
#define CLINICCHARGESTATISTICFORM_H

#include <QWidget>
#include "stdafx.h"
#include "subform.h"
#include "connectDB.h"

//-----------------------------------------------------------------------------------------------------------------------------------
// 门诊-收费统计界面
//-----------------------------------------------------------------------------------------------------------------------------------
class ClinicChargeStatisticForm : public SubForm
{
    Q_OBJECT
    
public:
    explicit ClinicChargeStatisticForm(SubForm *parent = 0);
    ~ClinicChargeStatisticForm();

    void newTableFile();
    bool saveTableFile();
    bool deleteTableFile();
    void exportTableFile();
    bool findTableFile();
    void amendTableFile();
    void previewTableFile();
    void printTableFile();

    void create();
    void setMyLayout();
    void init();
    void initTable();

protected slots:
    void updateTable();

protected:
    QLabel *m_nameLabel;                // 姓名
    QLineEdit *m_nameEdit;              // 姓名
    QLabel *m_genderLabel;              // 性别
    QComboBox *m_genderComboBox;        // 性别
    QLabel *m_startDateLabel;           // 收费单的起始查找日期
    QDateEdit *m_startDateEdit;         // 收费单的起始查找日期
    QLabel *m_endDateLabel;             // 收费单的结束查找日期
    QDateEdit *m_endDateEdit;           // 收费单的结束查找日期

    QTableView *m_resultsView;          // 统计结果
    QStandardItemModel *m_resultsModel;
};

#endif // CLINICCHARGESTATISTICFORM_H

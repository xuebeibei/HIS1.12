#ifndef CLINICPAYMENTSTATISTICFORM_H
#define CLINICPAYMENTSTATISTICFORM_H

#include <QWidget>
#include "stdafx.h"
#include "subform.h"

class ClinicPaymentStatisticForm : public SubForm
{
    Q_OBJECT
    
public:
    explicit ClinicPaymentStatisticForm(SubForm *parent = 0);
    ~ClinicPaymentStatisticForm();

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
    void setConditionSort();
    void setConditionWho();

protected:
    QLabel *m_startDateLabel;                   // 起始日期
    QDateEdit *m_startDateEdit;                 // 起始日期
    QLabel *m_endDateLabel;                     // 结束日期
    QDateEdit *m_endDateEdit;                   // 结束日期

    QButtonGroup *m_conditionSortBtnGroup;      // 收据/分类 查询条件组合
    QButtonGroup *m_conditionWhoBtnGroup;       // 科室/医生/制单人 查询条件组合


    QRadioButton *m_clinicReceiptRadio;         // 门诊收据
    QRadioButton *m_clinicSortRadio;            // 门诊分类

    QRadioButton *m_departmentRadio;            // 科室
    QRadioButton *m_doctorRadio;                // 医生
    QRadioButton *m_makerRadio;                 // 制单人

    QTableView *m_resultView;                   // 查询结果表
    QStandardItemModel *m_resultModel;          // 查询结果

    QString m_strConditionSort;                 // 收据/分类 查询条件的选中结果
    QString m_strConditionWho;                  // 科室/医生/制单人 查询条件的选中结果
};

#endif // CLINICPAYMENTSTATISTICFORM_H

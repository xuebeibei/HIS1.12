#ifndef CLINICPAYMENTSTATISTICFORM_H
#define CLINICPAYMENTSTATISTICFORM_H

#include <QWidget>
#include "stdafx.h"
#include "subform.h"
#include "connectDB.h"

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

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：selectFromDB
    // 作用：从数据库中查询一段时间内所有收据/分类 中 不同 科室/医生/制单人 的应收金额总计
    // 参数：
    // startDate - 起始日期
    // endDate - 结束日期
    // strConditionSort - 按照 收据/分类 进行筛选
    // strConditionWho - 按照 科室/医生/制单人 进行筛选
    // 返回值：无
    // 备注：无
    // 时间：2016-05-12
    //-----------------------------------------------------------------------------------------------------------------------------------
    void selectFromDB(QDate startDate, QDate endDate, QString strConditionSort,QString strConditionWho);

protected:
    QLabel *m_startDateLabel;                   // 起始日期
    QDateEdit *m_startDateEdit;                 // 起始日期
    QLabel *m_endDateLabel;                     // 结束日期
    QDateEdit *m_endDateEdit;                   // 结束日期

    QButtonGroup *m_conditionSortBtnGroup;      // 收据/分类 查询条件组合
    QButtonGroup *m_conditionWhoBtnGroup;       // 科室/医生/制单人 查询条件组合

    QGroupBox *m_conditionSortGroup;            // 收据/分类 组合框
    QRadioButton *m_clinicReceiptRadio;         // 门诊收据
    QRadioButton *m_clinicSortRadio;            // 门诊分类

    QGroupBox *m_conditionWhoGroup;             // 科室/医生/制单人 组合框
    QRadioButton *m_departmentRadio;            // 科室
    QRadioButton *m_doctorRadio;                // 医生
    QRadioButton *m_makerRadio;                 // 制单人

    QTableView *m_resultView;                   // 查询结果表
    QStandardItemModel *m_resultModel;          // 查询结果

    QString m_strConditionSort;                 // 收据/分类 查询条件的选中结果
    QString m_strConditionWho;                  // 科室/医生/制单人 查询条件的选中结果
    QVector<QString> m_vecSort;                 // 所有 收据/分类 的集合
    QVector<QString> m_vecWho;                  // 所有 科室/医生/制单人 的集合
    QVector<QVector<double> > m_dueIncome;      // 查询结果数据二元数组
};

#endif // CLINICPAYMENTSTATISTICFORM_H

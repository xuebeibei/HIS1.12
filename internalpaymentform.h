#ifndef INTERNALPAYMENTFORM_H
#define INTERNALPAYMENTFORM_H

#include <QWidget>
#include"stdafx.h"
#include"subform.h"

class InternalPaymentForm : public SubForm
{
    Q_OBJECT

public:
    explicit InternalPaymentForm(SubForm *parent = 0);
    ~InternalPaymentForm();

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
    void init();
    void initTable(QStringList strList);
    void setMyLayout();

protected slots:
    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：updateIncome
    // 作用：根据内部缴款列表的应收金额计算合计
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-27
    //-----------------------------------------------------------------------------------------------------------------------------------
    void updateIncome();

protected:
    QLabel *m_startDateLabel;         // 起始时间
    QLabel *m_endDateLabel;           // 结束时间

    QDateEdit *m_startDateEdit;       // 起始时间
    QDateEdit *m_endDateEdit;         // 结束时间

    QLabel *m_allDueIncomeLabel;      // 应收合计
    QLineEdit *m_allDueIncomeEdit;    // 应收合计

    QTableView *m_resultView;         // 查询结果表格
    QStandardItemModel *m_resultModel;// 查询结果表格
};

#endif // INTERNALPAYMENTFORM_H

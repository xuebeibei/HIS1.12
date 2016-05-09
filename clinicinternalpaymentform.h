#ifndef CLINICINTERNALPAYMENTFORM_H
#define CLINICINTERNALPAYMENTFORM_H

#include <QWidget>
#include"stdafx.h"
#include"subform.h"
#include "clinicinternalpayment.h"

class ClinicInternalPaymentForm : public SubForm
{
    Q_OBJECT
    
public:
    explicit ClinicInternalPaymentForm(SubForm *parent = 0);
    ~ClinicInternalPaymentForm();

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
    void initTable();
    void setMyLayout();
    
protected slots:

    //-----------------------------------------------------------------------------------------------------------------------------------
    // 名称：updateTable
    // 作用：根据起始和结束查询时间来更新查询结果
    // 参数：无
    // 返回值：无
    // 备注：无
    // 时间：2016-04-27
    //-----------------------------------------------------------------------------------------------------------------------------------
    void updateTable();
    void updateIncome();

private:
    QLabel *m_startDateLabel;         // 起始时间
    QLabel *m_endDateLabel;           // 结束时间

    QDateEdit *m_startDateEdit;       // 起始时间
    QDateEdit *m_endDateEdit;         // 结束时间

    QLabel *m_allDueIncomeLabel;      // 应收合计
    QLineEdit *m_allDueIncomeEdit;    // 应收合计

    QTableView *m_resultView;         // 查询结果表格
    QStandardItemModel *m_resultModel;// 查询结果表格
};

#endif // CLINICINTERNALPAYMENTFORM_H

#ifndef HOSPITALINTERNALPAYMENTFORM_H
#define HOSPITALINTERNALPAYMENTFORM_H

#include <QWidget>
#include "internalpaymentform.h"
#include "clinicinternalpayment.h"


class HospitalInternalPaymentForm : public InternalPaymentForm
{
    Q_OBJECT
    
public:
    explicit HospitalInternalPaymentForm(InternalPaymentForm *parent = 0);
    ~HospitalInternalPaymentForm();

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

    void onSummarizing();
    void onParticulars();
protected:
    void create();
    void setMyLayout();
    void init();
protected:
    QGroupBox *m_conditionSortGroup;
    QRadioButton *m_summarizing;
    QRadioButton *m_particulars;
    
};

#endif // HOSPITALINTERNALPAYMENTFORM_H

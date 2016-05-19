#ifndef CLINICINTERNALPAYMENTFORM_H
#define CLINICINTERNALPAYMENTFORM_H

#include <QWidget>
#include"stdafx.h"
#include "clinicinternalpayment.h"
#include "internalpaymentform.h"

class ClinicInternalPaymentForm : public InternalPaymentForm
{
    Q_OBJECT
    
public:
    explicit ClinicInternalPaymentForm(InternalPaymentForm *parent = 0);
    ~ClinicInternalPaymentForm();

protected:
    void create();
    void init();
    void setMyLayout();
    void initResults();
    
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
};

#endif // CLINICINTERNALPAYMENTFORM_H

#ifndef HOSPITALINTERNALPAYMENTFORM_H
#define HOSPITALINTERNALPAYMENTFORM_H

#include <QWidget>
#include "internalpaymentform.h"
#include "internalpayment.h"
#include "inpatient.h"


class HospitalInternalPaymentForm : public InternalPaymentForm
{
    Q_OBJECT
    
public:
    explicit HospitalInternalPaymentForm(InternalPaymentForm *parent = 0);
    ~HospitalInternalPaymentForm();

protected slots:
    void onSummarizing();
    void onParticulars();
    void setCondition();
protected:
    void create();
    void setMyLayout();
    void init();
    void initResults();

protected:
    QButtonGroup *m_conditionGroup;
    QRadioButton *m_summarizing;
    QRadioButton *m_particulars;
    
};

#endif // HOSPITALINTERNALPAYMENTFORM_H

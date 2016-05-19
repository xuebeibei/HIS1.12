#ifndef HOSPITALINTERPAYMENTFORM_H
#define HOSPITALINTERPAYMENTFORM_H
#include "internalpaymentform.h"

class HospitalInterPaymentForm : public InternalPaymentForm
{
public:
    HospitalInterPaymentForm();
protected slots:
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

#endif // HOSPITALINTERPAYMENTFORM_H

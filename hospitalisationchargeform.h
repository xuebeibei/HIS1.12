#ifndef HOSIPITALISATIONCHARGEFORM_H
#define HOSIPITALISATIONCHARGEFORM_H
#include <QWidget>
#include "stdafx.h"
#include "subform.h"
#include "hospitalchargetable.h"
#include "chargeform.h"
class HospitalisationChargeForm: public ChargeForm
{
    Q_OBJECT

public:
    explicit HospitalisationChargeForm(ChargeForm *parent = 0);
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
    void updateInpatientID(QString strInpatientID);
protected:
    void create();
    void setMyLayout();
    void init();

    void Read();
    bool Save();
protected:
    HospitalChargeTable *m_chargeTable;       // 收费单
    QString m_strInpatientID;
};

#endif // HOSIPITALISATIONCHARGEFORM_H


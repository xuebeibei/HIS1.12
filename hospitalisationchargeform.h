#ifndef HOSIPITALISATIONCHARGEFORM_H
#define HOSIPITALISATIONCHARGEFORM_H
#include <QWidget>
#include "stdafx.h"
#include "subform.h"
#include "hospitalchargetable.h"
#include "chargeform.h"
#include "findhospitalchargedlg.h"

class HospitalisationChargeForm: public ChargeForm
{
    Q_OBJECT

public:
    explicit HospitalisationChargeForm(ChargeForm *parent = 0);
    ~HospitalisationChargeForm();
    void init();
signals:
    void ChargeChanged();
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


    void Read();
    bool Save();
    bool Delete();
    void setAllDefaultEnable();
    void setAllUnEnable();
protected:
    QString m_InpatientID;
    HospitalChargeTable *m_chargeTable;       // 收费单
};

#endif // HOSIPITALISATIONCHARGEFORM_H


#ifndef HOSPITALISATIONREGISTRY_H
#define HOSPITALISATIONREGISTRY_H

#include <QWidget>
#include "stdafx.h"
#include "subform.h"
#include "inpatient.h"

class HospitalisationRegistry : public SubForm
{
    Q_OBJECT
    
public:
    explicit HospitalisationRegistry(SubForm *parent = 0);
    ~HospitalisationRegistry();
public slots:
    void newTableFile();
    bool saveTableFile();
    bool deleteTableFile();
    void exportTableFile();
    bool findTableFile();
    void amendTableFile();
    void previewTableFile();
    void printTableFile();
    void showInpatient(QString strID);

signals:
    void inpatientIDChanged(QString strID);
    void allInpatientsChanged();

protected:
    void create();
    void setMyLayout();
    void init();

    void setAllDefaultEnable();
    void setAllUnEnable();

    void createPatientPart();
    void createInsurancePart();
    void createHospitalPart();
    void createHospitalisationPart();

    void Read();
    void Save();
    void updateAllValue();
    void setInpatientID(QString strID);
protected:

    QLabel *m_nameLabel;                      // 姓名
    QLabel *m_genderLabel;                    // 性别
    QLabel *m_ageLabel;                       // 年龄
    QLabel *m_idCardNumLabel;                 // 身份证号码
    QLabel *m_contactsLabel;                  // 联系人
    QLabel *m_telLabel;                       // 联系方式
    QLabel *m_addressLabel;                   // 家庭住址

    QLabel *m_medicalInsuranceTypeLabel;      // 医保类型
    QLabel *m_socialSecurityNumLabel;         // 社保号码

    QLabel *m_departmentLabel;                // 科室
    QLabel *m_doctorLabel;                    // 医生
    QLabel *m_bedNumLabel;                    // 床位
    QLabel *m_nursinglevelLabel;              // 护理级别

    QLabel *m_hospitalisationNumLabel;        // 住院号
    QLabel *m_caseNumLabel;                   // 病例号
    QLabel *m_guaranteeDepositLabel;          // 押金
    QLabel *m_dateLabel;                      // 登记日期

    QLabel *m_medicalResultLabel;             // 诊断结果

    QLineEdit *m_nameEdit;                    // 姓名
    QComboBox *m_genderCombo;                 // 性别
    QLineEdit *m_ageEdit;                     // 年龄
    QLineEdit *m_idCardNumEdit;               // 身份证号码
    QLineEdit *m_contactsEdit;                // 联系人
    QLineEdit *m_telEdit;                     // 联系方式
    QTextEdit *m_addressEdit;                 // 家庭住址

    QComboBox *m_medicalInsuranceTypeCombo;   // 医保类型
    QLineEdit *m_socialSecurityNumEdit;       // 社保号码

    QLineEdit *m_departmentEdit;              // 科室
    QLineEdit *m_doctorEdit;                  // 医生
    QLineEdit *m_bedNumEdit;                  // 床位
    QComboBox *m_nursinglevelCombo;           // 护理级别

    QLineEdit *m_hospitalisationNumEdit;      // 住院号
    QLineEdit *m_caseNumEdit;                 // 病例号
    QDateEdit *m_dateEdit;                    // 登记日期

    QTextEdit *m_medicalResultEdit;           // 诊断结果

    QGroupBox *m_patientGroup;
    QGroupBox *m_insuranceGroup;
    QGroupBox *m_hospitalGroup;
    QGroupBox *m_hospitalisationGroup;

    Inpatient *m_inpatient;                   // 门诊登记表
};

#endif // HOSPITALISATIONREGISTRY_H

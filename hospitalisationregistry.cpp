#include "hospitalisationregistry.h"
#include "findregistrydlg.h"

HospitalisationRegistry::HospitalisationRegistry(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
    init();
    setAllDefaultEnable();
    newTableFile();
    setMaximumHeight(220);
}

HospitalisationRegistry::~HospitalisationRegistry()
{

}

void HospitalisationRegistry::newTableFile()
{
    setAllDefaultEnable();
    m_inpatient = new Inpatient;
    Read();
    emit inpatientIDChanged(m_inpatient->getID());
}

bool HospitalisationRegistry::saveTableFile()
{
    Save();
    setAllUnEnable();
    emit allInpatientsChanged();
    emit inpatientIDChanged(m_inpatient->getID());
    return true;
}

bool HospitalisationRegistry::deleteTableFile()
{
    if(m_inpatient->Delete())
    {
       newTableFile();
       emit allInpatientsChanged();
       return true;
    }
    else
       return false;
}

void HospitalisationRegistry::exportTableFile()
{
}

bool HospitalisationRegistry::findTableFile()
{
    FindRegistryDlg *dailog = new FindRegistryDlg;
    dailog->exec();
    QString strID = dailog->getID();
    if(!strID.isEmpty())
    {
        setInpatientID(strID);
        Read();
        setAllUnEnable();
    }

    return true;
}

void HospitalisationRegistry::amendTableFile()
{
    setAllDefaultEnable();
}

void HospitalisationRegistry::previewTableFile()
{
}

void HospitalisationRegistry::printTableFile()
{
}

void HospitalisationRegistry::showInpatient(QString strID)
{
    setInpatientID(strID);
    Read();
    setAllUnEnable();
}

void HospitalisationRegistry::create()
{  
    createPatientPart();
    createInsurancePart();
    createHospitalPart();
    createHospitalisationPart();
}

void HospitalisationRegistry::setMyLayout()
{   
    m_patientGroup = new QGroupBox;
    QGridLayout *patientLayout = new QGridLayout;

    patientLayout->addWidget(m_hospitalisationNumLabel,0,0);
    patientLayout->addWidget(m_hospitalisationNumEdit,0,1,1,3);
    patientLayout->addWidget(m_caseNumLabel,1,0);
    patientLayout->addWidget(m_caseNumEdit,1,1,1,3);
    patientLayout->addWidget(m_nameLabel,2,0);
    patientLayout->addWidget(m_nameEdit,2,1,1,3);
    patientLayout->addWidget(m_genderLabel,3,0);
    patientLayout->addWidget(m_genderCombo,3,1);
    patientLayout->addWidget(m_ageLabel,3,2);
    patientLayout->addWidget(m_ageEdit,3,3);
    patientLayout->addWidget(m_idCardNumLabel,4,0);
    patientLayout->addWidget(m_idCardNumEdit,4,1,1,3);
    m_patientGroup->setLayout(patientLayout);

    m_insuranceGroup = new QGroupBox;
    QGridLayout *insuranceLayout = new QGridLayout;
    insuranceLayout->addWidget(m_medicalInsuranceTypeLabel,0,0);
    insuranceLayout->addWidget(m_medicalInsuranceTypeCombo,0,1,1,3);
    insuranceLayout->addWidget(m_socialSecurityNumLabel,1,0);
    insuranceLayout->addWidget(m_socialSecurityNumEdit,1,1,1,3);
    insuranceLayout->addWidget(m_contactsLabel,2,0,1,1);
    insuranceLayout->addWidget(m_contactsEdit,2,1,1,1);
    insuranceLayout->addWidget(m_telLabel,2,2,1,1);
    insuranceLayout->addWidget(m_telEdit,2,3,1,1);
    insuranceLayout->addWidget(m_addressLabel,3,0,1,1);
    insuranceLayout->addWidget(m_addressEdit,3,1,1,3);

    m_insuranceGroup->setLayout(insuranceLayout);

    m_hospitalGroup = new QGroupBox;
    QGridLayout *hospitalLayout = new QGridLayout;
    hospitalLayout->addWidget(m_departmentLabel,0,0);
    hospitalLayout->addWidget(m_departmentEdit,0,1);
    hospitalLayout->addWidget(m_doctorLabel,0,2);
    hospitalLayout->addWidget(m_doctorEdit,0,3);
    hospitalLayout->addWidget(m_dateLabel,1,0);
    hospitalLayout->addWidget(m_dateEdit,1,1,1,3);
    hospitalLayout->addWidget(m_nursinglevelLabel,2,0);
    hospitalLayout->addWidget(m_nursinglevelCombo,2,1);
    hospitalLayout->addWidget(m_bedNumLabel,2,2);
    hospitalLayout->addWidget(m_bedNumEdit,2,3);
    hospitalLayout->addWidget(m_medicalResultLabel,3,0,1,1);
    hospitalLayout->addWidget(m_medicalResultEdit,3,1,1,3);
    m_hospitalGroup->setLayout(hospitalLayout);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(m_patientGroup);
    bottomLayout->addWidget(m_insuranceGroup);
    bottomLayout->addWidget(m_hospitalGroup);

    QGroupBox *allGroup = new QGroupBox;
    allGroup->setTitle("登记");
    QVBoxLayout *allLayout = new QVBoxLayout;
    allLayout->addLayout(bottomLayout);
    allGroup->setLayout(allLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(allGroup);
    setLayout(mainLayout);
}

void HospitalisationRegistry::init()
{
    m_dateEdit->setDate(QDate::currentDate());
}

void HospitalisationRegistry::setAllDefaultEnable()
{
    m_nameEdit->setReadOnly(false);
    m_genderCombo->setEnabled(true);
    m_ageEdit->setReadOnly(false);
    m_idCardNumEdit->setReadOnly(false);
    m_contactsEdit->setReadOnly(false);
    m_telEdit->setReadOnly(false);
    m_addressEdit->setReadOnly(false);

    m_medicalInsuranceTypeCombo->setEnabled(true);
    m_socialSecurityNumEdit->setReadOnly(false);

    m_departmentEdit->setReadOnly(false);
    m_doctorEdit->setReadOnly(false);
    m_bedNumEdit->setReadOnly(false);
    m_nursinglevelCombo->setEnabled(true);

    m_hospitalisationNumEdit->setReadOnly(true);
    m_caseNumEdit->setReadOnly(true);
    m_dateEdit->setReadOnly(true);
    m_medicalResultEdit->setReadOnly(false);
}

void HospitalisationRegistry::setAllUnEnable()
{
    m_nameEdit->setReadOnly(true);
    m_genderCombo->setEnabled(false);
    m_ageEdit->setReadOnly(true);
    m_idCardNumEdit->setReadOnly(true);
    m_contactsEdit->setReadOnly(true);
    m_telEdit->setReadOnly(true);
    m_addressEdit->setReadOnly(true);

    m_medicalInsuranceTypeCombo->setEnabled(false);
    m_socialSecurityNumEdit->setReadOnly(true);

    m_departmentEdit->setReadOnly(true);
    m_doctorEdit->setReadOnly(true);
    m_bedNumEdit->setReadOnly(true);
    m_nursinglevelCombo->setEnabled(false);

    m_hospitalisationNumEdit->setReadOnly(true);
    m_caseNumEdit->setReadOnly(true);
    m_dateEdit->setReadOnly(true);
    m_medicalResultEdit->setReadOnly(true);
}


void HospitalisationRegistry::createPatientPart()
{
    m_nameLabel = new QLabel(g_strNameLabel);
    m_genderLabel = new QLabel(g_strGenderLabel);
    m_ageLabel = new QLabel(g_strAgeLabel);
    m_idCardNumLabel = new QLabel(g_strIdCardLabel);
    m_contactsLabel = new QLabel(g_strContactsLabel);
    m_telLabel = new QLabel(g_strTelLabel);
    m_addressLabel = new QLabel(g_strAddressLabel);

    m_nameEdit = new QLineEdit;
    m_genderCombo = new QComboBox;
    m_genderCombo->addItem(g_strMan);
    m_genderCombo->addItem(g_strWoman);
    m_ageEdit = new QLineEdit;
    m_idCardNumEdit = new QLineEdit;
    m_contactsEdit = new QLineEdit;
    m_telEdit = new QLineEdit;
    m_addressEdit = new QTextEdit;
}

void HospitalisationRegistry::createInsurancePart()
{
    m_medicalInsuranceTypeLabel = new QLabel(g_strMedicalInsuranceTypeLabel);
    m_socialSecurityNumLabel = new QLabel(g_strSocialSecurityNumLabel);

    m_medicalInsuranceTypeCombo = new QComboBox;
    m_medicalInsuranceTypeCombo->addItem(g_strSelfPay);
    m_medicalInsuranceTypeCombo->addItem(g_strMedicare);
    m_medicalInsuranceTypeCombo->addItem(g_strNCMS);
    m_socialSecurityNumEdit = new QLineEdit;
}

void HospitalisationRegistry::createHospitalPart()
{
    m_departmentLabel = new QLabel(g_strDepartmentLabel);
    m_doctorLabel = new QLabel(g_strDoctorLabel);
    m_bedNumLabel = new QLabel(g_strBedNumLabel);
    m_nursinglevelLabel = new QLabel(g_strNursingLevelLabel);

    m_departmentEdit = new QLineEdit;
    m_doctorEdit = new QLineEdit;
    m_bedNumEdit = new QLineEdit;
    m_nursinglevelCombo = new QComboBox;
    m_nursinglevelCombo->addItem("普通");
    m_nursinglevelCombo->addItem("一级");
    m_nursinglevelCombo->addItem("二级");
    m_nursinglevelCombo->addItem("特级");
}

void HospitalisationRegistry::createHospitalisationPart()
{
    m_hospitalisationNumLabel = new QLabel(g_strHospitalisationNumLabel);
    m_caseNumLabel = new QLabel(g_strCaseNumLabel);
    m_guaranteeDepositLabel = new QLabel(g_strGuaranteeDepositLabel);
    m_dateLabel = new QLabel(g_strDateLabel);
    m_medicalResultLabel = new QLabel(g_strMedicalResultLabel);

    m_hospitalisationNumEdit = new QLineEdit;
    m_hospitalisationNumEdit->setStyleSheet(g_strLineEditNoBorder);
    m_caseNumEdit = new QLineEdit;
    m_caseNumEdit->setStyleSheet(g_strLineEditNoBorder);
    m_dateEdit = new QDateEdit;
    m_dateEdit->setCalendarPopup(true);

    m_medicalResultEdit = new QTextEdit;

}

void HospitalisationRegistry::Read()
{
    m_inpatient->Read();
    updateAllValue();
}

void HospitalisationRegistry::Save()
{
    m_inpatient->setName(m_nameEdit->text());
    m_inpatient->setGender((Gender)m_genderCombo->currentIndex());
    m_inpatient->setAge(m_ageEdit->text().toInt());
    m_inpatient->setIDCard(m_idCardNumEdit->text());

    Contacts oneContacts;
    oneContacts.setName(m_contactsEdit->text());
    oneContacts.setTel(m_telEdit->text());
    oneContacts.setAddress(m_addressEdit->toPlainText());
    m_inpatient->setContacts(oneContacts);

    m_inpatient->setDepartment(m_departmentEdit->text());
    m_inpatient->setDoctor(m_doctorEdit->text());
    m_inpatient->setBedNum(m_bedNumEdit->text().toInt());
    m_inpatient->setNursingLevel((NursingLevel)m_nursinglevelCombo->currentIndex());

    m_inpatient->setMedicalResult(m_medicalResultEdit->toPlainText());
    m_inpatient->setRegistryDate(m_dateEdit->date());

    m_inpatient->Save();
}

void HospitalisationRegistry::updateAllValue()
{
    m_nameEdit->setText(m_inpatient->getName());
    m_genderCombo->setCurrentIndex(m_inpatient->getGender());
    m_ageEdit->setText(QString::number(m_inpatient->getAge()));
    m_idCardNumEdit->setText(m_inpatient->getIDCard());
    m_contactsEdit->setText(m_inpatient->getContacts().getName());
    m_telEdit->setText(m_inpatient->getContacts().getTel());
    m_addressEdit->setText(m_inpatient->getContacts().getAddress());

    m_departmentEdit->setText(m_inpatient->getDepartment());
    m_doctorEdit->setText(m_inpatient->getDoctor());
    m_bedNumEdit->setText(QString::number(m_inpatient->getBedNum()));
    m_nursinglevelCombo->setCurrentIndex(m_inpatient->getNursingLevel());

    m_hospitalisationNumEdit->setText(m_inpatient->getID());
    m_caseNumEdit->setText(m_inpatient->getCaseID());
    m_dateEdit->setDate(m_inpatient->getRegistryDate());
    m_medicalResultEdit->setText(m_inpatient->getMedicalResult());
}

void HospitalisationRegistry::setInpatientID(QString strID)
{
    if(strID.compare(m_inpatient->getID()) != 0)
    {
        m_inpatient->setID(strID);
        emit inpatientIDChanged(strID);
    }
}

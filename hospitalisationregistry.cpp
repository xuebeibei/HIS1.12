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
}

HospitalisationRegistry::~HospitalisationRegistry()
{

}

void HospitalisationRegistry::newTableFile()
{
    m_inpatient = new Inpatient;
    Read();
}

bool HospitalisationRegistry::saveTableFile()
{
    Save();
    return true;
}

bool HospitalisationRegistry::deleteTableFile()
{
    if(m_inpatient->Delete())
    {
       newTableFile();
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
        m_inpatient->setID(strID);
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

void HospitalisationRegistry::create()
{
    createPatientPart();
    createInsurancePart();
    createHospitalPart();
    createHospitalisationPart();
}

void HospitalisationRegistry::setMyLayout()
{
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(m_patientGroup);

    QHBoxLayout *rightTopLayout = new QHBoxLayout;
    rightTopLayout->addWidget(m_hospitalisationGroup);
    rightTopLayout->addWidget(m_insuranceGroup);
    rightTopLayout->addWidget(m_hospitalGroup);

    QVBoxLayout *rightBottomLayout = new QVBoxLayout;
    rightBottomLayout->addWidget(m_medicalResultLabel);
    rightBottomLayout->addWidget(m_medicalResultEdit);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addLayout(rightTopLayout);
    rightLayout->addLayout(rightBottomLayout);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(rightLayout,1);

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
    m_NCMSNumEdit->setReadOnly(false);
    m_socialSecurityNumEdit->setReadOnly(false);

    m_departmentEdit->setReadOnly(false);
    m_doctorEdit->setReadOnly(false);
    m_bedNumEdit->setReadOnly(false);
    m_nursinglevelCombo->setEnabled(true);

    m_hospitalisationNumEdit->setReadOnly(true);
    m_caseNumEdit->setReadOnly(true);
    m_minGuaranteeDepositEdit->setReadOnly(false);
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
    m_NCMSNumEdit->setReadOnly(true);
    m_socialSecurityNumEdit->setReadOnly(true);

    m_departmentEdit->setReadOnly(true);
    m_doctorEdit->setReadOnly(true);
    m_bedNumEdit->setReadOnly(true);
    m_nursinglevelCombo->setEnabled(false);

    m_hospitalisationNumEdit->setReadOnly(true);
    m_caseNumEdit->setReadOnly(true);
    m_minGuaranteeDepositEdit->setReadOnly(true);
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

    m_patientGroup = new QGroupBox;
    QGridLayout *patientLayout = new QGridLayout;
    patientLayout->addWidget(m_nameLabel,0,0);
    patientLayout->addWidget(m_nameEdit,0,1);
    patientLayout->addWidget(m_genderLabel,1,0);
    patientLayout->addWidget(m_genderCombo,1,1);
    patientLayout->addWidget(m_ageLabel,2,0);
    patientLayout->addWidget(m_ageEdit,2,1);
    patientLayout->addWidget(m_idCardNumLabel,3,0);
    patientLayout->addWidget(m_idCardNumEdit,3,1);
    patientLayout->addWidget(m_contactsLabel,4,0);
    patientLayout->addWidget(m_contactsEdit,4,1);
    patientLayout->addWidget(m_telLabel,5,0);
    patientLayout->addWidget(m_telEdit,5,1);
    patientLayout->addWidget(m_addressLabel,6,0);
    patientLayout->addWidget(m_addressEdit,7,0,1,2);
    m_patientGroup->setLayout(patientLayout);
}

void HospitalisationRegistry::createInsurancePart()
{
    m_medicalInsuranceTypeLabel = new QLabel(g_strMedicalInsuranceTypeLabel);
    m_NCMSNumLabel = new QLabel(g_strNCMSNumLabel);
    m_socialSecurityNumLabel = new QLabel(g_strSocialSecurityNumLabel);

    m_medicalInsuranceTypeCombo = new QComboBox;
    m_medicalInsuranceTypeCombo->addItem(g_strSelfPay);
    m_medicalInsuranceTypeCombo->addItem(g_strMedicare);
    m_medicalInsuranceTypeCombo->addItem(g_strNCMS);
    m_NCMSNumEdit = new QLineEdit;
    m_socialSecurityNumEdit = new QLineEdit;

    m_insuranceGroup = new QGroupBox;
    QGridLayout *insuranceLayout = new QGridLayout;
    insuranceLayout->addWidget(m_medicalInsuranceTypeLabel,0,0);
    insuranceLayout->addWidget(m_medicalInsuranceTypeCombo,0,1);
    insuranceLayout->addWidget(m_NCMSNumLabel,1,0);
    insuranceLayout->addWidget(m_NCMSNumEdit,1,1);
    insuranceLayout->addWidget(m_socialSecurityNumLabel,2,0);
    insuranceLayout->addWidget(m_socialSecurityNumEdit,2,1);
    m_insuranceGroup->setLayout(insuranceLayout);
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

    m_hospitalGroup = new QGroupBox;
    QGridLayout *hospitalLayout = new QGridLayout;
    hospitalLayout->addWidget(m_departmentLabel,0,0);
    hospitalLayout->addWidget(m_departmentEdit,0,1);
    hospitalLayout->addWidget(m_doctorLabel,1,0);
    hospitalLayout->addWidget(m_doctorEdit,1,1);
    hospitalLayout->addWidget(m_bedNumLabel,2,0);
    hospitalLayout->addWidget(m_bedNumEdit,2,1);
    hospitalLayout->addWidget(m_nursinglevelLabel,3,0);
    hospitalLayout->addWidget(m_nursinglevelCombo,3,1);
    m_hospitalGroup->setLayout(hospitalLayout);
}

void HospitalisationRegistry::createHospitalisationPart()
{
    m_hospitalisationNumLabel = new QLabel(g_strHospitalisationNumLabel);
    m_caseNumLabel = new QLabel(g_strCaseNumLabel);
    m_guaranteeDepositLabel = new QLabel(g_strGuaranteeDepositLabel);
    m_dateLabel = new QLabel(g_strDateLabel);
    m_medicalResultLabel = new QLabel(g_strMedicalResultLabel);

    m_hospitalisationNumEdit = new QLineEdit;
    m_caseNumEdit = new QLineEdit;
    m_minGuaranteeDepositEdit = new QLineEdit;
    m_dateEdit = new QDateEdit;
    m_dateEdit->setCalendarPopup(true);

    m_medicalResultEdit = new QTextEdit;

    m_hospitalisationGroup = new QGroupBox;
    QGridLayout *hospitalisationLayout = new QGridLayout;
    hospitalisationLayout->addWidget(m_hospitalisationNumLabel,0,0);
    hospitalisationLayout->addWidget(m_hospitalisationNumEdit,0,1);
    hospitalisationLayout->addWidget(m_caseNumLabel,1,0);
    hospitalisationLayout->addWidget(m_caseNumEdit,1,1);
    hospitalisationLayout->addWidget(m_guaranteeDepositLabel,2,0);
    hospitalisationLayout->addWidget(m_minGuaranteeDepositEdit,2,1);
    hospitalisationLayout->addWidget(m_dateLabel,3,0);
    hospitalisationLayout->addWidget(m_dateEdit,3,1);
    m_hospitalisationGroup->setLayout(hospitalisationLayout);
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
    //oneInpatient->setCaseID(m_caseNumEdit->text());

    Account *oneAccount = new Account(m_inpatient->getID());
    oneAccount->setAction(payIn);
    oneAccount->setActionMoney(m_minGuaranteeDepositEdit->text().toDouble());

    m_inpatient->setAccount(oneAccount);
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
    m_minGuaranteeDepositEdit->setText(g_strNull); //??
    m_dateEdit->setDate(m_inpatient->getRegistryDate());
    m_medicalResultEdit->setText(m_inpatient->getMedicalResult());
}

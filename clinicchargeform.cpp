#include "clinicchargeform.h"
#include "findclincchargedlg.h"

ClinicChargeForm::ClinicChargeForm(ChargeForm *parent):
    ChargeForm(parent)
{
    create();
    init();
    setMyLayout();
    setAllDefaultEnable();
    newTableFile();
}

ClinicChargeForm::~ClinicChargeForm()
{
    delete m_numberLabel;
    delete m_nameLabel;
    delete m_genderLabel;
    delete m_ageLabel;
    delete m_idCardNumLabel;
    delete m_socialSecurityNumLabel;
    delete m_medicalInsuranceTypeLabel;
    delete m_departmentLabel;
    delete m_doctorLabel;
    delete m_allDueIncomeLabel;
    delete m_allRealIncomeLabel;

    delete m_numberEdit;
    delete m_nameEdit;
    delete m_ageEdit;
    delete m_idCardNumEdit;
    delete m_socialSecurityNumEdit;
    delete m_departmentEdit;
    delete m_doctorEdit;
    delete m_allDueIncomeEdit;
    delete m_allRealIncomeEdit;

    delete m_genderCombo;
    delete m_medicalInsuranceTypeCombo;

    delete m_patientGroup;
    delete m_insuranceGroup;
    delete m_doctorGroup;
    delete m_incomeGroup;
    delete m_chargeNumGroup;
}

void ClinicChargeForm::newTableFile()
{
    init();
    m_chargeTable = new ClinicChargeTable;
    Read();
    setAllDefaultEnable();
}

bool ClinicChargeForm::saveTableFile()
{
    if(Save())
    {
        setAllUnEnable();
        return true;
    }
    else
    {
        return false;
    }
}

bool ClinicChargeForm::deleteTableFile()
{

    return Delete();
}

void ClinicChargeForm::exportTableFile()
{
    QMessageBox::information(this,"提示","导出门诊收费单");
}

bool ClinicChargeForm::findTableFile()
{
    FindClincChargeDlg *findDlg = new FindClincChargeDlg;
    findDlg->exec();
    QString strId = findDlg->getId();

    if(strId.isEmpty())
    {
        return false;
    }
    else
    {
        m_chargeTable->setID(strId);
        Read();
        setAllUnEnable();
        return true;
    }
}

void ClinicChargeForm::amendTableFile()
{
    setAllDefaultEnable();
}

void ClinicChargeForm::previewTableFile()
{
    QMessageBox::information(this,"提示","预览收费单");
}

void ClinicChargeForm::printTableFile()
{
    QMessageBox::information(this,"提示","打印收费单");
}

void ClinicChargeForm::setAllDefaultEnable()
{
    m_nameEdit->setReadOnly(false);
    m_genderCombo->setEnabled(true);
    m_ageEdit->setReadOnly(false);
    m_idCardNumEdit->setReadOnly(false);
    m_socialSecurityNumEdit->setReadOnly(false);
    m_medicalInsuranceTypeCombo->setEnabled(true);
    m_departmentEdit->setReadOnly(false);
    m_doctorEdit->setReadOnly(false);
    m_allDueIncomeEdit->setReadOnly(true);
    m_allRealIncomeEdit->setReadOnly(false);
    m_numberEdit->setReadOnly(true);
    addRowButton->setEnabled(true);
    deleteRowButton->setEnabled(true);
    comboButton->setEnabled(true);
    m_chargeRecordsView->setEditTriggers(QAbstractItemView::DoubleClicked);
    m_chargeRecordsView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void ClinicChargeForm::setAllUnEnable()
{
    m_nameEdit->setReadOnly(true);

    m_genderCombo->setEnabled(false);
    m_ageEdit->setReadOnly(true);
    m_idCardNumEdit->setReadOnly(true);
    m_socialSecurityNumEdit->setReadOnly(true);
    m_medicalInsuranceTypeCombo->setEnabled(false);
    m_departmentEdit->setReadOnly(true);
    m_doctorEdit->setReadOnly(true);
    m_allDueIncomeEdit->setReadOnly(true);
    m_allRealIncomeEdit->setReadOnly(true);
    m_numberEdit->setReadOnly(true);

    addRowButton->setEnabled(false);
    deleteRowButton->setEnabled(false);
    comboButton->setEnabled(false);
    m_chargeRecordsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ClinicChargeForm::create()
{
    CreatePatientPart();
    CreateSocialSecurityPart();
    CreateDoctorPart();
    CreateIncomePart();
    CreateChargeTablePart();
    m_chargeTable = new ClinicChargeTable;
}

void ClinicChargeForm::init()
{
    m_nameEdit->setText(g_strNull);
    m_ageEdit->setText(g_strNull);
    m_idCardNumEdit->setText(g_strNull);

    m_socialSecurityNumEdit->setText(g_strNull);

    m_departmentEdit->setText(g_strNull);
    m_doctorEdit->setText(g_strNull);

    m_allDueIncomeEdit->setText(g_strNull);
    m_allRealIncomeEdit->setText(g_strNull);

    m_numberEdit->setText(g_strNull);
    initTableModel();
}

void ClinicChargeForm::initTableModel()
{
    QStringList strList;
    strList.append("收费项编码");
    strList.append("收费项名称");
    strList.append("数量");
    strList.append("单价");
    strList.append("门诊收据");
    strList.append("门诊分类");
    initTable(strList);
}

void ClinicChargeForm::CreatePatientPart()
{
    m_nameLabel = new QLabel(g_strNameLabel);
    m_nameEdit = new QLineEdit;
    m_nameLabel->setBuddy(m_nameEdit);

    m_genderLabel = new QLabel(g_strGenderLabel);
    m_genderCombo = new QComboBox;
    m_genderCombo->addItem(g_strMan);
    m_genderCombo->addItem(g_strWoman);
    m_genderLabel->setBuddy(m_genderCombo);

    m_ageLabel = new QLabel(g_strAgeLabel);
    m_ageEdit = new QLineEdit;
    m_ageLabel->setBuddy(m_ageEdit);

    m_idCardNumLabel = new QLabel(g_strIdCardLabel);
    m_idCardNumEdit = new QLineEdit;
    m_idCardNumLabel->setBuddy(m_idCardNumEdit);

    m_patientGroup = new QGroupBox(g_strPatientGroup);
    QGridLayout *patientGroupLayout = new QGridLayout;
    patientGroupLayout->addWidget(m_nameLabel,0,0);
    patientGroupLayout->addWidget(m_nameEdit,0,1);
    patientGroupLayout->addWidget(m_genderLabel,1,0);
    patientGroupLayout->addWidget(m_genderCombo,1,1);
    patientGroupLayout->addWidget(m_ageLabel,2,0);
    patientGroupLayout->addWidget(m_ageEdit,2,1);
    patientGroupLayout->addWidget(m_idCardNumLabel,3,0);
    patientGroupLayout->addWidget(m_idCardNumEdit,3,1);
    m_patientGroup->setLayout(patientGroupLayout);
}

void ClinicChargeForm::CreateSocialSecurityPart()
{
    m_socialSecurityNumLabel = new QLabel(g_strSocialSecurityNumLabel);
    m_socialSecurityNumEdit = new QLineEdit;
    m_socialSecurityNumLabel->setBuddy(m_socialSecurityNumEdit);

    m_medicalInsuranceTypeLabel = new QLabel(g_strMedicalInsuranceTypeLabel);
    m_medicalInsuranceTypeCombo = new QComboBox;
    m_medicalInsuranceTypeCombo->addItem(g_strSelfPay);
    m_medicalInsuranceTypeCombo->addItem(g_strMedicare);
    m_medicalInsuranceTypeCombo->addItem(g_strNCMS);
    m_medicalInsuranceTypeLabel->setBuddy(m_medicalInsuranceTypeCombo);

    m_insuranceGroup = new QGroupBox(g_strInsuranceGroup);
    QGridLayout *insuranceGroupLayout = new QGridLayout;
    insuranceGroupLayout->addWidget(m_socialSecurityNumLabel,0,0);
    insuranceGroupLayout->addWidget(m_socialSecurityNumEdit,0,1);
    insuranceGroupLayout->addWidget(m_medicalInsuranceTypeLabel,1,0);
    insuranceGroupLayout->addWidget(m_medicalInsuranceTypeCombo,1,1);
    m_insuranceGroup->setLayout(insuranceGroupLayout);
}

void ClinicChargeForm::CreateDoctorPart()
{
    m_departmentLabel = new QLabel(g_strDepartmentLabel);
    m_departmentEdit = new QLineEdit;
    m_departmentLabel->setBuddy(m_departmentEdit);

    m_doctorLabel = new QLabel(g_strDoctorLabel);
    m_doctorEdit = new QLineEdit;
    m_doctorLabel->setBuddy(m_doctorEdit);

    m_doctorGroup = new QGroupBox(g_strDoctorGroup);
    QGridLayout *doctorGroupLayout = new QGridLayout;
    doctorGroupLayout->addWidget(m_departmentLabel,0,0);
    doctorGroupLayout->addWidget(m_departmentEdit,0,1);
    doctorGroupLayout->addWidget(m_doctorLabel,1,0);
    doctorGroupLayout->addWidget(m_doctorEdit,1,1);
    m_doctorGroup->setLayout(doctorGroupLayout);
}

void ClinicChargeForm::CreateIncomePart()
{
    m_allRealIncomeLabel = new QLabel(g_strRealIncomeLabel);
    m_allRealIncomeEdit = new QLineEdit;
    connect(m_allDueIncomeEdit, SIGNAL(textChanged(QString)),m_allRealIncomeEdit, SLOT(setText(QString)));
    m_doctorLabel->setBuddy(m_doctorEdit);

    m_incomeGroup = new QGroupBox(g_strIncomeGroup);
    QGridLayout *incomeGroupLayout = new QGridLayout;
    incomeGroupLayout->addWidget(m_allDueIncomeLabel,0,0);
    incomeGroupLayout->addWidget(m_allDueIncomeEdit,0,1);
    incomeGroupLayout->addWidget(m_allRealIncomeLabel,1,0);
    incomeGroupLayout->addWidget(m_allRealIncomeEdit,1,1);
    m_incomeGroup->setLayout(incomeGroupLayout);
}

void ClinicChargeForm::CreateChargeTablePart()
{
    m_chargeNumGroup = new QGroupBox(g_strClinicChargeNumGroup);
    QGridLayout *chargeGroupLayout = new QGridLayout;
    chargeGroupLayout->addWidget(m_numberLabel,0,0);
    chargeGroupLayout->addWidget(m_numberEdit,0,1);
    m_chargeNumGroup->setLayout(chargeGroupLayout);
    initTableModel();
}

void ClinicChargeForm::setMyLayout()
{
    QVBoxLayout *LeftLayout = new QVBoxLayout;
    LeftLayout->addWidget(m_chargeNumGroup);
    LeftLayout->addWidget(m_patientGroup);
    LeftLayout->addWidget(m_insuranceGroup);
    LeftLayout->addWidget(m_doctorGroup);
    LeftLayout->addWidget(m_incomeGroup);
    LeftLayout->addStretch();

    QHBoxLayout *RightTopLayout = new QHBoxLayout;
    RightTopLayout->addWidget(addRowButton);
    RightTopLayout->addWidget(deleteRowButton);
    RightTopLayout->addWidget(comboButton);
    RightTopLayout->addStretch();
    QVBoxLayout *RightLayout = new QVBoxLayout;
    RightLayout->addLayout(RightTopLayout);
    RightLayout->addWidget(m_chargeRecordsView);

    QHBoxLayout *MainLayout = new QHBoxLayout;
    MainLayout->addLayout(LeftLayout);
    MainLayout->addLayout(RightLayout);
    MainLayout->setStretchFactor(RightLayout,1);
    setLayout(MainLayout);
}

bool ClinicChargeForm::Read()
{
    initTableModel();
    if(m_chargeTable->Read())
    {
        m_numberEdit->setText(m_chargeTable->getID());
        QString strName = m_chargeTable->getPatient().getName();
        m_nameEdit->setText(strName);
        m_ageEdit->setText(QString::number(m_chargeTable->getPatient().getAge()));
        m_genderCombo->setCurrentIndex(m_chargeTable->getPatient().getGender());
        m_idCardNumEdit->setText(m_chargeTable->getPatient().getIDCard());
        m_socialSecurityNumEdit->setText(m_chargeTable->getPatient().getSocialSecurityNum());
        m_medicalInsuranceTypeCombo->setCurrentIndex(m_chargeTable->getPatient().getMedicalInsuranceType());
        m_departmentEdit->setText(m_chargeTable->getPatient().getDepartment());
        m_doctorEdit->setText(m_chargeTable->getPatient().getDoctor());
        m_allDueIncomeEdit->setText(QString::number(m_chargeTable->getDueIncome()));
        m_allRealIncomeEdit->setText(QString::number(m_chargeTable->getRealImcome()));


        QVector<ChargeItem*> chargeItems = m_chargeTable->getChargeItems();
        setChargeItems(chargeItems);
        return true;
    }
    else
        return false;
}

bool ClinicChargeForm::Save()
{
    m_chargeTable->setID(m_numberEdit->text());

    Patient onePatient;
    onePatient.setName(m_nameEdit->text());
    onePatient.setGender((Gender)m_genderCombo->currentIndex());
    onePatient.setAge(m_ageEdit->text().toInt());
    onePatient.setIDCard(m_idCardNumEdit->text());
    onePatient.setSocialSecurityNum(m_socialSecurityNumEdit->text());
    onePatient.setMedicalInsuranceType((MedicalInsuranceType)m_medicalInsuranceTypeCombo->currentIndex());
    onePatient.setDepartment(m_departmentEdit->text());
    onePatient.setDoctor(m_doctorEdit->text());

    if(onePatient.getName().isEmpty())
    {
        QMessageBox::information(this,"提示","请填写姓名！");
        return false;
    }

    if(onePatient.getAge() == 0)
    {
        QMessageBox::information(this,"提示","请填写年龄！");
        return false;
    }

    m_chargeTable->setPatient(onePatient);
    m_chargeTable->setDueIncome(m_allDueIncomeEdit->text().toDouble());
    m_chargeTable->setRealIncome(m_allRealIncomeEdit->text().toDouble());
    QVector<ChargeItem*> chargeItems = getChargeItems();

    if(chargeItems.size() <= 0)
    {
        QMessageBox::information(this,"提示","请填写收费列表！");
        return false;
    }
    m_chargeTable->setChargeItems(chargeItems);

    if(m_chargeTable->Save())
    {
        return true;
    }
    else
        return false;
}

bool ClinicChargeForm::Delete()
{
    if(m_chargeTable->Delete())
    {
        newTableFile();
        return true;
    }
    else
    {
        return false;
    }
}


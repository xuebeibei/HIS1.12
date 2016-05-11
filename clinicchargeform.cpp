#include "clinicchargeform.h"
#include "findclincchargedlg.h"

ClinicChargeForm::ClinicChargeForm(SubForm *parent) :
    SubForm(parent)
{
    create();
    init();
    setMyLayout();
    setAllDefaultEnable();
    newTableFile();
}

ClinicChargeForm::~ClinicChargeForm()
{

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
    m_dueIncomeEdit->setReadOnly(true);
    m_realIncomeEdit->setReadOnly(false);
    m_chargeNumEdit->setReadOnly(true);
    addRowButton->setEnabled(true);
    deleteRowButton->setEnabled(true);
    comboButton->setEnabled(true);
    m_chargeTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    m_chargeTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
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
    m_dueIncomeEdit->setReadOnly(true);
    m_realIncomeEdit->setReadOnly(true);
    m_chargeNumEdit->setReadOnly(true);

    addRowButton->setEnabled(false);
    deleteRowButton->setEnabled(false);
    comboButton->setEnabled(false);
    m_chargeTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ClinicChargeForm::addRow()
{
    int row = m_chargeRecordsmodel->rowCount();
    m_chargeRecordsmodel->setItem(row, 5,NULL);
}

void ClinicChargeForm::deleteRow()
{
    QModelIndexList selected = m_chargeTableView->selectionModel()->selectedIndexes();
    QMap<int, int> rowMap;

    foreach (QModelIndex index, selected)
    {
        rowMap.insert(index.row(), 0);
    }

    QMapIterator<int, int> rowMapIterator(rowMap);
    rowMapIterator.toBack();
    while (rowMapIterator.hasPrevious())
    {
        rowMapIterator.previous();
        int rowToDel = rowMapIterator.key();
        m_chargeRecordsmodel->removeRow(rowToDel);
    }
}

void ClinicChargeForm::combo()
{
    QMessageBox::information(this,"提示","选择套餐！");
}

void ClinicChargeForm::updateIncome()
{
    double dIncome = 0.0;

    for(int i = 0; i < m_chargeRecordsmodel->rowCount();i++)
    {
        QStandardItem *countItem = m_chargeRecordsmodel->item(i,chargeItemCount);
        QStandardItem *priceItem = m_chargeRecordsmodel->item(i,chargeItemPrice);

        double dPrice = (priceItem == NULL) ? 0 : priceItem->text().toDouble();
        int nCount = (countItem == NULL) ? 0 : countItem->text().toInt();

        dIncome += (dPrice * nCount);
    }
    m_dueIncomeEdit->setText(QString::number(dIncome));
    m_realIncomeEdit->setText(QString::number(dIncome));
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

    m_dueIncomeEdit->setText(g_strNull);
    m_realIncomeEdit->setText(g_strNull);

    m_chargeNumEdit->setText(g_strNull);
    initTableModel();
}

void ClinicChargeForm::initTableModel()
{
    m_chargeRecordsmodel->clear();
    m_chargeRecordsmodel->setHorizontalHeaderItem(chargeItemNo, new QStandardItem(QObject::tr("收费项编码")));
    m_chargeRecordsmodel->setHorizontalHeaderItem(chargeItemName, new QStandardItem(QObject::tr("收费项名称")));
    m_chargeRecordsmodel->setHorizontalHeaderItem(chargeItemCount, new QStandardItem(QObject::tr("数量")));
    m_chargeRecordsmodel->setHorizontalHeaderItem(chargeItemPrice, new QStandardItem(QObject::tr("单价")));
    m_chargeRecordsmodel->setHorizontalHeaderItem(clinicReceipt, new QStandardItem(QObject::tr("门诊收据")));
    m_chargeRecordsmodel->setHorizontalHeaderItem(clinicSort, new QStandardItem(QObject::tr("门诊分类")));
    m_chargeRecordsmodel->setItem(0, 5, NULL);
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
    m_dueIncomeLabel = new QLabel(g_strDueIncomeLabel);
    m_dueIncomeEdit = new QLineEdit;
    m_dueIncomeLabel->setBuddy(m_dueIncomeEdit);

    m_realIncomeLabel = new QLabel(g_strRealIncomeLabel);
    m_realIncomeEdit = new QLineEdit;
    m_doctorLabel->setBuddy(m_doctorEdit);

    m_incomeGroup = new QGroupBox(g_strIncomeGroup);
    QGridLayout *incomeGroupLayout = new QGridLayout;
    incomeGroupLayout->addWidget(m_dueIncomeLabel,0,0);
    incomeGroupLayout->addWidget(m_dueIncomeEdit,0,1);
    incomeGroupLayout->addWidget(m_realIncomeLabel,1,0);
    incomeGroupLayout->addWidget(m_realIncomeEdit,1,1);
    m_incomeGroup->setLayout(incomeGroupLayout);
}

void ClinicChargeForm::CreateChargeTablePart()
{
    m_chargeNumLabel = new QLabel(g_strClincChargeNumLabel);
    m_chargeNumEdit = new QLineEdit;
    m_chargeNumLabel->setBuddy(m_chargeNumEdit);

    m_chargeNumGroup = new QGroupBox(g_strClinicChargeNumGroup);
    QGridLayout *chargeGroupLayout = new QGridLayout;
    chargeGroupLayout->addWidget(m_chargeNumLabel,0,0);
    chargeGroupLayout->addWidget(m_chargeNumEdit,0,1);
    m_chargeNumGroup->setLayout(chargeGroupLayout);

    addRowButton = new QToolButton;
    addRowButton->setIcon(QIcon(g_strIconPath + "addRow.png"));
    connect(addRowButton, SIGNAL(clicked()), this, SLOT(addRow()));
    deleteRowButton = new QToolButton;
    deleteRowButton->setIcon(QIcon(g_strIconPath + "deleteRow.png"));
    connect(deleteRowButton, SIGNAL(clicked()), this, SLOT(deleteRow()));
    comboButton = new QToolButton;
    comboButton->setIcon(QIcon(g_strIconPath + "combo.png"));
    connect(comboButton, SIGNAL(clicked()), this, SLOT(combo()));

    m_chargeTableView = new QTableView;
    m_chargeRecordsmodel = new QStandardItemModel;
    m_chargeTableView->setModel(m_chargeRecordsmodel);
    connect(m_chargeRecordsmodel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this, SLOT(updateIncome()));
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
    //RightTopLayout->addWidget(comboButton);
    RightTopLayout->addStretch();
    QVBoxLayout *RightLayout = new QVBoxLayout;
    RightLayout->addLayout(RightTopLayout);
    RightLayout->addWidget(m_chargeTableView);

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
        m_chargeNumEdit->setText(m_chargeTable->getID());
        QString strName = m_chargeTable->getPatient().getName();
        m_nameEdit->setText(strName);
        m_ageEdit->setText(QString::number(m_chargeTable->getPatient().getAge()));
        m_genderCombo->setCurrentIndex(m_chargeTable->getPatient().getGender());
        m_idCardNumEdit->setText(m_chargeTable->getPatient().getIDCard());
        m_socialSecurityNumEdit->setText(m_chargeTable->getPatient().getSocialSecurityNum());
        m_medicalInsuranceTypeCombo->setCurrentIndex(m_chargeTable->getPatient().getMedicalInsuranceType());
        m_departmentEdit->setText(m_chargeTable->getPatient().getDepartment());
        m_doctorEdit->setText(m_chargeTable->getPatient().getDoctor());
        m_dueIncomeEdit->setText(QString::number(m_chargeTable->getDueIncome()));
        m_realIncomeEdit->setText(QString::number(m_chargeTable->getRealImcome()));


        QVector<ClinicChargeItem*> chargeItems = m_chargeTable->getChargeItems();
        for(int index = 0; index< chargeItems.size();index++)
        {
            ClinicChargeItem *item = new ClinicChargeItem(chargeItems.at(index));

            m_chargeRecordsmodel->setItem(index, chargeItemNo, new QStandardItem(item->getChargeItemNo()));
            m_chargeRecordsmodel->setItem(index, chargeItemName, new QStandardItem(item->getChargeItemName()));
            m_chargeRecordsmodel->setItem(index, chargeItemCount, new QStandardItem(QString::number(item->getChargeItemCount())));
            m_chargeRecordsmodel->setItem(index, chargeItemPrice, new QStandardItem(QString::number(item->getChargeItemPrice())));
            m_chargeRecordsmodel->setItem(index, clinicReceipt, new QStandardItem(item->getClinicReceipt()));
            m_chargeRecordsmodel->setItem(index, clinicSort, new QStandardItem(item->getClinicSort()));
        }
        return true;
    }
    else
        return false;
}

bool ClinicChargeForm::Save()
{
    m_chargeTable->setID(m_chargeNumEdit->text());

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
    m_chargeTable->setDueIncome(m_dueIncomeEdit->text().toDouble());
    m_chargeTable->setRealIncome(m_realIncomeEdit->text().toDouble());

    QVector<ClinicChargeItem*> chargeItems;
    for(int row = 0; row< m_chargeRecordsmodel->rowCount();row++)
    {
        ClinicChargeItem *chargeItem = new ClinicChargeItem;
        for(int column = 0; column < m_chargeRecordsmodel->columnCount();column++)
        {
            QStandardItem *modelItem = m_chargeRecordsmodel->item(row,column);

            if(modelItem == NULL)
            {
                continue;
            }
            else
            {
                QString strData = modelItem->text();
                switch(column)
                {
                case chargeItemNo:
                {
                    chargeItem->setChargeItemNo(strData);
                    break;
                }
                case chargeItemName:
                {
                    chargeItem->setChargeItemName(strData);
                    break;
                }
                case chargeItemCount:
                {
                    int nCount = strData.isEmpty() ? 0 : strData.toInt();
                    chargeItem->setChargeItemCount(nCount);
                    break;
                }
                case chargeItemPrice:
                {
                    double nPrice= strData.isEmpty() ? 0 : strData.toDouble();
                    chargeItem->setChargeItemPrice(nPrice);
                    break;
                }
                case clinicReceipt:
                {
                    chargeItem->setClinicReceipt(strData);
                    break;
                }
                case clinicSort:
                {
                    chargeItem->setClinicSort(strData);
                    break;
                }
                default:
                    break;
                }
            }
        }
        if(chargeItem->isEmptyItem())
        {
            continue;
        }
        chargeItem->setClinicChargeId(m_chargeNumEdit->text());
        chargeItems.append(chargeItem);
    }
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


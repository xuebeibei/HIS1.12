#include "hospitalisationchargeform.h"

HospitalisationChargeForm::HospitalisationChargeForm(ChargeForm *parent) :
    ChargeForm(parent)
{
    create();
    setMyLayout();
    setMinimumHeight(240);
    init();
}

HospitalisationChargeForm::~HospitalisationChargeForm()
{
}

void HospitalisationChargeForm::newTableFile()
{
    m_chargeTable = new HospitalChargeTable;
    Read();
}

bool HospitalisationChargeForm::saveTableFile()
{
    return Save();
}

bool HospitalisationChargeForm::deleteTableFile()
{
    return true;
}

void HospitalisationChargeForm::exportTableFile()
{
}

bool HospitalisationChargeForm::findTableFile()
{
    return true;
}

void HospitalisationChargeForm::amendTableFile()
{
}

void HospitalisationChargeForm::previewTableFile()
{
}

void HospitalisationChargeForm::printTableFile()
{
}

void HospitalisationChargeForm::create()
{

}

void HospitalisationChargeForm::setMyLayout()
{
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_newButton);
    topLayout->addWidget(m_saveButton);
    topLayout->addWidget(m_deleteButton);
    topLayout->addWidget(m_amendButton);
    topLayout->addWidget(m_findButton);
    topLayout->addStretch();
    topLayout->addWidget(addRowButton);
    topLayout->addWidget(deleteRowButton);
    topLayout->addWidget(comboButton);

    QGroupBox *leftTopGroup = new QGroupBox;
    QGridLayout *leftTopLayout = new QGridLayout;
    leftTopLayout->addWidget(m_numberLabel,0,0);
    leftTopLayout->addWidget(m_numberEdit,0,1);
    leftTopLayout->addWidget(m_allDueIncomeLabel,1,0);
    leftTopLayout->addWidget(m_allDueIncomeEdit,1,1);
    leftTopGroup->setLayout(leftTopLayout);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(leftTopGroup);
    leftLayout->addStretch();

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(m_chargeRecordsView);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addLayout(leftLayout);
    bottomLayout->addLayout(rightLayout);
    bottomLayout->setStretchFactor(rightLayout,1);

    QGroupBox *allGroup = new QGroupBox;
    allGroup->setTitle("收费");
    QVBoxLayout *allLayout = new QVBoxLayout;
    allLayout->addLayout(topLayout);
    allLayout->addLayout(bottomLayout);
    allGroup->setLayout(allLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(allGroup);
    setLayout(mainLayout);
}

void HospitalisationChargeForm::init()
{
    QStringList strList;
    strList.append("收费项编码");
    strList.append("收费项名称");
    strList.append("数量");
    strList.append("单价");
    strList.append("住院收据");
    strList.append("住院分类");
    initTable(strList);
}

void HospitalisationChargeForm::Read()
{
    if(m_chargeTable->Read())
    {
        QVector<ChargeItem*> chargeItems = m_chargeTable->getChargeItems();
        setChargeItems(chargeItems);
    }

    m_numberEdit->setText(m_chargeTable->getID());
    m_allDueIncomeEdit->setText(QString::number(m_chargeTable->getDueIncome()));

}

bool HospitalisationChargeForm::Save()
{
    QVector<ChargeItem*> chargeItems = getChargeItems();
    m_chargeTable->setChargeItems(chargeItems);

    return m_chargeTable->Save();
}

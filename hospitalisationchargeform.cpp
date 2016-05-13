#include "hospitalisationchargeform.h"

HospitalisationChargeForm::HospitalisationChargeForm(SubForm *parent) :
    SubForm(parent)
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
    return true;
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
    m_numberLabel = new QLabel("收费单号：");
    m_numberEdit = new QLineEdit;
    m_numberEdit->setStyleSheet(g_strLineEditNoBorder);
    m_numberEdit->setReadOnly(true);
    m_allDueIncomeLabel = new QLabel("应收合计：");
    m_allDueIncomeEdit = new QLineEdit;
    m_allDueIncomeEdit->setStyleSheet(g_strLineEditNoBorder);
    m_allDueIncomeEdit->setReadOnly(true);

    m_chargeRecordsView = new QTableView;
    m_chargeRecordsModel = new QStandardItemModel;
    m_chargeRecordsView->setModel(m_chargeRecordsModel);
}

void HospitalisationChargeForm::setMyLayout()
{
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
    allLayout->addLayout(m_topLayout);
    allLayout->addLayout(bottomLayout);
    allGroup->setLayout(allLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(allGroup);
    setLayout(mainLayout);
}

void HospitalisationChargeForm::init()
{
    initTable();
}

void HospitalisationChargeForm::initTable()
{
    QStringList strList;
    strList.append("收费项编码");
    strList.append("收费项名称");
    strList.append("数量");
    strList.append("单价");
    strList.append("住院收据");
    strList.append("住院分类");

    m_chargeRecordsModel->clear();
    for(int i = 0; i < strList.size(); i++)
    {
        m_chargeRecordsModel->setHorizontalHeaderItem(i,new QStandardItem(strList.at(i)));
    }
    if(strList.size() > 0)
        m_chargeRecordsModel->setItem(0, strList.size()-1, NULL);
}

void HospitalisationChargeForm::Read()
{
    if(m_chargeTable->Read())
    {
        QVector<ChargeItem*> vec = m_chargeTable->getChargeItems();
        for(int i = 0; i < vec.size(); i++)
        {
            m_chargeRecordsModel->setItem(i, 0, new QStandardItem(vec.at(i)->getChargeItemNo()));
            m_chargeRecordsModel->setItem(i, 1, new QStandardItem(vec.at(i)->getChargeItemName()));
            m_chargeRecordsModel->setItem(i, 2, new QStandardItem(vec.at(i)->getChargeItemCount()));
            m_chargeRecordsModel->setItem(i, 3, new QStandardItem(vec.at(i)->getChargeItemPrice()));
            //m_chargeRecordsModel->setItem(i, 4, new QStandardItem(vec.at(i)->getC()));
           // m_chargeRecordsModel->setItem(i, 5, new QStandardItem(vec.at(i)->getChargeId()));
        }
    }

    m_numberEdit->setText(m_chargeTable->getID());
    m_allDueIncomeEdit->setText(QString::number(m_chargeTable->getDueIncome()));

}

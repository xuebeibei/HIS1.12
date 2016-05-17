#include "findhospitalchargedlg.h"


FindHospitalChargeDlg::FindHospitalChargeDlg(FindDlg *parent)
    :FindDlg(parent)
{
    create();
    setMyLayout();
    init();
}

FindHospitalChargeDlg::~FindHospitalChargeDlg()
{
    delete m_chargeIDLabel;
    delete m_chargeIDEdit;
}

void FindHospitalChargeDlg::setInpatientID(QString strInpatientID)
{
    m_InpatientID = strInpatientID;
}

void FindHospitalChargeDlg::create()
{
    m_chargeIDLabel = new QLabel("收费单号：");
    m_chargeIDEdit  = new QLineEdit;
}

void FindHospitalChargeDlg::setMyLayout()
{
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_chargeIDLabel);
    topLayout->addWidget(m_chargeIDEdit);
    topLayout->addStretch();
    topLayout->addWidget(m_findButton);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(m_choiseButton);
    bottomLayout->addWidget(m_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_resultsView);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
}

void FindHospitalChargeDlg::init()
{
    m_chargeIDEdit->setText(g_strNull);
    initResults();
}

void FindHospitalChargeDlg::initResults()
{
    QStringList strList;
    strList.append("收费单号");
    strList.append("收费时间");
    strList.append("应收合计");
    initTable(strList);
}

void FindHospitalChargeDlg::find()
{
    initResults();
    QVector<Account*> vec = Account::getRecords(m_InpatientID);
    int nIndex = 0;
    for(int i = 0; i < vec.size(); i++)
    {
        Account *temp = vec.at(i);
        QString strID = m_chargeIDEdit->text();

        if(!strID.isEmpty() && (QString::compare(temp->getID(),strID) != 0 ))
        {
            continue;
        }

        if(QString::compare(temp->getID().left(g_strHospitalChargeNumPR.length()),g_strHospitalChargeNumPR) == 0)
        {
            m_resultsModel->setItem(nIndex,0,new QStandardItem(temp->getID()));
            m_resultsModel->setItem(nIndex,1,new QStandardItem(temp->getDateTime().toString("yyyy-MM-dd")));
            m_resultsModel->setItem(nIndex,2,new QStandardItem(QString::number(temp->getActionMoney())));
            nIndex++;
        }
    }
}

#include "findregistrydlg.h"
#include "inpatient.h"

FindRegistryDlg::FindRegistryDlg(FindDlg *parent):
    FindDlg(parent)
{
    create();
    setMyLayout();
    init();
}

FindRegistryDlg::~FindRegistryDlg()
{
}

void FindRegistryDlg::create()
{
    m_hospitalisationNumLabel = new QLabel(g_strHospitalisationNumLabel);
    m_hospitalisationNumEdit = new QLineEdit;
    m_nameLabel = new QLabel(g_strNameLabel);
    m_nameEdit = new QLineEdit;
    m_genderLabel = new QLabel(g_strGenderLabel);
    m_genderCombo = new QComboBox;
    m_genderCombo->addItem(g_strMan);
    m_genderCombo->addItem(g_strWoman);
}

void FindRegistryDlg::setMyLayout()
{
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_hospitalisationNumLabel);
    topLayout->addWidget(m_hospitalisationNumEdit);
    topLayout->addWidget(m_nameLabel);
    topLayout->addWidget(m_nameEdit);
    topLayout->addWidget(m_genderLabel);
    topLayout->addWidget(m_genderCombo);
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

void FindRegistryDlg::init()
{
    initResults();
}

void FindRegistryDlg::initResults()
{
    QStringList strList;
    strList.append("住院号");
    strList.append("姓名");
    strList.append("住院时间");
    strList.append("科室");
    strList.append("医生");
    initTable(strList);
}

void FindRegistryDlg::find()
{
    QString strID = m_hospitalisationNumEdit->text();
    QString strName = m_nameEdit->text();
    Gender eGender = (Gender)m_genderCombo->currentIndex();

    initResults();

    QVector<Inpatient *> vec = Inpatient::selectFromDB(strID, strName, eGender);

    for(int i = 0; i < vec.size();i++)
    {
        Inpatient *temp = vec.at(i);
        m_resultsModel->setItem(i,0,new QStandardItem(temp->getID()));
        m_resultsModel->setItem(i,1,new QStandardItem(temp->getName()));
        m_resultsModel->setItem(i,2,new QStandardItem(temp->getRegistryDate().toString("yyyy-MM-dd")));
        m_resultsModel->setItem(i,3,new QStandardItem(temp->getDepartment()));
        m_resultsModel->setItem(i,4,new QStandardItem(temp->getDoctor()));
    }
    m_resultsView->setModel(m_resultsModel);
}

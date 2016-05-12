#include "allinpatientsform.h"

AllInpatientsForm::AllInpatientsForm(QWidget *parent) :
    QWidget(parent)
{
    create();
    setMyLayout();
    setMaximumWidth(200);
}

void AllInpatientsForm::create()
{
    m_allBedButton = new QRadioButton;
    m_allBedButton->setIcon(QIcon(g_strIconPath + "bed.png"));
    m_allPatientButton = new QRadioButton;
    m_allPatientButton->setIcon(QIcon(g_strIconPath + "patient.png"));

    m_setButton = new QToolButton;
    m_setButton->setIcon(QIcon(g_strIconPath + "set.png"));
    m_tree = new QTreeView;
    m_allBedNumLabel = new QLabel("剩余床位:");
    m_allInpatientNumLabel = new QLabel("患者数量:");
    m_allBedNum = new QLineEdit;
    m_allBedNum->setStyleSheet(g_strLineEditNoBorder);
    m_allInpatientNum = new QLineEdit;
    m_allInpatientNum->setStyleSheet(g_strLineEditNoBorder);
}

void AllInpatientsForm::setMyLayout()
{
    QHBoxLayout *toolLayout = new QHBoxLayout;
    toolLayout->addWidget(m_allBedButton);
    toolLayout->addWidget(m_allPatientButton);
    toolLayout->addStretch();
    toolLayout->addWidget(m_setButton);

    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->addLayout(toolLayout);
    topLayout->addWidget(m_tree);

    QGroupBox *bottomGroup = new QGroupBox;
    QGridLayout *bottomLayout = new QGridLayout;
    bottomLayout->addWidget(m_allBedNumLabel,0,0);
    bottomLayout->addWidget(m_allBedNum,0,1);
    bottomLayout->addWidget(m_allInpatientNumLabel,1,0);
    bottomLayout->addWidget(m_allInpatientNum,1,1);
    bottomGroup->setLayout(bottomLayout);

    QGroupBox *allGroup = new QGroupBox;
    allGroup->setTitle("床位总揽");
    QVBoxLayout *allLayout = new QVBoxLayout;
    allLayout->addLayout(topLayout);
    allLayout->addWidget(bottomGroup);
    allGroup->setLayout(allLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(allGroup);
    setLayout(mainLayout);
}

void AllInpatientsForm::init()
{

}

#include "allinpatientsform.h"

AllInpatientsForm::AllInpatientsForm(QWidget *parent) :
    QWidget(parent)
{
    create();
    setMyLayout();
    setMaximumWidth(200);
    updateAllInpatients();
}

AllInpatientsForm::~AllInpatientsForm()
{
    delete m_tree;
    delete m_allBedNumLabel;
    delete m_allInpatientNumLabel;
    delete m_allBedNum;
    delete m_allInpatientNum;
}

void AllInpatientsForm::create()
{
    m_InpatientID = "";
    m_tree = new QTreeView;
    m_tree->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_treeModel = new QStandardItemModel;
    m_tree->setModel(m_treeModel);
    connect(m_tree, SIGNAL(doubleClicked(QModelIndex)),this,SLOT(setInpatientID()));


    m_allBedNumLabel = new QLabel("剩余床位:");
    m_allInpatientNumLabel = new QLabel("患者数量:");
    m_allBedNum = new QLineEdit;
    m_allBedNum->setStyleSheet(g_strLineEditNoBorder);
    m_allInpatientNum = new QLineEdit;
    m_allInpatientNum->setStyleSheet(g_strLineEditNoBorder);
}

void AllInpatientsForm::setMyLayout()
{
    QVBoxLayout *topLayout = new QVBoxLayout;
    topLayout->addWidget(m_tree);

    QGroupBox *numberGroup = new QGroupBox;
    QGridLayout *numberLayout = new QGridLayout;
    numberLayout->addWidget(m_allBedNumLabel,0,0);
    numberLayout->addWidget(m_allBedNum,0,1);
    numberLayout->addWidget(m_allInpatientNumLabel,1,0);
    numberLayout->addWidget(m_allInpatientNum,1,1);
    numberGroup->setLayout(numberLayout);

    QGroupBox *allGroup = new QGroupBox;
    allGroup->setTitle("总览");
    QVBoxLayout *allLayout = new QVBoxLayout;
    allLayout->addLayout(topLayout);
    allLayout->addWidget(numberGroup);
    allGroup->setLayout(allLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(allGroup);
    setLayout(mainLayout);
}

void AllInpatientsForm::init()
{
    m_treeModel->clear();
    m_treeModel->setHorizontalHeaderLabels(QStringList()<<QStringLiteral("床位")<<QStringLiteral("姓名"));
}


void AllInpatientsForm::setInpatientID()
{
    QModelIndex index = m_tree->currentIndex();
    if(index.isValid() && index.parent().isValid())
    {
        QString strDepartment = index.parent().data().toString();

        QVector<Inpatient *> vec;
        QMap<QString,QVector<Inpatient*> >::iterator iter;
        iter = map.find(strDepartment);
        if(iter != map.end())
        {
            vec = iter.value();
            QString strID = vec.at(index.row())->getID();
            if(QString::compare(strID,m_InpatientID) != 0)
            {
                m_InpatientID = strID;
                emit UpdateInpatientID(m_InpatientID);
            }
        }
    }
}

void AllInpatientsForm::updateAllInpatients()
{
    init();
    getAllInpatients();
    QVector<Inpatient *> vec;
    QMap<QString,QVector<Inpatient*> >::iterator iter;

    int index = 0;
    for(iter = map.begin(); iter != map.end();iter++)
    {
        QStandardItem *departmentItem = new QStandardItem(iter.key());
        m_treeModel->insertRow(index, departmentItem);
        vec.resize(0);
        vec = iter.value();
        for(int i = 0;i < vec.size();i++)
        {
            QStandardItem* itemProject = new QStandardItem(QString::number(vec.at(i)->getBedNum()));
            departmentItem->setChild(i,itemProject);
            departmentItem->setChild(itemProject->index().row(),1,new QStandardItem(vec.at(i)->getName()));
        }

        index++;
    }

    m_tree->setModel(m_treeModel);
}


void AllInpatientsForm::getAllInpatients()
{
    QVector<Inpatient *> allInpatients = Inpatient::selectFromDB("", "", allGender);
    map.clear();

    QVector<Inpatient *> vec;
    QMap<QString,QVector<Inpatient*> >::iterator iter;
    for(int i = 0; i < allInpatients.size();i++)
    {
        vec.resize(0);

        Inpatient *tempInpatient = allInpatients.at(i);
        QString strDepartment = tempInpatient->getDepartment();

        iter = map.find(strDepartment);
        if(iter != map.end())
        {
            vec = iter.value();
        }
        vec.append(tempInpatient);

        map.insert(tempInpatient->getDepartment(),vec);
    }
}

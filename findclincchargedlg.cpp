#include "findclincchargedlg.h"
#include "connectDB.h"

FindClincChargeDlg::FindClincChargeDlg(QWidget *parent) :
    QDialog(parent)
{
    m_strId = g_strNull;
    create();
    init();
    setMyLayout();
}

FindClincChargeDlg::~FindClincChargeDlg()
{

}

QString FindClincChargeDlg::getId()
{
    return m_strId;
}

void FindClincChargeDlg::create()
{
    m_chargeNumLabel = new QLabel(g_strClincChargeNumLabel);
    m_chargeNumEdit = new QLineEdit();
    m_chargeNumLabel->setBuddy(m_chargeNumEdit);

    m_nameLabel = new QLabel(g_strNameLabel);
    m_nameEdit = new QLineEdit();
    m_nameLabel->setBuddy(m_nameEdit);

    m_genderLabel = new QLabel(g_strGenderLabel);
    m_genderComboBox = new QComboBox;
    m_genderComboBox->addItem(g_strMan);
    m_genderComboBox->addItem(g_strWoman);

    m_findButton = new QToolButton;
    m_findButton->setIcon(QIcon(g_strIconPath + "find.png"));
    connect(m_findButton, SIGNAL(clicked()), this, SLOT(find()));

    m_resultsTableView = new QTableView;
    m_resultsModel = new QStandardItemModel;
    m_resultsTableView->setModel(m_resultsModel);
    m_resultsTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_resultsTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(m_resultsTableView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(choise()));

    m_choiseButton = new QPushButton(g_strChoiseButton);
    connect(m_choiseButton, SIGNAL(clicked()), this, SLOT(choise()));
    m_cancelButton = new QPushButton(g_strCancelButton);
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}

void FindClincChargeDlg::setMyLayout()
{
    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(m_chargeNumLabel);
    topLayout->addWidget(m_chargeNumEdit);
    topLayout->addWidget(m_nameLabel);
    topLayout->addWidget(m_nameEdit);
    topLayout->addWidget(m_genderLabel);
    topLayout->addWidget(m_genderComboBox);
    topLayout->addStretch();
    topLayout->addWidget(m_findButton);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(m_choiseButton);
    bottomLayout->addWidget(m_cancelButton);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(m_resultsTableView);
    mainLayout->addLayout(bottomLayout);

    setLayout(mainLayout);
}

void FindClincChargeDlg::init()
{
    m_chargeNumEdit->setText(g_strNull);
    m_nameEdit->setText(g_strNull);
    m_genderComboBox->setCurrentIndex(man);
    initTable();
}

void FindClincChargeDlg::initTable()
{
    m_resultsModel->clear();
    m_resultsModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("收费单号")));
    m_resultsModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("时间")));
    m_resultsModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("姓名")));
    m_resultsModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("科室")));
    m_resultsModel->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("医生")));
    m_resultsModel->setItem(0, 3, NULL);
}

void FindClincChargeDlg::find()
{
    initTable();
    QString strId = m_chargeNumEdit->text();
    QString strName = m_nameEdit->text();
    Gender eGender = (Gender)m_genderComboBox->currentIndex();
    if(myDB::connectDB())
    {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable(g_strClinicCharge);
        QString strSql = "" , strTemp = "";

        strTemp = "Gender = " + QString::number((int)eGender);
        strSql += strTemp;

        if(!strId.isEmpty())
        {
            strTemp = " and ID = \'" + strId + "\'";
            strSql += strTemp;
        }
        if(!strName.isEmpty())
        {
            strTemp = " and Name = \'" + strName + "\'";
            strSql += strTemp;
        }

        model->setFilter(strSql);
        model->select();

        for(int i = 0; i < model->rowCount();i++)
        {
            QSqlRecord record = model->record(i);
            m_resultsModel->setItem(i,0,new QStandardItem(record.value("ID").toString()));
            m_resultsModel->setItem(i,1,new QStandardItem(record.value("Time").toString()));
            m_resultsModel->setItem(i,2,new QStandardItem(record.value("Name").toString()));
            m_resultsModel->setItem(i,3,new QStandardItem(record.value("Department").toString()));
            m_resultsModel->setItem(i,4,new QStandardItem(record.value("Doctor").toString()));
        }
    }
}

void FindClincChargeDlg::choise()
{
    QModelIndex index = m_resultsTableView->currentIndex();
    if(index.isValid())
    {
        QStandardItem *item = m_resultsModel->item(index.row(),0);
        m_strId = item->text();
        close();
    }
}

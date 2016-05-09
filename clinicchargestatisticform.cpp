#include "clinicchargestatisticform.h"

ClinicChargeStatisticForm::ClinicChargeStatisticForm(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
    init();
}

ClinicChargeStatisticForm::~ClinicChargeStatisticForm()
{
}

void ClinicChargeStatisticForm::newTableFile()
{
}

bool ClinicChargeStatisticForm::saveTableFile()
{
    return true;
}

bool ClinicChargeStatisticForm::deleteTableFile()
{
    return true;
}

void ClinicChargeStatisticForm::exportTableFile()
{
}

bool ClinicChargeStatisticForm::findTableFile()
{
    return true;
}

void ClinicChargeStatisticForm::amendTableFile()
{
}

void ClinicChargeStatisticForm::previewTableFile()
{
}

void ClinicChargeStatisticForm::printTableFile()
{
}

void ClinicChargeStatisticForm::create()
{
    m_nameLabel = new QLabel(g_strNameLabel);
    m_nameEdit = new QLineEdit;
    connect(m_nameEdit, SIGNAL(textChanged(QString)), this, SLOT(updateTable()));

    m_genderLabel = new QLabel(g_strGenderLabel);
    m_genderComboBox = new QComboBox;
    connect(m_genderComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateTable()));

    m_startDateLabel = new QLabel(g_strStartDateLabel);
    m_startDateEdit = new QDateEdit;
    m_startDateEdit->setCalendarPopup(true);
    m_startDateEdit->setMaximumDate(QDate::currentDate());
    connect(m_startDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(updateTable()));

    m_endDateLabel = new QLabel(g_strEndDateLabel);
    m_endDateEdit = new QDateEdit;
    m_endDateEdit->setCalendarPopup(true);
    m_endDateEdit->setMaximumDate(QDate::currentDate());
    connect(m_endDateEdit, SIGNAL(dateChanged(QDate)), this, SLOT(updateTable()));

    m_resultsView = new QTableView;
    m_resultsModel = new QStandardItemModel;
    m_resultsView->setModel(m_resultsModel);
    m_resultsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_resultsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void ClinicChargeStatisticForm::setMyLayout()
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *leftLayout = new QVBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout;
    QGridLayout *leftTopLayout = new QGridLayout;

    leftTopLayout->addWidget(m_nameLabel,0,0);
    leftTopLayout->addWidget(m_nameEdit,0,1);
    leftTopLayout->addWidget(m_genderLabel,1,0);
    leftTopLayout->addWidget(m_genderComboBox,1,1);
    leftTopLayout->addWidget(m_startDateLabel,2,0);
    leftTopLayout->addWidget(m_startDateEdit,2,1);
    leftTopLayout->addWidget(m_endDateLabel,3,0);
    leftTopLayout->addWidget(m_endDateEdit,3,1);

    leftLayout->addLayout(leftTopLayout);
    leftLayout->addStretch();

    rightLayout->addWidget(m_resultsView);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    mainLayout->setStretchFactor(rightLayout, 1);

    setLayout(mainLayout);
}

void ClinicChargeStatisticForm::init()
{
    initTable();
    m_genderComboBox->addItem(g_strMan);
    m_genderComboBox->addItem(g_strWoman);
    m_startDateEdit->setDate(QDate::currentDate());
    m_endDateEdit->setDate(QDate::currentDate());
}


void ClinicChargeStatisticForm::updateTable()
{
    initTable();
    QDate startDate = m_startDateEdit->date();
    QDate endDate = m_endDateEdit->date();

    if(startDate > endDate)
        return;

    QString strName = m_nameEdit->text();
    Gender eGender = (Gender)m_genderComboBox->currentIndex();
    if(myDB::connectDB())
    {
        QSqlTableModel *model = new QSqlTableModel;
        model->setTable(g_strClinicCharge);
        QString strSql = "" , strTemp = "";

        strTemp = "Gender = " + QString::number((int)eGender);
        strSql += strTemp;

        if(!strName.isEmpty())
        {
            strTemp = " and Name = \'" + strName + "\'";
            strSql += strTemp;
        }

        QString strStartTime = startDate.toString("yyyy-MM-dd") + "T00:00:00";
        QString strEndTime = endDate.toString("yyyy-MM-dd") + "T23:59:59";

        strTemp = " and Time between \'" + strStartTime + "\' and \'" + strEndTime + "\'";
        strSql += strTemp;

        model->setFilter(strSql);
        model->select();

        int index = 0;
        for(int i = 0; i < model->rowCount();i++)
        {
            QSqlRecord record = model->record(i);
            QString strID = record.value("ID").toString();
            QSqlTableModel *mymodel = new QSqlTableModel;
            mymodel->setTable(g_strClinicChargeDetails);
            mymodel->setFilter("ChargeId = \'" + strID + "\'");
            mymodel->select();
            for(int j = 0; j < mymodel->rowCount(); j++)
            {
                m_resultsModel->setItem(index,0,new QStandardItem(strID));

                m_resultsModel->setItem(index,1,new QStandardItem(record.value("Name").toString()));
                m_resultsModel->setItem(index,2,new QStandardItem(record.value("Department").toString()));
                m_resultsModel->setItem(index,3,new QStandardItem(record.value("Doctor").toString()));
                QSqlRecord record1 = mymodel->record(j);
                m_resultsModel->setItem(index,4,new QStandardItem(record1.value("ChargeItemName").toString()));
                m_resultsModel->setItem(index,5,new QStandardItem(record1.value("ChargeItemCount").toString()));
                m_resultsModel->setItem(index,6,new QStandardItem(record1.value("ChargeItemPrice").toString()));
                m_resultsModel->setItem(index,7,new QStandardItem(record.value("Time").toString()));
                index++;
            }
        }
    }
}

void ClinicChargeStatisticForm::initTable()
{
    m_resultsModel->clear();
    m_resultsModel->setHorizontalHeaderItem(0,new QStandardItem(QObject::tr("收费单号")));
    m_resultsModel->setHorizontalHeaderItem(1,new QStandardItem(QObject::tr("姓名")));
    m_resultsModel->setHorizontalHeaderItem(2,new QStandardItem(QObject::tr("科室")));
    m_resultsModel->setHorizontalHeaderItem(3,new QStandardItem(QObject::tr("医生")));
    m_resultsModel->setHorizontalHeaderItem(4,new QStandardItem(QObject::tr("收费项名称")));
    m_resultsModel->setHorizontalHeaderItem(5,new QStandardItem(QObject::tr("数量")));
    m_resultsModel->setHorizontalHeaderItem(6,new QStandardItem(QObject::tr("单价")));
    m_resultsModel->setHorizontalHeaderItem(7,new QStandardItem(QObject::tr("收费时间")));
    m_resultsModel->setItem(0, 7, NULL);
}

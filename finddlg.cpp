#include "finddlg.h"


FindDlg::FindDlg(QWidget *parent):
    QDialog(parent)
{
    create();
}

FindDlg::~FindDlg()
{
}


void FindDlg::create()
{
    m_findButton = new QToolButton;
    m_findButton->setIcon(QIcon(g_strIconPath + "find.png"));
    connect(m_findButton, SIGNAL(clicked()), this, SLOT(find()));

    m_resultsView = new QTableView;
    m_resultsModel = new QStandardItemModel;
    m_resultsView->setModel(m_resultsModel);
    m_resultsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_resultsView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(m_resultsView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(choise()));

    m_choiseButton = new QPushButton(g_strChoiseButton);
    connect(m_choiseButton, SIGNAL(clicked()), this, SLOT(choise()));

    m_cancelButton = new QPushButton(g_strCancelButton);
    connect(m_cancelButton, SIGNAL(clicked()), this, SLOT(close()));
}


void FindDlg::initTable(QStringList strList)
{
    m_resultsModel->clear();
    for(int i = 0; i < strList.size(); i++)
    {
         m_resultsModel->setHorizontalHeaderItem(i,new QStandardItem(strList.at(i)));
    }
    if(strList.size() > 0)
        m_resultsModel->setItem(0, strList.size()-1, NULL);
}

void FindDlg::choise()
{
    QModelIndex index = m_resultsView->currentIndex();
    if(index.isValid())
    {
        QStandardItem *item = m_resultsModel->item(index.row(),0);
        m_strId = item->text();
        close();
    }
}


QString FindDlg::getID()
{
    return m_strId;
}

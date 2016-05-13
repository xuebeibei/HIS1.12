#include "chargeform.h"

ChargeForm::ChargeForm(SubForm *parent) :
    SubForm(parent)
{
    create();
    setMyLayout();
    init();
}

QVector<ChargeItem *> ChargeForm::getChargeItems()
{
    QVector<ChargeItem*> chargeItems;
    for(int row = 0; row< m_chargeRecordsModel->rowCount();row++)
    {
        ChargeItem *chargeItem = new ChargeItem;
        for(int column = 0; column < m_chargeRecordsModel->columnCount();column++)
        {
            QStandardItem *modelItem = m_chargeRecordsModel->item(row,column);

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
                    chargeItem->setReceipt(strData);
                    break;
                }
                case clinicSort:
                {
                    chargeItem->setSort(strData);
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
        chargeItem->setChargeId(m_numberEdit->text());
        chargeItems.append(chargeItem);
    }
    return chargeItems;
}

void ChargeForm::setChargeItems(QVector<ChargeItem *> chargeItems)
{
    for(int index = 0; index< chargeItems.size();index++)
    {
        ChargeItem *item = new ChargeItem(chargeItems.at(index));
        m_chargeRecordsModel->setItem(index, chargeItemNo, new QStandardItem(item->getChargeItemNo()));
        m_chargeRecordsModel->setItem(index, chargeItemName, new QStandardItem(item->getChargeItemName()));
        m_chargeRecordsModel->setItem(index, chargeItemCount, new QStandardItem(QString::number(item->getChargeItemCount())));
        m_chargeRecordsModel->setItem(index, chargeItemPrice, new QStandardItem(QString::number(item->getChargeItemPrice())));
        m_chargeRecordsModel->setItem(index, clinicReceipt, new QStandardItem(item->getReceipt()));
        m_chargeRecordsModel->setItem(index, clinicSort, new QStandardItem(item->getSort()));
    }
}

void ChargeForm::newTableFile()
{
}

bool ChargeForm::saveTableFile()
{
    return true;
}

bool ChargeForm::deleteTableFile()
{
    return true;
}

void ChargeForm::exportTableFile()
{
}

bool ChargeForm::findTableFile()
{
    return true;
}

void ChargeForm::amendTableFile()
{
}

void ChargeForm::previewTableFile()
{
}

void ChargeForm::printTableFile()
{
}

void ChargeForm::addRow()
{
    int row = m_chargeRecordsModel->rowCount();
    m_chargeRecordsModel->setItem(row, 5,NULL);
}

void ChargeForm::deleteRow()
{
    QModelIndexList selected = m_chargeRecordsView->selectionModel()->selectedIndexes();
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
        m_chargeRecordsModel->removeRow(rowToDel);
    }
}

void ChargeForm::combo()
{
    QMessageBox::information(this,"提示","选择套餐！");
}

void ChargeForm::create()
{
    addRowButton = new QToolButton;
    addRowButton->setIcon(QIcon(g_strIconPath + "addRow.png"));
    connect(addRowButton, SIGNAL(clicked()), this, SLOT(addRow()));
    deleteRowButton = new QToolButton;
    deleteRowButton->setIcon(QIcon(g_strIconPath + "deleteRow.png"));
    connect(deleteRowButton, SIGNAL(clicked()), this, SLOT(deleteRow()));
    comboButton = new QToolButton;
    comboButton->setIcon(QIcon(g_strIconPath + "combo.png"));
    connect(comboButton, SIGNAL(clicked()), this, SLOT(combo()));

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
    m_chargeRecordsView->setEditTriggers(QAbstractItemView::DoubleClicked);
    m_chargeRecordsView->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(m_chargeRecordsModel,SIGNAL(dataChanged(QModelIndex,QModelIndex)),this, SLOT(updateIncome()));
}

void ChargeForm::setMyLayout()
{
}

void ChargeForm::init()
{
    QStringList strList;
    strList.append("收费项编码");
    strList.append("收费项名称");
    strList.append("数量");
    strList.append("单价");
    strList.append("收据");
    strList.append("分类");
    initTable(strList);
}

void ChargeForm::initTable(QStringList strList)
{
    m_chargeRecordsModel->clear();
    for(int i = 0; i < strList.size(); i++)
    {
        m_chargeRecordsModel->setHorizontalHeaderItem(i,new QStandardItem(strList.at(i)));
    }
    if(strList.size() > 0)
        m_chargeRecordsModel->setItem(0, strList.size()-1, NULL);
}

void ChargeForm::updateIncome()
{
    double dIncome = 0.0;

    for(int i = 0; i < m_chargeRecordsModel->rowCount();i++)
    {
        QStandardItem *countItem = m_chargeRecordsModel->item(i,chargeItemCount);
        QStandardItem *priceItem = m_chargeRecordsModel->item(i,chargeItemPrice);

        double dPrice = (priceItem == NULL) ? 0 : priceItem->text().toDouble();
        int nCount = (countItem == NULL) ? 0 : countItem->text().toInt();

        dIncome += (dPrice * nCount);
    }
    m_allDueIncomeEdit->setText(QString::number(dIncome));
}

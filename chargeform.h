#ifndef CHARGEFORM_H
#define CHARGEFORM_H

#include <QWidget>
#include "stdafx.h"
#include "chargetable.h"
#include "subform.h"

class ChargeForm:public SubForm
{
    Q_OBJECT
public:
    explicit ChargeForm(SubForm *parent = 0);
    QVector<ChargeItem*> getChargeItems();
    void setChargeItems(QVector<ChargeItem*> chargeItems);

public slots:
    void newTableFile();
    bool saveTableFile();
    bool deleteTableFile();
    void exportTableFile();
    bool findTableFile();
    void amendTableFile();
    void previewTableFile();
    void printTableFile();
protected:
    void create();
    void setMyLayout();
    void init();
    void initTable(QStringList strList);
protected slots:
    void addRow();
    void deleteRow();
    void combo();
    void updateIncome();

protected:
    QToolButton *addRowButton;                // 增行
    QToolButton *deleteRowButton;             // 删行
    QToolButton *comboButton;                 // 选择套餐

    QLabel *m_numberLabel;                    // 收费单号
    QLabel *m_allDueIncomeLabel;              // 应收合计
    QLineEdit *m_numberEdit;                  // 收费单号
    QLineEdit *m_allDueIncomeEdit;            // 应收合计

    QTableView *m_chargeRecordsView;          // 收费明细
    QStandardItemModel *m_chargeRecordsModel; // 收费明细
};

#endif // CHARGEFORM_H

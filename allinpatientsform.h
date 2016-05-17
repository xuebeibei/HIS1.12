#ifndef ALLINPATIENTSFORM_H
#define ALLINPATIENTSFORM_H

#include <QWidget>
#include "stdafx.h"
#include "inpatient.h"

enum TreeMenuType
{
    add = 0,
    addChild = 1,
    addUp = 2,
    addDown = 3,
    deleteItem = 4,
    renameItem = 5,
    moveItem = 6,
    upMove = 7,
    downMove = 8,
    leftMove = 9,
    rightMove = 10
};
//-----------------------------------------------------------------------------------------------------------------------------------
// 住院患者树形结构展示窗口
//-----------------------------------------------------------------------------------------------------------------------------------
class AllInpatientsForm : public QWidget
{
    Q_OBJECT
public:
    explicit AllInpatientsForm(QWidget *parent = 0);
    ~AllInpatientsForm();

    static QString TreeMenuTypeToString(TreeMenuType eType);
signals:
    void UpdateInpatientID(QString strID);
protected slots:
    void setInpatientID();
protected:
    void create();
    void setMyLayout();
    void init();
    void createTreeMenu();
    void createTools();
    void setTreeMenu();
    void getAllInpatients();

protected:
    QTreeView *m_tree;                  // 树形展示控件
    QStandardItemModel *m_treeModel;
    QLabel *m_allBedNumLabel;           // 床位数
    QLabel *m_allInpatientNumLabel;     // 患者数
    QLineEdit *m_allBedNum;             // 床位数
    QLineEdit *m_allInpatientNum;       // 患者数
    QString m_InpatientID;              // 选中患者ID
    QMap<QString,QVector<Inpatient*> > map; // 树形列表数据
};

#endif // ALLINPATIENTSFORM_H

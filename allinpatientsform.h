#ifndef ALLINPATIENTSFORM_H
#define ALLINPATIENTSFORM_H

#include <QWidget>
#include "stdafx.h"

//-----------------------------------------------------------------------------------------------------------------------------------
// 住院患者树形结构展示窗口
//-----------------------------------------------------------------------------------------------------------------------------------
class AllInpatientsForm : public QWidget
{
    Q_OBJECT
public:
    explicit AllInpatientsForm(QWidget *parent = 0);
    ~AllInpatientsForm();
    
protected:
    void create();
    void setMyLayout();
    void init();

protected:
    QRadioButton *m_allBedButton;       // 显示所有床位
    QRadioButton *m_allPatientButton;   // 显示所有患者
    QToolButton *m_setButton;           // 设置，添加删除科室和床位

    QTreeView *m_tree;                  // 树形展示控件
    QLabel *m_allBedNumLabel;           // 床位数
    QLabel *m_allInpatientNumLabel;     // 患者数
    QLineEdit *m_allBedNum;             // 床位数
    QLineEdit *m_allInpatientNum;       // 患者数
};

#endif // ALLINPATIENTSFORM_H

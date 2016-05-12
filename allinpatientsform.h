#ifndef ALLINPATIENTSFORM_H
#define ALLINPATIENTSFORM_H

#include <QWidget>
#include "stdafx.h"

class AllInpatientsForm : public QWidget
{
    Q_OBJECT
public:
    explicit AllInpatientsForm(QWidget *parent = 0);
    
signals:
    
public slots:

protected:
    void create();
    void setMyLayout();
    void init();

protected:
    QRadioButton *m_allBedButton;
    QRadioButton *m_allPatientButton;
    QToolButton *m_setButton;


    QTreeView *m_tree;
    QLabel *m_allBedNumLabel;
    QLabel *m_allInpatientNumLabel;
    QLineEdit *m_allBedNum;
    QLineEdit *m_allInpatientNum;
};

#endif // ALLINPATIENTSFORM_H

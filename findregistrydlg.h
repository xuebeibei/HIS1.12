#ifndef FINDREGISTRYDLG_H
#define FINDREGISTRYDLG_H
#include "finddlg.h"
#include "stdafx.h"

class FindRegistryDlg : public FindDlg
{
public:
    explicit FindRegistryDlg(FindDlg *parent = 0);
    ~FindRegistryDlg();
protected:
    void create();
    void setMyLayout();
    void init();
    void initResults();
protected slots:
    void find();

protected:
    QLabel *m_hospitalisationNumLabel;   // 住院号
    QLineEdit *m_hospitalisationNumEdit; // 住院号
    QLabel *m_nameLabel;                 // 姓名
    QLineEdit *m_nameEdit;               // 姓名
    QLabel *m_genderLabel;               // 性别
    QComboBox *m_genderCombo;            // 性别

};

#endif // FINDREGISTRYDLG_H

#ifndef FINDDLG_H
#define FINDDLG_H
#include <QDialog>
#include "stdafx.h"

class FindDlg : public QDialog
{
    Q_OBJECT

public:
    explicit FindDlg(QWidget *parent = 0);
    ~FindDlg();
    QString getID();
protected:
    void create();
    virtual void setMyLayout() = 0;
    virtual void init() = 0;
    void initTable(QStringList strList);

protected slots:
    virtual void find() = 0;
    void choise();
protected:

    QToolButton *m_findButton;
    QTableView *m_resultsView;
    QStandardItemModel *m_resultsModel;
    QPushButton *m_choiseButton;
    QPushButton *m_cancelButton;

    QString m_strId;
};

#endif // FINDDLG_H

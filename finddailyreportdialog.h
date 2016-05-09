#ifndef FINDDAILYREPORTDIALOG_H
#define FINDDAILYREPORTDIALOG_H

#include <QDialog>
#include "stdafx.h"

class FindDailyReportDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FindDailyReportDialog(QWidget *parent = 0);
    ~FindDailyReportDialog();
    QString getID();

protected:
    void create();
    void setMyLayout();
    void init();
    void initTable();
protected slots:
    void find();
    void choise();

protected:
    QDateEdit *m_dateEdit;
    QToolButton *m_findButton;
    QTableView *m_resultsView;
    QStandardItemModel *m_resultsModel;
    QPushButton *m_choiseButton;
    QPushButton *m_cancelButton;

    QString m_strId;
};

#endif // FINDDAILYREPORTDIALOG_H

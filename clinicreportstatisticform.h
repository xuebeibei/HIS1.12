#ifndef CLINICREPORTSTATISTICFORM_H
#define CLINICREPORTSTATISTICFORM_H

#include <QWidget>
#include "stdafx.h"
#include "subform.h"

class ClinicReportStatisticForm : public SubForm
{
    Q_OBJECT
    
public:
    explicit ClinicReportStatisticForm(SubForm *parent = 0);
    ~ClinicReportStatisticForm();

    void newTableFile();
    bool saveTableFile();
    bool deleteTableFile();
    void exportTableFile();
    bool findTableFile();
    void amendTableFile();
    void previewTableFile();
    void printTableFile();

    void create();
    void setMyLayout();
    void init();
    void initTable();

protected slots:
    void updateTable();

protected:
    QLabel *m_startDateLabel;
    QDateEdit *m_startDateEdit;
    QLabel *m_endDateLabel;
    QDateEdit *m_endDateEdit;

    QTableView *m_resultsView;
    QStandardItemModel *m_resultsModel;
};

#endif // CLINICREPORTSTATISTICFORM_H

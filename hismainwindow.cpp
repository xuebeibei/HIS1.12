#include "hismainwindow.h"

HISMainWindow::HISMainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createActions();
    createMenus();
    createToolBars();
    createStatusBar();
    //showClinicCharge();
    showHospitalisationRegistry();
}

HISMainWindow::~HISMainWindow()
{

}

void HISMainWindow::showClinicCharge()
{
    initToolsAllEnable();
    subForm = new ClinicChargeForm;
    setCentralWidget(subForm);

    saveAction->setEnabled(true);
    deleteAction->setEnabled(false);
    amendAction->setEnabled(false);
    locationLabel->setText("门诊收费");
}

void HISMainWindow::showClinicDailyReport()
{
    initToolsAllEnable();
    subForm = new ClinicDailyReportFrom;
    setCentralWidget(subForm);

    saveAction->setEnabled(true);
    deleteAction->setEnabled(false);
    amendAction->setEnabled(false);
    locationLabel->setText("门诊日结");
}

void HISMainWindow::showClinicInternalPayment()
{
    initToolsAllEnable();
    subForm = new ClinicInternalPaymentForm;
    setCentralWidget(subForm);

    newAction->setEnabled(false);
    deleteAction->setEnabled(false);
    amendAction->setEnabled(false);
    findAction->setEnabled(false);
    saveAction->setEnabled(false);
    locationLabel->setText("门诊内部缴款");
}

void HISMainWindow::showChargeStatistic()
{
    initToolsAllEnable();
    subForm = new ClinicChargeStatisticForm;
    setCentralWidget(subForm);

    newAction->setEnabled(false);
    deleteAction->setEnabled(false);
    amendAction->setEnabled(false);
    findAction->setEnabled(false);
    saveAction->setEnabled(false);
    locationLabel->setText("门诊收费查询");
}

void HISMainWindow::showReportStatistic()
{
    initToolsAllEnable();
    subForm = new ClinicReportStatisticForm;
    setCentralWidget(subForm);

    newAction->setEnabled(false);
    deleteAction->setEnabled(false);
    amendAction->setEnabled(false);
    findAction->setEnabled(false);
    saveAction->setEnabled(false);
    locationLabel->setText("门诊日结查询");
}

void HISMainWindow::showPaymentStatistic()
{
    initToolsAllEnable();
    subForm = new ClinicPaymentStatisticForm;
    setCentralWidget(subForm);

    newAction->setEnabled(false);
    deleteAction->setEnabled(false);
    amendAction->setEnabled(false);
    findAction->setEnabled(false);
    saveAction->setEnabled(false);
    locationLabel->setText("门诊项目查询");
}

void HISMainWindow::showHospitalisationRegistry()
{
    initToolsAllEnable();
    subForm = new HospitalisationRegistry;
    setCentralWidget(subForm);
    locationLabel->setText("住院登记");
}

void HISMainWindow::newTableFile()
{
    subForm->newTableFile();

    saveAction->setEnabled(true);
    deleteAction->setEnabled(false);
    amendAction->setEnabled(false);
}

void HISMainWindow::saveTableFile()
{
    if(subForm->saveTableFile())
    {
        saveAction->setEnabled(false);
        deleteAction->setEnabled(true);
        amendAction->setEnabled(true);
    }
}

void HISMainWindow::deleteTableFile()
{
    subForm->deleteTableFile();
    saveAction->setEnabled(true);
    deleteAction->setEnabled(false);
    amendAction->setEnabled(false);
}

void HISMainWindow::exportTableFile()
{
    subForm->exportTableFile();
}

void HISMainWindow::findTableFile()
{
    if(subForm->findTableFile())
    {
        saveAction->setEnabled(false);
        deleteAction->setEnabled(true);
        amendAction->setEnabled(true);
    }
}

void HISMainWindow::amendTableFile()
{
    subForm->amendTableFile();

    saveAction->setEnabled(true);
    deleteAction->setEnabled(true);
    amendAction->setEnabled(false);
}

void HISMainWindow::previewTableFile()
{
    subForm->previewTableFile();
}

void HISMainWindow::printTableFile()
{
    subForm->printTableFile();
}

void HISMainWindow::createActions()
{  
    clinicChargeAction = new QAction(g_strChargeAction,this);
    connect(clinicChargeAction, SIGNAL(triggered()), this, SLOT(showClinicCharge()));

    clinicDailyReportAction = new QAction(g_strDailyReportAction,this);
    connect(clinicDailyReportAction, SIGNAL(triggered()), this, SLOT(showClinicDailyReport()));

    clinicInternalPaymentAction = new QAction(g_strInternalPaymentAction,this);
    connect(clinicInternalPaymentAction, SIGNAL(triggered()), this, SLOT(showClinicInternalPayment()));

    clinicChargeStatisticAction = new QAction(g_strClinicChargeStatisticAction,this);
    connect(clinicChargeStatisticAction, SIGNAL(triggered()), this, SLOT(showChargeStatistic()));

    clinicReportStatisticAction = new QAction(g_strClinicReportStatisticAction,this);
    connect(clinicReportStatisticAction, SIGNAL(triggered()), this, SLOT(showReportStatistic()));

    clinicPaymentStatisticAction = new QAction(g_strClinicPaymentStatisticAction,this);
    connect(clinicPaymentStatisticAction, SIGNAL(triggered()), this, SLOT(showPaymentStatistic()));

    hospitalRegistryAction = new QAction(g_strhospitalRegistryAction,this);
    connect(hospitalRegistryAction, SIGNAL(triggered()), this, SLOT(showHospitalisationRegistry()));

    hospitalPayAction = new QAction(g_strhospitalPayAction,this);
    hospitalChargeAction = new QAction(g_strChargeAction,this);
    hospitalDischargeAction = new QAction(g_strhospitalDischargeAction,this);
    hospitalDailyreportAction = new QAction(g_strDailyReportAction,this);
    hospitalInternalPaymentAction = new QAction(g_strInternalPaymentAction,this);

    newAction = new QAction(g_strNewAction,this);
    connect(newAction, SIGNAL(triggered()), this, SLOT(newTableFile()));

    saveAction = new QAction(g_strSaveAction,this);
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveTableFile()));

    deleteAction = new QAction(g_strDeleteAction,this);
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteTableFile()));

    exportAction = new QAction(g_strExportAction,this);
    connect(exportAction, SIGNAL(triggered()), this, SLOT(exportTableFile()));

    findAction = new QAction(g_strFindAction,this);
    connect(findAction, SIGNAL(triggered()), this, SLOT(findTableFile()));

    amendAction = new QAction(g_strAmendAction,this);
    connect(amendAction, SIGNAL(triggered()), this, SLOT(amendTableFile()));

    previewAction = new QAction(g_strPreviewAction,this);
    connect(previewAction, SIGNAL(triggered()), this, SLOT(previewTableFile()));

    printAction = new QAction(g_strPrintAction,this);
    connect(printAction, SIGNAL(triggered()), this, SLOT(printTableFile()));
}

void HISMainWindow::createMenus()
{
    clinicMenu = menuBar()->addMenu(g_strClinicMenu);
    clinicMenu->addAction(clinicChargeAction);
    clinicMenu->addAction(clinicDailyReportAction);
    clinicMenu->addAction(clinicInternalPaymentAction);
    clinicStatistics = new QMenu("统计查询");
    clinicMenu->addMenu(clinicStatistics);

    clinicStatistics->addAction(clinicChargeStatisticAction);
    clinicStatistics->addAction(clinicReportStatisticAction);
    clinicStatistics->addAction(clinicPaymentStatisticAction);

    hospitalisationMenu = menuBar()->addMenu(g_strhospitalMenu);
    hospitalisationMenu->addAction(hospitalRegistryAction);
}

void HISMainWindow::createToolBars()
{
    fileToolBar = addToolBar(g_strFileToolBar);
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(saveAction);
    fileToolBar->addAction(deleteAction);
    //fileToolBar->addAction(exportAction);

    editToolBar = addToolBar(g_strEditToolBar);
    editToolBar->addAction(findAction);
    editToolBar->addAction(amendAction);

    //printToolBar = addToolBar(strPrintToolBar);
    //printToolBar->addAction(previewAction);
    //printToolBar->addAction(printAction);
}

void HISMainWindow::createStatusBar()
{
     locationLabel= new QLabel;
     statusBar()->addWidget(locationLabel);
     statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));
}

void HISMainWindow::initToolsAllEnable()
{
    newAction->setEnabled(true);
    saveAction->setEnabled(true);
    deleteAction->setEnabled(true);
    exportAction->setEnabled(true);
    findAction->setEnabled(true);
    amendAction->setEnabled(true);
    previewAction->setEnabled(true);
    printAction->setEnabled(true);
}

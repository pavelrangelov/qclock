#include "alarmsdialog.h"
#include "ui_alarmsdialog.h"

#define COL_TIME    0
#define COL_SNOOZE  1
#define COL_ENABLE  2
#define COL_COUNT   3

AlarmsDialog::AlarmsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AlarmsDialog) {
    ui->setupUi(this);

    this->setWindowTitle(tr("Alarms"));

    ui->tableAlarms->setColumnCount(COL_COUNT);
    ui->tableAlarms->setHorizontalHeaderLabels(QStringList() << tr("Time") << tr("Snooze") << tr("Enable"));
}

AlarmsDialog::~AlarmsDialog() {
    delete ui;
}

#include "alarmsdialog.h"
#include "ui_alarmsdialog.h"

AlarmsDialog::AlarmsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AlarmsDialog) {
    ui->setupUi(this);
}

AlarmsDialog::~AlarmsDialog() {
    delete ui;
}

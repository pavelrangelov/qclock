#include <QTableWidget>
#include <QTimeEdit>
#include <QCheckBox>
#include <QSettings>

#include "alarmsdialog.h"
#include "ui_alarmsdialog.h"

#define COL_TIME    0
#define COL_SNOOZE  1
#define COL_ENABLE  2
#define COL_COUNT   3

//-----------------------------------------------------------------------------
AlarmsDialog::AlarmsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::AlarmsDialog) {
    ui->setupUi(this);

    this->setWindowTitle(tr("Alarms"));

    ui->tableAlarms->setColumnCount(COL_COUNT);
    ui->tableAlarms->setHorizontalHeaderLabels(QStringList() << tr("Time") << tr("Snooze") << tr("Enable"));
    ui->tableAlarms->verticalHeader()->setVisible(false);
    ui->tableAlarms->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableAlarms->setColumnWidth(COL_SNOOZE, 50);
    ui->tableAlarms->setColumnWidth(COL_ENABLE, 50);

    ui->tableAlarms->horizontalHeader()->setSectionResizeMode(COL_TIME, QHeaderView::Stretch);
    ui->tableAlarms->horizontalHeader()->setSectionResizeMode(COL_SNOOZE, QHeaderView::Fixed);
    ui->tableAlarms->horizontalHeader()->setSectionResizeMode(COL_ENABLE, QHeaderView::Fixed);
}

//-----------------------------------------------------------------------------
AlarmsDialog::~AlarmsDialog() {
    delete ui;
}

//-----------------------------------------------------------------------------
void AlarmsDialog::on_toolNew_clicked() {
    addNewRow();
}

//-----------------------------------------------------------------------------
void AlarmsDialog::on_toolDelete_clicked() {
    deleteRow();
}

//-----------------------------------------------------------------------------
void AlarmsDialog::on_buttonBox_accepted() {
    QSettings settings;

    settings.beginWriteArray("Alarms");
    for (int row=0; row<ui->tableAlarms->rowCount(); row++) {
        alarm_t alarm;
        QTimeEdit *te = reinterpret_cast<QTimeEdit*>(ui->tableAlarms->cellWidget(row, COL_TIME));
        alarm.hour = te->time().hour();
        alarm.minute = te->time().minute();
        QCheckBox *cb_snooze = reinterpret_cast<QCheckBox*>(ui->tableAlarms->cellWidget(row, COL_SNOOZE));
        alarm.snooze = cb_snooze->isChecked();
        QCheckBox *cb_enable = reinterpret_cast<QCheckBox*>(ui->tableAlarms->cellWidget(row, COL_ENABLE));
        alarm.enable = cb_enable->isChecked();

        settings.setArrayIndex(row);
        settings.setValue("hour", alarm.hour);
        settings.setValue("minute", alarm.minute);
        settings.setValue("snooze", alarm.snooze);
        settings.setValue("enable", alarm.enable);
    }
    settings.endArray();

    emit alarmsUpdated();
}

//-----------------------------------------------------------------------------
void AlarmsDialog::setAlarms(QList<alarm_t> &alarms) {
    for (int i=0; i<alarms.count(); i++) {
        addNewRow();
        QTimeEdit *te = reinterpret_cast<QTimeEdit*>(ui->tableAlarms->cellWidget(i, COL_TIME));
        QCheckBox *cb_snooze = reinterpret_cast<QCheckBox*>(ui->tableAlarms->cellWidget(i, COL_SNOOZE));
        QCheckBox *cb_enable = reinterpret_cast<QCheckBox*>(ui->tableAlarms->cellWidget(i, COL_ENABLE));
        te->setTime(QTime(alarms.at(i).hour, alarms.at(i).minute));
        cb_snooze->setChecked(alarms.at(i).snooze);
        cb_enable->setChecked(alarms.at(i).enable);
    }
}

//-----------------------------------------------------------------------------
void AlarmsDialog::addNewRow() {
    int row = ui->tableAlarms->rowCount();
    ui->tableAlarms->insertRow(row);

    ui->tableAlarms->setItem(row, COL_TIME, new QTableWidgetItem());
    ui->tableAlarms->setItem(row, COL_SNOOZE, new QTableWidgetItem());
    ui->tableAlarms->setItem(row, COL_ENABLE, new QTableWidgetItem());

    QTimeEdit *te = new QTimeEdit();
    te->setTime(QTime(8,0,0));
    ui->tableAlarms->setCellWidget(row, COL_TIME, te);

    QCheckBox *cbSnooze = new QCheckBox();
    cbSnooze->setCheckState(Qt::Unchecked);
    cbSnooze->setStyleSheet("text-align: center; margin-left: 20%; margin-right: 20%;");
    ui->tableAlarms->setCellWidget(row, COL_SNOOZE, cbSnooze);
    ui->tableAlarms->resizeColumnToContents(COL_SNOOZE);

    QCheckBox *cbEnable = new QCheckBox();
    cbEnable->setCheckState(Qt::Checked);
    cbEnable->setStyleSheet("text-align: center; margin-left: 20%; margin-right: 20%;");
    ui->tableAlarms->setCellWidget(row, COL_ENABLE, cbEnable);
    ui->tableAlarms->resizeColumnToContents(COL_ENABLE);
}

#include <QDebug>
//-----------------------------------------------------------------------------
void AlarmsDialog::deleteRow() {
    int selectedRow = -1;

    for (int i=0; i<ui->tableAlarms->rowCount(); i++) {
        if (ui->tableAlarms->item(i, COL_TIME)->isSelected() ||
            ui->tableAlarms->item(i, COL_SNOOZE)->isSelected() ||
            ui->tableAlarms->item(i, COL_ENABLE)->isSelected()) {
            selectedRow = i;
            break;
        }
    }

    if (selectedRow != -1) {
        ui->tableAlarms->removeRow(selectedRow);
    }
}

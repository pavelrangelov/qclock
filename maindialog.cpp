#include <QString>
#include <QDateTime>
#include <QResizeEvent>
#include <QDebug>
#include <QFontDialog>
#include <QSettings>

#include "maindialog.h"
#include "ui_maindialog.h"
#include "alarmsdialog.h"

#define DIVFACTOR   4.5

//-----------------------------------------------------------------------------
MainDialog::MainDialog(QWidget *parent) : QDialog(parent), ui(new Ui::MainDialog) {
    QSettings settings;

    ui->setupUi(this);

    m_counter = 0;

    m_fontName = settings.value(STORE_FONTNAME, "Ubuntu Mono").toString();
    m_fontSize = settings.value(STORE_FONTSIZE, 20).toInt();
    m_fontBold = settings.value(STORE_FONTBOLD, false).toBool();

    restoreGeometry(settings.value(STORE_GEOMETRY).toByteArray());

    QFont font(m_fontName, m_fontSize);
    font.setBold(m_fontBold);
    ui->labelTime->setFont(font);

    font.setFamily("Ubuntu");
    font.setPointSize(40);
    ui->labelDate->setFont(font);
    ui->labelDayOfWeek->setFont(font);

    QString sDate = QDateTime::currentDateTime().toString("dd.MM.yyyy");
    ui->labelDate->setText(sDate);
    QString sTime = QDateTime::currentDateTime().toString("hh:mm");
    ui->labelTime->setText(sTime);

    loadAlarms();

    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &MainDialog::slot_timeout);
    m_timer->start(500);
}

//-----------------------------------------------------------------------------
MainDialog::~MainDialog() {
    delete ui;
}

//-----------------------------------------------------------------------------
void MainDialog::closeEvent(QCloseEvent *e) {
    QSettings settings;
    settings.setValue(STORE_GEOMETRY, saveGeometry());
    e->accept();
}

//-----------------------------------------------------------------------------
void MainDialog::resizeEvent(QResizeEvent *e) {
    QFont font = ui->labelTime->font();
    font.setPointSizeF((double)e->size().width()/DIVFACTOR);
    ui->labelTime->setFont(font);
}

//-----------------------------------------------------------------------------
void MainDialog::slot_timeout() {
    QString sDate, sTime;

    if (++m_counter & 0x1) {
        QDateTime currDateTime = QDateTime::currentDateTime();
        sDate = currDateTime.toString("dd.MM.yyyy");
        ui->labelDate->setText(sDate);
        sTime = currDateTime.toString("hh:mm");
        ui->labelDayOfWeek->setText(getDayOfWeek(currDateTime.date().dayOfWeek()));
        ui->labelTime->setText(sTime);
        processAlarms(currDateTime);
    } else {
        sTime = QDateTime::currentDateTime().toString("hh mm");
        ui->labelTime->setText(sTime);
    }
}

//-----------------------------------------------------------------------------
void MainDialog::on_toolSettings_clicked() {
    QSettings settings;

    QFont font;
    font.setFamily(m_fontName);
    font.setPointSize(m_fontSize);
    font.setBold(m_fontBold);

    QFontDialog dialog(this);
    dialog.setOption(QFontDialog::MonospacedFonts, true);
    dialog.setCurrentFont(font);

    if (dialog.exec() == QDialog::Accepted) {
        QFont font = dialog.selectedFont();
        m_fontName = font.family();
        m_fontSize = font.pointSize();
        m_fontBold = font.bold();

        font.setFamily(m_fontName);
        font.setBold(m_fontBold);
        font.setPointSizeF((double)this->size().width()/DIVFACTOR);
        ui->labelTime->setFont(font);

        settings.setValue(STORE_FONTNAME, m_fontName);
        settings.setValue(STORE_FONTSIZE, m_fontSize);
        settings.setValue(STORE_FONTBOLD, m_fontBold);
    }
}

//-----------------------------------------------------------------------------
void MainDialog::on_toolAlarms_clicked() {
    AlarmsDialog dialog(this);
    dialog.setAlarms(m_Alarms);
    connect(&dialog, SIGNAL(alarmsUpdated()), this, SLOT(slot_updateAlarms()));
    dialog.exec();
}

//-----------------------------------------------------------------------------
void MainDialog::slot_updateAlarms() {
    loadAlarms();
}

//-----------------------------------------------------------------------------
QString MainDialog::getDayOfWeek(int day) {
    QString result;

    switch (day) {
        case 1: result = QString("Monday"); break;
        case 2: result = QString("Tuesday"); break;
        case 3: result = QString("Wednesday"); break;
        case 4: result = QString("Thursday"); break;
        case 5: result = QString("Friday"); break;
        case 6: result = QString("Saturday"); break;
        case 7: result = QString("Sunday"); break;
    }

    return result;
}

//-----------------------------------------------------------------------------
void MainDialog::loadAlarms() {
    QSettings settings;

    m_Alarms.clear();

    int n = settings.beginReadArray("Alarms");
    for (int i=0; i<n; i++) {
        alarm_t alarm;
        settings.setArrayIndex(i);
        alarm.hour = settings.value("hour", 0).toInt();
        alarm.minute = settings.value("minute", 0).toInt();
        alarm.snooze = settings.value("snooze", false).toBool();
        alarm.enable = settings.value("enable", false).toBool();
        alarm.fired = false;
        m_Alarms.append(alarm);
    }
    settings.endArray();
}

//-----------------------------------------------------------------------------
void MainDialog::processAlarms(QDateTime( &currDateTime)) {
    for (alarm_t alarm: m_Alarms) {
        if (currDateTime.time().hour() == alarm.hour &&
            currDateTime.time().minute() == alarm.minute &&
            currDateTime.time().second() == 0) {
            if (!alarm.fired) {
                alarm.fired = true;
                qDebug() << "*** FIRE ***";
            }
        } else {
            alarm.fired = false;
        }
    }
}

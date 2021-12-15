#include <QString>
#include <QDateTime>
#include <QResizeEvent>
#include <QDebug>
#include <QFontDialog>
#include <QSettings>

#include "maindialog.h"
#include "ui_maindialog.h"

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

    QString sDate = QDateTime::currentDateTime().toString("dd.MM.yyyy");
    ui->labelDate->setText(sDate);
    QString sTime = QDateTime::currentDateTime().toString("hh:mm");
    ui->labelTime->setText(sTime);

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
        sDate = QDateTime::currentDateTime().toString("dd.MM.yyyy");
        ui->labelDate->setText(sDate);
        sTime = QDateTime::currentDateTime().toString("hh:mm");
        ui->labelTime->setText(sTime);
    } else {
        sTime = QDateTime::currentDateTime().toString("hh mm");
        ui->labelTime->setText(sTime);
    }
}

//-----------------------------------------------------------------------------
void MainDialog::on_toolSettings_clicked() {
    QSettings settings;

    QFontDialog dialog(this);

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

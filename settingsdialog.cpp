#include <QSettings>
#include <QFontDialog>
#include <QFileDialog>

#include "settingsdialog.h"
#include "ui_settingsdialog.h"

//-----------------------------------------------------------------------------
SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog) {
    ui->setupUi(this);
    setWindowTitle(tr("Settings"));

    ui->editRing->setReadOnly(true);
}

//-----------------------------------------------------------------------------
SettingsDialog::~SettingsDialog() {
    delete ui;
}

//-----------------------------------------------------------------------------
void SettingsDialog::on_btnFont_clicked() {
    QFontDialog dialog(this);
    dialog.setOption(QFontDialog::MonospacedFonts, true);
    dialog.setCurrentFont(m_font);

    QSettings settings;

    if (dialog.exec() == QDialog::Accepted) {
        QFont font = dialog.selectedFont();
        font.setStyle(QFont::StyleNormal);  // TODO
        setCurrentFont(font);
    }
}

//-----------------------------------------------------------------------------
void SettingsDialog::on_btnRing_clicked() {
    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Audio (*.wav)"));
    dialog.setViewMode(QFileDialog::Detail);

    if (dialog.exec() == QFileDialog::Accepted) {
        QString fileName = dialog.selectedFiles().at(0);
        setCurrentRingTone(fileName);
    }
}

//-----------------------------------------------------------------------------
void SettingsDialog::setCurrentFont(QFont &font) {
    m_font = font;
    ui->labelFont->setText(QString("%1, %2").arg(m_font.family()).arg(m_font.pointSize()));
}

//-----------------------------------------------------------------------------
QFont SettingsDialog::getSelectedFont() {
    return m_font;
}

//-----------------------------------------------------------------------------
void SettingsDialog::setCurrentRingTone(QString &ringTone) {
    m_ringTone = ringTone;
    ui->editRing->setText(m_ringTone);
}

//-----------------------------------------------------------------------------
QString SettingsDialog::getRingTone() {
    return m_ringTone;
}

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QFont>
#include <QString>

namespace Ui {
    class SettingsDialog;
}

//-----------------------------------------------------------------------------
class SettingsDialog : public QDialog {
    Q_OBJECT

    public:
        explicit SettingsDialog(QWidget *parent = nullptr);
        ~SettingsDialog();

        void setCurrentFont(QFont &font);
        QFont getSelectedFont();
        void setCurrentRingTone(QString &ringTone);
        QString getRingTone();

    private:
        Ui::SettingsDialog *ui;
        QFont m_font;
        QString m_ringTone;

    public slots:
        void on_btnFont_clicked();
        void on_btnRing_clicked();
};

#endif // SETTINGSDIALOG_H

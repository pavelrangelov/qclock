#ifndef ALARMSDIALOG_H
#define ALARMSDIALOG_H

#include <QDialog>

namespace Ui {
    class AlarmsDialog;
}

class AlarmsDialog : public QDialog {
    Q_OBJECT

    public:
        explicit AlarmsDialog(QWidget *parent = nullptr);
        ~AlarmsDialog();

    private:
        Ui::AlarmsDialog *ui;
};

#endif // ALARMSDIALOG_H

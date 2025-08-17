#ifndef ALARMSDIALOG_H
#define ALARMSDIALOG_H

#include <QDialog>

namespace Ui {
    class AlarmsDialog;
}

typedef struct alarm_struct {
    int hour;
    int minute;
    bool snooze;
    bool enable;
    bool fired;
} alarm_t;

class AlarmsDialog : public QDialog {
    Q_OBJECT

    public:
        explicit AlarmsDialog(QWidget *parent = nullptr);
        ~AlarmsDialog();
        void setAlarms(QList<alarm_t> &alarms);

    private:
        Ui::AlarmsDialog *ui;

        void addNewRow();
        void deleteRow();

    public slots:
        void on_toolNew_clicked();
        void on_toolDelete_clicked();
        void on_buttonBox_accepted();

    signals:
        void alarmsUpdated();
};

#endif // ALARMSDIALOG_H

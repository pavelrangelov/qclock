#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QList>

#include "alarmsdialog.h"

#define STORE_GEOMETRY  "APP/Geometry"
#define STORE_FONTNAME  "APP/FontName"
#define STORE_FONTSIZE  "APP/FontSize"
#define STORE_FONTBOLD  "APP/FontBold"

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

//-----------------------------------------------------------------------------
class MainDialog : public QDialog {
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

private:
    Ui::MainDialog *ui;
    QTimer *m_timer;
    uint16_t m_counter;
    QString m_fontName;
    int m_fontSize;
    bool m_fontBold;
    QList<alarm_t> m_Alarms;

    QString getDayOfWeek(int day);
    void loadAlarms();

private slots:
    void slot_timeout();
    void on_toolSettings_clicked();
    void on_toolAlarms_clicked();

protected:
    virtual void closeEvent(QCloseEvent *e) override;
    virtual void resizeEvent(QResizeEvent *) override;
};
#endif // MAINDIALOG_H

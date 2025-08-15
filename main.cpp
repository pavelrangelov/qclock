#include "maindialog.h"

#include <QApplication>

#define ORG_NAME    "Nifelheim"
#define APP_NAME    "QClock"
#define APP_VERS    "1.01"

//-----------------------------------------------------------------------------
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    app.setOrganizationName(ORG_NAME);
    app.setApplicationName(APP_NAME);
    app.setApplicationVersion(APP_VERS);

    MainDialog dialog;
    dialog.setWindowFlags(Qt::Window);
    dialog.show();

    return app.exec();
}

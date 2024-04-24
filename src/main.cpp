#include <auroraapp.h>
#include <QtQuick>
#include "class1.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("eBooksReader"));

    qmlRegisterType<Class1>("ru.omp.SimpleBLE", 1, 0, "Class1");

    QScopedPointer<QQuickView> view(Aurora::Application::createView());
    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/eBooksReader.qml")));
    view->show();


    return application->exec();
}

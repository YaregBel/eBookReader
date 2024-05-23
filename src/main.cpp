#include <auroraapp.h>
#include <QtQuick>
#include "class1.h"
#include "filereader.h"

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> application(Aurora::Application::application(argc, argv));
    application->setOrganizationName(QStringLiteral("ru.auroraos"));
    application->setApplicationName(QStringLiteral("eBooksReader"));

    qmlRegisterType<Class1>("ru.omp.SimpleBLE", 1, 0, "Class1");
    qmlRegisterType<FileReader>("ru.omp.FileReader", 1, 0, "FileReader");

    QScopedPointer<QQuickView> view(Aurora::Application::createView());

    // Создаем объект вашего QML класса
    Class1 class1Object;

    // Создаем контекст приложения и устанавливаем в него объект через setProperty()
    QQmlContext *context = view->rootContext();
    context->engine()->rootContext()->setContextProperty("class1Object", &class1Object);

    view->setSource(Aurora::Application::pathTo(QStringLiteral("qml/eBooksReader.qml")));
    //view.rootContext();
    view->show();

    return application->exec();
}

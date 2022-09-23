#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QDir>

#include "fixedsizetree.h"

int main(int argc, char *argv[]) {

    qmlRegisterType<FixedSizeTreeModel>("example", 1, 0, "FixedSizeTreeModel");
    qRegisterMetaType<FixedSizeTreeModel*>("FixedSizeTreeModel");

#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    SimpleTreeNode n("test");
    n.row();

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Add import search path
    engine.addImportPath("../plugin");
    engine.load(QUrl(QLatin1String("qrc:/example/Main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}

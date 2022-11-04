#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <QDebug>
#include <QDir>

#include "editablestringstree.h"

int main(int argc, char *argv[]) {

    qmlRegisterType<tvexample::EditableStringsTreeModel>("demo", 1, 0, "EditableStringsTreeModel");
    qRegisterMetaType<tvexample::EditableStringsTreeModel*>("EditableStringsTreeModel");

#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QObject* model = new tvexample::EditableStringsTreeModel();
    treeview::QmlTreeModel* m = qobject_cast<treeview::QmlTreeModel*>(model);
    Q_ASSERT(m);

    // Add import search path
    //engine.addImportPath(".");
    engine.load(QUrl(QLatin1String("qrc:/qml/Main.qml")));
    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}

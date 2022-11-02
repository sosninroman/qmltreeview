#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtQml/QQmlExtensionPlugin>

namespace treeview
{

class TreeViewPlugin: public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tree/1.0")
public:
    void registerTypes(const char* uri) override;
};

}
#endif

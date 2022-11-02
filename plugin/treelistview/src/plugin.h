#ifndef PLUGIN_H
#define PLUGIN_H

#include <QtQml/QQmlExtensionPlugin>

namespace treeview
{

/**
 * @brief The MyPlugin class. Simple qml plugin example.
 */

class TreeViewPlugin: public QQmlExtensionPlugin {
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "tree/1.0")
public:

    /**
     * @brief registerTypes Overrided function that should register all
     * C++ classes exported by this plugin.
     * @param uri           Plugin uri.
     */
    void registerTypes(const char* uri) override;
};

}
#endif

#include "fixedsizetree.h"

FixedSizeTreeModel::FixedSizeTreeModel(QObject* parent)
    :BaseClass(parent)
{
    auto node = new NodeType("test");
    node->appendChild(new SimpleTreeNode("child test1"));
    node->appendChild(new SimpleTreeNode("child test2"));
    addTopLevelNode(node);
}

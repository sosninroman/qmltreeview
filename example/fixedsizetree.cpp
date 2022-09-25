#include "fixedsizetree.h"

FixedSizeTreeModel::FixedSizeTreeModel(QObject* parent)
    :BaseClass(parent)
{
    auto node = new NodeType("top level node 1");
    node->appendChild(new SimpleTreeNode("1 1"));
    node->appendChild(new SimpleTreeNode("1 2"));
    addTopLevelNode(node);
    auto node2 = new NodeType("top level node 2");
    auto node21 = new SimpleTreeNode("2 1");
    node21->appendChild(new SimpleTreeNode("2 1 1"));
    node2->appendChild(node21);
    node2->appendChild(new SimpleTreeNode("2 2"));
    addTopLevelNode(node2);
}

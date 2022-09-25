#include "fixedsizetree.h"

FixedSizeTreeModel::FixedSizeTreeModel(QObject* parent)
    :BaseClass(parent)
{
    auto node = new NodeType("test");
    node->appendChild(new SimpleTreeNode("child test1"));
    node->appendChild(new SimpleTreeNode("child test2"));
    node->appendChild(new SimpleTreeNode("abcde123456789abcd123456789qwerty987654321qwerty1234567689"));
    addTopLevelNode(node);
    auto node2 = new NodeType("2");
    node2->appendChild(new SimpleTreeNode("2 1"));
    node2->appendChild(new SimpleTreeNode("2 2"));
    addTopLevelNode(node2);
}

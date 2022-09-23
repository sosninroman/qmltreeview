#include "fixedsizetree.h"

FixedSizeTreeModel::FixedSizeTreeModel(QObject* parent)
    :BaseClass(parent)
{
    auto node = new NodeType("test");
    node->appendChild(new SimpleTreeNode("child test1"));
    node->appendChild(new SimpleTreeNode("child test2"));
    node->appendChild(new SimpleTreeNode("abcde123456789abcd123456789qwerty987654321qwerty1234567689"));
    addTopLevelNode(node);
}

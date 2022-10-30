#include "editablestringstree.h"

EditableStringsTreeModel::EditableStringsTreeModel(QObject* parent)
    :BaseClass(parent)
{
    auto node = new NodeType("top level node #1");
    node->appendChild(new NodeType("node #1.1"));
    node->appendChild(new NodeType("node #1.2"));
    addTopLevelNode(node);
    auto node2 = new NodeType("top level node #2");
    node2->appendChild(new NodeType("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq1"));
    auto node21 = new NodeType("node #2.1");
    node21->appendChild(new NodeType("node #2.1.1"));
    node2->appendChild(node21);
    node2->appendChild(new NodeType("node #2.2"));
    addTopLevelNode(node2);
}

void EditableStringsTreeModel::addChild(const QVariant& index, const QString& name)
{
    const auto parentIndex = index.value<QModelIndex>();
    if(!parentIndex.isValid())
    {
        return;
    }

    auto* node = static_cast<StringTreeNode*>(parentIndex.internalPointer());

    beginInsertRows(parentIndex, node->childrenCount(), node->childrenCount());
    node->appendChild(new StringTreeNode(name));
    endInsertRows();
}

bool isParent(StringTreeNode* node, StringTreeNode* parent)
{
    auto currentParent = node->parent();
    while(currentParent)
    {
        if(currentParent == parent)
        {
            return true;
        }
        currentParent = currentParent->parent();
    }
    return false;
}

void EditableStringsTreeModel::moveNode(const QVariant& parentIndexV, const QVariant& indexV)
{
    const auto index = indexV.value<QModelIndex>();
    const auto toIndex = parentIndexV.value<QModelIndex>();
    if(!toIndex.isValid() || !index.isValid() || index == toIndex)
    {
        return;
    }

    const auto node = static_cast<StringTreeNode*>(index.internalPointer());
    const auto fromNode = node->parent();

    if(!fromNode)
    {
        return;
    }

    const auto toNode = static_cast<StringTreeNode*>(toIndex.internalPointer());
    const auto insertPos = toNode->childrenCount();

    if(isParent(toNode, node) || node->parent() == toNode)
    {
        return;
    }

    beginMoveRows(QmlTreeModelInterface::index(fromNode), node->row(), node->row(), toIndex, insertPos);
    //beginResetModel();
    fromNode->detachChild(node);
    toNode->appendChild(node);
    //endResetModel();
    endMoveRows();
}

void EditableStringsTreeModel::removeNode(const QVariant& indexV)
{
    const auto index = indexV.value<QModelIndex>();
    if(!index.isValid())
    {
        return;
    }

    const auto node = static_cast<StringTreeNode*>(index.internalPointer());

    if(!node)
    {
        return;
    }

    const auto parent = node->parent();
    Q_ASSERT(parent);

    beginRemoveRows(QmlTreeModelInterface::index(parent), node->row(), node->row());
    parent->removeChild(node);
    endRemoveRows();
}

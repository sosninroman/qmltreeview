#include "editablestringstree.h"

EditableStringsTreeModel::EditableStringsTreeModel(QObject* parent)
    :BaseClass(parent)
{
    auto node = new NodeType("top level node #1");
    node->appendChild(new NodeType("node #1.1"));
    node->appendChild(new NodeType("node #1.2"));
    addTopLevelNode(node);
    auto node2 = new NodeType("top level node #2");
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

void EditableStringsTreeModel::moveNode(const QVariant& parentIndexV, const QVariant& indexV)
{
    const auto index = indexV.value<QModelIndex>();
    const auto parentDestinationIndex = parentIndexV.value<QModelIndex>();
    if(!parentDestinationIndex.isValid() || !index.isValid())
    {
        return;
    }

    const auto node = static_cast<StringTreeNode*>(index.internalPointer());
    const auto sourceParentNode = node->parent();

    if(!sourceParentNode)
    {
        return;
    }

    const auto parentDestinationNode = static_cast<StringTreeNode*>(parentDestinationIndex.internalPointer());
    const auto insertPos = parentDestinationNode->childrenCount();

    //beginMoveRows(QmlTreeModelInterface::index(sourceParentNode), node->row(), node->row(), parentDestinationIndex, insertPos);
    beginResetModel();
    sourceParentNode->detachChild(node);
    parentDestinationNode->appendChild(node);
    endResetModel();
    //endMoveRows();
}

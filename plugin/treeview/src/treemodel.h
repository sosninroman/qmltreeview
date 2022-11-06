#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <memory>
#include <QAbstractItemModel>
#include "export.h"
#include "treenode.h"

namespace treeview
{

class TreeNode;

enum TreeModelRoles
{
    ExpandedRole = Qt::UserRole,
    ExpandableRole,
    NodeLevelRole,
    NodeIdRole,
    IndexRole,

    ExtraRole
};

/*!
 * \brief Base class for tree models.
 */
class TREE_VIEW_API TreeModel : public QAbstractItemModel
{
    Q_OBJECT
    using BaseClass = QAbstractItemModel;

    class RootNode : public TreeNode
    {
    public:
        void appendChild(TreeNode *node) final {
            node->setParent(this);
            m_children.append(node);
        }
    };

public:
    explicit TreeModel(QObject* parent = nullptr);

    /*!
     * \brief Returns root index of the model
     */
    Q_INVOKABLE QModelIndex rootIndex();

    /*!
     * \brief Returns QQmlPropertyMap with model data by its index. Model data is wrapped by QVariant.
     */
    Q_INVOKABLE QVariant nodeData(const QModelIndex& index);

    /*!
     * \brief Creates index of the node by its pointer
     */
    QModelIndex index(TreeNode* node);

    /*!
     * \brief Attaches new node to the root node.
     * Root node is responsible for calling destructor of child nodes.
     */
    void addTopLevelNode(TreeNode* node);

    /*!
     * \brief Resets model without its changing.
     */
    void reset();

    // QAbstractItemModel interface
    QHash<int, QByteArray> roleNames() const override;
    int columnCount(const QModelIndex&) const override;
    bool hasChildren(const QModelIndex& parentIndex) const override;
    QModelIndex parent(const QModelIndex &index) const override;
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant &value, int role = Qt::EditRole) override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

private:
    std::unique_ptr<RootNode> m_root;
};

}

#endif

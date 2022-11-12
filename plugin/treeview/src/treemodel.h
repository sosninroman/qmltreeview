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
     * \brief Return root index of the model
     */
    Q_INVOKABLE QModelIndex rootIndex();

    /*!
     * \brief Return model data by index.
     * Model data is a QQmlPropertyMap wrapped by QVariant.
     * Values can be readed and writed there by role name.
     * There is no need to use this function directly, data of each row
     * is avaliable via modelData property in all delegates.
     */
    Q_INVOKABLE QVariant nodeData(const QModelIndex& index);

    /*!
     * \brief Create index of the node.
     */
    QModelIndex index(TreeNode* node);

    /*!
     * \brief Attache new node to the root node.
     * Root node removes top level nodes on model destruction.
     */
    void addTopLevelNode(TreeNode* node);

    /*!
     * \brief Reset model without content changing.
     */
    void reset();

    /*!
     * \brief Return pointer on the root node of the tree model.
     * Root node is invisible node, which contains all top level nodes.
     */
    TreeNode* rootNode() const {return m_root.get();}

    // QAbstractItemModel interface implementation
    QHash<int, QByteArray> roleNames() const override;
    int columnCount(const QModelIndex&) const override;
    int rowCount(const QModelIndex& parent) const override;

    bool hasChildren(const QModelIndex& parentIndex) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    QVariant data(const QModelIndex& index, int role) const override;
    bool setData(const QModelIndex& index, const QVariant &value, int role = Qt::EditRole) override;
    QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;

private:
    std::unique_ptr<RootNode> m_root;
};

}

#endif

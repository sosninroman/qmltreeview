#ifndef TREENODE_H
#define TREENODE_H

#include <QVector>
#include "export.h"

namespace treeview
{

/*!
 * \brief The base class of a tree node.
 *
 */
class TREE_VIEW_API TreeNode
{
public:
    explicit TreeNode(TreeNode* parent = nullptr);
    virtual ~TreeNode();

    /*!
     * \brief Return the number of the row referred to the parent node.
     */
    int row() const;

    /*!
     * \brief Return the depth of the node in the hierarchy.
     */
    int level() const {return m_level;}

    /*!
     * \brief Set the depth of the node in the hierarchy.
     */
    void setLevel(int val);

    /*!
     * \brief Return parent node.
     */
    TreeNode* parent() {return m_parent;}

    /*!
     * \brief Set parent node.
     */
    void setParent(TreeNode* val) {m_parent = val;}

    /*!
     * \brief Return number of children of the node.
     */
    int childrenCount() const {return m_children.size();}

    /*!
     * \brief Add child node.
     */
    virtual void appendChild(TreeNode* child);

    /*!
     * \brief Remove child node from the hierarchy and delete it.
     */
    void removeChild(TreeNode* child);

    /*!
     * \brief Remove child node from the hierarchy without deleting.
     */
    void detachChild(TreeNode* child);

    /*!
     * \brief Get child node by its position.
     */
    TreeNode* child(int row);

    /*!
     * \brief Get a list of the children.
     */
    QVector<TreeNode*> children() const;

    /*!
     * \brief Get list of the children.
     * This method clears the list of children of the current node.
     * The calling method takes ownership of the returned nodes.
     */
    QVector<TreeNode*> takeChildren();

    /*!
     * \brief Return true if the node has children.
     */
    bool hasChildren() const {return !m_children.isEmpty();}

    /*!
     * \brief Remove all children from the node.
     */
    void clearChildren();

    /*!
     * \brief Return true if the node is expanded.
     */
    bool expanded() const {return m_expanded;}

    /*!
     * \brief Set expanded attribute value.
     */
    void setExpanded(bool val) {m_expanded = val;}

protected:
    QVector<TreeNode*> m_children;
    TreeNode* m_parent = nullptr;

private:
    bool m_expanded = true;
    int m_level = 0;
};

}

#endif

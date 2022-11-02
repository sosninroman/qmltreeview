#ifndef TREENODE_H
#define TREENODE_H

#include <QVector>
#include "export.h"

namespace treeview
{

//Basic tree node
class TREE_LIST_VIEW_API TreeNode
{
public:
    explicit TreeNode(TreeNode* parent = nullptr);
    virtual ~TreeNode();

    TreeNode* parent() {return m_parent;}

    int childrenCount() const {return m_children.size();}

    virtual void appendChild(TreeNode* child);

    TreeNode* child(int row);

    QVector<TreeNode*> children() const
    {
        return m_children;
    }

    QVector<TreeNode*> takeChildren()
    {
        const auto result = m_children;
        m_children.clear();
        return result;
    }

    bool expanded() const {return m_expanded;}
    void setExpanded(bool val) {m_expanded = val;}

    int level() const {return m_level;}
    void setLevel(int val);

    int row() const;

    bool hasChildren() const {return !m_children.isEmpty();}

    void clearChildren();
    void removeChild(TreeNode* child);
    void detachChild(TreeNode* child);

    void setParent(TreeNode* val) {m_parent = val;}
protected:
    QVector<TreeNode*> m_children;
    TreeNode* m_parent = nullptr;

private:
    bool m_expanded = true;
    int m_level = 0;
};

}

#endif

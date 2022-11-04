#include "treenode.h"

namespace treeview
{

TreeNode::TreeNode(TreeNode* parent):
      m_parent(parent)
{}

TreeNode::~TreeNode()
{
    qDeleteAll(m_children);
}

void TreeNode::appendChild(TreeNode* child)
{
    child->m_parent = this;
    child->setLevel(m_level + 1);
    m_children.append(child);
}

TreeNode* TreeNode::child(int row)
{
    if( row < 0 || row >= m_children.size() )
    {
        return nullptr;
    }
    return m_children.at(row);
}

int TreeNode::row() const
{
    if(!m_parent)
    {
        return 0;
    }
    for(auto ind = 0; ind < m_parent->m_children.size(); ++ind)
    {
        if(m_parent->m_children.at(ind) == this)
        {
            return ind;
        }
    }
    return 0;
}

void TreeNode::clearChildren()
{
    qDeleteAll(m_children);
    m_children.clear();
}

void TreeNode::setLevel(int val)
{
    m_level = val;
    for(const auto child : m_children)
    {
        child->setLevel(m_level + 1);
    }
}

void TreeNode::removeChild(TreeNode* child)
{
    m_children.removeOne(child);
    delete child;
}

void TreeNode::detachChild(TreeNode* child)
{
    m_children.removeOne(child);
}

}

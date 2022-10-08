#include "treehelper.h"
#include "QDebug"
#include "treenode.h"
#include <stack>

TreeHelper* TreeHelper::m_instance = nullptr;

QObject* TreeHelper::instance(QQmlEngine *engine,  QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    if( m_instance == nullptr){m_instance = new TreeHelper;}
    return m_instance;
}

bool TreeHelper::checkNodeBetween(QVariant index, QVariant lIndex, QVariant rIndex)
{
    QModelIndex i = index.value<QModelIndex>();
    QModelIndex r = rIndex.value<QModelIndex>();
    QModelIndex l = lIndex.value<QModelIndex>();

    if(!r.isValid() || !l.isValid())
    {
        return true;
    }

    TreeNode* node = static_cast<TreeNode*>(i.internalPointer());
    TreeNode* rNode = static_cast<TreeNode*>(r.internalPointer());
    TreeNode* lNode = static_cast<TreeNode*>(l.internalPointer());

    if(!rNode || !lNode)
    {
        return true;
    }
    Q_ASSERT(node);

    //const auto level = node->level();
    const auto lLevel = lNode->level();
    const auto rLevel = rNode->level();

    const auto pos = node->row();
    const auto lPos = lNode->row();
    const auto rPos = rNode->row();

    if(lLevel == rLevel)
    {
        Q_ASSERT(lNode->row() <= rNode->row());
        return pos >= lPos && pos <= rPos;
    }
    else
    {
        bool inBranch = false;
        auto nodeUp = node;
        while(nodeUp)
        {
            if(nodeUp == lNode)
            {
                inBranch = true;
                break;
            }
            nodeUp = nodeUp->parent();
        }
        std::stack<TreeNode*> nodesToCheck;
        nodesToCheck.push(node);
        while(!nodesToCheck.empty())
        {
            const auto rNodeRow = rNode->row();

            const auto nodeToCheck = nodesToCheck.top();
            nodesToCheck.pop();

            if(nodeToCheck == rNode)
            {
                inBranch = true;
                break;
            }
            else
            {
                if(nodeToCheck->childrenCount() > rNodeRow)
                {
                    nodesToCheck.push(nodeToCheck->child(rNodeRow));
                }
            }
        }
        return inBranch;
    }
}

#include <gtest/gtest.h>
#include "src/treemodel.h"

struct ObjectsCounter
{
public:
    int trackedObjects() const {return m_objectsAlived;}

    void increment() {++m_objectsAlived;}
    void decrement() {--m_objectsAlived;}

private:
    int m_objectsAlived = 0;
};

class TrackedNode : public treeview::TreeNode
{
public:
    explicit TrackedNode(ObjectsCounter* counter):
        m_counter(counter)
    {
        m_counter->increment();
    }
    ~TrackedNode(){
        m_counter->decrement();
    }
private:
    ObjectsCounter* m_counter = nullptr;
};

TEST(TREE_MODEL_TEST, nodesRemovingTest)
{
    ObjectsCounter counter;
    {
        treeview::TreeModel model;
        model.addTopLevelNode(new TrackedNode(&counter));
        auto branch = new TrackedNode(&counter);
        model.addTopLevelNode(branch);

        const auto childrenInBranch = 1000;
        for(int i = 0; i < childrenInBranch; ++i)
        {
            auto node = new TrackedNode(&counter);
            branch->appendChild(node);
            branch = node;
        }
        ASSERT_EQ(counter.trackedObjects(), childrenInBranch + 2);
    }
    ASSERT_EQ(counter.trackedObjects(), 0);
}

class TreeModelTest : public ::testing::Test {
protected:
    void SetUp() override
    {
        m_model = new treeview::TreeModel();
        m_model->addTopLevelNode(new treeview::TreeNode());
        auto branch = new treeview::TreeNode();
        branch->appendChild(new treeview::TreeNode());
        m_model->addTopLevelNode(branch);
    }

    void TearDown() override
    {
        delete m_model;
    }

    treeview::TreeModel* model(){return m_model;}

    treeview::TreeModel* m_model;
};

TEST_F(TreeModelTest, indexTest)
{
    const auto rootIndex = model()->rootIndex();
    const auto rootNode = model()->rootNode();
    ASSERT_EQ(rootNode, static_cast<treeview::TreeNode*>(rootIndex.internalPointer()));
    ASSERT_EQ(rootIndex, model()->index(rootNode));

    const auto childNode = rootNode->child(0);
    ASSERT_EQ(model()->index(0,0,rootIndex), model()->index(childNode));

    const auto branchNode = rootNode->child(1);
    const auto branchIndex = model()->index(branchNode);
    ASSERT_EQ(branchNode->childrenCount(), 1);
    ASSERT_EQ(model()->index(0,0,branchIndex), model()->index(branchNode->child(0)));
}

TEST_F(TreeModelTest, countTest)
{
    const auto rootIndex = model()->rootIndex();
    const auto rootNode = model()->rootNode();
    ASSERT_EQ(model()->rowCount(rootIndex), rootNode->childrenCount());

    const auto childIndex = model()->index(0, 0, rootIndex);
    const auto childNode = static_cast<treeview::TreeNode*>(childIndex.internalPointer());
    ASSERT_EQ(model()->rowCount(childIndex), childNode->childrenCount());

    const auto branchIndex = model()->index(1, 0, rootIndex);
    const auto branchNode = static_cast<treeview::TreeNode*>(branchIndex.internalPointer());
    ASSERT_EQ(model()->rowCount(branchIndex), branchNode->childrenCount());
}

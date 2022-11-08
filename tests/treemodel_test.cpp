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

    // Try to get indexes for wrong rows
    ASSERT_FALSE(model()->index(2, 0, rootIndex).isValid());
    ASSERT_FALSE(model()->index(1, 0, branchIndex).isValid());

    const auto leafNode = branchNode->child(0);
    ASSERT_TRUE(leafNode);
    const auto leafNodeIndex = model()->index(leafNode);
    // Index from parent index without children
    ASSERT_FALSE(model()->index(1, 0, leafNodeIndex).isValid());

    ASSERT_FALSE(leafNode->child(1));

    // Wrong column
    ASSERT_FALSE(model()->index(0, 1, rootIndex).isValid());

    // If parent index is not specified, consider root index as parent
    ASSERT_EQ(model()->index(0, 0), model()->index(0, 0, rootIndex));
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

TEST_F(TreeModelTest, addNodesTest)
{
    const auto rootIndex = model()->rootIndex();
    const auto rootNode = model()->rootNode();
    ASSERT_EQ(model()->rowCount(rootIndex), 2);
    ASSERT_EQ(rootNode->childrenCount(), 2);

    model()->addTopLevelNode(new treeview::TreeNode());
    ASSERT_EQ(model()->rowCount(rootIndex), 3);
    ASSERT_EQ(rootNode->childrenCount(), 3);
}

TEST_F(TreeModelTest, childrenCountingTest)
{
    const auto rootIndex = model()->rootIndex();
    const auto indexOfTheNodeWithoutChildren = model()->index(0, 0, rootIndex);
    const auto indexOfTheNodeWithChildren = model()->index(1, 0, rootIndex);
    ASSERT_TRUE(model()->hasChildren(rootIndex));
    ASSERT_FALSE(model()->hasChildren(indexOfTheNodeWithoutChildren));
    ASSERT_TRUE(model()->hasChildren(indexOfTheNodeWithChildren));

    const auto rootParentIndex = model()->parent(rootIndex);
    ASSERT_FALSE(rootParentIndex.isValid());

    ASSERT_EQ(model()->parent(indexOfTheNodeWithChildren), rootIndex);
    ASSERT_EQ(model()->parent(indexOfTheNodeWithoutChildren), rootIndex);

    const auto indexofTheLeaf = model()->index(0, 0, indexOfTheNodeWithChildren);
    ASSERT_EQ(model()->parent(indexofTheLeaf), indexOfTheNodeWithChildren);
}

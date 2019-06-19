#include "list.h"
#include "stllist.h"
#include "stlmap.h"
#include "stlvector.h"
#include "splaytree.h"
#include "osrbtree.h"
#include "randomgenerator.h"
#include "gtest/gtest.h"

using std::vector;

const int Amount = 500;

void fillVectorDifferent(vector<int> &vec,const int& amount)
{
    for(int i = 0; i < amount; i++)
    {
        int a = QRandomGenerator::global()->bounded(-500,500);
        auto it = find_if(vec.begin(),vec.end(),[a](const int& elem){return a == elem;});
        if(it!=vec.end())
            i--;
        else{
            vec.push_back(a);
        }
    }
}

TEST(AlgoTest,Random_Insert_Find)
{
    RandomGenerator<int,int>*random = new RandomGenerator<int,int>;
    vector<int>keys,values;
    random->fillVector(values,Amount);
    ASSERT_EQ(values.size(),Amount);
    fillVectorDifferent(keys,Amount);
    StructureRepresentor<int,int>*stlList = new StlList<int,int>;
    StructureRepresentor<int,int>*stlMap = new StlMap<int,int>;
    StructureRepresentor<int,int>*stlVector = new StlVector<int,int>;
    StructureRepresentor<int,int>*my_list = new List<int,int>;
    StructureRepresentor<int,int>*rb = new OSTreeRB<int,int>;
    StructureRepresentor<int,int>*splay = new Splay_Tree<int,int>;
    for(int i = 0; i < Amount;i++)
    {
        stlList->insert(keys[i],values[i]);
        stlMap->insert(keys[i],values[i]);
        stlVector->insert(keys[i],values[i]);
        my_list->insert(keys[i],values[i]);
        rb->insert(keys[i],values[i]);
        splay->insert(keys[i],values[i]);
    }
    for(int i = 0; i < Amount;i++)
    {
        EXPECT_EQ(stlList->find(keys[i]),values[i]);
        EXPECT_EQ(stlMap->find(keys[i]),values[i]);
        EXPECT_EQ(stlVector->find(keys[i]),values[i]);
        EXPECT_EQ(my_list->find(keys[i]),values[i]);
        EXPECT_EQ(rb->find(keys[i]),values[i]);
        EXPECT_EQ(splay->find(keys[i]),values[i]);
    }
}

TEST(AlgoTest,Random_Insert_Find_Remove)
{
    RandomGenerator<int,int>*random = new RandomGenerator<int,int>;
    vector<int>keys,values;
    random->fillVector(values,Amount);
    ASSERT_EQ(values.size(),Amount);
    fillVectorDifferent(keys,Amount);
    StructureRepresentor<int,int>*stlList = new StlList<int,int>;
    StructureRepresentor<int,int>*stlMap = new StlMap<int,int>;
    StructureRepresentor<int,int>*stlVector = new StlVector<int,int>;
    StructureRepresentor<int,int>*my_list = new List<int,int>;
    StructureRepresentor<int,int>*rb = new OSTreeRB<int,int>;
    StructureRepresentor<int,int>*splay = new Splay_Tree<int,int>;
    for(int i = 0; i < Amount;i++)
    {
        stlList->insert(keys[i],values[i]);
        stlMap->insert(keys[i],values[i]);
        stlVector->insert(keys[i],values[i]);
        my_list->insert(keys[i],values[i]);
        rb->insert(keys[i],values[i]);
        splay->insert(keys[i],values[i]);
    }
    for(int i = 0; i < Amount/2;i++)
    {
        stlList->remove(keys[i]);
        stlMap->remove(keys[i]);
        stlVector->remove(keys[i]);
        my_list->remove(keys[i]);
        rb->remove(keys[i]);
        splay->remove(keys[i]);
    }
    for(int i = 0; i < Amount/2;i++)
    {
        EXPECT_EQ(stlList->find(keys[i]),0);
        EXPECT_EQ(stlMap->find(keys[i]),0);
        EXPECT_EQ(stlVector->find(keys[i]),0);
        EXPECT_EQ(my_list->find(keys[i]),0);
        EXPECT_EQ(rb->find(keys[i]),0);
        EXPECT_EQ(splay->find(keys[i]),0);
    }
    for(int i = Amount/2; i < Amount;i++)
    {
        EXPECT_EQ(stlList->find(keys[i]),values[i]);
        EXPECT_EQ(stlMap->find(keys[i]),values[i]);
        EXPECT_EQ(stlVector->find(keys[i]),values[i]);
        EXPECT_EQ(my_list->find(keys[i]),values[i]);
        EXPECT_EQ(rb->find(keys[i]),values[i]);
        EXPECT_EQ(splay->find(keys[i]),values[i]);
    }
}

TEST(AlgoTest,Clear_isEmpty)
{
    RandomGenerator<int,int>*random = new RandomGenerator<int,int>;
    vector<int>keys,values;
    random->fillVector(values,Amount);
    ASSERT_EQ(values.size(),Amount);
    fillVectorDifferent(keys,Amount);
    StructureRepresentor<int,int>*stlList = new StlList<int,int>;
    StructureRepresentor<int,int>*stlMap = new StlMap<int,int>;
    StructureRepresentor<int,int>*stlVector = new StlVector<int,int>;
    StructureRepresentor<int,int>*my_list = new List<int,int>;
    StructureRepresentor<int,int>*rb = new OSTreeRB<int,int>;
    StructureRepresentor<int,int>*splay = new Splay_Tree<int,int>;
    for(int i = 0; i < Amount;i++)
    {
        stlList->insert(keys[i],values[i]);
        stlMap->insert(keys[i],values[i]);
        stlVector->insert(keys[i],values[i]);
        my_list->insert(keys[i],values[i]);
        rb->insert(keys[i],values[i]);
        splay->insert(keys[i],values[i]);
    }
    for(int i = 0; i < Amount;i++)
    {
        EXPECT_EQ(stlList->find(keys[i]),values[i]);
        EXPECT_EQ(stlMap->find(keys[i]),values[i]);
        EXPECT_EQ(stlVector->find(keys[i]),values[i]);
        EXPECT_EQ(my_list->find(keys[i]),values[i]);
        EXPECT_EQ(rb->find(keys[i]),values[i]);
        EXPECT_EQ(splay->find(keys[i]),values[i]);
    }

    stlList->clear();
    stlMap->clear();
    stlVector->clear();
    my_list->clear();
    splay->clear();

    EXPECT_TRUE(stlList->isEmpty());
    EXPECT_TRUE(stlMap->isEmpty());
    EXPECT_TRUE(stlVector->isEmpty());
    EXPECT_TRUE(my_list->isEmpty());
    EXPECT_TRUE(splay->isEmpty());
}

TEST(AlgoTest,Insert_GetKeys)
{
    RandomGenerator<int,int>*random = new RandomGenerator<int,int>;
    vector<int>keys,values;
    random->fillVector(values,Amount);
    ASSERT_EQ(values.size(),Amount);
    fillVectorDifferent(keys,Amount);
    StructureRepresentor<int,int>*stlList = new StlList<int,int>;
    StructureRepresentor<int,int>*stlMap = new StlMap<int,int>;
    StructureRepresentor<int,int>*stlVector = new StlVector<int,int>;
    StructureRepresentor<int,int>*my_list = new List<int,int>;
    StructureRepresentor<int,int>*splay = new Splay_Tree<int,int>;
    for(int i = 0; i < Amount;i++)
    {
        stlList->insert(keys[i],values[i]);
        stlMap->insert(keys[i],values[i]);
        stlVector->insert(keys[i],values[i]);
        my_list->insert(keys[i],values[i]);
        splay->insert(keys[i],values[i]);
    }
    vector<pair<int,int>> stlL = stlList->getKeys();
    vector<pair<int,int>> stlV = stlVector->getKeys();
    vector<pair<int,int>> stlM = stlMap->getKeys();
    vector<pair<int,int>> L = my_list->getKeys();
    vector<pair<int,int>> SP = splay->getKeys();

    for(int i = 0; i < Amount; i++)
    {
        auto it1 = find_if(keys.begin(),keys.end(),[=](const int&elem){return stlL[i].first == elem;});
        EXPECT_NE(it1,keys.end());
        auto it2 = find_if(keys.begin(),keys.end(),[=](const int&elem){return stlV[i].first == elem;});
        EXPECT_NE(it2,keys.end());
        auto it3 = find_if(keys.begin(),keys.end(),[=](const int&elem){return stlM[i].first == elem;});
        EXPECT_NE(it3,keys.end());
        auto it4 = find_if(keys.begin(),keys.end(),[=](const int&elem){return L[i].first == elem;});
        EXPECT_NE(it4,keys.end());
        auto it6 = find_if(keys.begin(),keys.end(),[=](const int&elem){return SP[i].first == elem;});
        EXPECT_NE(it6,keys.end());
    }
}

int main(int argc,char*argv[])
{
    ::testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}

#include "skiplist.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <ctime>
#include <vector>
#include <algorithm>
using namespace std;

void insert_test()
{
    SkipList sl;
    vector<int> test_vec;
    const int len = 4096;
    for (int i = 0; i < len; i++)
    {
        int k = rand();
        test_vec.push_back(k);
        sl.Insert(k);
    }
    sort(test_vec.begin(), test_vec.end());
    Node *p = sl.head->Next();
    for (int i = 0; i < len; i++, p = p->Next())
    {
        assert(p);
        assert(p->key == test_vec[i]);
    }
}

void delete_test()
{
    SkipList sl;
    vector<int> test_vec;
    int len = 4096;
    for (int i = 0; i < len; i++)
    {
        int k = rand();
        test_vec.push_back(k);
        sl.Insert(k);
    }
    sort(test_vec.begin(), test_vec.end());
    Node *p = sl.head->Next();

    while (len)
    {
        int idx = rand() % len;
        int e = test_vec[idx];
        test_vec.erase(test_vec.begin() + idx);
        sl.Delete(e);
        len--;
        Node *p = sl.head->Next();

        for (int i = 0; i < len; i++, p = p->Next())
        {

            assert(p->key == test_vec[i]);
        }
    }
}

void mix_test()
{
    SkipList sl;
    vector<int> test_vec;
    const int max_len = 4096;
    int len = max_len;
    for (int i = 0; i < len; i++)
    {
        int k = rand();
        test_vec.push_back(k);
        sl.Insert(k);
    }

    time_t st = time(0);
    time_t d = 10;
    time_t init = st;
    while (1)
    {
        int op = rand() % 2;
        if (op) // insert
        {
            if (len < max_len)
            {
                int e = rand();
                test_vec.push_back(e);
                sl.Insert(e);
                len++;
                sort(test_vec.begin(), test_vec.end());

                Node *p = sl.head->Next();
                for (int i = 0; i < len; i++, p = p->Next())
                {
                    assert(p->key == test_vec[i]);
                }
            }
        }
        else
        { // delete
            if (len > 0)
            {
                int idx = rand() % len;
                int e = test_vec[idx];
                test_vec.erase(test_vec.begin() + idx);
                sl.Delete(e);
                len--;
                sort(test_vec.begin(), test_vec.end());

                Node *p = sl.head->Next();
                for (int i = 0; i < len; i++, p = p->Next())
                {
                    assert(p->key == test_vec[i]);
                }
            }
        }

        if (st + d < time(0))
        {
            st = time(0);
            cout << st - init << "s mix test ok!" << endl;
            if (st - init > 20)
                break;
        }
    }
}

void long_insert_test()
{
    time_t st = time(0);
    time_t d = 10;
    time_t init = st;
    while (1)
    {
        insert_test();
        if (st + d < time(0))
        {
            st = time(0);
            cout << st - init << "s insert test ok!" << endl;
            if (st - init > 20)
                break;
        }
    }
}

void long_delete_test()
{
    time_t st = time(0);
    time_t d = 10;
    time_t init = st;
    while (1)
    {
        delete_test();
        if (st + d < time(0))
        {
            st = time(0);
            cout << st - init << "s delete test ok!" << endl;
            if (st - init > 20)
                break;
        }
    }
}

int main()
{
    long_insert_test();
    long_delete_test();
    mix_test();
    return 0;
}
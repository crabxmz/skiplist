#include "skiplist.h"
#include <cassert>
#include <iostream>
int SkipList::Insert(int key)
{
    // allocate new node
    Node *new_node = new Node();
    new_node->key = key;
    // get insert point from top to bottom
    Node *prev[this->max_h];
    for (int i = 0; i < this->max_h; i++)
        prev[i] = this->head;
    Node *insert_point = FindGreaterOrEqual(key, prev);
    // calc random height
    int node_h = GetRandH();
    // insert node
    for (int i = 0; i <= cur_h; i++)
    {
        new_node->nxt[i] = prev[i]->nxt[i];
        prev[i]->nxt[i] = new_node;
    }

    if (node_h > cur_h)
    {
        for (int i = cur_h + 1; i <= node_h; i++)
        {
            new_node->nxt[i] = 0;
            head->nxt[i] = new_node;
        }
        cur_h = node_h;
    }
    return 0;
}

Node *SkipList::Get(int k) const
{
    Node *prev[this->max_h];
    Node *res = FindGreaterOrEqual(k, prev);
    if (res->key == k)
    {
        return res;
    }
    return 0;
}

int SkipList::Delete(int key)
{
    Node *prev[this->max_h];
    for (int i = 0; i < this->max_h; i++)
        prev[i] = this->head;
    Node *delete_point = FindGreaterOrEqual(key, prev);
    if (!delete_point || delete_point->key != key)
    {
        std::cout << "Delete() err" << std::endl;
        return -1;
    }
    for (int i = 0; i < this->max_h; i++)
    {
        if (prev[i]->nxt[i] == delete_point)
            prev[i]->nxt[i] = delete_point->nxt[i];
    }
    // deallocate
    delete delete_point;

    return 0;
}
int SkipList::Update(int key)
{
    Node *p = Get(key);
    if (!p)
    {
        std::cout << "Update() err" << std::endl;
        return -1;
    }
    Delete(key);
    Insert(key);
    return 0;
}

// return nearest Node* whose key >= k
Node *SkipList::FindGreaterOrEqual(int k, Node *prev[]) const
{
    Node *cur = this->head;
    int cur_level = this->cur_h;
    while (1)
    {
         if (cur->nxt[cur_level])
        {
            if (cur->nxt[cur_level]->key < k)
            {
                cur = cur->nxt[cur_level];
            }
            else
            {
                 prev[cur_level] = cur;
                if (cur_level == 0)
                {
                    return cur->nxt[cur_level];
                }
                else
                {
                    cur_level--;
                }
            }
        }
        else
        {
             prev[cur_level] = cur;
            if (cur_level == 0)
            {
                return cur->nxt[cur_level];
            }
            else
            {
                cur_level--;
            }
        }
    }

    return 0;
}

Node *SkipList::GetLast()
{
    Node *cur = this->head;
    int cur_level = this->cur_h;
    assert(cur_level >= 0);
    while (1)
    {
        if (this->head->nxt[cur_level])
        {
            cur = this->head->nxt[cur_level];
        }
        else
        {
            if (!cur_level)
            {
                return cur;
            }
            else
            {
                cur_level--;
            }
        }
    }
    return 0;
}

// [0, max_h-1]
int SkipList::GetRandH()
{
    int n = 4;
    int res = 0;
    while (res < this->max_h - 1)
    {
        if (!rnd.getOneInN(n))
            res++;
        else
            break;
    }
    return res;
}

void SkipList::Print()
{
    std::cout << "----------\n";
    Node *p = this->head->Next();
    while (p)
    {
        int h = 0;
        while (h < max_h && p->nxt[h])
        {
            h++;
        }
        std::cout << " key=" << p->key << " ,height=" << h << ',';
        p = p->Next();
    }
    std::cout << '\n';
}
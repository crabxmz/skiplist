#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cstring>

#define MAX_H 12
class RandInt
{
public:
    RandInt()
    {
        srand(time(NULL));
    }
    int getOneInN(int N)
    {
        return rand() % N;
    }
};

class Node
{
public:
    Node *nxt[MAX_H];
    int key;
    Node()
    {
        memset(nxt, 0, sizeof(nxt));
    }
    Node *Next()
    {
        return nxt[0];
    }
};

class SkipList
{
public:
    int Insert(int key);
    Node *Get(int key) const;
    int Delete(int key);
    int Update(int key);

    Node *head; // placeholder
    int max_h;
    int cur_h;
    SkipList()
    {
        head = 0;
        max_h = MAX_H;
        cur_h = 0;
        _hd.key = 0xbeef;
        head = &_hd;
    }
    ~SkipList()
    {
        Node *p = head->Next();
        while (p)
        {
            Node *d = p;
            p = p->Next();
            delete d;
        }
    }
    void Print();

private:
    RandInt rnd;
    Node _hd;
    Node *FindGreaterOrEqual(int k, Node *prev[]) const;
    Node *GetLast();
    int GetRandH();
};
#undef MAX_H

/*
template <typename Key, class Comparator>
class SkipList {
private:
struct Node;

public:
// Create a new SkipList object that will use "cmp" for comparing keys,
// and will allocate memory using "*arena".  Objects allocated in the arena
// must remain allocated for the lifetime of the skiplist object.
explicit SkipList(Comparator cmp, Arena* arena);

SkipList(const SkipList&) = delete;
SkipList& operator=(const SkipList&) = delete;

// Insert key into the list.
// REQUIRES: nothing that compares equal to key is currently in the list.
void Insert(const Key& key);

// Returns true iff an entry that compares equal to key is in the list.
bool Contains(const Key& key) const;

// Iteration over the contents of a skip list
class Iterator {
public:
// Initialize an iterator over the specified list.
// The returned iterator is not valid.
explicit Iterator(const SkipList* list);

// Returns true iff the iterator is positioned at a valid node.
bool Valid() const;

// Returns the key at the current position.
// REQUIRES: Valid()
const Key& key() const;

// Advances to the next position.
// REQUIRES: Valid()
void Next();

// Advances to the previous position.
// REQUIRES: Valid()
void Prev();

// Advance to the first entry with a key >= target
void Seek(const Key& target);

// Position at the first entry in list.
// Final state of iterator is Valid() iff list is not empty.
void SeekToFirst();

// Position at the last entry in list.
// Final state of iterator is Valid() iff list is not empty.
void SeekToLast();

private:
const SkipList* list_;
Node* node_;
// Intentionally copyable
};

private:
enum { kMaxHeight = 12 };

inline int GetMaxHeight() const {
return max_height_.load(std::memory_order_relaxed);
}

Node* NewNode(const Key& key, int height);
int RandomHeight();
bool Equal(const Key& a, const Key& b) const { return (compare_(a, b) == 0); }

// Return true if key is greater than the data stored in "n"
bool KeyIsAfterNode(const Key& key, Node* n) const;

// Return the earliest node that comes at or after key.
// Return nullptr if there is no such node.
//
// If prev is non-null, fills prev[level] with pointer to previous
// node at "level" for every level in [0..max_height_-1].
Node* FindGreaterOrEqual(const Key& key, Node** prev) const;

// Return the latest node with a key < key.
// Return head_ if there is no such node.
Node* FindLessThan(const Key& key) const;

// Return the last node in the list.
// Return head_ if list is empty.
Node* FindLast() const;

// Immutable after construction
Comparator const compare_;
Arena* const arena_;  // Arena used for allocations of nodes

Node* const head_;

// Modified only by Insert().  Read racily by readers, but stale
// values are ok.
std::atomic<int> max_height_;  // Height of the entire list

// Read/written only by Insert().
Random rnd_;
};

*/

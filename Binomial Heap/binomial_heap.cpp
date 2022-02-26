#include <bits/stdc++.h>
using namespace std;
#define M INT_MAX

class PatientNode
{
public:
    int key;
    int degree;
    PatientNode *parent;
    PatientNode *sibling;
    PatientNode *child;

    PatientNode(int key);
};

PatientNode::PatientNode(int key)
{
    this->key = key;
    this->degree = 0;
    this->parent = nullptr;
    this->sibling = nullptr;
    this->child = nullptr;
}

class MaxBinomialHeap
{
public:
    PatientNode *head;
    int size;
    PatientNode *max;
    int highest_value;
    MaxBinomialHeap(int highest_value);
    bool isEmpty();

    PatientNode *FindMax();
    PatientNode *ExtractMax();
    void Insert(PatientNode *p);
    bool IncreaseKey(PatientNode *p, int new_value);
    void Print();

    MaxBinomialHeap *Union(MaxBinomialHeap *other);
    MaxBinomialHeap *Merge(MaxBinomialHeap *h1, MaxBinomialHeap *h2);
    void Link(PatientNode *n1, PatientNode *n2);
    void FixMaxProperty();
    PatientNode *DeleteMaxRoot();
    PatientNode *ReverseChildren(PatientNode *head);
    void PrintTree(PatientNode *p, int level);
    void PrintChild(PatientNode *p, int level);
};

// =============================================== //
MaxBinomialHeap::MaxBinomialHeap(int highest_value)
{
    this->head = nullptr;
    this->highest_value = highest_value;
    this->max = nullptr;
    this->size = 0;
}

bool MaxBinomialHeap::isEmpty()
{
    return this->size == 0;
}

void MaxBinomialHeap::FixMaxProperty()
{
    if (!this->head)
        return;
    PatientNode *current = this->head->sibling;
    PatientNode *highest = this->head;

    while (current)
    {
        if (current->key > highest->key)
            highest = current;
        current = current->sibling;
    }

    this->max = highest;
}

void MaxBinomialHeap::Insert(PatientNode *p)
{
    MaxBinomialHeap *new_heap = new MaxBinomialHeap(this->highest_value);
    new_heap->head = p;

    MaxBinomialHeap *merged_heap = this->Union(new_heap);
    this->size++;
    this->head = merged_heap->head;

    this->FixMaxProperty();
    cout << "Inserted " << p->key << endl;
}

MaxBinomialHeap *MaxBinomialHeap::Union(MaxBinomialHeap *other)
{
    // cout << other->head->sibling->key << endl;
    // other->head->sibling ==  nullptr?cout << "NULL" : cout << "No";
    MaxBinomialHeap *merged_heap = this->Merge(this, other);
    if (merged_heap->head == nullptr)
        return merged_heap;

    // start linking roots with same degree to form a new one

    PatientNode *previous = nullptr;
    PatientNode *current = merged_heap->head;
    PatientNode *next = current->sibling;

    while (next != nullptr)
    {
        // move forward when either current two nodes are not equal (move)
        // or current three nodes are equal (move and merge the later two)
        if ((current->degree != next->degree) || (next->sibling != nullptr && next->sibling->degree == next->degree))
        {
            previous = current;
            current = next;
        }
        else
        {
            // must find the node with smaller key before linking, to maintain heap property
            if (current->key >= next->key)
            {
                // linking and moving forward
                current->sibling = next->sibling;
                this->Link(current, next);
            }
            else
            {
                // the very first link with the second one being root, leaves the parent empty
                // if not, simply make it the sibling of the previous non null node
                if (previous == nullptr)
                {
                    merged_heap->head = next;
                }
                else
                {
                    previous->sibling = next;
                }

                // linking and moving forward
                this->Link(next, current);
                current = next;
            }
        }
        next = current->sibling;
    }
    return merged_heap;
}

MaxBinomialHeap *MaxBinomialHeap::Merge(MaxBinomialHeap *h1, MaxBinomialHeap *h2)
{
    // if merged with null
    if (!h1->head)
        return h2;
    if (!h2->head)
        return h1;

    // cout << "Inside Merge" << endl;
    PatientNode *start = nullptr;

    PatientNode *a = h1->head;
    // cout << a->key << endl;
    PatientNode *b = h2->head;
    

    // taking the minimum degree head as the starting point of a new heap
    if (a->degree < b->degree)
    {
        start = a;
        a = a->sibling;
        // cout << a->key << endl;
    }
    else
    {
        start = b;
        b = b->sibling;
        // cout << "Eikhane" << endl;
    }

    PatientNode *current = start;
    // cout << start->sibling->key << endl;

    // traverse until the root nodes of any one heap reaches the end
    while (a != nullptr && b != nullptr)
    {
        if (a->degree < b->degree)
        {
            current->sibling = a;
            a = a->sibling;
        }
        else
        {
            current->sibling = b;
            b = b->sibling;
        }
    }

    // merging simply the one that remains
    if (a != nullptr)
    {
        current->sibling = a;
    }

    if (b != nullptr)
    {
        current->sibling = b;
    }

    // creating new merged heap with roots ascendingly sorted by degree
    MaxBinomialHeap *merged_heap = new MaxBinomialHeap(this->highest_value);
    merged_heap->head = start;
    merged_heap->size = h1->size + h2->size;

    return merged_heap;
}

bool MaxBinomialHeap::IncreaseKey(PatientNode *p, int new_value)
{
    PatientNode *current = this->head;
    // cout << current->key << endl;
    PatientNode *found, *parent;
    while (current)
    {
        if (current->key > p->key && current->child)
        {
            // cout << "Niche Namlam" << endl;
            current = current->child;
            // cout << current->key << endl;
        }
        else if (current->key < p->key || current->child == nullptr)
        {
            if (current->key == p->key)
            {
                // cout << "Found!" << endl;
                found = current;
                current->key = new_value;

                current = found;
                parent = current->parent;

                while (parent && current->key > parent->key)
                {
                    int temp = parent->key;
                    parent->key = current->key;
                    current->key = temp;

                    current = parent;
                    parent = current->parent;
                }
                break;
            }
            while (!current->sibling)
            {
                // cout << "Sibling Khuji" << endl;
                current = current->parent;
                if (!current)
                {
                    cout << "Error From Increase Key" << endl;
                    return false;
                }
            }
            current = current->sibling;
            // cout << current->key << endl;
        }
    }

    cout << "Increased " << p->key << ". The updated value is " << current->key << endl;
    return true;
}


// =============================================== //

PatientNode *MaxBinomialHeap::FindMax()
{
    if (!this->head)
        return nullptr;

    cout << "Find Max Returned " << this->max->key << endl;
    return this->max;
}

PatientNode *MaxBinomialHeap::DeleteMaxRoot()
{
    if (!this->head)
        return nullptr;
    PatientNode *current = this->head;
    PatientNode *previous = current;
    PatientNode *maximum = current;
    PatientNode *prev_max = nullptr;

    current = current->sibling;

    // finding the max root node
    while (current)
    {
        if (current->key > maximum->key)
        {
            maximum = current;
            prev_max = previous;
        }
        previous = current;
        current = current->sibling;
    }

    if (previous == nullptr || prev_max == nullptr)
    {
        this->head = this->head->sibling;
    }
    else
    {
        prev_max->sibling = maximum->sibling;
    }

    return maximum;
}

PatientNode *MaxBinomialHeap::ReverseChildren(PatientNode *head)
{
    PatientNode *current = head;
    // cout << current->key << endl;
    PatientNode *previous = nullptr;
    PatientNode *next = nullptr;

    while (current)
    {
        next = current->sibling;
        current->sibling = previous;
        previous = current;
        current = next;

    }
    return previous;
}

PatientNode *MaxBinomialHeap::ExtractMax()
{
    PatientNode *max_node = this->DeleteMaxRoot();
    // cout << max_node->key << endl;
    this->size--;

    if (!max_node)
        return max_node;
    if (max_node->child)
    {
        MaxBinomialHeap *reveresedChildren = new MaxBinomialHeap(this->highest_value);
        reveresedChildren->head = this->ReverseChildren(max_node->child);

        // cout << reveresedChildren->head->sibling->key << endl;
        // cout << this->head->child->key << endl;
        MaxBinomialHeap *new_heap = this->Union(reveresedChildren);
        // cout << new_heap->head->sibling->key << endl;
        this->head = new_heap->head;
        // cout << "Here" << endl;
        // this->Print();
    }

    this->FixMaxProperty();
    cout << "Extract Max Returned " << max_node->key << endl;
    return max_node;
}


void MaxBinomialHeap::Print()
{
    cout << "Printing Binomial Heap... " << endl;
    cout << "--------------------------" << endl;
    int count = 1;
    PatientNode *node = this->head;
    for (PatientNode *i = node; i != nullptr; i = i->sibling)
    {
        cout << "Binomial Tree, B" << count << endl;
        PrintTree(node, 0);
        node = node->sibling;
        count++;
    }
    cout << "--------------------------" << endl;
    return;
}

void MaxBinomialHeap::PrintTree(PatientNode *p, int level)
{
    cout << "Level " << level << ": ";
    cout << p->key << endl;
    if (p->child)
    {
        PrintChild(p->child, level + 1);
    }
    else
    {
        return;
    }
}

void MaxBinomialHeap::PrintChild(PatientNode *p, int level)
{
    cout << "Level " << level << ": ";

    for (PatientNode *i = p; i != nullptr; i = i->sibling)
    {
        cout << i->key << " ";
    }
    cout << endl;
    if (p->child)
    {
        PrintChild(p->child, level + 1);
    }
    else
    {
        return;
    }
}

void MaxBinomialHeap::Link(PatientNode *n1, PatientNode *n2)
{
    n2->parent = n1;
    n2->sibling = n1->child;
    n1->child = n2;
    n1->degree++;
}

int main()
{
    MaxBinomialHeap Eye_Bank(M);
    string s;
    int n, m;
    fstream file;
    file.open("input.txt");
    while (true)
    {
        file >> s;
        if (s == "INS")
        {
            file >> n;
            Eye_Bank.Insert(new PatientNode(n));
        }
        else if (s == "EXT")
        {
            Eye_Bank.ExtractMax();
        }
        else if (s == "FIN")
        {
            Eye_Bank.FindMax();
        }
        else if (s == "INC")
        {
            file >> n >> m;
            Eye_Bank.IncreaseKey(new PatientNode(n), m);
        }
        else if (s == "PRI")
        {
            Eye_Bank.Print();
        }
        else if (s == "END")
            break;
    }
    file.close();
    return 0;
}

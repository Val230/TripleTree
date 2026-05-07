// TripleTree.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <random>
#include <chrono>

//using namespace std;
//using namespace std::chrono;

struct tree {
    int key;
    tree* left, * middle, * right;
}*root = NULL;

void add(int n, tree *&r)
{
    if (r == NULL)
    {
        r = new tree;
        r->key = n;
        r->left = r->middle = r->right = NULL;
    }
    else
    {
        std::random_device randAdd;
        int place = (randAdd() * 1.0 / randAdd.max() * 3) + 1; // (randAdd() % 3) + 1
        if (place == 1)
        {
            add(n, r->left);
        }
        else if (place == 2)
        {
            add(n, r->middle);
        }
        else 
        {
            add(n, r->right);
        }
    }
}

void Depth(tree*& r, std::vector<int> &dpth)
{
    static int count = 0;
    if (r->left)
    {
        count++;
        Depth(r->left, dpth);
    }
    dpth.push_back(count);
    count--;
    if (r->middle)
    {
        count++;
        Depth(r->middle, dpth);
    }
    dpth.push_back(count);
    count--;
    if (r->right)
    {
        count++;
        Depth(r->right, dpth);
    }
    dpth.push_back(count);
    count--;
}

void Sum(int mxdpth, tree *&r, int &sum) 
{
    static int depth = 0;
    if (depth < mxdpth)
    {
        if (r->left)
        {
            depth++;
            Sum(mxdpth, r->left, sum);
            depth--;
        }
        if (r->middle)
        {
            depth++;
            Sum(mxdpth, r->middle, sum);
            depth--;
        }
        if (r->right)
        {
            depth++;
            Sum(mxdpth, r->right, sum);
            depth--;
        }
    }
    else
    {
        if (r->key != NULL)
        {
            sum += r->key;
        }
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    std::random_device rand;
    int n;
    std::cout << "Enter array size: ";
    std::cin >> n;
    std::vector<int> vec;
    for (int i = 0; i < n; i++)
    {
        vec.push_back((rand() * 1.0 / rand.max() * 100) + 1);
        add(vec[i], root);
    }
    vec.clear();
    Depth(root, vec);
    int mxdpth = vec[0];
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec[i] > mxdpth)
        {
            mxdpth = vec[i];
        }
    }
    vec.clear();
    int sum = 0;
    for (int i = 0; i <= mxdpth; i++)
    {
        Sum(i, root, sum);
        std::cout << "\nSum of elements for level " << i << ": " << sum;
        sum = 0;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\nExecution time: " << duration.count() << "ms";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

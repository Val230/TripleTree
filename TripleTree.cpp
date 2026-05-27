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

struct ref {
    tree** key;
    int depth_pos;
};

void minDepth(tree*& r, std::vector<ref> &vech)
{
    static int count = 0;
    if (r->left)
    {
        count++;
        minDepth(r->left, *&vech);
        count--;
    }
    else
    {
        count++;
        vech.push_back({ &r->left, count });
        count--;
    }
    if (r->middle)
    {
        count++;
        minDepth(r->middle, *&vech);
        count--;
    }
    else
    {
        count++;
        vech.push_back({ &r->middle, count });
        count--;
    }
    if (r->right)
    {
        count++;
        minDepth(r->right, *&vech);
        count--;
    }
    else
    {
        count++;
        vech.push_back({ &r->right, count });
        count--;
    }
}

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
        std::vector<ref> vech;
        minDepth(r, vech);
        ref p = vech.at(0);
        for (int i = 1; i < vech.size(); i++)
        {
            if (vech.at(i).depth_pos < p.depth_pos)
            {
                p = vech.at(i);
            }
        }
        vech.clear();
        add(n, *p.key);      
    }
}

void Depth(tree*& r, std::vector<int> &dpth)
{
    static int count = 0;
    if (r->left)
    {
        count++;
        Depth(r->left, dpth);
        dpth.push_back(count);
        count--;
    } 
    if (r->middle)
    {
        count++;
        Depth(r->middle, dpth);
        dpth.push_back(count);
        count--;
    }
    if (r->right)
    {
        count++;
        Depth(r->right, dpth);
        dpth.push_back(count);
        count--;
    }
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
        sum += r->key;
    }
}

void BrowseLRMR(tree *&r)
{
    if (r != NULL)
    {
        BrowseLRMR(r->left);
        std::cout << r->key << " ";
        BrowseLRMR(r->middle);
        BrowseLRMR(r->right);
    }
}
int main()
{
    std::random_device rand;
    std::mt19937 gen(rand()); 
    std::uniform_real_distribution<> dist(1, 100);
    int n;
    std::cout << "Enter array size: ";
    std::cin >> n;
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> vec;
    for (int i = 0; i < n; i++)
    {
        vec.push_back(dist(gen)); 
        add(vec.at(i), root);
        std::cout << "Entered element " << vec.at(i) << "\n";
    }
    std::cout << "Browsing tree (Left -> Root -> Middle -> Right): ";
    BrowseLRMR(root);
    vec.clear();
    Depth(root, vec);
    int mxdpth = vec.at(0);
    for (int i = 1; i < vec.size(); i++)
    {
        if (vec.at(i) > mxdpth)
        {
            mxdpth = vec.at(i);
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

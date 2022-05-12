#pragma once

#include <iostream>
#include <stdexcept>
#include <stack>
#include <vector>
#include <list>

namespace ariel
{
    template <class T>
    class OrgChart
    {
    private:
        struct Node
        {
            T data;
            vector<Node *> childs;
            Node *next;

            Node(const T &data, Node *next = nullptr) : data(data), next(next) {}
        };
        Node *root;

        bool is_empty()
        {
            return this->root == nullptr;
        }
        Node *search_node(Node *node, T data)
        {
            if (node == nullptr)
            {
                return nullptr;
            }
            if (node->data == data)
            {
                return node;
            }
            Node *child = nullptr;
            for (int i = 0; i < node->childs.size(); i++)
            {
                child = search_node(node->childs.at(i), data);
            }
            Node *ans = nullptr;
            if (child != nullptr)
            {
                ans = child;
                return ans;
            }
            return ans;
        }
    public:
        enum order_type
        {
            PREORDER,
            POSTORDER,
            INORDER
        };
        OrgChart()
        {
            this->root = nullptr;
        }
        ~OrgChart()
        {
            if (!is_empty())
            {
                delete this->root;
            }
        }
        OrgChart<T> &add_root(const T &data)
        {
            if (this->root == nullptr)
            {
                this->root = new Node(data);
            }
            else
            {
                this->root->data = data;
            }
            return *this;
        }
        OrgChart<T> &add_sub(const T &data1, const T &data2)
        {
            if (this->root == nullptr)
            {
                throw std::invalid_argument("OrgChart as no root");
            }
            Node *node1 = this->search_node(this->root, data1);
            Node *node2 = this->search_node(this->root, data2);
            if (node1 == nullptr)
            {
                throw std::invalid_argument("can't add this nodes");
            }
            else
            {
                if (node2 == nullptr)
                {
                    node1->childs..push_back(new Node(data2));
                }
                else
                {
                    Node *check = this->search_node(node2, data1);
                    if (check == nullptr)
                    {
                        node1->childs.push_back(node2);
                    }
                    else
                    {
                        throw std::invalid_argument("can't add higher node to be sub node");
                    }
                }
            }
            return *this;
        }

    class iterator{
        
    }
    };
}
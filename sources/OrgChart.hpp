#pragma once

#include <iostream>
#include <stdexcept>
#include <stack>
#include <vector>
#include <queue>

namespace ariel
{
    template <typename T = std::string>
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
            if (data == node->data)
            {
                return node;
            }
            stack<Node *> s;
            queue<Node *> q;
            Node *curr = this->root;
            s.push(curr);
            while (!s.empty())
            {
                curr = s.top();
                s.pop();
                if (curr->childs.size() > 0)
                {
                    for (auto c : curr->childs)
                    {
                        q.push(c);
                        s.push(c);
                    }
                }
            }
            Node *a = nullptr;
            while (!q.empty())
            {
                a = q.front();
                if (data == a->data)
                {
                    return a;
                }
                q.pop();
            }

            return nullptr;
        }

    public:
        enum order_type
        {
            LevelOrder,
            PreOrder,
            ReverseOrder
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
        // OrgChart(OrgChart<T> &other) noexcept
        // {
        //     this->root = other.root;
        // }
        // OrgChart(OrgChart<T> &&other) noexcept
        // {
        //     this->root = other.root;
        //     other.root = nullptr;
        // }
        // OrgChart &operator=(OrgChart<T> &&other) noexcept
        // {
        //     this->root = other.root;
        //     other.root = nullptr;
        // }
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
                    node1->childs.push_back(new Node(data2));
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
        friend ostream &operator<<(ostream &os, const OrgChart &chart)
        {
            os << "chart" << endl;
            return os;
        }

        class iterator
        {
        private:
            Node *curr_node;
            stack<Node *> st;
            queue<Node *> que;
            order_type order;

        public:
            iterator(order_type order, Node *node) : order(order), curr_node(node)
            {
                if (this->curr_node != nullptr)
                {
                    if (this->order == order_type::LevelOrder)
                    {
                        for (auto c : this->curr_node->childs)
                        {
                            this->que.push(c);
                        }
                    }
                    else if (this->order == order_type::PreOrder)
                    {
                        for (size_t i = this->curr_node->childs.size() - 1; i >= 0; i--)
                        {
                            this->st.push(this->curr_node->childs.at(i));
                        }
                    }
                    else
                    {
                        Node *n = this->curr_node;
                        this->que.push(n);
                        while (!this->que.empty())
                        {
                            n = this->que.front();
                            this->que.pop();
                            this->st.push(n);
                            for (size_t i = this->curr_node->childs.size() - 1; i >= 0; i--)
                            {
                                this->que.push(this->curr_node->childs.at(i));
                            }
                        }
                    }
                }
            }
            iterator &operator++()
            {
                if (this->order == order_type::LevelOrder)
                {
                    if (this->que.empty())
                    {
                        this->curr_node = nullptr;
                        return *this;
                    }
                    this->curr_node = this->que.front();
                    this->que.pop();
                    for (size_t i = 0; i < this->curr_node->childs.size(); i++)
                    {
                        this->que.push(this->curr_node->childs.at(i));
                    }
                }
                else if (this->order == order_type::PreOrder)
                {
                    if (this->st.empty())
                    {
                        this->curr_node = nullptr;
                        return *this;
                    }
                    this->curr_node = this->st.top();
                    this->st.pop();
                    for (size_t i = this->curr_node->childs.size() - 1; i >= 0; i--)
                    {
                        this->st.push(this->curr_node->childs.at(i));
                    }
                }
                else
                {
                    if (this->st.empty())
                    {
                        this->curr_node = nullptr;
                        return *this;
                    }
                    this->curr_node = this->st.top();
                    this->st.pop();
                }
                return *this;
            }
            T &operator*() const
            {
                return this->curr_node->data;
            }
            T *operator->() const
            {
                return &(this->curr_node->data);
            }
            bool operator==(const iterator &other)
            {
                return this->curr_node == other.curr_node;
            }
            bool operator!=(const iterator &other)
            {
                return this->curr_node != other.curr_node;
            }
        };
        iterator begin_level_order()
        {
            return iterator(order_type::LevelOrder, this->root);
        }
        iterator end_level_order()
        {
            return iterator(order_type::LevelOrder, nullptr);
        }
        iterator begin_reverse_order()
        {
            return iterator(order_type::ReverseOrder, this->root);
        }
        iterator reverse_order()
        {
            return iterator(order_type::ReverseOrder, nullptr);
        }
        iterator begin_preorder()
        {
            return iterator(order_type::PreOrder, this->root);
        }
        iterator end_preorder()
        {
            return iterator(order_type::PreOrder, nullptr);
        }
        iterator begin()
        {
            return iterator(order_type::LevelOrder, this->root);
        }
        iterator end()
        {
            return iterator(order_type::LevelOrder, nullptr);
        }
    };
}
#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <limits>
#include "list2.h"
using namespace std;
class Graphs
{
    class Iterator
    {
        class Stack
        {
            struct Elem
            {
                ListsElem* data;
                Elem* next;
            };
            Elem* start;
        public:
            Stack()
            {
                start = nullptr;
            }
            bool contains(ListsElem* E)
            {
                Elem* Cur = start;
                while (Cur)
                {
                    if (Cur->data == E)
                        return true;
                    Cur = Cur->next;
                }
                return false;
            }
            bool is_empty()
            {
                return (!start);
            }
            void push(ListsElem* Push)
            {
                Elem* New = new Elem;
                New->data = Push;
                New->next = start;
                start = New;
            }
            ListsElem* pop()
            {
                if (!start)
                    return nullptr;
                Elem* nextHead = start->next;
                ListsElem* ans = start->data;
                delete start;
                start = nextHead;
                return ans;
            }
            int find_min_edge(ListsElem* E, ListsList* list)
            {
                int minEdge = 2147483647;
                int temp;
                ListsElem* ListsCur = E;
                ListsElem* ListsParent;
                Elem* StackCur = start;

                while (StackCur)
                {
                    ListsParent = StackCur->data;

                    temp = ListsParent->data->find_data(list->get_value(ListsCur->tag))->flow_size;
                    if (temp < minEdge)
                        minEdge = temp;

                    ListsCur = ListsParent;
                    StackCur = StackCur->next;
                }
                return minEdge;
            }
            void clear()
            {
                while (start)
                    pop();
            }
            ~Stack()
            {
                clear();
            }
        };
        Stack* Way;
        Stack* Visited;
        ListsElem* Cur;
        ListsList* list;
    public:
        Iterator(ListsElem* Start, ListsList* lists)
        {
            Cur = Start;
            list = lists;
            Way = new Stack;
            Visited = new Stack;
            Visited->push(Cur);
        }
        ListsElem* get_cur()
        {
            return Cur;
        }
        void prev(int quantity)
        {
            ListsElem* Prev = Way->pop();
            int cur_index = list->get_value(Cur->tag);
            int prev_index = list->get_value(Prev->tag);
            List2* edge = Prev->data->find_data(cur_index);
            List2* other_edge = Cur->data->find_data(prev_index);
            edge->flow_size -= quantity;
            other_edge->flow_size += quantity;

            Cur = Prev;
        }
        void next()
        {
            List2* Cur2 = Cur->data->at(0);
            int max_edge = 0;
            while (Cur2)
            {
                if (!Visited->contains(list->at(Cur2->data)))
                {
                    if (max_edge < Cur2->flow_size)
                        max_edge = Cur2->flow_size;
                }
                Cur2 = Cur2->next;
            }

            Cur2 = Cur->data->at(0);
            while (Cur2)
            {
                if (!Visited->contains(list->at(Cur2->data)) && Cur2->flow_size == max_edge)
                    break;
                Cur2 = Cur2->next;
            }

            Way->push(Cur);
            Cur = list->at(Cur2->data);
            Visited->push(Cur);
        }
        bool has_next()
        {
            List2* Cur2 = Cur->data->at(0);
            while (Cur2)
            {
                if (Cur2->flow_size > 0)
                {
                    if (!Visited->contains(list->at(Cur2->data)))
                        return true;
                }
                Cur2 = Cur2->next;
            }
            return false;
        }
        bool has_prev()
        {
            return (!Way->is_empty());
        }
        int to_start()
        {
            int quantity = Way->find_min_edge(Cur, list);
            while (has_prev())
                prev(quantity);
            Visited->clear();
            Visited->push(Cur);
            if (quantity == INT_MAX)
                return 0;
            return quantity;
        }
        ~Iterator()
        {
            delete Way;
            delete Visited;
        }
    };
    ListsList* lists;
    bool cur_edge(string tag1, string tag2, string edge)
    {
        if (edge.empty() || tag2.empty())
            return 0;
        int weight;
        try { weight = stoi(edge); }
        catch (exception) { return 0; }
        if (weight < 0)
            return 0;
        bool indicator = lists->add_edge(tag1, tag2, weight);
        if (indicator)
            indicator = lists->add_edge(tag2, tag1, 0);
        return indicator;
    }
    bool str_correct(ifstream* inp_str)
    {
        string str;
        getline(*inp_str, str);
        if (str.empty())
            return 0;
        size_t tmp1 = 0, tmp2 = 0;
        string tag1, tag2, edge;
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] == ';')
            {
                if (tmp1 == 0)
                    tmp1 = i;
                else if (tmp2 == 0)
                    tmp2 = i;
                else
                    return 0;
            }
        }
        if (tmp1 == 0 || tmp2 == 0)
            return 0;
        edge = str.substr(tmp2 + 1);
        str.erase(tmp2);
        tag2 = str.substr(tmp1 + 1);
        str.erase(tmp1);
        tag1 = str;

        if (!cur_edge(tag1, tag2, edge))
            return 0;
        return 1;
    }
    void inp_str(string filename)
    {
        ifstream inp_str;
        inp_str.open(filename);
        if (!inp_str.is_open())
            throw runtime_error("Could not open file " + filename);
        while (!inp_str.eof())
        {
            if (!str_correct(&inp_str))
            {
                inp_str.close();
                delete lists;
                throw invalid_argument("Incorrect inp_str");
            }
        }
        inp_str.close();
    }
public:
    Graphs(string filename)
    {
        lists = new ListsList;
        inp_str(filename);
        if ((!lists->find("T") || (!lists->find("S"))))
            throw invalid_argument("Graph must contain S- and T- elements");
    }
    int get_max_flow_size()
    {
        int max_flow = 0;
        ListsElem* Cur = lists->find("S");
        Iterator* iter = new Iterator(Cur, lists);

        while (iter->has_next())
        {
            Cur = iter->get_cur();
            while (Cur->tag != "T")
            {
                if (iter->has_next())
                {
                    iter->next();
                    Cur = iter->get_cur();
                }
                else
                {
                    while (!iter->has_next() && iter->has_prev())
                        iter->prev(0);
                    Cur = iter->get_cur();
                    if (Cur->tag == "S" && !iter->has_next())
                    {
                        delete iter;
                        return max_flow;
                    }
                }
            }
            max_flow += iter->to_start();
        }
        delete iter;
        return max_flow;
    }
    ~Graphs()
    {
        delete lists;
    }
};
#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <limits>
#include "list.h"
using namespace std;
class ListsElem
{
    List* data;
    string tag;
    ListsElem* next;
public:
    ListsElem(string Tag, List* Data)
    {
        next = nullptr;
        data = Data;
        tag = Tag;
    }
    friend class ListsList;
    friend class Graphs;
    ~ListsElem()
    {
        if (data)
            delete data;
    }
};
class ListsList
{
    ListsElem* start;
    size_t value;
public:
    ListsList()
    {
        start = nullptr;
        value = 0;
    }
    size_t getSize()
    {
        return value;
    }
    bool add_edge(string from, string to, int weight)
    {
        ListsElem* cur = find(from);
        if (!cur)
        {
            List* lst = new List;
            push_back(from, lst);
            cur = find(from);
        }
        int size_to = get_value(to);
        if (size_to == -1)
        {
            List* lst = new List;
            push_back(to, lst);
            size_to = get_value(to);
        }
        List2* edge = cur->data->find_data(size_to);
        if (edge)
            return 0;
        cur->data->push_back(size_to, weight);
        return 1;
    }
    void push_back(string tag, List* data)
    {
        ListsElem* Cur = start;
        if (Cur)
        {
            while (Cur->next)
                Cur = Cur->next;
            Cur->next = new ListsElem(tag, data);
        }
        else
            start = new ListsElem(tag, data);
        value++;
    }
    ListsElem* find(string tag)
    {
        ListsElem* Cur = start;
        while (Cur)
        {
            if (Cur->tag == tag)
                return Cur;
            Cur = Cur->next;
        }
        return nullptr;
    }
    ListsElem* at(size_t index)
    {
        ListsElem* Cur;
        Cur = start;
        int count = 0;
        while (count != index)
        {
            Cur = Cur->next;
            count++;
        }
        return Cur;
    }
    int get_value(string tag)
    {
        ListsElem* Cur = start;
        int index = -1;
        while (Cur)
        {
            index++;
            if (Cur->tag == tag)
                return index;
            Cur = Cur->next;
        }
        return -1;
    }
    ~ListsList()
    {
        ListsElem* Cur = start;
        ListsElem* next;
        while (Cur)
        {
            next = Cur->next;
            delete Cur;
            Cur = next;
        }
    }
};
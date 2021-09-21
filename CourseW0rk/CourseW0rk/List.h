#pragma once
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <limits>
using namespace std;
class List2
{
    int data;
    int flow_size;
    List2* next;
    List2* prev;
public:
    List2(int Data, int Key)
    {
        next = nullptr;
        prev = nullptr;
        data = Data;
        flow_size = Key;
    }
    friend class List;
    friend class ListsList;
    friend class Graphs;
    ~List2()
    {
        if (next)
            next->prev = prev;
        if (prev)
            prev->next = next;
    }
};
class List
{
    List2* start;
    List2* last;
    size_t value;
public:
    List()
    {
        start = nullptr;
        last = nullptr;
        value = 0;
    }
    bool isEmpty()
    {
        return value == 0;
    }
    size_t getSize()
    {
        return value;
    }
    void push_back(int data, int flow_size)
    {
        if (!isEmpty())
        {
            last->next = new List2(data, flow_size);
            last->next->prev = last;
            last = last->next;
        }
        else
        {
            start = new List2(data, flow_size);
            last = start;
        }
        value += 1;
    }
    void push_front(int data, int flow_size)
    {
        if (!isEmpty())
        {
            start->prev = new List2(data, flow_size);
            start->prev->next = start;
            start = start->prev;
        }
        else
        {
            start = new List2(data, flow_size);
            last = start;
        }
        value += 1;
    }
    void pop_back()
    {
        if (isEmpty())
            throw runtime_error("List is empty\n");
        List2* newLast = last->prev;
        delete last;
        last = newLast;
        if (!newLast)
            start = nullptr;
        value -= 1;
    }
    void pop_front()
    {
        if (isEmpty())
            throw runtime_error("List is empty\n");
        List2* newHead = start->next;
        delete start;
        start = newHead;
        if (!newHead)
            last = nullptr;
        value -= 1;
    }
    List2* at(size_t index)
    {
        if (index >= value)
            return nullptr;
        if (index == 0)
            return start;
        if (index == (value - 1))
            return last;
        int count;
        List2* Cur;
        if ((value / 2) > index)
        {
            Cur = start;
            count = 0;
            while (count != index)
            {
                Cur = Cur->next;
                count++;
            }
        }
        else
        {
            Cur = last;
            count = value - 1;
            while (count != index)
            {
                Cur = Cur->prev;
                count--;
            }
        }
        return Cur;
    }
    List2* find_data(int data)
    {
        List2* Cur = start;
        while (Cur)
        {
            if (Cur->data == data)
                return Cur;
            Cur = Cur->next;
        }
        return nullptr;
    }
    void insert(int data, int flow_size, size_t index)
    {
        if (index == 0)
            push_front(data, flow_size);
        else
        {
            try
            {
                List2* Next = at(index);
                List2* Prev = Next->prev;
                List2* Allow = new List2(data, flow_size);
                Prev->next = Allow;
                Allow->prev = Prev;
                Next->prev = Allow;
                Allow->next = Next;
                value += 1;
            }
            catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
        }
    }
    void remove(size_t index)
    {
        try
        {
            if (index == 0)
                pop_front();
            else if (index == (value - 1))
                pop_back();
            else
            {
                List2* Ignore = at(index);
                delete Ignore;
                value -= 1;
            }
        }
        catch (runtime_error& exception) { throw runtime_error("List is empty\n"); }
        catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
    }
    void set(int data, int flow_size, size_t index)
    {
        List2* str;
        try
        {
            str = at(index);
            str->data = data;
            str->flow_size = flow_size;
        }
        catch (out_of_range& exception) { throw out_of_range("Index is out of range\n"); }
    }
    void clear()
    {
        while (!isEmpty())
            pop_front();
    }
    ~List()
    {
        clear();
    }
};

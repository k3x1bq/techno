#ifndef MULTIMAP_MULTIMAP_HPP
#define MULTIMAP_MULTIMAP_HPP

#include <iostream>

template <class V>
class list{
public:
    list(): head(NULL){}
    ~list(){
        while (head != NULL){
            element* tmp = head->next;
            delete head;
            head = tmp;
        }
    }
    void add(V elem){
        element* tmp = new element(elem, head);
       // tmp->data = new V(elem);
        //tmp->next = head;
        head = tmp;
    }
    V* find(V elem){
        element* p = head;
        while(p != NULL){
            if (*(p->data) == elem)
                return p->data;
            else {p = p->next;}
        }
        return NULL;
    }
    void remove(V elem){
        element* p = head;
        if (p != NULL && *(p->data) == elem) {
            head = p->next;
            delete p;
        }
        while(p->next != NULL) {
            if (*(p->next->data) == elem){
                element* tmp = p->next;
                p->next = p->next->next;
                delete tmp;
            } else
                p = p->next;
        }
    }
    void show(){
        element* tmp = head;
        while (tmp != 0){
            //tmp->data->show_all();
            std::cout << *(tmp->data) << " ";
            tmp = tmp->next;
        }
        std::cout << std::endl;
    }
private:
    class element{
    public:
        element() : data(NULL), next(NULL){}
        element(V elem, element* head) : data(new V(elem)) {
            next = head;
        }
        ~element(){
            delete data;
        }
        V* data;
        element* next;
    };
    element* head;
};




template <class K,class V>
class Multimap {
public:
    Multimap(K key, V val){
        mas = new element_multimap(key, val);
    }

    ~Multimap() {
        delete mas;
    }


private:
    class element_multimap{
    public:
        element_multimap(K key, V value): key(key){
            this->val.add(value);
        }
        K key;
        list<V> val;
    };

    int cap;
    element_multimap* mas;
};

#endif //MULTIMAP_MULTIMAP_HPP

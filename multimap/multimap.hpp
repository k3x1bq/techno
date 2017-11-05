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
//    list(const list& other){
//        head = NULL;
//        element* p = other.head;
//
//        while (p != NULL){
//            this->add(*(p->data));
//            //std::cout<<"oke " << *(this->head->data) <<std::endl;
//            p = p->next;
//        }
//    }
    list(const list& other){
        head = NULL;
        element* p = other.head;
        try {
            if (p == NULL)
                throw 1;
            element *last = NULL;
            while (last != p) {
                while (p->next != last)
                    p = p->next;
                this->add(*(p->data));
                last = p;
                p = other.head;
            }
        } catch(int a){
            if (a == 1){
                head = NULL;
            }
        }
    }
//    list& operator=(const list& other){
//        while (head != NULL){
//            element* tmp = head->next;
//            delete head;
//            head = tmp;
//        }
//        element* p = other.head;
//        while (p != NULL){
//            this->add(*(p->data));
//            p = p->next;
//        }
//        return *this;
//    }
    list& operator= (const list& other){
        while (head != NULL){
            element* tmp = head->next;
            delete head;
            head = tmp;
        }
        element* p = other.head;
        if (p==NULL)
            return *this;
        element* last = NULL;
        while (last != p){
            while (p->next != last)
                p = p->next;
            this->add(*(p->data));
            last = p;
            p = other.head;
        }
        return *this;
    }
    void add(const V& elem){
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
    void remove(const V& elem){
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
    void show() const {
        element* tmp = head;
        while (tmp != 0){
            //tmp->data->show_all();
            std::cout << *(tmp->data) << " ";
            tmp = tmp->next;
        }
        std::cout << std::endl;
    }
//private:
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
    class element_multimap;
    Multimap(){}
    Multimap(K key, V val){
       // mas = new list<element_multimap>();
        mas.add(element_multimap(key, val));
    }

    ~Multimap() {
        //delete mas;
    }

    void add(const K& key,const V& value){
        if (mas.head == NULL){
            mas.add(element_multimap(key, value));
            return;
        }
        auto p = mas.head;
        while (p != NULL){
            if ((p->data->key) == key) {
                p->data->val.add(value);
                return;
            }
            p = p->next;
        }
        mas.add(element_multimap(key, value));
    }

    void remove (const K& key){
        auto p = mas.head;
        while (p != NULL){
            if (p->data->key == key){
                mas.remove(*(p->data));
            }
            p = p->next;
        }
    }
    element_multimap* find(const K& key){
        auto p = mas.head;
        try {
            while (p != NULL) {
                if (p->data->key == key) {
                    return p->data;
                }
                p = p->next;
            }
            throw 1;
        } catch(int a) {
            if (a == 1){
                std::cout << "no such key in map" << std::endl;
                return NULL;
            }

        }
       // return NULL;
    }
    void show() const {
        auto p = mas.head;
        while (p!=NULL) {
            std::cout << p->data->key << " :";
            p->data->val.show();
            p = p->next;
        }
    }
    friend std::ostream& operator << (std::ostream& os, Multimap const& obj){
        auto p = obj.mas.head;
        try {
            if (p == NULL)
                throw 1;
            while (p != NULL) {
                os << p->data->key << " :";
                p->data->val.show();
                p = p->next;
            }
            return os;
        } catch (int a){
            if (a == 1)
                return os;
        }
    }
    Multimap& operator+=(Multimap& other){
        auto p = mas.head;
        try {
            if (p == NULL)
                throw 1;
            while (p->next != NULL)
                p = p->next;
            p->next = other.mas.head;
            other.mas.head = this->mas.head;
            return *this;
        } catch (int a){
            if (a == 1){
                this->mas = other.mas;
            }
            return *this;
        }
    }
//private:
    class element_multimap{
    public:
        element_multimap(const element_multimap& other){
            this->key = other.key;
            this->val = other.val;
        }
        element_multimap(K key, V value): key(key){
            this->val.add(value);
        }
        ~element_multimap(){

        }
        friend bool operator==(const element_multimap& e1, const element_multimap& e2){
            return e1.key == e2.key;
        }
        friend std::ostream& operator << (std::ostream& os, element_multimap const& obj){
            obj.show();
            return os;
        }
        void show() const {
            try {
                if (this == NULL)
                    throw 1;
                std::cout << key << " : ";
                val.show();
            }
            catch (int a) {
                if (a == 1)
                    std::cout << "empty value list" << std::endl;
            }
        }
        K key;
        list<V> val;
    };

    list<element_multimap> mas;
};



#endif //MULTIMAP_MULTIMAP_HPP

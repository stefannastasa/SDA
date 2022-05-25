#include <cstddef>

template<typename TElem>
class list{
    private:

        struct component{
            component* next;
            component* bef;
            TElem value;
        };

    
    component* head;
    component* tail;
    int nrElems;

    public:
        class iterator_lista{
            friend class list;
            private:
                list& myList ;
                list::component* current;

            public:

                iterator_lista(list& lst):myList(lst),current(lst.head){}
                iterator_lista(const iterator_lista& a):myList(a.myList),current(a.current){}
                iterator_lista& operator=(iterator_lista a){
                    this->myList = a.myList;
                    this->current = a.current;
                    return *this;
                }
                
                bool valid() const{
                    if(myList.size() > 0)
                        return current != myList.tail && current != NULL ;
                    else
                        return false;
                }

                bool next(){
                    if(valid())
                        current = current->next;
                    
                }

                void deleteElem(){
                    if(valid()){
                        if(myList.size() == 1)
                        {
                            delete myList.tail;
                            delete myList.head;
                            myList.head = NULL;
                            myList.tail = NULL;
                            --myList.nrElems;
                            return;
                        }
                        list::component* aux = current;
                        if(current == myList.head){
                            myList.head = current->next;
                            current = current->next;

                            current->bef = NULL;
                        }else{
                            current->bef->next = current->next;
                            current->next->bef = current->bef;
                            current = current->next;
                        }
                        delete aux;
                        --myList.nrElems;
                    }
                }
                TElem operator*()const{
                    if(valid())
                        return this->current->value;
                    else{
                        TElem random;
                        return random;
                    }
                }
                
                void modif(TElem val){
                    if(valid())
                        current->value = val;
                }

        };

        list(){
            head = NULL;
            tail = NULL;
            nrElems = 0;
        }
        list(list& a){
            head = a.head;
            tail = a.tail;
            nrElems = a.nrElems;
        }
        list& operator=(list& a){
            head = a.head;
            tail = a.tail;
            nrElems = a.nrElems;
        }
        void pushBack(TElem to_add){
            if(nrElems == 0){
                head = new component;
                head->value = to_add;
                head->bef = NULL;

                tail = new component;
                head->next = tail;

                tail->next = NULL;
                tail->bef = head;
            }else{
                component* adder = new component;
                adder->value = to_add;
                adder->bef = tail->bef;
                tail->bef->next = adder;

                adder->next = tail;
                tail->bef = adder;
            }
            ++nrElems;
        }

        iterator_lista iterator(){
            return iterator_lista(*this);
        }
        int size() const{
            return this->nrElems;
        }

       ~list(){
           while(head != tail){
               component* aux = head;
               head = head->next;
               delete aux;
           }
           delete head;
       }
};
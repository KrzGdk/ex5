#ifndef AGHSLIST_H
#define AGHSLIST_H

template<class T>
class aghSlist: public aghContainer<T>{
    int length;

    template<class D>
    class element{
    public:    
        D data;
        element<D>* next;
        
        element(): next(NULL) {}
        element(element<D>* _next, D _data) :
            next(_next), data(_data) {}
    };

    element<T> *first;
public:
    aghSlist(): first(NULL), length(0) {}
    aghSlist(const aghSlist& other);
    ~aghSlist();

    aghSlist(const aghContainer<T>& other);
    /// \brief Metoda dodajaca wartosc do pojemnika
    ///
    /// \param index - indeks wstawianego elementu
    /// \param value - wstawiana wartosc
    /// \return Wartosc logiczna informujaca o powodzeniu operacji
    virtual bool insert(int index, T const& value);

    /// \brief Metoda pobierajaca wartosc z pojemnika
    ///
    /// \param index - indeks pobieranego elementu
    /// \return Pobierana wartosc
    virtual T& at(int index) const;

    /// \brief Metoda pobierajaca ilosc elementow pojemnika
    ///
    /// \return Ilosc elementow w pojemniku
    virtual int size(void) const;

    /// \brief Metoda usuwajaca wartosc z pojemnika
    ///
    /// \param index - indeks usuwanego elementu
    /// \return Wartosc logiczna informujaca o powodzeniu operacji
    virtual bool remove(int index);

    aghSlist<T>& operator=(aghSlist<T> const& other);
    
    aghSlist<T>& operator=(aghContainer<T> const& other);
};

template<class T>
aghSlist<T>::aghSlist(const aghSlist& other): first(NULL), length(0){
    element<T> *temp;
    length = other.size();

    first = new element<T>; // WYJATKI!
    first->data = other.at(0);
    temp = first;
    for(int i=1;i<length;i++){
        temp->next = new element<T>;
        temp = temp->next;
        temp->data = other.at(i);
    }
}

template<class T>
aghSlist<T>::aghSlist(const aghContainer<T>& other): first(NULL), length(0){
    element<T> *temp;
    length = other.size();

    first = new element<T>; // WYJATKI!
    first->data = other.at(0);
    temp = first;
    for(int i=1;i<length;i++){
        temp->next = new element<T>;
        temp = temp->next;
        temp->data = other.at(i);
    }
}

template<class T>
aghSlist<T>& aghSlist<T>::operator=(aghSlist<T> const& other){
    if(this == &other) return *this;
    element<T> *temp;
    if(length == other.size()){
        temp = first;
        for(int i=0;i<length;i++){
            temp->data = other.at(i);
        }
    }
    else{
        while(length > 1){
            temp = first;
            for(int i=0;i<length-1;i++) temp = temp->next;
            delete temp;
            length--;
        }
        delete first;
        length = other.size();
        
        first = new element<T>; // WYJATKI!
        first->data = other.at(0);
        temp = first;
        for(int i=1;i<length;i++){
            temp->next = new element<T>;
            temp = temp->next;
            temp->data = other.at(i);
        }
    }
    return *this;
}

template<class T>
aghSlist<T>& aghSlist<T>::operator=(aghContainer<T> const& other){
    if(this == &other) return *this;
    element<T> *temp;
    if(length == other.size()){
        temp = first;
        for(int i=0;i<length;i++){
            temp->data = other.at(i);
        }
    }
    else{
         while(length > 1){
            temp = first;
            for(int i=0;i<length-1;i++) temp = temp->next;
            delete temp;
            length--;
        }
        delete first;
        length = other.size();
        
        first = new element<T>; // WYJATKI!
        first->data = other.at(0);
        temp = first;
        for(int i=1;i<length;i++){
            temp->next = new element<T>;
            temp = temp->next;
            temp->data = other.at(i);
        }
    }
    return *this;
}


template<class T>
aghSlist<T>::~aghSlist(){
    element<T>* temp = first;
     while(length > 1){
        temp = first;
        for(int i=0;i<length-1;i++) temp = temp->next;
        delete temp;
        length--;
    }
    delete first;
    length = 0;
}

template <class T>
bool aghSlist<T>::insert(int index, T const& value){
    if(index < 0 || index > length){
        return false;
    }

    element<T> *temp;
    element<T> *new_el = new element<T>; // WYJATEK!
    new_el->data = value;

    if(index == 0){
        if(first == NULL){
            first = new_el;
            new_el->next = NULL;
        }
        else{
            temp = first;
            first = new_el;
            new_el->next = temp;
        }
    }
    else{
        temp = first;
        for(int i=0;i<index-1;i++){
            temp = temp->next;
        }

        if(temp->next == NULL){
            temp->next = new_el;
            new_el->next = NULL;
        }
        else{
            // TUUUUUUUUU!
        }
    }

    length++;

    return true;
}

template<class T>
T& aghSlist<T>::at(int index) const{
    if(index < 0 || index > length){
        throw aghException(4,"Blad zakresu", __FILE__, __LINE__);
    }
    else{
        element<T> *temp = first;
        for(int i=0;i<index;i++){
            temp = temp->next;
        }
        return temp->data;
    }
}

template<class T>
int aghSlist<T>::size(void) const{
    return length;
}

template<class T>
bool aghSlist<T>::remove(int index){
    if(index < 0 || index > length){
        return false;
    }
    else{
        element<T>* temp = first;
        if(index == 0){
            first = temp->next;
            delete temp;
            length--;
        }
        else{
            for(int i=1;i<index;i++){
                temp = temp->next;
            }
            element<T>* to_rem = temp->next;
            if(to_rem->next != NULL) temp->next = to_rem->next;
            else temp->next = NULL;
            delete to_rem;
            length--;
        }
        if(length == 0) first = NULL;
        return true;
    }
}

#endif

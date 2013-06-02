#ifndef AGHDLIST_H
#define AGHDLIST_H
 
template<class T>
class aghDlist: public aghContainer<T>{
    int length;
 
    template<class D>
    class element{
    public:    
        D data;
        element<D>* next;
        element<D>* prev;
        
        element(): next(NULL), prev(NULL) {}
        element(element<D>* _next, element<D>* _prev, D _data) :
            next(_next), prev(_prev), data(_data) {}
    };
 
    element<T> *first, *last;
public:
    aghDlist(): first(NULL), last(NULL), length(0) {}
    aghDlist(const aghDlist& other);
    ~aghDlist();
 
    aghDlist(const aghContainer<T>& other);
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
 
    aghDlist<T>& operator=(aghDlist<T> const& other);
    
    aghDlist<T>& operator=(aghContainer<T> const& other);
};
 
template<class T>
aghDlist<T>::aghDlist(const aghDlist& other): first(NULL), last(NULL), length(0){
    element<T> *temp;
    length = other.size();
 
    first = new element<T>; 
    if(first == NULL) throw aghException(2,"Blad przydzialu pamieci", __FILE__, __LINE__);
    first->data = other.at(0);
    temp = first;
    for(int i=1;i<length;i++){
        temp->next = new element<T>;
        if(temp->next == NULL) throw aghException(2,"Blad przydzialu pamieci", __FILE__, __LINE__);
        temp->next->prev = temp;
        temp = temp->next;
        temp->data = other.at(i);
    }
    last = temp;
}
 
template<class T>
aghDlist<T>::aghDlist(const aghContainer<T>& other): first(NULL), last(NULL), length(0){
    element<T> *temp;
    length = other.size();
 
    first = new element<T>;
    if(first == NULL) throw aghException(2,"Blad przydzialu pamieci", __FILE__, __LINE__);
    first->data = other.at(0);
    temp = first;
    for(int i=1;i<length;i++){
        temp->next = new element<T>;
        if(temp->next == NULL) throw aghException(2,"Blad przydzialu pamieci", __FILE__, __LINE__);
        temp->next->prev = temp;
        temp = temp->next;
        temp->data = other.at(i);
    }
    last = temp;
}
 
template<class T>
aghDlist<T>& aghDlist<T>::operator=(aghDlist<T> const& other){
    if(this == &other) return *this;
    element<T> *temp;
    if(length == other.size()){
        temp = first;
        for(int i=0;i<length;i++){
            temp->data = other.at(i);
        }
    }
    else{
        temp = last;
        for(int i=1;i<length;i++){
            temp = temp->prev;
            delete temp->next;
        }
        delete temp;
        length = other.size();
        
        first = new element<T>;
        if(first == NULL) throw aghException(2,"Blad przydzialu pamieci", __FILE__, __LINE__);
        first->data = other.at(0);
        temp = first;
        for(int i=1;i<length;i++){
            temp->next = new element<T>;
            if(temp->next == NULL) throw aghException(2,"Blad przydzialu pamieci", __FILE__, __LINE__);
            temp->next->prev = temp;
            temp = temp->next;
            temp->data = other.at(i);
        }
    }
    return *this;
}
 
template<class T>
aghDlist<T>& aghDlist<T>::operator=(aghContainer<T> const& other){
    if(this == &other) return *this;
    element<T> *temp;
    if(length == other.size()){
        temp = first;
        for(int i=0;i<length;i++){
            temp->data = other.at(i);
        }
    }
    else{
        temp = last;
        for(int i=1;i<length;i++){
            temp = temp->prev;
            delete temp->next;
        }
        delete temp;
        length = other.size();
        
        first = new element<T>;
        if(first == NULL) throw aghException(2,"Blad przydzialu pamieci", __FILE__, __LINE__);
        first->data = other.at(0);
        temp = first;
        for(int i=1;i<length;i++){
            temp->next = new element<T>;
            if(temp->next == NULL) throw aghException(2,"Blad przydzialu pamieci", __FILE__, __LINE__);
            temp->next->prev = temp;
            temp = temp->next;
            temp->data = other.at(i);
        }
    }
    return *this;
}
 
 
template<class T>
aghDlist<T>::~aghDlist(){
    element<T>* temp = first;
    while(length){
        temp = first;
        for(int i=0;i<length-1;i++){
            temp = temp->next;
        }
        delete temp;
        length--;
    }
    length = 0;
}
 
template <class T>
bool aghDlist<T>::insert(int index, T const& value){
    if(index < 0 || index > length){
        return false;
    }
 
    element<T> *temp;
    element<T> *new_el = new element<T>;
    if(new_el == NULL) throw aghException(2,"Blad przydzialu pamieci", __FILE__, __LINE__);
    new_el->data = value;
 
    if(index == 0){
        if(first == NULL){
            first = new_el;
            last = new_el;
            new_el->next = NULL;
            new_el->prev = NULL;
        }
        else{
            temp = first;
            first = new_el;
            new_el->next = temp;
            new_el->prev = NULL;
            temp->prev = first;
        }
    }
    else{
        temp = first;
        for(int i=0;i<index-1;i++){
            temp = temp->next;
        }
 
        if(temp->next == NULL){
            temp->next = new_el;
            new_el->prev = temp;
            new_el->next = NULL;
            last = new_el;
        }
        else{
            new_el->next = temp->next;
            new_el->prev = temp;
            temp->next = new_el;
        }
    }
 
    length++;
 
    return true;
}
 
template<class T>
T& aghDlist<T>::at(int index) const{
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
int aghDlist<T>::size(void) const{
    return length;
}
 
template<class T>
bool aghDlist<T>::remove(int index){
    if(index < 0 || index > length){
        return false;
    }
    else{
        element<T>* temp = first;
        for(int i=0;i<index;i++){
            temp = temp->next;
        }
 
        if(temp->next != NULL && temp->prev != NULL){
            temp->next->prev = temp->prev;
            temp->prev->next = temp->next;
        }
        if(temp->next == NULL && temp->prev != NULL) temp->prev->next = NULL;
        if(temp->next != NULL && temp->prev == NULL) temp->next->prev = NULL;
        if(temp->next == NULL && temp->prev == NULL) first = NULL;
 
        if(index == length-1) last = temp->prev;
        if(index == 0) first = temp->next;
        
        delete temp;
        length--;
        return true;
    }
}
 
#endif

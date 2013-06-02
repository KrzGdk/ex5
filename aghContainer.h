/**
* \file aghContainer.h
* \author Krzysztof Gadek i Stanislaw Burkat
* \date 24.05.2013
* \version 1.0
* \brief Definicja klasy abstrakcyjnej aghContainer, z ktorej beda dziedziczone klasy pojemnikowe
*/
// -------------------------------------------------------------------------

#ifndef AGHCONTAINER_H
#define AGHCONTAINER_H

// -------------------------------------------------------------------------
 
/**
* \class aghContainer
* \author Krzysztof Gadek i Stanislaw Burkat
* \date 24.05.2013
* \brief Definicja klasy abstrakcyjnej aghContainer, z ktorej beda dziedziczone klasy pojemnikowe
*/

// -------------------------------------------------------------------------

template<class T>
class aghContainer{
public:
    /// \brief Konstruktor domyślny
    aghContainer() {}
    /// \brief Konstruktor kopiujacy
    aghContainer(const aghContainer&) {}
    /// \brief Wirtualny destruktor
    virtual ~aghContainer() {}

    /// \brief Metoda dodajaca wartosc do pojemnika
    ///
    /// \param index - indeks wstawianego elementu
    /// \param value - wstawiana wartosc
    /// \return Wartosc logiczna informujaca o powodzeniu operacji
    virtual bool insert(int index, T const& value) = 0;

    /// \brief Metoda pobierajaca wartosc z pojemnika
    ///
    /// \param index - indeks pobieranego elementu
    /// \return Pobierana wartosc
    virtual T& at(int index) const = 0;

    /// \brief Metoda pobierajaca ilosc elementow pojemnika
    ///
    /// \return Ilosc elementow w pojemniku
    virtual int size(void) const = 0;

    /// \brief Metoda usuwajaca wartosc z pojemnika
    ///
    /// \param index - indeks usuwanego elementu
    /// \return Wartosc logiczna informujaca o powodzeniu operacji
    virtual bool remove(int index) = 0;

    /// \brief Metoda dodajaca wartosc na koniec pojemnika
    ///
    /// \param value - wstawiana wartosc
    /// \return Wartosc logiczna informujaca o powodzeniu operacji
    void append(T const& value);

    /// \brief Metoda zastepujaca wartosc w pojemniku
    ///
    /// \param index - indeks zastepowanego elementu
    /// \param value - wstawiana wartosc
    /// \return Wartosc logiczna informujaca o powodzeniu operacji
    bool replace(int index, T const& value);

    /// \brief Metoda usuwajaca wszystkie elementy pojemnika
    void clear(void);

    /// \brief Metoda sprawdzajaca czy pojemnik jest pusty
    ///
    /// \return Wartosc logiczna informujaca czy pojemnik jest pusty
    bool isEmpty(void);

    /// \brief Metoda podajaca indeks pierwszego znalezionego elementu o danej wartosci
    ///
    /// \param _value - szukana wartosc
    /// \param _from - indeks elementu, od ktorego rozpoczyna sie wyszukiwanie (domyslnie 0)
    /// \return Indeks pierwszego znalezionego elementu
    int indexOf(T const& _value, int _from = 0) const;

    /// \brief Metoda sprawdzajaca czy pojemnik zawiera dana wartosc
    ///
    /// \param _value - sprawdzana wartosc
    /// \param _from - indeks elementu, od ktorego rozpoczyna sie sprawdzanie (domyslnie 0)
    /// \return Wartosc logiczna informujaca o znalezieniu elementu
    bool contains(T const& _value, int _from = 0) const;
    
    /// \brief Operator porownojacy dwa pojemniki z dokladnoscia do kolejnosci
    ///
    /// \param right - pojemnik do porownania
    /// \return Wartosc logiczna informujaca o rownosci
    bool operator==(aghContainer<T> const& right);

    /// \brief Operator sprawdzajacy czy pojemniki sa rozne (z dokladnoscia do kolejnosci)
    ///
    /// \param right - pojemnik do porownania
    /// \return Wartosc logiczna informujaca o nierownosci
    bool operator!=(aghContainer<T> const& right);

    /// \brief Operator pobierajacy wartosc z pojemnika
    ///
    /// \param n - indeks pobieranego elementu
    /// \return Pobierana wartosc
    T& operator[](int n) const;

    /// \brief Operator dodajacy wszystkie elementy z podanego pojemnika
    ///
    /// \param right - Pojemnik, z ktorego dodawane sa elementy
    /// \return Referencja do this
    aghContainer<T>& operator+=(aghContainer<T> const& right);

    /// \brief Operator dodajacy dany element na koniec pojemnika
    ///
    /// \param element - dodawany element
    /// \return Referencja do this
    aghContainer<T>& operator+=(T const& element);

    /// \brief Operator dodajacy dany element na koniec pojemnika
    ///
    /// \param element - dodawany element
    /// \return Referencja do this
    aghContainer<T>& operator<<(T const& element);

    /// \brief Operator dodajacy wszystkie elementy z podanego pojemnika
    ///
    /// \param right - Pojemnik, z ktorego dodawane sa elementy
    /// \return Referencja do this
    aghContainer<T>& operator<<(aghContainer<T> const& right);

    /// \brief Operator wypisujacy zawartosc pojemnika na podany strumien
    ///
    /// \param out - Strumien do wypisania danych
    /// \param right - Pojemnik, ktorego zawartosc zostanie wypisany
    /// \return Referencja do danego strumienia
    template<class T2>
    friend ostream& operator<<(ostream& out, aghContainer<T2> const& right);
    
    /// \brief Wirtualny perator przypisania pojemnika
    ///
    /// \param right - Pojemnik, z ktorego dodawane sa elementy
    /// \return Referencja do this
    virtual aghContainer<T>& operator=(aghContainer<T> const& other) = 0;
};

// -------------------------------------------------------------------------

template<class T2>
ostream& operator<<(ostream& out, aghContainer<T2> const& right){
    for(int i=0;i<right.size();i++){
        out << right.at(i) << " ";
    }
    return out;
}

template<class T>
void aghContainer<T>::append(T const& value)
{
	insert(size(), value);
}

template<class T>
bool aghContainer<T>::replace(int index, T const& value)
{
	return (remove(index) && insert(at(index), value));
}

template<class T>
void aghContainer<T>::clear(void)
{
	while (size())
	{
		remove(size()-1);
	}
}

template<class T>
bool aghContainer<T>::isEmpty(void)
{
	if (size())
		return false;
	else
		return true;
}

template<class T>
int aghContainer<T>::indexOf(T const& _value, int _from) const
{
	for (int i=_from;i < size();i++)
	{
		if(at(i)==_value) return i;
	}
	return -1;

}
template<class T>
bool aghContainer<T>::contains(T const& _value, int _from) const{
	if(indexOf(_value, _from)==-1)
		return false;
	else return true;
}

template<class T>
bool aghContainer<T>::operator==(aghContainer<T> const& right){
    if(size() != right.size()){
        return false;
    }
    else{
        for(int i=0;i<size();i++){
            if(this->at(i) != right.at(i)){
                return false;
            }
        }
        return true;
    }
                
}

template<class T>
bool aghContainer<T>::operator!=(aghContainer<T> const& right){
    return !(*this == right);
}

template<class T>
T& aghContainer<T>::operator[](int n) const{
	return at(n);
}

template<class T>
aghContainer<T>& aghContainer<T>::operator+=(aghContainer<T> const& right){
	for(int i=0; i<right.size(); i++){
		append(right.at(i));
	}
	return *this;
}

template<class T>
aghContainer<T>& aghContainer<T>::operator+=(T const& element){
	append(element);
	return *this;
}

template<class T>
aghContainer<T>& aghContainer<T>::operator<<(T const& element){
	append(element);
	return *this;
}

template<class T>
aghContainer<T>& aghContainer<T>::operator<<(aghContainer<T> const& right){
	for(int i=0; i<right.size(); i++){
		append(right[i]);
	}
	return *this;
}

#endif

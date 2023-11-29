/* ==========================
   (c) WMP.SNS UKSW, 2015
========================== */

#include<iostream>
#include<fstream>
#include<string>
#include<limits>
#include<exception>

using namespace std;

class _Bazowe_Cechy {
public:
	// pola statyczne sta³e - dla sta³ych wartoœci ca³kowitych
	static const bool _jest_liczba = false;
	static const bool _nalezy_do_przedzialu = false;
	static const bool _jest_liczba_calkowita = false;
	static const bool _jest_czasem_uderzen_zegara = false;
	static const bool _jest_iloscia_piwa = false;
	static const bool _jest_liczba_pierwsza = false;
};

template<typename T>
class _Cechy : public _Bazowe_Cechy {
public:
	// metody statyczne - dla wartoœci innych typów ni¿ liczby ca³kowite
	static const T _dolna_granica() { return T(); };
	static const T _gorna_granica() { return T(); };
};

template<typename T>
class Cechy : public _Cechy<T> {
};

class przyspieszenie {
	double a;
public:
	przyspieszenie(double acc = 0) : a(acc) {};
	double operator()() const { return a; };
	przyspieszenie& operator=(double acc) { a = acc; return *this; };
	bool operator<(const przyspieszenie& p) const { return (a < p.a); };
	friend ostream& operator<<(ostream& os, const przyspieszenie&);
};
ostream& operator<<(ostream& os, const przyspieszenie& p) { return os << p.a; };

template<>
class Cechy<przyspieszenie> : public _Cechy<przyspieszenie> {
public:
	static const bool _jest_liczba = true;
};

class temperatura_wody {
	double t;
public:
	temperatura_wody(double temp = 50) : t(temp) {};
	double operator()() const { return t; };
	temperatura_wody& operator=(double temp) { t = temp; return *this; };
	bool operator<(const temperatura_wody& tw) const { return (t < tw.t); };
	friend ostream& operator<<(ostream& os, const temperatura_wody&);
};
ostream& operator<<(ostream& os, const temperatura_wody& tw) { return os << tw.t; };

template<>
class Cechy<temperatura_wody> : public _Cechy<temperatura_wody> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const temperatura_wody _dolna_granica() { return temperatura_wody(0); };
	static const temperatura_wody _gorna_granica() { return temperatura_wody(100); };
};

class kostka_do_gry {
	int n;
public:
	kostka_do_gry(int num = 1) : n(num) {};
	int operator()() const { return n; };
	kostka_do_gry& operator=(int num) { n = num; return *this; };
	bool operator<(const kostka_do_gry& k) const { return (n < k.n); };
	friend ostream& operator<<(ostream& os, const kostka_do_gry&);
};
ostream& operator<<(ostream& os, const kostka_do_gry& k) { return os << k.n; };

template<>
class Cechy<kostka_do_gry> : public _Cechy<kostka_do_gry> {
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_liczba_calkowita = true;
	static const kostka_do_gry _dolna_granica() { return kostka_do_gry(1); };
	static const kostka_do_gry _gorna_granica() { return kostka_do_gry(6); };
};

class Przepelnienie : public exception {
	char opis[100];
public:
	Przepelnienie(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};
class BrakDanych : public exception {
	char opis[100];
public:
	BrakDanych(const char* o) { strcpy_s(opis, o); }
	const char* what() const throw() { return opis; };
};



//kod dopisany na zajeciach!
class minuta_dnia
{
	int m;
public:
	minuta_dnia(int minuta = 1) :m(minuta) {};
	int operator()() const { return m; };
	minuta_dnia& operator=(int md) { m = md; return *this; };
	bool operator<(const minuta_dnia& md) const { return (m < md.m); };
	friend ostream& operator<<(ostream& os, const minuta_dnia&);
};
ostream& operator<<(ostream& os, const minuta_dnia& md) { return os << md.m; };

template<>
class Cechy<minuta_dnia> : public _Cechy<minuta_dnia>
{
public:
	static const bool _jest_liczba = true;
	static const bool _jest_liczba_calkowita = true;
	static const bool _nalezy_do_przedzialu = true;
	static const minuta_dnia _dolna_granica() { return minuta_dnia(0); };
	static const minuta_dnia _gorna_granica() { return minuta_dnia(24*60); };
};



class zegar
{
	double c;
public:
	zegar(double czas = 0.8) :c(czas) {};
	double operator()() const { return c; };
	zegar& operator=(double z) { c = z; return *this; };
	bool operator<(const zegar& z) const { return (c < z.c); };
	friend ostream& operator<<(ostream& os, const zegar&);
};

template<>
class Cechy<zegar> : public _Cechy<zegar>
{
public:
	static const bool _jest_liczba = true;
	static const bool _nalezy_do_przedzialu = true;
	static const bool _jest_czasem_uderzen_zegara = true;
	static const zegar _dolna_granica() { return zegar(0.8); };
	static const zegar _gorna_granica() { return zegar(22.8); };
};
ostream& operator<<(ostream& os, const zegar& z) { return os << z.c; };

bool Czy_jest_uderzeniem_zegara(double c)
{
 	c = c - 0.8;
	int pom = c;
	if (abs(pom - c) < 0.001 && pom % 2 == 0)
		return true;
	else
		return false;
}



class piwo
{
	double ml;
public:
	piwo(double obj = 0.568) :ml(obj) {};
	double operator()() const { return ml; };
	piwo& operator=(double p) { ml = p; return *this; };
	bool operator<(const piwo& p) const { return (ml < p.ml); };
	friend ostream& operator<<(ostream& os, const piwo&);
};
template<>
class Cechy<piwo> :public _Cechy<piwo>
{
public:
	static const bool _jest_liczba = true;
	static const bool _jest_iloscia_piwa = true;
};
ostream& operator<<(ostream& os, const piwo& p) { return os << p.ml; };

bool Czy_przemienny_na_pinty(double ml)
{
	double pom = ml / 0.568;
	int p = pom;
 	if (abs(pom - p) < 0.001)
		return true;
	else
		return false;
}


class liczba_pierwsza
{
	int p;
public:
	liczba_pierwsza(int lp = 3) :p(lp) {};
	int operator()() const { return p; };
	liczba_pierwsza& operator=(int lp) { p = lp; return *this; };
	bool operator<(const liczba_pierwsza& lp) const { return(p < lp.p); };
	friend ostream& operator<<(ostream& os, const liczba_pierwsza&);
};
template<>
class Cechy<liczba_pierwsza> :public _Cechy<liczba_pierwsza>
{
public:
	static const bool _jest_liczba = true;
	static const bool _jest_liczba_pierwsza = true;
	static const bool _jest_liczba_calkowita = true;
};
ostream& operator<<(ostream& os, const liczba_pierwsza& lp) { return os << lp.p; };

bool Czy_jest_liczba_pierwsza(int p)
{
	if (p < 2)
		return false;
	int pom = sqrt(p);
	for (int i = 2; i <= pom; i++)
	{
		if (p%i == 0)
			return false;
	}
	return true;
}

//szablon stosu
template<typename T, int rozmiar, typename CechyT = Cechy<T>>
class SzablonStosu {
	T stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	SzablonStosu() : top(0) {}
	void push(const T& i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	void push(int i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja wartoœci przekazanej do zapisu
		if (CechyT::_jest_liczba && CechyT::_jest_liczba_calkowita)
		{
			if (CechyT::_jest_liczba_pierwsza)
			{
				if (Czy_jest_liczba_pierwsza(i))
				{
					if (CechyT::_nalezy_do_przedzialu) {
						if (!(T(i) < CechyT::_dolna_granica()) && !(CechyT::_gorna_granica() < T(i)))
							stos[top++] = i;
					}
					else
						stos[top++] = i;
				}
				return;
			}
			if (CechyT::_nalezy_do_przedzialu) {
				if (!(T(i) < CechyT::_dolna_granica()) && !(CechyT::_gorna_granica() < T(i)))
					stos[top++] = i;
			}
			else
				stos[top++] = i;
		}
 	}
	void push(double i) {
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());

		// walidacja wartoœci przekazanej do zapisu
		if (CechyT::_jest_liczba && !CechyT::_jest_liczba_calkowita) 
		{
			if (CechyT::_jest_czasem_uderzen_zegara)
			{
				if (Czy_jest_uderzeniem_zegara(i))
				{
					if (CechyT::_nalezy_do_przedzialu) {
						if (!(T(i) < CechyT::_dolna_granica()) && !(CechyT::_gorna_granica() < T(i)))
							stos[top++] = i;
					}
					else
						stos[top++] = i;
				}
				return;
			}
			if (CechyT::_jest_iloscia_piwa)
			{
				if(Czy_przemienny_na_pinty(i))
				{
					if (CechyT::_nalezy_do_przedzialu) {
						if (!(T(i) < CechyT::_dolna_granica()) && !(CechyT::_gorna_granica() < T(i)))
							stos[top++] = i;
					}
					else
						stos[top++] = i;
				}
				return;
			}
			if (CechyT::_nalezy_do_przedzialu) {
				if (!(T(i) < CechyT::_dolna_granica()) && !(CechyT::_gorna_granica() < T(i)))
					stos[top++] = i;
			}
			else
				stos[top++] = i;
		}
 	}
	T pop() {
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());

		return stos[--top];
	}
	template<typename U1, int r, typename U2>
	friend ostream& operator<<(ostream& os, const SzablonStosu<U1, r, U2>&);
};
template<typename U1, int r, typename U2>
ostream& operator<<(ostream& os, const SzablonStosu<U1, r, U2>& S)
{
	for (int i = 0; i < S.top; i++) cout << S.stos[i] << endl;
	return os;
};



//ZADANIE 2
class Stos2
{
	static const int rozmiar = 10;
protected:
	double stos[rozmiar];
	int top;
public:
	int zajetosc() { return top; };
	Stos2() : top(0) {}
	virtual void push(const double& i)
	{
		if (top == rozmiar)
			throw Przepelnienie(typeid(i).name());
		stos[top++] = i;
	}
	virtual double pop() 
	{
		if (top == 0)
			throw BrakDanych(typeid(stos[0]).name());
		return stos[--top];
	}
	virtual void wypisz()
	{
		for (int i = 0; i < top; i++)
			cout << stos[i] << endl;
	}
};


template<class T>
class domieszka1 : public T
{
public:
	double pop()
	{
		cout << "Twoj stos przed wyrzuceniem liczby to:" << endl;
		T::wypisz();
		double pom = T::pop();
		cout << "Wyrzucona licba to " << pom << endl;
		return pom;
	}
};

template<class T>
class domieszka2: public T
{
	double suma;
public:
	domieszka2(double s = 0) :suma(s) {};
	double pop()
	{
		cout << "Suma przed zdjeciem liczby to " << suma << endl;
		double pom = T::pop();
		suma = suma - pom;
		return pom;
	}
	void push(const double& i)
	{
		suma = suma + i;
		T::push(i);
	}
};



int main() {
	SzablonStosu<string, 7> K1;
	SzablonStosu<przyspieszenie, 10> K2;
	SzablonStosu<temperatura_wody, 10> K3;
	SzablonStosu<kostka_do_gry, 10> K4;

	// zape³nianie stosów K1, K2, K3 i K4:
	ifstream fi("qv-lab4.txt");
	string s;
	try {
		K1.push("Henryk");
		K1.push("Sienkiewicz");
		while (fi) {
			fi >> s;
			K1.push(s);
			fi.seekg(ios::beg);
			fi.clear();
			cout << '*';
		};
	}
	catch (Przepelnienie& e) {
		cout << "K1 gotowy: " << e.what() << endl;
	};
	cout << "Danych na stosie K1: " << K1.zajetosc() << endl << endl;

	K2.push(przyspieszenie());
	K2.push(przyspieszenie(5.0));
	K2.push(10);	// uwaga: nie akceptujemy przyspieszenia jako liczby ca³kowitej
	K2.push(10.0);
	cout << K2;
	cout << "Danych na stosie K2: " << K2.zajetosc() << endl << endl;

	K3.push(temperatura_wody());
	K3.push(temperatura_wody(36.6));
	K3.push(71.2);
	K3.push(112.1); // uwaga: nie akceptujemy wartoœci spoza przedzia³u
	cout << K3;
	cout << "Danych na stosie K3: " << K3.zajetosc() << endl << endl;

	K4.push(kostka_do_gry(3));
	K4.push(kostka_do_gry());
	K4.push(6);
	K4.push(10); // uwaga: nie akceptujemy wartoœci spoza przedzia³u
	cout << K4;
	cout << "Danych na stosie K4: " << K4.zajetosc() << endl << endl;

	// opró¿nianie stosów
	try {
		while (true)
			K1.pop();
	}
	catch (BrakDanych& e) {
		cout << "K1 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K2.pop();
	}
	catch (BrakDanych& e) {
		cout << "K2 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K3.pop();
	}
	catch (BrakDanych& e) {
		cout << "K3 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			K4.pop();
	}
	catch (BrakDanych& e) {
		cout << "K4 pusty: " << e.what() << endl;
	}

	system("pause");
	//kod dopisany na zajeciach!
	cout << "\n" << endl;
	SzablonStosu<minuta_dnia, 10> M1;
	M1.push(minuta_dnia());
	M1.push(minuta_dnia(120));
	M1.push(123.3);					//zle
	M1.push(1231);
	M1.push(1500);					//zle
	M1.push(180);
	M1.push(1440);
	cout << M1;
	cout << "Danych na stosie M1: " << M1.zajetosc() << endl << endl;

	SzablonStosu<zegar, 10> Z1;
	Z1.push(zegar());
	Z1.push(zegar(2.8));
	Z1.push(22.8);
	Z1.push(3.8);					//zle
	Z1.push(8.8);
	Z1.push(7.7);					//zle
	Z1.push(24.8);					//zle
	cout << Z1;
	cout << "Danych na stosie Z1: " << Z1.zajetosc() << endl << endl;

	SzablonStosu<piwo, 10> P1;
	P1.push(piwo());
	P1.push(piwo(1.136));
	P1.push(4.0);					//zle
	P1.push(12);					//zle
	P1.push(568.0);
	P1.push(0.789);					//zle
	P1.push(0.569);					//zle
	P1.push(1.704);
	cout << P1;
	cout << "Danych na stosie P1: " << P1.zajetosc() << endl << endl;

	SzablonStosu<liczba_pierwsza, 10> L1;
	L1.push(liczba_pierwsza());
	L1.push(liczba_pierwsza(7));
	L1.push(4);						//zle
	L1.push(13);
	L1.push(121);					//zle
	L1.push(51432);					//zle
	L1.push(23);
	cout << L1;
	cout << "Danych na stosie L1: " << L1.zajetosc() << endl << endl;

	try {
		while (true)
			M1.pop();
	}
	catch (BrakDanych& e) {
		cout << "M1 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			Z1.pop();
	}
	catch (BrakDanych& e) {
		cout << "Z1 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			P1.pop();
	}
	catch (BrakDanych& e) {
		cout << "P1 pusty: " << e.what() << endl;
	}
	try {
		while (true)
			L1.pop();
	}
	catch (BrakDanych& e) {
		cout << "L1 pusty: " << e.what() << endl;
	}
	system("pause");

	//ZADANIE 2
	cout << "\n" << endl;
	//domieszka2<domieszka1<Stos2>> S1;
	domieszka1<Stos2> S1;
	domieszka2<Stos2> S2;
	cout << "Stos z 1. domieszka:" << endl;
	for (double i = 0.1; i < 10; i = i + 2)
	{
		S1.push(i);
	}
	S1.pop();
	S1.pop();
	cout << "Stos z 2. domieszka" << endl;
	for (double i = 1.1; i < 10; i = i + 2)
	{
		S2.push(i);
	}
	S2.pop();
	S2.pop();
	cout << "\n ZMIANA w programie!!!!" << endl;
	cout << "Koniec programu." << endl;
	return 0;
}
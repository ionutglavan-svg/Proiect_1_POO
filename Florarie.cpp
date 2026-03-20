//Tin sa mentionez ca in implementarea programului nu am folosit instrumente AI
//afisarile ce includ linii '-' sunt pur estetice.

//Programul simuleaza baza de date a unei florarii cu urmatoarele entitati:
//a) Produsele florariei;
//b) Comenzile aflate in procesare;
//c) Livrarile unor comenzi;

//Fiecare dintre cele 3 entitati are un set de functionalitati specifice:
//a) i. afisarea tuturor produselor;
//  ii. afisarea produselor perisabile;

//b) i. afisarea tuturor comenzilor;
//  ii. stergerea unei comenzi din lista;
// iii. adaugarea unei comenzi in lista;

//c) i. afisarea tuturor livrarilor;
//  ii. modificarea statutului unei livrari (livrata/nelivrata);

//Scurta descriere:

//	Programul contine 3 clase in care fiecare obiect al fiecarei clase este aflat intr o 
// lista simplu inlantuita alaturi de celelalte obiecte de acelasi tip. De asemenea, 
// intre fiecare obiect al clasei 'Livrare' este un pointer catre un obiect de tipul 
// 'Comanda', pentru ca fiecarei livrari sa ii fie legata o comanda (in adevaratul sens 
// al cuvantului).
//		In 'main' am creat cate un set de obiecte implicit pentru fiecare clasa, iar mai 
// apoi cu ajutorul structurii 'switch' am realizat un meniu interactiv.

//Descrierea datelor de intrare:
//	Am definit clasele "Produs", "Comanda", "Livrare". 
		//->Un obiect din clasa "Produs" are urmatoarele campuri :
			//-denumire(un pointer de tip char ce retine denumirea produsului);
			//-pret(retine pretul produsului);
			//-stoc(retine numarul de bucati al fiecarui produs);
			//-perisabil(o variabila bool - eana ce indica daca un produs este perisabil sau nu);
			//-urm(un pointer spre urmatorul obiect de tip "Produs");
			
		//->Un obiect din clasa "Comanda" are urmatoarele campuri :
			//-telefonClient(un pointer de tip char ce retine adresa unui sir de caractere ce reprezinta numarul de telefon al clientului);
			//-totalPlata(retine pretul total al comenzii in functie de cantitate/pret);
			//-nrProduse(retine numarul de bucati comandat);
			//-id(retine ID - ul comenzii);
			//-valid(initializat implicit cu true, indica daca numarul de bucati solicitat este disponibil sau nu);
			//-adresa(un pointer de tip char ce retine adresa unui sir de caractere ce reprezinta adresa in care se va livra comanda);
			//-urm(un pointer spre urmatorul obiect de tip "Comanda");
			
		//->Un obiect din clasa "Livrare" are urmatoarele campuri :
			//-cmdAsociata(un pointer de tip Comanda ce retine adresa unui obiect reprezinta comanda asociata livrarii din baza de date);
			//-idCmd(retine ID - ul comenzii ce coincide cu ID - ul livrarii);
			//-livrat(initializat implicit cu false, indica daca livrarea a fost efectuata sau nu);
			//-urm(un pointer spre urmatorul obiect de tip "Livrare");




#define _CRT_SECURE_NO_WARNINGS //<-----spatiu de lucru: VisualStudioComunity nu imi permite folosirea 'strcpy' fara linia asa ca sunt nevoit sa o folosesc
#include <iostream>
#include <cstring>

//using namespace std;

class Comanda;//sunt declarate inainte de toate in scopul vizibilitatii pentru functia prieten 'strgLivrareComanda'
class Livrare;

class Produs {
	char* denumire;
	float pret;
	int stoc;
	Produs* urm;
	bool perisabil;
public:

	static int cont, index;//'cont' este destinat numerotarii produselor la afisare (este incrementat doar in functia de afisare)
							//'index' este destinat retinerii numarului total de obiecte (este incrementat doar in constructor)
	
	//CONSTRUCTOR fara parametrii
	Produs() {
		this->denumire = new char[2];
		strcpy(this->denumire, "");
		this->pret = 0;
		this->stoc = 0;
		this->perisabil = 0;
		this->urm = NULL;
	}

	//CONSTRUCTOR cu parametrii
	Produs(Produs*& prim, const char d[], double p, int s, bool per) : pret(p), stoc(s), perisabil(per)
			//parametrul 'prim' va retine adresa pointerului care pointeaza spre primul obiect creat
			//parametrul 'd[]' va retine un sir de caractere (denumirea produsului)
			//parametrul 'p' va retine	valoarea pretului
			//parametrul 's' va retine valoarea stocului
			//parametrul 'per' va retine true/false
			
	{
		index++;
		this->denumire = new char[strlen(d) + 1];
		strcpy(this->denumire, d);

		this->urm = NULL;

		if (prim == NULL)
		{
			prim = this;
		}
		else
		{

			Produs* ptr = prim;
			while (ptr->urm != NULL)
			{
				ptr = ptr->urm;
			}

			ptr->urm = this;
		}
	}

	//Functie prieten destinata supraincarcarii operatorului de afisare
	friend std::ostream& operator<<(std::ostream& out, const Produs& pr)
	{
		out << pr.denumire << "  ||  " << pr.pret << " RON "
			<< "  ||  " << pr.stoc << "  ||  " << ((pr.perisabil == true) ? "perisabil" : "nonperisabil") << "\n\n";
		return out;
	}

	//CONSTRUCTOR DE COPIERE
	Produs(const Produs& nou)
	{
		this->pret = nou.pret;
		this->stoc = nou.stoc;
		this->urm = NULL;
		this->perisabil = nou.perisabil;

		this->denumire = new char[strlen(nou.denumire) + 1];
		strcpy(this->denumire, nou.denumire);

	}

	//METODE
	void restoc(const Produs& re)
	{
		this->stoc = re.stoc;
	}

	void afisare(bool tipAfisare=false)
	{	
		Produs::cont = 0;
		if(!tipAfisare)
		{
			if (this != NULL)
			{
				std::cout << "-- Produsle disponibile -- \n\n";
				Produs* pr = this;
				while (pr != NULL)
				{
					std::cout <<++cont<<". "<< * pr;	//	SUPRAINCARCAREA OPERATORILOR
					pr = pr->urm;
				}
			}
			else
				std::cout << "-- Produs indisponibile --  \n";
		}
		else
		{
			if (this != NULL)
			{
				std::cout << "-- Produsle disponibile -- \n\n";
				Produs* pr = this;
				while (pr != NULL)
				{
					std::cout << ++cont << ". "<< pr->denumire << "  ||  " << pr->pret << " RON "
						<< "  ||  " << pr->stoc << "\n\n";
					pr = pr->urm;
				}
			}
			else
				std::cout << "-- Produs indisponibile --  \n";
		}
	}

	void afisare_perisabile()
	{
		if (this != NULL)
		{
			bool ok = false;
			std::cout << "-- Produsle perisabile -- \n";
			Produs* pr = this;
			while (pr != NULL)
			{
				char frum[20];
				if (pr->perisabil == true)
				{
					strcpy(frum, "perisabil");
					std::cout << pr->denumire << "  |  " << pr->pret << " RON "
						<< "  |  " << pr->stoc << "  |  " << frum << "\n";
					ok = true;
				}
				
				pr = pr->urm;
			}
			if (!ok)
				std::cout << "-- Nu sunt Produs perisabile in stoc -- \n";
		}
		else
			std::cout << "-- Nu sunt Produs inca --  \n";
		std::cout << "\n";
	}

	//GETTERI

	float getPret() const;

	int getStoc() const;

	char* getDen() const;

	Produs* getByDen(char d[]);

	//SETTER(I)

	void setStoc(int st)
	{
		stoc = st;
	}

	//DESTRUCTOR

	~Produs()
	{
		//cout << "~Produs()" << endl;
		delete[] denumire;
		delete urm; //recursie
	} 


};

int Produs::cont = 0, Produs::index=0;
inline float Produs::getPret() const
{
	return pret;
}
inline int Produs::getStoc() const
{
	return stoc;
}
inline Produs* Produs::getByDen(char d[])
{
	//apelat cu prim->...
	Produs* p = this;
	while (p != NULL)
	{
		char aux[256];
		strcpy(aux, p->denumire);
		if (strcmp(_strupr(aux), _strupr(d)) == 0)
			return p;
		p = p->urm;
	}
	return NULL;
}

char* Produs::getDen() const
{
	return denumire;
}


class Comanda {
	char *telefonClient;
	float totalPlata;
	int nrProduse;
	char* produs;
	int id;
	bool valid = true;
	char* adresa;
	Comanda* urm;

public:

	static int contor;//'contor' este incrementat la creerea unui nou obiect si decrementat la stergerea unui obiect de tip Comanda, el este ID - ul

	//CONSTRUCTOR fara parametrii
	Comanda()
	{
		this->telefonClient = new char[2];
		strcpy(this->telefonClient, "");
		this->totalPlata = 0;
		this->nrProduse = 0;
		this->produs = new char[2];
		strcpy(this->produs, "");
		this->id = 0;
		this->valid = 0;
		this->adresa = new char[2];
		strcpy(this->adresa, "");
		this->urm = NULL;
	}

	//CONSTRUCTOR cu parametrii
	Comanda(Comanda*& cap, const char tel[], Produs* prd, int nr, const char adr[]) : id(++contor), nrProduse(nr)
		//'cap' va retine adresa pointerului care pointeaza spre primul obiect creat
		//'tel' va retine un sir de caractere (numarul de telefon)
		//'prd' va retine un pointer spre un obiect de tip produs (pentru a avea acces la getteri din clasa Produs)
		//'nr' va retine numarul de produse
		//'adr' va retine un sir de caractere (adresa pentru livrarea comenzii)
	{

		if (prd->getStoc() >= nr)
		{
			prd->setStoc(prd->getStoc() - nr);
			totalPlata = nr * prd->getPret();
		}
		else
		{
			this->valid = false;
			totalPlata = 0;

		}
		this->adresa = new char[strlen(adr) + 1];
		strcpy(this->adresa, adr);

		this->produs = new char[strlen(prd->getDen()) + 1];
		strcpy(this->produs, prd->getDen());

		this->telefonClient = new char[strlen(tel) + 1];
		strcpy(telefonClient, tel);
		this->urm = NULL;
		if (cap == NULL)
		{
			cap = this;
		}
		else
		{
			Comanda* i = cap;
			while (i->urm != NULL)
			{
				i = i->urm;
			}
			i->urm = this;
		}


	}

	//Functie prieten destinata supraincarcarii operatorului de afisare
	friend std::ostream& operator<<(std::ostream& t, Comanda& cmd)
	{
		t << "Comanda numarul-> " << cmd.id << " || "
			<< "Continut comanda-> " << cmd.produs << " || "
			<< "Numar Produse-> " << cmd.nrProduse << " || "
			<< "Pret total-> " << cmd.totalPlata
			<< " || " << "Contact-> " << cmd.telefonClient << " || "
			<< "Adresa-> " << cmd.adresa << "\n" << "\n" << "\n";
		return t;
	}

	//METODE

	void afisare()
	{
		if (this != NULL)
		{
			Comanda* cmd = this;
			std::cout << "--  Comanda in procesare  --\n\n";
			while (cmd != NULL)
			{
				if (cmd->valid)
				{
					std::cout << *cmd;
				}
				else
				{
					std::cout << "Comanda numarul-> " << cmd->id << " || "<< "Pret total-> "
						<< cmd->totalPlata
						<< " || " << "Contact-> " << cmd->telefonClient << "  <-- STOC INSUFICIENT" << "\n" << "\n" << "\n";
				}
				cmd = cmd->urm;
			}
		}
		else
			std::cout << "----- NICIO COMANDA PLASATA INCA -----" << "\n";
		std::cout << "\n";
	}

	Comanda* CautId(Comanda* cap, int id) const;//Metoda ce returneaza pointerul de tip Comanda ce pointeaza spre comanda cu ID - ul cautat

	//GETTERI

	int getNrProd() const;

	bool getValid() const;

	const char* getAdresa() const;

	const int getId() const;

	//FUNCTIE PRIETEN comuna clasei Livrare destinata stergerii unei comenzi, si, implicit livrarea corespunzatoare ei (daca exista)
	friend void strgLivrareComanda(Comanda*& cap, Livrare*& vf, int id);

	//DESTRUCTOR
	~Comanda()
	{
		//cout << "Am sters na" << endl;
		delete[] telefonClient;
		delete[] produs;
		delete[] adresa;
		delete urm; //recursie
	}
};

inline Comanda* Comanda::CautId(Comanda* cap, int id) const
{

	if (cap != NULL && cap->id == id)
	{
		return cap;
	}
	else
		if (cap != NULL)
		{
			Comanda* p = cap;
			while (p->urm != NULL && p->urm->id != id)
			{
				p = p->urm;
			}
			if (p->urm != NULL)
			{
				return p->urm;
			}
		}

	return NULL;
}
inline const int Comanda::getId() const
{
	return id;
}

int Comanda::getNrProd() const
{
	return this->nrProduse;
}
bool Comanda::getValid() const
{
	return this->valid;
}
const char* Comanda::getAdresa() const
{
	return adresa;
}

int Comanda::contor = 0;

class Livrare {
	Comanda* cmdAsociata;
	int idCmd;
	bool livrat = false;
	Livrare* urm;

public:
	//CONSTRUCTOR fara parametrii
	Livrare()
	{
		this->cmdAsociata = NULL;
		this->idCmd = 0;
		this->livrat = 0;
		this->urm = NULL;
	}

	//CONSTRUCTOR cu parametrii
	Livrare(Livrare*& vf,Comanda* prm, int id, bool liv = false) : idCmd(id)
		//'vf' va retine adresa pointerului care pointeaza spre primul obiect creat
		//'prm' va retine un pointer spre un obiect de tip Comanda (comanda asociata livrarii)
		//'id' va retine ID - ul comenzii asociate
		//'liv' setat implicit cu false, retine statusul livrarii (livrata/nelivrata)
	{
		cmdAsociata = prm->CautId(prm, id);
		livrat = liv;


		if (vf == NULL)
		{
			vf = this;
			this->urm = NULL;
		}
		else
		{
			if (vf->idCmd > this->idCmd)
			{
				this->urm = vf;
				vf = this;
				
			}
			else

			{
				Livrare* l = vf;
				while (l->urm != NULL && l->idCmd < this->idCmd)
				{
					l = l->urm;
				}


				this->urm = l->urm;
				l->urm = this;
			}
			
		}
	}

	//Functie prieten destinata supraincarcarii operatorului de afisare
	friend std::ostream& operator<<(std::ostream& o, Livrare& p)
	{
		o << "ID-comanda-livrare-> " << p.idCmd << "  |  "
			<< "Adresa-> " << p.cmdAsociata->getAdresa() << "  |  "
			<< "Stare-> " << ((p.livrat == true) ? "livrat" : "nelivrat") << "  |  "
			<< "Numar Produs-> " << ((p.cmdAsociata->getValid() == true) ? (p.cmdAsociata)->getNrProd() : 0) << "\n";
		return o;
	}

	//METODE

	void afisare()
	{
		if (this != NULL)
		{
			std::cout << "--- DATE LIVRARE ---\n\n";
			Livrare* p = this;
			while (p != NULL)
			{
				std::cout << *p;
				p = p->urm;
			}
		}
		else
			std::cout << "--  NICIO LIVRARE INCARCATA  --\n";
		std::cout << "\n" << "\n";
	}

	//SETTER
	void setLivrare();

	//GETTER
	Livrare* getLivrare(Livrare* vf, int id) const;

	//FUNCTIE PRIETEN comuna clasei Comanda destinata stergerii unei comenzi, si, implicit livrarea corespunzatoare ei (daca exista)
	friend void strgLivrareComanda(Comanda*& cap, Livrare*& vf, int id);

	//DESTRUCTOR
	~Livrare()
	{
		//cout << "Am sters na 2" << endl;
		delete urm; //recursie
	}
};

inline Livrare* Livrare::getLivrare(Livrare* vf, int id) const
{

	if (vf != NULL && vf->idCmd == id)
	{
		return vf;
	}
	else
		if (vf != NULL)
		{
			Livrare* p = vf;
			while (p->urm != NULL && p->urm->idCmd != id)
			{
				p = p->urm;
			}
			if (p->urm != NULL)
			{
				return p->urm;
			}
		}

	return NULL;
}

void Livrare::setLivrare()
{
	int x;
	std::cout << "Pachetul cu ID-ul " << this->idCmd << " este " << ((this->livrat == true) ? "livrat" : "nelivrat") << ".\n\n";
	std::cout << "Apasati tasta 1 pentru a modifica in LIVRAT /  0 pentru a modifica in NELIVRAT\n\n";
	std::cin >> x;
	while (x != 0 && x != 1)
	{
		std::cout << "------OPTIUNE INVALIDA------\n\n" << "Reitroduceti: ";
		std::cin >> x;
	}
	this->livrat = x;
	std::cout << "\n" << "\n";
}

void strgLivrareComanda(Comanda*& cap, Livrare*& vf, int id)
{
	if (cap != NULL)//daca exista comenzi plasate
	{
		bool x = true;//true daca voi continua, false daca ma razgandesc
		if (vf != NULL && vf->idCmd == id)//daca am gasit livrarea cu ID - ul cautat si este prima
		{
			std::cout << "--ATENTIE! LIVRAREA CU ID-UL SELECTAT VA FI DE ASEMENEA STEARSA--\n\nDoriti sa continuati?	( 1->DA / 0->NU )\n\n";
			std::cin >> x;//aici decid daca ma razgandesc sau nu
			if (x)
			{
				Livrare* IlStergL = vf;
				vf = vf->urm;
				IlStergL->urm = NULL;
				delete IlStergL;//stergerea efectiva

				Livrare* p2L = vf;
				while (p2L != NULL)
				{
					p2L->idCmd--;//fiecare ID este actualizat
					p2L = p2L->urm;
				}
			}

		}
		else //altfel caut in restul listei simplu inlantuite
			if (vf != NULL)//daca am elemente in lista
			{
				Livrare* pL = vf;
				while (pL->urm != NULL && pL->urm->idCmd != id)
				{
					pL = pL->urm;
				}

				if (pL->urm != NULL)
				{
					std::cout << "--ATENTIE! LIVRAREA CU ID-UL SELECTAT VA FI DE ASEMENEA STEARSA--\n\nDoriti sa continuati?	( 1->DA / 0->NU )\n\n";
					std::cin >> x;
					if (x)
					{
						Livrare* IlStergL = pL->urm;
						pL->urm = pL->urm->urm;
						IlStergL->urm = NULL;
						delete IlStergL;//stergerea efectiva

						Livrare* p2L = pL->urm;
						while (p2L != NULL)
						{
							p2L->idCmd--;
							p2L = p2L->urm;
						}
					}
				}
			}

		if (x)//daca vreau sa continui, caut in lista de comenzi
		{
			Comanda::contor--;//'contor' este folosit pentru atribuirea fiecarei 
							//comenzi un ID unic, astfel, la creerea unui nou obiect,
							//ID - ul este ++contor, asa ca la stergere trebuie actualizat si 'contor'
			if (cap != NULL && cap->id == id)//daca am gasit comanda cu ID - ul cautat si este prima
			{
				std::cout << "\n\n---VECHEA COMANDA CU ID-UL "
					<< id << "---\n\n";
				if (cap->valid)
				{
					std::cout << *cap;
				}
				else
				{
					std::cout << "Comanda numarul-> " << cap->id << " || " << "Pret total-> "
						<< cap->totalPlata
						<< " || " << "Contact-> " << cap->telefonClient << "  <-- STOC INSUFICIENT" << "\n" << "\n" << "\n";
				}

				std::cout << "-------------------------------------------------------------------\n\n";

				Comanda* IlSterg = cap;
				cap = cap->urm;
				IlSterg->urm = NULL;
				delete IlSterg;	//stergerea efectiva


				Comanda* p2 = cap;
				while (p2 != NULL)
				{
					p2->id--;//ACTUALIZEZ ID-urile 
					if (p2->id == id)
					{
						std::cout << "\n\n---NOUA COMANDA CU ID-UL "
							<< id << "---\n\n";
						if (p2->valid)//afisare diferita in functie de validate
						{
							std::cout << *p2;
							std::cout << "-------------------------------------------------------------------\n\n";

						}
						else
						{
							std::cout << "Comanda numarul-> " << p2->id << " || " << "Pret total-> "
								<< p2->totalPlata
								<< " || " << "Contact-> " << p2->telefonClient << "  <-- STOC INSUFICIENT" << "\n" << "\n" << "\n";
							std::cout << "-------------------------------------------------------------------\n\n";

						}
					}
					p2 = p2->urm;
				}
			}
			else//altfel caut in restul listei
				if (cap != NULL)//daca lista are obiecte
				{
					Comanda* p = cap;
					while (p->urm != NULL && p->urm->id != id)
					{
						p = p->urm;
					}
					if (p->urm != NULL)
					{
						std::cout << "\n\n---VECHEA COMANDA CU ID-UL "
							<< id << "---\n\n";
						if (p->urm->valid)
						{
							std::cout << *(p->urm);
						}
						else
						{
							std::cout << "Comanda numarul-> " << p->urm->id << " || " << "Pret total-> "
								<< p->urm->totalPlata
								<< " || " << "Contact-> " << p->urm->telefonClient << "  <-- STOC INSUFICIENT" << "\n" << "\n" << "\n";
						}

						std::cout << "-------------------------------------------------------------------\n\n";

						Comanda* IlSterg = p->urm;
						p->urm = p->urm->urm;
						IlSterg->urm = NULL;
						delete IlSterg;//stergerea efectiva



						Comanda* p2 = p->urm;
						while (p2 != NULL)
						{
							p2->id--;
							if (p2->id == id)
							{
								std::cout << "\n\n---NOUA COMANDA CU ID-UL "
									<< id << "---\n\n";
								if (p2->valid)
								{
									std::cout << *p2;
									std::cout << "-------------------------------------------------------------------\n\n";

								}
								else
								{
									std::cout << "Comanda numarul-> " << p2->id << " || " << "Pret total-> "
										<< p2->totalPlata
										<< " || " << "Contact-> " << p2->telefonClient << "  <-- STOC INSUFICIENT" << "\n" << "\n" << "\n";
									std::cout << "-------------------------------------------------------------------\n\n";

								}
							}
							p2 = p2->urm;
						}
					}
				}
			std::cout << "!!!BAZA DE DATE A FOST ACTUALIZATA CU SUCCES!!!\n\n";
		}
		else
			std::cout << "!!!ABANDON!!!\n\n";
	}

}

int main()
{
	std::cout << "--- EVIDENTA DATELOR INTR-O FLORARIE --- \n\n";

	Produs* prim = NULL;//primul obiect din clasa Produs

	Produs* nou1 = new Produs(prim, "Trandafir rosu", 13.99, 4, true);
	Produs* nou2 = new Produs(prim, "Lalea rosie", 10.99, 8, true);
	Produs* nou3 = new Produs(prim, "Ghiveci Lavanda", 27.99, 9, false);	//pointeri ai obiectelor 
	Produs* nou4 = new Produs(prim, "Ghiveci Orhidee", 49.99, 8, false);
	Produs* nou5 = new Produs(prim, "Ornament Floral", 40.50, 15, false);

	Produs nouNOUT1 = Produs(*nou1);
	Produs nouNOUT2= Produs(*nou2);
	Produs nouNOUT3 = Produs(*nou3);		// APELARE CONSTRUCTOR DE COPIERE
	Produs nouNOUT4 = Produs(*nou4);
	Produs nouNOUT5 = Produs(*nou5);

	Comanda* cap = NULL;//primul obiect din clasa Comanda

	Comanda* n1 = new Comanda(cap, "0722 650 037", nou1, 2, "Strada Copacului nr. 22");
	Comanda* n2 = new Comanda(cap, "0744 435 678", nou1, 1, "Strada Ariciului nr. 123");
	Comanda* n3 = new Comanda(cap, "0723 456 123", nou2, 4, "Strada Copacului nr. 123");	//pointeri ai obiectelor 
	Comanda* n4 = new Comanda(cap, "0789 069 078", nou5, 10, "Strada Pitpalac nr. 42");
	Comanda* n5 = new Comanda(cap, "0712 068 078", nou3, 2, "Strada Pitigoi nr. 1");

	Livrare* vf = NULL;//primul obiect din clasa Livrare

	Livrare* l1 = new Livrare(vf, cap, 2, true);
	Livrare* l2 = new Livrare(vf, cap, 1);
	Livrare* l3 = new Livrare(vf, cap, 3);				//pointeri ai obiectelor 
	Livrare* l4 = new Livrare(vf, cap, 4, true);
	Livrare* l5 = new Livrare(vf, cap, 5, true);


	int ok;//il folosesc ca sa citesc optiunea de la tastatura

	std::cout << "Apasati tasta :\n" << "0 -> EXIT\n" << "1 -> MENIU PRODUS\n"
		<< "2 -> MENIU COMANDA\n" << "3 -> MENIU LIVRARE\n\n\n";

	std::cin >> ok;

	while (ok)
	{
		switch (ok) {
		case 0: 
			ok = 0;
			break;
		case 1:
			std::cout << "----------------------------------------------------------------------------------------------------------------\n\n";
			std::cout << "------MENIU PRODUS-----\n\n";
			std::cout << "Apasati tasta :\n" << "0 -> BACK\n" << "1 -> AFISARE DATE PRODUSE\n"
				<< "2 -> AFISARE PRODUSE PERISABILE\n" << "3 -> RESTOC\n\n\n";
			int m1; //m1 este notatie pentru meniul 1
			std::cin >> m1;//il folosesc ca sa citesc optiunea de la tastatura
			while (m1)
			{
				switch (m1) {

				case 0:
					m1 = 0;
					break;
				case 1:
					std::cout << "<-----------------------------\n";
					prim->afisare();
					std::cout << "\n";
					std::cout << "<-----------------------------\n";
					break;
				case 2:
					std::cout << "<-----------------------------\n";
					prim->afisare_perisabile();
					std::cout << "\n";
					std::cout << "<-----------------------------\n";
					break;
				case 3:
					std::cout << "<-----------------------------\n";
					std::cout << "OPTIUNI:\n->introduceti 0 pentru BACK;";
					std::cout << "\n->introduceti " << Produs::index+1 << " pentru a se face restoc la toate produsele;";//Daca vreau sa resetez toate stocurile, introduc numarul maxim de produse + 1
					std::cout << "\n->introduceti numarul unui produs(pentru restoc);\n\n";
					
					std::cout << "--- VARIANTE PRODUSE ---\n\n";
					prim->afisare(1);
					int varianta;//va fi una din variantele alese
					std::cin >> varianta;
					if (varianta != 0)
					{
						//Setez stocul tuturor produselor la valoarea maxim posibila (cea initiala) in acelasi timp
						if (varianta == Produs::index + 1)
						{
							nou1->restoc(nouNOUT1);
							nou2->restoc(nouNOUT2);
							nou3->restoc(nouNOUT3);
							nou4->restoc(nouNOUT4);
							nou5->restoc(nouNOUT5);
						}
						else//Altfel setez stocul tuturor produselor la valoarea maxim posibila (cea initiala) selectiv
						{
							switch (varianta) {
							case 1:
								nou1->restoc(nouNOUT1);
								break;
							case 2:
								nou2->restoc(nouNOUT2);
								break;
							case 3:
								nou3->restoc(nouNOUT3);
								break;
							case 4:
								nou4->restoc(nouNOUT4);
								break;
							case 5:
								nou5->restoc(nouNOUT5);
								break;
							}

						}
						std::cout << "------ ACTUALIZARE COMPLETA -----\n\n";
						prim->afisare();
					}

					std::cout << "------ BACK -----\n";

					std::cout << "<-----------------------------\n";
					break;
				}
				std::cout << "Apasati tasta :\n" << "0 -> BACK\n" << "1 -> AFISARE DATE PRODUSE\n"
					<< "2 -> AFISARE PRODUSE PERISABILE\n" << "3 -> RESTOC\n\n\n";
				std::cin >> m1;
			}
			std::cout << "----------------------------------------------------------------------------------------------------------------\n\n";
			break;

		case 2:
			std::cout << "----------------------------------------------------------------------------------------------------------------\n\n";
			std::cout << "------MENIU COMANDA-----\n\n";
			std::cout << "Apasati tasta :\n" << "0 -> BACK\n" << "1 -> AFISARE COMANDA\n"
				<< "2 -> STERGE COMANDA\n" << "3 -> ADAUGA COMANDA\n\n\n";
			int m2;//m1 este notatie pentru meniul 2
			std::cin >> m2;//il folosesc ca sa citesc optiunea de la tastatura
			while (m2)
			{
				switch (m2) {

				case 0:
					m2 = 0;
					break;
				case 1:
					std::cout << "<-----------------------------\n";
					cap->afisare();
					std::cout << "\n";
					std::cout << "<-----------------------------\n";
					break;
				case 2:
					std::cout << "<-----------------------------\n";
					int k;//Va retine ID - ul comenzii destinate stergerii
					std::cout << "Introduceti ID-ul comenzii: ";
					std::cin >> k;
					std::cout << "\n";
					std::cout << "\n";
					strgLivrareComanda(cap, vf, k);
					std::cout << "\n";
					cap->afisare();//Afisez lista actualizata
					std::cout << "\n";
					std::cout << "<-----------------------------\n";
					break;
				case 3:
					std::cout << "<-----------------------------\n\n";

					int numar;//numarul de bucati

					char numePrd[256], NrTele[256], ad[256];
					//->numePrd este numele produsului
					//->NrTele este numarul de telefon
					//->ad este adresa (de livrare)

					std::cout << "\n\n";
					prim->afisare(1);
					std::cout << "\n";

					std::cout << "	-> Numele produsului: ";
					std::cin.get();
					std::cin.get(numePrd, 256);

					std::cout << "	-> Numarul de telefon in formatul `07XX XXX XXX` : ";
					std::cin.get();
					std::cin.get(NrTele, 256);

					std::cout << "	-> Adresa dvs. : ";
					std::cin.get();
					std::cin.get(ad, 256);

					std::cout << "	-> Numarul de bucati: ";

					std::cin >> numar;

					std::cout << "\n";
					while (prim->getByDen(numePrd) == NULL)//cat timp numele introdus nu este gasit in clasa Produse, este solicitata reintroducerea
					{
						std::cout << "Reintroduceti unul din produsele: \n\n";
						prim->afisare();
						std::cin.get();
						std::cin.get(numePrd, 256);

					}
					std::cout << "\n";
					Comanda* noua = new Comanda(cap, NrTele, prim->getByDen(numePrd), numar, ad);
					if(noua->getValid())//Daca comanda este valida, ii este creata si o livrare, altfel nu
					Livrare* nouaL= new Livrare(vf, cap, noua->getId());
					std::cout << "-----------LISTA A FOST ACTUALIZATA CU SUSCCES-------------\n\n";
					cap->afisare();
					std::cout << "\n";
					std::cout << "<-----------------------------\n";
					break;
				}
				std::cout << "Apasati tasta :\n" << "0 -> BACK\n" << "1 -> AFISARE COMANDA\n"
					<< "2 -> STERGE COMANDA\n" << "3 -> ADAUGA COMANDA\n\n\n";
				std::cin >> m2;


			}
			std::cout << "----------------------------------------------------------------------------------------------------------------\n\n";
			break;
		case 3:
			std::cout << "----------------------------------------------------------------------------------------------------------------\n\n";
			std::cout << "------MENIU LIVRARE-----\n\n";
			std::cout << "Apasati tasta :\n" << "0 -> BACK\n" << "1 -> AFISARE DATE LIVRARE\n"
				<< "2 -> MODIFICA STAREA UNEI LIVRARI\n\n\n";
			int m3;//m1 este notatie pentru meniul 3
			std::cin >> m3;//il folosesc ca sa citesc optiunea de la tastatura
			while (m3)
			{
				switch (m3) {

				case 0:
					m3 = 0;
					break;
				case 1:
					std::cout << "<-----------------------------\n";
					vf->afisare();
					std::cout << "\n";
					std::cout << "<-----------------------------\n";
					break;
				case 2:
					std::cout << "<-----------------------------\n\n";
					std::cout << "Introduceti ID-ul livrarii careia ii va fi schimbata starea sau 0 pentru a renunta: ";
					int x;
					std::cin >> x;
					std::cout << "\n";

					while (x!=0 && vf->getLivrare(vf, x) == NULL)
					{
						std::cout << "-- ID INVALID --\n\n";
						std::cout << "Reintroduceti: \na) Un ID valid;\nb) 0 (cancel)\n";
						std::cin >> x;
						std::cout << "\n";
					}
					if(x!=0)
					{
						vf->getLivrare(vf, x)->setLivrare();
						std::cout << "\n";
					}
					else {
						std::cout << "---- RENUNTARE ----\n\n";
					}
					std::cout << "<-----------------------------\n";
					break;
				}
				std::cout << "Apasati tasta :\n" << "0 -> BACK\n" << "1 -> AFISARE DATE LIVRARE\n"
					<< "2 -> MODIFICA STAREA UNEI LIVRARI\n\n\n";
				std::cin >> m3;
			}
			std::cout << "----------------------------------------------------------------------------------------------------------------\n\n";
			break;
		}
		std::cout << "Apasati tasta :\n" << "0 -> EXIT\n" << "1 -> MENIU PRODUS\n"
			<< "2 -> MENIU COMANDA\n" << "3 -> MENIU LIVRARE\n\n\n";
		std::cin >> ok;
	}
	std::cout << "----- LA REVEDERE -----" << "\n";
	
	delete prim;
	delete cap;			//TOATE CELE 3 DELETE-URI PRODUC APELAREA RECURSIVA A DESTRUCTORILOR !!
	delete vf;

	

	return 0;
}
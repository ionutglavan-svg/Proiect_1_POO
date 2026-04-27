Am definit clasele "Produs", "Comanda", "Livrare". 


		->Un obiect din clasa "Produs" are urmatoarele campuri :
			-denumire(un pointer de tip char ce retine denumirea produsului);
			-pret(retine pretul produsului);
			-stoc(retine numarul de bucati al fiecarui produs);
			-perisabil(o variabila bool - eana ce indica daca un produs este perisabil sau nu);
			-urm(un pointer spre urmatorul obiect de tip "Produs");
			
		->Un obiect din clasa "Comanda" are urmatoarele campuri :
			-telefonClient(un pointer de tip char ce retine adresa unui sir de caractere ce reprezinta numarul de telefon al clientului);
			-totalPlata(retine pretul total al comenzii in functie de cantitate/pret);
			-nrProduse(retine numarul de bucati comandat);
			-id(retine ID - ul comenzii);
			-valid(initializat implicit cu true, indica daca numarul de bucati solicitat este disponibil sau nu);
			-adresa(un pointer de tip char ce retine adresa unui sir de caractere ce reprezinta adresa in care se va livra comanda);
			-urm(un pointer spre urmatorul obiect de tip "Comanda");
			
		->Un obiect din clasa "Livrare" are urmatoarele campuri :
			-cmdAsociata(un pointer de tip Comanda ce retine adresa unui obiect reprezinta comanda asociata livrarii din baza de date);
			-idCmd(retine ID - ul comenzii ce coincide cu ID - ul livrarii);
			-livrat(initializat implicit cu false, indica daca livrarea a fost efectuata sau nu);
			-urm(un pointer spre urmatorul obiect de tip "Livrare");
# 									!!!_strupr() trebuie inlocuit cu strupr() pentru CodeBlocks!!!

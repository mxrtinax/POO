# POO
   Sa se realizeze o aplicatie C++ de evidenta a articolelor (carti si CD –uri) dintr-o
biblioteca studenteasca. Orice articol existent in biblioteca contine o cota si numarul de
exemplare existent in biblioteca. Cota articolelor din biblioteca foloseste la cautarea si
imprumutarea acestora catre studenti. Fiecare carte are un titlu, iar fiecare revista este emisa
intr-o anumita luna.
Sa se implementeze clasele necesare pentru gestionarea imprumuturilor din biblioteca si
afisarea situatiei exitente la un moment dat. Un exemplu de test pentru functia main este :
main () {
try {
CBiblioteca B;
CArticol *C1 = new CCarte (1000, 10, “Programare in C++”);
CArticol *C2 = new CCarte (1001, 15, “Programare in Java”);
CArticol *C3 = new CCD (1002, 8, “Documentatie electronica C++”);
CArticol *C4 = new CCD (1003, 8, “Documentatie electronica Java”);
CArticol *C5 = new CCD (1004, 8, “Documentatie electronica Retele”);
B.addArticol (C1); B.addArticol (C2); B.addArticol (C3);
B.printArticole ( ); // afiseaza articolele existente, tipul acestora (carte sau cd) si numarul
de bucati existente in acest moment
B.addArticol (C4); B.addArticol (C5);
B.imprumutaArticol (1001); B.printArticole ( ); B.imprumutaArticol (1002);
B.printArticole ( );
B.restituieArticol(1001); B.printArticole ( );
} catch (CException *e)
{
e->printErrMessage();
delete e;
}
}

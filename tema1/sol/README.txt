	Am facut variabile globale, cum am lucrat in toate laboratoarele de C 
de la APD, pentru fiecare (pentru a le putea initializa in main si sa le 
folosesc in functia pentru thread-uri), iar par_julia si par_mandelbrot 
le-am facut pointeri pentru a nu mai modifica functiile date in schelet,
deoarece acolo nu se initializau ca pointeri, dar in functii se trimite 
adresa lor.

	In main apelez functia de init_params(), care, imi aloca memorie pentru
atat pentru structura algoritmului julia, cat si pentru cea a algoritmului
Mandelbrot si verifica daca initializarea acestora a avut succes. Tot aici,
apelez functia de citirea din fisier si calculez pentru cei doi algoritmi 
inaltimea si latimea matricii si apelez functia de alocare de memorie
pentru matricile rezultate ale celor doi algoritmului. Tot in main, 
initializez bariera, thread-urile si variabilele necesare si 
apoi cu un for parcurg thread-urile si apelez functia de create
si in urmatorul cea de join.
	
	In functia thread-urilor, initializez o variabila pentru a retine
id-ul fiecarui thread, start-ul si end-ul, variabile "specifice" 
fiecarui thread. Apelez functia pe care, de fapt fiecare thread
o va apela si calculeaza fiecare portiune din matrice. Apoi apelez
functia de wait de la bariera ca fiecare thread sa astepte rezultatul
celorlalte thread-uri. Thread-ul "main", asa cum l-am numit la curs
imi va face scrierea in fisier cu functia data in schelet de scriere 
in fisier. Apoi urmez aceeasi pasi si pentru algoritmul Mandelbrot.

	Functia compute_julia_result, are ca parametru start-ul si end-ul
care vor diferi in functie de ce thread o apeleaza. Aplic algoritmul
din schelet cu o mica modificare si anume: renunt la ultimul for
care trecea matricea din coordonate matematice in coordonate
ecran si fac aceasta operatie direct in momentul in care
calculez matricea rezultata. Aceasta face acelasi lucru ca si for-ul
eliminat si anume imi intoarce matricea, adica prima linie devine ultima
si tot asa. Functia compute_mandelbrot_result, are aceleasi modificari si
functioneaza la fel, doar algoritmul este diferit
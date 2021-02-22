	Am creat clasa Producer ce reprezinta producatorii,
i-am atribuit un buffer, id si string-ul pe care trebuie
sa il puna in buffer.
	Am creat clasa Consumer, ce reprezinta consumatorii, care
au campurile buffer-ul, id-ul si un counter cu ajutorul caruia
voi retine daca un thread a citit deja mesajul.
	Am creat clasa Buffer care va retine intr-un limitedQueue mesajele
scrise.
	Incerc sa aplic metoda de la laboratorul 5 in care thread-urile
producator vor scrie mesaje pana cand limitedQueue este plin, apoi
thread-urile consumator vor incepe sa citeasca mesajele, apoi
operatia se va repeta. Acest lucru il voi face cu ajutorul unor
semafoare, un semafor pentru Producatori, iar altul pentru Consumatori.


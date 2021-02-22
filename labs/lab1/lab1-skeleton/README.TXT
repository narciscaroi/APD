task1-> Am modificat num_thread. Am tot incrementat numarul pana cand am
		depasit numarul thread-urilor pe care le suporta. La depasirea
		acestui numar, output-ul programului nu s-a mai modificat.
		
task3-> Nu se afiseaza in ordinea asteptata de mine. Executia se afiseaza
		probabil in functie de cum s-a terminat procesul, thread-urile
		"lucrand" in paralel.
		
task6-> Am rulat programul de la task5 cu urmatorul argument: 100000000000
		Diferentele:
			num_thread = 1 ->real    0m5.683s 
			num_thread = 2 ->real    0m4.974s 
			num_thread = 4 ->real    0m4.917s
			num_thread = 6 ->real    0m4.024s  
			num_thread = 8 ->real    0m3.980s
			num_thread = 12->real    0m3.971s 
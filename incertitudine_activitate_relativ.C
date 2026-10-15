// Script de calcul a incertitudinii activitatii unei surse daca se stiu ariile nete
// ale etalonului si a ei si activitatea etalonului, fol. propagarea erorilor.
//
// ATENTIE: ariile nete trebuie sa fie pt. acelasi timp de masurare pt. ambele surse!!
// activitate_sursa = activitate_etalon * (arie_sursa / arie_etalon).
{
	double A_s, A_e, N_s, N_e;  // activitate sursa, etalon, arie neta sursa, arie neta etalon
	double uA_s, uA_e, uN_s, uN_e;  // incertitudinile


	// Activitate etalon (inc. este pt. k=2):
	A_e = 2014.59;
	uA_e = 60.41;
	uA_e = uA_e/2;  // k=1
	// Arie neta peak etalon (inc. sunt pt. k=1 la arie neta):
	N_e = 42.87;
	uN_e = 0.28;
	// Arie neta peak sursa beneficiar (inc. sunt pt. k=1 la arie neta):
	N_s = 0.1934;
	uN_s = 0.0017;


	A_s = A_e * (N_s / N_e);
	uA_s = A_s * sqrt(pow(uA_e/A_e,2) + pow(uN_s/N_s,2) + pow(uN_e/N_e,2)); // toate pt. k=1
	uA_s = 2*uA_s;  // k=2

	cout << "\nActivitate sursa beneficiar:" << endl;
	cout << "  " << A_s << " +/- " << uA_s << "  [Bq]" << endl << endl;
}

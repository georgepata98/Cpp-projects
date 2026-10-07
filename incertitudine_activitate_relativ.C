// Script de calcul a incertitudinii activitatii unei surse daca se stiu ariile nete
// ale etalonului si a ei si activitatea etalonului, fol. propagarea erorilor.
//
// ATENTIE: ambele surse trebuie masurate pe acelasi interval de timp!!!
// activitate_sursa = activitate_etalon * (arie_sursa / arie_etalon).
{
	double A_s, A_e, N_s, N_e;  // activitate sursa, etalon, arie neta sursa, arie neta etalon
	double uA_s, uA_e, uN_s, uN_e;  // incertitudinile

	// Activitate etalon:
	A_e = 91.44;
	uA_e = 4.18;
	// Arie neta peak etalon:
	N_e = 18262;
	uN_e = 142;
	// Arie neta peak sursa beneficiar:
	N_s = 6376;
	uN_s = 83;

	A_s = A_e * (N_s / N_e);
	uA_s = A_s * sqrt(pow(uA_e/A_e,2) + pow(uN_s/N_s,2) + pow(uN_e/N_e,2));

	cout << "\nActivitate sursa beneficiar:" << endl;
	cout << "  " << A_s << " +/- " << uA_s << "  [Bq]" << endl << endl;
}

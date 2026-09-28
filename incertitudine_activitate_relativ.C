// Script de calcul a incertitudinii activitatii unei surse daca se stiu ariile nete
// ale etalonului si a ei si activitatea etalonului, fol. propagarea erorilor.
//
// activitate_sursa = activitate_etalon * (arie_sursa / arie_etalon).
{
	double A_s, A_e, N_s, N_e;  // activitate sursa, etalon, arie neta sursa, arie neta etalon
	double uA_s, uA_e, uN_s, uN_e;  // incertitudinile

	// Activitate etalon:
	A_e = 5000;
	uA_e = 100;
	// Arie neta peak etalon:
	N_e = 10000;
	uN_e = 230;
	// Arie neta peak sursa beneficiar:
	N_s = 12000;
	uN_s = 300;

	A_s = A_e * (N_s / N_e);
	uA_s = A_s * sqrt(pow(uA_e/A_e,2) + pow(uN_s/N_s,2) + pow(uN_e/N_e,2));

	cout << "\nActivitate sursa beneficiar:" << endl;
	cout << "A = " << A_s << " +/- " << uA_s << "  [Bq], k=2" << endl << endl;
}
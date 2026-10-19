// Calculator activitate si incertitudine activitate sursa gama, data de formula:
// A = N / (t * I * epsilon)
#include <cmath>
#include <iostream>
using namespace std;

int main()
{
  double N;  // aria
  double sigma_N, sigma_t, I, sigma_I, epsilon, sigma_epsilon, t; // I=intensitatea de emisie a gamei, epsilon=eficacitatea de detectie, t=timp achizitie

  cout << "\nTOATE INCERTITUDINILE SI REZULTATUL FINAL SUNT PT. k=1 !!!\n";

  cout << "\n1. Aria picului: " << endl;
  cout << "   N = "; cin >> N;
  cout << "   sigma_N = "; cin >> sigma_N;
  cout << endl;

  cout << "2. Timpul de achizitie, in [s]: " << endl;
  cout << "   t = "; cin >> t;
  cout << "   sigma_t = "; cin >> sigma_t;
  cout << endl;

  cout << "3. Intensitatea de emisie, normata la 1: " << endl;
  cout << "   I = "; cin >> I;
  cout << "   sigma_I = "; cin >> sigma_I;
  cout << endl;

  cout << "4. Eficacitatea de detectie, normata la 1: " << endl;
  cout << "   epsilon = "; cin >> epsilon;
  cout << "   sigma_epsilon = "; cin >> sigma_epsilon;
  cout << endl;

  // Calcul activitate si incertitudine asociata cu propagarea erorilor

  double arie = (sigma_N * sigma_N) / (t * t * I * I * epsilon * epsilon);
  double intensitate = (N * N * sigma_I * sigma_I) / (t * t * pow(I, 4) * epsilon * epsilon);
  double eficacitate = (N * N * sigma_epsilon * sigma_epsilon) / (t * t * I * I * pow(epsilon, 4));
  double timp = (N * N * sigma_t * sigma_t) / (pow(t, 4) * I * I * epsilon * epsilon);

  double sigma_A = sqrt(arie + intensitate + eficacitate + timp);
  double A = N / (t * I * epsilon);

  cout << "******** Rezultat final *********" << endl << endl;
  cout << "Activitatea = " << A << " [Bq]" << endl;
  cout << "Incertitudinea = +/- " << sigma_A << " [Bq] pt. k=1" << endl << endl;
  cout << "*********************************" << endl;

  return 0;
}

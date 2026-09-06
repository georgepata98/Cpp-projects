// Plotare activitate in functie de timp
{
int opt, nbins = 256;
string opt2;
double A0, A, halft, t;


// =============== DECLARAREA VARIABILELOR ===============

cout << "\nUnitatea in care se exprima T1/2:\n";
cout << "1. secunde\n2. zile\n3. ani\nAlegeti: ";
cin >> opt;

while (opt != 1 && opt != 2 && opt != 3)
{
    cout << "Alegeti dintre 1, 2 sau 3: "; cin >> opt;
}
if (opt == 1) opt2 = "secunde";
if (opt == 2) opt2 = "zile";
if (opt == 3) opt2 = "ani";

cout << "\nPeste cat timp de la timpul 0 doriti activitatea calculata?\n";
cout << "Timpul trebuie precizat in " << opt2 << " fata de timpul 0: ";
cin >> t;
while (t < 0)
{
    cout << "Selectati un timp mai mare de 0: "; cin >> t;
}

cout << "T1/2 al radionuclidului ales, in " << opt2 << ": ";
cin >> halft;
while (halft < 0)
{
    cout << "Selectati un T1/2 mai mare de 0: "; cin >> halft;
}

cout << "Activitatea la timpul 0: ";
cin >> A0;
while (A0 < 0)
{
    cout << "Selectati o activitate mai mare de 0: "; cin >> A0;
}

// =======================================================


A = A0 * exp((-log(2) * t) / halft);
cout << "\n   Activitatea dupa " << t << " " << opt2 << ": " << A << endl;

TH1D *h1 = new TH1D("h1", "hist", nbins, 0, 1.05 * t);

double dt = (1.05 * t - 0) / nbins;  // grosime bin
double aux_t = 0;

for (int i = 0; i < nbins; i++)
{
    double y = A0 * exp((-log(2) * aux_t) / halft);
    aux_t = i * dt + 0.5 * dt;

    h1->SetBinContent(i + 1, y);  // in ROOT, binurile sunt numerotate de la 1 nu de la 0
}


TCanvas *c1 = new TCanvas("c1", "canvas", 900, 550);
if (opt == 1) h1->GetXaxis()->SetTitle("Timp [sec.]");
if (opt == 2) h1->GetXaxis()->SetTitle("Timp [zile]");
if (opt == 3) h1->GetXaxis()->SetTitle("Timp [ani]");
h1->GetYaxis()->SetTitle("Activitate");
h1->SetTitle("Activitatea de la t=0 la timpul dorit");
h1->Draw("hist");
}

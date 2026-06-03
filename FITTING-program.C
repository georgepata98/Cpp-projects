// Fisierul de date trebuie sa aiba 3 coloane: x, Y si incertitudinea lui Y
// Mai jos, in program, se modifica functia de fit (vezi documentatia ROOT)
{
ifstream file;
string fName;

cout << "\nNumele complet al fisierului text cu date (ex: data.txt):" << endl;
cin >> fName;

file.open(fName);
if(!file)
{
	cout << "\nNu s-a putut deschide fisierul " << fName << " ..." << endl;
	exit(0);
}

TGraphErrors *gr1 = new TGraphErrors();
double x, Y, u_Y, st, dr, x_min, x_max;
int i = 0;
while(!file.eof())
{
	file >> x >> Y >> u_Y;
	gr1->SetPoint(i, x, Y);
	gr1->SetPointError(i, 0, u_Y);  // de folosit daca incertitudinea este in aceleasi unitati ca Y
	// gr1->SetPointError(i, 0, u_Y * Y);  // de folosit daca incertitudinea este in procente
	if(i==0) { x_min = x; }
	x_max = x;
	i++;
}
file.close();
cout << "\nMarginile x_min si x_max din grafic:" << endl;
cout << "  x_min = " << x_min << endl;
cout << "  x_max = " << x_max << endl;
cout << "\nIntroduceti intervalul de fitare:" << endl;
cout << "- capat stang: "; cin >> st;
cout << "- capat drept: "; cin >> dr;


// Aici se modifica functia de fitare:
TF1 *f1 = new TF1("f1", "pol1", st, dr);  // pol1 = p0 + p1 * x



TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
c1->SetGrid();
gr1->GetXaxis()->SetTitle("x");
gr1->GetYaxis()->SetTitle("Y(x)");
gr1->SetMarkerStyle(20);
gr1->Fit("f1", "R");
gr1->Draw("AP");
}

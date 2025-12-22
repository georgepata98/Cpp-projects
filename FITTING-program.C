// Program care fiteaza datele cu diferite functii de fit
{
ifstream file;
string fName;

// Scrie aici numele fisierului text care contine datele:
// (trebuie sa aiba 3 coloane, x, Y si incertitudinea in Y)
fName = "kl_PTB_neutroni.txt";
// PS: mai jos in program se modifica functia de fitare.


file.open(fName);
if(!file)
{
	cout << "\nNu s-a putut deschide fisierul "<< fName << endl;
	return;
}

TGraphErrors *gr1 = new TGraphErrors();

double x, Y, u_Y, st, dr, x_min, x_max;
int i=0;

while(1)
{
	file >> x >> Y >> u_Y;

	if(file.eof()) break;
	gr1->SetPoint(i, x, Y);
	gr1->SetPointError(i, 0, u_Y);

	if(i==0) x_min = x;
	x_max = x;
	i++;
}
file.close();

cout << "\nCapetele x_min si x_max din fisierul de date:\n";
cout << "  x_min = " << x_min << endl;
cout << "  x_max = " << x_max << endl;
cout << "\nScrieti capetele de fitare:\n";
cout << "-capatul stanga: "; cin >> st;
cout << "-capatul dreapta: "; cin >> dr;


// Aici se modifica functia de fitare:
TF1 *f1 = new TF1("f1", "pol1", st, dr);  // pol1 = p0 + p1 * x



cout << "\nDoriti sa vedeti graficul? (da/nu): "; cin >> fName;
if(fName == "da" || fName == "yes" || fName == "y" || fName == "d")
{
	// Plotare
	TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
	c1->SetGrid();
	gr1->GetXaxis()->SetTitle("x");
	gr1->GetYaxis()->SetTitle("Y(x)");
	gr1->SetMarkerStyle(20);
	gr1->Fit("f1", "R");
	gr1->Draw("AP");
}
else
{
	gr1->Fit("f1", "R");  // printare doar informatiile de fit (valorile constantelor functiei de fit)
}
}

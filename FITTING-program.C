// Program care fiteaza datele cu diferite functii de fit
{
TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
TGraphErrors *gr1 = new TGraphErrors();
ifstream file;

double x, Y, u_Y, st, dr, x_min, x_max;
int i=0;
string fName;


// Scrie aici numele fisierului text care contine datele:
// (trebuie sa aiba 3 coloane, x, Y si incertitudinea in Y)
// PS: mai jos in program se modifica functia de fitare.
fName = "kl_PTB_neutroni.txt";


file.open(fName);
if(!file)
{
	cout << "\nNu s-a deschis fisierul "<< fName << endl;
	return;
}
while(1)
{
	file >> x >> Y >> u_Y;

	if(file.eof()) break;
	gr1->SetPoint(i, x, Y);
	gr1->SetPointError(i, 0, u_Y);
	if(i == 0) x_min = x;
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
TF1 *f1 = new TF1("f1", "pol1", st, dr);  // f1 = p0 + p1 * x


// Plotare
c1->SetGrid();
gr1->GetXaxis()->SetTitle("x");
gr1->GetYaxis()->SetTitle("Y(x)");
gr1->SetMarkerStyle(20);
gr1->Fit("f1", "R");
gr1->Draw("AP");
}

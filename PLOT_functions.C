// Fisierul cu date trebuie sa aiba 2 coloane: prima col. x si a doua Y
{
ifstream file;
string fileName;

cout << "\nNumele complet al fisierului text cu date (ex: data.txt):" << endl;
cin >> fileName;

file.open(fileName);
if(!file)
{
    cout << "\nNu s-a putut deschide fisierul " << fileName << " ..." << endl;
    exit(0);
}

TGraph *gr1 = new TGraph();
double x, y;
int i = 0;
while(!file.eof())
{
    file >> x >> y;
    gr1->SetPoint(i, x, y);
    i++;
}
file.close();

TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
c1->SetGrid();
gr1->SetLineWidth(1);
gr1->SetMarkerStyle(20);
gr1->GetXaxis()->SetTitle("x");
gr1->GetYaxis()->SetTitle("Y(x)");
gr1->Draw("APL");
c1->Update();
}

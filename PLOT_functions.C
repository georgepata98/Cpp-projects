// Plotare Y(x) in ROOT
{
TGraph *gr1 = new TGraph();
ifstream file;
string filename;
double x, y;
int i = 0;


// Scrie mai jos numele fisierului de date (trebuie sa fie in acelasi folder cu acest cod):
filename = "AmBe_TRS403.txt";
// IMPORTANT: Fisierul cu date trebuie sa aiba 2 coloane (pe prima X si pe a doua Y).


file.open(filename);
while(1)
{
    file >> x >> y;
    if(file.eof()) break;
    gr1->SetPoint(i, x, y);
    i++;
}
file.close();

TCanvas *c1 = new TCanvas("c1", "canvas", 1000, 600);
c1->SetGrid();
gr1->SetLineWidth(1);
gr1->SetLineColor(kBlue);
gr1->SetMarkerColor(kBlue);
gr1->SetMarkerStyle(20);
gr1->GetXaxis()->SetTitle("x");
gr1->GetYaxis()->SetTitle("Y(x)");
gr1->Draw("APL");
c1->Update();
}

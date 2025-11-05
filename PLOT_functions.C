// Plotare f(x) in ROOT
{
    TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
    TGraph *gr1 = new TGraph();
    ifstream file;


    // ---> Scrie aici numele fisierului de date (trebuie sa fie in acelasi dir. cu acest cod):
    string filename = "AmBe_TRS403.txt";
    
  
    file.open(filename);
    double x, y;
    int i = 0;
    while(1)
    {
        file >> x >> y;
        if(file.eof()) break;
      
        gr1->SetPoint(i, x, y);
        i++;
    }
    file.close();


    c1->SetGrid();
    gr1->SetLineWidth(1);
    gr1->SetLineColor(kBlue);
    gr1->SetMarkerColor(kBlue);
    gr1->SetMarkerStyle(20);
    gr1->GetXaxis()->SetTitle("x");
    gr1->GetYaxis()->SetTitle("f(x)");
    gr1->Draw("APL");
    c1->Update();
}

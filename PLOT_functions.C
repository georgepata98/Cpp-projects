// Plotare f(x) in ROOT
{
    ifstream file;
    string fileName;

    // ---> Scrie aici numele fisierului de date:
    fileName = "AmBe_TRS403.txt";
    
  
    file.open(fileName);
    if(!file)
    {
        cout << "\nNu s-a putut deschide fisierul " << fileName << endl;
        return;
    }

    TCanvas *c1 = new TCanvas("c1", "canvas", 800, 600);
    TGraph *gr1 = new TGraph();

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
    gr1->Draw("AL");
    c1->Update();
}

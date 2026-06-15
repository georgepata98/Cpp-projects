// Programul se poate folosi pentru plotarea ca histograma a spectrelor rezultate din MCNP si se pot calcula si ariile picurilor.
// Fisierul cu date din MCNP trebuie sa aiba 3 coloane: Energie, Nr. count-uri,  incertitudine count-uri in %.
{
    fstream file;
    int nbins=0, i;
    double e0, e1, canal, pulsuri, eroare;
    string fName;


    cout << "\nProgramul se poate folosi pentru plotarea ca histograma a spectrelor rezultate din MCNP si se pot calcula si ariile picurilor ...\nFisierul cu date din MCNP trebuie sa aiba 3 coloane: Energie, Nr. count-uri,  incertitudine count-uri in %." << endl << endl;
    cout << "Nume fisier text cu date (fara .txt): "; cin >> fName;

    file.open((fName + ".txt").c_str(), ios::in);
    if(!file)
    {
        cout << "\nEROARE: Nu s-a putut deschide fisierul " << fName << ".txt !" << endl;
        exit(0);
    }

    while(!file.eof())
    {
        file >> canal >> pulsuri >> eroare;
        if(nbins==0) { e0 = canal; }
        e1 = canal;
        nbins++;
    }
    file.close();

    cout << "\nNr. de canale = " << nbins << endl;
    cout << "Capetele histogramei:" << endl;
    cout << " " << e0 * 1000 << " [keV]\n " << e1 * 1000 << " [keV]" << endl;

    TH1F *h1 = new TH1F("h1", "MCNP spectrum", nbins, e0, e1);
    file.open((fName + ".txt").c_str(), ios::in);
    while(!file.eof())
    {
        file >> canal >> pulsuri >> eroare;
        i = h1->FindBin(canal + (e1-e0)/nbins/2);
        h1->SetBinContent(i, pulsuri);
        h1->SetBinError(i, pulsuri*eroare);
    }
    file.close();


    cout << "\nSe calculeaza eficacitatea absoluta la fotopic? (da/nu): "; cin >> fName;
    if(fName=="da" || fName=="yes" || fName=="y" || fName=="d")
    {
        double e_st, e_dr, bin_width, bin_err, sum=0;
        int bin_st, bin_dr;

        bin_width = (e1 - e0) / nbins;
        cout << "Largime canal = " << bin_width * 1000 << " [keV]" << endl;
        cout << "\nIntervalul de energii pe care se integreaza, in keV:" << endl;
        cout << "E_stanga  = "; cin >> e_st;
        cout << "E_dreapta = "; cin >> e_dr;
        e_st = e_st / 1000;
        e_dr = e_dr / 1000;

        for(int k=1; k<=h1->GetNbinsX(); ++k)
        {
            if(e0+k*bin_width < e_st) bin_st = k+1;
            if(e0+k*bin_width == e_st) bin_st = k;
            if(e0+k*bin_width < e_dr) bin_dr = k+1;
            if(e0+k*bin_width == e_dr) bin_dr = k;
        }
        for(int k=1; k<=h1->GetNbinsX(); ++k)
        {
            if(k>=bin_st && k<=bin_dr)
            {
                bin_err = h1->GetBinError(k);
                sum += bin_err*bin_err;
            }
        }
        sum = TMath::Sqrt(sum);

        cout << "\nCanalele de integrare:";
        cout << "\n-> ch_stanga  = " << bin_st << "\n-> ch_dreapta = " << bin_dr << endl;
        cout << "\nEficacitate_detectie(delta_ch) = " << h1->Integral(bin_st, bin_dr) << " +/- " << sum << endl << endl;
    }


    TCanvas *c1 = new TCanvas("c1", "Canvas", 800, 600);
    
    h1->SetTitle("MCNP simulated spectrum");
    h1->GetXaxis()->SetTitle("Energy (MeV)");
    h1->GetYaxis()->SetTitle("Counts");
    h1->Draw("hsit");
    c1->Update();
}

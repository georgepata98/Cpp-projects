{
    fstream file;
    int nbins=0, i;
    double e0, e1, canal, pulsuri, eroare;
    string a;

    
    cout << "\nProgramul se poate folosi pentru plotarea ca histograma a spectrelor rezultate din MCNP si se pot calcula si ariile picurilor ...\nFisierul cu date din MCNP trebuie sa aiba 3 coloane: Energie, Nr. count-uri, % incertitudine count-uri." << endl << endl;
    cout << "Nume fisier text cu date (fara .txt): "; cin >> a;

    file.open((a + ".txt").c_str(), ios::in);
    if(!file)
    {
        cout << "\nEROARE: Nu s-a putut deschide fisierul " << a << ".txt !" << endl;
        return 1;
    }

    while(1)  // gasire capete histograma (e0 si e1) si numar de bini
    {
        file >> canal >> pulsuri >> eroare;
        if(file.eof()) break;
        canal *= 1000; // keV -> MeV
        if(nbins==0) { e0 = canal; }
        e1 = canal;
        nbins++;
    }
    file.close();

    cout << "\nNr. de canale = " << nbins << endl;
    cout << "Capetele histogramei:" << endl;
    cout << " " << e0 << " [keV]\n " << e1 << " [keV]" << endl;


    TH1F *h1 = new TH1F("h1", "MCNP spectrum", nbins, e0, e1);

    file.open((a + ".txt").c_str(), ios::in);
    while(1)
    {
        file >> canal >> pulsuri >> eroare;
        if(file.eof()) break;
        canal *= 1000;
        i = h1->FindBin(canal + (e1-e0)/nbins/2);  // setare centru bin i
        h1->SetBinContent(i, pulsuri);  // umplere binul i
        h1->SetBinError(i, pulsuri*eroare);  // eroare binul i
    }
    file.close();



    // Eficacitatea absoluta la fotopic

    cout << "\nSe calculeaza eficacitatea absoluta la fotopic? (da/nu): "; cin >> a;
    if(a=="da" || a=="yes" || a=="y" || a=="d")
    {
        double e_st, e_dr, bin_width, bin_err, sum=0;
        int bin_st, bin_dr;  // binul din stanga si dreapta al picului

        bin_width = (e1-e0)/nbins;
        cout << "Largime canal = " << bin_width << " [keV]" << endl;
        cout << "Intervalul de energii pe care se integreaza, in [keV]:" << endl;
        cout << "E_stanga  = "; cin >> e_st;
        cout << "E_dreapta = "; cin >> e_dr;


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

        cout << "\n=> ch_stanga = " << bin_st << "\n=> ch_dreapta = " << bin_dr;
        cout << "\nEficacitate_detectie(delta_ch) = " << h1->Integral(bin_st, bin_dr) << " +/- " << sum << endl;
    }



    // Reprezentare grafica

    TCanvas *c1 = new TCanvas("c1", "Canvas", 800, 600);

    h1->SetTitle("MCNP spectrum");
    h1->GetXaxis()->SetTitle("Energy [keV]");
    h1->GetYaxis()->SetTitle("Counts [arb. units]");
    h1->Draw("hsit");
    c1->Update();

    return 0;
}

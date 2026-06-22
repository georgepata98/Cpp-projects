// Exemplu program de la chatgpt care listeaza toate fisierele .ROOT dintr-un folder
#include <TFile.h>
#include <TList.h>
#include <TString.h>
#include <TSystem.h>
#include <TSystemDirectory.h>
#include <TSystemFile.h>
#include <iostream>

void rootlist()
{
  TString dir_path = "."; // Set to current directory
  TSystemDirectory dir(dir_path, dir_path);
  TList *files = dir.GetListOfFiles();

  if (!files) {
    std::cerr << "Error: No files found in directory!" << std::endl;
    return;
  }

  TIter next(files);
  TSystemFile *file;

  while ((file = (TSystemFile *)next())) {
    TString fileName = file->GetName();

    // Check if the file is a ROOT file
    if (!file->IsDirectory() && fileName.EndsWith(".root")) {
      std::cout << "Found ROOT file: " << fileName << std::endl;

      // Correctly format the path with a separator "/"
      TString filePath = Form("%s/%s", dir_path.Data(), fileName.Data());

      // Debugging: Print the full file path
      std::cout << "Opening file: " << filePath << std::endl;

      // Open the ROOT file
      TFile *rootFile = TFile::Open(filePath);
      if (!rootFile || rootFile->IsZombie()) {
        std::cerr << "Error: Could not open " << filePath << std::endl;
      } else {
        std::cout << "Successfully opened " << filePath << std::endl;
        rootFile->Close();
      }
    }
  }
}

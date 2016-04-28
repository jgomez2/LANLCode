#include <iomanip>
#include <string>
#include <cstdio>

string cutName (int doinc, int ppac, int ligl) {
  // arghh ROOT sucks - no snprintf
  //                    no right iomanip for strstream
  //                    can't tell if setf works
  // name.setf( ' ');
  // name << "cut_dc1_" << doinc << "_tdi3_t00"
  //      << "_ppac" << setw(2) << ppac
  //      << "_ligl" << setw(2) << ligl
  //      << ends;
  char name[128];
  sprintf( name, "cut_dc1_%d_tdi3_t00_ppac%02d_ligl%02d",
           doinc, ppac, ligl);
  return string (name);
}

void newPoly (const char* fileName) {

  TFile* file = TFile::Open( fileName, "update");
  
  for (int iPPAC=1; iPPAC<=10; ++iPPAC) {
    for (int iLigl=1; iLigl<=22; ++iLigl) {

      string oldName = cutName( 3, iPPAC, iLigl);
      TObject* o = file->FindObjectAny( oldName.c_str());
      if (!o) {
        cerr << "can't find " << oldName << endl;
        continue;
      }

      for (int iDoinc=6; iDoinc<=7; ++iDoinc) {
        string newName = cutName( iDoinc, iPPAC, iLigl);
        cout << "                 " << newName << endl;
        TObject* n = o->Clone( newName.c_str());
        n->Write();
      }
    }
  }

  file->Write();
  return;
}

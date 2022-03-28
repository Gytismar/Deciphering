#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

bool palyginti(pair<string, int>& a, pair<string, int>& b);
bool palyginti_char(pair<char, int>& a, pair<char, int>& b);

void rusiavimas(map<string, int>& M, vector<pair<string, int> >& A);

void rusiavimas_char(map<char, int>& M, vector<pair<char, int> >& A);

void idejimas(string s_text[], string ne_text[], bool &t, string &s_raides, string &ne_raides,int kiekis ,string is, string ika);

char rasti (char ro,string ne_raides, string s_raides)
{
  char temp;
  for (int i = 0; i < ne_raides.size(); i++)
  {
    if (ne_raides[i] == ro)
    {
      temp = s_raides[i];
      i = ne_raides.size();
    }
  }
  return temp;
}

int main()
{
  bool ar_paejo;
  
  ifstream input ("uzsifruotastekstas.txt");

  map<char,int>raides;  //pavienes raides
  map<string,int>dviraides; //po dvi raides
  map<string,int>triraides; // po tris raides

  map <string,int>dvigubi;//dvi tos pacios raides

  map<char,int>pirma;// pirmos raides
  map<char,int>pask;// paskutines raides
  map<string,int>pir_pas; //pirma ir paskutine raide

  map <char,   int>pavieni; // vienos raides zodziai
  map <string, int>dvivieni; // dvieju raidziu zodziai
  map <string, int>trivieni; // triju raidziu zodziai
  map <string, int>keturvieni; // keturiu raidziu zodziai

  string temp;
  string temp2;

  string ne_text[25000];
  string s_text[25000];
  int kiekis = 0;

  while (!input.eof())
  {
    input >> temp;

    s_text [kiekis] = temp;
    ne_text[kiekis] = s_text[kiekis];
    kiekis++;

    for (int i = 0; i < temp.size(); i++) //ivedu po raide
    {
      raides[temp[i]]++;
    }

    if (temp.size() >= 2)
    {
      for (int i = 0; i < temp.size()-1; i++)//ivedu po dvi raides
      {
        temp2 = "";
        temp2 = temp2 + temp[i] + temp[i+1];
        dviraides[temp2]++;

        if (temp2[0] == temp2[1])
        {
          dvigubi[temp2]++;
        }
      }
    }

    if (temp.size() >= 3)
    {
      for (int i = 0; i < temp.size()-2; i++)//ivedu po dvi raides
     {
        temp2 = "";
        temp2 = temp2 + temp[i] + temp[i+1] + temp[i+2];
        triraides[temp2]++;
      }
    }

    pirma[temp[0]]++; // pirmos raides
    pask[temp[temp.size()-1]]++; // paskutines raides
    
    temp2 = "";
    temp2 = temp2 + temp[0] + temp[temp.size()-1];
    pir_pas[temp2]++; //pirma ir paskutine

    if (temp.size() == 1)
      pavieni[temp[0]]++;
    else if (temp.size() == 2)
    {
      temp2 = "";
      temp2 = temp2 + temp[0] + temp[1];
      dvivieni[temp2]++;
    }
    else if (temp.size() == 3)
    {
      temp2 = "";
      temp2 = temp2 + temp[0] + temp[1] + temp[2];
      trivieni[temp2]++;
    }
    else if (temp.size() == 4)
    {
      temp2 = "";
      temp2 = temp2 + temp[0] + temp[1] + temp[2] + temp[3];
      keturvieni[temp2]++;
    }

    
  }

  for (int i = 0; i < kiekis; i++)
  {
    for (int b = 0; b < ne_text[i].size(); b++)
    {
      ne_text[i][b] = '-';
    }
  }


  vector<pair<char, int> > vienos; // vienos raides
  rusiavimas_char(pavieni,vienos);

  vector<pair<string, int> > dvienos; // po dvi raides
  rusiavimas(dviraides,dvienos);

  vector<pair<string, int> > tvienos; // trys raides
  rusiavimas(triraides,tvienos);

  vector<pair<string, int> > dvigub; // dvigubos pasikartojancios
  rusiavimas(dvigubi,dvigub);

  vector<pair<char, int> > pirmi; // pirmos raides
  rusiavimas_char(pirma,pirmi);
  
  vector<pair<char, int> > pasku; // paskutines raides
  rusiavimas_char(pask,pasku);

  vector<pair<string, int> > pir_pask; // pirma ir paskutine zodyje
  rusiavimas(pir_pas,pir_pask);

  vector<pair<char, int> > vieni; // vienos raides zodziai
  rusiavimas_char(pavieni,vieni);

  vector<pair<string, int> > dvieni; // dvieju r zodziai
  rusiavimas(dvivieni,dvieni);

  vector<pair<string, int> > tvieni; // triju r zodziai
  rusiavimas(trivieni,tvieni);

  vector<pair<string, int> > kvieni; // keturiu r zodziai
  rusiavimas(keturvieni,kvieni);
////////////////////////////////////////////////////////////////
string s_raides = "";
string ne_raides = "";
bool t;
////////////////////////////////////////////////////////////////

temp = "A";
temp2 = vienos[0].first;
idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);

///////////////////////////////////////////////////////////////

temp2 = tvieni[0].first;
if (temp2[0] == s_raides[0])
{
  
  temp = "AND";
  idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);

  temp2 = tvieni[1].first;
  temp = "THE";
  idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
}
else
{
  temp = "THE";
  idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);

  temp2 = tvieni[1].first;
  temp = "AND";
  idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
}
//////////////////////////////////////////////////////////////
 int r = 0;
 temp2 = dvieni[0].first;

  for (int b = 0; b < s_raides.size(); b++)
   {
     if (s_raides[b] == temp2[1])
     {
       if (ne_raides[b] == 'N')
       {
         b = s_raides.size();
         r = 1;
       }
     }
   }

 if(r == 0)
 {
   for (int i = 0; i < s_raides.size(); i++)
   {
     if (dvieni[4].first[1] == s_raides[i])
     {
       if (ne_raides[i] == 'N')
       {
         r = 2;
         i = s_raides.size();
       }
     }
   }
 }
  ///////////
  char tem [9];
  char ro;
  ///////////
  ro = 'A'; tem[0] = rasti(ro,ne_raides,s_raides);
  ro = 'N'; tem[1] = rasti(ro,ne_raides,s_raides);
  ro = 'T'; tem[2] = rasti(ro,ne_raides,s_raides);


 if (r == 0)
 {
   temp = "OF";
   temp2 = dvieni[0].first;
   idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
 }
 else if (r == 1)
 {
   temp = "OF";
   temp2 = dvieni[1].first;
   idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
 }
 else if (r == 2)
 {
   temp = "OF";
   temp2 = dvieni[2].first;
   idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
 }
  
 ////////////////////////////////////////////////////

  
  tem [0] = temp2[1];
  tem [1] = temp2[0];
  t = false;

  for (int i = 0; i < 10 && !t; i++)
  {
    if (tvieni[i].first[0] == tem[0] && tvieni[i].first[1] == tem [1])
    {
      tem[2] = tvieni[i].first[2];
      t = true;
    }
  }

  temp = "FOR";
  temp2 = "";
  temp2 = temp2 + tem[0] + tem[1] + tem[2];
  idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
  
 ////////////////////////////////////////////////////
  ro = 'N'; tem[1] = rasti(ro,ne_raides,s_raides);

  t =false;
  for (int i = 0; i < 10 && !t; i++)
  {
    if (dvieni[i].first[1] == tem[1])
    {
      tem[0] = dvieni[i].first[0];
      t = true;
    }
  }

  temp = 'I';
  temp2 = tem[0];
  idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
 ////////////////////////////////////////////////////
  ro = 'T'; tem[0] = rasti(ro,ne_raides,s_raides);
  ro = 'H'; tem[1] = rasti(ro,ne_raides,s_raides);
  ro = 'I'; tem[2] = rasti(ro,ne_raides,s_raides);

  ar_paejo = false;

  for (int i = 0; i < kvieni.size() && !ar_paejo; i++)
  {
    if (kvieni[i].first[0] == tem[0] && kvieni[i].first[1] == tem[1] && kvieni[i].first[2] == tem[2])
    {
      ar_paejo = true;
      temp2 = kvieni[i].first[3];
    }
  }

  if (ar_paejo)
  {
    temp = 'S';
    idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
  }
  else
  {
    ro = 'I'; tem[0] = rasti(ro,ne_raides,s_raides);
    ro = 'T'; tem[1] = rasti(ro,ne_raides,s_raides);
    ro = 'E'; tem[2] = rasti(ro,ne_raides,s_raides);

    for (int i = 0; i < kvieni.size() && !ar_paejo; i++)
    {
    if (kvieni[i].first[1] == tem[0] && kvieni[i].first[2] == tem[1] && kvieni[i].first[3] == tem[2])
    {
      ar_paejo = true;
      temp2 = kvieni[i].first[0];
      }
    }
    temp = 'S';
    idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);

    
  }
  //////////////////////////////////////////////////
    ro = 'T'; tem[0] = rasti(ro,ne_raides,s_raides);
    ro = 'S'; tem[1] = rasti(ro,ne_raides,s_raides);
    ro = 'E'; tem[2] = rasti(ro,ne_raides,s_raides);
    ro = 'O'; tem[3] = rasti(ro,ne_raides,s_raides);

  t = false;
  for (int i = 0; i < 10 && !t; i++)
  {
    if (dvigub[i].first[0] != tem[0] && dvigub[i].first[0] != tem[1] && dvigub[i].first[0] != tem[2] && dvigub[i].first[0] != tem[3])
    {
      temp2 = "";
      temp2 = temp2 + dvigub[i].first[0] + dvigub[i].first[0];
      t = true;
    }
  }

  temp = "LL";
  idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
 //////////////////////////////////////////////////
  ro = 'O'; tem[0] = rasti(ro,ne_raides,s_raides);
  ro = 'F'; tem[1] = rasti(ro,ne_raides,s_raides);
  ro = 'T'; tem[2] = rasti(ro,ne_raides,s_raides);
  ro = 'I'; tem[3] = rasti(ro,ne_raides,s_raides);
  ro = 'N'; tem[4] = rasti(ro,ne_raides,s_raides);
  ro = 'A'; tem[5] = rasti(ro,ne_raides,s_raides);
  ro = 'S'; tem[6] = rasti(ro,ne_raides,s_raides);
  ro = 'E'; tem[7] = rasti(ro,ne_raides,s_raides);

  t = false;
  for (int i = 0; i < 10 && !t; i++)
  {
    if (dvieni[i].first[0] != tem[0] && dvieni[i].first[0] != tem[1] && dvieni[i].first[0] != tem[2] && dvieni[i].first[0] != tem[3] && dvieni[i].first[0] != tem[4] && dvieni[i].first[0] != tem[5] && dvieni[i].first[0] != tem[6] && dvieni[i].first[0] != tem[7] && dvieni[i].first[1] != tem[0] && dvieni[i].first[1] != tem[1] && dvieni[i].first[1] != tem[2] && dvieni[i].first[1] != tem[3] && dvieni[i].first[1] != tem[4] && dvieni[i].first[1] != tem[5] && dvieni[i].first[1] != tem[6] && dvieni[i].first[1] != tem[7])
    {
      temp2 = "";
      temp2 += dvieni[i].first[0];
      temp2 += dvieni[i].first[1];
      t = true;
    }
  }

  temp = "BY";
  idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);

 //////////////////////////////////////////////////

  ro = 'I'; tem[0] = rasti(ro,ne_raides,s_raides);
  ro = 'T'; tem[1] = rasti(ro,ne_raides,s_raides);
  ro = 'H'; tem[2] = rasti(ro,ne_raides,s_raides);

  t = false;
  for (int i = 0; i < 10 && !t; i++)
  {
    if (kvieni[i].first[1] == tem[0] && kvieni[i].first[2] == tem[1] && kvieni[i].first[3] == tem[2])
    {
      temp2 = "";
      temp2 = temp2 + kvieni[i].first[0];
      t = true;
    }
  }

    temp = "W";
    idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
 //////////////////////////////////////////////////
  ro = 'F'; tem[0] = rasti(ro,ne_raides,s_raides);
  ro = 'R'; tem[1] = rasti(ro,ne_raides,s_raides);
  ro = 'O'; tem[2] = rasti(ro,ne_raides,s_raides);
  
  t = false;
  for (int i = 0; i < 10 && !t; i++)
  {
    if (kvieni[i].first[0] == tem[0] && kvieni[i].first[1] == tem[1] && kvieni[i].first[2] == tem[2])
    {
      temp2 = "";
      temp2 = temp2 + kvieni[i].first[3];
      t = true;
    }
  }

  temp = "M";
  idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
  
 /////////////////////////////////////////////////
  ro = 'I'; tem[0] = rasti(ro,ne_raides,s_raides);
  ro = 'N'; tem[1] = rasti(ro,ne_raides,s_raides);
  
  bool k = false;
  for (int i = 0; i < tvienos.size() && !k; i++)
  {
    if (tvienos[i].first[0] == tem[0] && tvienos[i].first[1] == tem[1])
    {
      temp2 = "";
      temp2 = tvienos[i].first[2];
      k = true;
    }
  }

  temp = "G";
  if (t)
    idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);

  cout << temp2;

 //////////////////////////////////////////////////
  ro = 'G'; tem[0] = rasti(ro,ne_raides,s_raides);
  ro = 'O'; tem[1] = rasti(ro,ne_raides,s_raides);
  ro = 'D'; tem[2] = rasti(ro,ne_raides,s_raides);

  if (t && !(tvieni[10].first[0] == tem[0] && tvieni[10].first[1] == tem[1] && tvieni[10].first[2] == tem[2] ))
  {
    ro = 'H'; tem[0] = rasti(ro,ne_raides,s_raides);
    ro = 'A'; tem[1] = rasti(ro,ne_raides,s_raides);
    ro = 'E'; tem[2] = rasti(ro,ne_raides,s_raides);

    k = false;
    for (int i = 0; i < tvienos.size() && !k; i++)
    {
      if (kvieni[i].first[0] == tem[0] && kvieni[i].first[1] == tem[1] && kvieni[i].first[3] == tem[2])
      {
        temp2 = "";
        temp2 = kvieni[i].first[2];
        k = true;
      }
    }

    temp = "V";
      idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
  }
  
  /////////////////////////////////////////////////

  ro = 'S'; tem[0] = rasti(ro,ne_raides,s_raides);
  ro = 'E'; tem[1] = rasti(ro,ne_raides,s_raides);
  ro = 'D'; tem[2] = rasti(ro,ne_raides,s_raides);

  k = false;
  for (int i = 0; i < kvieni.size() && !k; i++)
    {
      if (kvieni[i].first[1] == tem[0] && kvieni[i].first[2] == tem[1] && kvieni[i].first[3] == tem[2])
      {
        temp2 = "";
        temp2 = kvieni[i].first[0];
        k = true;
      }
    }

  temp = "U";
  idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
  //////////////////////////////////////////////////

  ro = 'A'; tem[0] = rasti(ro,ne_raides,s_raides);
  ro = 'N'; tem[1] = rasti(ro,ne_raides,s_raides);

  k = false;
  for (int i = 0; i < tvieni.size() && !k; i++)
    {
      if (tvieni[i].first[1] == tem[0] && tvieni[i].first[2] == tem[1])
      {
        temp2 = "";
        tem[4] = tvieni[i].first[0];
        temp2 = tvieni[i].first[0];
        k = true;
        for (int b = 0; b < s_raides.size(); b++)
        {
          if (s_raides[i] == tem[4])
          {
            k = false;
            b = s_raides.size();
          }
        }
      }
    }

  if (k)
  {
    temp = "C";
    idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
  }
  else
  {
    ro = 'B'; tem[0] = rasti(ro,ne_raides,s_raides);
    k = false;
    for (int i = 0; i < dvieni.size() && !k; i++)
    {
      if (dvieni[i].first[0] == tem[0])
      {
        temp2 = "";
        tem[4] = dvieni[i].first[1];
        temp2 = dvieni[i].first[1];
        k = true;
        for (int b = 0; b < s_raides.size(); b++)
        {
          if (s_raides[i] == tem[4])
          {
            k = false;
            b = s_raides.size();
          }
        }
      }
    }
    temp = "C";
    idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);
    
  }

  /////////////////////////////////////////////////
  string raides_daznos = "EARIOTNSLCUDPMHGBFYWKVXZJQ";
  string raides_daznos2 = "EARIOTNSLCUDPMHGBFYWKVXZJQ";

 char liko [26];
 char bliko[26];

  for (int i = 0; i < raides_daznos.size(); i++)
  {
    t = true;
    for (int b = 0; b < ne_raides.size(); b++)
    {
      if (ne_raides[b] == raides_daznos[i])
      {
        raides_daznos[i] = '-';
        for (int y = 0; y < raides_daznos2.size(); y++)
        {
          if (raides_daznos2[y] == s_raides[b])
          {
            raides_daznos2[y] = '-';
          }
        }
      }
    }
  }

  int kiek_liko = 0;

  for (int i = 0; i < raides_daznos.size(); i++)
  {
    if (raides_daznos[i] != '-')
    {

      liko[kiek_liko] = raides_daznos[i];
      kiek_liko++;
    }
  }
  r = 0;
  for (int i = 0; i < raides_daznos2.size(); i++)
  {
    if (raides_daznos2[i] != '-')
    {
      bliko[r] = raides_daznos2[i];
      r++;
    }
  }

   for (int i = 0; i < kiek_liko; i++)
  {
    temp = liko[i];
    temp2 = bliko[i];
    idejimas(s_text,ne_text,t,s_raides,ne_raides,kiekis,temp2,temp);

    cout << t << " " << liko[i] << " " << bliko[i] << endl;
  }

  cout << kiek_liko;


  for (int i = 0; i < kiekis; i++)
    {
      for (int b = 0; b < ne_text[i].size(); b++)
      {
        if (ne_text[i][b] ==  '-')
        {
          ne_text[i][b] = 'C';
        }
      }
    }

  ofstream rezu ("tikrastekstas.txt");
  for (int i = 0; i < kiekis-1; i++)
  { 
    rezu << ne_text[i];
    if (kiekis != i+1)
      rezu << " ";
  }
} 

void idejimas(string s_text[], string ne_text[], bool &t, string &s_raides, string &ne_raides,int kiekis ,string is, string ika)
{
  
  t = true;
  for(int i = 0; i < ika.size(); i++)
  {
    for (int b = 0; b < ne_raides.size(); b++)
    {
      if (ika[i] == ne_raides[b])
      {
        if (is[i] != s_raides[b])
        {
          t = false;
        }
      }
    }
  }

  if (t)
  {
    for (int i = 0; i < ika.size(); i++)
    {
      for (int b = 0; b < kiekis; b++)
      {
        for (int y = 0; y < s_text[b].size(); y++)
        {
          if (s_text[b][y] == is[i])
          {
            ne_text[b][y] = ika[i];
          }
        }
      }
      ne_raides += ika[i];
      s_raides += is[i];
    }
  }

}

bool palyginti(pair<string, int>& a, pair<string, int>& b)
{
    return a.second > b.second;
}

void rusiavimas(map<string, int>& M, vector<pair<string, int> >& A)
{

    for (auto& it : M) {
        A.push_back(it);
    }
  
    sort(A.begin(), A.end(), palyginti);
  
    
}

bool palyginti_char(pair<char, int>& a, pair<char, int>& b)
{
    return a.second > b.second;
}

void rusiavimas_char(map<char, int>& M, vector<pair<char, int> >& A)
{

    for (auto& it : M) {
        A.push_back(it);
    }
  
    sort(A.begin(), A.end(), palyginti_char);
  
    
}
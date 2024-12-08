ifstream ifile ("risultati.dat");

int i;

ifile >> i;

double a, b;

while(ifile >> a >> b){
  if (a > b){
    cout << a << endl;
  }

  if else (b > a){
      cout << b << endl;
    }

  else (a = b){
      cout << "i due valori sono uguali" << endl;
    }
 }

return 0;

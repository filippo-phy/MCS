int b, h;

cout << "inserire la base e l'altezza del rettangolo: " << endl;
cin>>b;
cin >> h;
cout << endl;
for (int i=0; i<b ; i++){
  cout << "*" << flush;
 }

cout << endl;

for (int j=0; j<(h-2); j++){
  cout << "*" << flush;

  for (int i=0; i<(b-2); i++){
    cout << " " << flush;
  }

  cout << "*" << endl;
 }

for (int i=0; i<b ; i++){
  cout << "*" << flush;
 }

cout << endl;

return 0;




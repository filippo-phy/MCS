double a, b, c;

cout << "inserire i lati del triangolo: " << endl;
cin >> a;
cin >> b;
cin >> c;

if (a<0 || b<0 || c<0){
  cout << "i valori dei lati devono essere tutti positivi" << endl;
  return 1;
 }

if (a+b>c && a+c>b && b+c>a){
  cout << "i valori " << a << ", " << b << ", " << c << " possono essere i lati di un triangolo" << endl;
 }

 else {
   cout << "i valori " << a << ", " << b << ", " << c << " non possono essere i lati di un triangolo" << endl;
 }

return 0;

MotoParabolico p1(9.6, 7.1, 12.1, 8.2);
MotoParabolico p2(4.5, 22.0, 15.9, 3.7);

double distanza1, distanza2;

distanza1=p1.xAtterraggio;
distanza2=p2.xAtterraggio;

if (distanza1>distanza2){
  cout << distanza1 << endl;

 }

 else {
   cout << distanza2 << endl;

 }

return 0;

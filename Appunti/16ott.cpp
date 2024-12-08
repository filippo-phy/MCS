//Propagazione del calore

T((N-1)/2+1)=T0+DeltaT //il centro a 100°C
  //dopo plot, nel while
  T(2:N-1) = T(2:N-1)+eta*(T(3:N))+T(1:N-2)-2*T(2:N-1));


Tteo = T0+DeltaT*dx*normpdf(x, L/2, sigma)

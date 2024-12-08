#include "Vector3.h"
#include "OdeSolver.h"
#include <cmath>

void OdeSolver::AddMatPoint(MatPoint tmp){
  m_p.push_back(tmp);
}

vector<MatPoint> OdeSolver::GetMatPoints(){
  return m_p;
}

MatPoint OdeSolver::GetMatPoint(unsigned int i){
  return m_p[i];
}

unsigned int OdeSolver::N(){
  return m_p.size();
}

void OdeSolver::T(double t0){
  m_t=t0;
}

double OdeSolver::T(){
  return      m_t;
}

void OdeSolver::DeltaT(double h){
  m_h = h;
}

double OdeSolver::DeltaT(){
  return   m_h;
}


Vector3 OdeSolver::m_A(unsigned int i, double t, vector<MatPoint> p){
  //STEP 3 Calcolo dell'accelerazione dovuta a forze interne e forze esterne
  // * Sommo le forze interne dovute a tutti i MatPoint con indice j diverso da i
  Vector3 F_int_tot;

  for(unsigned int j=0; j<p.size(); j++){
    if (j!=i){
      F_int_tot = F_int_tot+fInternal(i, j, t, p);
    }
  }
    
  // * Sommo la forza esterna su i
  Vector3 F_tot=fExternal(i, t, p)+F_int_tot;
  
  
  // * Ritorno l'accelerazione
  double mass_i=p[i].Mass();
  return F_tot*(1/mass_i) ;
}

//Da implementare a cura dello studente
void OdeSolver::Step(){

  if (m_method=="Eulero"){
    vector<Vector3>  k1(m_p.size());
    vector<Vector3>  w1(m_p.size());
    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_A(i,m_t,m_p);
    }

    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k1[i]);
      m_p[i].V(m_p[i].V() + w1[i]);
    }

  }

  else if (m_method=="Rk2"){
    // STEP 5 implementare Runge Kutta al secondo ordine
    // * Riprendere il calcolo di k1/w1
    vector<Vector3>  k1(m_p.size());
    vector<Vector3>  w1(m_p.size());
    vector<Vector3>  k2(m_p.size());
    vector<Vector3>  w2(m_p.size());
    for (unsigned int i=0;i<m_p.size();i++){
      k1[i] = m_h*m_p[i].V();
      w1[i] = m_h*m_A(i,m_t,m_p);
    }
     vector<MatPoint> m_p_half=m_p;
    // * Per il calcolo di k2/w2 devo dotarmi di una copia di m_p
    for (unsigned int i=0;i<m_p.size();i++){
      m_p_half[i].R(m_p[i].R()+0.5*k1[i]);//posizione a metà intervallo
      m_p_half[i].V(m_p[i].V()+0.5*w1[i]);
    }

    
   for (unsigned int i=0;i<m_p.size();i++){   
      k2[i] = m_h*m_p_half[i].V();
      w2[i] = m_h*m_A(i,m_t,m_p_half);
    }

    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p[i].R() + k2[i]);
      m_p[i].V(m_p[i].V() + w2[i]);
    }//calcolata nel punto intermedio dell'intervallo temporale
  }

  else if (m_method=="Verlet_V"){
    vector<MatPoint> m_p_future=m_p;
    for (unsigned int i=0;i<m_p.size();i++){   
      m_p_future[i].R(m_p[i].R()+m_h*m_p[i].V()+0.5*pow(m_h, 2)*m_A(i, m_t, m_p));
      m_p_future[i].V(m_p[i].V()+0.5*m_h*(m_A(i, m_t, m_p)+m_A(i, m_t+m_h, m_p_future)));
    }

    for (unsigned int i=0;i<m_p.size();i++){
      m_p[i].R(m_p_future[i].R());
      m_p[i].V(m_p_future[i].V());
    }

    
  }
  m_t += m_h;

}


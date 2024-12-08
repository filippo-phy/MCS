import math

def a(sigma,f,x):
    return -f/(sigma**2)

def soleq(n1,n2,sigma):
    f=np.array(x)
    j=np.sign(n2-n1)
    f[n1]=0.0
    f[n1+j]=1.0e-4

    for i in range(n1+2*j,n2+j,j):
        f[i]=2*f [i-j]-f[i-2*j]+h*h*a(sigma, f[i-j, x[i-j])

    return f
                                                                       


sigma = 1
                                                    
    
                   

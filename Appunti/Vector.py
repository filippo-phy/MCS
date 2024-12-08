import math #importazione libreria, si può cambiando nome e nel caso di contrasto sovrascrive librerie già presenti

class vector:
    def __init__(self, a=0, b=0):
        self.x = a
        self.y = b
    def __str__(self):
        return "("+str(self.x)+","+str(self.y)+")"
    def __add__(self,b):
        return vector(self.x+b.x, self.y+b.y) #in base a com'è b lui fa cose
    def __mul__ (self,b):
        if isinstance (b, int) or isinstance (b, float):#float è un qualsiasi floating point
            return vector(self.x*b, self.y*b)
        elif isinstance (b, vector):
            return self.x*b.x+self.y*b.y
    def __rmul__(self,b):
        return self*b
    def mod (self):
        return math.sqrt(self*self)

class complex(vector):#classe derivata
    def cong(self):
        return complex(self.x,-self.y)
    
        
    
    

v= vector(1,0)
w = vector(2,1)
print(v)
z=v+w
print(z)
print(z*2)
print(z*w)
print(v.mod())

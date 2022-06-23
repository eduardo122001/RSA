#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

//ALGORITMOS PARA LA GENERACION DEL INVERSO
int64_t euclides(int64_t num1,int64_t num2){
    while(num2!=0){
        int t=num2;
        num2=num1%num2;
        num1=t;
    }
    return num1;
}

int64_t ext_euclides(int64_t a,int64_t b,int64_t &x,int64_t &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }else{
        int64_t x1,y1;
        int64_t d=ext_euclides(b,a%b,x1,y1);
        x=y1;
        y = x1-y1*(a/b);
        return d;
    }
}

int64_t inverso(int64_t a,int64_t n){
    if(euclides(a,n)==1){
       int64_t x,y;
       int64_t d=ext_euclides(a,n,x,y);
       return (x%n+n)%n;
    }else{
        cout<<"no existe inverso"<<endl;
        return 0;
    }
}

//ALGORITMOS PARA LA GENERACION DE PRIMOS
int64_t random(int64_t  s,int64_t n){
    int64_t num=s+rand()%((n+1)-s);
    return num;
}

int64_t exp_mod(int64_t a,int64_t x, int64_t n){
     int64_t c=a%n;
     int64_t r=1;
    while(x>0){
        if(x%2!=0){r=(r*c)%n;}
        c=(c*c)%n;
        x=x/2;
    }
    return r;
}

bool es_compuesto(int64_t a,int64_t n,int64_t t,int64_t u){
     int64_t x=exp_mod(a,u,n);
    if(x==1||x==n-1){
        return false;
    }
    for(int64_t i=1;i<t+1;i++){

         int64_t xi=exp_mod(x,2,n);
        x=xi;
        if(xi==n-1){
            return false;
        }
    }
    return true;
}

int64_t miller_rabin(int64_t n , int64_t s){
     int64_t t=0;
     int64_t u=n-1;
    while(u%2==0){
        u=u/2;
        t++;
    }
    for(int64_t j=1;j<s+1;j++){
         int64_t a=random(2,n-1);
        if(es_compuesto(a,n,t,u)){return false;}
    }
    return true;
}

int64_t random_bits(int64_t b){
    srand (time (NULL));
    int64_t n = random(0,pow(2,b)-1);
    int64_t m = ((pow(2,b-1))+1)*(1);
    if(m>n){
        n=n+(m-1);
    }
    if(n%2==0){n=n+1;}
    return n;
}

//ALGORITMO PARA GENERACION DE LLAVE RSA(BOOL REVISARA SI CUMPLE TODAS LAS CONDICIONES PARA CUMPLIR CON RSA)
bool RSA(int64_t b,int64_t &n,int64_t &e,int64_t &d){
    int k=b;
    k=k/2;
    int64_t primo1;
    int64_t primo2;
    for(int64_t i=0;i<2;i++){
        int64_t n=random_bits(k);
        int64_t s=sqrt(n);
        switch(i){
            case 0:
                while(miller_rabin(n,s)==false){
                  n = n+2;
                }
                primo1=n;
            case 1:
                n=n*3;
                while(miller_rabin(n,s)==false){
                  n = n-2;
                }
                primo2=n;
            break;
        }
    }
    n=primo1*primo2;
    int64_t euler=(primo1-1)*(primo2-1);
    while(true){
        int64_t num=2+rand()%((n+1)-2);
        if(euclides(num,euler)==1){
            e=num;
            break;
        }
    }
     d=inverso(e,euler );
    if((d*e)%euler==1)
    {   return true;}
    else
    {   return false;}
}



int main()
{   //GENERACION DE RSA
    int64_t n,e,d;
    int k=31;
    bool rsa=RSA(k,n,e,d);
    //SI RSA ES (1) SE ACEPTA LA LLAVE, CASO CONTRARIO GENERARA OTRA LLAVE QUE CUMPLA TODAS LAS CONDICIONES
    while(rsa==0){
        rsa=RSA(k,n,e,d);
    }
    cout<<"RSA valores:"<<endl;
    cout<<"n= "<<n<<" ; e= "<<e<<" ; d= "<<d<<endl<<endl;
    cout<<"Generacion de numeros aleatorios para m"<<endl;
    for(int i=0;i<10;i++){
        int64_t m=rand()%100;
        int64_t c=exp_mod(m,e,n);
        int64_t s=exp_mod(c,d,n);
        cout<<"m= "<<m<<" ; C= "<<c<<" ; m'= "<<s<<endl;
    }
}

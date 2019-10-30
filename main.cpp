#include <iostream>
#include <math.h>
#include <fstream>
//problema 26 Popescu Stefan-Augustin, gr254
using namespace std;

ifstream in ("p1.in"); //folosit la teste
//Se presupune ca matricea respecta regulile matematice pentru operatii (Nu putem aduna/scadea matrici de marimi diferite).


class matrice
{
private:
    int nr_l;
    int nr_c;
    double **v;
public:
    matrice();
    matrice(float, int, int);
    matrice(double**,int, int);
    ~matrice();


    void citire();
    void afisare();
    void actualizare(double, int, int);

    //void inversa(double**, int); //e comentata mai jos nu am putut sa o fac si sa o combin cu operatorul friend ~
    //void calcul();

    matrice& operator = (const matrice& ob);
    double& operator [] (const int index); //nu imi dau seama daca am facut conform cerintei

    friend matrice& operator + (matrice& ob1,matrice& ob2);
    friend matrice& operator + (matrice& ob1);

    friend matrice& operator - (matrice& ob1,matrice& ob2);
    friend matrice& operator - (matrice& ob1);

    friend matrice operator * (matrice ob1,matrice ob2); //aici reusesc cu matrici cu marimi asemanatoare (sa zicem n*n), dar nu stiu cum sa adaptez pentru toate tipurile de marimi (imi da crash)
    friend matrice operator * (matrice ob1, int);

    friend matrice operator *= (matrice ob1,matrice ob2); // Nu imi dau seama cum sa transmit ca sa imi iasa x*=y
    friend matrice operator *= (matrice ob1, int);

    friend matrice& operator += (matrice& ob1,matrice& ob2);
    friend matrice& operator -= (matrice& ob1,matrice& ob2);

    friend bool operator == (matrice& ob1,matrice& ob2);
    friend bool operator == (matrice& ob1,double*);
    friend bool operator == (double*,matrice& ob2);

    friend bool operator != (matrice& ob1,matrice& ob2);
    friend bool operator != (matrice& ob1,double*);
    friend bool operator != (double*,matrice& ob2);

    friend bool operator < (matrice& ob1,matrice& ob2);
    friend bool operator < (matrice& ob1,double*);
    friend bool operator < (double*,matrice& ob2);

    friend bool operator <= (matrice& ob1,matrice& ob2);
    friend bool operator <= (matrice& ob1,double*);
    friend bool operator <= (double*,matrice& ob2);

    friend bool operator > (matrice& ob1,matrice& ob2);
    friend bool operator > (matrice& ob1,double*);
    friend bool operator > (double*,matrice& ob2);

    friend bool operator >= (matrice& ob1,matrice& ob2);
    friend bool operator >= (matrice& ob1,double*);
    friend bool operator >= (double*,matrice& ob2);

    friend bool operator ! (matrice& ob1);
    //friend matrice& operator ~ (matrice& ob1); //am incercat dar nu imi iese la afisare, imi iese ori aiurea ori imi da crash



    friend int nrlinii(matrice&);
    friend int nrcoloane(matrice&);
    friend int nrelemente(matrice&);

};
matrice::matrice()
{
    nr_l=0;
    nr_c=0;
    v=NULL;
}

matrice::matrice(float f, int a, int b)
{
    nr_l=a;
    nr_c=b;
    v = new double*[nr_l];
    for(int i=0; i<nr_c; i++)
        v[i]=new double[nr_c];
    for(int i=0; i<a; i++)
        for(int j=0; j<b; j++)
            v[i][j]=f;
}
matrice::matrice(double **M, int a, int b)
{
    nr_l=a;
    nr_c=b;
    v=M;
}
matrice::~matrice()
{
    delete []v;
}

matrice& matrice::operator = (const matrice& ob)
{
    if(this!= &ob)
    {
        this->nr_l= ob.nr_l;
        this->nr_c= ob.nr_c;
        this->v= ob.v;
    }
    return *this;

}
double& matrice::operator [] (const int index)
{
    return *(this->v[index]);
}
matrice& operator + (matrice& ob1,matrice& ob2)
{
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            ob1.v[i][j]+=ob2.v[i][j];
    return ob1;

}
matrice& operator + (matrice& ob1)
{
    return ob1;
}
matrice& operator - (matrice& ob1)
{
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            ob1.v[i][j]=0-ob1.v[i][j];
}
/*matrice& operator ~ (matrice& ob1) //
{
    matrice ob2;
    ob2.nr_c=ob1.nr_c;
    ob2.nr_l=ob1.nr_l;
    ob2.v=ob1.v;
    inversa(ob2.v,ob2.nr_l);
    return ob2;
}
void matrice::inversa(double **v,int n) //
{
    int i, j, k;
    double d;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < 2 * n; j++)
        {
            if (j == (i + n))
            {
                v[i][j] = 1;
            }
        }
    }
    for (i = n-1; i > 0; i--)
    {
        if (v[i-1][0] < v[i][0])
        {
            for(j = 0; j < n * 2; j++)
            {
                d = v[i][j];
                v[i][j] = v[i-1][j];
            v[i-1][j] = d;
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n * 2; j++)
        {
            if (j != i)
            {
                d = v[j][i] / v[i][i];
                for (k = 0; k < n * 2; k++)
                {
                    v[j][k] = v[j][k] - (v[i][k] * d);
                }
            }
        }
    }
    for (i = 0; i < n; i++)
    {
        d=v[i][i];
        for (j = 0; j < n * 2; j++)
        {
            v[i][j] = v[i][j] / d;
        }
    }

}
void matrice::calcul(int n, float **a, float *b, float *x) // ma folosesc de Ax=-B (Ca sa fac Ax+B=0), dar nu inteleg de ce nu imi iese, transmit matricea obiectului prin ea, ex ob1.v
{
  int i,j;
  float s;

  for(i = 0; i < n; i++) {
        s = 0;
        for(j = 0; j < i; j++) {
            s = s + a[ i][ j] * x[ j];
        }
        x[ i] = ( b[ i] - s) / a[ i][ i];
   }
}
*/
matrice& operator - (matrice& ob1,matrice& ob2)
{
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            ob1.v[i][j]-=ob2.v[i][j];
    return ob1;

}
matrice operator * (matrice ob1,matrice ob2)
{
    int i,j,k;
    matrice c;
    c.nr_l=ob1.nr_l;
    c.nr_c=ob2.nr_c;
    double **v;
    v = new double*[c.nr_l];
    for(int i=0; i<c.nr_c; i++)
        v[i]=new double[c.nr_c];

    for(i=0; i<ob1.nr_l; i++)
        for(j=0; j<ob2.nr_c; j++)
            for(k=0; k<ob2.nr_l; k++)
                v[i][j]+=ob1.v[i][k]*ob2.v[k][j];
    c.v=v;
    return c;

}
matrice operator * (matrice ob1, int a)
{
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            ob1.v[i][j]*=a;
    return ob1;

}
matrice operator *= (matrice ob1,matrice ob2)
{
    int i,j,k;
    matrice c;
    c.nr_l=ob1.nr_l;
    c.nr_c=ob2.nr_c;
    double **v;
    v = new double*[c.nr_l];
    for(int i=0; i<c.nr_c; i++)
        v[i]=new double[c.nr_c];

    for(i=0; i<ob1.nr_l; i++)
        for(j=0; j<ob2.nr_c; j++)
            for(k=0; k<ob2.nr_l; k++)
                v[i][j]+=ob1.v[i][k]*ob2.v[k][j];
    c.v=v;
    return c;

}
matrice operator *= (matrice ob1,int a)
{
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            ob1.v[i][j]*=a;
    return ob1;

}
matrice& operator += (matrice& ob1,matrice& ob2)
{
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            ob1.v[i][j]+=ob2.v[i][j];
    return ob1;
}
matrice& operator -= (matrice& ob1,matrice& ob2)
{
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            ob1.v[i][j]-=ob2.v[i][j];
    return ob1;
}
bool operator == (matrice& ob1,matrice& ob2)
{
    bool pp=1;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]!=ob2.v[i][j])
                pp=0;
    return pp;
}
bool operator == (matrice& ob1,double* A)
{
    bool pp=1;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]!=A[j])
                pp=0;
    return pp;
}
bool operator == (double *A, matrice& ob1)
{
    bool pp=1;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]!=A[j])
                pp=0;
    return pp;
}
bool operator != (matrice& ob1,matrice& ob2)
{
    bool pp=0;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]!=ob2.v[i][j])
                pp=1;
    return pp;
}
bool operator != (double *A, matrice& ob1)
{
    bool pp=0;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]!=A[j])
                pp=0;
    return pp;
}
bool operator != (matrice& ob1,double *A)
{
    bool pp=0;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]!=A[j])
                pp=0;
    return pp;
}
bool operator ! (matrice& ob1)
{
    bool pp=0;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]!=0)
                pp=1;

    return pp;
}
bool operator < (matrice& ob1,matrice& ob2)
{
    bool pp=1;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]>=ob2.v[i][j])
                pp=0;
    return pp;
}
bool operator < (double *A, matrice& ob1)
{
    bool pp=1;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]<=A[j])
                pp=0;
    return pp;
}
bool operator < (matrice&ob1, double *A)
{
    bool pp=1;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]>=A[j])
                pp=0;
    return pp;
}
bool operator > (matrice& ob1,matrice& ob2)
{
    bool pp=1;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]<=ob2.v[i][j])
                pp=0;
    return pp;
}
bool operator > (double *A, matrice& ob1)
{
    bool pp=1;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]>=A[j])
                pp=0;
    return pp;
}
bool operator > ( matrice& ob1, double *A)
{
    bool pp=1;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]<=A[j])
                pp=0;
    return pp;
}
bool operator <= (matrice& ob1,matrice& ob2)
{
    bool pp=1;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]>ob2.v[i][j])
                pp=0;
    return pp;
}
bool operator <= (matrice&ob1, double *A)
{
    bool pp=1;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]>A[j])
                pp=0;
    return pp;
}
bool operator <= (double *A, matrice&ob1 )
{
    bool pp=1;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]<A[j])
                pp=0;
    return pp;
}
bool operator >= (matrice& ob1,matrice& ob2)
{
    bool pp=1;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]<ob2.v[i][j])
                pp=0;
    return pp;
}
bool operator >= (double *A, matrice&ob1 )
{
    bool pp=1;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]>A[j])
                pp=0;
    return pp;
}
bool operator >= (matrice&ob1, double *A)
{
    bool pp=1;
    double a;
    A=new double[ob1.nr_c];
    cout<<"Introdu numarul pentru vector de comparat: ";
    cin>>a;
    for(int i=0; i<ob1.nr_c; i++)
        A[i]=a;
    for(int i=0; i<ob1.nr_l; i++)
        for(int j=0; j<ob1.nr_c; j++)
            if(ob1.v[i][j]<A[j])
                pp=0;
    return pp;
}
void matrice::citire()
{
    cout<<"Nr linii: ";
    cin>>nr_l;
    cout<<"Nr coloane: ";
    cin>>nr_c;
    v = new double*[nr_l];
    for(int i=0; i<nr_c; i++)
        v[i]=new double[nr_c];
    for(int i=0; i<nr_l; i++)
        for(int j=0; j<nr_c; j++)
            cin>>v[i][j];
}
void matrice::afisare()
{
    cout<<"Nr linii: "<<nr_l<<" Nr coloane: "<<nr_c<<endl;
    for(int i=0; i<nr_l; i++)
    {
        for(int j=0; j<nr_c; j++)
            cout<<v[i][j]<<" ";
        cout<<endl;
    }


}
void matrice::actualizare(double x, int a, int b)
{
    nr_l=a;
    nr_c=b;
    v = new double*[nr_l];
    for(int i=0; i<nr_c; i++)
        v[i]=new double[nr_c];
    for(int i=0; i<a; i++)
        for(int j=0; j<b; j++)
            v[i][j]=x;
}

int nrlinii(matrice& a)
{
    return a.nr_l;
}
int nrcoloane(matrice& a)
{
    return a.nr_c;
}
int nrelemente(matrice& a)
{
    return (a.nr_c*a.nr_l);
}



int main()
{
    matrice x,y,o;
    x.citire();
    cout<<nrelemente(x)<<endl;
    double *u;
    u=new double[3];
    if(x>u)
        cout<<"Y";
    else
        cout<<"N";


}

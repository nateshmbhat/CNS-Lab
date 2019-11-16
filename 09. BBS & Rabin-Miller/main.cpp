#include <bits/stdc++.h>
using namespace std;

int randInRange(int low, int high)
{
    return (rand()%(high-low))+(low+1) ;
}

int genPrime3mod4()
{
    while(true)
    {
        int num = randInRange(10000,100000); // to generate large random number
        bool prime = true;
        for(int i=2; i<=sqrt(num); i++)
        {
            if(num % i == 0)
            {
                prime = false;
                break;
            }
        }
        if(prime && num%4 == 3) return num;
    }
}

int bbs(int p, int q)
{
    long n = p*q ;

    long s; // non-zero and relatively prime to n
    do{ s = rand(); } while(s%p==0 || s%q==0 || s==0);

    int B = 0;
    unsigned long x = (s*s) % n;
    for(int i=0; i<10; i++) // to generate 10 bit output
    {
        x = (x*x) % n;
        B = B<<1 | (x & 1); // x%2 = x&1
    }

    if(B==0) return bbs(p,q); // check that the number generated should not be zero
    cout<<"Blum Blum Shub"<<endl<<"--------------"<<endl;
    cout<<"p = "<< p <<"\nq = "<< q <<"\nn = "<< n <<"\ns = "<< s <<endl;
    return B;
}

// (num pow p)%n
int powModN(int num,int p,int n)
{
	int res=1;
	for(int i=0; i<p; i++)
	{
        res = res * num;
        res = res %  n;
	}
	return res;
}

bool rabinMiller(int n)
{
    double temp = n-1;
    int k = -1;
    while(ceil(temp) == floor(temp))
    {
        temp = temp/2.0;
        k++ ;
    }
    int q = (n-1)/pow(2,k);
    int a = randInRange(1, n-1);

    cout << "\nRabin Miller(" << n << ")\n-----------------" << endl;
    cout << n-1 << " = 2^" << k << " * " << q << endl;
    cout << "k = " << k << "\nq = " << q << "\na = " << a << endl;

    // if (a pow q)%n == 1
    if(powModN(a,q,n) == 1) return true;
    for(int j=0; j<=k-1; j++)
    {
        if(powModN(a, pow(2,j)*q, n) == n-1) return true;
    }
    return false;
}

int main()
{
    srand(time(NULL));
    int p = genPrime3mod4(); // large prime number (p%4=3)
    int q = genPrime3mod4(); // large prime number (q%4=3)
    int randNum = bbs(p, q);
    cout << "Random number generated by BBS = " << randNum << endl;

    bool isPrime = rabinMiller(randNum);
    if(isPrime) cout << "Inconclusive" << endl;
    else        cout << "Composite" << endl;
}

/*************** output-1 **************
Blum Blum Shub
--------------
p = 10223
q = 34543
n = 353133089
s = 22252
Random number generated by BBS = 443

Rabin Miller(443)
-----------------
442 = 2^1 * 221
k = 1
q = 221
a = 81
Inconclusive
****************************************/

/**************** output-2 **************
Blum Blum Shub
--------------
p = 25447
q = 41983
n = 1068341401
s = 27864
Random number generated by BBS = 982

Rabin Miller(982)
-----------------
981 = 2^0 * 981
k = 0
q = 981
a = 234
Composite
****************************************/
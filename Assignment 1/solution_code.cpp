#include <iostream>
using namespace std;
int b1[]={2,5,7};/*prime factors of roll. no. 70 */
/*iterative implementation function of binary GCD*/
int gcd1(int u,int v,int b){/*b is 2 here*/
    int c=0;/* counter for no. of operations*/
    int res=1;
    /* GCD of any number with zero is number itself*/
    if (u == 0) return v;
    if (v == 0) return u;
     /* checking if u and v have common factors of b*/
     while (((u/b)*b==u) && ((v/b*b) ==v)) {
        res*=b;/* storing these common factors of b as they will contribute to GCD
                  in along with GCD(u/b,v/b)*/
        u /=b;
        v /=b;
        c+=3;
     }
     while ((u/b)*b==u) {u/=b;c+=1;}

     /* Now u will be odd(if b=2) or non-multiple of b forever in the algorithm*/
     /* this loop will run until both numbers become equal, so  after subtraction i.e v=v-u=0 */
     while(v!=0){
         while ((v/b)*b==v) {v/=b;c+=1;}
         /* now u and v are both odd(or non-multiple of b).Now  we ensure that v>=u*/
         if (u > v){
            int temp = v; v = u; u = temp; // Swap u and v
            }
        v=v-u;c+=1;
        /* the new v will be even(odd-odd) if b=2 and equal to zero if old u and old v are equal
           new v can be a multiple of b*/
        cout<<"="<<res<<"*GCD("<<u<<","<<v<<") with "<<c<<" total operations\n";
     }

    return u*res/* putting back common factors of b*/;
}
/* iterative implementation of gcd using all available prime factors */
int gcd2(int u,int v){
    int res=1;
    int c=0;/* counter for no. of operations*/
    /* GCD of any number with zero is number itself*/
    if (u == 0) return v;
    if (v == 0) return u;
    int b;
     /* checking if u and v have common factors of b*/
     for (int i=0;i<sizeof(b1)/sizeof(int);i++){b=b1[i];
     while (((u/b)*b==u) && ((v/b*b) ==v)) {
        res*=b;/* storing these common factors of b as they will contribute to gcd
                  in along with gcd(u/b,v/b)*/
        u /=b;
        v /=b;
        c+=3;
     }
     while ((u/b)*b==u) u/=b;c+=1;}

     /* Now u will be odd(if b=2) or non-multiple of b forever in the algorithm*/
     /* this loop will run until both numbers become equal, so  after subtraction i.e v=v-u=0 */
     while(v!=0){
         for (int i=0;i<sizeof(b1)/sizeof(int);i++){b=b1[i];
         while ((v/b)*b==v) v/=b;c+=1;}
         /* now u and v are both odd(or non-multiple of b).Now  we ensure that v>=u*/
         if (u > v){
            int temp = v; v = u; u = temp; // Swap u and v
            }
        v=v-u;c+=1;
        /* the new v will be even(odd-odd) if b=2 and equal to zero if old u and old v are equal
           new v can be a multiple of b*/
        cout<<"="<<res<<"*GCD("<<u<<","<<v<<") with "<<c<<" total operations\n";
     }
    return u*res/* putting back common factors */;
}


int main()
{
    cout<<"Enter the two numbers of which you want GCD:\n";
    int x,y;
    cin>>x>>y;
    cout<<"Question 1\nThe GCD using prime factor 2 is \n";
    cout<<"The GCD using prime factor 2 is "<<gcd1(x,y,2)<<"\n";
    cout<<"\n";

    cout<<"Question 2 \n The GCD using prime factors {2,5,7} is \n";
    cout<<"The GCD using prime factors {2,5,7} is "<<gcd2(x,y)<<"\n";

    return 0;
}



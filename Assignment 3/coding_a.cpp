#include<bits/stdc++.h>
using namespace std;
#define ll long long
// i have used only one stack to store the multiplication factor
stack<pair<ll,ll> >st;
// this question can pass all constraints as i have done calculations while iterating and
// i have  not stored the equivalent character string which can be very large in extreme cases i.e. (9^300000)
//i have calculated the resultant position while opening the brackets and using the multiplication factor
int main()
{   ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t=1;// as we are having only one test case
    ll N,M;// N is no. of rows and M is no. of columns
    cin>>N>>M;
    while(t--)
    {
        
        ll r=0,c=0,num1=1,num2=1;//num is multiplication factor
        //r and c are current row and column
        string  s;
        st.push(make_pair(1,1));// multiplication factor for while string is initially  one
        // num will increase with sub brackets
        cin>>s;// taking string as input
        for(int i=0; i<s.size(); i++)
        {
            if(s[i]>='0'&&s[i]<='9')
            {
                ll d=s[i]-'0';
                num1=(num1*d)%N;
                num2=(num2*d)%M;// modifying the multiplication factor for a particular bracket by including
                   // all multiplication factors which are in the parent brackets

                st.push(make_pair(num1,num2));// pushing the multiplication factor into the stack
            }
            else if(s[i]=='(')
            {
                continue;
            }
            else if(s[i]==')')
            {
                st.pop(); // taking out the multiplication factor for a particular bracket
                num1=st.top().first;
                num2=st.top().second;
            }
            else
            {
                if(s[i]=='S')
                {
                    r=(r+num1)%N;//i have taken n and m to be mod initially later i will change them
                    // so doing % with mod for both rows and columns so that i have only one multiplication variable
                    // otherwise i have to maintain two stacks one for row and other for column
                }
                else if(s[i]=='N')
                {
                    r=(r-num1);
                    while(r<0)// if r<0 then we will start from end
                        r+=N;
                }
                else if(s[i]=='W')
                {
                    c=c-num2;
                    while(c<0)
                        c+=M;
                }
                else
                {
                    c=(c+num2)%M;
                }
            }
        }
        cout<<(r)%N<<" "<<(c)%M<<endl;// here i have taken modulo w.r.t given m and n
    }
    return 0;
}




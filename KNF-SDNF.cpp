#include <bits/stdc++.h>

#define files(x) ((x != "")? (freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)):(0))
#define fast ios_base::sync_with_stdio(NULL); cin.tie(0); cout.tie(0);
#define pb push_back
#define ft first
#define sd second

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector< pii > vii;
typedef long long ll;

map<char, int> q;
map<string, bool> is;

void func(string s, int a, int b, vi &x, vi &y)
{
    for(int i = 0; i < 4; i++)
        x[i] = 0,
        y[i] = 0;
    for(int i = 0; i < 4; i++)
    {
        int z = 1;
        if(s[a] == '!')
        {
            z = -1;
            a++;
        }
        x[q[s[a]]] = z;
        a++;
        if(a == s.length() || s[a] == '+' || s[a] == ')')
            break;
        //a++;
    }
    for(int i = 0; i < 4; i++)
    {
        int z = 1;
        if(s[b] == '!')
        {
            z = -1;
            b++;
        }
        y[q[s[b]]] = z;
        b++;
        if(b == s.length() || s[b] == '+' || s[b] == ')')
            break;
        //b++;
    }
}

bool rivni(string s, int a, int b)
{
    vi x(4), y(4);
    func(s, a, b, x, y);
    int ok = 0;
    for(int i = 0; i < 4; i++)
        ok += abs(x[i]-y[i]);
    return !ok;
}

bool zero(string s, int a, int b)
{
    vi x(4), y(4);
    func(s, a, b, x, y);
    int dif = 0;
    for(int i = 0; i < 4; i++)
        if(x[i]*y[i] == -1)
            dif++;
    return (dif == 1);
}

string multi(string s, int a, int b)
{
    vi x(4), y(4);
    func(s, a, b, x, y);
    string res = "";
    for(int i = 0; i < 4; i++)
    {
        if(x[i] + y[i] == 0)
            continue;
        int d = (x[i]+y[i])/abs(x[i]+y[i]);
        if(d < 0)
            res.pb('!');
        if(i == 0) res.pb('x');
        if(i == 1) res.pb('y');
        if(i == 2) res.pb('z');
        if(i == 3) res.pb('t');
    }
    return res;
}

void add(string a)
{
    //cerr << a << '\n';
    vi x(4), y(4);
    func(a, 0, 0, x, y);
    int cnt = abs(x[0])+abs(x[1])+abs(x[2])+abs(x[3]);
    if(cnt == 4) return;
    if(!zero(a+")x", 0, a.length()+1) && multi(a+")x", 0, a.length()+1)!= a)
    {
        is[multi(a+")x", 0, a.length()+1)] = 1;
        add(multi(a+")x", 0, a.length()+1));
    }
    if(!zero(a+")!x", 0, a.length()+1) && multi(a+")!x", 0, a.length()+1) != a)
    {
        //if(a == "x") cerr << "%%%%%%%%%%%%%%%55" << multi(a+")x", 0, a.length()+1) << '\n';
        is[multi(a+")!x", 0, a.length()+1)] = 1;
        add(multi(a+")!x", 0, a.length()+1));
    }
    if(!zero(a+")y", 0, a.length()+1) && multi(a+")y", 0, a.length()+1) != a)
    {
        is[multi(a+")y", 0, a.length()+1)] = 1;
        add(multi(a+")y", 0, a.length()+1));
    }
    if(!zero(a+")!y", 0, a.length()+1) && multi(a+")!y", 0, a.length()+1) != a)
    {
        is[multi(a+")!y", 0, a.length()+1)] = 1;
        add(multi(a+")!y", 0, a.length()+1));
    }
    if(!zero(a+")z", 0, a.length()+1) && multi(a+")z", 0, a.length()+1) != a)
    {
        is[multi(a+")z", 0, a.length()+1)] = 1;
        add(multi(a+")z", 0, a.length()+1));
    }
    if(!zero(a+")!z", 0, a.length()+1) && multi(a+")!z", 0, a.length()+1) != a)
    {
        is[multi(a+")!z", 0, a.length()+1)] = 1;
        add(multi(a+")!z", 0, a.length()+1));
    }
    if(!zero(a+")t", 0, a.length()+1) && multi(a+")t", 0, a.length()+1) != a)
    {
        is[multi(a+")t", 0, a.length()+1)] = 1;
        add(multi(a+")t", 0, a.length()+1));
    }
    if(!zero(a+")!t", 0, a.length()+1) && multi(a+")!t", 0, a.length()+1) != a)
    {
        is[multi(a+")!t", 0, a.length()+1)] = 1;
        add(multi(a+")!t", 0, a.length()+1));
    }
}

int main()
{
    #ifdef ANDRII
        freopen("main.in", "r", stdin);
        freopen("main.out", "w", stdout);
    #else
        files("");
    #endif // ANDRII
    q['x'] = 0;
    q['y'] = 1;
    q['z'] = 2;
    q['t'] = 3;
    string s;
    cin >> s;
    string res;
    int i = 0;
    while(i < s.length())
    {
        cout << s << '\n';
        res = "";
        for(i = 0; i < s.length(); i++)
            if(s[i] == '*')
            {
                for(int r = i+2; s[r-1] != ')'; r++)
                {
                    for(int l = 1; l < i-1; l++)
                    {
                        if(!zero(s, l, r))
                        {
                            string dop = multi(s, l, r);
                            res.pb('+');
                            for(auto j:dop)
                                res.pb(j);
                        }
                        while(l < i-1 && s[l] != '+')
                            l++;
                    }
                    while(s[r] != ')' && s[r] != '+')
                        r++;
                }
                //cout << res << '\n';
                for(int j = 1; j < res.length(); j++)
                {
                    string dop = "";
                    while(j < res.length() && res[j] != '+')
                        dop.pb(res[j++]);
                    //cerr << "@@@@@@@@@@@ " << dop << '\n';
                    add(dop);
                }
                string s1 = res;
                res = "";
                for(int j = 1; j < s1.length(); j++)
                {
                    string dop = "";
                    while(j < s1.length() && s1[j] != '+')
                        dop.pb(s1[j++]);
                    cerr << dop << ' ' << is[dop] << '\n';
                    if(!is[dop])
                    {
                        is[dop] = 1;
                        res.pb('+');
                        for(auto o:dop)
                            res.pb(o);
                    }
                }
                res.pb(')');
                int was = 0;
                for(int j = i+2; j < s.length(); j++)
                    if(was)
                        res.pb(s[j]);
                    else if(s[j] == ')')
                        was = 1;
                break;
            }
        is.clear();
        res[0] = '(';
        s = res;
    }
    cout << s;
}

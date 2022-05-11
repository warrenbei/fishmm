#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>
#include <time.h>
#define I u_int64_t
#define bk back()
#define pb push_back
#define ppb pop_back()
#define ticklimit 1000000000
#define hashmod 123456789
I stdIN()
{
    char c;
    return std::cin.get(c)?c:0;
}
std::ifstream _FIN("./fishmm2.in");
I stdFIN()
{
    char c;
    return _FIN.get(c)?c:0;
}
void stdOUT(std::string s)
{
    std::cout << s;
}
std::ofstream _OUT("./fishmm2.out");
void stdFOUT(std::string s)
{
    _OUT << s;
}
std::ofstream _LOG("./fishmm2.log");
void stdLOG(std::string s)
{
    _LOG << s;
}
int fishmm2(std::vector<std::string> prog,
            I(*IN)(), void(*OUT)(std::string), void(*LOG)(std::string),
            int delay=50, bool fastflush=false, bool display=false, bool log=false)
{
    int m=prog.size(), n=prog[0].size(), x=0, y=0, dx=0, dy=1;
    I ticks=0;
    std::vector<std::vector<I> > s;
    s.pb(std::vector<I>());
    if(display)
    {
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++) std::cout<<prog[i][j];
            std::cout<<'\n';
        }
        for(int i=0;i<n;i++) std::cout<<'#';
        std::cout<<'-';
    }
    if(log)
    {
        LOG("Running fishmm 2.0 using ><>-- 2.0\nHash: ");
        long long hash = m^n^142857;
        for(int i=0;i<m;i++) for(int j=0;j<n;j++)
        hash = ((hash+246813579)^(12345*prog[i][j])+hash*123456+i+j+123*m+176*n)%hashmod;
        LOG(std::to_string(hash)+"\n"+std::to_string(m)+"\t"+std::to_string(n)+"\n");
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++) LOG(std::string(1,prog[i][j]));
            LOG("\n");
        }
        LOG("\n");
    }
    while (true)
    {
        if(fastflush)
        {
            std::cout<<std::flush;
            _OUT<<std::flush;
            _LOG<<std::flush;
        }
        if(display)
        {
            std::cout<<"-\n";
            for(int i=0;i<m;i++)
            {
                for(int j=0;j<n;j++) std::cout << ((i==x&&j==y)?'#':prog[i][j]);
                std::cout<<'\n';
            }
            for(int i=0;i<n;i++) std::cout<<'#';
            std::cout<<'-';
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
        char c = prog[x][y]; ticks++;
        if(log)
        {
LOG(std::to_string(ticks)+"\t"+c+"\t"+std::to_string(x)+"\t"+std::to_string(y)+"\t");
for(int i=0;i<s.size();i++)
{
    LOG("[");
    for(int j=0;j<s[i].size();j++) LOG(std::to_string(s[i][j])+",");
    LOG("#");
}
LOG("\n");
        }
             if(c==' '){}
        else if(c==';'){if(log){LOG("Terminated successfully\n");}return 0;}
        else if(c=='<'){dx=0;dy=-1;}
        else if(c=='>'){dx=0;dy=1;}
        else if(c=='^'){dx=-1;dy=0;}
        else if(c=='v'){dx=1;dy=0;}
        else if(c=='/'){std::swap(dx,dy);dx=-dx;dy=-dy;}
        else if(c=='\\'){std::swap(dx,dy);}
        else if(c=='|'){if(dy)dy=-dy;}
        else if(c=='_'){if(dx)dx=-dx;}
        else if(c=='x'){srand(time(NULL));
                        if(dx){dx=0;dy=1-2*(rand()%2);}
                        else{dy=0;dx=1-2*(rand()%2);}}
        else if(c=='!'){x+=dx;y+=dy;}
        else if(c=='?'){if(s.bk.size()==0)return 2;
                        if(s.bk.bk!=0){x+=dx;y+=dy;}
                        s.bk.ppb;}
        else if(c=='&'){if(s.bk.size()==0)return 2;
                        if(s.bk.bk==0){x+=dx;y+=dy;}
                        s.bk.ppb;}
        else if(c>='0'&&c<='9'){s.bk.pb(c-'0');}
        else if(c=='.'){s.bk.pb(32);}
        else if(c=='#'){s.bk.pb(48);}
        else if(c>='A'&&c<='Z'){s.bk.pb(c);}
        else if(c=='+'){if(s.bk.size()<=1)return 2;
                        I y=s.bk.bk;s.bk.ppb;I x=s.bk.bk;
                        s.bk.bk=x+y;}
        else if(c=='-'){if(s.bk.size()<=1)return 2;
                        I y=s.bk.bk;s.bk.ppb;I x=s.bk.bk;
                        if(x<y)return 4;
                        s.bk.bk=x-y;}
        else if(c=='*'){if(s.bk.size()<=1)return 2;
                        I y=s.bk.bk;s.bk.ppb;I x=s.bk.bk;
                        s.bk.bk=x*y;}
        else if(c==','){if(s.bk.size()<=1)return 2;
                        I y=s.bk.bk;s.bk.ppb;I x=s.bk.bk;
                        if(y==0)return 4;
                        s.bk.bk=x/y;}
        else if(c=='%'){if(s.bk.size()<=1)return 2;
                        I y=s.bk.bk;s.bk.ppb;I x=s.bk.bk;
                        if(y==0)return 4;
                        s.bk.bk=x%y;}
        else if(c=='('){if(s.bk.size()<=1)return 2;
                        I y=s.bk.bk;s.bk.ppb;I x=s.bk.bk;
                        s.bk.bk=x<y;}
        else if(c==')'){if(s.bk.size()<=1)return 2;
                        I y=s.bk.bk;s.bk.ppb;I x=s.bk.bk;
                        s.bk.bk=x>y;}
        else if(c=='='){if(s.bk.size()<=1)return 2;
                        I y=s.bk.bk;s.bk.ppb;I x=s.bk.bk;
                        s.bk.bk=x==y;}
        else if(c==':'){if(!s.bk.size())return 2;
                        s.bk.pb(s.bk.bk);}
        else if(c=='~'){if(!s.bk.size())return 2;
                        s.bk.ppb;}
        else if(c=='$'){if(s.bk.size()<=1)return 2;
                        std::swap(s.bk.bk,*(&(s.bk.bk)-1));}
        else if(c=='@'){if(s.bk.size()<=2)return 2;
                        std::swap(s.bk.bk,*(&(s.bk.bk)-1));
                        std::swap(*(&(s.bk.bk)-1),*(&(s.bk.bk)-2));}
        else if(c=='{'){if(s.bk.size())
                        {s.bk.pb(s.bk[0]);
                        s.bk.erase(s.bk.begin());}}
        else if(c=='}'){if(s.bk.size())
                        {s.bk.insert(s.bk.begin(),s.bk.bk);
                        s.bk.ppb;}}
        else if(c=='r'){std::reverse(s.bk.begin(),s.bk.end());}
        else if(c=='l'){s.bk.pb(s.bk.size());}
        else if(c=='['){if(!s.bk.size())return 2;
                        int k=s.bk.bk;s.bk.ppb;
                        if(k>s.bk.size())return 5;
                        std::vector<I> t;
                        while(k--){t.pb(s.bk.bk);s.bk.ppb;}
                        s.pb(t);}
        else if(c==']'){if(s.size()<=1)return 2;
                        std::vector<I> t=s.bk;s.ppb;
                        for(int k=0;k<t.size();k++)s.bk.pb(t[k]);}
        else if(c=='i'){s.bk.pb(IN());}
        else if(c=='o'){if(!s.bk.size())return 2;
                        OUT(std::string(1,char(s.bk.bk)));s.bk.ppb;}
        else if(c=='n'){if(!s.bk.size())return 2;
                        OUT(std::to_string(s.bk.bk));s.bk.ppb;}
        else           {return 1;}
        x+=dx;y+=dy;
        if(x<0||x>=m||y<0||y>=n) return 3;
        if(ticks>=ticklimit) return 6;
    }
}

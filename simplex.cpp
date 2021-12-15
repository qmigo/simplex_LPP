#include<bits/stdc++.h>
using namespace std;
void show(pair<int,int> mat[5][8])
{
    for(int i=1;i<=4;i++)
   {
       for(int j=1;j<=7;j++)
       cout<<mat[i][j].first<<"/"<<mat[i][j].second<<" ";
       cout<<"\n";
   }

}
void entry(pair<int,int> mat[5][8])
{   

    cout<<"Enter eqn to optimise : \t";
    for(int i=1;i<=3;i++)
    {
        cin>>mat[4][i].first;
        mat[4][i].first*=-1;
        mat[4][i].second=1;
    }
    for(int i=1;i<=3;i++)
    {
    cout<<"Enter subject to eqn : "<<i<<"\t";
    for(int j=1;j<=4;j++)
    {   
        if(j==4)
        {
            cin>>mat[i][7].first;
            mat[i][7].second=1;
        }
        else
        {
        cin>>mat[i][j].first;
        mat[i][j].second=1;
        }
    }
    }
    for(int i=1;i<=4;i++)
    for(int j=4;j<=6;j++)
    if(i+3==j)
    {
        mat[i][j].first=1;
        mat[i][j].second=1;
    }
    else
    {
        mat[i][j].first=0;
        mat[i][j].second=1;
    }
    mat[4][7].first=0;
    mat[4][7].second=1;
}

int greatcd(int div,int did)
{   
    
    if(div>did)
    {
        int c;
        c=div;
        div=did;
        did=c;
    }
    if(div==0)
    return 0;

    int rem=did%div;

    if(rem==0)
    return div;

    return greatcd (rem,div);
}
int toppleCol(pair<int,int> mat[5][8])
{
    float least=INTMAX_MAX;
    int pos=0;
    for(int j=1;j<=3;j++)
    {
    float x=mat[4][j].first/mat[4][j].second;
        if(x<least)
        {
            least=x;
            pos=j;
        }
    }
    if(least>=0)
    return 0;

    return pos;
}
int toppleRow(pair<int,int> mat[5][8])
{
    int tc=toppleCol(mat);
    if(tc==0)
    return 0;

    float least=INTMAX_MAX;
    int pos=0;
    for(int i=1;i<=3;i++)
    {   
        
       float x=mat[i][7].first/mat[i][7].second;
       float y=mat[i][tc].first/mat[i][tc].second;
      
       float r=x/y;
       if(r<least && r>0)
       {
            least=r;
            pos=i;
       }
    }
    return pos;
}
void matop1(pair<int,int> mat[5][8])
{
    int tc=toppleCol(mat);
    int tr=toppleRow(mat);
    int num=mat[tr][tc].first;
    int den=mat[tr][tc].second;

    for(int j=1;j<=7;j++)
    {   
        if(mat[tr][j].first==0)
        {
        mat[tr][j].second=1;
        }
        else
        {
        mat[tr][j].first*=den;
        mat[tr][j].second*=num;
        int hcf=greatcd(abs(mat[tr][j].first),mat[tr][j].second);
        if(hcf!=0)
        {
        mat[tr][j].first/=hcf;
        mat[tr][j].second/=hcf;
        }
        }
    }
}
pair <int,int> sum(pair<int,int> left,pair<int,int> right)
{   
    
    int a=left.first;
    int b=left.second;
    int c=right.first;
    int d=right.second;
    
    // cout<<a<<"/"<<b<<"  "<<c<<"/"<<d;
    int e=(a*d)+(b*c);
    int f=(b*d);

    int hcf=greatcd(abs(e),f);
    if(hcf!=0)
    {
    e/=hcf;
    f/=hcf;
    }
    // cout<<" = "<<e<<"/"<<f<<"\n";
    return {e,f};

}
void matop2(pair<int,int> mat[5][8])
{
    int tr=toppleRow(mat);
    int tc=toppleCol(mat);

    for(int i=1;i<=4;i++)
    {
        if(i==tr)
        continue;

    
        int num=((-1)*mat[i][tc].first);
        int den=mat[i][tc].second;
        // cout<<"for "<<i<<"\n";
        
        for(int j=1;j<=7;j++)
        {   
            int x=mat[tr][j].first*num;
            int y=mat[tr][j].second*den;
            
            // cout<<x<<"/"<<y<<" \n";
            
            int hcf=greatcd(abs(x),y);
            if(hcf!=0)
            {
            x/=hcf;
            y/=hcf;
            }
            pair<int,int> temp=sum(mat[i][j],{x,y});
            mat[i][j].first=temp.first;
            mat[i][j].second=temp.second;
            

        }
    }
}

int main()
{
    // Test Case
    // pair<int,int> mat[5][8]={{{0,0},{0,0},{0,0},{0,0},{0,0},{0,0},{0,0}},{{0,0},{4,1},{2,1},{1,1},{1,1},{0,1},{0,1},{60,1}},{{0,0},{2,1},{3,1},{3,1},{0,1},{1,1},{0,1},{50,1}},{{0,0},{1,1},{3,1},{1,1},{0,1},{0,1},{1,1},{45,1}},{{0,0},{-12,1},{-6,1},{-4,1},{0,1},{0,1},{0,1},{0,1}}};

    pair<int,int> mat[5][8];
    entry(mat); 
    int k=1;
    while(1)
    {
        if(toppleCol(mat)==0)
        break;
        cout<<"Pivot Column :\t"<<toppleCol(mat)<<"\n";
        cout<<"Pivot Row :\t"<<toppleRow(mat)<<"\n";
        matop1(mat);
        matop2(mat);
        cout<<"After op "<<k<<" \n\n";
        show(mat);
        cout<<"\n";
        k++;
    }
  

}
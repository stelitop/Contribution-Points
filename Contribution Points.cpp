#include<iostream>
#include<conio.h>
#include<cstdlib>
#include<cstdio>
#include<fstream>
#include<map>
using namespace std;
string mining[1001],smithing[1001],alchemy[1001];
map<string,int> miningprice,smithingprice,alchemyprice;
int amountmining,amountsmithing,amountalchemy,amountplayers,multiplier=35;
string textinput;
struct player
{
    string name;
    map<string,pair<int,int>> mining; /// .first - amount ; .second - CP
    map<string,pair<int,int>> smithing;
    map<string,pair<int,int>> alchemy;
    int currpoints=0;
}players[1001];

string num_to_string(int x)
{
    string a1="";
    if (x==0)
    {
        a1="0";
        return a1;
    }
    while (x>0)
    {
        char a=(x%10+'0');
        a1=a1+a;
        x/=10;
    }
    string a2="";
    for (int i=0;i<a1.size();i++) a2+=a1[a1.size()-i-1];
    return a2;
}

void save()
{
    string data="";
    data+=num_to_string(amountplayers);
    data+=';';
    data+=num_to_string(amountmining);
    data+=';';
    data+=num_to_string(amountsmithing);
    data+=';';
    data+=num_to_string(amountalchemy);
    data+=';';
    for (int i=1;i<=amountplayers;i++)
    {
        data+=players[i].name;
        data+=';';
    }
    for (int i=1;i<=amountmining;i++)
    {
        data+=mining[i];
        data+=';';
    }
    for (int i=1;i<=amountsmithing;i++)
    {
        data+=smithing[i];
        data+=';';
    }
    for (int i=1;i<=amountalchemy;i++)
    {
        data+=alchemy[i];
        data+=';';
    }
    for (int i=1;i<=amountplayers;i++)
    {
        data+="\n:";
        data+=num_to_string(players[i].currpoints);
        data+=';';
        for (int j=1;j<=amountmining;j++)
        {
            data+=num_to_string(players[i].mining[mining[j]].first);
            data+=';';
            data+=num_to_string(players[i].mining[mining[j]].second);
            data+=';';
        }
        for (int j=1;j<=amountsmithing;j++)
        {
            data+=num_to_string(players[i].smithing[smithing[j]].first);
            data+=';';
            data+=num_to_string(players[i].smithing[smithing[j]].second);
            data+=';';
        }
        for (int j=1;j<=amountalchemy;j++)
        {
            data+=num_to_string(players[i].alchemy[alchemy[j]].first);
            data+=';';
            data+=num_to_string(players[i].alchemy[alchemy[j]].second);
            data+=';';
        }
    }
    data+="\n:";
    data+=num_to_string(multiplier);
    data+=';';
    data+="\n:";
    for (int i=1;i<=amountmining;i++)
    {
        data+=num_to_string(miningprice[mining[i]]);
        data+=';';
    }
    data+="\n:";
    for (int i=1;i<=amountsmithing;i++)
    {
        data+=num_to_string(smithingprice[smithing[i]]);
        data+=';';
    }
    data+="\n:";
    for (int i=1;i<=amountalchemy;i++)
    {
        data+=num_to_string(alchemyprice[alchemy[i]]);
        data+=';';
    }
    ofstream openFile("Data.txt");
    openFile<<data;
}

void load_data()
{
    ifstream openFile("Data.txt");
    string x;
    textinput="";
    while(getline(openFile, x))
    {
        textinput+=x;
        textinput+='\n';
    }

    int c=0,num=0;
    while (textinput[c]!=';')
    {
        num=num*10+textinput[c]-'0';
        c++;
    }
    amountplayers=num;
    c++;
    num=0;
    while (textinput[c]!=';')
    {
        num=num*10+textinput[c]-'0';
        c++;
    }
    amountmining=num;
    c++;
    num=0;
    while (textinput[c]!=';')
    {
        num=num*10+textinput[c]-'0';
        c++;
    }
    amountsmithing=num;
    c++;
    num=0;
    while (textinput[c]!=';')
    {
        num=num*10+textinput[c]-'0';
        c++;
    }
    amountalchemy=num;
    c++;
    num=0;
    string name="";
    for (int i=1;i<=amountplayers;)
    {
        if (textinput[c]==';')
        {
            players[i].name=name;
            i++;
            name="";
        }
        else
        {
            name+=textinput[c];
        }
        c++;
    }
    for (int i=1;i<=amountmining;)
    {
        if (textinput[c]==';')
        {
            mining[i]=name;
            i++;
            name="";
        }
        else
        {
            name+=textinput[c];
        }
        c++;
    }
    for (int i=1;i<=amountsmithing;)
    {
        if (textinput[c]==';')
        {
            smithing[i]=name;
            i++;
            name="";
        }
        else
        {
            name+=textinput[c];
        }
        c++;
    }
    for (int i=1;i<=amountalchemy;)
    {
        if (textinput[c]==';')
        {
            alchemy[i]=name;
            i++;
            name="";
        }
        else
        {
            name+=textinput[c];
        }
        c++;
    }
    for (int i=1;i<=amountplayers;i++)
    {
        while (textinput[c]!=':') c++;
        c++;
        num=0;
        while (textinput[c]!=';')
        {
            num=num*10+textinput[c]-'0';
            c++;
        }
        players[i].currpoints=num;
        c++;
        for (int j=1;j<=amountmining*2;j++)
        {
            num=0;
            while (textinput[c]!=';')
            {
                num=num*10+textinput[c]-'0';
                c++;
            }
            c++;
            if (j%2==1) players[i].mining[mining[j/2+1]].first=num;
            else players[i].mining[mining[j/2]].second=num;
        }
        for (int j=1;j<=amountsmithing*2;j++)
        {
            num=0;
            while (textinput[c]!=';')
            {
                num=num*10+textinput[c]-'0';
                c++;
            }
            c++;
            if (j%2==1) players[i].smithing[smithing[j/2+1]].first=num;
            else players[i].smithing[smithing[j/2]].second=num;
        }
        for (int j=1;j<=amountalchemy*2;j++)
        {
            num=0;
            while (textinput[c]!=';')
            {
                num=num*10+textinput[c]-'0';
                c++;
            }
            c++;
            if (j%2==1) players[i].alchemy[alchemy[j/2+1]].first=num;
            else players[i].alchemy[alchemy[j/2]].second=num;
        }
    }
    while(textinput[c]!=':') c++;
    c++;
    num=0;
    while (textinput[c]!=';')
    {
        num=num*10+textinput[c]-'0';
        c++;
    }
    multiplier=num;
    while(textinput[c]!=':') c++;
    c++;
    for (int i=1;i<=amountmining;i++)
    {
        int num=0;
        while (textinput[c]!=';')
        {
            num=num*10+textinput[c]-'0';
            c++;
        }
        miningprice[mining[i]]=num;
        c++;
    }
    while(textinput[c]!=':') c++;
    c++;
    for (int i=1;i<=amountsmithing;i++)
    {
        int num=0;
        while (textinput[c]!=';')
        {
            num=num*10+textinput[c]-'0';
            c++;
        }
        smithingprice[smithing[i]]=num;
        c++;
    }
    while(textinput[c]!=':') c++;
    c++;
    for (int i=1;i<=amountalchemy;i++)
    {
        int num=0;
        while (textinput[c]!=';')
        {
            num=num*10+textinput[c]-'0';
            c++;
        }
        alchemyprice[alchemy[i]]=num;
        c++;
    }
}

void load_profile(player x)
{
    char plmen;
    while (1)
    {
        cout<<"Player : "<<x.name<<endl;
        cout<<"Current Contribution Points : "<<x.currpoints<<endl;
        cout<<endl;
        cout<<"'M'ining Stats"<<endl;
        cout<<"'S'mithing Stats"<<endl;
        cout<<"'A'lchemy Stats"<<endl;
        cout<<endl;
        cout<<"'R'eturn"<<endl;
        plmen=getch();
        system("cls");
        if (plmen=='r' || plmen=='R') break;
        if (plmen=='m' || plmen=='M')
        {
            string morethan0[1001];
            int amount=0;
            for (int i=1;i<=amountmining;i++)
            {
                if (x.mining[mining[i]].first>0)
                {
                    amount++;
                    morethan0[amount]=mining[i];
                }
            }
            char mmenu;
            int pages=(amount-1)/10+1,currpage=1;
            while (1)
            {
                cout<<"Player : "<<x.name<<endl;
                cout<<"Current Contribution Points : "<<x.currpoints<<endl;
                cout<<"Contributed Mining Materials :"<<endl;
                cout<<endl;
                cout<<"Page "<<currpage<<'/'<<pages<<endl;
                for (int i=(currpage-1)*10+1;i<=min(amount,currpage*10);i++)
                {
                    cout<<endl;
                    cout<<morethan0[i]<<" :"<<endl;
                    cout<<"Amount Contributed : "<<x.mining[morethan0[i]].first<<"; CP rewarded : "<<x.mining[morethan0[i]].second<<endl;
                }
                cout<<endl;
                if (pages>1)
                {
                    if (currpage==pages)  cout<<"     'P'revious Page"<<endl;
                    else if (currpage==1) cout<<"                                              'N'ext Page"<<endl;
                    else                  cout<<"     'P'revious Page                          'N'ext Page"<<endl;
                }
                cout<<"'R'eturn"<<endl;
                mmenu=getch();
                system("cls");
                if (mmenu=='r' || mmenu=='R') break;
                if (currpage>1 && (mmenu=='p' || mmenu=='P')) currpage--;
                if (currpage<pages && (mmenu=='n' || mmenu=='N')) currpage++;
            }
        }
        if (plmen=='s' || plmen=='S')
        {
            string morethan0[1001];
            int amount=0;
            for (int i=1;i<=amountsmithing;i++)
            {
                if (x.smithing[smithing[i]].first>0)
                {
                    amount++;
                    morethan0[amount]=smithing[i];
                }
            }
            char mmenu;
            int pages=(amount-1)/10+1,currpage=1;
            while (1)
            {
                cout<<"Player : "<<x.name<<endl;
                cout<<"Current Contribution Points : "<<x.currpoints<<endl;
                cout<<"Contributed Smithing Materials :"<<endl;
                cout<<endl;
                cout<<"Page "<<currpage<<'/'<<pages<<endl;
                for (int i=(currpage-1)*10+1;i<=min(amount,currpage*10);i++)
                {
                    cout<<endl;
                    cout<<morethan0[i]<<" :"<<endl;
                    cout<<"Amount Contributed : "<<x.smithing[morethan0[i]].first<<"; CP rewarded : "<<x.smithing[morethan0[i]].second<<endl;
                }
                cout<<endl;
                if (pages>1)
                {
                    if (currpage==pages)  cout<<"     'P'revious Page"<<endl;
                    else if (currpage==1) cout<<"                                              'N'ext Page"<<endl;
                    else                  cout<<"     'P'revious Page                          'N'ext Page"<<endl;
                }
                cout<<"'R'eturn"<<endl;
                mmenu=getch();
                system("cls");
                if (mmenu=='r' || mmenu=='R') break;
                if (currpage>1 && (mmenu=='p' || mmenu=='P')) currpage--;
                if (currpage<pages && (mmenu=='n' || mmenu=='N')) currpage++;
            }
        }
        if (plmen=='a' || plmen=='A')
        {
            string morethan0[1001];
            int amount=0;
            for (int i=1;i<=amountalchemy;i++)
            {
                if (x.alchemy[alchemy[i]].first>0)
                {
                    amount++;
                    morethan0[amount]=alchemy[i];
                }
            }
            char mmenu;
            int pages=(amount-1)/10+1,currpage=1;
            while (1)
            {
                cout<<"Player : "<<x.name<<endl;
                cout<<"Current Contribution Points : "<<x.currpoints<<endl;
                cout<<"Contributed Alchemy Materials :"<<endl;
                cout<<endl;
                cout<<"Page "<<currpage<<'/'<<pages<<endl;
                for (int i=(currpage-1)*10+1;i<=min(amount,currpage*10);i++)
                {
                    cout<<endl;
                    cout<<morethan0[i]<<" :"<<endl;
                    cout<<"Amount Contributed : "<<x.alchemy[morethan0[i]].first<<"; CP rewarded : "<<x.alchemy[morethan0[i]].second<<endl;
                }
                cout<<endl;
                if (pages>1)
                {
                    if (currpage==pages)  cout<<"     'P'revious Page"<<endl;
                    else if (currpage==1) cout<<"                                              'N'ext Page"<<endl;
                    else                  cout<<"     'P'revious Page                          'N'ext Page"<<endl;
                }
                cout<<"'R'eturn"<<endl;
                mmenu=getch();
                system("cls");
                if (mmenu=='r' || mmenu=='R') break;
                if (currpage>1 && (mmenu=='p' || mmenu=='P')) currpage--;
                if (currpage<pages && (mmenu=='n' || mmenu=='N')) currpage++;
            }
        }
    }
}

void add_player (string x)
{
    amountplayers++;
    players[amountplayers].name=x;
    system("cls");
    save();
    cout<<x<<" has been successfully added to the players list!"<<endl;
    system("pause");
    system("cls");
}

void remove_player (int x)
{
    string name=players[x].name;
    if (x==amountplayers) players[x]=players[0];
    amountplayers--;
    for (int i=x;i<=amountplayers;i++) players[i]=players[i+1];
    system("cls");
    cout<<name<<"'s profile has been successfully removed!"<<endl;
    save();
    system("pause");
    system("cls");
}

void add_item (int type)
{
    system("cls");
    string newit;
    cout<<"Type the name of the item you want to be added to the ";
    if (type==1) cout<<"mining ";
    if (type==2) cout<<"smithing ";
    if (type==3) cout<<"alchemy ";
    cout<<"database."<<endl;
    getline(cin,newit);
    system("cls");
    char yn;
    while (yn!='y' && yn!='Y' && yn!='n' && yn!='N')
    {
        cout<<"Are you sure that you want to add "<<newit<<" to the ";
        if (type==1) cout<<"mining ";
        if (type==2) cout<<"smithing ";
        if (type==3) cout<<"alchemy ";
        cout<<"database?"<<endl;
        cout<<"                       'Y'es or 'N'o"<<endl;
        yn=getch();
    }
    system("cls");
    if (yn=='y' || yn=='Y')
    {
        if (type==1)
        {
            amountmining++;
            mining[amountmining]=newit;
        }
        if (type==2)
        {
            amountsmithing++;
            smithing[amountsmithing]=newit;
        }
        if (type==3)
        {
            amountalchemy++;
            alchemy[amountalchemy]=newit;
        }
        int number=0;
        cout<<"Type a selling price for the new item"<<endl;
        cout<<"Note : If the amount is less than 0 it will be automatically change to 0"<<endl;
        cout<<"Note : The purchase price will be automatically calculated"<<endl;
        cin>>number;
        number=max(number,0);
        if (type==1) miningprice[mining[amountmining]]=number;
        if (type==2) smithingprice[smithing[amountsmithing]]=number;
        if (type==3) alchemyprice[alchemy[amountalchemy]]=number;
        system("cls");
        cout<<newit<<" has been successfully added to the database!"<<endl;
        system("pause");
        system("cls");
    }
    save();
}

void remove_item (int x,int type)
{
    char yn;
    system("cls");
    while (yn!='y' && yn!='Y' && yn!='n' && yn!='N')
    {
        cout<<"Are you sure that you want to remove '";
        if (type==1) cout<<mining[x];
        if (type==2) cout<<smithing[x];
        if (type==3) cout<<alchemy[x];
        cout<<"' from the database?"<<endl;
        cout<<"Warning : Readding the item won't return the database of it"<<endl;
        cout<<"                       'Y'es or 'N'o"<<endl;
        yn=getch();
        system("cls");
    }
    if (yn=='y' || yn=='Y')
    {
        if (type==1)
        {
            cout<<mining[x]<<" has been successfully removed from the database!"<<endl;
            for (int i=1;i<=amountplayers;i++)
            {
                players[i].mining[mining[x]].first=0;
                players[i].mining[mining[x]].second=0;
            }
            if (x==amountmining) mining[x]=mining[0];
            else for (int i=x;i<=amountmining;i++) mining[i]=mining[i+1];
            amountmining--;
        }
        if (type==2)
        {
            cout<<smithing[x]<<" has been successfully removed from the database!"<<endl;
            for (int i=1;i<=amountplayers;i++)
            {
                players[i].smithing[smithing[x]].first=0;
                players[i].smithing[smithing[x]].second=0;
            }
            if (x==amountsmithing) smithing[x]=smithing[0];
            else for (int i=x;i<=amountsmithing;i++) smithing[i]=smithing[i+1];
            amountsmithing--;
        }
        if (type==3)
        {
            cout<<alchemy[x]<<" has been successfully removed from the database!"<<endl;
            for (int i=1;i<=amountplayers;i++)
            {
                players[i].alchemy[alchemy[x]].first=0;
                players[i].alchemy[alchemy[x]].second=0;
            }
            if (x==amountalchemy) alchemy[x]=alchemy[0];
            else for (int i=x;i<=amountalchemy;i++) alchemy[i]=alchemy[i+1];
            amountalchemy--;
        }
    }
    save();
}

/// 1 - Mining ; 2 - Smithing ; 3 - Alchemy

void update_material (int num, int type, int p)
{
    while (1)
    {
        char fff;
        cout<<"Material Chosen : ";
        if (type==1) cout<<mining[num]<<endl;
        if (type==2) cout<<smithing[num]<<endl;
        if (type==3) cout<<alchemy[num]<<endl;
        cout<<"'U'pdate contributed amount"<<endl;
        ///cout<<"'C'hange raw stats"<<endl;
        cout<<"'R'eturn"<<endl;
        fff=getch();
        system("cls");
        if (fff=='r' || fff=='R') break;
        if (fff=='u' || fff=='U')
        {
            int number;
            cout<<"Type the amount of ";
            if (type==1) cout<<mining[num];
            if (type==2) cout<<smithing[num];
            if (type==3) cout<<alchemy[num];
            cout<<' '<<players[p].name<<" will receive"<<endl;
            cout<<"Note : Amounts less than 0 will be changed to 0"<<endl;
            cout<<"Note : The CP will be automatically updated depending on the current price of the item"<<endl;
            cin>>number;
            number=max(number,0);
            system("cls");
            int contr=0;
            if (type==1) contr=number*miningprice[mining[num]];
            if (type==2) contr=number*smithingprice[smithing[num]];
            if (type==3) contr=number*alchemyprice[alchemy[num]];
            cout<<'x'<<number<<' ';
            if (type==1) cout<<mining[num];
            if (type==2) cout<<smithing[num];
            if (type==3) cout<<alchemy[num];
            cout<<" has been successfully added to the player's profile! He receives "<<contr<<" Contribution Points for the contribution!"<<endl;
            players[p].currpoints+=contr;
            if (type==1)
            {
                players[p].mining[mining[num]].first+=number;
                players[p].mining[mining[num]].second+=contr;
            }
            if (type==2)
            {
                players[p].smithing[smithing[num]].first+=number;
                players[p].smithing[smithing[num]].second+=contr;
            }
            if (type==3)
            {
                players[p].alchemy[alchemy[num]].first+=number;
                players[p].alchemy[alchemy[num]].second+=contr;
            }
        }

        /**if (fff=='c' || fff=='C')
        {
            int number;
            cout<<"Type the new amount of ";
            if (type==1) cout<<mining[num];
            if (type==2) cout<<smithing[num];
            if (type==3) cout<<alchemy[num];
            cout<<" that will be shown in "<<players[p].name<<"'s profile as contributed"<<endl;
            cout<<"Note : Amounts less than 0 will be changed to 0"<<endl;
            cout<<"Note : The CP stat won't be affected by the new amount"<<endl;
            cin>>number;
            number=max(0,number);
        }*/
    }
    save();
}

void update_player (int x)
{
    char u;
    while (1)
    {
        cout<<"Selected Player : "<<players[x].name<<endl;
        cout<<endl;
        cout<<"'U'pdate Player's Statistic"<<endl;
        cout<<"'A'dd CP"<<endl;
        cout<<"'T'ake CP"<<endl;
        cout<<"'R'eturn"<<endl;
        u=getch();
        system("cls");
        if (u=='r' || u=='R') break;
        if (u=='a' || u=='A')
        {
            int num;
            cout<<"Type the amount of CP "<<players[x].name<<" will receive"<<endl;
            cout<<"Tip : You can use this if you mistyped the amount of CP to be taken"<<endl;
            cout<<"Note : Amounts less than 0 will be changed to 0"<<endl;
            cout<<endl;
            cin>>num;
            num=max(num,0);
            players[x].currpoints+=num;
            system("cls");
            cout<<players[x].name<<" has successfully received "<<num<<" Contribution Points!"<<endl;
            system("pause");
            system("cls");
        }
        if (u=='t' || u=='T')
        {
            int num;
            cout<<"Type the amount of CP that will be taken from "<<players[x].name<<"'s profile"<<endl;
            cout<<"Tip : Use it after the players has made a transaction"<<endl;
            cout<<"Note : Amounts less than 0 will be changed to 0"<<endl;
            cout<<endl;
            cin>>num;
            num=max(num,0);
            players[x].currpoints-=num;
            system("cls");
            cout<<num<<" CP has been successfully taken from "<<players[x].name<<"'s profile!"<<endl;
            system("pause");
            system("cls");
        }
        if (u=='u' || u=='U')
        {
            char upm;
            while (1)
            {
                cout<<"Note : Updating the contributed amount will automatically give CP. Changing the raw stats won't"<<endl;
                cout<<"Select group of materials :"<<endl;
                cout<<"(1) Mining"<<endl;
                cout<<"(2) Smithing"<<endl;
                cout<<"(3) Alchemy"<<endl;
                cout<<"'R'eturn"<<endl;
                upm=getch();
                system("cls");
                char m=' ';
                if (upm=='r' || upm=='R') break;
                if (upm=='1')
                {
                    int currpage=1,pages=(amountmining-1)/10+1;
                    while (1)
                    {
                        cout<<"Click on the number in brackets to update the stats about the chosen material"<<endl;
                        cout<<"Page "<<currpage<<'/'<<pages<<endl;
                        cout<<"List of mining materials :"<<endl;
                        cout<<endl;
                        for (int i=(currpage-1)*10+1 ; i <= min(amountmining,currpage*10); i++)
                            cout<<'('<<i%10<<')'<<' '<<mining[i]<<"; Current Amount Contributed : "<<players[x].mining[mining[i]].first<<endl;
                        cout<<endl;
                        if (pages>1)
                        {
                            if (currpage==pages) cout<<"   'P'revious Page                      "<<endl;
                            else if (currpage==1) cout<<"                             'N'ext page"<<endl;
                            else cout<<"   'P'revious Page           'N'ext page"<<endl;
                        }
                        cout<<"'R'eturn"<<endl;
                        m=getch();
                        system("cls");
                        if (m=='r' || m=='R') break;
                        if ((m=='p' || m=='P') && currpage>1) currpage--;
                        if ((m=='n' || m=='N') && currpage<pages) currpage++;
                        if ((m>='1' && m<='9' && (currpage-1)*10+m-'0'<=amountmining) || (m=='0' && currpage*10<+amountmining))
                        {
                            int slot=(currpage-1)*10+m-'0';
                            if (m=='0') slot+=10;
                            update_material(slot,1,x);
                        }
                    }
                }
                if (upm=='2')
                {
                    int currpage=1,pages=(amountsmithing-1)/10+1;
                    while (1)
                    {
                        cout<<"Click on the number in brackets to update the stats about the chosen material"<<endl;
                        cout<<"Page "<<currpage<<'/'<<pages<<endl;
                        cout<<"List of smithing materials :"<<endl;
                        cout<<endl;
                        for (int i=(currpage-1)*10+1 ; i <= min(amountsmithing,currpage*10); i++)
                            cout<<'('<<i%10<<')'<<' '<<smithing[i]<<"; Current Amount Contributed : "<<players[x].smithing[smithing[i]].first<<endl;
                        cout<<endl;
                        if (pages>1)
                        {
                            if (currpage==pages) cout<<"   'P'revious Page                      "<<endl;
                            else if (currpage==1) cout<<"                             'N'ext page"<<endl;
                            else cout<<"   'P'revious Page           'N'ext page"<<endl;
                        }
                        cout<<"'R'eturn"<<endl;
                        m=getch();
                        system("cls");
                        if (m=='r' || m=='R') break;
                        if ((m=='p' || m=='P') && currpage>1) currpage--;
                        if ((m=='n' || m=='N') && currpage<pages) currpage++;
                        if ((m>='1' && m<='9' && (currpage-1)*10+m-'0'<=amountsmithing) || (m=='0' && currpage*10<+amountsmithing))
                        {
                            int slot=(currpage-1)*10+m-'0';
                            if (m=='0') slot+=10;
                            update_material(slot,2,x);
                        }
                    }
                }
                if (upm=='3')
                {
                    int currpage=1,pages=(amountmining-1)/10+1;
                    while (1)
                    {
                        cout<<"Click on the number in brackets to update the stats about the chosen material"<<endl;
                        cout<<"Page "<<currpage<<'/'<<pages<<endl;
                        cout<<"List of alchemy materials :"<<endl;
                        cout<<endl;
                        for (int i=(currpage-1)*10+1 ; i <= min(amountalchemy,currpage*10); i++)
                            cout<<'('<<i%10<<')'<<' '<<alchemy[i]<<"; Current Amount Contributed : "<<players[x].alchemy[alchemy[i]].first<<endl;
                        cout<<endl;
                        if (pages>1)
                        {
                            if (currpage==pages) cout<<"   'P'revious Page                      "<<endl;
                            else if (currpage==1) cout<<"                             'N'ext page"<<endl;
                            else cout<<"   'P'revious Page           'N'ext page"<<endl;
                        }
                        cout<<"'R'eturn"<<endl;
                        m=getch();
                        system("cls");
                        if (m=='r' || m=='R') break;
                        if ((m=='p' || m=='P') && currpage>1) currpage--;
                        if ((m=='n' || m=='N') && currpage<pages) currpage++;
                        if ((m>='1' && m<='9' && (currpage-1)*10+m-'0'<=amountalchemy) || (m=='0' && currpage*10<+amountalchemy))
                        {
                            int slot=(currpage-1)*10+m-'0';
                            if (m=='0') slot+=10;
                            update_material(slot,3,x);
                        }
                    }
                }
            }
        }
    }
    save();
}

int main ()
{
    load_data();
    while(1)
    {
        char menu;
        cout<<"'P'layer Base"<<endl;
        cout<<"'I'tems"<<endl;
        //cout<<"'H'elp and navigation"<<endl;
        cout<<"'S'ave"<<endl;
        menu=getch();
        system("cls");
        if (menu=='p' || menu=='P')
        {
            while (1)
            {
                char plm;
                cout<<"'P'layer statistics"<<endl;
                cout<<"'A'dd a player"<<endl;
                cout<<"'D'elete a player's profile"<<endl;
                cout<<"'U'pdate a player's profile"<<endl;
                cout<<"'R'eturn"<<endl;
                plm=getch();
                system("cls");
                if (plm=='r' || plm=='R') break;
                if (plm=='p' || plm=='P')
                {
                    int lpages=(amountplayers-1)/10+1,lcurrpage=1;
                    char lmenu;
                    while (1)
                    {
                        cout<<"Click on the number in brackets to see the player's profile"<<endl;
                        cout<<"Page "<<lcurrpage<<'/'<<lpages<<endl;
                        cout<<"List of players :"<<endl;
                        cout<<endl;
                        for (int i=(lcurrpage-1)*10+1 ; i <= min(amountplayers,lcurrpage*10); i++)
                        {
                            cout<<'('<<i%10<<')'<<' '<<players[i].name<<endl;
                        }
                        cout<<endl;
                        if (lpages>1)
                        {
                            if (lcurrpage==lpages) cout<<"   'P'revious Page                      "<<endl;
                            else if (lcurrpage==1) cout<<"                             'N'ext page"<<endl;
                            else cout<<"   'P'revious Page           'N'ext page"<<endl;
                        }
                        cout<<"'R'eturn"<<endl;
                        lmenu=getch();
                        system("cls");
                        if (lmenu=='r' || lmenu=='R') break;
                        if ((lmenu>='1' && lmenu<='9' && lmenu-'0'+10*(lcurrpage-1)*10<=amountplayers) || (lmenu=='0' && lcurrpage*10<=amountplayers))
                        {
                            int currpl=(lcurrpage-1)*10+lmenu-'0';
                            if (lmenu=='0') currpl+=10;
                            load_profile(players[currpl]);
                        }
                    }
                }
                if (plm=='a' || plm=='A')
                {
                    string newplayer;
                    cout<<"Type the name of the player you want to add. Type 'cancel' if you don't want to add any."<<endl;
                    getline(cin,newplayer);
                    system("cls");
                    if (newplayer!="cancel")
                    {
                        char yn;
                        while (1)
                        {
                            cout<<"Are you sure that you want to add '"<<newplayer<<"' in the player list? (it can be removed later)"<<endl;
                            cout<<"                                           'Y'es or 'N'o?"<<endl;
                            yn=getch();
                            system("cls");
                            if (yn=='n' || yn=='N') break;
                            if (yn=='y' || yn=='Y')
                            {
                                add_player(newplayer);
                                break;
                            }

                        }
                    }
                }
                if (plm=='d' || plm=='D')
                {
                    char rmpl;
                    int currpage=1,pages=(amountplayers-1)/10+1;
                    while (1)
                    {
                        cout<<"Click on the number in brackets to delete the player"<<endl;
                        cout<<"Page "<<currpage<<'/'<<pages<<endl;
                        cout<<"List of players :"<<endl;
                        cout<<endl;
                        for (int i=(currpage-1)*10+1;i<=min(amountplayers,currpage*10);i++)
                            cout<<'('<<i%10<<')'<<' '<<players[i].name<<endl;
                        cout<<endl;
                        if (pages>1)
                        {
                            if (currpage==1)          cout<<"                                   'N'ext Page"<<endl;
                            else if (currpage==pages) cout<<"      'P'revious Page                         "<<endl;
                            else                      cout<<"      'P'revious Page              'N'ext Page"<<endl;
                        }
                        cout<<"'R'eturn"<<endl;
                        rmpl=getch();
                        system("cls");
                        if (rmpl=='r' || rmpl=='R') break;
                        if ((rmpl=='n' || rmpl=='N') && currpage<pages) currpage++;
                        if ((rmpl=='p' || rmpl=='P') && currpage>1) currpage--;
                        if ((rmpl>='1' && rmpl<='9' && (currpage-1)*10+rmpl-'0'<=amountplayers) || (rmpl=='0' && currpage*10<=amountplayers))
                        {
                            int pl=(currpage-1)*10+rmpl-'0';
                            if (rmpl=='0') pl+=10;
                            while (1)
                            {
                                char yn;
                                cout<<"Are you sure that you want to delete "<<players[pl].name<<"'s profile? (Readding it won't return the old stats)"<<endl;
                                cout<<"                                           'Y'es or 'N'o?"<<endl;
                                yn=getch();
                                system("cls");
                                if (yn=='n' || yn=='N') break;
                                if (yn=='y' || yn=='Y')
                                {
                                    remove_player(pl);
                                    break;
                                }
                            }
                        }
                    }
                }
                if (plm=='u' || plm=='U')
                {
                    char upd;
                    int pages=(amountplayers-1)/10+1,currpage=1;
                    while (1)
                    {
                        cout<<"List of players"<<endl;
                        cout<<"Page "<<currpage<<'/'<<pages<<endl;
                        cout<<endl;
                        for (int i=(currpage-1)*10+1;i<=min(amountplayers,currpage*10);i++)
                            cout<<'('<<i%10<<") "<<players[i].name<<endl;
                        cout<<endl;
                        if (pages>1)
                        {
                            if (currpage==pages) cout<<"   'P'revious Page"<<endl;
                            else if (currpage==1) cout<<"                                   'N'ext Page"<<endl;
                            else cout<<"   'P'revious Page                 'N'ext Page"<<endl;
                        }
                        cout<<"'R'eturn"<<endl;
                        upd=getch();
                        system("cls");
                        if (upd=='r' || upd=='R') break;
                        if ((upd=='p' || upd=='P') && currpage>1) currpage--;
                        if ((upd=='n' || upd=='N') && currpage<pages) currpage++;
                        if ((upd>='1' && upd<='9' && (currpage-1)*10+upd-'0'<=amountplayers) || (upd=='0' && currpage*10<amountplayers))
                        {
                            int num=(currpage-1)*10+upd-'0';
                            if (upd=='0') num+=10;
                            update_player(num);
                        }
                    }
                }
            }
        }

        if (menu=='i' || menu=='I')
        {
            while(1)
            {
                char mat;
                cout<<"'L'ist of items"<<endl;
                cout<<"'I'tem Prices"<<endl;
                cout<<"'A'dd an Item"<<endl;
                cout<<"'D'elete an Item"<<endl;
                cout<<"'R'eturn"<<endl;
                mat=getch();
                system("cls");
                if (mat=='r' || mat=='R') break;
                if (mat=='l' || mat=='L')
                {
                    while (1)
                    {
                        char fff;
                        cout<<"Select the group of items you want to see"<<endl;
                        cout<<endl;
                        cout<<"(1) Mining"<<endl;
                        cout<<"(2) Smithing"<<endl;
                        cout<<"(3) Alchemy"<<endl;
                        cout<<endl;
                        cout<<"'R'eturn"<<endl;
                        fff=getch();
                        system("cls");
                        if (fff=='r' || fff=='R') break;
                        if (fff=='1')
                        {
                            char iii;
                            int pages=(amountmining-1)/10+1,currpage=1;
                            while (1)
                            {
                                cout<<"List of all mining materials"<<endl;
                                cout<<"Click the number to see more information"<<endl;
                                cout<<"Page "<<currpage<<'/'<<pages<<endl;
                                cout<<endl;
                                for (int i=(currpage-1)*10+1;i<=min(amountmining,currpage*10);i++)
                                    cout<<'('<<i%10<<") "<<mining[i]<<" - Sell Price : "<<miningprice[mining[i]]<<"; Purchase Price : "<<miningprice[mining[i]]*(multiplier+100)/100<<endl;
                                cout<<endl;
                                if (pages>1)
                                {
                                    if (currpage==pages)  cout<<"    'P'revious Page"<<endl;
                                    else if (currpage==1) cout<<"                                'N'ext Page"<<endl;
                                    else                  cout<<"    'P'revious Page             'N'ext Page"<<endl;
                                }
                                cout<<"'R'eturn"<<endl;
                                iii=getch();
                                system("cls");
                                if (iii=='r' || iii=='R') break;
                                if ((iii=='p' || iii=='P') && currpage>1) currpage--;
                                if ((iii=='n' || iii=='N') && currpage<pages) currpage++;
                                if ((iii>='1' && iii<='9' && (currpage-1)*10+iii-'0'<=amountmining) || (iii=='0' && currpage*10<=amountmining))
                                {
                                    int slot=(currpage-1)*10+iii-'0';
                                    if (iii=='0') slot+=10;
                                    cout<<"Mining Material : "<<mining[slot]<<endl;
                                    cout<<endl;
                                    int num=0;
                                    for (int i=1;i<=amountplayers;i++)
                                    {
                                        num+=players[i].mining[mining[slot]].first;
                                    }
                                    cout<<"Total Amount Contributed : "<<num<<endl;
                                    num=0;
                                    for (int i=1;i<=amountplayers;i++)
                                    {
                                        num+=players[i].mining[mining[slot]].second;
                                    }
                                    cout<<"Total CP rewarded from contributed "<<mining[slot]<<" : "<<num<<endl;
                                    cout<<"Current Sell Price : "<<miningprice[mining[slot]]<<" CP"<<endl;
                                    cout<<"Current Purchase Price : "<<miningprice[mining[slot]]*multiplier<<" CP"<<endl;
                                    system("pause");
                                    system("cls");
                                }
                            }
                        }
                        if (fff=='2')
                        {
                            char iii;
                            int pages=(amountsmithing-1)/10+1,currpage=1;
                            while (1)
                            {
                                cout<<"List of all smithing materials"<<endl;
                                cout<<"Click the number to see more information"<<endl;
                                cout<<"Page "<<currpage<<'/'<<pages<<endl;
                                cout<<endl;
                                for (int i=(currpage-1)*10+1;i<=min(amountsmithing,currpage*10);i++)
                                    cout<<'('<<i%10<<") "<<smithing[i]<<" - Sell Price : "<<smithingprice[smithing[i]]<<"; Purchase Price : "<<smithingprice[smithing[i]]*(multiplier+100)/100<<endl;
                                cout<<endl;
                                if (pages>1)
                                {
                                    if (currpage==pages)  cout<<"    'P'revious Page"<<endl;
                                    else if (currpage==1) cout<<"                                'N'ext Page"<<endl;
                                    else                  cout<<"    'P'revious Page             'N'ext Page"<<endl;
                                }
                                cout<<"'R'eturn"<<endl;
                                iii=getch();
                                system("cls");
                                if (iii=='r' || iii=='R') break;
                                if ((iii=='p' || iii=='P') && currpage>1) currpage--;
                                if ((iii=='n' || iii=='N') && currpage<pages) currpage++;
                                if ((iii>='1' && iii<='9' && (currpage-1)*10+iii-'0'<=amountsmithing) || (iii=='0' && currpage*10<=amountsmithing))
                                {
                                    int slot=(currpage-1)*10+iii-'0';
                                    if (iii=='0') slot+=10;
                                    cout<<"Smithing Material : "<<smithing[slot]<<endl;
                                    cout<<endl;
                                    int num=0;
                                    for (int i=1;i<=amountplayers;i++)
                                    {
                                        num+=players[i].smithing[smithing[slot]].first;
                                    }
                                    cout<<"Total Amount Contributed : "<<num<<endl;
                                    num=0;
                                    for (int i=1;i<=amountplayers;i++)
                                    {
                                        num+=players[i].smithing[smithing[slot]].second;
                                    }
                                    cout<<"Total CP rewarded from contributed "<<smithing[slot]<<" : "<<num<<endl;
                                    cout<<"Current Sell Price : "<<smithingprice[smithing[slot]]<<" CP"<<endl;
                                    cout<<"Current Purchase Price : "<<smithingprice[smithing[slot]]*multiplier<<" CP"<<endl;
                                    system("pause");
                                    system("cls");
                                }
                            }
                        }
                        if (fff=='3')
                        {
                            char iii;
                            int pages=(amountalchemy-1)/10+1,currpage=1;
                            while (1)
                            {
                                cout<<"List of all alchemy materials"<<endl;
                                cout<<"Click the number to see more information"<<endl;
                                cout<<"Page "<<currpage<<'/'<<pages<<endl;
                                cout<<endl;
                                for (int i=(currpage-1)*10+1;i<=min(amountalchemy,currpage*10);i++)
                                    cout<<'('<<i%10<<") "<<alchemy[i]<<" - Sell Price : "<<alchemyprice[alchemy[i]]<<"; Purchase Price : "<<alchemyprice[alchemy[i]]*(multiplier+100)/100<<endl;
                                cout<<endl;
                                if (pages>1)
                                {
                                    if (currpage==pages)  cout<<"    'P'revious Page"<<endl;
                                    else if (currpage==1) cout<<"                                'N'ext Page"<<endl;
                                    else                  cout<<"    'P'revious Page             'N'ext Page"<<endl;
                                }
                                cout<<"'R'eturn"<<endl;
                                iii=getch();
                                system("cls");
                                if (iii=='r' || iii=='R') break;
                                if ((iii=='p' || iii=='P') && currpage>1) currpage--;
                                if ((iii=='n' || iii=='N') && currpage<pages) currpage++;
                                if ((iii>='1' && iii<='9' && (currpage-1)*10+iii-'0'<=amountsmithing) || (iii=='0' && currpage*10<=amountsmithing))
                                {
                                    int slot=(currpage-1)*10+iii-'0';
                                    if (iii=='0') slot+=10;
                                    cout<<"Alchemy Material : "<<alchemy[slot]<<endl;
                                    cout<<endl;
                                    int num=0;
                                    for (int i=1;i<=amountplayers;i++)
                                    {
                                        num+=players[i].alchemy[alchemy[slot]].first;
                                    }
                                    cout<<"Total Amount Contributed : "<<num<<endl;
                                    num=0;
                                    for (int i=1;i<=amountplayers;i++)
                                    {
                                        num+=players[i].alchemy[alchemy[slot]].second;
                                    }
                                    cout<<"Total CP rewarded from contributed "<<alchemy[slot]<<" : "<<num<<endl;
                                    cout<<"Current Sell Price : "<<alchemyprice[alchemy[slot]]<<" CP"<<endl;
                                    cout<<"Current Purchase Price : "<<alchemyprice[alchemy[slot]]*multiplier<<" CP"<<endl;
                                    system("pause");
                                    system("cls");
                                }
                            }
                        }
                    }
                }
                if (mat=='i' || mat=='I')
                {
                    char iii;
                    while (1)
                    {
                        cout<<"Choose a group of items :"<<endl;
                        cout<<endl;
                        cout<<"(1) Mining"<<endl;
                        cout<<"(2) Smithing"<<endl;
                        cout<<"(3) Alchemy"<<endl;
                        cout<<endl;
                        cout<<"'C'hange Purchase Multiplier"<<endl;
                        cout<<"Current Multiplier : "<<multiplier<<endl;
                        cout<<"'R'eturn"<<endl;
                        iii=getch();
                        system("cls");
                        if (iii=='r' || iii=='R') break;
                        if (iii=='c' || iii=='C')
                        {
                            int number;
                            cout<<"Type the PERCENTAGE that will be added when calculating cost from purchasing."<<endl;
                            cout<<"Input a negative number to NOT change the current amount"<<endl;
                            cout<<"Example : Cost = 1000; Multiplier = 35%; Purchase Cost : 1350"<<endl;
                            cout<<"Note : You mustn't add '%' at the end (it will break everything)"<<endl;
                            cin>>number;
                            system("cls");
                            if (number>=0)
                            {
                                multiplier=number;
                                cout<<"You successfully changed the purchase multiplier!"<<endl;
                            }
                            else cout<<"The current multiplier hasn't been changed."<<endl;
                            system("pause");
                            system("cls");
                        }
                        if (iii=='1')
                        {
                            char jjj;
                            int pages=(amountmining-1)/10+1,currpage=1;
                            while (1)
                            {
                                cout<<"List of all mining materials"<<endl;
                                cout<<"Click the number to change the prices"<<endl;
                                cout<<"Page "<<currpage<<'/'<<pages<<endl;
                                cout<<endl;
                                for (int i=(currpage-1)*10+1;i<=min(amountmining,currpage*10);i++)
                                    cout<<'('<<i%10<<") "<<mining[i]<<" - Sell Price : "<<miningprice[mining[i]]<<"; Purchase Price : "<<miningprice[mining[i]]*(multiplier+100)/100<<endl;
                                cout<<endl;
                                if (pages>1)
                                {
                                    if (currpage==pages)  cout<<"    'P'revious Page"<<endl;
                                    else if (currpage==1) cout<<"                                'N'ext Page"<<endl;
                                    else                  cout<<"    'P'revious Page             'N'ext Page"<<endl;
                                }
                                cout<<"'R'eturn"<<endl;
                                jjj=getch();
                                system("cls");
                                if (jjj=='r' || jjj=='R') break;
                                if ((jjj=='p' || jjj=='P') && currpage>1) currpage--;
                                if ((jjj=='n' || jjj=='N') && currpage<pages) currpage++;
                                if ((jjj>='1' && jjj<='9' && (currpage-1)*10+jjj-'0'<=amountmining) || (jjj=='0' && currpage*10<=amountmining))
                                {
                                    int slot=(currpage-1)*10+jjj-'0';
                                    if (jjj=='0') slot+=10;
                                    int number;
                                    cout<<"Enter the new selling price for the "<<mining[slot]<<endl;
                                    cout<<"Note : The purchase price will be automatically changed by the multiplier"<<endl;
                                    cout<<"Note : Amounts less than 0 will be automatically changed to 0"<<endl;
                                    cin>>number;
                                    number=max(number,0);
                                    miningprice[mining[slot]]=number;
                                    system("cls");
                                    cout<<"The price of the "<<mining[slot]<<" has been successfully changed!"<<endl;
                                    system("pause");
                                    system("cls");
                                }
                            }
                        }
                        if (iii=='2')
                        {
                            char jjj;
                            int pages=(amountsmithing-1)/10+1,currpage=1;
                            while (1)
                            {
                                cout<<"List of all smithing materials"<<endl;
                                cout<<"Click the number to change the prices"<<endl;
                                cout<<"Page "<<currpage<<'/'<<pages<<endl;
                                cout<<endl;
                                for (int i=(currpage-1)*10+1;i<=min(amountsmithing,currpage*10);i++)
                                    cout<<'('<<i%10<<") "<<smithing[i]<<" - Sell Price : "<<smithingprice[smithing[i]]<<"; Purchase Price : "<<smithingprice[smithing[i]]*(multiplier+100)/100<<endl;
                                cout<<endl;
                                if (pages>1)
                                {
                                    if (currpage==pages)  cout<<"    'P'revious Page"<<endl;
                                    else if (currpage==1) cout<<"                                'N'ext Page"<<endl;
                                    else                  cout<<"    'P'revious Page             'N'ext Page"<<endl;
                                }
                                cout<<"'R'eturn"<<endl;
                                jjj=getch();
                                system("cls");
                                if (jjj=='r' || jjj=='R') break;
                                if ((jjj=='p' || jjj=='P') && currpage>1) currpage--;
                                if ((jjj=='n' || jjj=='N') && currpage<pages) currpage++;
                                if ((jjj>='1' && jjj<='9' && (currpage-1)*10+jjj-'0'<=amountsmithing) || (jjj=='0' && currpage*10<=amountsmithing))
                                {
                                    int slot=(currpage-1)*10+jjj-'0';
                                    if (jjj=='0') slot+=10;
                                    int number;
                                    cout<<"Enter the new selling price for the "<<smithing[slot]<<endl;
                                    cout<<"Note : The purchase price will be automatically changed by the multiplier"<<endl;
                                    cout<<"Note : Amounts less than 0 will be automatically changed to 0"<<endl;
                                    cin>>number;
                                    number=max(number,0);
                                    smithingprice[smithing[slot]]=number;
                                    system("cls");
                                    cout<<"The price of the "<<smithing[slot]<<" has been successfully changed!"<<endl;
                                    system("pause");
                                    system("cls");
                                }
                            }
                        }
                        if (iii=='3')
                        {
                            char jjj;
                            int pages=(amountalchemy-1)/10+1,currpage=1;
                            while (1)
                            {
                                cout<<"List of all alchemy materials"<<endl;
                                cout<<"Click the number to change the prices"<<endl;
                                cout<<"Page "<<currpage<<'/'<<pages<<endl;
                                cout<<endl;
                                for (int i=(currpage-1)*10+1;i<=min(amountalchemy,currpage*10);i++)
                                    cout<<'('<<i%10<<") "<<alchemy[i]<<" - Sell Price : "<<alchemyprice[alchemy[i]]<<"; Purchase Price : "<<alchemyprice[alchemy[i]]*(multiplier+100)/100<<endl;
                                cout<<endl;
                                if (pages>1)
                                {
                                    if (currpage==pages)  cout<<"    'P'revious Page"<<endl;
                                    else if (currpage==1) cout<<"                                'N'ext Page"<<endl;
                                    else                  cout<<"    'P'revious Page             'N'ext Page"<<endl;
                                }
                                cout<<"'R'eturn"<<endl;
                                jjj=getch();
                                system("cls");
                                if (jjj=='r' || jjj=='R') break;
                                if ((jjj=='p' || jjj=='P') && currpage>1) currpage--;
                                if ((jjj=='n' || jjj=='N') && currpage<pages) currpage++;
                                if ((jjj>='1' && jjj<='9' && (currpage-1)*10+jjj-'0'<=amountalchemy) || (jjj=='0' && currpage*10<=amountalchemy))
                                {
                                    int slot=(currpage-1)*10+jjj-'0';
                                    if (jjj=='0') slot+=10;
                                    int number;
                                    cout<<"Enter the new selling price for the "<<alchemy[slot]<<endl;
                                    cout<<"Note : The purchase price will be automatically changed by the multiplier"<<endl;
                                    cout<<"Note : Amounts less than 0 will be automatically changed to 0"<<endl;
                                    cin>>number;
                                    number=max(number,0);
                                    alchemyprice[alchemy[slot]]=number;
                                    system("cls");
                                    cout<<"The price of the "<<alchemy[slot]<<" has been successfully changed!"<<endl;
                                    system("pause");
                                    system("cls");
                                }
                            }
                        }
                    }
                }
                if (mat=='d' || mat=='D')
                {
                    char ccc;
                    while (1)
                    {
                        cout<<"Select a group of materials"<<endl;
                        cout<<endl;
                        cout<<"(1) Mining"<<endl;
                        cout<<"(2) Smithing"<<endl;
                        cout<<"(3) Alchemy"<<endl;
                        cout<<endl;
                        cout<<"'R'eturn"<<endl;
                        ccc=getch();
                        system("cls");
                        if (ccc=='r' || ccc=='R') break;
                        if (ccc=='1')
                        {
                            char mmm;
                            int currpage=1;
                            while (1)
                            {
                                int pages=(amountmining-1)/10+1;
                                cout<<"Select the number to delete the following item"<<endl;
                                cout<<endl;
                                for (int i=(currpage-1)*10+1;i<=min(amountmining,currpage*10);i++)
                                    cout<<'('<<i%10<<") "<<mining[i]<<endl;
                                cout<<endl;
                                if (pages>1)
                                {
                                    if (currpage==pages) cout<<"   'P'revious Page"<<endl;
                                    else if (currpage==1) cout<<"                          'N'ext Page"<<endl;
                                    else cout<<"   'P'revious Page        'N'ext Page"<<endl;
                                }
                                cout<<"'R'eturn"<<endl;
                                mmm=getch();
                                system("cls");
                                if (mmm=='r' || mmm=='R') break;
                                if ((mmm>='1' && mmm<='9' && (currpage-1)*10+mmm-'0'<=amountmining) || (mmm=='0' && currpage*10<=amountmining))
                                {
                                    int slot=(currpage-1)*10+mmm-'0';
                                    if (mmm=='0') slot+=10;
                                    remove_item(slot,1);
                                }
                            }
                        }
                        if (ccc=='2')
                        {
                            char mmm;
                            int currpage=1;
                            while (1)
                            {
                                int pages=(amountsmithing-1)/10+1;
                                cout<<"Select the number to delete the following item"<<endl;
                                cout<<endl;
                                for (int i=(currpage-1)*10+1;i<=min(amountsmithing,currpage*10);i++)
                                    cout<<'('<<i%10<<") "<<smithing[i]<<endl;
                                cout<<endl;
                                if (pages>1)
                                {
                                    if (currpage==pages) cout<<"   'P'revious Page"<<endl;
                                    else if (currpage==1) cout<<"                          'N'ext Page"<<endl;
                                    else cout<<"   'P'revious Page        'N'ext Page"<<endl;
                                }
                                cout<<"'R'eturn"<<endl;
                                mmm=getch();
                                system("cls");
                                if (mmm=='r' || mmm=='R') break;
                                if ((mmm>='1' && mmm<='9' && (currpage-1)*10+mmm-'0'<=amountsmithing) || (mmm=='0' && currpage*10<=amountsmithing))
                                {
                                    int slot=(currpage-1)*10+mmm-'0';
                                    if (mmm=='0') slot+=10;
                                    remove_item(slot,2);
                                }
                            }
                        }
                        if (ccc=='3')
                        {
                            char mmm;
                            int currpage=1;
                            while (1)
                            {
                                int pages=(amountalchemy-1)/10+1;
                                cout<<"Select the number to delete the following item"<<endl;
                                cout<<endl;
                                for (int i=(currpage-1)*10+1;i<=min(amountalchemy,currpage*10);i++)
                                    cout<<'('<<i%10<<") "<<alchemy[i]<<endl;
                                cout<<endl;
                                if (pages>1)
                                {
                                    if (currpage==pages) cout<<"   'P'revious Page"<<endl;
                                    else if (currpage==1) cout<<"                          'N'ext Page"<<endl;
                                    else cout<<"   'P'revious Page        'N'ext Page"<<endl;
                                }
                                cout<<"'R'eturn"<<endl;
                                mmm=getch();
                                system("cls");
                                if (mmm=='r' || mmm=='R') break;
                                if ((mmm>='1' && mmm<='9' && (currpage-1)*10+mmm-'0'<=amountalchemy) || (mmm=='0' && currpage*10<=amountalchemy))
                                {
                                    int slot=(currpage-1)*10+mmm-'0';
                                    if (mmm=='0') slot+=10;
                                    remove_item(slot,3);
                                }
                            }
                        }
                    }
                }
                if (mat=='a' || mat=='A')
                {
                    char ccc;
                    while (1)
                    {
                        cout<<"Select a group of materials"<<endl;
                        cout<<endl;
                        cout<<"(1) Mining"<<endl;
                        cout<<"(2) Smithing"<<endl;
                        cout<<"(3) Alchemy"<<endl;
                        cout<<endl;
                        cout<<"'R'eturn"<<endl;
                        ccc=getch();
                        system("cls");
                        if (ccc=='r' || ccc=='R') break;
                        if (ccc=='1') add_item(1);
                        if (ccc=='2') add_item(2);
                        if (ccc=='3') add_item(3);
                     }
                }
            }
        }

        if (menu=='h' || menu=='H')
        {

        }

        if (menu=='s' || menu=='S')
        {
            save();
            cout<<"The current database has been successfully saved!"<<endl;
            system("pause");
            system("cls");
        }
    }
}

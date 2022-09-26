#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;

// structura ce definseste o singura carte
// prin tip (culoarea) si numar
struct carti
{
    int tip,val;
};

// pachetul fiecarui jucator este o lista simplu inlantuita de carti
struct nod
{
    carti carte ;
    nod *leg;
};

// fiecare jucator are propriul pachet si o variabila
// care tine cont daca mai joaca sau nu
struct jucator
{
    nod *pachet;
    bool InJoc;
};

int nr,nrc,nrtot=52,v[54],i,j,z;

// vectori ce contin descriptorii de culoare si numar
char numetip[4][13]={"Inima Rosie","Romb","Inima Neagra","Trefla"};
char numeNr[13][15]={"AS","2","3","4","5","6","7","8","9","10","J","Q","K"};

// functie care genereaza random pachetul de 52 de carti
// si il intoarce drept lista
nod *citire()
{
    nod *p,*q,*u;
    p=NULL;
    // initializam toate cartile ca nefiind gasite
    for(i=1;i<=53;i++)
        v[i]=0;

    // generam random un nr si ne asiguram ca este din cele ramase
    for(i=1;i<=52;i++)
    {
        q=new nod;
        nr=rand()%nrtot+1;
        z=0; //numara cate carti libere am gasit
        j=0; //numara pozitia efectiva din vector
        while(z<nr)
        {
            if(v[j]==0)
                z++;
            j++;
        }
        nr=j-1;
        v[nr]=1;
        nrtot--;
        q->carte.tip=nr/13;
        q->carte.val=nr%13;
        q->leg=0;
        // legam carte noua la pachet
        if(p==NULL)
        {
            p=q;
            u=q;
        }
        else
        {
            u->leg=q;
            u=q;
        }
    }
    return p;
}

// functie care afiseaza un intreg pachet, in ordinea din mana
void parcurgere(nod *p)
{
    nod *q;
    q=p;
    while(q)
    {
        cout<<numeNr[q->carte.val]<<" "<<numetip[q->carte.tip]<<'\n';
        q=q->leg;
    }
}

// functie care afiseaza, la un moment dat, pachetele jucatorilor ramasi
// si cartile de pe masa
void afisare_joc(jucator *juc, int nrj, nod *masa)
{
    int i;
    nod *q;
    for(i=0;i<nrj;i++)
    {
        q=juc[i].pachet;
        cout<<"JUC "<<i+1<<" : ";
        cout<<'\n';
        parcurgere(q);
        cout<<'\n';
        getwchar();
    }
    cout<<"Masa: ";
    cout<<'\n';
    q=masa;
    parcurgere(q);
    cout<<'\n';
    getwchar();
}

// calculeaza cate carti trebuie puse de urmatorul jucator drept pedeapsa
int counter_pedeapsa(int valoare)
{
    int counter=0;
    switch(valoare)
    {
        case 0: counter=4;
        break;
        case 10: counter=1;
        break;
        case 11: counter=2;
        break;
        case 12: counter=3;
        break;
    }
    return counter;
}

// functia principala, practic tot flow-ul jocului este aici
// la fiecare iteratie se afiseaza pachetele jucatorilor si masa
int desfasurare_joc(jucator *juc, int nrj)
{
    int jucInJoc,i,counter=0,LaRand,castigator,ok,imax,c,y;
    nod *masa=NULL,*q;
    LaRand=0;
    // pana cand mai este un singur jucator in joc
    do{
        counter=0;
        // pana cand nu mai exista pedeapsa acrtiva
        do
        {
            afisare_joc(juc,nrj,masa);
            // punere carti pe masa
            // daca masa era goala
            if(masa==NULL)
            {
                if(juc[LaRand].pachet)
                {
                    q=juc[LaRand].pachet;
                    juc[LaRand].pachet=juc[LaRand].pachet->leg;
                    q->leg=masa;
                    masa=q;
                    counter=counter_pedeapsa(masa->carte.val);
                    if(counter>0)
                        castigator=LaRand;
                }
                if(LaRand==nrj-1)
                    LaRand=0;
                else
                    LaRand++;
                while(!juc[LaRand].pachet)
                    LaRand++;
            }
            else // daca existau deja carti pe masa
            {
                // daca nu exista pedeapsa activa
                if(counter==0)
                {
                    if(juc[LaRand].pachet)
                    {
                        q=juc[LaRand].pachet;
                        juc[LaRand].pachet=juc[LaRand].pachet->leg;
                        q->leg=masa;
                        masa=q;
                        counter=counter_pedeapsa(masa->carte.val);
                        if(counter>0)
                            castigator=LaRand;
                    }
                    if(LaRand>=nrj-1)
                        LaRand=0;
                    else
                        LaRand++;
                    while(!juc[LaRand].pachet)
                        LaRand++;
                }
                else
                {
                    // altfel, un jucator pune carti pana la terminarea pedepsei
                    if(juc[LaRand].pachet)
                    {
                        ok=0;
                        do{
                            q=juc[LaRand].pachet;
                            juc[LaRand].pachet=juc[LaRand].pachet->leg;
                            q->leg=masa;
                            masa=q;
                            // update pedeapsa daca s-a gasit o carte speciala
                            if((masa->carte.val==0)||(masa->carte.val==10)||(masa->carte.val==11)||(masa->carte.val==12))
                            {
                                counter=counter_pedeapsa(masa->carte.val);
                                ok=1;
                                castigator=LaRand;
                                if(LaRand==nrj-1)
                                    LaRand=0;
                                else
                                    LaRand++;
                            }
                            else
                                counter--;
                                // s-a terminat pedeapsa si mutam cartile
                            if(counter<=0)
                            {
                                ok=1;
                                // pachet gol
                                if(juc[castigator].pachet==NULL)
                                {
                                    cout<<"Masa urmatoare: "<<'\n';
                                    q=masa;
                                    y=1;
                                    c=castigator;
                                    while(y==1)
                                    {
                                        if(c==nrj-1)
                                            c=-1;
                                        c++;
                                        if(juc[c].pachet!=NULL)
                                            y=0;
                                    }
                                    cout<<numeNr[q->carte.val]<<" "<<numetip[q->carte.tip]<<
                                        " (carte pusa de jucatorul "<<c+1<<" care nu poate continua lantul)"<<'\n';
                                    q=q->leg;
                                    while(q)
                                    {
                                        cout<<numeNr[q->carte.val]<<" "<<numetip[q->carte.tip]<<'\n';
                                        q=q->leg;
                                    }

                                    cout<<'\n';
                                    getwchar();
                                    cout<<"Jucatorul "<<castigator+1<<" a luat mana!"<<'\n';
                                    juc[castigator].pachet=masa;
                                    masa=NULL;
                                    getwchar();

                                }
                                else
                                {
                                    // jucatorul care a castigat mai are carti
                                    cout<<"Masa urmatoare: "<<'\n';
                                    q=masa;
                                    y=1;
                                    c=castigator;
                                    while(y==1)
                                    {
                                        if(c==nrj-1)
                                            c=-1;
                                        c++;
                                        if(juc[c].pachet!=NULL)
                                            y=0;
                                    }
                                    cout<<numeNr[q->carte.val]<<" "<<numetip[q->carte.tip]<<
                                        " (carte pusa de jucatorul "<<c+1<<" care nu poate continua lantul)"<<'\n';

                                    q=q->leg;
                                    while(q)
                                    {
                                        cout<<numeNr[q->carte.val]<<" "<<numetip[q->carte.tip]<<'\n';
                                        q=q->leg;
                                    }

                                    cout<<'\n';
                                    getwchar();
                                    cout<<"Jucatorul "<<castigator+1<<" a luat mana!"<<'\n';
                                    q=juc[castigator].pachet;
                                    while(q->leg)
                                        q=q->leg;
                                    q->leg=masa;
                                    masa=NULL;
                                    getwchar();
                                }
                            }
                        }while(ok==0);
                    }
                    else
                    {
                        if(LaRand==nrj-1)
                            LaRand=0;
                        else
                            LaRand++;
                        while(!juc[LaRand].pachet)
                            LaRand++;
                    }
                }
            }
        }while(counter>0);
        // se calculeaza cati jucatori mai au carti
        jucInJoc=0;
        for(i=0;i<nrj;i++)
        {
            if(juc[i].InJoc)
            {
                jucInJoc++;
                imax=i;
            }
        }
    }while(jucInJoc>1);
    return imax+1;
}

// main-ul lanseaza functia Desfasurare_joc
int main()
{
    srand(time(NULL));
    nod *pachet,*q,*u[10];
    jucator juc[10];
    int nrjuc,i;
    // se parseaza input-ul de la tastatura (maxim 10 jucatori)
    cout<<"Cati jucatori vor adera la joc?  : ";
    cin>>nrjuc;
    getwchar();
    cout<<"Se afiseaza pachetul initial: ";
    cout<<'\n';
    getwchar();
    pachet=citire();
    parcurgere(pachet);
    // urmeaza impartirea
    for(i=0;i<nrjuc;i++)
    {
        juc[i].pachet=NULL;
        juc[i].InJoc=true;
    }
    // se imparte pachetul initial la toti jucatorii
    while(pachet)
    {
        for(i=0;i<nrjuc;i++)
        {
            if(pachet)
            {
                q=new nod;
                q->carte=pachet->carte;
                q->leg=0;
                if(juc[i].pachet==NULL)
                {
                    juc[i].pachet=q;
                    u[i]=q;
                }
                else
                {
                    u[i]->leg=q;
                    u[i]=q;
                }
                pachet=pachet->leg;
            }
        }
    }
    cout<<'\n';
    cout<<"Se afiseaza pachetele jucatorilor: ";
    cout<<'\n';
    getwchar();
    int jucCastigator=desfasurare_joc(juc,nrjuc);
    afisare_joc(juc,nrjuc,NULL);
    cout<<jucCastigator;
    cout<<"Sfarsitul Jocului!";

    return 0;
}

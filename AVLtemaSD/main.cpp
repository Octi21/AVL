#include <bits/stdc++.h>

using namespace std;

/// documentatie :https://www.geeksforgeeks.org/avl-tree-set-1-insertion/


struct nod  // struct de noduri
{
    int val;
    nod * st;
    nod *dr;
    int h;
};


int maxx(int x, int y)
{
    if(x>y)
        return x;
    return y;
}

int inaltime(nod * n)
{
    if(n !=NULL)
        return n -> h;
    return 0;
}

nod * newnod(int valoare)
{
    nod* n = new nod();
    n-> val =  valoare;
    n-> st = NULL;
    n-> dr = NULL;
    n-> h = 1;

    return (n);
}


nod * rRotate(nod *y) // y reprezinta varful
{
    nod *x = y-> st;
    nod *copil2x = x-> dr;

    ///rotatie
    x-> dr = y;
    y-> st = copil2x;

    /// update la h lui x si y
    y-> h = maxx(inaltime(y->st),(inaltime(y->dr))) + 1;
    x-> h = maxx(inaltime(x->st),inaltime(x->dr)) +1;

    return x;
}

nod * lRotate(nod *x)
{
    nod * y  = x-> dr;
    nod * copil1y = y->st;

    ///rotatie
    y-> st = x;
    x-> dr = copil1y;

    /// update la h lui x si y
    y-> h = maxx(inaltime(y->st),(inaltime(y->dr))) + 1;
    x-> h = maxx(inaltime(x->st),inaltime(x->dr)) +1;

    return y;
}

int difNivel(nod *n)
{
    if(n == NULL)
        return 0;
    return inaltime(n->st) - inaltime(n->dr);
}


nod * insrt(nod * n, int valoare)
{
    /// inserarea elementelor in arbore ca si frunze
    if(n == NULL)
    {
        return (newnod(valoare));
    }

    if(valoare > n->val)
    {
        n->dr = insrt(n->dr,valoare);
    }
    else if (valoare < n->val)
    {
        n-> st = insrt(n->st,valoare);
    }
    else if (valoare == n->val)
        return n;

    /// update la h
    n->h = maxx(inaltime(n->st), inaltime(n->dr)) +1;

    /// calc dif dintre copiii unui nod
    int dif = difNivel(n);

    /// in cazul in care dupa inserare arborele in mai e avl
    ///(dif dintre h a 2copii ai unui nod >1 || <-1)

    /// caz 1: left left
    if(dif > 1 && valoare < n->st->val)
    {
        return rRotate(n);
    }

     ///  caz 2: right right
    if(dif < -1 && valoare > n->dr->val)
    {
        return lRotate(n);
    }

    /// caz 3: left right
    if(dif > 1 && valoare > n->st->val)
    {
        n -> st = lRotate(n ->st);
        return rRotate(n);
    }

    /// caz 4: r l
    if(dif < -1 && valoare < n->st->val)
    {
        n -> dr = rRotate(n ->dr);
        return lRotate(n);
    }

    /// returnezi nodul pe care te afli daca in adaugarea unui
    /// nod nou avl-ul nu a fost stricat
    return n;
}


nod * findMin (nod *n)///returneaza nodul in care se afla val min
{
    nod * aux = n;
    while(aux->st !=NULL)
        aux = aux->st;
    return aux;
}

nod * findMax (nod * n)
{
    nod * aux = n;
    while(aux->dr !=NULL)
        aux = aux-> dr;
    return aux;
}

nod* dlete(nod* n, int valoare)
{
    if(n == NULL)    // cazul in care nodul e nul
        return n;

    if(valoare < n->val)
        n->st = dlete(n->st, valoare);
    else if(valoare > n->val)
        n->dr = dlete(n->dr, valoare);
    else  /// cand gasesc nodul pe care in sterg
    {
        if(n->dr == NULL || n->st == NULL)/// nod are cel mult un copil
        {
            nod * temp;
            if(n->dr == NULL && n->st == NULL)
            {
                temp = n;
                n = NULL;
            }
            else
            {
                if(n->dr == NULL && n->st != NULL)
                {
                    temp = n->st;
                    //n =  n->st;
                    *n = *temp;
                }
                else if(n->dr != NULL && n->st == NULL)
                {
                    temp = n->dr;
                    //n = n->dr;
                    *n = *temp;
                }
            }
            free(temp);
        }
        else /// nod cu 2 copii
        {
            nod* temp = findMin(n->dr);

            n->val = temp->val;

            n ->dr = dlete(n->dr, temp ->val);
        }
    }

    if(n == NULL) // daca arborele avea doar 1 nod
        return n;

    int dif = difNivel(n);

     /// caz 1: left left
    if(dif > 1 && difNivel(n->st) >= 0)
    {
        return rRotate(n);
    }

     ///  caz 2: right right
    if(dif < -1 && difNivel(n->dr) <= 0)
    {
        return lRotate(n);
    }

    /// caz 3: left right
    if(dif > 1 && difNivel(n->st) < 0)
    {
        n -> st = lRotate(n ->st);
        return rRotate(n);
    }

    /// caz 4: r l
    if(dif < -1 && difNivel(n->dr) > 0)
    {
        n -> dr = rRotate(n ->dr);
        return lRotate(n);
    }


    return n;
}


void preorder(nod* n)
{
    if(n != NULL)
    {
        cout<< n->val<<" ";
        preorder(n->st);
        preorder(n->dr);
    }
}

void inorder (nod * n)
{
    if(n != NULL)
    {
        inorder(n->st);
        cout<< n->val<<" ";
        inorder(n->dr);
    }
}


int cautare (nod *n, int valoare)
{
    if(n == NULL)
    {
        return 0;
    }
    if(n->val == valoare)
        return 1;
    if(n->val < valoare)
        return cautare(n->dr,valoare);
    if(n->val > valoare)
        return cautare(n->st,valoare);
}


nod* pred (nod* n, int valoare, nod* actual = NULL)
{
    if (n == NULL)
    {
        return actual;
    }

    int dif = valoare - n->val;
    if (dif >= 0)
    {
        actual = n;
    }
    /*if(valoare>=n->val)
        return(n->dr,valoare,actual);
    return(n->st,valoare,actual);*/
    return pred(
    valoare >= n->val ? n->dr : n->st,
    valoare,
    actual
    );
}

nod* succ (nod* n, int valoare, nod* actual = NULL)
{
    if (!n)
    {
        return actual;
    }

    int dif = valoare - n->val;
    if (dif <= 0)
    {
        actual = n;
    }
    if(valoare>=n->val)
        return(n->dr,valoare,actual);
    return(n->st,valoare,actual);
    /*
    return getSuccessorOf(
    value > root->value ? root->right : root->left,
    value,
    crtSuccessor
    );*/
}

int main()
{
    nod * root = NULL;

    root = insrt(root, 9);
    root = insrt(root, 5);
    root = insrt(root, 10);
    root = insrt(root, 0);
    root = insrt(root, 6);
    root = insrt(root, 11);
    root = insrt(root, -1);
    root = insrt(root, 1);
    root = insrt(root, 2);

    //preorder(root);
    cout<<"\n";
    nod* pre = pred(root,10,pre);
    cout<<pre->val;
    //inorder(root);
    //cout<<"\n"<<cautare(root,9)<<"\n";

    //root = dlete(root, 10);
    //preorder(root);

    //cout<<"\n"<<cautare(root,10);
    return 0;
}



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <ctype.h>
#include <limits.h>

typedef struct lista
{
    char c;
    struct lista* sig;
}string;

struct num{
    //Numero
    int n;
    //STR
    char *str;
    //Si es cerrado o abierto 
    //0 -- Abierto 1 --- Cerrado
    int s;
    //Dice si es del conjunto a o b
    int i;
};

void gotoxy(int x, int y);

void getpos(int *x, int *y);

void back(int p);

string *add(string *list, char C);

int sizel(string* list);

char* lts(string *list);

string *addstr(string *list, const char* str);

int delx(string **lista, char x);

void del(string **lista, int x);

void delstr(string **lista);

char* input();

void __getnum(char* num, int* a);

void _getnum(char* num, struct num *n);

void getnum(const char* a, struct num *n1, struct num *n2, int j);

void ops(char* a, char* b);

void nswap(int *a, int *b);

void swap(struct num *x, struct num *y);

void sorder(struct num *p);

void norder(struct num *p);

string* interval(struct num *p1, struct num *p2);

char* uni(struct num *p, char *a, char *b);

char* inter(struct num *p);

char* dif(struct num *p, int mode);

char* comple(char* x);

void data(int c, int n, int s, string* str){
    int x, y;
    getpos(&x,&y);
    printf("\nc: %d n: %d e: %d s: %d  \n",c,n,sizel(str),s);
    char *r = lts(str);
    puts("            ");
    gotoxy(0,y+2);
    puts(r);
    free(r);
    gotoxy(x,y);
}

void console();

int main(){    

    console();
    char *a, *b;
    while(1)
    {
        puts("Hello, type the sets in interval notation, please.");
        printf("A = \n");
        printf("B = ");
        gotoxy(4,1);
        a = input();
        gotoxy(4,2);
        b = input();
        //printf("%s %s\n",a,b);
        ops(a,b);
        printf("Press any key to continue...");
        system("pause>nul");
        free(a);
        free(b);
        system("cls");
    
    }
    
    return 0;
}

void console()
{
    system("mode 65, 11");
    system("color 01");
    system("title Operations between intervals");
}

void gotoxy(int x, int y){
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwpos;
    dwpos.X = x;
    dwpos.Y = y;
    SetConsoleCursorPosition(h,dwpos);
}

void getpos(int *x, int *y){
    CONSOLE_SCREEN_BUFFER_INFO CSBI;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(h,&CSBI);
    *x = CSBI.dwCursorPosition.X;
    *y = CSBI.dwCursorPosition.Y;
}

void back(int p){
    int x, y;
    getpos(&x,&y);
    while (y != -1)
    {
        while (x != 0)
        {
            
            if(p == 0)
            {
                return;
            }
            x -= 1;
            p -= 1;
            gotoxy(x,y);
            printf(" ");
            gotoxy(x,y);
        }
        x = 119;
        y -= 1;
    }
    
}

string *add(string *list, char C){
    string *new = (string*)malloc(sizeof(string));
    new->c = C;
    new->sig = NULL;
    if(list == NULL)
    {
        list = new;
    }
    else
    {
        string *aux = list;
        while(aux->sig != NULL)
        {
            aux = aux->sig;
        }
        aux->sig = new;
    }
    return list;
}

int sizel(string* list){
    int i = 0;
    while(list != NULL)
    {
        list = list->sig;
        i ++;
    }
    return i;
}

char* lts(string *list){
    //Obtengo el size de la lista
    int c = sizel(list)+1;
    //Reservo la memoria
    char *r;
    r = (char*)malloc(sizeof(char)*c);
    //Relleno la str
    for(int i = 0; list != NULL; i++)
    {
        r[i] = list->c;
        list = list->sig;
    }
    //Le pongo fin a la str
    r[c-1] = '\0'; 
    return r;
}

string *addstr(string *list, const char* str){
    int i = 0, size = strlen(str);
    if(list == NULL)
    {
        list = (string*)malloc(sizeof(string));
        list->c = str[0];
        i++;
    }
    string *aux = list;
    if(i == 0)
    {
        while (list->sig != NULL)
        {
            list = list->sig;
        }
    }
    while (i < size)
    {
        list->sig = (string*)malloc(sizeof(string));
        list = list->sig;
        list->c = str[i];
        i++;
    }
    list->sig = NULL;
    return aux;
}

int delx(string **lista, char x){
    //Inicializamos a aux en null, si este no cambia su valor, significa que el primer nodo alberga el char
    //list es el puntero que recorrera la lista, con aux como el puntero que apuntara al nodo anterior
    string *aux = NULL, *list = *lista;
    //Buscamos el caracter
    while(list != NULL && list->c != x)
    {
        aux = list;
        list = list->sig;
    }
    //Si list es igual a null no vale la pena seguir
    //O la lista esta vacia o no se encontro el char
    if(list == NULL)
    {
        return 0;
    }
    //Si se encontro el char
    if (list->c == x)
    {
        //Si aux no es null significa que el char no estaba en el primer nodo
        if(aux != NULL)
        {
            //Conecto el puntero, del nodo anterior al nodo que alberga el char, con la siguiente lista al nodo que alberga el char
            aux->sig = list->sig;
        }
        else
        {
            //aux es null, es decir, el primer nodo alberga el char

            //Si el size de la lista es de 1, significa que eliminaremos por completo a la lista
            //Debemos dejar al puntero lista en null
            if(sizel(*lista) == 1)
            {
                *lista = NULL;
            }
            else
            {
                //hay mas de un nodo vigente
                //Hago que lista se mueva al siguiente nodo
                aux = *lista;
                *lista = aux->sig;
            }
        }
        //Elimino el nodo o mejor dicho, librero la memoria
        free(list);
        return 1;
    }
}

void del(string **lista, int x){
    //Si es null, no vale la pena seguir
    if(*lista == NULL)
    {
        return;
    }
    
    string *list = *lista, *aux = NULL;
    while (list->sig != NULL && x != 0)
    {
        aux = list;
        list = list->sig;
        x -= 1;
    }
    if(aux == NULL)
    {
        *lista = list->sig;
    }
    else
    {
        aux->sig = list->sig;
    }
    free(list);
}

void delstr(string **lista){
    string *list = *lista, *aux;
    while (list != NULL)
    {
        aux = list->sig;
        free(list);
        list = aux;
    }
    *lista = NULL;
}

char* input(){
    char *r;
    string *str = NULL, *N = NULL;
    int c = 0, n = 0, aux[3], i = 0;
    aux[2] = 1;
    char k = 0;
    while(1)
    {
        k = getch();

        //Guardamos en aux[0] si k es un numero o no (true/false)
        aux[0] = (isdigit(k) || k == 'i');

        switch (c)
        {
        case 0:
        //Inicio
            if(k == '[' || k == '(')
            {
                aux[2] = k;
                putchar(k);
                str = add(str,k);

                //c simboliza en que parte del intervalo vamos
                c++;
                
            }
            break;
        case 1:
        //Primer numero
            //Eliminar
            if(k == 8)
            {
                i = 0;
                //Se elimina
                //Si no se ha escrito ningun numero se eliminara el [(
                putchar(k);
                putchar(' ');
                putchar(k);
                //Se elimina el caracter de la lista
                del(&str,-1);
                //Si se ha escrito como minimo un digito (numero o '+' '-')
                if(n != 0)
                {
                    //Si se ha digitado un '+' '-' n sera menor que 0
                    if(n < 0)
                    {
                        //Por eso lo devolvemos a la normalidad, para poder restarle
                        n = n*-1;
                    }
                    //Restamos n
                    n -= 1;

                    //Si se digito un numero, solo retrocederemos
                    //Si se digito un '+' '-' solo retrocederemos y n quedara igual a cero
                }
                else
                {
                    //No hemos digitado nada
                    //Por eso podemos retroceder un case
                    c -= 1;
                }
                
            }
            //Se digito un valor valido
            if(aux[0] || k == '-' || k == '+')
            {

                //El valor no es un numero, es '+' o '-'
                if(aux[0] == 0)
                {
                    //Solo se puede ingresar un '+' o '-' si es que n es cero, es decir, si no se ha digitado nada
                    if(n == 0)
                    {
                        //Guardo si el numero es positivo
                        // aux[2]*('+' - 44)*-1 = aux[2]*(43-44)*-1 = aux[2]*(-1)*-1 = aux[2]*1 -----> positivo
                        // aux[2]*('-' - 44)*-1 = aux[2]*(45-44)*-1 = aux[2]*(1)*-1 = aux[2]*-1 -----> negativo
                        aux[2] = aux[2]*(k - 44)*-1;
                        //Añadimos e imprimimos
                        str = add(str,k);
                        putchar(k);

                        //Aumentamos 1 pq hay un elemento mas
                        n ++;
                        //Hacemos que n sea negativo para dejar en claro que se ha digitado un '+' '-' pero aun no el valor numerico
                        n = n*-1;
                    }
                }
                else
                {
                    if(i != 1 && !(k == 'i' && abs(aux[2]) == '['))
                    {
                        //El valor es un numero 

                        //Si el numero es un infinito
                        if (k == 'i')
                        {
                            i ++;
                        }
                        

                        //Añadimos e imprimimos
                        str = add(str,k);
                        putchar(k);

                        //si n es menor que cero significa que se digito previamente un '+' '-'
                        //Como ya se ingreso el valor numerico, podemos hacer a n positivo
                        if(n < 0)
                        {
                            n = n*-1;
                        }
                        //Aumentamos a n pq hay un elemento mas
                        n ++;

                        //Que quede en claro que n siempre terminara siendo positivo, si se cumple este condicional
                        //Si se cumple este condicional, ya se cumplen los requisitos minimos para pasar poder ingresar un ; y asi poder pasar al siguiente case
                    }
                }

            }
            else
            {
                //Si el valor ingresado es ; y n es mayor que 0 (es decir ya se cumplen los requisitos minimos)
                if(k == ';' && n > 0)
                {
                    //imprimimos y añadimos
                    str = add(str,k);
                    putchar(k);

                    //Aumentamos a c para pasar al siguiente case
                    c++;
                    
                }
            }
            break;
        case 2:
        //Segundo numero
            //Guardamos en aux[1] si aun no se ha sigitado ningun valor (true/false)
            aux[1] = (sizel(str) == abs(n)+2);
            //Eliminar
            if(k == 8)
            {
                i = abs(i);
                //Se elimina
                putchar(k);
                putchar(' ');
                putchar(k);

                //Si aun no se ha digitado nada
                if(aux[1])
                {
                    //se borrara el ; y se retrocedera un case, es decir, se le restara 1 a c
                    c -= 1;
                    if(n < 0)
                    {
                        n = n*-1;
                    }
                }
                //Eliminamos el caracter de la lista
                del(&str,-1);
            }
            
            //Si se ha ingresado un valor valido
            if(aux[0] || k == '-' || k == '+')
            {
                //el valor no es un numero
                if(aux[0] == 0)
                {
                    //Aun no se ha digitado ningun numero, y por lo tanto, se puede ingresar un '+' o '-'
                    if(aux[1] && aux[2] <= abs(aux[2])*(k-44)*-1)
                    {
                        //Añadimos e imprimimos
                        putchar(k);
                        str = add(str,k);
                        //Hacemos a n negativo para dejar en claro que se ha digitado un '+' '-' pero aun falta un numero
                        n = n*-1;
                    }
                }
                else
                {
                    if(i > -1)
                    {
                        //El valor es un numero

                        //Si es un infinito
                        if(k == 'i')
                        {
                            i *= -1;
                        }

                        //Añadimos e imprimimos
                        putchar(k);
                        str = add(str,k);

                        //Ya se cumplen las condiciones para añadir un ])
                    }
                }
            }
            //Se ha digitado un digito como minimo y se tiene un valor numerico
            if(!aux[1] && 0 < n || (sizel(str) - n+2) != 1 && n < 0)
            {
                //Se ha ingresado ')' o ']'
                if(k == ']' && i > -1 || k == ')')
                {


                    //Primero debemos ver si se cumplen los requisitos minimos

                    //Replicamos la lista str:
                    r = lts(str);
                    N = addstr(N,r);
                    free(r);
                    //Hacemos que N solo alberge el primer numero:
                    //Haremos que se borren todos los elementos despues de nuestro primer numero
                    //Restamos el num de elementos menos el numero de digitos del primer numero + 1 (este uno simboliza el '[' '(' del inicio)
                    aux[0] = sizel(N) - (abs(n)+1);
                    for(int i = 0; i < aux[0]; i++)
                    {
                        del(&N,-1);
                    }
                    //Borro el '[' '(' del inicio
                    del(&N,0);
                    //Guardo el valor del primer numero
                    r = lts(N);
                    __getnum(r,&aux[0]);
                    free(r);

                    //Replicamos str de nuevo
                    delstr(&N);
                    r = lts(str);
                    N = addstr(N,r);
                    free(r);

                    //Borro todos los elementos por detras del segundo numero:
                    aux[1] = abs(n)+2;
                    for(int i = 0; i < aux[1]; i++)
                    {
                        del(&N,0);
                    }
                    r = lts(N);
                    __getnum(r,&aux[1]);
                    free(r);
                    delstr(&N);

                    if(aux[0] < aux[1] || aux[0] == aux[1] && abs(aux[2]) == '[' && k == ']')
                    {
                        //Añadimos e imprimimos
                        str = add(str,k);
                        putchar(k);

                        //Sumamos a c
                        c++;
                    }
                    
                }
            }
            break;
        case 3:
            //Se ha presionado un return
            if(k == 13)
            {
                //Terminamos con la funcion
                //Devolvemos una cadena de caracteres, compuesta por los elementos de la lista llamada str
                r = lts(str);
                delstr(&str);
                return r; 
            }
            else
            {
                //Eliminar
                if(k == 8)
                {
                    //Eliminamos
                    putchar(k);
                    putchar(' ');
                    putchar(k);

                    //Eliminamos el )] de la lista
                    del(&str,-1);

                    //Retrocedemos un case
                    c -= 1;
                }

            }
            break;
        }
        //Esta funcion la use para saber los datos mientras testeaba la funcion
        //data(c,n,aux[2],str);

    }
}

void __getnum(char* num, int *a){

    if(strcmp(num,"i") == 0 || strcmp(num,"+i") == 0 || strcmp(num,"-i") == 0)
    {
        if(num[0] == '-')
        {
            *a = INT_MIN;
        }
        else
        {
            *a = INT_MAX;
        }
        
    }
    else
    {
        *a = atoi(num);
    }
}

void _getnum(char* num, struct num *n)
{
    n->str = num;
    __getnum(num,&(*n).n);
}

void getnum(const char* a, struct num *n1, struct num *n2, int j){
    n1->i = j;
    n2->i = j;

    if(a[0] == '[')
    {
        n1->s = 1;
    }
    else
    {
        n1->s = 0;
    }

    int i = 1, tam = strlen(a);

    if(a[tam-1] == ']')
    {
        n2->s = 1;
    }
    else
    {
        n2->s = 0;
    }

    string *n = NULL;

    for(; a[i] != ';'; i++)
    {
        n = add(n,a[i]);
    }

    char* str = lts(n); 

    _getnum(str,n1);

    delstr(&n);

    for(i = i+1; i < tam-1; i++)
    {
        n = add(n,a[i]);
    }

    str = lts(n);

    _getnum(str,n2);

    delstr(&n);

}

void nswap(int *a, int *b){
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

void swap(struct num *x, struct num *y){
    
    //Numeros
    nswap(&x->n,&y->n);

    //Intervalo
    nswap(&x->i,&y->i);

    //[]  ()
    nswap(&x->s,&y->s);

    //str
    char* aux = x->str;
    x->str = y->str;
    y->str = aux;
}

void sorder(struct num *p){
    int c = (p->i != (p+3)->i);

    if (p->n == (p+1)->n && p->s == (p+1)->s)
    {
        if(c)
        {
            nswap(&p->i,&(p+1)->i);
        }
    }

    if((p+2)->n == (p+3)->n && (p+2)->s == (p+3)->s)
    {
        if(c)
        {
            nswap(&(p+2)->i,&(p+3)->i);
        }
    }

    if((p+1)->n == (p+2)->n && (*(p)).i != (*(p+1)).i)
    {
        swap(p+1,p+2);
    }

    if(0)
    {
        putchar('\n');
        for(int i = 0; i < 4; i++)
        {
            printf("N: %d C: %d S: %d\n",p[i].n,p[i].i,p[i].s);
        }
    
    }    
}

void norder(struct num *p){

    for(int i = 0; i < 4; i++)
    {
        for(int j = i; j != 0; j-=1)
        {
            if((p+j)->n < (p+j-1)->n)
            {
                swap(p+j,p+j-1);
            }
        }
    }

    for(int i = 0, j; i < 3; i+=2)
    {
        if((p+i)->n == (p+i+1)->n)
        {
            j = (p+i+1)->s - (p+i)->s - i;
            if(j == 1 || j == -3)
            {
                swap(p+i,p+i+1);
            }
        }
    }

    
}

string* interval(struct num *p1, struct num *p2){
    string *str = NULL;
    char s;
    if(p1->s == 0)
    {
        s = '(';
    }
    else
    {
        s = '[';
    }
    str = add(str,s);
    str = addstr(str,p1->str);
    str = add(str,';');
    str = addstr(str,p2->str);
    if(p2->s == 0)
    {
        s = ')';
    }
    else
    {
        s = ']';
    }
    str = add(str,s);
    return str;
}

char* uni(struct num *p, char *a, char *b){
    string *str = NULL;
    int v[4];
    v[0] = ((p+1)->n == (p+2)->n && (p+1)->s + (p+2)->s != 0);
    v[1] = (p->i == (p+1)->i);
    v[2] = (p->i == (p+2)->i || p->i == (p+3)->i);

    if(v[0] && v[1] || v[2])
    {
        str = interval(p,p+3);   
    }
    if(!v[0] && v[1])
    {
        if(p->i == 0)
        {
            str = addstr(str,a);
        }
        else
        {
            str = addstr(str,b);
        }
        str = add(str,'U');
        if((p+3)->i == 0)
        {
            str = addstr(str,a);
        }
        else
        {
            str = addstr(str,b);
        }
    }

    char *r = lts(str);
    delstr(&str);
    return r;
}

char* inter(struct num *p){
    string *str = NULL;

    if(p->i == (p+1)->i)
    {
        if((p+1)->n == (p+2)->n && (p+1)->s + (p+2)->s == 2)
        {
            str = add(str,'{');
            str = addstr(str,(p+1)->str);
            str = add(str,'}'); 
        }
        else
        {
            str = add(str,157);
        }
    }
    else
    {
        str = interval(p+1,p+2);
    }
    

    char *r = lts(str);
    delstr(&str);
    return r;
}

char* dif(struct num *p, int mode){
    string *str = NULL;
    int v;
    v = mode == p->i;
    if (p->i == (p+1)->i)
    {
        int s = 0;
        if((p+1)->n == (p+2)->n && (p+1)->s + (p+2)->s == 2)
        {
            s = 1;
        }
        if(v)
        {
            str = interval(p,p+1);
            if(s)
            {
                del(&str,-1);
                str = add(str,')');
            }

        }
        else
        {
            str = interval(p+2,p+3);
            if(s)
            {
                str->c = '(';
            }
        }
        
    }
    else
    {
        int s = 0, s1 = 0;
        for (int i = 0; i < 3; i+=2)
        {
            if ((p+i)->n == (p+i+1)->n)
            {
                s1++;
                if((p+i)->s == (p+i+1)->s)
                {
                    s++;
                }
            }
        }
        if(p->i == (p+3)->i)
        {
            if(s1 != 2)
            {
                if(v)
                {
                    if(p->n != (p+1)->n)
                    {
                        str = interval(p,p+1);
                        del(&str,-1);
                        if ((p+1)->s)
                        {
                            str = add(str,')');
                        }
                        else
                        {
                            str = add(str,']');   
                        }
                    }
                    if(p->n != (p+1)->n && (p+2)->n != (p+3)->n)
                    {
                        str = add(str,'U');
                    }
                    if((p+2)->n != (p+3)->n)
                    {
                        if ((p+2)->s)
                        {
                            str = add(str,'(');
                        }
                        else
                        {
                            str = add(str,'[');   
                        }
                        string *aux = str;
                        while (aux->sig != NULL)
                        {
                            aux = aux->sig;
                        }
                        aux->sig = interval(p+2,p+3);
                        del(&aux,1);
                    }
                }
                else
                {
                    str = add(str,157);
                }
            }
            else
            {
                if (v)
                {
                    str = add(str,'{');
                    if (p->s != (p+1)->s)
                    {
                        s = 0;
                    }
                    else
                    {
                        s = 3;
                    }
                    str = addstr(str,(p+s)->str);
                    str = add(str,'}');
                }
                else
                {
                    str = add(str,157);
                }
                
            }
        }
        else
        {
            
            if (s == 2)
            {
                str = add(str,157);
            }
            else
            {
                if(s1 == 2)
                {
                    str = add(str,'{');            
                    if(v)
                    {
                        if(p->s == 1)
                        {
                            s1 = 0;
                        }
                        else
                        {
                            s1 = 2;
                        }
                    }
                    else
                    {
                        if((p+3)->s == 1)
                        {
                            s1 = 3;
                        }
                        else
                        {
                            s1 = 1;
                        }
                    }
                    str = addstr(str,(p+s1)->str);
                    str = add(str,'}');
                }
                else
                {
                    
                    if(v)
                    {
                        if (p->n == (p+1)->n)
                        {
                            str = add(str,'{');
                            str = addstr(str,p->str);
                            str = add(str,'}');
                        }
                        else
                        {
                            str = interval(p,p+1);
                            del(&str,-1);
                            if((p+1)->s)
                            {
                                s = ')';
                            }
                            else
                            {
                                s = ']';
                            }
                            str = add(str,s);
                        }
                    }
                    else
                    {
                        if((p+2)->n == (p+3)->n)
                        {
                            str = add(str,'{');
                            str = addstr(str,(p+2)->str);
                            str = add(str,'}');
                        }
                        else
                        {
                            str = interval(p+2,p+3);
                            if((p+2)->s)
                            {
                                s = '(';
                            }
                            else
                            {
                                s = '[';
                            }
                            str->c = s;
                        }
                    }
                
                }    
            }    
        }
    }
    
    char *r = lts(str);
    delstr(&str);
    return r;
}

char* comple(char* x){
    struct num con[2];
    getnum(x,&con[0],&con[1],0);
    string *str = NULL;
    char s, *r;
    if(con[0].str[1] != 'i')
    {
        str = addstr(str,"(-i;");
        str = addstr(str,con[0].str);
        if(con[0].s)
        {
            s = ')';
        }
        else
        {
            s = ']';
        }
        str = add(str,s);
    }
    else
    {
        s = 1;
    }
    if(con[1].str[0] != 'i' && con[1].str[1] != 'i')
    {
        if(s != 1)
        {
            str = add(str,'U');
        }
        if(con[1].s)
        {
            s = '(';
        }
        else
        {
            s = '[';
        }
        str = add(str,s);
        str = addstr(str,con[1].str);
        str = addstr(str,";+i)");
    }
    else
    {
        if(s == 1)
        {
            str = add(str,157);
        }
    }
    r = lts(str);
    delstr(&str);
    return r;
}

void ops(char* a, char* b){
    
    //Array de estructuras que guardaran los numeros y los datos respectivos de estos numeros (a que intervalo pertenecen y si pertenecen o no ---> [] o () )
    struct num con[4];
    //Rellenamos las variables del grupo a (0)
    getnum(a,&con[0],&con[1],0);
    //Rellenamos las variables del grupo b (1)
    getnum(b,&con[2],&con[3],1);
    //Ordenamos a todos los elementos, de menor a mayor 
    norder(&con[0]);
    sorder(&con[0]);

    //OPERACIONES:
    char *r = uni(&con[0],a,b);
    printf("\nAUB = %s\n",r);
    free(r);
    r = inter(&con[0]);
    printf("AnB = %s\n",r);
    free(r);

    r = dif(&con[0],0);
    printf("A-B = %s\n",r);
    free(r);
    r = dif(&con[0],1);
    printf("B-A = %s\n",r);
    free(r);

    r = comple(a);
    printf("A complement: %s\n",r);
    free(r);
    r = comple(b);
    printf("B complement: %s\n",r);
    free(r);
    for(int i = 0; i < 4; i++)
    {
        free(con[i].str);
    }
}

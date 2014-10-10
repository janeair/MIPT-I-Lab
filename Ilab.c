#include <stdio.h>
#include <math.h>
#include <assert.h>

/*
    Dickarev Oleg. I-Lab. 10 tasks from examination 2007
*/

/*
    1. Transpose of a square matrix (var.2 (A))
*/

void transp_matr()
{
    long a[50][50];
    int i, j, n;
    long temp; // temporary variable for interchage

    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            a[i][j]=0;  // reset array

    scanf("%d", &n);
    assert(n>0 && n<=50);

    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            scanf("%ld", &a[i][j]); // read array

    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)  // transpose array
        {
            temp=a[i][j];
            a[i][j]=a[j][i];
            a[j][i]=temp;
        }

    for (i=0; i<n; i++)
    {
        for (j=0; j<n; j++)
            printf("%ld ", a[i][j]);
        printf("\n");
    }
}


/*
    2. Find NOK of three numbers (var.4 (A))
*/

long nok (long n, long m) // nok for two numbers
{
    long z; // nok(n,m)
    if (n > m) z = n;
          else z = m;
    while (!( (z%n==0) && (z%m==0) )) z++;
    return z;
}

void nok_three_numbers ()
{
    long a, b, c;
    scanf("%ld %ld %ld", &a, &b, &c);
    assert(a>0 && b>0 && c>0);
    printf("\n%ld", nok(nok(a,b),c));
}


/*
    3. Find numbers which dividers are not squares (var.6 (C))
*/

void free_numbers ()
{
    int n, i, flag;
    long numb=0, j;

    scanf("%d", &n);
    assert(n>0 && n<=200);
    for (i=0; i<n; i++)
    {
        flag=0;
        scanf("%ld", &numb);
        assert(numb>=1);
        for (j=2; j<=sqrt(numb); j++)
        {
            if (numb%(j*j)==0) // check divisibility on the j^2
            {
              flag = 1; // if numb does not meet the condition tasks
              break;
            }
        }
        if (flag == 0) printf("%ld ", numb);
    }
}


/*
    4. Find simple numbers (var.1 (A))
*/

int simple (long numb) // check numb | 1 - simple; 0 - not;
{
    int j, flag=1;
    if (numb == 1) return 0;
    for (j=2; j < sqrt(numb)+1; j++)
        if (numb%j == 0)
        {
            flag = 0;
            break;
        }
    return flag;
}

void simple_numbers()
{
    int n, i;
    long number;

    scanf ("%d", &n);
    assert(n>0 && n<10000);
    for (i=0; i < n; i++)
    {
        scanf ("%ld", &number);
        assert(n>=1);
        if ( simple(number) == 1 ) printf ("%ld ", number);
    }
}


/*
    5. Find N-th simple number (var.2 (C))
*/

void n_simple()
{
    int n, i=1;
    long numb=1;

    scanf("%d", &n);
    assert(n>0 && n<=10000);
    do {
        numb++;
        if ( simple(numb)==1 ) i++; // use function "simple" which is described above | 1 - simple; 0 - not;
    }
    while (i < n);
    printf("%ld", numb);
}


/*
    6. Check out whether the weighing (var.1 (C))
       with kettlebells 4^n, n = 0,1,2..
*/

void weighting()
{
    long weight;

    scanf("%ld", &weight);
    assert(weight>=0);
    while( weight > 1)
    {
        if ( weight%4==2 ) break; // weighting isn't possible
        weight/=4;
    }
    if (weight == 1)
        printf("YES"); // weighting successful
    else
        printf("NO");
}


/*
    7. Put the number for the sum of four squares (var.3 (C))
*/

void sum_of_four_squares()
{
    long numb;
    long a, b, c, d;
    int flag = 0; // indicator possible decomposition
    float e;

    scanf("%ld", &numb);
    assert(numb>0);
    e = floor(sqrt(numb));
    for (a=e; a>1 & flag == 0; a--) // search from e downto 1
        for (b=e; b>=0 & flag == 0; b--) // search from e downto 0
            for (c=e; c>=0 & flag == 0; c--) // search from e downto 1
                for (d=0; d<e & flag == 0; d++) // search from 0 to e because d<<numb
                    if (d*d+c*c+b*b+a*a == numb)
                    {
                        printf("%ld %ld %ld %ld", d*d, c*c, b*b, a*a);
                        flag = 1;
                    }
}


/*
    8. Find the sum of range a(k) = x^k/k! (var.5 (A))
*/

void sum_of_range()
{
    int n; // limit
    int k; // counter
    double x, sum=1, y=1; // y - next member of range
    // s = 1 because first member = 1

    scanf("%d %lg", &n, &x);
    assert(n>0 && x>-10.0 && x<10.0);
    for (k=1; k<=n; k++) // sum from 1 to n members of range
    {
        y*=x/k;
        sum+=y;
    }
    printf("%.6lg", sum);

}


/*
    9. Find the sum of dividers (var.5 (B))
*/

void sum_of_dividers()
{
    long numb;
    long i, sum=1; // every number divided by 1

    scanf("%ld", &numb);
    assert(numb>0);
    for(i=2; i<=numb/2; i++) // dividers of number can't be more than numb/2
    if (numb%i == 0) sum+=i;

    if (numb != 1) sum+=numb; // if number != 1, it can be divided by itself
    printf("%ld", sum);
}


/*
    10. Sorting students. First alphabetically, then by marks (var.5 (C))
*/

void organize_student()
{
    struct student // declare the new type - student
    {
        char name[10];
        int mark;
    };
    struct student list[10000];
    int i, j, k; // counters
    int n;

    scanf("%d", &n);
    assert(n>0 && n<10000);
    for (i=0; i<n; i++)
    {
        scanf("%s %d", list[i].name, &list[i].mark);
        assert(list[i].mark>=1 && list[i].mark<=10);
    }

    // sort names alphabetically (bubble method)
    for (i=0; i<n-1; i++)
        for (j=0; j<n-i-1; j++)
        {
            k=-1; // counter of letters in the name
            do
            {
                k++;
                if (list[j].name[k] > list[j+1].name[k]) // compare names in k-letter
                {
                    list[n]=list[j];
                    list[j]=list[j+1];
                    list[j+1]=list[n];
                }
            } while ( list[j].name[k] == list[j+1].name[k] ); // if k-letters are the same, repeat comparing in k+1-letter
        }

    // output sorted array
    for (i=0; i<n; i++)
        printf("\n%s %d", list[i].name, list[i].mark);
    printf("\n");

    // sort marks (bubble method)
    for (i=0; i<n-1; i++)
        for (j=0; j<n-i-1; j++)
        {
            if ( list[j].mark < list[j+1].mark )
            {
                    list[n]=list[j];
                    list[j]=list[j+1];
                    list[j+1]=list[n];
            }
            else
                if ( list[j].mark == list[j+1].mark ) // if marks are the same compare names in alphabetical order
                {
                    k=-1;
                    do
                    {
                        k++;
                        if (list[j].name[k] > list[j+1].name[k]) // same as mentioned above
                        {
                            list[n]=list[j];
                            list[j]=list[j+1];
                            list[j+1]=list[n];
                        }
                    } while ( list[j].name[k] == list[j+1].name[k] );
                }
        }

        // output sorted array
        for (i=0; i<n; i++)
            printf("\n%s %d", list[i].name, list[i].mark);
}

int main()
{
    transp_matr();
    organize_student();
    sum_of_dividers();
    sum_of_range();
    sum_of_four_squares();
    weighting();
    n_simple();
    simple_numbers();
    free_numbers();
    nok_three_numbers();
    return 0;
}

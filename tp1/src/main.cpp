//---------------------------------------------------------------------
// Arquivo      : evalenum.c
// Conteudo     : avaliacao de desempenho de algoritmos de ordenacao
// Autor        : Wagner Meira Jr. (meira@dcc.ufmg.br)
// Historico    : 2023-11-04 - arquivo criado
//---------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <algorithm>

#define ALGINSERTION 1
#define ALGSELECTION 2
#define ALGQSORT 3
#define ALGQSORT3 4
#define ALGQSORTINS 5
#define ALGQSORT3INS 6
#define ALGSHELLSORT 7
#define ALGRECSEL 8
#define ALGBUBBLE 9
#define ALGMERGE 10
#define ALGCOUTING 11
#define ALGBUCKET 12
#define ALGRADIX 13

typedef struct alg {
  int num;
  char *name;
} alg_t;

alg_t algvet[] = {
    {ALGINSERTION, "i"}, {ALGSELECTION, "s"}, {ALGQSORT, "q"},
    {ALGQSORT3, "q3"},   {ALGQSORTINS, "qi"}, {ALGQSORT3INS, "q3i"},
    {ALGSHELLSORT, "h"}, {ALGRECSEL, "rs"},  {ALGBUBBLE, "b"}, {ALGMERGE, "m"}, {ALGCOUTING, "c"},{ALGBUCKET, "bk"}, {ALGRADIX, "rx"}, {0, 0}};

int name2num(char *name) {
  int i = 0;
  while (algvet[i].num) {
    if (!strcmp(algvet[i].name, name))
      return algvet[i].num;
    i++;
  }
  return 0;
}

char *num2name(int num) {
  int i = 0;
  while (algvet[i].num) {
    if (algvet[i].num == num)
      return algvet[i].name;
    i++;
  }
  return 0;
}

typedef struct opt {
  int size;
  int seed;
  int alg;
} opt_t;

typedef struct sortperf {
  int cmp;
  int move;
  int calls;
} sortperf_t;

void resetcounter(sortperf_t *s) {
  // Descricao: inicializa estrutura
  // Entrada:
  // Saida: s
  s->cmp = 0;
  s->move = 0;
  s->calls = 0;
}

void inccmp(sortperf_t *s, int num) {
  // Descricao: incrementa o numero de comparacoes em num
  // Entrada: s, num
  // Saida: s
  s->cmp += num;
}

void incmove(sortperf_t *s, int num) {
  // Descricao: incrementa o numero de movimentacoes de dados em num
  // Entrada: s, num
  // Saida: s
  s->move += num;
}

void inccalls(sortperf_t *s, int num) {
  // Descricao: incrementa o numero de chamadas de função em num
  // Entrada: s, num
  // Saida: s
  s->calls += num;
}

char *printsortperf(sortperf_t *s, char *str, char *pref) {
  // Descricao: gera string com valores de sortperf
  // Entrada: s, pref
  // Saida: str

  sprintf(str, "%s cmp %d move %d calls %d", pref, s->cmp, s->move, s->calls);
  return str;
}

void initVector(int *vet, int size) {
  // Descricao: inicializa vet com valores aleatorios
  // Entrada: vet
  // Saida: vet
  int i;
  // inicializa a parte alocada da vetor com valores aleatorios
  for (i = 0; i < size; i++) {
    vet[i] = (int)(drand48() * size);
  }
}

void printVector(int *vet, int size) {
  // Descricao: inicializa vet com valores aleatorios
  // Entrada: vet
  // Saida: vet
  int i;
  for (i = 0; i < size; i++) {
    printf("%d ", vet[i]);
  }
  printf("\n");
}

void swap(int *xp, int *yp, sortperf_t *s) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
  incmove(s, 3);
}

// shellsort
void shellSort(int *A, int n, sortperf_t *s) {
  inccalls(s, 1);  
  for (int h = n / 2; h > 0; h /= 2) {
    for (int i = h; i < n; i ++) {
      int temp = A[i];
      int j = i;
      inccmp(s, 1);
      incmove(s, 1);
      for (j = i; j >= h && A[j - h] > temp; j = j - h) {
        inccmp(s, 1);
        A[j] = A[j - h];
        incmove(s, 1);
      }
      A[j] = temp;
      incmove(s, 1);
    }
  }
}


// recursive selection sort
void recursiveSelectionSort(int arr[], int l, int r, sortperf_t *s) {
  // find the minimum element in the unsorted subarray `[i…n-1]`
  // and swap it with `arr[i]`
  int min = l;
  inccalls(s, 1);
  for (int j = l + 1; j <= r; j++) {
    // if `arr[j]` is less, then it is the new minimum
    inccmp(s, 1);
    if (arr[j] < arr[min]) {
      min = j; // update the index of minimum element
    }
  }

  // swap the minimum element in subarray `arr[i…n-1]` with `arr[i]`
  if (min != l)
    swap(&arr[min], &arr[l], s);

  if (l + 1 < r) {
    recursiveSelectionSort(arr, l + 1, r, s);
  }
}

// selection sort
void selectionSort(int arr[], int l, int r, sortperf_t *s) {
  inccalls(s,1);
  for (int i= l ; i <= r; i++) {
    int Min = i;
    for (int j = i + 1; j <= r; j++) {
      inccmp(s, 1);
      if (arr[j] < arr[Min]){
        Min = j;}
    }
    if (Min != i){
      swap(&arr[i], &arr[Min], s);}
  }
  return;
}

// insertion sort
void insertionSort(int v[], int l, int r, sortperf_t *s) {
  inccalls(s, 1);
  int j = 0;
  int aux = 0;
  for (int i = l+1; i <= r; i++) {
    incmove(s, 1);
    aux = v[i];
    j = i - 1;
    while ((j >= 0) && (aux < v[j])) {
      inccmp(s, 1);
      v[j + 1] = v[j];
      incmove(s, 1);
      j--;
    }
    inccmp(s, 1);
    v[j + 1] = aux;
    incmove(s, 1);
  }
}

// median of 3 integers
int median(int a, int b, int c) {
  if ((a <= b) && (b <= c))
    return b; // a b c
  if ((a <= c) && (c <= b))
    return c; // a c b
  if ((b <= a) && (a <= c))
    return a; // b a c
  if ((b <= c) && (c <= a))
    return c; // b c a
  if ((c <= a) && (a <= b))
    return a; // c a b
  return b;   // c b a
}

// quicksort partition using median of 3
void partition3(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
  inccalls(s, 1);
  int w = 0;
  *i = l;
  *j = r;

  int pivo = median(A[l], A[l + (r - l) / 2], A[r]);

  int x = pivo; 

  do {
    while (A[*i] < x) {
      (*i)++;
      inccmp(s, 1);
    }
    inccmp(s, 1);
    while (A[*j] > x) {
      (*j)--;
      inccmp(s, 1);
    }
    inccmp(s, 1); 

    if (*i <= *j) {
      swap(&A[*i], &A[*j], s);
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

// standard quicksort partition
void partition(int *A, int l, int r, int *i, int *j, sortperf_t *s) {
  inccalls(s, 1);

  int x, w;
  *i = l;
  *j = r;
  x = A[(*i + *j) / 2]; 
  do {
    while (x > A[*i]) {
      inccmp(s, 1);
      (*i)++;
    }
    inccmp(s, 1);
    while (x < A[*j]) {
      inccmp(s, 1);
      (*j)--;
    }
    inccmp(s, 1);
    if (*i <= *j) {
      swap(&A[*i], &A[*j], s);
      (*i)++;
      (*j)--;
    }
  } while (*i <= *j);
}

// standard quicksort
void quickSort(int *A, int l, int r, sortperf_t *s) {
  if (l < r) {
    int i = 0;
    int j = 0;
    inccalls(s, 1);
    partition(A, l, r, &i, &j, s);
    quickSort(A, l, j, s);
    quickSort(A, i, r, s);
  }
}

// quicksort with median of 3
void quickSort3(int *A, int l, int r, sortperf_t *s) {
  if (l < r) {
    inccalls(s, 1);
    int i, j;
    partition3(A, l, r, &i, &j, s);
    quickSort3(A, l, j, s);
    quickSort3(A, i, r, s);
  }
}

// quicksort with insertion for small partitions
void quickSortIns(int *A, int l, int r, sortperf_t *s) {
  inccalls(s, 1);
  if(l < r){
      int i, j;
      partition(A, l, r, &i, &j, s);
      if(l < j){
        if (j - l <= 50) { 
            insertionSort(A, l, j, s);
        }
        else {
            quickSortIns(A, l, j, s);}
      }
      if (i < r){
          if (r - i <= 50) { 
            insertionSort(A, i, r, s);
        } else {
            quickSortIns(A, i, r, s);}
      }
  }
}


// quicksort with insertion for small partitions and median of 3
void quickSort3Ins(int *A, int l, int r, sortperf_t *s) {
  inccalls(s, 1);
  if(l < r){
      int i, j;
      partition3(A, l, r, &i, &j, s);
      if(l < j){
        if (j - l <= 50) { 
            insertionSort(A, l, j, s);
        }
        else {
            quickSort3Ins(A, l, j, s);}
      }
      if (i < r){
          if (r - i <= 50) { 
            insertionSort(A, i, r, s);
        } else {
            quickSort3Ins(A, i, r, s);}
      }
  }
}

void bubbleSort(int arr[], int n, sortperf_t *s) {
    int i, j;
    inccalls(s, 1);
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            inccmp(s, 1);
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1], s);
            }
        }
    }
}

void merge(int arr[], int l, int m, int r, sortperf_t *s) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // create temp arrays
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // merge the temp arrays back into arr[l..r]
    i = 0; // initial index of first subarray
    j = 0; // initial index of second subarray
    k = l; // initial index of merged subarray

    while (i < n1 && j < n2) {
        inccmp(s, 1);
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            incmove(s, 1);
            i++;
        } else {
            arr[k] = R[j];
            incmove(s, 1);
            j++;
        }
        k++;
    }

    // copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        incmove(s, 1);
        i++;
        k++;
    }

    // copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        incmove(s, 1);
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r, sortperf_t *s) {
    inccalls(s, 1);
    if (l < r) {
        int m = l + (r - l) / 2;

        // sort first and second halves
        mergeSort(arr, l, m, s);
        mergeSort(arr, m + 1, r, s);

        merge(arr, l, m, r, s);
    }
}

void countingSort(int arr[], int n, sortperf_t *s) {
  inccalls(s, 1);
  int i, j;

  int max_val = *std::max_element(arr, arr + n);

  // Alocar memória para o array auxiliar usando malloc
  int* auxiliar = (int*)malloc((max_val + 1) * sizeof(int));
  
  // Inicializar o array auxiliar com zeros
  if (auxiliar == NULL) {
    fprintf(stderr, "Erro ao alocar memória\n");
    exit(EXIT_FAILURE);
  }
  memset(auxiliar, 0, (max_val + 1) * sizeof(int));

  for (i = 0; i < n; i++) {
    auxiliar[arr[i]]++;
    incmove(s, 1);
  }
  for (i = 0, j = 0; i <= max_val; i++) {
    while (auxiliar[i] > 0) {
      inccmp(s, 1);
      arr[j++] = i;
      auxiliar[i]--;
      incmove(s, 1);
    }
  }
  free(auxiliar);
}


void bucketSort(int arr[], int n, sortperf_t *s) {
    inccalls(s, 1);
    int i, j, k;
    int max = *std::max_element(arr, arr + n);
    int min = *std::min_element(arr, arr + n);

    int range = max - min + 1;
    int bucketCount = range / 5 + 1; // Adjust bucket size as needed
    int **buckets = (int **)malloc(bucketCount * sizeof(int *));
    int *bucketSizes = (int *)malloc(bucketCount * sizeof(int));
    for (i = 0; i < bucketCount; i++) {
        buckets[i] = (int *)malloc(n * sizeof(int));
        bucketSizes[i] = 0;
    }

    for (i = 0; i < n; i++) {
        int idx = (arr[i] - min) / 5;
        buckets[idx][bucketSizes[idx]++] = arr[i];
        incmove(s, 1);
    }

    for (i = 0, k = 0; i < bucketCount; i++) {
        if (bucketSizes[i] > 0) {
            insertionSort(buckets[i], 0, bucketSizes[i] - 1, s);
            for (j = 0; j < bucketSizes[i]; j++) {
                arr[k++] = buckets[i][j];
                incmove(s, 1);
            }
        }
        free(buckets[i]);
    }

    free(buckets);
    free(bucketSizes);
}

void countingSortForRadix(int arr[], int n, int exp, sortperf_t *s) {
    int *output = (int *)malloc(n * sizeof(int));
    int count[10] = {0};
    inccalls(s, 1);

    for (int i = 0; i < n; i++) {
        count[(arr[i] / exp) % 10]++;
        incmove(s, 1);
    }
    for (int i = 1; i < 10; i++) {
        count[i] += count[i - 1];
        incmove(s, 1);
    }
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
        incmove(s, 2);
    }
    for (int i = 0; i < n; i++) {
        arr[i] = output[i];
        incmove(s, 1);
    }

    free(output);
}

void radixSort(int arr[], int n, sortperf_t *s) {
    inccalls(s, 1);
    int max = *std::max_element(arr, arr + n);
    
    for (int exp = 1; max / exp > 0; exp *= 10) {
        countingSortForRadix(arr, n, exp, s);
    }
}

void uso()
// Descricao: imprime as opcoes de uso
// Entrada: nao tem
// Saida: impressao das opcoes de linha de comando
{
  fprintf(stderr, "sortperf\n");
  fprintf(stderr, "\t-z <int>\t(vector size)\n");
  fprintf(stderr, "\t-s <int>\t(initialization seed)\n");
  fprintf(stderr, "\t-a <s|i|q|q3|qi|q3i|h|rs>\t(algorithm)\n");
  fprintf(stderr, "\t    s\tselection\n");
  fprintf(stderr, "\t    i\tinsertion\n");
  fprintf(stderr, "\t    q\tquicksort\n");
  fprintf(stderr, "\t    q3\tquicksort+median3\n");
  fprintf(stderr, "\t    qi\tquicksort+insertion\n");
  fprintf(stderr, "\t    q3i\tquicksort+median3+insertion\n");
  fprintf(stderr, "\t    h\theapsort\n");
  fprintf(stderr, "\t    rs\trecursive selection\n");
  fprintf(stderr, "\t    b\tbubble\n");
  fprintf(stderr, "\t    m\tmerge\n");
  fprintf(stderr, "\t    c\tcouting sort\n");
  fprintf(stderr, "\t    bk\tbucket sort\n");
  fprintf(stderr, "\t    rx\tradix sort\n");
}

void parse_args(int argc, char **argv, opt_t *opt)
// Descricao: le as opcoes da linha de comando e inicializa variaveis
// Entrada: argc, argv, opt
// Saida: opt
{
  // variaveis externas do getopt
  extern char *optarg;
  extern int optind;

  // variavel auxiliar
  int c;

  // inicializacao variaveis globais para opcoes
  opt->seed = 1;
  opt->size = 10;
  opt->alg = 1;

  // getopt - letra indica a opcao, : junto a letra indica parametro
  // no caso de escolher mais de uma operacao, vale a ultima
  while ((c = getopt(argc, argv, "z:s:a:h")) != EOF) {
    switch (c) {
    case 'z':
      opt->size = atoi(optarg);
      break;
    case 's':
      opt->seed = atoi(optarg);
      break;
    case 'a':
      opt->alg = name2num(optarg);
      break;
    case 'h':
    default:
      uso();
      exit(1);
    }
  }
  if (!opt->alg) {
    uso();
    exit(1);
  }
}

void clkDiff(struct timespec t1, struct timespec t2, struct timespec *res)
// Descricao: calcula a diferenca entre t2 e t1, que e armazenada em res
// Entrada: t1, t2
// Saida: res
{
  if (t2.tv_nsec < t1.tv_nsec) {
    // ajuste necessario, utilizando um segundo de tv_sec
    res->tv_nsec = 1000000000 + t2.tv_nsec - t1.tv_nsec;
    res->tv_sec = t2.tv_sec - t1.tv_sec - 1;
  } else {
    // nao e necessario ajuste
    res->tv_nsec = t2.tv_nsec - t1.tv_nsec;
    res->tv_sec = t2.tv_sec - t1.tv_sec;
  }
}

int main(int argc, char **argv) {
  sortperf_t s;
  int *vet;
  char buf[200];
  char pref[100];
  opt_t opt;
  struct timespec inittp, endtp, restp;
  int retp;

  // parse_args
  parse_args(argc, argv, &opt);

  // malloc with opt.size+1 for heapsort
  vet = (int *)malloc((opt.size + 1) * sizeof(int));

  // initialize
  resetcounter(&s);
  srand48(opt.seed);
  initVector(vet, opt.size);
  vet[opt.size] = vet[0]; // for heapsort
  printVector(vet, opt.size);

  retp = clock_gettime(CLOCK_MONOTONIC, &inittp);

  // execute algorithm
  switch (opt.alg) {
  case ALGINSERTION:
    insertionSort(vet, 0, opt.size - 1, &s);
    break;
  case ALGSELECTION:
    selectionSort(vet, 0, opt.size - 1, &s);
    break;
  case ALGQSORT:
    quickSort(vet, 0, opt.size - 1, &s);
    break;
  case ALGQSORT3:
    quickSort3(vet, 0, opt.size - 1, &s);
    break;
  case ALGQSORTINS:
    quickSortIns(vet, 0, opt.size - 1, &s);
    break;
  case ALGQSORT3INS:
    quickSort3Ins(vet, 0, opt.size - 1, &s);
    break;
  case ALGSHELLSORT:
    shellSort(vet, opt.size, &s);
    break;
  case ALGRECSEL:
    recursiveSelectionSort(vet, 0, opt.size - 1, &s);
    break;
  case ALGBUBBLE:
    bubbleSort(vet, opt.size, &s);
    break;
  case ALGMERGE:
    mergeSort(vet, 0, opt.size - 1, &s);
    break;
  case ALGCOUTING:
    countingSort(vet, opt.size, &s);
    break;
  case ALGBUCKET:
    bucketSort(vet, opt.size, &s);
    break;
  case ALGRADIX:
    radixSort(vet, opt.size, &s);
    break;
  }
  retp = clock_gettime(CLOCK_MONOTONIC, &endtp);
  clkDiff(inittp, endtp, &restp);

  printVector(vet, opt.size);

  // print stats
  sprintf(pref, "alg %s seed %d size %d time %ld.%.9ld", num2name(opt.alg),
          opt.seed, opt.size, restp.tv_sec, restp.tv_nsec);

  printsortperf(&s, buf, pref);
  printf("%s\n", buf);

  exit(0);
}
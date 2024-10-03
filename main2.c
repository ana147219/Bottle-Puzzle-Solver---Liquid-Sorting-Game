#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>

typedef struct knot
{
    int** matrix;                //stanje matrice
    struct knot** children;      //niz pokazivaca na decu
    struct knot* parent;         //pokazivac na roditelja
    struct knot* left;           //zbog ulancavanja dece, preorder
    struct knot* right;
    int id;                      //print stabla od nula uz inkrementiranje
    int level;                  //nivo cvora u stablu
    int counter;                //ukupan broj dece
    int truth;                 //da li cvor vodi ka resenju
    int moves[20][2];           //matrica mogucih poteza

}knot;

knot* createKnot() {
    knot* new = malloc(sizeof(knot));
    new->children = NULL;                                 //niz pokazivaca na decu
    new->parent = new->right = new->left = NULL;         //pokazivac na roditelja
    new->truth = 0;
    return new;
}


typedef knot** stack;

void PUSH(stack S, int* len, knot* p) {
    S[*len] = p;
    (*len)++;
}

knot* POP(stack S, int* len) {
    knot* x = S[(*len) - 1];
    (*len)--;
    return x;
}

int** LCG(int n, int k)
{
    double Xn, Xn1;
    unsigned long long m = pow(2, 31), a = 429493445, c = 907633385;
    int indexes[21] = { 0 }, ** bottles, i, j, index;
    bottles = calloc(5, sizeof(int*));
    if (bottles == NULL) return 0;
    for (i = 0;i < 5;i++)
    {
        bottles[i] = calloc(n, sizeof(int));
        if (bottles[i] == NULL) return 0;
    }
    printf("Tell me your favorite number: ");
    scanf("%lf", &Xn);
    printf("\n");
    for (j = 0; j < n - k; j++)
    {
        for (i = 0;i < 4;i++)
        {
            Xn1 = ((unsigned long long)(a * Xn + c) % m);
            index = (int)(Xn1 / m * (n - k));
            Xn = Xn1;
            if (indexes[index] == 4)
            {
                i--;
                continue;
            }
            indexes[index]++;
            bottles[i][j] = index + 1;
        }
    }
    return (bottles);
}
int counting_top(int** bottles, int j)
{
    int i = 0, s, counter = 1;
    while (bottles[i][j] == 0 && i < 4) i++;
    if (i < 3)
    {
        for (s = i;s < 3;s++)
        {
            if (bottles[s][j] == bottles[s + 1][j]) counter++;
            else
                return counter;
        }
        return counter;
    }
    if (i == 3) return counter;
    return 0; //prazna bocica
}
int canI_pour(int** bottles, int j1, int j2) //1u2
{
    int i = 0, s = 0;
    if (bottles[4][j1] == 4) return 0;
    if (bottles[4][j2] == 4) return 1;
    if (bottles[4][j2] == 0) return 0;
    while (bottles[i][j1] == 0 && i < 4) i++;
    while (bottles[s][j2] == 0 && s < 4) s++;
    if (bottles[i][j1] == bottles[s][j2]) return 1;
    else
        return 0;
}
int done(int** bottles, int n)
{
    int i, j;
    for (j = 0;j < n;j++)
    {
        if (counting_top(bottles, j) == 4 || counting_top(bottles, j) == 0) continue;
        return 0;
    }
    return 1;
}
int** copy_matrix(int** bottles, int n)
{
    int** bottles_next, i, j;
    bottles_next = calloc(5, sizeof(int*));
    if (bottles_next == NULL) return 0;
    for (i = 0;i < 5;i++)
    {
        bottles_next[i] = calloc(n, sizeof(int));
        if (bottles[i] == NULL) return 0;
        for (j = 0;j < n;j++) bottles_next[i][j] = bottles[i][j];
    }
    return bottles_next;
}
int** pour(int** bottles, int n, int j1, int j2) //1u2
{
    int** bottles_next, counter;
    bottles_next = copy_matrix(bottles, n);
    counter = counting_top(bottles_next, j1);
    while (counter > 0)
    {
        if (canI_pour(bottles_next, j1, j2))
        {
            bottles_next[(bottles_next[4][j2]--) - 1][j2] = bottles_next[bottles_next[4][j1]][j1];
            bottles_next[(bottles_next[4][j1]++)][j1] = 0;
            counter--;
        }
        else break;
    }
    return bottles_next;
}
void matrix(int** bottles, int n)
{
    int i, j;
    char colours[21][20] = { "empty","yellow","green","red","purple","blue","pink","azure","grey","black","white","beige","bistre","bittersweet","orange","canary","carmine","celadon","cherry","chestnut","cinnamon" };
    for (i = 0;i < 4;i++)
    {
        for (j = 0;j < n - 1;j++) printf("%-16s ", colours[bottles[i][j]]);
        printf("%-16s\n", colours[bottles[i][n - 1]]);
    }
}

int make_tree(knot* root, int n, int steps)
{
    stack S = malloc(1000 * sizeof(knot*));
    int len = 0;
    PUSH(S, &len, root);
    int id = 1, goal = 0;
    while (len > 0)
    {
        knot* sibling = POP(S, &len);
        if (sibling == NULL) break;
        if (sibling->level == steps)
        {
            sibling->counter = 0;
            continue;
        }
        int s = 0, i, j;
        for (i = 0;i < n; i++)
        {
            for (j = 0;j < n;j++)
            {
                if (i != j && canI_pour(sibling->matrix, i, j) == 1)
                {
                    sibling->moves[s][0] = i;
                    sibling->moves[s][1] = j;
                    s++;
                }
            }
        }
        sibling->counter = s;
        sibling->children = calloc(s, sizeof(knot*));

        for (i = 0;i < s;i++)
        {
            knot* child = createKnot();
            knot* current, * father = sibling;
            child->id = id++;
            child->level = father->level + 1;
            child->parent = father;
            child->matrix = pour(father->matrix, n, father->moves[i][0], father->moves[i][1]);
            child->truth = done(child->matrix, n);
            father->children[i] = child;

            if (child->truth == 1)
            {
                current = child;
                child->counter = 0;
                while (current->parent != NULL)
                {
                    current->truth = 1;
                    current = current->parent;
                }
                goal = 1;
                continue;
            }
            PUSH(S, &len, child);
        }
        sibling->left = sibling->children[0];
        for (i = 0;i < s - 1;i++) {
            sibling->children[i]->right = sibling->children[i + 1];
        }

    }
    return goal;
}

void preorderN(knot* root, int n) {
    stack S = malloc(100000 * sizeof(knot*));
    int len = 0, i, j;
    knot* next;
    PUSH(S, &len, root);
    while (len > 0) {
        next = POP(S, &len);
        while (next) {
            matrix(next->matrix, n);
            printf("\n");
            if (next->right) {
                PUSH(S, &len, next->right);
            }
            next = next->left;
        }
    }
}
void hint(knot* current, int n)
{
    int bottle1, bottle2, q;
    for (q = 0;q < current->counter;q++)
    {
        if (current->children[q]->truth)
        {
            for (int z = 0;z < n;z++)
            {
                if (current->matrix[4][z] < current->children[q]->matrix[4][z]) bottle1 = z;
                if (current->matrix[4][z] > current->children[q]->matrix[4][z]) bottle2 = z;
            }
            printf("Pour from %d to %d\n", bottle1, bottle2);
            break;
        }
        else continue;
    }
}
int main()
{
    int** bottles, i, j, n, k, option, steps, tree;
    printf("Enter the number of bottles and the number of empty bottles: ");
    scanf("%d %d", &n, &k);
    printf("\n");
    printf("Enter the max number of steps: ");
    scanf("%d", &steps);
    printf("\n");

    bottles = LCG(n, k);
    knot* root, * current;
    stack* top = NULL;
    root = calloc(1, sizeof(knot));
    if (root == NULL) return 0;
    root->matrix = bottles;
    root->parent = NULL;
    root->level = 0;
    root->id = 10;
    root->truth = 1;
    current = root;
    char colours[21][20] = { "empty","yellow","green","red","purple","blue","pink","azure","grey","black","white","beige","bistre","bittersweet","orange","canary","carmine","celadon","cherry","chestnut","cinnamon" };
    for (i = n - k;i < n;i++) bottles[4][i] = 4;


    //ISPIS POCETNOG STANJA
    for (i = 0;i < 4;i++)
    {
        for (j = 0;j < n - 1;j++) printf("%-16s ", colours[bottles[i][j]]);
        printf("%-16s\n", colours[bottles[i][n - 1]]);
    }
    printf("\n");
    tree = make_tree(root, n, steps);

    //start meni
    printf("1. Im playing\n");
    printf("2. Give me a hint\n");
    printf("3. Show me step by step \n");
    printf("4. Show me a tree \n");
    printf("5. Stop\n");

    i = 0;
    while (i < steps)
    {
        printf("Choose an option: ");
        scanf("%d", &option);
        printf("\n");
        if (option == 1)
        {
            int j1, j2;
            printf("Make a move x->y?: ");
            scanf("%d %d", &j1, &j2);
            printf("\n");
            if (canI_pour(current->matrix, j1, j2) == 0)
            {
                printf("Unable to pour, repeat your move\n");
                continue;
            }
            for (j = 0;j < current->counter;j++)
            {
                if (current->moves[j][0] == j1 && current->moves[j][1] == j2)
                {
                    current = current->children[j];
                    break;
                }
            }
            matrix(current->matrix, n);
            if (current->truth == 0)
            {
                printf("Bad move! The game is over");
                return 0;
            }
            if (done(current->matrix, n))
            {
                printf("ENDGAME! You are a star!");
                return 0;
            }
            i++;
        }
        if (option == 2) hint(current, n);

        if (option == 3)
        {
            while (current->counter != 0)
            {
                for (int m = 0;m < current->counter;m++)
                {
                    if (current->children[m]->truth == 1)
                    {
                        current = current->children[m];
                        hint(current->parent, n);
                        matrix(current->matrix, n);
                        break;
                    }
                }
            }
        }

        if (option == 4) preorderN(root, n);
        if (option == 5) exit(-1);
    }
    return 0;
}

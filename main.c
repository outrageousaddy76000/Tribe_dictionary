#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int freq;
    int height;
    char word[10];
    char meaning[10];
    struct node *left, *right;
};

struct node* root = NULL;

void inorder(struct node* node)
{
    if (node == NULL)
        return;

    /* first recur on left child */
    inorder(node->left);

    /* then print the data of node */
    printf("Word - %s -> Meaning - %s --- Search Frequency - %d\n", node->word,node->meaning,node->freq);

    /* now recur on right child */
    inorder(node->right);
}

int max(int a,int b){
    if(a>b) return a;
    else return b;
}

int height(struct node *N){
    if (N == NULL)
        return 0;
    return 1+max(height(N->left), height(N->right));
}

struct node* newnode(char word[],char meaning[]){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->freq = 0;
    temp->height = 0;
    strcpy(temp->word,word);
    strcpy(temp->meaning,meaning);
    temp->left = temp->right = NULL;
    return temp;
}

struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = height(y);
    x->height = height(x);

    // Return new root
    return x;
}

// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = height(x);
    y->height = height(y);

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct node* insert(struct node* node, char word[],char meaning[])
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newnode(word,meaning));

    if (strcmp(word,node->word) < 0)
        node->left  = insert(node->left, word,meaning);
    else if (strcmp(word,node->word) > 0)
        node->right = insert(node->right, word,meaning);
    else{
        printf("Word already has a meaning in dictionary!\n");
         // Same words are not allowed
        return node;
    }
    /* 2. Update height of this ancestor node */
    node->height = height(node);

    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && strcmp(word,(node->left)->word) < 0)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && strcmp(word,(node->right)->word) > 0)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && strcmp(word,(node->left)->word)>0)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && strcmp(word,(node->right)->word)<0)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}

struct node * search(struct node *node,char word[]){
    while (node != NULL){
        if (strcmp(word,node->word)>0)
        {
            return search(node->right, word);
        }
        else if (strcmp(word,node->word)<0)
        {
            return search(node->left, word);
        }
        else
        {
            printf("Word - %s\nMeaning - %s\n",node->word,node->meaning);
            node->freq++;
            return 1;
        }
    }
    return 0;
}

int main()
{
    FILE *dict = fopen("dict.txt","r+"); //Reads file and adds all meanings to the avl tree
    char line[21];
    while(fgets(line,sizeof(line),dict)){
        char word[10] ="";
        char meaning[10]="";
        int i=0;
        while(line[i]!=' '){
            word[i]=line[i];
            i++;
        }
        int j=0;
        i++;
        while(line[i]!='\n'){
            meaning[j]=line[i];
            i++;
            j++;
        }
        root=insert(root,word,meaning);
    }
    //Phase - 1 - Building
    int addtodict;
    printf("Do you want to add words to the dictionary?\n1.Yes\nAny Other Key - No\nYour Choice : ");
    scanf("%d",&addtodict);
    if(addtodict==1)
    while(1){
        char word[10],meaning[10];
        printf("\nEnter the word you want to add to the dictionary : ");
        scanf("%s",word);
        printf("\nEnter the meaning of the word : ");
        scanf("%s",meaning);
        for(int i=0;i<=strlen(word);i++){
            if(word[i]>=65&&word[i]<=90)
                word[i]=word[i]+32;
        }
        for(int i=0;i<=strlen(meaning);i++){
            if(meaning[i]>=65&&meaning[i]<=90)
                meaning[i]=meaning[i]+32;
        }
        fputs(word,dict);
        fputc(' ',dict);
        fputs(meaning,dict);
        fputc('\n',dict);
        root = insert(root,word,meaning);
        int choice;
        printf("\nDo you want to add more words to the dictionary?\n1.Yes\nAny Other Key - EXIT\nYour Choice : ");
        scanf("%d",&choice);
        if(choice==1){
            continue;
        }
        else {
            break;
        }
    }
    //Phase - 2 - Translation
    while(1){
        printf("\n\nSearch the dictionary ---\nEnter the word you want to know the meaning of : ");
        char word[10];
        scanf("%s",word);
        for(int i=0;i<=strlen(word);i++){
            if(word[i]>=65&&word[i]<=90)
                word[i]=word[i]+32;
        }
        if(!search(root,word)){
            int c;
            printf("\nWord not found in dictionary!\nDo you wish to add the word in the dictionary?\n1.Yes\nAny Other Key - No\nYour Choice : ");
            scanf("%d",&c);
            if(c==1){
                char meaning[10];
                printf("\nEnter the meaning of the word : ");
                scanf("%s",meaning);
                for(int i=0;i<=strlen(meaning);i++){
                    if(meaning[i]>=65&&meaning[i]<=90)
                        meaning[i]=meaning[i]+32;
                }
                fputs(word,dict);
                fputc(' ',dict);
                fputs(meaning,dict);
                fputc('\n',dict);
                root=insert(root,word,meaning);
            }
        }
        int choice3;
        printf("Do you want to know another word's meaning?\n1.Yes\nAny Other Key - EXIT\nYour Choice : ");
        scanf("%d",&choice3);
        if(choice3 == 1){
            continue;
        }
        else{
            break;
        }
    }
    printf("\nAll the words in dictionary are(in alphabetical order) ---\n");
    inorder(root);
    printf("\nDictionary closed!");
    return 0;
}


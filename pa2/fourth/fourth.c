#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fourth.h"

typedef struct graphvert * gptr;
typedef struct hashnode * hptr;

gptr* initALL(char *name,int pos,gptr* ALL){
  ALL[pos]=malloc(sizeof(struct graphvert));
  char *temp=malloc(strlen(name)+1);
  strcpy(temp,name);
  ALL[pos]->name=temp;
  ALL[pos]->index=pos;
  ALL[pos]->next=0;
  ALL[pos]->outdeg=0;
  ALL[pos]->indeg=0;
  //printf("%s",ALL[pos]->name);
  return ALL;
}

void mergesort(int l,int h, gptr* ALL){
  if(h-l==0){
    return;
  }
  mergesort(l,(h+l)/2,ALL);
  //printf("L: %d ",l);
  mergesort((l+h)/2+1,h,ALL);
  //printf("R: %d ",l);
  merge(l,h,ALL);
  return;
}

void merge(int l, int h, gptr* ALL){
  int rightsi=(h-l+1)/2;
  int leftsi=(h-l+1)/2;
  if((h-l)%2==0){
    leftsi=rightsi+1;
  }
  gptr* tl=malloc(sizeof(gptr)*(leftsi));
  gptr* tr=malloc(sizeof(gptr)*rightsi);
  for(int i=0;i<leftsi;i++){
    tl[i]=ALL[l+i];
  }
  for(int i=0;i<rightsi;i++){
    tr[i]=ALL[(l+h)/2+1+i];
  }

  int indmain=l;
  int indl=0;
  int indr=0;
  while(indl!=leftsi || indr!=rightsi){
    if(indl==leftsi){
      ALL[indmain]=tr[indr];
      indr++;
      indmain++;
      continue;
    }
    if(indr==rightsi){
      ALL[indmain]=tl[indl];
      indl++;
      indmain++;
      continue;
    }
    int cmp=strcmp(tl[indl]->name,tr[indr]->name);
    if(cmp<=0){
      ALL[indmain]=tl[indl];
      indl++;
      indmain++;
      continue;
    }
    else{
      ALL[indmain]=tr[indr];
      indr++;
      indmain++;
    }
  }
  free(tl);
  free(tr);
}

void resetind(gptr* ALL,int n){
  for (int i=0;i<n;i++){
    gptr temp=ALL[i];
    temp->index=i;
  }
}

gptr* insert(char* conn,int connindex,int weight, int index,gptr *ALL){
  gptr temp = ALL[index]->next;
  gptr prev =ALL[index];
  gptr ins = malloc(sizeof(struct graphvert));
  char *nametemp=malloc(strlen(conn)+1);
  strcpy(nametemp,conn);
  ins->name=nametemp;
  ins->index=connindex;
  ins->outdeg=0;
  ins->indeg=0;
  ins->weight=weight;
  prev->outdeg+=1;
  ALL[connindex]->indeg+=1;
  while(temp!=0){
    int check=strcmp(conn,temp->name);
    if(check<0){
      prev->next=ins;
      ins->next=temp;
      return ALL;
    }
    if(check==0){
      ALL[index]->outdeg-=1;
      free(nametemp);
      free(ins);
      return ALL;
    }
    temp=temp->next;
    prev=prev->next;
  }
  prev->next=ins;
  ins->next=temp;  
  return ALL;
}

void getindegree (int num, gptr* ALL){
  printf("%d\n",ALL[num]->indeg);
}

void getoutdegree (int num, gptr* ALL){
  printf("%d\n",ALL[num]->outdeg);
}

void getchain (int num, gptr* ALL){
  gptr temp=ALL[num]->next;
  while(temp!=0){
    if(temp->next==0){
      printf("%s",temp->name);
    }
    else{
      printf("%s ",temp->name);
    }
    temp=temp->next;
  }
  printf("\n");
}

hptr* initHASH(hptr* HASH, int n){
  for(int i=0;i<n;i++){
    HASH[i]=0;
  }
  return HASH;
}

hptr* insertHASH(char *name, int pos, hptr*HASH, int n){
  int hc=0;
  for(int i=0;i<strlen(name);i++){
    hc+=name[i];
  }
  //printf("%s -> %d\n",name,hc%n);
  int hi=hc%n;
  hptr temp= malloc(sizeof(struct hashnode));
  char *nametemp=malloc(strlen(name)+1);
  strcpy(nametemp,name);
  temp->name=nametemp;
  temp->hashcode=hc;
  temp->index=pos;
  if(HASH[hi]==0){
    temp->next=0;
  }
  else{
    temp->next=HASH[hi];
  }
  HASH[hi]=temp;
  return HASH;
}

int getIndex(char *name, int n,hptr *HASH){
  int hc=0;
  for(int i=0;i<strlen(name);i++){
    hc+=name[i];
  }
  int hi = hc%n;
  hptr temp=HASH[hi];
  while(temp!=0){
    if(strcmp(temp->name,name)==0){
      return temp->index;
    }
    temp=temp->next;
  }
  return -1;
}
  
void printALL(gptr* ALL,int n){
  for (int i=0;i<n;i++){
    gptr temp=ALL[i];
    while(temp!=0){
      printf("%s in(%d) out(%d)",temp->name, temp->indeg,temp->outdeg);
      temp=temp->next;
    }
    printf("\n");
  }
}
void printHASH(hptr *HASH,int n){
  for(int i=0;i<n;i++){
    hptr temp=HASH[i];
    while(temp!=0){
      printf("%s -> %d", temp->name,temp->index);
      temp=temp->next;
    }
    printf("\n");
  }
}

void freenodes (hptr *HASH,gptr* ALL, int n){
  for(int i=0;i<n;i++){
    hptr prev = 0;
    hptr temp = HASH[i];
    while(temp!=0){
      prev=temp;
      temp=temp->next;
      free(prev->name);
      free(prev);
    }
    /*if(temp==0 && prev!=0){
      free(prev->name);
      free(prev);
      }*/
    gptr prev1 = 0;
    gptr temp1 = ALL[i];
    while(temp1!=0){
      prev1=temp1;
      temp1=temp1->next;
      free(prev1->name);
      free(prev1);
    }
    /*if(prev1!=0 && temp1==0){
      free(prev1->name);
      free(prev1);
      }*/
  }
  //free(HASH);
  //free(ALL);
}
/*
void freeLL(gptr* ALL,int size){
   gptr prev1 = 0;
   gptr temp1 = ALL[i];
   while(temp1!=0){
      prev1=temp1;
      temp1=temp1->next;
      free(prev1->name);
      free(prev1);
    }
}
*/
void dfs(gptr*ALL,hptr*HASH,int n){
  for(int i=0;i<n;i++){
    if(ALL[i]->visited==1){continue;}
    else{
      dfshelp(ALL[i],ALL,HASH,n);
    }
  }
  printf("\n");
}

void dfshelp(gptr L, gptr*ALL,hptr*HASH,int n){
  if(L==0 || L->visited==1){return;}
  printf("%s ",L->name);
  L->visited=1;
  L=L->next;
  while(L!=0){
    dfshelp(ALL[L->index],ALL,HASH,n);
    L=L->next;
  }
  return;
}

int main(int argc, char* argv[argc+1]){
  int n=0;
  gptr* ALL=0;
  hptr* HASH=0;
  char*name=malloc(20);
  char* conn=malloc(20);
  for(int i=1;i<argc;i++){
    FILE *curr=fopen(argv[i],"r");
    if(curr==0){
      printf("error\n");
      return EXIT_SUCCESS;
    }
    fscanf(curr,"%d",&n);
    ALL=malloc(n*sizeof(struct graphvert*));
    HASH=malloc(n*sizeof(struct hashnode*));
    initHASH(HASH,n);
    for(int j=0;j<n;j++){
      fscanf(curr,"%s",name);
      ALL=initALL(name,j,ALL);
    }
    mergesort(0,n-1,ALL);
    resetind(ALL,n);

    for(int j=0;j<n;j++){
       HASH=insertHASH(ALL[j]->name, j, HASH,n);
    }
    //printALL(ALL,n);
    int weight=0;
    while(fscanf(curr,"%s %s %d\n", name, conn,&weight)!=EOF){
      //printf("%s -> %s\n",name,conn);
      ALL=insert(conn,getIndex(conn,n,HASH),weight,getIndex(name,n,HASH),ALL);
    }
    fclose(curr);
  }
  dfs(ALL,HASH,n);
  //printALL(ALL,n);
  //printHASH(HASH,n);
  freenodes(HASH,ALL,n);
  free(HASH);
  free(ALL);
  free(name);
  free(conn);
  return EXIT_SUCCESS;
}

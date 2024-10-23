#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
typedef struct{
    double a1,a2;
    int clusterId;
}point;
double distance(point p1,point p2)
{return sqrt(pow((p1.a1-p2.a1),2)+pow((p1.a2-p2.a2),2));
}
void randomcenter(point* centers,int k,double minx,double maxx,double miny,double maxy)
{int i;
srand(time(NULL));
for(i=0;i<k;i++)
{centers[i].a1=minx+(rand()/(double)RAND_MAX)*(maxx-minx);
centers[i].a2=miny+(rand()/(double)RAND_MAX)*(maxy-miny);
centers[i].clusterId=i;
}
}
int assignClusters(point* points,point* centers,int n,int k)
{int c=0,i,j;
for(i=0;i<n;i++)
{double minDist=distance(points[i],centers[0]);;
int newClId=points[i].clusterId;
if(newClId==-1)
newClId=0;
for(j=1;j<k;j++)
{double dist=distance(points[i],centers[j]);
if(dist<minDist)
{minDist=dist;
newClId=j;
}
}
if(points[i].clusterId!=newClId)
{points[i].clusterId=newClId;
c++;
}
}
return c;
}
void recompute(point* points,point* centers,int n,int k)
{int* clusterSizes=(int*)calloc(k,sizeof(int));
point* newCenters=(point*)calloc(k,sizeof(point));
int i,j;
for(i=0;i<n;i++)
{newCenters[points[i].clusterId].a1+=points[i].a1;
newCenters[points[i].clusterId].a2+=points[i].a2;
clusterSizes[points[i].clusterId]++;
}
for(j=0;j<k;j++)
{if(clusterSizes[j]>0)
{centers[j].a1=newCenters[j].a1/clusterSizes[j];
centers[j].a2=newCenters[j].a2/clusterSizes[j];
}
}
free(clusterSizes);
free(newCenters);
}
void main()
{int n,k,i;
point* points=NULL;
FILE* file=fopen("data.txt","r");
if(file==NULL)
printf("Failed to open file");
else
{fscanf(file,"%d",&n);
points=(point*)malloc(n*sizeof(point));
for(i=0;i<n;i++)
{fscanf(file,"%lf %lf",&points[i].a1,&points[i].a2);
points[i].clusterId=-1;
}
fclose(file);
printf("Enter the number of clusters k:");
scanf("%d",&k);
point* centers=(point*)malloc(k*sizeof(point));
double minx=points[0].a1,maxx=points[0].a1,miny=points[0].a2,maxy=points[0].a2;
for(i=1;i<n;i++)
{if(points[i].a1<minx)
minx=points[i].a1;
if(points[i].a1>maxx)
maxx=points[i].a1;
if(points[i].a2<miny)
miny=points[i].a2;
if(points[i].a2>maxy)
maxy=points[i].a2;
}
randomcenter(centers,k,minx,maxx,miny,maxy);
int c;
do
{c=assignClusters(points,centers,n,k);
recompute(points,centers,n,k);
} while(c>0);
for(i=0;i<k;i++)
printf("Cluster %d:(%.2lf,%.2lf)\n",i,centers[i].a1,centers[i].a2);
for(i=0;i<n;i++)
printf("Point (%.2lf,%.2lf) belongs to cluster %d\n",points[i].a1,points[i].a2,points[i].clusterId);
free(points);
free(centers);
}
}

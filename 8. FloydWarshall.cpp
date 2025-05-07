#include<iostream>
using namespace std;
#define V 5
#define INF 99999


void printsolution(int dist[V][V]){
	cout<<"\ndisplaying :\n";
	
	for(int i=0;i<V;i++){
		for(int j=0;j<V;j++){
			if(dist[i][j]==INF){
				cout<<"INF"<<"   ";
			}
			else{
				cout<<dist[i][j]<<"   ";
			}

		}
					cout<<endl;
	}
}


void flyodwarshall(){

    int dist[V][V];
    for (int i=0; i<V;i++){
        for (int j=0;j<V;j++)
        {
            if (i!=j){
            cout<<"is there edge in "<<i <<"and"<<j;
          int ch;
          cin>> ch;
          if(ch==1){
            cout<<"enter weight ";
            int w;
            cin>>w;
            dist[i][j]=w;


          }
          else { dist[i][j] = INF ;} 

        }
    }
    }
	int i,j,k;
	
	for(k=0;k<V;k++)
	{
		for(i=0;i<V;i++)
		{
			for(j=0;j<V;j++)
			{
				if((dist[i][j]>dist[i][k]+dist[k][j])&&dist[k][j]!=INF && dist[i][k]!=INF){
					dist[i][j]=dist[i][k]+dist[k][j];					
				}
			}
		}
	}
	printsolution(dist);
}






int main ()
{
    
    flyodwarshall() ;
    return 0;
}

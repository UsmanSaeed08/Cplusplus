
//seq 2 horizontal ata hai!!!




#include<stdio.h>
#include<conio.h>
#include<iostream.h>
#include<string.h>

struct node
{
	char seq1;
	char seq2;
	int origin[3];
	int score;
	int index;
	node *next;
	node *pre;
	node *up;
	node *down;
};

node * addnode(node*,char,char,int[],int,int);
node* addnode1(node*,char,char,int[],int,int);
node* addnode2(node*,char,char,int[],int,int,int,int);

void dpnode(node*,int);
void chek(int,int,int);
void tracebak(node*,int);
//void display(int,int,char [],char []);

int og[3];
//int arr[100][100];

node *start;

void main(void)
{
	
	
	char c[20];
	char c1[20];
	int gap,mm,m,x,y;
	int diagonal,upside,leftside;
	int p=0,q=0;
	
	node *temp;
	
	cout<<"enter sequence 1"<<endl;
	cin>>c;
	cout<<"enter sequence 2"<<endl;
	cin>>c1;
	
	x=strlen(c);
	y=strlen(c1);
	/*
	int k=x+1,l=y+1;
	int **arr;
	arr=new int *[l];					Dynamic 2-D
	for(int i=0;i<k;i++)
	{
	arr[i]=new int [l];
	}
	*/
	//ptr[2][2]=10;
	//cout<<ptr[2][2];
	
	
	int l=x;
	int k=y;
	
	
	/*for(int i=0;i<=k;i++)
	{
	
	  for(int j=0;j<=l;j++)
	  {
	  arr[i][j]=0;
	  
		}
}*/
	
	cout<<"The string length of sequence of one is :"<<x<<endl;
	cout<<"The string length of sequence of two is :"<<y<<endl;
	
	cout<<"enter gap penalty"<<endl;
	cin>>gap;
	cout<<"enter mismatch penalty"<<endl;
	cin>>mm;
	cout<<"enter match score"<<endl;
	cin>>m;
	
	
	
	//use these lengths to make the 2D aray size accordingly.
	
	//temp=new node;
	temp=NULL;
	
	og[0]=0;
	og[1]=0;
	og[2]=0;
	
	//arr[0][0]=0;
	
	for(int i=0;i<=k;i++)
	{
		temp=addnode1(temp,c[p],c1[q],og,gap,i);
	}
	int index=i;
	//for(i=1;i<=l+1;i++)
	//{
	//	addnode2(temp,c[p],c1[q],og,gap,i);
	//}
	
	
	
	for(int r=1;r<=l;r++)
	{
		
		temp=addnode2(temp,c[p],c1[q],og,gap,r,l,index);
		index++;
		
		for(int d=1;d<=k;d++)
		{
			og[0]=0;
			og[1]=0;
			og[2]=0;
			
			if (c[p]==c1[q])
			{
				diagonal=temp->up->score+m;
			}
			else
			{
				diagonal=temp->up->score+mm;
			}
			leftside=temp->score+gap;
			upside=temp->up->next->score+gap;
			
			
			/*diagonal=arr[r-1][d-1]+m;
			leftside=arr[r][d-1]+gap+m;
			upside=arr[r-1][d]+gap+m;
			*/
			chek(leftside,upside,diagonal);
			
			
			
			if(leftside>upside && leftside>diagonal)	//leftside a[r][d-1] upseide a[r-1][d]
			{
				
				//arr[r][d]=leftside;						//trace bak
				temp=addnode(temp,c[p],c1[q],og,leftside,index);
				index++;
				
			}
			else if(upside>leftside && upside>diagonal)
			{
				
				//arr[r][d]=upside;
				temp=addnode(temp,c[p],c1[q],og,upside,index);
				index++;
			}
			else if(diagonal>leftside && diagonal>upside)
			{
				
				//arr[r][d]=arr[r-1][d-1]+m;
				temp=addnode(temp,c[p],c1[q],og,diagonal,index);
				index++;
			}
			/*else if(diagonal>upside)
			{
			
			  //arr[r][d]=arr[r-1][d-1]+m;
			  temp=addnode(temp,c[p],c1[q],og,diagonal,index);
			  index++;
			  }
			*/
			
			/*else 
			{
			diagonal=temp->up->score+mm;
			leftside=temp->score+gap;
			upside=temp->up->next->score+gap;
			
			  /*diagonal=arr[r-1][d-1]+mm;
			  upside=arr[r-1][d]+gap;
			  leftside=arr[r][d-1]+gap;
			  
				chek(leftside,upside,diagonal);
				
				  if(diagonal>upside && diagonal>leftside)
				  {
				  
					//arr[r][d]=diagonal;
					temp=addnode(temp,c[p],c1[q],og,diagonal,index);
					index++;
					}
					else if(upside>leftside)
					{
					
					  //arr[r][d]=upside;
					  temp=addnode(temp,c[p],c1[q],og,upside,index);
					  index++;
					  }
					  else
					  {
					  
						//arr[r][d]=leftside;
						temp=addnode(temp,c[p],c1[q],og,leftside,index);
						index++;
						}
		}*/
			q++;
			
		}
		p++;
		q=0;
	}
	//	display(k,l,c,c1);
	dpnode(start,k);
	tracebak(temp,l);
	
}


/*void display(int k,int l,char c[],char c1[])
{
cout<<"		";
for (int a=0;a<=k-1;a++)
{
cout<<c1[a];
cout<<"		";
}

  /*for(int b=0;b<=l-1;b++)
  {
  cout<<c[b]<<endl;
  }
  
	for(int i=0;i<=k-1;i++)
	{
	cout<<endl;
	for(int j=0;j<=l-1;j++)
	{
	cout<<arr[i][j];
	cout<<"		";
	}
	}
	
	  
		cout<<endl;
		cout<<endl<<endl;
		cout<<"i love caty"<<endl;
		return ;
}*/

node * addnode(node *temp,char sq1,char sq2,int org[],int score,int index)
{
	
	if (temp==NULL)
	{
		start->pre=NULL;
		start->next=NULL;
		start->seq1=sq1;
		start->seq2=sq2;
		start->origin[0]=org[0];
		start->origin[1]=org[1];
		start->origin[2]=org[2];
		
		temp=start;
		return temp;
	}
	node *temp1;
	temp1=new node;
	
	temp1->pre=temp;
	temp->next=temp1;
	temp1->next=NULL;
	temp1->down=NULL;
	temp1->up=temp->up->next;
	temp1->up->down=temp1;
	temp=temp1;
	
	temp1->score=score;
	temp1->index=index;
	
	temp1->seq1=sq1;
	temp1->seq2=sq2;
	
	temp1->origin[0]=org[0];
	temp1->origin[1]=org[1];
	temp1->origin[2]=org[2];
	
	return temp;
}

node* addnode1(node *temp,char sq1,char sq2,int org[],int gap,int gapno)
{
	
	if (start==NULL)
	{
		start=new node;
		start->pre=NULL;
		start->next=NULL;
		start->up=NULL;
		start->down=NULL;
		
		start->seq1=NULL;
		start->seq2=NULL;
		start->score=0;
		start->index=1;
		
		start->origin[0]=org[0];
		start->origin[1]=org[1];
		start->origin[2]=org[2];
		
		temp=start;
		return temp;
	}
	node *temp1;
	temp1=new node;
	
	temp1->pre=temp;
	temp->next=temp1;
	temp1->next=NULL;
	temp1->up=NULL;
	temp1->down=NULL;
	temp=temp1;
	temp1->index=gapno;
	
	temp1->score=gap*gapno;
	temp1->seq1=NULL;
	temp1->seq2=NULL;
	
	temp1->origin[0]=org[0];
	temp1->origin[1]=org[1];
	temp1->origin[2]=org[2];
	
	return temp;
}

node* addnode2(node *temp,char sq1,char sq2,int org[],int gap,int gapno,int k,int index)
{
	node *temp1;
	temp1= new node;
	
	if (gapno==1)
	{
		start->down=temp1;
		
		temp1->pre=temp;
		temp->next=temp1;
		temp1->next=NULL;
		temp1->up=start;
		temp1->down=NULL;
		temp1->index=index;
		
		temp1->score=gap*gapno;
		temp1->seq1=NULL;
		temp1->seq2=NULL;
		
		temp1->origin[0]=org[0];
		temp1->origin[1]=org[1];
		temp1->origin[2]=org[2];
		
		temp=temp1;
		
		return temp;
	}
	else 
	{
		node *tp;
		tp=temp;
		tp=tp->up->next;
		//while(tp->index==index-k+1)
		//{
		//	tp=tp->pre;
		//}
		/*for(int i=1;i<=k;i++)
		{
		tp=tp->pre;
	}*/
		cout<<"usman";
		cout<<tp->score<<endl;
		temp1->pre=temp;
		temp->next=temp1;
		temp1->next=NULL;
		temp1->up=tp;
		tp->down=temp1;
		temp1->down=NULL;
		
		temp1->score=gap*gapno;
		temp1->seq1=NULL;
		temp1->seq2=NULL;
		temp1->index=index;
		
		temp1->origin[0]=org[0];
		temp1->origin[1]=org[1];
		temp1->origin[2]=org[2];
		
		temp=temp1;
		
		return temp;
	}
}

void dpnode (node *dp,int k)
{
	int count=1;
	while(dp!=NULL)
	{
		cout<<"	";
		cout<<dp->score;
		//if(count==k)
		//{
		//	cout<<endl;
		//	cout<<endl;
		//	cout<<endl;
		//}
		count++;
		dp=dp->next;
		
	}
	//for(int i=0;i<=2;i++)
	//{
	//	cout<<og[i];
	//}
}

void chek(int lft,int up,int dig)
{
	
				if(lft>up && lft>dig)	
				{
					og[0]=1;
					og[1]=0;
					og[2]=0;
					
				}
				else if(up>lft && up>dig)
				{
					og[0]=0;
					og[1]=2;
					og[2]=0;					
				}
				else if(dig>lft)
				{
					og[0]=0;
					og[1]=0;
					og[2]=3;
				}
				else if(dig>up)
				{
					og[0]=0;
					og[1]=0;
					og[2]=3;
				}
				else if(dig==lft && lft>up)
				{
					og[0]=1;
					og[1]=0;
					og[2]=3;
				}
				else if(dig==up && up>lft)
				{
					og[0]=0;
					og[1]=2;
					og[2]=3;
				}
				else if(up==lft && lft>dig)
				{
					og[0]=1;
					og[1]=2;
					og[2]=0;
				}
				
				
}

void tracebak(node *temp,int lp)
{
	while(temp->pre!=NULL)
	{
						  if (temp->origin[2]==3)		//diagonal
						  {
							  cout<<endl;
							  cout<<temp->seq2<<endl;
							  cout<<temp->seq1;
							  temp=temp->up->pre;
						  }
						  
						  else if(temp->origin[1]==2)		//up
						  {
							  cout<<endl;
							  cout<<temp->seq1<<endl;
							  cout<<"_"<<endl;
							  temp=temp->up;
						  }
						  else if(temp->origin[0]==1)		//left
						  {
							  cout<<endl;
							  cout<<temp->seq1<<endl;
							  cout<<"_";
							  temp=temp->pre;
						  }
						 
	}
}
	
/*	void tracebak(node *temp,int lp)
	{
		int i;
		char s1[6];
		char s2[4];
		
		cout<<lp<<endl;
		int z=0;
		while(temp->pre!=NULL)
		{
			if (temp->origin[2]==3)		//diagonal
			{
				s1[z]=temp->seq1;
				s2[z]=temp->seq2;
				z++;
				
				cout<<endl;
				cout<<temp->seq2<<endl;
				cout<<temp->seq1;
				
				for(i=1;i<=lp;i++)
				{
					temp=temp->pre;
				}
			}
			else if(temp->origin[1]==2)		//up
			{
				cout<<endl;
				cout<<temp->seq1<<endl;
				cout<<"_"<<endl;
				
				s1[z]=temp->seq1;
				s2[z]='-';
				z++;
				
				for(i=1;i<=lp-1;i++)
				{
					temp=temp->pre;
				}
			}
			else if(temp->origin[0]==1)		//left
			{
				s1[z]=temp->seq1;
				s2[z]='-';
				z++;
				
				cout<<endl;
				cout<<temp->seq1<<endl;
				cout<<"_";
				temp=temp->pre;
				z++;
			}
			else
			{
				temp=temp->pre;
			}
		}
		cout<<endl;
		cout<<s1<<endl;
		cout<<s2<<endl;
	}
	*/
	

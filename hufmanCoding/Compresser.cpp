class tree;
class dictionary;
class filing;
class codegenerator;
class compressor;
class directory;
class node;
class word;

class word
{
public:
	char data;
	int bitcode;
	int legnth;
	void setbit(int a);
	int getbit(int at);
	word ()
	{
		data = 0;
		bitcode = 0;
		length = 0;
	}
}

class node
{
public:
	char data;
	char bit;
	int weight;
	node *left;
	node *right;
	node ()
	{
		data = 0;
		bit = 2;
		wight = 0;
		left = NULL;
		right = NULL;
	}
};

class tree
{
private:
	node *reference;
	int non;
	int dep;
	void depth ();
	void pushback (int from);
public:	
	void setref (node *ref , int nn);
	void unify ();
	int telldepth ();
	node* returnroot ();
};

int tree::telldepth ()
{
	return dep;
}

void tree::depth () // calculate depth
{
	int i=0;
	int j=0;
	while (j=pow(2,i)<non)
	{
		i++;
	}
	return i;
}

node* tree::returnroot()
{
	return &reference[0];
}

void tree::setref (node *ref)
{
	reference = ref;
}

void tree::unify ()
{
	int i;
	dep = depth ();
	while (non>1)
	{
		i=0;
		while ( i<non)
		{
			node parent;
			parent.left = reference[i];
			
			if(i != non-1)
			{
				parent.right = reference[i+1];
				parent.weight = reference[i+1].weight +reference[i].weight;
			}
			else
				parent.weight = reference[i].weight;
			
			pushback(i+1);
			reference[i]=parent;
			i++;
		}
	}
}

void tree::pushback(int from)
{
	for(int i=from ; i<non;i++)
	{
		reference[i] = reference[i+1];
	}
	non--;
}




class directory : private tree
{
private:
	node *dir;
	node *tosend;
	int Len;
	void sortdir ();
	void repcheck ();
	int checkthere (char that);
public:
	void arrange (char array[]);  // master fuction which sorts and checks redundancy
	directory ()
	{
		non = 0;
	}
};

void directory::arrange (char array[])
{
	Len = strlen (array);
	dir = new node [Len];
	tosend = new node[Len];
	for(int i=0 ; i<Len; i++)
	{
		dir[i].data = array[i];
	}

	repcheck();
	sortdir();
	tree::setref(tosend,non);
	tree::unify();
}

void directory::sortdir ()
{
	int min;
	for(int i=0 ; i<non; i++)
	{
		min = i;
		for(int j=i; j<non; j++)
		{
			if(tosend[j].weight<tosend[min].weight)
				min = j;

			node temp = tosend[i];
			tosend[i] = tosend[min];
			tosend[min] = temp;
		}

	}
}

void directory::repcheck()
{
	int pos;
	for(int i=0; i<Len; i++)
	{
		if(pos = checkthere(dir[i].data)  == -1)
		{
			tosend[non++].data = dir[i].data;
			tosend[non++].weight++;
		}
		else
		{
			tosend[pos].weight++;
		}
	}
}

int directory::checkthere(char that)
{
	int i=0;
	while(i<non)
	{
		if(tosend[i].data==that)
			return i;
		i++;
	}
	return -1;
}

class dictionary
{
private:
	word array [50];
	int index;
	int geti;
public:
	dictionary ()
	{
		index = -1;
		geti = 0;
	}
	void addword (char data, char code[]);
	word* getword ();
	dictionary* returndict ();
};

class codegenerator : private dictionary
{
	// gets root and gives dictionary
private:
	node *root;
	char *temp;
	char thischar;
	char lastchar;

	void set2 (int a);
	void _assigncode (node *root, int bit);
	void _generatecode(node *root, int pos);	
public:
	void setref (node *rot, int depth); // initilizes temp to length depth;
	void assigncode ();
	void generatecode();	
};

void codegenerator ::generatecode ()
{
	_generatecode(root,0);
}

void codegenerator ::_generatecode (node *root, int pos)
{
	if(root == NULL)
	{
		if(thischar == lastchar)
		{
		addword(thischar,temp);
		set2(pos);
		lastchar = thischar;
		}
		else
		return;
	}
	thischar = root->data;
	_generatecode(root,pos+1);
	_generatecode(root,pos+1);
}
void codegenerator ::_assigncode(node *root, int bit)
{
	if(root == NULL)
	{
	return;
	}
	root->bit = bit;
	_assigncode(root->left, 0);
	_assigncode(root->right, 1);
}

void codegenerator ::assigncode ()
{
	_assigncode(root,bit);
}

void codegenerator ::setref (node* rot, int depth)
{
	root = rot;
	temp = new char[depth];
	set2(0);
}

void codegenerator ::set2 (int from)
{
	for(int i=from; i<strlen(temp); i++)
		temp[i] = 2;
} 

class filing
{
private:
	char inputaddress[100];
	char otputaddress[100];
public:
	filing (char in[], char out[])
	{
		strcpy(inputaddress,in);
		strcpy(otputaddress,out);
	}
	
	char * fileinput ();
	void fileoutput (char toput[]);
};

char* filing::fileinput ()
{
	int length;
	ifstream file(inputaddress);
	file.seekg(0,ios::end);
	length=file.tellg();
	file.seekg(0,ios::beg);
	
	int count = 0;
	char *c=new char[length];
	while(!file.eof())
	{
		file.get(c[count]);			//geting the input file
		count++;
	}
	c[count]=NULL;
	file.close();
	return c;
}

class compresser : private directory, private codegenerator, private filing
{
private:
	char input[200];
	char output[200];
	void convert ();
public:
	void compress ();
	compresser (char in[] , char out[]):filing (in,out)
	{}
};


void compresser::compress ()
{
	strcpy(input, fileinput());//
	//cout<<input;
	directory::arrange(input);
	codegenerator::setref(tree::returnroot(),tree::telldepth());
	codegenerator::assigncode();
	compresser::convert();
}

void compresser::convert()
{
	dictionary* reference = dictionary::returndict();
	//dekh dekh ke karta rahay ga
}
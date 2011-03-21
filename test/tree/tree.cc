#include <stdio.h>
#include "tree.ph"

Tree::Tree(int id)
{
	myid=id;
	n=0;
	printf("Node\t%d\ton\t%s\n",myid,(const char *)POPSystem::GetHost());
}

Tree::Tree()
{
	myid=0;
	n=0;
	printf("Node\t%d\ton\t%s\n",myid, (const char *)POPSystem::GetHost());
}

Tree::~Tree()
{
	printf("Destroy node \t%d now!\n",myid);
	for (int i=0;i<n;i++) delete test[i];
}

void Tree::Create(int w, int d, int startid)
{
	n=0;
	if (d<=0 || w<=0)
	{
		printf("Node\t%d:  leaf\n",myid);
	}
	else
	{
		for (int i=0;i<w;i++)
		{
			test[i]=new Tree(startid+i);
			n++;
			test[i]->Create(w,d-1,startid+w*(i+1));
		}
	}
}


@pack(Tree);

int main(int argc, char ** argv)
{
	printf("Tree: Starting test..\n");
	
	if (argc<=2)
	{
		printf("Usage: tree <width> <depth>\n");
		return 0;
	}
	int w,d;
	if (sscanf(argv[1],"%d", &w)!=1 || sscanf(argv[1],"%d", &d)!=1)
	{
		printf("Invalid argument\nUsage: tree <width> <depth>\n");
		return 0;
	}
	Tree root;
	root.Create(w,d,1);
	printf("Tree: test succeeded, destroying objects..\n");
	
	return 0;
}

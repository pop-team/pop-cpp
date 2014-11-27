parclass Tree
{
	public:

	Tree() @ { od.url("localhost");};
    Tree(int id) @ { od.url("localhost");};
	~Tree();

	conc sync void Create(int w, int d, int startid);

	classuid(1000);

	private:
	int myid;
	Tree *test[100];
	int n;

};

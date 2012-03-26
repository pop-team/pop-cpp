parclass Tree
{
	public:

	Tree(int id) @ { od.power(10,100);};
	Tree() @ { od.power(10,100);};
	~Tree();

	conc sync void Create(int w, int d, int startid);

	classuid(1000);

	private:
	int myid;
	Tree *test[100];
	int n;

};

parclass Tree
{
	public:

	Tree() @ { od.node(1); od.executable("./tree.obj"); };
  Tree(int id) @{ od.node(1); od.executable("./tree.obj");};
	~Tree();

	conc sync void Create(int w, int d, int startid);

	classuid(1000);

	private:
	int myid;
	Tree *test[100];
	int n;

};

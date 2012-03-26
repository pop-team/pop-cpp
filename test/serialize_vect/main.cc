#include "myobj.ph"
#include <sys/time.h>

int main(int argc, char** argv)

{
	if (argc<3)
	{
		printf("Usage: popcrun obj.map %s size_vect nb_repeat\n", argv[0]);
		printf(" e.g.: popcrun obj.map %s 10000 100\n", argv[0]);
		return 0;
	}
	else
	{
		printf("\nSerialize_vect: Starting test..\n");
		int size_vect=atoi(argv[1]);
		int nb_repeat=atoi(argv[2]);

		// Fill the vectors with arbitrary values
		vector <int> vect_int1(size_vect,0);
		for (int j =0;j<vect_int1.size();j++)vect_int1[j]=j;

		vector <int> vect_int_copy(size_vect,0);
		for (int j =0;j<vect_int_copy.size();j++)vect_int_copy[j]=j;

		vector <double> vect_double1(size_vect,0);
		for (int j =0;j<vect_double1.size();j++)vect_double1[j]=j*1.1234;

		POPintVector1 vect_herit_int1;
		for (int i=0;i<vect_int1.size();i++)vect_herit_int1.push_back(vect_int1[i]);

		POPintVector2 vect_container_int1;
		for (int i=0;i<vect_int1.size();i++)vect_container_int1.vect.push_back(vect_int1[i]);

		vector <std::string> vect_str1(size_vect,"20 char long string.\n");
		vect_str1.push_back("... end of vector !!\n");

		vector <vector <int> > vect2d_int1(10,vect_int1);
		for (int i =0;i<vect2d_int1.size();i++) {
			for (int j =0;j<vect2d_int1[i].size();j++) {
				vect2d_int1[i][j]=100*i+j;
			}
		}

		POPCobject* myobj=new POPCobject(0,"localhost");

		timeval start,stop,result;

		printf("\n\n\t Timing the marshalling of vectors : vector length %d, repeat %d times\n\n",size_vect,nb_repeat);

		/*---------------------------------------------------------------------------------------*/
		printf("Serialize a integer vector : \n");
		gettimeofday(&start,NULL);

		for (int i=0;i<nb_repeat;i++)myobj->test1(vect_int1,i==0);
		gettimeofday(&stop,NULL);
		timersub(&stop,&start,&result);
		printf("->  Completed in %lf seconds\n\n",result.tv_sec + result.tv_usec/1000000.0);

		/*---------------------------------------------------------------------------------------*/
		printf("Serialize a vector class heriting from POPBase and vector<int> : \n");
		char legend1[3][256]={"  * using a for loop with iterator","  * pack by address as int*","  * pack as vector<int>"};
		for (int i=0;i<2;i++) {
			printf("%s\n",legend1[i]);
			vect_herit_int1.ser=i;
			gettimeofday(&start,NULL);
			for (int j=0;j<nb_repeat;j++)myobj->test2(vect_herit_int1,j==0);
			gettimeofday(&stop,NULL);
			timersub(&stop,&start,&result);
			printf("->  Completed in %lf seconds\n\n",result.tv_sec + result.tv_usec/1000000.0);
		}

		/*---------------------------------------------------------------------------------------*/
		printf("Serialize a vector class heriting from POPBase containing vector<int> : \n");
		char legend2[3][256]={"  * using a for loop with iterator","  * pack by address as int*","  * pack as vector<int>"};
		for (int i=0;i<3;i++) {
			printf("%s\n",legend2[i]);
			vect_container_int1.ser=i;
			gettimeofday(&start,NULL);
			for (int j=0;j<nb_repeat;j++)myobj->test5(vect_container_int1,j==0);
			gettimeofday(&stop,NULL);
			timersub(&stop,&start,&result);
			printf("->  Completed in %lf seconds\n\n",result.tv_sec + result.tv_usec/1000000.0);
		}


		/*---------------------------------------------------------------------------------------*/
		printf("Serialize a double vector : \n");
		gettimeofday(&start,NULL);

		for (int i=0;i<nb_repeat;i++)myobj->test4(vect_double1,i==0);
		gettimeofday(&stop,NULL);
		timersub(&stop,&start,&result);
		printf("->  Completed in %lf seconds\n\n",result.tv_sec + result.tv_usec/1000000.0);

		/*---------------------------------------------------------------------------------------*/
		printf("Serialize a string vector : \n");
		gettimeofday(&start,NULL);
		for (int i=0;i<nb_repeat;i++)myobj->test3(vect_str1,i==0);
		gettimeofday(&stop,NULL);
		timersub(&stop,&start,&result);
		printf("->  Completed in %lf seconds\n\n",result.tv_sec + result.tv_usec/1000000.0);

		/*---------------------------------------------------------------------------------------*/
		if (vect2d_int1.size()>0)printf("Serialize a 2D vector of int : (%dx%d) \n",vect2d_int1.size(),vect2d_int1[0].size());
		gettimeofday(&start,NULL);
		for (int i=0;i<nb_repeat;i++)myobj->test0(vect2d_int1,i==0);
		gettimeofday(&stop,NULL);
		timersub(&stop,&start,&result);
		printf("->  Completed in %lf seconds\n\n",result.tv_sec + result.tv_usec/1000000.0);


		for (int i=0;i<vect_int1.size();i++)assert(vect_int_copy[i]==vect_int1[i]/2);
		/*---------------------------------------------------------------------------------------*/


		printf("\nSerialize_vect: test succeeded, destroying objects..\n");
		delete myobj;
	}
	printf("\nEND of %s program\n", argv[0]);
	return 0;
}

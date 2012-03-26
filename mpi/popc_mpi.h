#ifndef POPC_MPI_H
#define POPC_MPI_H

#include <stdlib.h>

#include <paroc_array.h>
#include <paroc_interface.h>
#include <paroc_buffer_factory_finder.h>
#include <paroc_broker.h>
#include <jobmgr.ph>
#include <codemgr.ph>

template<class T> class POPMPI
{
public:
	POPMPI();
	POPMPI(int np);
	~POPMPI();

	//Initialize...
	bool Create(int np);
	bool Success();
	int GetNP();

	//Operation...
	bool ExecuteMPI();
	inline operator T*();

private:

	bool startMPI(T *&array, int np);
	void stopMPI(T *array, int np);

private:
	T *mpi_obj;
	int mpi_np;
};

template<class T>
POPMPI<T>::POPMPI()
{
	mpi_np=0;
	mpi_obj=NULL;
}
template<class T>
POPMPI<T>::POPMPI(int np)
{

	mpi_np=0;
	mpi_obj=NULL;
	Create(np);
}

template<class T>
POPMPI<T>::~POPMPI()
{
	stopMPI(mpi_obj, mpi_np);
	mpi_obj=NULL;
	mpi_np=0;
}

template<class T>
bool POPMPI<T>::Create(int np)
{
	stopMPI(mpi_obj, mpi_np);
	if (startMPI(mpi_obj, np))
	{
		mpi_np=np;
	}
	else
	{
		mpi_obj=NULL;
		mpi_np=-1;
	}
}

template<class T>
bool POPMPI<T>::Success()
{
	return (mpi_np>0);
}

template<class T>
int POPMPI<T>::GetNP()
{
	return (mpi_np);
}

template<class T>
bool POPMPI<T>::ExecuteMPI()
{
	if (!Success()) return false;
	for (int i=0;i<mpi_np;i++) mpi_obj[i].ExecuteMPI();
	return true;
}

template<class T>
POPMPI<T>::operator T*()
{
	return mpi_obj;
}



//Private method....


template<class T>
void POPMPI<T>::stopMPI(T *array, int np)
{
	if (array==NULL) return;
	for (int i=0;i<np;i++)  array[i].~T();
	free(array);
}

template<class T>
bool  POPMPI<T>::startMPI(T *&array, int np)
{
	if (np<=0) return false;
	T test(paroc_interface::_paroc_nobind);
	const char *name=test.ClassName();

	array=NULL;
	paroc_string codefile;
	int i=0;
	try
	{
		CodeMgr mgr(paroc_system::appservice);
		paroc_string objname(name);

		if (!mgr.QueryCode(objname,paroc_system::platform,codefile))
		{
			printf("startMPI failed: no supported executable\n");
			return false;
		}
		char mpicmd[1024];
		const char *mpirun;
		mpirun=getenv("POPC_MPIRUN");
		if (mpirun==NULL) mpirun="mpirun";

		sprintf(mpicmd,"%s -np %d %s", mpirun, np,(const char *)codefile);

		paroc_array<paroc_accesspoint> ap(np);
		paroc_od od; // Note: The od is empty !!
		if (paroc_interface::LocalExec(NULL,mpicmd, name, paroc_system::jobservice, paroc_system::appservice, ap,np,od)!=0)
		{
			printf("startMPI failed: mpirun returned error\n");
			return false;
		}
		array=(T *)malloc(sizeof(T)*np);
		for (i=0;i<np;i++)
		{
			new (array+i) T(ap[i]);
			(array+i)->_paroc_Construct();
		}
	}

	catch (...)
	{
		if (array!=NULL)
		{
			for (int j=0;j<i;j++)
			{
				array[j].~T();
			}
			free(array);
		}
		return false;
	}
	return true;
}


#endif

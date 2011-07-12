#include "paroc_buffer_utils.h"

//Some addition marshalling procedures...
void marshalstring ( paroc_buffer &buf, char *str, int maxsize, int flag, paroc_memspool *temp)
{
	if (flag & FLAG_MARSHAL)
	{
		int n=(str!=NULL) ?  strlen(str)+1 : 0;
		if (n>maxsize) n=maxsize;

		buf.Pack(&n,1);
		if (n>0) buf.Pack(str,n);
	}
	else
	{
		int n;
		buf.UnPack(&n,1);
		if (n>maxsize || (n>0 && str==NULL)) paroc_exception::paroc_throw(POPC_BUFFER_FORMAT);
		if (n>0)
		{
			buf.UnPack(str,n);
			str[n-1]=0;
		}
		else if (str!=NULL) *str=0;
	}
}

template <class T> void packarray (paroc_buffer &buf, T *param, int size, int flag, paroc_memspool *temp)
{
	if (flag & FLAG_MARSHAL)
	{
		int n=(param!=0) ?  size : 0;
		buf.Pack(&n,1);
		if (n>0) buf.Pack(param,n);
	}
	else
	{
		int n;
		buf.UnPack(&n,1);
		if (n>0) buf.UnPack(param,n);
		else param=0;
	}

}


template void packarray<char> (paroc_buffer &buf, char *param, int size, int flags, paroc_memspool *tmp);
template void packarray<unsigned char> (paroc_buffer &buf, unsigned char *param, int size, int flags, paroc_memspool *tmp);
template void packarray<int> (paroc_buffer &buf, int  *param, int size, int flags, paroc_memspool *tmp);
template void packarray<long> (paroc_buffer &buf, long *param, int size, int flags, paroc_memspool *tmp);
template void packarray<unsigned> (paroc_buffer &buf, unsigned  *param, int size, int flags, paroc_memspool *tmp);
template void packarray<short> (paroc_buffer &buf, short *param, int size, int flags, paroc_memspool *tmp);
template void packarray<unsigned short> (paroc_buffer &buf, unsigned short *param, int size, int flags, paroc_memspool *tmp);
template void packarray<double> (paroc_buffer &buf, double *param, int size, int flags, paroc_memspool *tmp);
template void packarray<float> (paroc_buffer &buf, float *param, int size, int flags, paroc_memspool *tmp);
//template void packarray<paroc_interface> (paroc_buffer &buf, paroc_interface *param, int size, int flags, paroc_memspool *tmp);

void marshalnull ( paroc_buffer &buf, void * & param, int hint, int flags, paroc_memspool *tmp)
{
	param=NULL;
}

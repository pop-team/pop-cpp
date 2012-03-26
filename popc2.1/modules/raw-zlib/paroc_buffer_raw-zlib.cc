#include <string.h>
#include <zlib.h>
#include "paroc_interface.h"
#include "paroc_buffer_raw-zlib.h"

paroc_buffer_raw_zlib::paroc_buffer_raw_zlib()
{
	//  DEBUG("raw-zlib");
	Reset();
}

paroc_buffer_raw_zlib::~paroc_buffer_raw_zlib()
{
}

void paroc_buffer_raw_zlib::Reset()
{
	unpackpos=0;
	packeddata.RemoveAll();
}

bool paroc_buffer_raw_zlib::Send(paroc_combox &s, paroc_connection *conn)
{
	int n=packeddata.GetSize();
	char *src=packeddata;

	int h[6];
	memset(h,0, 6*sizeof(int));

	paroc_array<char> tmp;
	tmp.SetSize(36+n*115/100);

	char *dest=tmp+24;
	uLongf len=tmp.GetSize()-24;
	if (n>0)
	{
		int ret=compress((Bytef *)dest,&len, (const Bytef *)src,n);
		if (ret!=Z_OK)
		{
			DEBUG("Compression error");
			return false;
		}
		//      DEBUG("Compression: before: %d , after: %d",n,(int)len);
	}
	else
	{
		len=0;
	}

	len+=24;
	dest=tmp;

	int type=header.GetType();

	h[0]=len;
	h[1]=n;
	h[2]=type;

	switch (type)
	{
	case TYPE_REQUEST:
		h[3]=header.GetClassID();
		h[4]=header.GetMethodID();
		h[5]=header.GetSemantics();
		break;
	case TYPE_EXCEPTION:
		h[3]=header.GetExceptionCode();
		break;
	case TYPE_RESPONSE:
		break;
	default:
		return false;
	}

	memcpy(dest,h,24);

	if (s.Send(dest,len, conn)<0)
	{
		DEBUG("Fail to send a message!");
		return false;
	}
	return true;
}

//Propagation of exceptions back to caller...

bool paroc_buffer_raw_zlib::Recv(paroc_combox &s, paroc_connection *conn)
{
	int h[6];
	int n, i;

	//Recv the header...
	char *dat=(char *)h;
	n=24;
	do
	{
		if ((i=s.Recv(dat,n, conn)) <=0)
		{
			return false;
		}
		n-=i;
		dat+=i;
	}
	while (n);

	Reset();

	n=h[0];
	if (n<24)
	{
		DEBUG("Bad message header(size error:%d)",n);
		return false;
	}

	int type=h[2];
	header.SetType(type);
	switch (type)
	{
	case TYPE_REQUEST:
		header.SetClassID(h[3]);
		header.SetMethodID(h[4]);
		header.SetSemantics(h[5]);
		break;
	case TYPE_EXCEPTION:
		header.SetExceptionCode(h[3]);
		break;
	case TYPE_RESPONSE:
		break;
	default:
		return false;
	}

	//read body...
	paroc_array<char> tmp;
	n-=24;

	tmp.SetSize(n);
	dat=(char *)tmp;
	while (n>0)
	{
		if ((i=s.Recv(dat,n, conn))<=0)
		{
			return false;
		}
		dat+=i;
		n-=i;
	}

	//Uncompress data..
	uLongf len=h[1];
	packeddata.SetSize(len);
	char *dest=packeddata;

	char *src=tmp;
	n=tmp.GetSize();

	if (len>0)
	{
		int ret=uncompress((Bytef *)dest,&len,(const Bytef *)src,n);
		//      DEBUG("Uncompress: bufsize:%d, src:%d, dest:%d",packeddata.GetSize(),n,(int)len)
		if (len!=packeddata.GetSize()) DEBUG("Uncompress size error!");
		if (ret!=Z_OK)
		{
			DEBUG("Uncompression error");
			return false;
		}

	}
	return true;
}



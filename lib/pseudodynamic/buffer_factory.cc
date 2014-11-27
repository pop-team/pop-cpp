/**
 * File : buffer_factory.cc
 * Author : Tuan Anh Nguyen
 * Description : implementation of buffer factory base class
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */

#include "paroc_buffer_factory.h"

paroc_buffer_factory::paroc_buffer_factory()
{
}

paroc_buffer_factory::~paroc_buffer_factory()
{
}

void paroc_buffer_factory::Destroy()
{
	delete this;
}


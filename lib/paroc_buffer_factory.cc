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


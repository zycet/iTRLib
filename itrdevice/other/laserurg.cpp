#include "laserurg.h"

LaserUrg::LaserUrg()
{
    //ctor
}

LaserUrg::~LaserUrg()
{
    //dtor
}
void LaserUrg::Start()
{

    pthread_create(&tid,NULL,LaserUrg::WorkThread,NULL);
}

void LaserUrg::Stop()
{
    pthread_cancel(tid);
}

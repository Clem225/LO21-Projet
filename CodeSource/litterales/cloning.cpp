#include "litterales.h"

Litterale* Programme::clone()
{
    return NULL;
    //return new Programme(*this);
}

Litterale* Expression::clone()
{
    return NULL;
    //return new Expression(*this);
}
Litterale* Atome::clone()
{
    return new Atome(*this);
}
Litterale* Entier::clone()
{
    return new Entier(*this);
}
Litterale* Rationnel::clone()
{
    return new Rationnel(*this);
}
Litterale* Reel::clone()
{
    return new Reel(*this);
}
Litterale* Complexe::clone()
{
    return new Complexe(*this);
}

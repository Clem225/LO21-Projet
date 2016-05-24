#include "../litterales/litterales.h"
#include "../manager/manager.h"



int main(/*int argc, char *argv[]*/)
{
    // Creation du manager de litterales
    FactoryLitterale& myFactory = FactoryLitterale::getInstance();

    Litterale* myTest = myFactory.addLitterale("3.14");


    return 0;
}

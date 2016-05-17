#include "litterales.h"


void Rationnel::simplification() {
	if (denominateur==1)
		//faire un cast vers un Entier
	//Simplification
}

Rationnel::Rationnel(int e1, int e2) {
	numerateur=e1;
	denominateur=e2;
	simplification();
}


Reel::Reel(int e1, int e2) {
	if (e2==0)
		//cast vers Entier
	entiere=e1;
	mantisse=e2;
}


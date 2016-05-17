class Entier {
private:
	int nb;
public:
	Entier(unsigned int n): nb(n) {}
	void NEG() {if (nb>0) nb=-nb;}
	int getNb() const {return nb;}
	void afficher() const {/*.....*/;}
};

class Rationnel {
private:
	Entier numerateur;
	Entier denominateur;
public:
	void simplification();
	Rationnel(int e1, int e2);	
	int getNum() const {return numerateur.getNb();}
	int getDenom() const {return denominateur.getNb();}
	double getNb() const {return (double numerateur/denominateur);}
	void afficher() const {/*.....*/;}
};


class Reel {
private:
	Entier entiere;
	Entier mantisse;
public:
	void NEG() {if (entiere.getNb()>0) entiere=NEG(entiere);}
	Reel(int e1=0, int e2=0);
	void afficher() const {/*.....*/;}

};






Rationnel operator/(int e1, int e2);
Reel operator.(int e1, int e2);


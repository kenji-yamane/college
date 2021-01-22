#include <iostream>
#include <map>
#include <string>


using namespace std;

int main()
{
	string aux;
	map<string, string> translator;
	
	translator["brasil"] = "Feliz Natal!";
    translator["alemanha"] = "Frohliche Weihnachten!";
    translator["austria"] = "Frohe Weihnacht!";
    translator["coreia"] = "Chuk Sung Tan!";
    translator["espanha"] = "Feliz Navidad!";
    translator["grecia"] = "Kala Christougena!";
    translator["estados-unidos"] = "Merry Christmas!";
    translator["inglaterra"] = "Merry Christmas!";
    translator["australia"] = "Merry Christmas!";
    translator["portugal"] = "Feliz Natal!";
    translator["suecia"] = "God Jul!";
    translator["turquia"] = "Mutlu Noeller";
    translator["argentina"] = "Feliz Navidad!";
    translator["chile"] = "Feliz Navidad!";
    translator["mexico"] = "Feliz Navidad!";
    translator["antardida"] = "Merry Christmas!";
    translator["canada"] = "Merry Christmas!";
    translator["irlanda"] = "Nollaig Shona Dhuit!";
    translator["belgica"] = "Zalig Kerstfeest!";
    translator["italia"] = "Buon Natale!";
    translator["libia"] = "Buon Natale!";
    translator["siria"] = "Milad Mubarak!";
    translator["marrocos"] = "Milad Mubarak!";
    translator["japao"] = "Merii Kurisumasu!";
	
	while (cin >> aux)
		if (translator.find(aux) == translator.end())
			cout << "--- NOT FOUND ---" << endl;
		else
			cout << translator[aux] << endl;
	
	return 0;
}

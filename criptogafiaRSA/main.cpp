#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <windows.h>
#include <iomanip>
#include <sstream>

using namespace std;


bool validate(string valor) {
    if (valor.size() > 0)
        if (all_of(valor.begin(), valor.end(), ::isdigit))
            return true;
    return false;
}

int convertValor(string svalor) {
    try {
        int ivalor = std::stoi(svalor); // Convertendo string para inteiro
        return ivalor;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Entrada inválida: não é um número válido.\n";
        return 1;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Entrada inválida: número fora do intervalo permitido.\n";
        return 1;
    }
}

bool isPrimo(int num) {
    int aux, div = 0;

    for (aux = 1; aux <= num; aux++) {
        if (num % aux == 0)
            div++;
    }

    if (div == 2)
        return true;
    else
        return false;
}

int getRandomPrime() {
    std::vector<int> primes;
    for (int i = 1; i <= 100; ++i) {
        if (isPrimo(i)) {
            primes.push_back(i);
        }
    }

    std::srand(std::time(0));
    int randomIndex = std::rand() % primes.size();
    return primes[randomIndex];
}




bool valorEstaNoVetor(const std::vector<int>& vetor, int valor) {
    for (int elemento : vetor) {
        if (elemento == valor) {
            return true;
        }
    }
    return false;
}


int random(const std::vector<int>& vec) {
    if (vec.empty()) {
        throw std::runtime_error("O vetor está vazio.");
    }
    // Inicializa o gerador de números aleatórios
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int index = std::rand() % vec.size();
    return vec[index];
}



int mdc(int num1, int num2)
{
    if (num1 % num2 == 0)
        return num2;
    else
        return mdc(num2, num1 % num2);
}

std::vector<int> coPrimos(int valor) {
    std::vector<int> coPrimes;

    for (int i = 1; i < valor; i++) {
        if (mdc(i, valor) == 1) {
            coPrimes.push_back(i);
        }
    }
    return coPrimes;
}


unsigned long long mod_pow(int base, int exp, int mod) {
    
    unsigned long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}



int pegarValorP() {
    string mystr;
    printf("Digite o valor de p ou clique deixe vazio para gerar automaticamente: ");
    getline(cin, mystr);
    if (validate(mystr))
        return convertValor(mystr);
    //return getRandomPrime();
    return 3;
}

int pegarValorQ() {
    string mystr;
    printf("Digite o valor de q ou clique deixe vazio para gerar automaticamente: ");
    getline(cin, mystr);
    if (validate(mystr))
        return  convertValor(mystr);
    //return getRandomPrime();
    return 11;
}


int pegarValorD(int e, int totiente) {

    int i = 1;
    if (e == 1 && totiente == 1) {
        return 1;
    }
    while (true) {
        if (i == 1000) {
            return 0;
        }
        if (e * i % totiente == 1 ){
            return i;
            break;
        }
        i++;
    }//Numero muito grande, vai demorar pra encontrar.  
}



int pegarValorE(int p, int q) {
    string mystr;
    int n = p * q;
    int e = 0;
    vector<int>coPrimosN;
    vector<int>Ds;

    coPrimosN = coPrimos(n);
    
    
    for (int primo : coPrimosN) {
        printf("%i ", primo);
        
        
        if (pegarValorD(primo, (p - 1) * (q - 1)) != 0) {
            Ds.push_back(primo);
        }
    }

    printf("\n\nValor de E sugerido:");
    for (int d : Ds) {
        printf("%d ", d);
    }
std:cout << std::endl;


    printf("\n\nDigite o valor de E caso contrário sera selecionado aleatoriamente: ");



    getline(cin, mystr);
    if (validate(mystr)) {
        e = convertValor(mystr);
        if (!(valorEstaNoVetor(coPrimosN, e))) {
            printf("Valor não está nos valores informados, inserindo valor aleátorio em E.");
            return random(coPrimosN);
        }
    }
    return e;

}






uintmax_t criptografar(int mensagem, int e, int n) {
	return mod_pow(mensagem, e, n);
}

uintmax_t descriptografar(int mensagemCriptografada, int d, int n){
    uintmax_t msg = mod_pow(mensagemCriptografada, d, n);
    return msg;
}










uint64_t stringToDecimal(const char& input) {
    return static_cast<int>(input);
}


std::string decimalToString(uint64_t decimalInput) {
    std::string result;
    std::string decimalString = std::to_string(decimalInput);

    // Lê a string em partes de três caracteres (considerando valores ASCII de três dígitos)
    for (size_t i = 0; i < decimalString.size(); i += 3) {
        std::string part = decimalString.substr(i, 3);
        int decimalValue = std::stoi(part);
        result += static_cast<char>(decimalValue);
    }

    return result;
}


int main(char* args[]) {
    SetConsoleCP(1252);
    SetConsoleOutputCP(1252);

    string mensagem;
    vector<int> mensagemCriptografada;
    vector<int> mensagemDescriptografada;


    while (true) {
        mensagemCriptografada = {};
        mensagemDescriptografada = {};
        printf("================================================================\n");
        int p = pegarValorP();
        int q = pegarValorQ();
        int n = p * q;
        int e = pegarValorE(p,q);
        int d = pegarValorD(e, ((p - 1) * (q - 1)));
        vector<int>coPrimosN;

        printf("================================================================\n");
        printf("\nValores:\n"
            "p = %i\n"
            "q = %i\n"
            "n = %i\n"
            "e = %i\n"
            "d = %i\n"
            , p, q, n, e, d);
        printf("================================================================\n");
        
        while (true) {
            mensagem = "";
            printf("\nDigite a mensagem para ser criptografada: ");
            getline(cin, mensagem);


            printf("Mensagem: ");




            vector<int> mensagemCriptografada = {};
            vector<int> mensagemDescriptografada = {};

            for (int i = 0; i < mensagem.size(); i++) {
                std::cout << stringToDecimal(mensagem[i]);
                mensagemCriptografada.push_back(criptografar(stringToDecimal(mensagem[i]), e, n));
            }
            std::cout << endl;
            for (int i = 0; i < mensagemCriptografada.size(); i++) {
                mensagemDescriptografada.push_back(descriptografar(mensagemCriptografada[i], e, n));
            }





            printf("Mensagem criptografada: ");
            for (int c : mensagemCriptografada) {
                printf("%i", c);
            }
            std::cout << std::endl;

            printf("Mensagem descriptografada: ");
            for (int c : mensagemDescriptografada) {
                printf("%i", c);
            }
            std::cout << std::endl;
        }
    }
    
    return 0;
}


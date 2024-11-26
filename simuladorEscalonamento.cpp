#include <iostream>
#include <list>
#include <cstdlib> // Para system(), rand()
#include <ctime> // para usar time()
#include <chrono>  // Para controle de tempo
#include <thread>  // Para sleep_for
using namespace std;

// Variavel global para usar no algortmo R.R
int contadorRR = 0;

// Variavel global para usar no meu algoritimo
int trocador = 0;

// Define a estrutura da "variável" Processo
struct Processo {
    int id;
    int prioridade;
    int tempo;
    int tempoDeEspera;
    bool finalizado;

    // Construtor para inicializar os campos do processo
    Processo(int i, int p, int t, int tE, bool e) 
        : id(i), prioridade(p), tempo(t), tempoDeEspera(tE), finalizado(e) {}
};

// Declaração das listas
list<Processo> fila; // Lista para armazenar os processos em execução
list<Processo> listaDeProntos; // Lista para armazenar os processos prontos
list<Processo> listaDeExecução; // armazena cada execução feita

// Função para limpar a tela
void limparTela() {
    // Para sistemas Windows
    #ifdef _WIN32
        system("cls");  // Limpa a tela no Windows
    #else
        system("clear");  // Limpa a tela em sistemas Unix/Linux
    #endif
}

// Função para subitrair quantum do tempo
void quantumMenosTempo(Processo& p) {
    listaDeExecução.push_back(fila.front());
    int quantum = 1;

    // Incrementa 1 no tempo de espera de cada processo ativo
    for (auto& processo : fila) {
        processo.tempoDeEspera++;
    }

    fila.front().tempo -= quantum;
}

// Seleciona e aplica as regras para cada 
void organizaFila(char argumentoSeletor){

    switch (argumentoSeletor) {
        case 'a':
        case 'A': // FIFO (First In, First Out)
            // Organiza por id em ordem crecente
            fila.sort([](const Processo& a, const Processo& b){
                return a.id < b.id;
            });
            break;
        case 'b':
        case 'B': // SJF (Shortest Job First)
            // Organiza por tempo em ordem crecente
            fila.sort([](const Processo& a, const Processo& b){
                return a.tempo < b.tempo;
            });
            break;
        case '5': // Meu algoritimo
        case 'C':
        case 'c': // RR (Round Robin) com prioridade
        case 'd':
        case 'D': // Escalonamento por Prioridade (Priority Scheduling)
            // Prganiza por priorfade em ordem decrecente
            fila.sort([](const Processo& a, const Processo& b){
                return a.prioridade > b.prioridade;
            });
            break;
        default:
            cout << "Argumento invalido" << endl;
            break;
    }

}

// Lida com a fila pos interação
void posProcessamentoFila(list<Processo>& fila, char argumentoSeletor){

    if (!fila.empty()){

        // Código para RR (Round Robin) com prioridade // e meu algoritmo
        if (argumentoSeletor == 'c' || argumentoSeletor == 'C' || argumentoSeletor == '5') {
            if (fila.front().tempo <= 0) // Quando o tempo do processo zera tira ele da fila 
            {
                listaDeProntos.push_back(fila.front()); // Adiciona a lista de exibição
                fila.pop_front(); // Elimina o primeiro processo da fila
                contadorRR = 0;
            } else {
                if (contadorRR >= 1){ // quando contador chega da 3 passos tira o processo do começo e coloca ele no final
                    fila.push_back(fila.front()); //Adiciona o primeiro processo da fila no final
                    fila.pop_front(); // Elimina o primeiro processo da fila
                    contadorRR = 0;

                    // Organiza a fila pelo meu algortimo se ele tiver selecionado
                    if (argumentoSeletor == '5')
                    {

                        switch (trocador){
                            case 0:
                                organizaFila('a');
                                trocador++;
                                break;
                            case 1:
                                organizaFila('b');
                                trocador++;
                                break;
                            case 2:
                                organizaFila('c');
                                trocador = 0;
                                break;
                        }
                    }
                } else {
                    contadorRR++;
                }
            }
        // Código para qualquer outro
        } else {
            if (fila.front().tempo <= 0){
                listaDeProntos.push_back(fila.front()); // Adiciona a lista de exibição
                fila.pop_front(); // Elimina o primeiro processo da fila
            }
        
        }

    }

}


void saidaPrompt(char argumentoSeletor){

    // Algoritimo usado

    cout << endl <<" Usando";
    switch (argumentoSeletor) {
        case 'a':
        case 'A': // FIFO (First In, First Out)
            cout << " FIFO (First In, First Out)" << endl;
            break;
        case 'b':
        case 'B': // SJF (Shortest Job First)
            cout << " SJF (Shortest Job First)" << endl;
            break;
        case '5': // Meu algoritmo
            cout << " Meu algoritimo" << endl;
            break;
        case 'c':
        case 'C': // RR (Round Robin) com prioridade
            cout << " RR (Round Robin) com prioridade" << endl;
            break;
        case 'D':
        case 'd': // Escalonamento por Prioridade (Priority Scheduling)
            cout << " Escalonamento por Prioridade (Priority Scheduling)" << endl;
            break;
    }

    cout << endl;

    //Processo em execução

    cout << " Em exe: ";
    if (!fila.empty()){
        cout << "p" << fila.front().id << " " << endl;
    } else {
        cout << " null " << endl;
    }

    cout << endl;

    // Exibe a fla de processos

    cout << " Fila de espera: ";
    if (!fila.empty()){
        auto it = fila.begin();
        it++;  // Avança para o segundo elemento

        for (; it != fila.end(); ++it) { // Exibe a lista menos o processo em exe
            cout << " p" << it->id;
        }
    } else {
        cout << " Vazia " << endl;
    }

    cout << endl;

    // Exibe os processos finalizados
    cout << " Fila de prontos: ";
    if (!listaDeProntos.empty()){
        for (const auto& processo : listaDeProntos) {
            cout << " p" << processo.id;
        }
    }

    cout << endl;
    cout << endl;

}

// Função que implementa o contador de 3 segundos antes de cada interação
void esperarAteTempoLimite(int segundos) {
    static auto ultimoTempo = chrono::steady_clock::now();  // Inicializa na primeira chamada

    auto agora = chrono::steady_clock::now();  // Marca o tempo atual
    auto decorrido = chrono::duration_cast<chrono::seconds>(agora - ultimoTempo);

    if (decorrido.count() < segundos) {
        this_thread::sleep_for(chrono::seconds(segundos - decorrido.count()));
    }

    // Atualiza o último tempo
    ultimoTempo = chrono::steady_clock::now();
}

void createFila() {

    fila.push_back(Processo(1, 10, 5, 0, false));
    fila.push_back(Processo(2, 20, 3, 0, false));
    fila.push_back(Processo(3, 1, 4, 0, false));
    fila.push_back(Processo(4, 3, 1, 0, false));
    fila.push_back(Processo(5, 2, 2, 0, false));
    fila.push_back(Processo(6, 1, 3, 0, false));

}

int main() {

    char argumentoSeletor = ' ';
    char argumentoSeletorSaida = ' ';
    char argumentoSeletorJump = ' ';
    int tempoMedio = 0;
    bool jump = false;
    

    while (true){ // Loop para retornar a interação com o usuario
        while (true) {  // Loop que garante que o usuário escolhe uma opção válida
            tempoMedio = 0;
            fila.clear();
            createFila();
            listaDeProntos.clear();
            limparTela();  // Limpa a tela

            cin.clear(); // limpa entrada
            cout << "Selecione o algoritimo" << endl;
            cout << "A) FIFO (First In, First Out)" << endl;
            cout << "B) SJF (Shortest Job First)" << endl;
            cout << "C) RR (Round Robin) com prioridade" << endl;
            cout << "D) Escalonamento por Prioridade (Priority Scheduling)" << endl << endl;
            cin >> argumentoSeletor;

            // Chama a função para organizar
            organizaFila(argumentoSeletor);

            // Se o usuário escolher uma opção válida, podemos sair do loop
            if (argumentoSeletor == 'A' || argumentoSeletor == 'B' || argumentoSeletor == 'C' || 
                argumentoSeletor == 'D' || argumentoSeletor == 'a' || argumentoSeletor == 'b' || argumentoSeletor == 'c' || 
                argumentoSeletor == 'd' || argumentoSeletor == '5') {
                limparTela();  // Limpa a tela
                cin.clear(); // limpa entrada
                cout << "Gostaria de pular direto para o relatorio?" << endl;
                cout << "y | n" << endl;
                cin >> argumentoSeletorJump;
                
                if (argumentoSeletorJump == 'y' || argumentoSeletorJump == 'Y'){
                  jump = true;
                } else { jump = false;}
                
                break;  // Encerra o loop quando uma escolha válida for feita
            }  
        }

        while (!fila.empty()) {

            limparTela();  // Limpa a tela no início de cada iteração

       	    quantumMenosTempo(fila.front());    

            posProcessamentoFila(fila, argumentoSeletor);

            saidaPrompt(argumentoSeletor);
            
            if (!jump){
              esperarAteTempoLimite(1);
            }

        }

        fila.clear();
        createFila();

        // Atualizando os tempos de listaDeProntos com os tempos correspondentes de fila
        for (auto& processo2 : listaDeProntos) {
            for (const auto& processo1 : fila) {
                if (processo1.id == processo2.id) {
                    processo2.tempo = processo1.tempo;  // Atribui o tempo de lista1 para lista2
                    break;  // Não precisa continuar procurando após encontrar o id correspondente
                }
            }
        }
        
        limparTela();  // Limpa a tela
        cout << endl << "Relatório Final:" << endl;
        cout << endl <<" Usando";
        switch (argumentoSeletor) {
            case 'a':
            case 'A': // FIFO (First In, First Out)
                cout << " FIFO (First In, First Out)" << endl;
                break;
            case 'b':
            case 'B': // SJF (Shortest Job First)
                cout << " SJF (Shortest Job First)" << endl;
                break;
            case '5': // Meu algoritmo
                cout << " Meu algoritimo" << endl;
                break;
            case 'c':
            case 'C': // RR (Round Robin) com prioridade
                cout << " RR (Round Robin) com prioridade" << endl;
                break;
            case 'D':
            case 'd': // Escalonamento por Prioridade (Priority Scheduling)
                cout << " Escalonamento por Prioridade (Priority Scheduling)" << endl;
                break;
        }
        
        cout << endl;

        // Exibe todos os processos finalizados na fila de prontos
        for (const auto& processo : listaDeProntos) {
            cout << " Processo p" << processo.id << endl;
            cout << " Tempo de execução: " << processo.tempo << endl;
            cout << " Tempo total de espera: " << processo.tempoDeEspera << endl;
            cout << " Prioridade: " << processo.prioridade << endl;
            cout << endl;
            tempoMedio += processo.tempoDeEspera;
        }

        cout << " Tempo médio de execução: " << static_cast<double>(tempoMedio) / fila.size() << endl << endl;

        cout << " Como foi executado: ";
        for (const auto& processo : listaDeExecução) {
            cout << " p" << processo.id;
        }

        cin.clear(); // limpa entrada
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n";
        cout << endl << " A) voltar  || B) sair" << endl << endl;
        cin >> argumentoSeletorSaida;
        if (argumentoSeletorSaida == 'b' || argumentoSeletorSaida == 'B')
        {
            break;
        }

    }

    return 0;
}

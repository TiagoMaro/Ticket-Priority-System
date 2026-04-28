#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <limits>
#include <cstdlib>

using namespace std;

const int MAX = 10;

struct Cliente
{
    string nome;
    string senha;
    char tipo_atendimento;
    time_t hora_entrada;
};

Cliente fila[MAX];
int tamFila = 0;
int clientesAtendidos = 0;

int senNormal = 1;
int senPref = 1;
int senUrg = 1;

string gerarSenha(char tipo)
{
    stringstream ss;
    ss << tipo;
    if (tipo == 'A')
    {
        ss << setfill('0') << setw(3) << senNormal++;
    }
    else if (tipo == 'P')
    {
        ss << setfill('0') << setw(3) << senPref++;
    }
    else if (tipo == 'U')
    {
        ss << setfill('0') << setw(3) << senUrg++;
    }
    return ss.str();
}

string formatarHora(time_t tempo)
{
    tm *ltm = localtime(&tempo);
    stringstream ss;
    ss << setfill('0') << setw(2) << ltm->tm_hour << ":"
       << setfill('0') << setw(2) << ltm->tm_min << ":"
       << setfill('0') << setw(2) << ltm->tm_sec;
    return ss.str();
}

void emitirSenha()
{
    if (tamFila >= MAX)
    {
        cout << "\n[ERRO] A fila atingiu a capacidade máxima (" << MAX << " pessoas).\n";
        return;
    }

    Cliente c;
    cout << "\nNome do cliente: ";
    cin.ignore();
    getline(cin, c.nome);

    cout << "Tipo de atendimento (U - Urgencia, P - Preferencial, A - Normal): ";
    cin >> c.tipo_atendimento;
    c.tipo_atendimento = toupper(c.tipo_atendimento);

    if (c.tipo_atendimento != 'U' && c.tipo_atendimento != 'P' && c.tipo_atendimento != 'A')
    {
        cout << "\n[ERRO] Tipo de atendimento inválido!\n";
        return;
    }

    c.senha = gerarSenha(c.tipo_atendimento);
    c.hora_entrada = time(0);

    int pos = 0;
    if (c.tipo_atendimento == 'U')
    {
        while (pos < tamFila && fila[pos].tipo_atendimento == 'U')
            pos++;
    }
    else if (c.tipo_atendimento == 'P')
    {
        while (pos < tamFila && (fila[pos].tipo_atendimento == 'U' || fila[pos].tipo_atendimento == 'P'))
            pos++;
    }
    else
    {
        pos = tamFila;
    }

    for (int i = tamFila; i > pos; i--)
    {
        fila[i] = fila[i - 1];
    }

    fila[pos] = c;
    tamFila++;

    cout << "\n[SUCESSO] Senha " << c.senha << " emitida para " << c.nome << ".\n";
}

void chamarSenha()
{
    if (tamFila == 0)
    {
        cout << "\n[AVISO] A fila esta vazia. Nenhum cliente para chamar.\n";
        return;
    }

    Cliente chamado = fila[0];

    for (int i = 0; i < tamFila - 1; i++)
    {
        fila[i] = fila[i + 1];
    }
    tamFila--;
    clientesAtendidos++;

    cout << "\n========================================" << endl;
    cout << "   CHAMANDO SENHA: " << chamado.senha << endl;
    cout << "   CLIENTE: " << chamado.nome << endl;
    cout << "   HORA DE ENTRADA: " << formatarHora(chamado.hora_entrada) << endl;
    cout << "========================================\n";
}

void exibirFila()
{
    if (tamFila == 0)
    {
        cout << "\n[AVISO] A fila atual esta vazia.\n";
        return;
    }

    cout << "\n--- ESTADO ATUAL DA FILA ---\n";
    for (int i = 0; i < tamFila; i++)
    {
        cout << i + 1 << "º | Senha: " << fila[i].senha
             << " | Nome: " << fila[i].nome
             << " | Entrada: " << formatarHora(fila[i].hora_entrada) << "\n";
    }
    cout << "----------------------------\n";
}

void cancelarSenha()
{
    if (tamFila == 0)
    {
        cout << "\n[AVISO] A fila esta vazia.\n";
        return;
    }

    string senhaCancelamento;
    cout << "\nDigite a senha que deseja cancelar (Ex: P001): ";
    cin >> senhaCancelamento;

    for (char &c : senhaCancelamento)
        c = toupper(c);

    int indiceEncontrado = -1;
    for (int i = 0; i < tamFila; i++)
    {
        if (fila[i].senha == senhaCancelamento)
        {
            indiceEncontrado = i;
            break;
        }
    }

    if (indiceEncontrado != -1)
    {
        string nomeCancelado = fila[indiceEncontrado].nome;
        for (int i = indiceEncontrado; i < tamFila - 1; i++)
        {
            fila[i] = fila[i + 1];
        }
        tamFila--;

        cout << "\n[SUCESSO] Senha " << senhaCancelamento << " (" << nomeCancelado << ") cancelada e removida da fila.\n";
    }
    else
    {
        cout << "\n[ERRO] Senha não encontrada na fila atual.\n";
    }
}

void estatisticas()
{
    cout << "\n--- ESTATISTICAS DO SISTEMA ---\n";
    cout << "Clientes aguardando na fila : " << tamFila << "\n";
    cout << "Total de clientes atendidos : " << clientesAtendidos << "\n";
    cout << "-------------------------------\n";
}

int main()
{
    int opcao = 0;
    while (opcao != 6)
    {
        cout << "\n=== SISTEMA DE GERENCIAMENTO DE FILAS ===\n";
        cout << "1. Emitir Nova Senha" << endl;
        cout << "2. Chamar Cliente" << endl;
        cout << "3. Cancelar Senha" << endl;
        cout << "4. Exibir Fila de Espera" << endl;
        cout << "5. Exibir Estatisticas" << endl;
        cout << "6. Sair do Sistema" << endl;
        cout << "Escolha uma opcao: ";

        cin >> opcao;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\n[ERRO] Entrada invalida! Por favor, digite apenas numeros.\n";
            cin.get();
            system("clear");
            continue;
        }

        switch (opcao)
        {
        case 1:
            emitirSenha();
            break;

        case 2:
            chamarSenha();
            break;

        case 3:
            cancelarSenha();
            break;

        case 4:
            exibirFila();
            break;

        case 5:
            estatisticas();
            break;

        case 6:
            cout << "Encerrando atendimentos." << endl;
            system("clear");
            break;

        default:
            cout << "Opção inválida" << endl;
            break;
        }

        if (opcao != 6)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
            system("clear");
        }
    }
    return 0;
}
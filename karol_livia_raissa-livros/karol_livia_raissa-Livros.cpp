//Alunas: Karol Guimarães Souza de Miranda, Lívia Fagundes dos Santos e Raissa Fernandes de Souza
//Tema: Livros | Turma: 14b

#include <iostream>
#include <fstream>
#include <limits>
#include <cstring>
#include <cstdlib> 

using namespace std;


const int TAM_MAX_LINHA = 256; 
const char* nomeCSV = "karol_livia_raissa-Livros.csv";
const char* nomeBinario = "karol_livia_raissa-Livros.bin";

struct Livro {
    short id_livro;
    char titulo[100];
    char autor[100];
    short quantidade_de_paginas;
    char genero[50];
    bool ativo;
};

void lerCSV(const char* nomeArquivo, Livro*& livros, int& quantidadeAtual, int& capacidade) {
    ifstream arquivo(nomeArquivo);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo CSV! Verifique se ambos os arquivos (.cpp e .csv) estão na mesma pasta." << endl;
        return;
    }

    
    char linhaTemp[TAM_MAX_LINHA]; 
    arquivo.getline(linhaTemp, TAM_MAX_LINHA); 

    quantidadeAtual = 0;
    capacidade = 40;
    if (livros) {
        delete[] livros;
    }
    livros = new Livro[capacidade];

    char lixo;
    Livro temp;

    while (arquivo.peek() != EOF) {
		
        if (quantidadeAtual == capacidade) {
			
            capacidade += 10;
            Livro* novoVetor = new Livro[capacidade];
            for (int i = 0; i < quantidadeAtual; i++) {
				
                novoVetor[i] = livros[i];
            }
            delete[] livros;
            livros = novoVetor;
        }

        arquivo >> lixo;
        arquivo >> temp.id_livro;
        arquivo >> lixo >> lixo;
        arquivo >> lixo;
        arquivo.getline(temp.titulo, 100, '"');
        arquivo >> lixo >> lixo;
        arquivo.getline(temp.autor, 100, '"');
        arquivo >> lixo >> lixo;
        arquivo >> temp.quantidade_de_paginas;
        arquivo >> lixo >> lixo >> lixo;
        arquivo.getline(temp.genero, 50, '"');

        temp.ativo = true;
        livros[quantidadeAtual++] = temp;

        arquivo.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    arquivo.close();
}

bool conferirSeLivroRepetido(Livro* livros, int quantidadeAtual, const char* novoTitulo, const char* novoAutor) {
	
    for (int i = 0; i < quantidadeAtual; i++) {
		
        if (strcmp(livros[i].titulo, novoTitulo) == 0 && strcmp(livros[i].autor, novoAutor) == 0 && livros[i].ativo) {
            return true;
        }
    }
    return false;
}

void adicionarNovoLivro(Livro*& livros, int& quantidadeAtual, int& capacidade) {
	
    Livro novoLivro;
    short maiorID = 0;
    for (int i = 0; i < quantidadeAtual; i++) {
		
        if (livros[i].id_livro > maiorID) {
            maiorID = livros[i].id_livro;
        }
    }
    novoLivro.id_livro = maiorID + 1;

    cout << "Insira os dados abaixo para adicionar um novo livro à lista:" << endl;
    cout << "Título do livro: ";
    cin.getline(novoLivro.titulo, 100);
    cout << "Nome do autor: ";
    cin.getline(novoLivro.autor, 100);
    cout << "Quantidade de páginas (incluindo prólogo e epílogo): ";
    cin >> novoLivro.quantidade_de_paginas;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Gênero do livro: ";
    cin.getline(novoLivro.genero, 50);

    novoLivro.ativo = true;

    if (conferirSeLivroRepetido(livros, quantidadeAtual, novoLivro.titulo, novoLivro.autor)) {
		
        cout << "Esse livro já existe na lista. Não será adicionado." << endl;
        cout << "Retorne ao menu e saiba mais sobre o livro realizando uma busca." << endl;
        return;
    }

    if (quantidadeAtual == capacidade) {
		
        capacidade += 10;
        Livro* novoVetor = new Livro[capacidade];
        for (int i = 0; i < quantidadeAtual; i++) {
			
            novoVetor[i] = livros[i];
        }
        delete[] livros;
        livros = novoVetor;
    }

    livros[quantidadeAtual++] = novoLivro;
    cout << "Livro adicionado com sucesso! O ID gerado é: " << novoLivro.id_livro << endl;
}

void buscarLivroPorTitulo(Livro livros[], int quantidade) {
	
    char tituloBuscado[100];
    cout << "Digite o título do livro que deseja buscar: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(tituloBuscado, 100);

    int esquerda = 0;
    int direita = quantidade - 1;
    int posEncontrado = -1;

    while (esquerda <= direita) {
		
        int meio = esquerda + (direita - esquerda) / 2;
        int comparar = strcmp(tituloBuscado, livros[meio].titulo);

        if (comparar == 0) {
			
            posEncontrado = meio;
           
            
        } else if (comparar < 0) {
			
            direita = meio - 1;
            
        } else {
			
            esquerda = meio + 1;
        }
    }

    if (posEncontrado != -1 && livros[posEncontrado].ativo) {
		
        cout << "Livro encontrado: " << endl;
        cout << "Autor: " << livros[posEncontrado].autor << endl;
        cout << "ID: " << livros[posEncontrado].id_livro << endl;
        cout << "Quantidade de páginas: " << livros[posEncontrado].quantidade_de_paginas << endl;
        cout << "Gênero: " << livros[posEncontrado].genero << endl;
        
    } else {
		
        cout << "Livro com o título \"" << tituloBuscado << "\" não encontrado ou inativo.\n";
    }
}

void ordenarLivrosPorId(Livro livros[], int quantidadeAtual) {
	
    Livro valor_pivo;
    
    int j;

    for (int i = 1; i < quantidadeAtual; i++) {
		
        valor_pivo = livros[i];
        j = i - 1;

        while ((j >= 0) && (valor_pivo.id_livro < livros[j].id_livro)) {
			
            livros[j + 1] = livros[j];
            j--;
        }
        livros[j + 1] = valor_pivo;
    }

    cout << endl;
    cout << "Livros ordenados por ID com sucesso!" << endl;
}

void ordenarLivrosPorTitulo(Livro livros[], int quantidadeAtual) {
	
    int i, j, pos_menor;
    Livro aux;

    for (i = 0; i < quantidadeAtual - 1; i++) {
		
        pos_menor = i;

        for (j = i + 1; j < quantidadeAtual; j++) {
			
            if (strcmp(livros[j].titulo, livros[pos_menor].titulo) < 0) {
				
                pos_menor = j;
            }
        }

        if (pos_menor != i) {
			
            aux = livros[i];
            livros[i] = livros[pos_menor];
            livros[pos_menor] = aux;
        }
    }

    cout << endl;
    cout << "Livros ordenados por título com sucesso!" << endl;
}

Livro* _buscarLivroPorIdRecursivo(Livro livros[], int esquerda, int direita, int idBuscado) {
    if (esquerda > direita) {
        return nullptr;
    }

    int meio = esquerda + (direita - esquerda) / 2;

    if (livros[meio].id_livro == idBuscado) {
		
        return &livros[meio];
        
    } else if (livros[meio].id_livro < idBuscado) {
		
        return _buscarLivroPorIdRecursivo(livros, meio + 1, direita, idBuscado);
        
    } else {
		
        return _buscarLivroPorIdRecursivo(livros, esquerda, meio - 1, idBuscado);
    }
}

void buscarLivroPorId(Livro livros[], int quantidadeAtual) {
    int idBuscado;
    cout << "Digite o ID do livro que deseja buscar (busca binária recursiva): ";
    cin >> idBuscado;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Livro* livroEncontrado = _buscarLivroPorIdRecursivo(livros, 0, quantidadeAtual - 1, idBuscado);

    if (livroEncontrado != nullptr && livroEncontrado->ativo) {
		
        cout << "Livro encontrado: " << endl;
        cout << "Título: " << livroEncontrado->titulo << endl;
        cout << "Autor: " << livroEncontrado->autor << endl;
        cout << "Páginas: " << livroEncontrado->quantidade_de_paginas << endl;
        cout << "Gênero: " << livroEncontrado->genero << endl;
    } else {
        cout << "Livro com ID " << idBuscado << " não encontrado ou inativo.\n";
    }
}

void removerLogicamente(Livro* livros, int quantidadeAtual) {
    short idParaRemover = 0;

    cout << "Escreva o ID do livro que você deseja remover da lista:" << endl;
    cin >> idParaRemover;
    cout << endl;

    bool encontrado = false;
    for (int i = 0; i < quantidadeAtual; i++) {
		
        if (livros[i].ativo && livros[i].id_livro == idParaRemover) {
			
            livros[i].ativo = false;
            encontrado = true;
            cout << "Livro com ID equivalente a " << idParaRemover << " foi removido logicamente com sucesso." << endl;
            
        }
    }
    if (!encontrado) {
        cout << "Livro com ID equivalente a " << idParaRemover << " NÃO ENCONTRADO." << endl;
    }
}

void ReativarLogicamenteLivroRemovido(Livro* livros, int quantidadeAtual) {
	short idParaReativar = 0;

	cout << "Escreva o ID do livro que você deseja reativar na lista:" << endl;
    cin >> idParaReativar;
    cout << endl;

    bool encontrado = false;
    for (int i = 0; i < quantidadeAtual; i++) {
		
        if (livros[i].id_livro == idParaReativar) {
			
            if (!livros[i].ativo) {
                livros[i].ativo = true;
                cout << "Livro com ID equivalente a " << idParaReativar << " foi reativado logicamente com sucesso." << endl;
                
            } else {
                cout << "Livro com ID " << idParaReativar << " já se encontra ativo." << endl;
            }
            encontrado = true;
            
        }
    }
    if (!encontrado) {
        cout << "Livro com ID " << idParaReativar << " não encontrado." << endl;
    }
}

void imprimirLivros(Livro* livros, int quantidadeAtual, int inicio = 0, int fim = -1) {
	
    if (quantidadeAtual == 0) {
        cout << "NENHUM livro para exibir no momento, adicione novos livros na lista." << endl;
        return;
    }

    if (fim == -1) {
        fim = quantidadeAtual - 1;
    }
    if (inicio < 0) inicio = 0;
    if (fim >= quantidadeAtual) fim = quantidadeAtual - 1;

    if (inicio > fim) {
        cout << "Intervalo de exibição inválido! " << endl;
        
        return;
    }
    cout << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "---------- Livros Solicitados para a exibição ----------" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << endl;

    int exibidos = 0;
    for (int i = inicio; i <= fim; i++) {
		
        if (livros[i].ativo) {
			
            cout << "ID: " << livros[i].id_livro << endl;
            cout << "Título: " << livros[i].titulo << endl;
            cout << "Autor: " << livros[i].autor << endl;
            cout << "Páginas: " << livros[i].quantidade_de_paginas << endl;
            cout << "Gênero: " << livros[i].genero << endl;
            cout << "--------------------------------------------------------" << endl;
            cout << endl;
            exibidos++;
        }
    }
    if (exibidos == 0) {
        cout << "Nenhum livro ativo no intervalo especificado." << endl;
    }
}

void mostrarTodosLivrosAtivos(Livro* livros, int quantidadeAtual) {
	
    imprimirLivros(livros, quantidadeAtual);
}

void pedirEExibirLivrosPorIntervalo(Livro* livros, int quantidadeAtual) {
	
    int inicio, fim;
    bool valido = false;
    do {
		
        cout << "Digite o índice inicial (0 para começar do primeiro): ";
        cin >> inicio;
        cout << endl;
        cout << "Digite o índice final (até " << quantidadeAtual -1 << "): ";
        cin >> fim;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (cin.fail() || inicio < 0 || fim < 0 || inicio > fim || fim >= quantidadeAtual) {
			
			cout << endl;
            cout << "Intervalo de exibição inválido! " << endl;
			cout << "Para melhor funcionamento, NÃO INSIRA:" << endl;
			cout << "- Números negativos " << endl;
			cout << "- Índice inicial maior que o final" << endl;
			cout << "- Índice final maior que o disponível" << endl;
			cout << endl;
			
            cin.clear();
        } else {
            valido = true;
        }
    } while (!valido);

    imprimirLivros(livros, quantidadeAtual, inicio, fim);
}

void salvarCSV(const char* nomeArquivo, Livro* livros, int quantidadeAtual) {
	
    ofstream arquivo(nomeArquivo);
    if (!arquivo) {
		
        cout << "Erro ao salvar o arquivo CSV." << endl;
        return;
    }

    for (int i = 0; i < quantidadeAtual; i++) {
		
        if (livros[i].ativo) {
			
            arquivo << "\"" << livros[i].id_livro << "\";"
                    << "\"" << livros[i].titulo << "\";"
                    << "\"" << livros[i].autor << "\";"
                    << "\"" << livros[i].quantidade_de_paginas << "\";"
                    << "\"" << livros[i].genero << "\"" << endl;
        }
    }
    arquivo.close();
}

void TransformarEmBinario(const char* nomeCSV, const char* nomeBinario) {
	
    ifstream csv(nomeCSV);
    ofstream bin(nomeBinario, ios::binary);
    
    if (!csv || !bin) {
		
        cout << "Erro ao abrir arquivos! Verifique se os arquivos (.cpp e .bin) estão na mesma pasta." << endl;
        return;
    }

    
    char linhaTemp[TAM_MAX_LINHA]; 
    csv.getline(linhaTemp, TAM_MAX_LINHA); 

    Livro temp;

    while (csv.peek() != EOF) {
		
        char lixo;
        csv >> lixo;
        csv >> temp.id_livro;
        csv >> lixo >> lixo;
        csv >> lixo;
        csv.getline(temp.titulo, 100, '"');
        csv >> lixo >> lixo;
        csv.getline(temp.autor, 100, '"');
        csv >> lixo >> lixo;
        csv >> temp.quantidade_de_paginas;
        csv >> lixo >> lixo >> lixo;
        csv.getline(temp.genero, 50, '"');

        temp.ativo = true;
        bin.write(reinterpret_cast<const char*>(&temp), sizeof(Livro));
        csv.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    csv.close();
    bin.close();
}

void traduzirArquivoBinario(const char* nomeBinario) {
    ifstream bin(nomeBinario, ios::binary);
    if (!bin) {
        cout << "Erro ao abrir o arquivo binário! Verifique se ambos os arquivos (.cpp e .bin) estão na mesma pasta." << endl;
        return;
    }

    Livro temp;
    cout << "--------------------------------------------------------" << endl;
    cout << "---------- Livros no Arquivo Binário ----------" << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << endl;

    bool encontrouAtivo = false;
    while (bin.read(reinterpret_cast<char*>(&temp), sizeof(Livro))) {
		
        if (temp.ativo) {
			
            encontrouAtivo = true;
            cout << "ID: " << temp.id_livro << endl;
            cout << "Título: " << temp.titulo << endl;
            cout << "Autor: " << temp.autor << endl;
            cout << "Páginas: " << temp.quantidade_de_paginas << endl;
            cout << "Gênero: " << temp.genero << endl;
            cout << "--------------------------------------------------------" << endl;
            cout << endl;
        }
    }
    if (!encontrouAtivo) {
		
        cout << "Nenhum livro ativo encontrado no arquivo binário." << endl;
    }
    bin.close();
}

void perguntaParaSalvarAlteracoes(const char* nomeCSV, Livro* livros, int quantidade) {
    char salvar;
    bool resposta_valida = false;

    do {
        cout << endl;
        cout << "Deseja salvar alterações?" << endl << "S - sim" << endl << "N - não" << endl;
        cin >> salvar;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (salvar == 'S' || salvar == 's') {
			
            resposta_valida = true;
            salvarCSV(nomeCSV, livros, quantidade);
            TransformarEmBinario(nomeCSV, nomeBinario);
            cout << endl << "Alteração salva com sucesso!" << endl;
            
        } else if (salvar == 'N' || salvar == 'n') {
			
            resposta_valida = true;
            cout << endl << "Que pena que você não quer salvar as alterações :/" << endl;
            
        } else {
			
            resposta_valida = false;
            cout << "Resposta inválida. Por favor, digite 'S' ou 'N'." << endl;
        }
        
    } while (!resposta_valida);
}

int main() {
	
    Livro* livros = nullptr;
    int quantidade = 0;
    int capacidade = 0;
    int opcao = 0;
    char opcao_busca = ' ';

    lerCSV(nomeCSV, livros, quantidade, capacidade);
    TransformarEmBinario(nomeCSV, nomeBinario);

    do {
        system("clear"); 

        cout << "--------------------------------------------------------" << endl;
        cout << "------------------- MENU PRINCIPAL----------------------" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << endl;
        cout << "1 - Adicionar livros" << endl;
        cout << "2 - Ordenar livros por nome" << endl;
        cout << "3 - Ordenar livros por ID " << endl;
        cout << "4 - Buscar registro " << endl;
        cout << "5 - Remover livro logicamente " << endl;
        cout << "6 - Reativar livro logicamente " << endl;
        cout << "7 - Listar livros direto do arquivo binário" << endl;
        cout << "8 - Exibir intervalo de livros " << endl;
        cout << "9 - Exibir todos os livros ativos" << endl;
        cout << "10 - Sair" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << endl;

        cout << "Escolha uma opção: ";
        cin >> opcao;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch(opcao) {
            case 1:
            
                adicionarNovoLivro(livros, quantidade, capacidade);
                perguntaParaSalvarAlteracoes(nomeCSV, livros, quantidade);
                break;

            case 2:
            
                ordenarLivrosPorTitulo(livros, quantidade);
                perguntaParaSalvarAlteracoes(nomeCSV, livros, quantidade);
                break;

            case 3:
            
                ordenarLivrosPorId(livros, quantidade);
                perguntaParaSalvarAlteracoes(nomeCSV, livros, quantidade);
                break;

            case 4:
            
                do {
                    cout << endl;
                    cout << "Qual método você gostaria de usar para buscar registro?" << endl
                         << "a - Buscar por título " << endl
                         << "b - Buscar por ID " << endl;
                    cin >> opcao_busca;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                    if(opcao_busca == 'a' || opcao_busca == 'A') {
                        buscarLivroPorTitulo(livros, quantidade);
                    } else if (opcao_busca == 'b' || opcao_busca == 'B') {
                        buscarLivroPorId(livros, quantidade);
                    } else {
                        cout << "Opção inválida. Digite 'a' ou 'b'." << endl;
                    }
                    
                } while (opcao_busca != 'a' && opcao_busca != 'A' && opcao_busca != 'b' && opcao_busca != 'B');
                break;

            case 5:
                removerLogicamente(livros, quantidade);
                perguntaParaSalvarAlteracoes(nomeCSV, livros, quantidade);
                break;

            case 6: 
            
                ReativarLogicamenteLivroRemovido(livros, quantidade);
                perguntaParaSalvarAlteracoes(nomeCSV, livros, quantidade);
                break;

            case 7:
            
                traduzirArquivoBinario(nomeBinario);
                break;

            case 8:
            
                pedirEExibirLivrosPorIntervalo(livros, quantidade);
                break;

            case 9:
            
                mostrarTodosLivrosAtivos(livros, quantidade);
                break;

            case 10:
            
				cout << endl; 
                cout << "Obrigada por usar nosso sistema! Volte sempre ;)" << endl;
                break;

            default:
            
				cout << endl;
                cout << "Opção inválida! Tente novamente." << endl;
                break;
        }

        if (opcao != 10) {
			
            cout << endl << "Pressione ENTER para voltar ao menu...";
            cin.get();
        }

    } while (opcao != 10);

    delete[] livros;

    return 0;
}
	

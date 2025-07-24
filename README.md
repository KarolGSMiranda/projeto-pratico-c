1. INTRODUÇÃO 
Este projeto teve como objetivo o desenvolvimento de um sistema de cadastro 
de livros, implementado na linguagem C++, com funcionalidades como inserção de 
novos registros, remoção lógica, busca binária para consultas eficientes e ordenação 
de registros, além de permitir a importação e exportação dos dados no formato CSV, 
o que facilita sua manipulação por ferramentas externas. 
Ao longo do desenvolvimento, foi projetado um sistema semelhante a uma 
biblioteca digital, capaz de gerenciar dados como ID do livro, título, autor, quantidade 
de páginas e gênero literário.  
2. LÓGICA DO PROGRAMA 
O programa tem como objetivo realizar o gerenciamento completo de uma 
coleção de livros. Logo no início, os dados são carregados de um arquivo CSV e 
armazenados dinamicamente na memória, possibilitando a manipulação durante a 
execução. Esses dados também podem ser convertidos para um arquivo binário, o 
que garante uma forma de armazenamento mais rápida e compacta. 
O sistema permite que o usuário visualize todos os livros cadastrados ou 
apenas parte deles, escolhendo um intervalo específico. Também é possível adicionar 
novos livros, garantindo que não haja duplicidade, e realizar remoções lógicas, que 
apenas desativam os registros sem apagá-los, mantendo a integridade dos dados.  
Para facilitar o acesso às informações, o programa permite ordenar os livros 
por título (ordem alfabética) ou por ID (ordem crescente), o que possibilita buscas mais 
rápidas e organizadas. A busca por título utiliza o método de busca binária, enquanto 
a busca por ID é feita de forma recursiva. Ao final de cada ação importante, o sistema 
oferece ao usuário a opção de salvar as alterações, garantindo que os dados mais 
recentes sejam mantidos nos arquivos utilizados. 
2.1. 
lerCSV 
FUNÇÕES 
Lê os dados do arquivo .csv e armazena os livros em um vetor dinâmico na 
memória. 
conferirSeLivroRepetido 
Verifica se já existe um livro com o mesmo título e autor, evitando duplicatas. 
adicionarNovoLivro 
Permite ao usuário adicionar um novo livro preenchendo os dados via teclado. 
buscarLivroPorTitulo 
Realiza uma busca binária pelo título do livro (requer lista ordenada por título). 
ordenarLivrosPorId 
Ordena os livros com base no ID de forma crescente. 
ordenarLivrosPorTitulo 
Ordena os livros em ordem alfabética de título. 
_buscarLivroPorIdRecursivo 
Executa a busca binária recursiva por ID internamente. 
buscarLivroPorId 
Busca um livro pelo ID utilizando a função recursiva interna. 
removerLogicamente 
Marca um livro como inativo, sem removê-lo da memória. 
ReativarLogicamenteLivroRemovido 
Reativa um livro que foi removido logicamente, tornando-o visível novamente. 
imprimirLivros 
Exibe os livros ativos, com opção de mostrar apenas um intervalo da lista. 
mostrarTodosLivrosAtivos 
Mostra todos os livros ativos da lista. 
pedirEExibirLivrosPorIntervalo 
Pede ao usuário um intervalo de posições e exibe os livros correspondentes. 
salvarCSV 
Salva os livros ativos em um novo arquivo .csv. 
TransformarEmBinario 
Converte o conteúdo do .csv em um arquivo binário .bin. 
traduzirArquivoBinario 
Lê e exibe os livros ativos armazenados no arquivo binário. 
perguntaParaSalvarAlteracoes 
Pergunta ao usuário se deseja salvar as alterações feitas na lista de livros. 
3. ERROS E ACERTOS DURANTE O DESENVOLVIMENTO DO PROJETO 
Durante o desenvolvimento do projeto, foram enfrentados alguns desafios. 
Organizar a ordem das funções foi complicado, pois algumas dependem de outras 
para funcionar, o que exigiu atenção para evitar erros na execução. A 
implementação da busca binária, especialmente por ser um conteúdo novo, 
demandou estudos extras para compreender e aplicar corretamente. Também 
houve dificuldade ao juntar as partes desenvolvidas por cada integrante, já que era 
necessário garantir a integração e a consistência do código. Por fim, como o 
projeto foi desenvolvido no Windows, foi necessário a realização de diversos testes 
no Linux para assegurar que tudo rodasse bem no sistema desejado para 
avaliação final. Por outro lado, algumas etapas foram executadas com facilidade. 
A implementação da ordenação, por exemplo, ocorreu de forma fluida, sem 
apresentar maiores complicações, e o desenvolvimento o menu principal também 
foi bem-sucedido. 
4. CONCLUSÃO 
O desenvolvimento deste sistema de cadastro de livros em C++ 
proporcionou uma oportunidade valiosa de aplicar, na prática, conceitos 
fundamentais de lógica de programação, estrutura de dados, manipulação de 
arquivos e algoritmos de ordenação e busca.  Além dos aspectos técnicos, o 
projeto também demandou organização, trabalho em equipe e superação de 
desafios, contribuindo para o crescimento acadêmico e pessoal por meio de estudo 
autônomo, testes e constantes ajustes. Com isso, o projeto se mostrou uma 
experiência completa e enriquecedora, tanto no aspecto prático quanto no 
desenvolvimento das habilidades essenciais para a área de tecnologia.

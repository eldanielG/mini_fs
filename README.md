# Mini Sistema de Arquivos em Memória

Este projeto implementa um mini sistema de arquivos em memória em C, que simula operações básicas de um sistema de arquivos real. O objetivo é demonstrar a estrutura de diretórios, gerenciamento de arquivos e controle de acesso.

## Estruturas de Dados

### FCB (File Control Block)
O FCB é uma estrutura que contém metadados sobre um arquivo, incluindo:
- Nome do arquivo
- Tamanho do arquivo
- Tipo do arquivo
- Datas de criação e modificação
- ID único (simulando inode)
- Permissões (RWX para owner, group e public)

### Árvore de Diretórios
A estrutura de diretórios é implementada como uma árvore, permitindo operações como:
- `mkdir`: criar diretórios
- `cd`: mudar de diretório

## Conceitos Teóricos Implementados

- **Atributos de Arquivos**: Cada arquivo possui atributos que são armazenados no FCB, permitindo o gerenciamento de informações essenciais.
- **Permissões**: O sistema implementa controle de acesso com permissões numéricas, permitindo que usuários definam quem pode ler, escrever ou executar arquivos.
- **Alocação de Blocos**: O sistema simula a alocação de blocos em disco usando um array de caracteres, permitindo a alocação contínua ou indexada de espaço para arquivos.

## Exemplos de Uso

- Criar um diretório: `mkdir nome_do_diretorio`
- Mudar para um diretório: `cd nome_do_diretorio`
- Criar um arquivo: `touch nome_do_arquivo`
- Escrever em um arquivo: `echo "conteúdo" > nome_do_arquivo`
- Ler um arquivo: `cat nome_do_arquivo`
- Copiar um arquivo: `cp nome_do_arquivo destino`
- Mover ou renomear um arquivo: `mv nome_do_arquivo novo_nome`
- Excluir um arquivo: `rm nome_do_arquivo`
- Alterar permissões: `chmod 755 nome_do_arquivo`

## Comparação com Comandos Linux Reais

Os comandos implementados neste mini sistema de arquivos são semelhantes aos comandos do Linux, permitindo que usuários familiarizados com o terminal Linux utilizem o sistema de forma intuitiva.

## Compilação e Execução

Para compilar o projeto, utilize o Makefile incluído. Execute o seguinte comando no terminal:

```
make
```

Após a compilação, execute o programa gerado:

```
./mini_fs
```

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests para melhorias e correções.
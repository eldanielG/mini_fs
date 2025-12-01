# MiniFS

Mini sistema de arquivos em C com interface interativa. Nesta versão, as operações usam o sistema de arquivos real do Windows: pastas e arquivos são criados/alterados dentro do diretório raiz onde o programa é executado.

## Visão Geral

- Diretório raiz: é o `cwd` (diretório atual) no momento da execução.
- Diretório atual: começa no raiz e muda com `cd`. Não é permitido navegar para fora do raiz.
- Nomes de arquivos e diretórios devem ser simples (sem `/` ou `\`). Use `cd` para entrar em subpastas.

## Comandos Disponíveis

- `mkdir <nome>`: cria uma subpasta real no diretório atual.
- `cd <nome>`: entra em uma subpasta existente. `cd /` volta ao raiz; `cd ..` sobe um nível (sem sair do raiz).
- `touch <arquivo>`: cria o arquivo (ou atualiza sua data) no diretório atual.
- `echo <arquivo> <conteudo>`: escreve o conteúdo no arquivo (substitui o conteúdo anterior). Na UI, use `_` para espaços.
- `cat <arquivo>`: lê e imprime o conteúdo do arquivo.
- `cp <origem> <destino>`: copia o arquivo no diretório atual.
- `mv <origem> <destino>`: renomeia o arquivo no diretório atual.
- `rm <arquivo>`: remove o arquivo.
- `chmod <arquivo> <permissao>`: altera permissões (ver seção abaixo).

## Sobre `chmod` no Windows

- O programa aceita permissões em formato octal (ex.: `755`, `644`).
- Em ambientes `ucrt64/MSYS2`, `chmod` é mapeado, mas o efeito é limitado ao que o Windows suporta. Em geral:
	- Bits de leitura/escrita podem refletir no atributo somente leitura.
	- Bit de execução não tem efeito nativo em arquivos regulares no Windows.
- A chamada tenta `_chmod` e, em seguida, `chmod`. Se nenhuma surtir efeito, retorna `-1`.
- Use `chmod` como metadado de intenção e compatibilidade; não espere o mesmo comportamento do Linux.

## Compilação e Execução

Via task do VS Code (recomendado):
- Execute a task "Build MiniFS" e depois rode `mini_fs.exe`.

Via terminal PowerShell:
```powershell
Set-Location "c:\Users\(seuUsuario)\(pastadoprojeto)\mini_fs"
C:\msys64\ucrt64\bin\gcc.exe -fdiagnostics-color=always -g src/main.c src/filesystem.c -I include -o mini_fs.exe
.\mini_fs.exe
```

## Exemplo Rápido

Sequência de operações comuns:
1. `mkdir pasta1`
2. `cd pasta1`
3. `touch arquivo.txt`
4. `echo arquivo.txt conteudo_com_espacos_usa_underscore`
5. `cat arquivo.txt`

## Limitações e Próximos Passos

- Não há listagem (`ls`) de arquivos/diretórios no menu.
- Navegação e operações são somente no diretório atual (sem caminhos com barras).
- Podemos adicionar `ls` e suporte opcional a caminhos relativos se necessário.

## Contribuições

Contribuições são bem-vindas! Abra issues ou PRs com sugestões e correções.
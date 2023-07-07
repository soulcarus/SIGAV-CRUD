# SIGAV-CRUD
Aplicação WEB com Python e C para Integração de um Sistema de Gerenciamento de Eventos Simples

O projeto foi desenvolvido para um trabalho da cadeira de Laboratório de Programação.

---

## Índice
1. [Pré-requisitos](#prerequisites)
2. [Construindo o projeto](#building)
3. [Executando o projeto](#running)
4. [Desenvolvimento do Projeto](#functions)
5. [Autores](#authors)

## Pré-requisitos <a name="prerequisites"></a>
- python 3.11 ou superior [Download oficial](https://www.python.org)
- Testado no Windows 10, Windows 11 e Linux Satux

## Construindo o projeto <a name="building"></a>
Clonando o repositório
```bash
$ git clone https://github.com/icarufc/SIGAV-CRUD
$ cd SIGAV_CRUD
```

## Executando o projeto <a name="running"></a>
```bash
$ gcc -o teste prerequisites.c && ./teste
$ gcc -o script script.c && ./script
$ gcc -o script script.c && python3 main.py
```
É obrigatório na primeira vez que for usar o programa, executar essa ordem de funções, depois, só precisa executar:

```bash
$ gcc -o script script.c && python3 main.py
```

No terminal será apresentado: 
- as requisições HTTP e seus modos;
- os prints dentro de funções do C não funcionam (está desabilitado o print por um método built-in de como chamamos a função pelo python)
- será apresentado um link de onde estará ativo a aplicação

## Desenvolvimento do Código <a name="functions"></a>
Parte concluída:
- Documentação
- HTML &  CSS
- Login
- Cadastro
- Participar de Evento
- Ler Eventos do Usuário
- Adicionar Evento
- Listar Eventos

To-do (corrigir ou melhorar) :

- Remover Evento (corrigir, parou de remover com as alterações no lab) [limite: 08/07]
- Alterar Evento (corrigir, parou de alterar com as alterações no lab) [limite: 08/07]
- add atributo password html
- add atributo date html
- log de erro senha inválida
- Função alterar senha
- Permitir cadastro + 1 evento
- Solicitar dados de ADMIN para acessar painel admin

## Autores <a name="authors"></a>
<div style="display: flex; gap: 8px">

  <img src="./collaborators/icaro.png" width="128" height="128"/>
  <img src="./collaborators/ylana.jpeg" width="128" height="128"/>
  <img src="./collaborators/maju.png" width="128" height="128"/>
  <img src="./collaborators/zaca.png" width="128" height="128"/>

</div>

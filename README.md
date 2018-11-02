# Projeto BARES LP1

Desenvolvido  por [Allan de Miranda](https://github.com/allandemiranda)
                e [Josué Cláudio](https://github.com/JO5U3)

30 de outubro de 2018 - LP1 - IMD

## Introdução

O projeto tem como intuito desenvolver um avaliador de expressões aritméticas utilizando as ferramentas e conhecimentos adquiridos durante a disciplina de Linguagem de Programação 1 do curso de Tecnologia da Informação da UFRN/IMD.

## Instalação e execução

Para instalar e executar o programa siga as instruções: 

1. Abra o terminal do seu sistema operacional e digite ...
2. `git clone https://github.com/allandemiranda/BARES_LP1.git`
3. `cd BARES_LP1`
4. `g++ -Wall -std=c++11 src/*.cpp -I include -o ./bin/bares.o`
5. `./bin/bares.o < "caminho do arquivo de entrada" > "saída com as respostas"`

## Arquivos de entrada e saída

É recomendado que os arquivos de entrada e saída sejam manipulados dentro da pasta /data do projeto.

`cd data`</br>
`vim entrada.txt`

Caso existam mais de uma expressão no arquivo de entrada, os separe por linha. Assim como as respostas correspondem unicamente a linha da expressão matemática.

`./bin/bares.o < ./data/entrada.txt > ./data/saida.txt`


entrada.txt -> `vim ./data/entrada.txt`</br>
`240 / 12`</br>
`12 / 240`</br>
`120 / (2- 12 % 10 )`</br>
` 2 * 4`</br>
` 10 * 23`</br>
` 10000 * 50 * 30 * 2 * 5`</br>
` 30 * 2 * 5`</br>
` 1 - 2 - 3 - 4 - 5 - 6 - 7 - 8 - 9`</br>

saida.txt -> `vim ./data/saida.txt`</br>
`20`</br>
`0`</br>
`Division by zero!`</br>
`8`</br>
`230`</br>
`Numeric overflow error!`</br>
`300`</br>
`-43`</br>

## Operações suportadas

Será suportado para esta versão:

- Números inteiros constantes de -32.768 a 32.767
- Operadores +, −, /, ∗, ˆ, %
- Parênteses "(" e ")"

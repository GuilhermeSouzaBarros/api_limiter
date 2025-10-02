# Limitador de Taxa de Requisições (API Rate Limiter)

**Dupla**: Guilherme Souza Barros, Vítor Oliveira Amorim
**Disciplina**: Conceitos de Linguagens de Programação

## Compilação e Execução
O programa deverá ser compilado utilizando a diretiva `make`, que segue as instruções de compilação especificadas no arquivo Makefile, localizado na raíz do projeto.

Para executar, basta utilizar a diretiva `make run`.

Caso precise limpar os arquivos desnecessários, basta utilizar a diretiva `make clean`.

## Respostas (Questões para Reflexão)

1 - Para preservar o estado limitador entre as invocações da função nós utilizamos uma estrutura de `Bucket` declarada globalmente. Isso é importante porque a estrutura precisa ter o seu estado preservado durantes diferentes chamadas da função para que a aplicação funcione como o desejado. Caso as informações de estado fossem armazenadas em variáveis locais automáticas, não seria possível identificar qual foi o tempo em que ocorreu a última requisição. Em nossa solução, o tempo de vida das informações fica limitado até que a estrutura seja desalocada da memória, as informações são acessíveis por qualquer lugar do programa e o tempo de binding é em tempo de compilação. A alternativa de utilizar variável estática teria tempo de binding relativo se ela é uma variável global ou não: caso fosse alocada de forma global, ela seria em tempo de compilação, e caso fosse de forma local, ela seria em tempo de execução.

2 - Caso o cliente utilizar as funções compiladas em um .a, ele precisará recompilar o código toodas as vezes que ele for realizar uma modificação na biblioteca, contudo ele não precisará compilar esse trecho de código caso ele precise apenas alterar o código da aplicação dele. Além disso, ele não pode fazer alterações durante a execução do programa. Como o código está em binário, ele sempre funcionará de forma consistente independentemente do ambiente de utilização. Por outro lado, se o cliente utilizar a biblioteca de forma dinâmica com um arquivo .so, ele poderá fazer alterações na biblioteca durante a execução do programa, porém esse trecho de código precisará ser reinterpretado todas as vezes que o interpretador passar por esse trecho de código. Como consequência, não é mais garantido que o código sempre terá os mesmos resultados em cada ambiente de execução, já que o código não está em binário

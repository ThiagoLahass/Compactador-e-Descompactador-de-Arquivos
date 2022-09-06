<h1 align="center"> Compactador/Descompactador de Arquivos </h1>
<p align="center">
<img src="http://img.shields.io/static/v1?label=VERSAO&message=v0.0.0&color=blue&style=for-the-badge"/>
</p>
<p align="center">
<img src="http://img.shields.io/static/v1?label=code_quality&message=C&color=res&style=for-the-badge"/>
</p>
<p align="center">
<img src="http://img.shields.io/static/v1?label=STATUS&message=CONCLUIDO&color=GREEN&style=for-the-badge"/>
</p>

## Visão Geral:
  O projeto em questão tem como objetivo a criação de um programa
compactador/descompactador de arquivos, com base na codificação de Huffman. Ao
fim da implementação, o código Compacta deverá ler a entrada fornecida em um
arquivo (passado como parâmetro no terminal) e gerar um arquivo compactado do
tipo “.comp”. Além disso, o código Descompacta deverá ler um arquivo compactado
(“.comp”) e, a partir dele, gerar o original.

## Implementação:
Para implementar os programas citados foram utilizadas estruturas de
dados, sendo elas, os TADs dos tipos árvore, lista encadeada e bitmap.


## Execução do programa:
Todos os comandos devem ser dados a partir do diretório raiz, onde se
encontra o arquivo Makefile. <br /> Comandos:
- Para apagar os arquivos temporários:<br />
 make clean
- Para compilar os códigos e criar o executável:<br />
 make
- Para rodar o programa “compacta”:<br />
 ./compacta ‘arquivo.extensão’
- Para rodar o programa “descompacta”:<br />
 ./descompacta ‘arquivo.comp’

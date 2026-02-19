implemente um mecanismo que aceita markdown na criação de artigos.

implemente no seguinte formato: 
~~~bash
vibelog start --port  3000 --database-path test --root-password teste --markdown-converter-command  'command #INPUT# --o #OUTPUT#'
~~~
um exemplo de **markdown-converter-command** é:
~~~bash
pandoc --from markdown --to html --standalone --output #OUTPUT# #INPUT#
~~~
aonde deve ser executado o commando dando um replace no #OUTPUT# pelo caminho do arquivo que deve ser gerado. 
e #INPUT# pelo caminho do arquivo de markdown.

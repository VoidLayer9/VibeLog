implemente um mecanismo que aceita markdown na criação de artigos.

implemente no seguinte formato: 
~~~bash
vibelog start --port  3000 --database-path test --root-password teste --markdown-converter-command  'command --o #OUT#'
~~~
aonde deve ser executado o commando dando um replace no #OUT# pelo caminho do arquivo que deve ser gerado. 
use um mecanismo de cacheamento baseado em sha256 para converter o arquivo de markdown para html para evitar reprocessamento.

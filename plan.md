implemente um mecanismo que aceita markdown na criação de artigos.

entrada de CLI: 
~~~bash
vibelog start --port  3000 --database-path test --root-password teste --markdown-converter-command  'command #INPUT# --o #OUTPUT#'
~~~
um exemplo de **markdown-converter-command** é:
~~~bash
pandoc --from markdown --to html --standalone --output #OUTPUT# #INPUT#
~~~
aonde deve ser executado o commando dando um replace no #OUTPUT# pelo caminho do arquivo que deve ser gerado. 
e #INPUT# pelo caminho do arquivo de markdown.

use um mecanismo de cache para que não precise gerar o html toda vez que o usuário entrar no site.

para isso, crie um wrapper que gere um hash do arquivo de markdown e compare com o hash do arquivo de cache.

se o hash for diferente, gere o html e salve no cache.

se o hash for igual, use o html do cache.

para gerar o hash, use a função wrapper_generate_cached_sha_from_file.


edite  o README.md com as instruções de como usar o markdown-converter-command.
faça o refactor de lang na aplicação:
todas as rotas devem ser iniciadas com  /<lang>/<route>

<lang> pode ser pt ou en qualquer linguagem 
<route> pode ser / ou /list_articles ou /upload-articles ou /download-articles ou /upload-authors ou /download-authors ou /upload-metrics ou /

todas as ações de cli que precisem da url devem receber a url com a lang tipo vibelog.mateusmoutinho.com/pt ou vibelog.mateusmoutinho.com/en 
as ações devem ser feitas na lang especificada na url

note que você deverá refatorar o app.c com a nova lógica de lang
